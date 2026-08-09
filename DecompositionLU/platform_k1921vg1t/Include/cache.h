// @file       <cache.h>
// @brief      Syntacore SCR* framework
//             Cache subsytem defs and inline funcs
//
// Copyright by Syntacore LLC © 2021. ALL RIGHTS RESERVED. STRICTLY CONFIDENTIAL.
// Information contained in this material is confidential and proprietary to Syntacore LLC
// and its affiliates and may not be modified, copied, published, disclosed, distributed,
// displayed or exhibited, in either electronic or printed formats without written
// authorization of the Syntacore LLC. Subject to License Agreement.
//

#ifndef SCR_CACHE_H
#define SCR_CACHE_H

#include "arch.h"
#include "plf.h"

// cache control CSRs
#define SCR_CSR_CACHE_GLBL (0xBD4)
// global cache's control bits
#define CACHE_GLBL_L1I_EN           (1 << 0)
#define CACHE_GLBL_L1D_EN           (1 << 1)
#define CACHE_GLBL_L1I_FLUSH        (1 << 2)
#define CACHE_GLBL_L1D_FLUSH        (1 << 3)
#define CACHE_GLBL_L1I_NC           (1 << 4)
#define CACHE_GLBL_L1D_NC           (1 << 5)
#define CACHE_GLBL_L1I_EX           (1 << 6)
#define CACHE_GLBL_L1D_EX           (1 << 7)
#define CACHE_GLBL_CLIU_EN          (1 << 16)
#define CACHE_GLBL_CLFU_EN          (1 << 17)

//#define CACHE_GLBL_ENABLE           (CACHE_GLBL_L1I_EN | CACHE_GLBL_L1D_EN | CACHE_GLBL_L1I_EX | CACHE_GLBL_L1D_EX)
#define CACHE_GLBL_ENABLE           (CACHE_GLBL_L1I_EN | CACHE_GLBL_L1D_EN)
#define CACHE_GLBL_DISABLE          (0)
#define CACHE_GLBL_NC               (CACHE_GLBL_L1I_NC | CACHE_GLBL_L1D_NC)
#define CACHE_GLBL_FLUSH            (CACHE_GLBL_L1I_FLUSH | CACHE_GLBL_L1D_FLUSH)

#ifndef SYS_CACHE_CFG
#define SYS_CACHE_CFG               (CACHE_GLBL_ENABLE)
#endif

// cache support
#ifndef PLF_CACHELINE_SIZE
#define PLF_CACHELINE_SIZE 16
#endif

// instruction: clinv <regn> (cache line invalidate)
#define ENC_CLINV(regn) (0x10800073 | (((regn) & 0x1f) << 15))
// instruction: clflush <regn> (cache line flush & invalidate)
#define ENC_CLFLUSH(regn) (0x10900073 | (((regn) & 0x1f) << 15))

// L2$ registers
#ifdef PLF_L2CTL_BASE
#define L2_CSR_VER_IDX      (0)
#define L2_CSR_DESCR_IDX    (1)
#define L2_CSR_EN_IDX       (4)
#define L2_CSR_FLUSH_IDX    (5)
#define L2_CSR_INV_IDX      (6)

#define L2_CSR_ERR_ST0_IDX  (32)
#define L2_CSR_ERR_ST1_IDX  (34)
#define L2_CSR_ERR_ST2_IDX  (35)
#define L2_CSR_ERR_EN_IDX   (36)

#define L2_CSR_MAU_RERR_ADDR_IDX   (64)
#define L2_CSR_MAU_BERR_ADDR_IDX   (68)
#define L2_CSR_NCAU_RERR_ADDR_IDX  (72)
#define L2_CSR_NCAU_BERR_ADDR_IDX  (76)
#define L2_CSR_MAU_RERR_CODE_IDX   (80)
#define L2_CSR_MAU_BERR_CODE_IDX   (84)
#define L2_CSR_NCAU_RERR_CODE_IDX  (88)
#define L2_CSR_NCAU_BERR_CODE_IDX  (92)
#define L2_CSR_SNOOP_ERR_IDX       (96)

