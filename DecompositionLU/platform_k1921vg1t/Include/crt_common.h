#ifndef __CRT__COMMON__H
#define __CRT__COMMON__H

#include "common_asm.h"
#include "plf.h"


#ifndef MPU_DEFAULT_CTRL
#define MPU_DEFAULT_CTRL        (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL | SCR_MPU_CTRL_VALID)
#endif // #ifndef MPU_DEFAULT_CTRL

#ifndef MPU_REGION_MMCFG_CTRL
#define MPU_REGION_MMCFG_CTRL   (SCR_MPU_CTRL_MT_CONFIG | SCR_MPU_CTRL_MR | SCR_MPU_CTRL_MW | SCR_MPU_CTRL_VALID)
#endif  // #ifndef MPU_REGION_MMCFG_CTRL

#ifndef MPU_REGION_MMIO_CTRL
#define MPU_REGION_MMIO_CTRL    (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL | SCR_MPU_CTRL_VALID)
#endif  // #ifndef MPU_REGION_MMIO_CTRL


#ifdef REGION_PLIC_ADDR
#define REGION_PLIC_SETUP                   \
    csrw    SCR_CSR_MPU_SEL, 3;             \
    csrw    SCR_CSR_MPU_CTRL, zero;         \
    li      t0, (REGION_PLIC_ADDR);         \
    srai    t0, t0, 2;                      \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (REGION_PLIC_MASK);         \
    srai    t0, t0, 2;                      \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else 
#define REGION_PLIC_SETUP 
#endif

#ifdef PLF_PERIPH_BASE
#define MPU_PERIPH_REGION_SETUP             \
    csrw    SCR_CSR_MPU_SEL, 4;             \
    li      t0, (PLF_PERIPH_BASE >> 2);     \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_PERIPH_MASK >> 2);     \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_PERIPH_REGION_SETUP 
#endif

#ifdef PLF_EXT_BASE
#define MPU_EXT_REGION_SETUP                \
    csrw    SCR_CSR_MPU_SEL, 6;             \
    li      t0, (PLF_EXT_BASE >> 2);        \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_EXT_MASK >> 2);        \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_EXT_REGION_SETUP 
#endif

#ifdef PLF_SDRAM_BASE
#define MPU_SDRAM_REGION_SETUP              \
    csrw    SCR_CSR_MPU_SEL, 7;             \
    li      t0, (PLF_SDRAM_BASE >> 2);      \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_SDRAM_MASK >> 2);      \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_SDRAM_REGION_SETUP 
#endif

#ifdef PLF_QSPI0_BASE
#define MPU_QSPI0_REGION_SETUP              \
    csrw    SCR_CSR_MPU_SEL, 8;             \
    li      t0, (PLF_QSPI0_BASE >> 2);      \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_QSPI0_MASK >> 2);      \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_QSPI0_REGION_SETUP 
#endif

#ifdef PLF_QSPI1_BASE
#define MPU_QSPI1_REGION_SETUP              \
    csrw    SCR_CSR_MPU_SEL, 9;             \
    li      t0, (PLF_QSPI1_BASE >> 2);      \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_QSPI1_MASK >> 2);      \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_QSPI1_REGION_SETUP 
#endif

#ifdef PLF_FLASH_BASE
#define MPU_FLASH_REGION_SETUP              \
    csrw    SCR_CSR_MPU_SEL, 0;             \
    li      t0, (PLF_FLASH_BASE >> 2);      \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_FLASH_MASK >> 2);      \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_FLASH_REGION_SETUP 
#endif

#ifdef PLF_SRAM_BASE
#define MPU_SRAM_REGION_SETUP               \
    csrw    SCR_CSR_MPU_SEL, 5;             \
    li      t0, (PLF_SRAM_BASE >> 2);       \
    csrw    SCR_CSR_MPU_ADDR, t0;           \
    li      t0, (PLF_SRAM_MASK >> 2);       \
    csrw    SCR_CSR_MPU_MASK, t0;           \
    li      t0, (MPU_DEFAULT_CTRL);         \
    csrw    SCR_CSR_MPU_CTRL, t0;           \
    fence.i;
#else
#define MPU_SRAM_REGION_SETUP 
#endif

#define MPU_ZERO_REGION_OFF                 \
    csrw    SCR_CSR_MPU_SEL, 0;             \
    csrw    SCR_CSR_MPU_CTRL, zero;         \
    fence.i;


#define MPU_DEFAULT_INIT                 \
    MPU_FLASH_REGION_SETUP;              \
    csrw    SCR_CSR_MPU_SEL, 1;          \
    csrw    SCR_CSR_MPU_CTRL, zero;      \
    li      t0, (REGION_MMCFG_BASE >> 2);   \
    csrw    SCR_CSR_MPU_ADDR, t0;        \
    li      t0, (REGION_MMCFG_MASK >> 2);   \
    csrw    SCR_CSR_MPU_MASK, t0;        \
    li      t0, (MPU_REGION_MMCFG_CTRL); \
    csrw    SCR_CSR_MPU_CTRL, t0;        \
    csrw    SCR_CSR_MPU_SEL, 2;          \
    csrw    SCR_CSR_MPU_CTRL, zero;      \
    li      t0, (REGION_MMIO_ADDR >> 2); \
    csrw    SCR_CSR_MPU_ADDR, t0;        \
    li      t0, (REGION_MMIO_MASK >> 2); \
    csrw    SCR_CSR_MPU_MASK, t0;        \
    li      t0, (MPU_REGION_MMIO_CTRL);  \
    csrw    SCR_CSR_MPU_CTRL, t0;        \
    fence.i;                             \
    REGION_PLIC_SETUP;                   \
    MPU_PERIPH_REGION_SETUP;             \
    MPU_SRAM_REGION_SETUP;               \
    MPU_EXT_REGION_SETUP;                \
    MPU_SDRAM_REGION_SETUP;              \
    MPU_QSPI0_REGION_SETUP;              \
    MPU_QSPI1_REGION_SETUP;              \
    li t5, 16;                           \
    li      t4, MPU_LAST_ENTRY;          \
