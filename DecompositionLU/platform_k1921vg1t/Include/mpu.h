#ifndef __MPU__H
#define __MPU__H

#include "riscv_csr_encoding.h"
#include "plf.h"
//#include "crt_common.h"

// MPU CSRs
#define SCR_CSR_MPU_SEL  0xBC4
#define SCR_CSR_MPU_CTRL (SCR_CSR_MPU_SEL + 1)
#define SCR_CSR_MPU_ADDR (SCR_CSR_MPU_SEL + 2)
#define SCR_CSR_MPU_MASK (SCR_CSR_MPU_SEL + 3)

#define SCR_CSR_MPU_SEL_VALID_BITS_MASK     0xF

#ifdef RVS_EXT
#define SCR_CSR_MPU_CTRL_VALID_BITS_MASK        0x800303FF
#else
#define SCR_CSR_MPU_CTRL_VALID_BITS_MASK        0x8003007F
#endif


//MPU CTRL OFFSETS
#define SCR_MPU_CTRL_MT_OFF             0x10
#define SCR_MPU_CTRL_SATTR_OFF          7
#define SCR_MPU_CTRL_UATTR_OFF          4
#define SCR_MPU_CTRL_MATTR_OFF          1

#ifndef SCR_MPU_NUM_ENTRIES
#define SCR_MPU_NUM_ENTRIES             16
#endif

// MPU sel bits
// #define SCR_MPU_CTRL 0
// #define SCR_MPU_ADDR 1
// #define SCR_MPU_MASK 2
//#define SCR_MPU_SEL_ENTRY(type, index) (((index) << 2) | ((type) & 0x3))
// MPU dat bits
#define SCR_MPU_CTRL_VALID      (1 << 0)
#define SCR_MPU_CTRL_MR         (1 << 1)
#define SCR_MPU_CTRL_MW         (1 << 2)
#define SCR_MPU_CTRL_MX         (1 << 3)
#define SCR_MPU_CTRL_UR         (1 << 4)
#define SCR_MPU_CTRL_UW         (1 << 5)
#define SCR_MPU_CTRL_UX         (1 << 6)
#define SCR_MPU_CTRL_SR         (1 << 7)
#define SCR_MPU_CTRL_SW         (1 << 8)
#define SCR_MPU_CTRL_SX         (1 << 9)
#define SCR_MPU_CTRL_MT_MASK    (3 << 16)
#define SCR_MPU_CTRL_MT_WEAKLY  (0 << 16)
#define SCR_MPU_CTRL_MT_STRONG  (1 << 16)
#define SCR_MPU_CTRL_MT_CONFIG  (3 << 16)
#define SCR_MPU_CTRL_LOCK       (1 << 31)
#define SCR_MPU_CTRL_MA         (SCR_MPU_CTRL_MR | SCR_MPU_CTRL_MW | SCR_MPU_CTRL_MX)
#define SCR_MPU_CTRL_SA         (SCR_MPU_CTRL_SR | SCR_MPU_CTRL_SW | SCR_MPU_CTRL_SX)
#define SCR_MPU_CTRL_UA         (SCR_MPU_CTRL_UR | SCR_MPU_CTRL_UW | SCR_MPU_CTRL_UX)
#define SCR_MPU_CTRL_ALL        (SCR_MPU_CTRL_MA | SCR_MPU_CTRL_SA | SCR_MPU_CTRL_UA)

#define SCR_MPU_MK_ADDR(addr)   ((((addr) / 4) | ((addr) & 0x80000000) | ((addr) & 0x80000000) / 2) & 0xffffffff)
#define SCR_MPU_MK_MASK(size)   ((~((size) - 1) / 4) & 0xffffffff)

#ifndef __ASSEMBLER__

#include "arch.h"
#include <stdint.h>

//void create_mpu_region(uint32_t, uint32_t, int, uint32_t);
//void disable_mpu_region(uint32_t);
//void enable_mpu_region(uint32_t);
//uint32_t write_mpu_ctrl_region(int, uint32_t);


static inline void create_mpu_region(uint32_t sel, uint32_t addr, int mask, uint32_t ctrl)
{
    write_csr(SCR_CSR_MPU_SEL,  sel);
    if (sel != 0) write_csr(SCR_CSR_MPU_CTRL, 0);
    write_csr(SCR_CSR_MPU_ADDR, addr >> 2);
    write_csr(SCR_CSR_MPU_MASK, mask >> 2);
    write_csr(SCR_CSR_MPU_CTRL, ctrl | SCR_MPU_CTRL_VALID);
}

static inline void disable_mpu_region(uint32_t sel)
{
    write_csr(SCR_CSR_MPU_SEL, sel);
    uint32_t old_ctrl = read_csr(SCR_CSR_MPU_CTRL);
    write_csr(SCR_CSR_MPU_CTRL, (old_ctrl & ~SCR_MPU_CTRL_VALID) );
}

static inline void enable_mpu_region(uint32_t sel)
{
    uint32_t old_ctrl;
    write_csr(SCR_CSR_MPU_SEL, sel);
    old_ctrl = read_csr(SCR_CSR_MPU_CTRL);
    write_csr(SCR_CSR_MPU_CTRL, (old_ctrl | SCR_MPU_CTRL_VALID) );
}

static inline uint32_t write_mpu_ctrl_region(int sel, uint32_t attrs)
{
    uint32_t old_ctrl;
    write_csr(SCR_CSR_MPU_SEL, sel);
    old_ctrl = read_csr(SCR_CSR_MPU_CTRL);
    write_csr(SCR_CSR_MPU_CTRL, (attrs | (old_ctrl & SCR_MPU_CTRL_VALID)));

    return old_ctrl;
}

static inline void write_mpu_ctrl(uint32_t sel, uint32_t ctrl)
{
    write_csr(SCR_CSR_MPU_SEL,  sel);
    write_csr(SCR_CSR_MPU_CTRL, ctrl);
}

static inline uint32_t read_mpu_ctrl(uint32_t sel)
{
    write_csr(SCR_CSR_MPU_SEL,  sel);
    return read_csr(SCR_CSR_MPU_CTRL);
}

#else // #if !defined (__ASSEMBLY__ ) && !defined (ASM)
   .altmacro

// assembler macros

.macro _csr_write csr_reg, val
    .if \val == 0
    csrw \csr_reg, zero
    .elseif \val <= 31
    csrwi \csr_reg, \val
    .else
    li   t0, \val
    csrw \csr_reg, t0
    .endif
.endm

.macro mpu_region_update_attr idx,attr
    _csr_write SCR_CSR_MPU_SEL, \idx
    _csr_write SCR_CSR_MPU_CTRL, \attr
.endm

// setup region
.macro mpu_region_setup idx,addr,mask,attr
    mpu_region_update_attr \idx,0
    _csr_write SCR_CSR_MPU_ADDR, \addr
    _csr_write SCR_CSR_MPU_MASK, \mask
    _csr_write SCR_CSR_MPU_CTRL, \attr
.endm

//#ifdef MPU_EN
#define MPU_INIT  MPU_DEFAULT_INIT
//#endif // #ifdef _MPU_EN

#endif // #if !defined (__ASSEMBLY__) && !defined (ASM)

#endif // #ifndef __MPU__H