#define L2_CSR_ECC_ERR_TAG_MEM_ST_B0_IDX   (128)
#define L2_CSR_ECC_ERR_TAG_MEM_ST_B1_IDX   (129)
#define L2_CSR_ECC_ERR_TAG_MEM_ST_B2_IDX   (130)
#define L2_CSR_ECC_ERR_TAG_MEM_ST_B3_IDX   (131)
#define L2_CSR_ECC_ERR_DATA_MEM_ST_B0_IDX  (192)
#define L2_CSR_ECC_ERR_DATA_MEM_ST_B1_IDX  (193)
#define L2_CSR_ECC_ERR_DATA_MEM_ST_B2_IDX  (194)
#define L2_CSR_ECC_ERR_DATA_MEM_ST_B3_IDX  (195)

#define L2_CSR_SWERR_CNTR_EN_IDX    (320)
#define L2_CSR_SWERR_CNTR_OVFL_IDX  (321)
#define L2_CSR_SWERR_CNTR_THLD_IDX  (322)
#define L2_CSR_SWERR_CNTR_SEL_IDX   (323)
#define L2_CSR_SWERR_CNTR_IDX       (324)

#define L2_CSR_VER_OFFS     (L2_CSR_VER_IDX * 4)
#define L2_CSR_DESCR_OFFS   (L2_CSR_DESCR_IDX * 4)
#define L2_CSR_EN_OFFS      (L2_CSR_EN_IDX * 4)
#define L2_CSR_FLUSH_OFFS   (L2_CSR_FLUSH_IDX * 4)
#define L2_CSR_INV_OFFS     (L2_CSR_INV_IDX * 4)

#define L2_CSR_VER          (PLF_L2CTL_BASE + L2_CSR_VER_OFFS)
#define L2_CSR_DESCR        (PLF_L2CTL_BASE + L2_CSR_DESCR_OFFS)
#define L2_CSR_EN           (PLF_L2CTL_BASE + L2_CSR_FLUSH_OFFS)
#define L2_CSR_FLUSH        (PLF_L2CTL_BASE + L2_CSR_FLUSH_OFFS)
#define L2_CSR_INV          (PLF_L2CTL_BASE + L2_CSR_INV_OFFS)

#define L2_CSR_DESCR_L2WAYS_OFFS    (0)
#define L2_CSR_DESCR_L2WAYS_MASK    (0x7)
#define L2_CSR_DESCR_L2LINE_OFFS    (4)
#define L2_CSR_DESCR_L2LINE_MASK    (0xF)
#define L2_CSR_DESCR_L2WIDTH_OFFS   (8)
#define L2_CSR_DESCR_L2WIDTH_MASK   (0x1F)

#define L2_VER_ADDR                         (PLF_L2CTL_BASE + 0x0)
#define L2_DESC0_ADDR                       (PLF_L2CTL_BASE + 0x4)
#define L2_DESC1_ADDR                       (PLF_L2CTL_BASE + 0x8)
#define L2_CACHE_EN_ADDR                    (PLF_L2CTL_BASE + 0x10)
#define L2_CACHE_FLUSH_ADDR                 (PLF_L2CTL_BASE + 0x14)
#define L2_CACHE_INVALIDATE_ADDR            (PLF_L2CTL_BASE + 0x18)
#define L2_CACHE_EN_DENIED_STS_ADDR         (PLF_L2CTL_BASE + 0x20)
#define L2_CACHE_FLUSH_DENIED_STS_ADDR      (PLF_L2CTL_BASE + 0x20)

#define L2_CACHE_EN_ALL_BANKS_MASK          (0xF)

#endif // PLF_L2CTL_BASE

//#if !defined (__ASSEMBLY__ ) && !defined (ASM)
#ifndef __ASSEMBLER__

static inline void l1_enable(void)
{
    asm volatile (
        ".equiv CACHE_EN_VAL, "XSTRINGIFY((SYS_CACHE_CFG | CACHE_GLBL_FLUSH))";"
        "li a0, CACHE_EN_VAL;"
        "csrw "XSTRINGIFY(SCR_CSR_CACHE_GLBL)", a0;"
        :::"a0");
}

static inline void l1_disable(void)
{
    asm volatile (
        "csrw "XSTRINGIFY(SCR_CSR_CACHE_GLBL)", zero;"
        :::);
}

__attribute__((always_inline))
static inline void cache_invalidate(void *vaddr, unsigned size)
{
    if (!size)
        return;

    register size_t a0 asm("a0") = (size_t)vaddr;
    a0 &= -PLF_CACHELINE_SIZE;
    /* Invalidate the cache for the requested range */
    for (; a0 < (size_t)vaddr + size; a0 += PLF_CACHELINE_SIZE) {
        asm volatile (".word %0" :: "i"(ENC_CLINV(10)), "r"(a0) : "memory");
    }
}