1:  csrw    SCR_CSR_MPU_SEL, t4;         \
    csrw    SCR_CSR_MPU_ADDR, x0;        \
    csrw    SCR_CSR_MPU_MASK, x0;        \
    csrw    SCR_CSR_MPU_CTRL, x0;        \
    addi    t4, t4, 1;                   \
    bne     t4, t5, 1b;                  \
    fence.i;

#define SAVE_CTX_1_15           \
    addi sp, sp, -272;          \
    SREG x1, 1*REGBYTES(sp);    \
    addi x1, sp, 272;           \
    SREG x1, 2*REGBYTES(sp);    \
    SREG x3, 3*REGBYTES(sp);    \
    SREG x4, 4*REGBYTES(sp);    \
    SREG x5, 5*REGBYTES(sp);    \
    SREG x6, 6*REGBYTES(sp);    \
    SREG x7, 7*REGBYTES(sp);    \
    SREG x8, 8*REGBYTES(sp);    \
    SREG x9, 9*REGBYTES(sp);    \
    SREG x10, 10*REGBYTES(sp);  \
    SREG x11, 11*REGBYTES(sp);  \
    SREG x12, 12*REGBYTES(sp);  \
    SREG x13, 13*REGBYTES(sp);  \
    SREG x14, 14*REGBYTES(sp);  \
    SREG x15, 15*REGBYTES(sp);

#define SAVE_CTX_16_31          \
    SREG x16, 16*REGBYTES(sp);  \
    SREG x17, 17*REGBYTES(sp);  \
    SREG x18, 18*REGBYTES(sp);  \
    SREG x19, 19*REGBYTES(sp);  \
    SREG x20, 20*REGBYTES(sp);  \
    SREG x21, 21*REGBYTES(sp);  \
    SREG x22, 22*REGBYTES(sp);  \
    SREG x23, 23*REGBYTES(sp);  \
    SREG x24, 24*REGBYTES(sp);  \
    SREG x25, 25*REGBYTES(sp);  \
    SREG x26, 26*REGBYTES(sp);  \
    SREG x27, 27*REGBYTES(sp);  \
    SREG x28, 28*REGBYTES(sp);  \
    SREG x29, 29*REGBYTES(sp);  \
    SREG x30, 30*REGBYTES(sp);  \
    SREG x31, 31*REGBYTES(sp);

#define RESTORE_CTX_1_15        \
    LREG x1, 1*REGBYTES(sp);    \
    LREG x3, 3*REGBYTES(sp);    \
    LREG x4, 4*REGBYTES(sp);    \
    LREG x5, 5*REGBYTES(sp);    \
    LREG x6, 6*REGBYTES(sp);    \
    LREG x7, 7*REGBYTES(sp);    \
    LREG x8, 8*REGBYTES(sp);    \
    LREG x9, 9*REGBYTES(sp);    \
    LREG x10, 10*REGBYTES(sp);  \
    LREG x11, 11*REGBYTES(sp);  \
    LREG x12, 12*REGBYTES(sp);  \
    LREG x13, 13*REGBYTES(sp);  \
    LREG x14, 14*REGBYTES(sp);  \
    LREG x15, 15*REGBYTES(sp); \

#define RESTORE_CTX_16_31       \
    LREG x16, 16*REGBYTES(sp);  \
    LREG x17, 17*REGBYTES(sp);  \
    LREG x18, 18*REGBYTES(sp);  \
    LREG x19, 19*REGBYTES(sp);  \
    LREG x20, 20*REGBYTES(sp);  \
    LREG x21, 21*REGBYTES(sp);  \
    LREG x22, 22*REGBYTES(sp);  \
    LREG x23, 23*REGBYTES(sp);  \
    LREG x24, 24*REGBYTES(sp);  \
    LREG x25, 25*REGBYTES(sp);  \
    LREG x26, 26*REGBYTES(sp);  \
    LREG x27, 27*REGBYTES(sp);  \
    LREG x28, 28*REGBYTES(sp);  \
    LREG x29, 29*REGBYTES(sp);  \
    LREG x30, 30*REGBYTES(sp);  \
    LREG x31, 31*REGBYTES(sp);
    

#ifdef RVE_EXT 

#define SAVE_CTX        SAVE_CTX_1_15
#define RESTORE_CTX     RESTORE_CTX_1_15; LREG x2, 2*REGBYTES(sp);

#else // #ifdef RVE_EXT

#define SAVE_CTX        SAVE_CTX_1_15; \
                        SAVE_CTX_16_31;

#define RESTORE_CTX     RESTORE_CTX_1_15; \
                        RESTORE_CTX_16_31; LREG x2, 2*REGBYTES(sp);

#endif // #else #ifdef RVE_EXT


#define MTIMER_100MHZ_INIT         \
/* init timer for 100MHz clock */  \
    li  t0, 99;                    \
    li  t1, TIMER_ADDR;            \
    sw  t0, 0x04(t1);              \
    li      t0, MEM_MTIMECMP;      \
    li      t1, -1;                \
    sw      t1, (t0);              \
    sw      t1, 4(t0);


#endif  // #ifndef CRT_COMMON_H
