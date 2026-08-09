### Syntacore SCR* infra
###
### @copyright (C) Syntacore 2015-2020. All rights reserved.
### @author mn-sc
###
### @brief SCR* infra startup code
###
### Build flags:
###   USE_DUALCORE       - original dual-core mode (IPI wake, shared stack)
###   USE_DUALCORE_SMP   - FreeRTOS SMP mode (polling wake, separate stacks,
###                        FreeRTOS trap handler)

#include "arch.h"
#include "cache.h"
#include "ipi.h"
#include "memasm.h"
#include "common_asm.h"
#include "mpu.h"
#include "crt_common.h"

#define PLF_SMP_HART_NUM 2

##-----------------------------------------------------------------------------------------
## startup code

    .globl _start, main, exit, abort, trap_handler, trap_entry, _hart_halt
    .globl slave_hart_start, plf_init, app_init

#if defined(USE_DUALCORE) || defined(USE_DUALCORE_SMP)
    .globl slave_main_loop
    .weak  slave_main_loop
#endif

#ifdef USE_DUALCORE_SMP
    .globl g_core1_marker
    .extern freertos_risc_v_trap_handler
    .extern xCore1CanStart
#else
    .globl hart_start_table, slave_main
#endif

    .weak exit, abort, trap_entry, trap_handler, app_init

    .option norvc

    .section ".startup.entry","ax",@progbits

##-----------------------------------------------------------------------------------------
## Entry point
_start:
    ## reset mstatus
    csrw  mstatus, zero
    zero_int_regs 1,31

    ## setup gp
    load_addrword_abs gp, __global_pointer$

    ## setup MTVEC
#ifdef USE_DUALCORE_SMP
    la    t0, freertos_risc_v_trap_handler
    csrw  mtvec, t0
#else
    load_addrword_abs t0, trap_entry
    csrw  mtvec, t0
#endif

    ## setup MIE, MIP
    csrw  mie, zero
    csrw  mip, zero

    ## prepare disabling of caches: flush init sections
    load_addrword_pcrel t0, __TEXT_INIT_START__
    load_const_int32 t1, __TEXT_INIT_SIZE__
    cache_l1l2_flush t0, t1

    ## init FPU (if supported)
    csrr  a0, misa
    andi  a0, a0, (1 << ('F' - 'A')) | (1 << ('D' - 'A'))
    beqz  a0, 1f
    li    a0, (1 << 13)
    csrs  mstatus, a0
    csrw  fcsr, zero
    zero_f_regs 0, 31
    fsflags zero, zero
    fsrm zero, zero
1:

    ## MPU setup
    MPU_DEFAULT_INIT

    ## park/prep SMP slaves
    csrr  a0, mhartid
    bnez  a0, slave_hart_start

    ## init HART#0 sp, tp
    load_addrword_abs sp, __TLS0_BASE__
    mv    tp, sp
    csrw  mscratch, sp

    ## platform init
    load_addrword t0, plf_init
    jalr  t0

    ## application-specific initialization hook
    load_addrword t0, app_init
    jalr  t0

    ## main() args
    li    a0, 0
    li    a1, 0

    ## start main
    load_addrword t0, main
    load_addrword ra, exit
    jr    t0

##-----------------------------------------------------------------------------------------
trap_handler:
_hart_halt:
    ## disable interrupts
    csrci mstatus, 0xf
    csrw  mie, zero
1:  wfi
    j     1b

exit:
    nop

abort:
    j     _hart_halt

##-----------------------------------------------------------------------------------------
## Slave hart entry
##-----------------------------------------------------------------------------------------
slave_hart_start:

#ifdef USE_DUALCORE_SMP
    ## ---- FreeRTOS SMP mode ----

    ## Set FreeRTOS trap handler for Core 1
    la    t0, freertos_risc_v_trap_handler
    csrw  mtvec, t0

    ## Re-init MPU on Core 1
    MPU_DEFAULT_INIT

    ## Park unsupported harts
    li    a1, PLF_SMP_HART_NUM
    bgeu  a0, a1, _hart_halt

    ## Init Core 1 stack (separate region)
    load_addrword_abs sp, __stack_top_c1__
    mv    tp, sp
    csrw  mscratch, sp

    ## Poll xCore1CanStart (set by xPortStartScheduler on Core 0)
smp_wait_kick:
    fence
    la    t1, xCore1CanStart
    lw    t0, 0(t1)
    beqz  t0, smp_wait_kick

    ## Jump to FreeRTOS secondary core entry
    load_addrword t0, slave_main_loop
    jr    t0

#else
    ## ---- Original mode ----

    ## Park unsupported harts
    li    a1, PLF_SMP_HART_NUM
    bgeu  a0, a1, _hart_halt

    ## Init HART#N sp, tp (shared stack region with offset)
    load_addrword_abs sp, __TLS0_BASE__
    slli  a0, a0, 12
    sub   sp, sp, a0
    mv    tp, sp
    csrw  mscratch, sp

    ## Wait for master IPI cmd
1:
    csrrwi a1, SCR_CSR_IPI_MRDATA, 1
    bltz  a1, 1b

    ## Start slave
    li    a0, 0
    li    a1, 0
#ifdef USE_DUALCORE
    load_addrword t0, slave_main_loop
#else
    load_addrword t0, main
#endif
    load_addrword ra, exit
    jr    t0

#endif /* USE_DUALCORE_SMP */

##-----------------------------------------------------------------------------------------
## Data
##-----------------------------------------------------------------------------------------
#ifdef USE_DUALCORE_SMP
    .section .data
    .align 4
g_core1_marker:
    .word 0
#endif

##-----------------------------------------------------------------------------------------
## Stubs
    .section ".startup.entry","ax",@progbits
app_init:
    ret

##-----------------------------------------------------------------------------------------
## Trap entry
    .section ".text.crt.trap_entry","ax",@progbits
    .align 6
    .type trap_entry, @function
trap_entry:
#ifdef USE_DUALCORE_SMP
    ## FreeRTOS SMP: redirect to FreeRTOS handler
    j freertos_risc_v_trap_handler
#else
    ## Original: save context, call trap_handler, restore
    context_save
    csrr s0, mstatus
    csrr a0, mcause
    csrr a1, mepc
    mv   a2, sp
    load_addrword_abs gp, __global_pointer$
    load_addrword t0, trap_handler
    jalr t0
    csrw mstatus, s0
    context_restore
    mret
#endif
    .size trap_entry, .-trap_entry