__attribute__((always_inline))
static inline void cache_flush(void *vaddr, unsigned size)
{
    if (!size)
        return;

    asm volatile ("fence" ::: "memory");
    register size_t a0 asm("a0") = (size_t)vaddr;
    a0 &= -PLF_CACHELINE_SIZE;
    /* Flush the cache for the requested range */
    for (; a0 < (size_t)vaddr + size; a0 += PLF_CACHELINE_SIZE) {
        asm volatile (".word %0" :: "i"(ENC_CLFLUSH(10)), "r"(a0) : "memory");
    }
    asm volatile ("fence" ::: "memory");
}


static inline void scr_l2cache_enable(void)
{
#if PLF_L2C_BANKS
    // init L2$: disable, confirm  state, invalidate, confirm, enable, confirm
    volatile uint32_t *l2ctl = (uint32_t*)PLF_L2CTL_BASE;
    uint32_t cbmask;

    if (!l2ctl[L2_CSR_VER_IDX])
        return; // cache not exists or not supported

    cbmask = (1 << (((l2ctl[L2_CSR_DESCR_IDX] >> 16) & 0xf) + 1)) - 1;

    // disable L2$
    l2ctl[L2_CSR_EN_IDX] = 0;
    // confirm state
    while (l2ctl[L2_CSR_EN_IDX]);
    // invalidate
    l2ctl[L2_CSR_INV_IDX] = cbmask;
    // confirm state
    while (l2ctl[L2_CSR_INV_IDX]);
    // enable
    l2ctl[L2_CSR_EN_IDX] = cbmask;
    // confirm state
    while (l2ctl[L2_CSR_EN_IDX] != cbmask);
#endif // PLF_L2C_BANKS
}

static inline void scr_l2cache_flush(void)
{
#if PLF_L2C_BANKS
    volatile uint32_t *l2ctl = (uint32_t*)PLF_L2CTL_BASE;

    l2ctl[L2_CSR_FLUSH_IDX] = -1;
    // confirm state
    while (l2ctl[L2_CSR_FLUSH_IDX]);
#endif // PLF_L2C_BANKS
}

static inline void scr_l2cache_inv(void)
{
#if PLF_L2C_BANKS
    volatile uint32_t *l2ctl = (uint32_t*)PLF_L2CTL_BASE;

    l2ctl[L2_CSR_INV_IDX] = -1;
    // confirm state
    while (l2ctl[L2_CSR_INV_IDX]);
#endif // PLF_L2C_BANKS
}

static inline void scr_l2cache_disable(void)
{
#if PLF_L2C_BANKS
    volatile uint32_t *l2ctl = (uint32_t*)PLF_L2CTL_BASE;

    if (!l2ctl[L2_CSR_VER_IDX])
        return; // cache not exists or not supported

#ifdef PLF_OCRAM_BASE
    cache_flush((void*)PLF_OCRAM_BASE, PLF_OCRAM_SIZE);
#endif  /// #ifdef PLF_OCRAM_BASE 
    // disable
    l2ctl[L2_CSR_EN_IDX] = 0;
    // confirm state
    while (l2ctl[L2_CSR_EN_IDX]);
    // flush overall
    l2ctl[L2_CSR_FLUSH_IDX] = ~0;
    // confirm state
    while (l2ctl[L2_CSR_FLUSH_IDX]);
    // invalidate
    l2ctl[L2_CSR_INV_IDX] = ~0;
    // confirm state
    while (l2ctl[L2_CSR_INV_IDX]);
#endif // PLF_L2C_BANKS
}

static inline bool scr_l2cache_is_enabled(void)
{
#if PLF_L2C_BANKS
    volatile uint32_t *l2ctl = (uint32_t*)PLF_L2CTL_BASE;

    return l2ctl[L2_CSR_VER_IDX] && l2ctl[L2_CSR_EN_IDX];
#else
    return false;
#endif // PLF_L2C_BANKS
}

// GAS macro: custom op
// clflush <reg> (cache line flush & invalidate)
asm (".macro clflush reg;"
     "__scr_reg2num \\reg;"
     ".word 0x10900073 + (__scr_macro_regn << 15);"
     ".endm;"
    );

// GAS macro: custom op
// clinvd <reg> (cache line invalidate)
asm (".macro clinvd reg;"
     "__scr_reg2num \\reg;"
     ".word 0x10800073 + (__scr_macro_regn << 15);"
     ".endm;"
    );


static inline void scr_l2cache_init(void)
{
    scr_l2cache_enable();
}

#else  /// #if !defined (__ASSEMBLY__ ) && !defined (ASM) #ifndef __ASSEMBLER__
 // GAS macro: convert symbolic register names to numbers
.macro __scr_reg2num reg_name
    .ifc \reg_name, x0;.set __scr_macro_regn,0;.endif
    .ifc \reg_name, x1;.set __scr_macro_regn,1;.endif
    .ifc \reg_name, x2;.set __scr_macro_regn,2;.endif
    .ifc \reg_name, x3;.set __scr_macro_regn,3;.endif
    .ifc \reg_name, x4;.set __scr_macro_regn,4;.endif
    .ifc \reg_name, x5;.set __scr_macro_regn,5;.endif
    .ifc \reg_name, x6;.set __scr_macro_regn,6;.endif
    .ifc \reg_name, x7;.set __scr_macro_regn,7;.endif
    .ifc \reg_name, x8;.set __scr_macro_regn,8;.endif
    .ifc \reg_name, x9;.set __scr_macro_regn,9;.endif
    .ifc \reg_name, x10;.set __scr_macro_regn,10;.endif
    .ifc \reg_name, x11;.set __scr_macro_regn,11;.endif
    .ifc \reg_name, x12;.set __scr_macro_regn,12;.endif
    .ifc \reg_name, x13;.set __scr_macro_regn,13;.endif
    .ifc \reg_name, x14;.set __scr_macro_regn,14;.endif
    .ifc \reg_name, x15;.set __scr_macro_regn,15;.endif
    .ifc \reg_name, x16;.set __scr_macro_regn,16;.endif
    .ifc \reg_name, x17;.set __scr_macro_regn,17;.endif
    .ifc \reg_name, x18;.set __scr_macro_regn,18;.endif
    .ifc \reg_name, x19;.set __scr_macro_regn,19;.endif
    .ifc \reg_name, x20;.set __scr_macro_regn,20;.endif
    .ifc \reg_name, x21;.set __scr_macro_regn,21;.endif
    .ifc \reg_name, x22;.set __scr_macro_regn,22;.endif
    .ifc \reg_name, x23;.set __scr_macro_regn,23;.endif
    .ifc \reg_name, x24;.set __scr_macro_regn,24;.endif
    .ifc \reg_name, x25;.set __scr_macro_regn,25;.endif
    .ifc \reg_name, x26;.set __scr_macro_regn,26;.endif
    .ifc \reg_name, x27;.set __scr_macro_regn,27;.endif
    .ifc \reg_name, x28;.set __scr_macro_regn,28;.endif
    .ifc \reg_name, x29;.set __scr_macro_regn,29;.endif
    .ifc \reg_name, x30;.set __scr_macro_regn,30;.endif
    .ifc \reg_name, x31;.set __scr_macro_regn,31;.endif

    .ifc \reg_name, zero;.set __scr_macro_regn,0;.endif
    .ifc \reg_name, ra;.set __scr_macro_regn,1;.endif
    .ifc \reg_name, sp;.set __scr_macro_regn,2;.endif
    .ifc \reg_name, gp;.set __scr_macro_regn,3;.endif
    .ifc \reg_name, tp;.set __scr_macro_regn,4;.endif
    .ifc \reg_name, t0;.set __scr_macro_regn,5;.endif
    .ifc \reg_name, t1;.set __scr_macro_regn,6;.endif
    .ifc \reg_name, t2;.set __scr_macro_regn,7;.endif
    .ifc \reg_name, s0;.set __scr_macro_regn,8;.endif
    .ifc \reg_name, fp;.set __scr_macro_regn,8;.endif
    .ifc \reg_name, s1;.set __scr_macro_regn,9;.endif
    .ifc \reg_name, a0;.set __scr_macro_regn,10;.endif
    .ifc \reg_name, a1;.set __scr_macro_regn,11;.endif
    .ifc \reg_name, a2;.set __scr_macro_regn,12;.endif
    .ifc \reg_name, a3;.set __scr_macro_regn,13;.endif
    .ifc \reg_name, a4;.set __scr_macro_regn,14;.endif
    .ifc \reg_name, a5;.set __scr_macro_regn,15;.endif
    .ifc \reg_name, a6;.set __scr_macro_regn,16;.endif
    .ifc \reg_name, a7;.set __scr_macro_regn,17;.endif
    .ifc \reg_name, s2;.set __scr_macro_regn,18;.endif
    .ifc \reg_name, s3;.set __scr_macro_regn,19;.endif
    .ifc \reg_name, s4;.set __scr_macro_regn,20;.endif
    .ifc \reg_name, s5;.set __scr_macro_regn,21;.endif
    .ifc \reg_name, s6;.set __scr_macro_regn,22;.endif
    .ifc \reg_name, s7;.set __scr_macro_regn,23;.endif
    .ifc \reg_name, s8;.set __scr_macro_regn,24;.endif
    .ifc \reg_name, s9;.set __scr_macro_regn,25;.endif
    .ifc \reg_name, s10;.set __scr_macro_regn,26;.endif
    .ifc \reg_name, s11;.set __scr_macro_regn,27;.endif
    .ifc \reg_name, t3;.set __scr_macro_regn,28;.endif
    .ifc \reg_name, t4;.set __scr_macro_regn,29;.endif
    .ifc \reg_name, t5;.set __scr_macro_regn,30;.endif
    .ifc \reg_name, t6;.set __scr_macro_regn,31;.endif
.endm
// GAS macro: custom op: clflush reg
.macro clflush reg
    __scr_reg2num \reg
    .word 0x10900073 + (__scr_macro_regn << 15)
    .endm
// GAS macro: custom op: clinvd reg
.macro clinvd reg
    __scr_reg2num \reg
    .word 0x10800073 + (__scr_macro_regn << 15)
.endm

.macro cache_l1l2_flush addr, size
#if PLF_CACHELINE_SIZE
1:  clflush \addr
    addi \size, \size, -PLF_CACHELINE_SIZE
    addi \addr, \addr, PLF_CACHELINE_SIZE
    bgez \size, 1b
#endif // PLF_CACHELINE_SIZE
.endm // cache_l1l2_flush

.macro l2_flush
    li   t1, PLF_L2CTL_BASE
    li   t2, -1
    sw   t2, L2_CSR_FLUSH_OFFS(t1)
1:  lw   t0, L2_CSR_FLUSH_OFFS(t1)
    bnez t0, 1b
.endm
/*
.macro asm_cache_flush 
    li   a3,t1
    fence
    li   a4,t0
// a0 &= -PLF_CACHELINE_SIZE;
    andi a0,a4,-16
// for (; a0 < (size_t)vaddr + size; a0 += PLF_CACHELINE_SIZE) {
    j   __afe
__af8: .word 0x10950073
    addi a0,a0,16
__afe:
    add  a5,a3,a4
    bltu a0,a5,__af8
    fence
.endm
*/
// init L2$: disable, confirm  state, invalidate, confirm, enable, confirm
.macro cache_l2_init
#if PLF_L2C_BANKS
    LOCAL l2cache_wait_dis, l2cache_wait_inv, l2cache_wait_en, l2cache_init_done
    li   t1, PLF_L2CTL_BASE
    lw   t0, L2_CSR_VER_OFFS(t1)
    beqz t0, l2cache_init_done
    // calc L2banks' mask
    lw   t2, L2_CSR_DESCR_OFFS(t1)
    srli t2, t2, 16
    andi t2, t2, 0xf
    addi t2, t2, 1
    li   t0, 1
    sll  t2, t0, t2
    addi t2, t2, -1
    // disable all banks
    sw   zero, L2_CSR_EN_OFFS(t1)
l2cache_wait_dis:
    fence
    lw   t0, L2_CSR_EN_OFFS(t1)
    bnez t0, l2cache_wait_dis
    // invalidate all banks
    sw   t2, L2_CSR_INV_OFFS(t1)
l2cache_wait_inv:
    lw   t0, L2_CSR_INV_OFFS(t1)
    bnez t0, l2cache_wait_inv

#ifndef PLF_L2C_DISABLE
    // enable all banks
    sw   t2, L2_CSR_EN_OFFS(t1)
l2cache_wait_en:
    lw   t0, L2_CSR_EN_OFFS(t1)
    bne  t0, t2, l2cache_wait_en
#endif // PLF_L2C_DISABLE
    fence.i
l2cache_init_done:
#endif // PLF_L2C_BANKS
.endm // cache_l2_init

#endif  // #else #if !defined (__ASSEMBLY__ ) && !defined (ASM) #ifndef __ASSEMBLER__

#endif // SCR_CACHE_H
