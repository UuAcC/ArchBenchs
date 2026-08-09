// @file       <ipic.c>
// @brief      IPIC defs and inline funcs
//
// Copyright by Syntacore LLC © 2019. ALL RIGHTS RESERVED. STRICTLY CONFIDENTIAL.
// Information contained in this material is confidential and proprietary to Syntacore LLC
// and its affiliates and may not be modified, copied, published, disclosed, distributed,
// displayed or exhibited, in either electronic or printed formats without written
// authorization of the Syntacore LLC. Subject to License Agreement.
//

#ifndef SCR_IPIC_H
#define SCR_IPIC_H

#include <stddef.h>
#include "arch.h"
#include "plf.h"

enum intvec_config_consts {
    IRQ_PENDING    = (1 << 0),
    IRQ_CLEAR_PENDING = IRQ_PENDING,
    IRQ_ENABLE     = (1 << 1),
    IRQ_LEVEL      = (0 << 2),
    IRQ_EDGE       = (1 << 2),
    IRQ_INV        = (1 << 3),
    IRQ_MODE_MASK  = (3 << 2),

    IRQ_TYPE_EDGE_RISING = IRQ_EDGE,
    IRQ_TYPE_EDGE_FALLING = IRQ_EDGE | IRQ_INV,
    IRQ_TYPE_LEVEL_HIGH = IRQ_LEVEL,
    IRQ_TYPE_LEVEL_LOW = IRQ_LEVEL | IRQ_INV,

    IRQ_PRV_M     = 3,
    IRQ_PRV_S     = 1,

    IRQ_PRV_OFFS   = 8,
    IRQ_SACCESS    = (IRQ_PRV_S << IRQ_PRV_OFFS),
    IRQ_MACCESS    = (IRQ_PRV_M << IRQ_PRV_OFFS),
    IRQ_IN_SERVICE = (1 << 4), // RO
    IRQ_LN_OFFS    = 12,
#ifdef PLATFORM_SCR1
    IRQ_LN_NUM     = 16,
#else
    IRQ_LN_NUM     = 32,
#endif
    IRQ_LN_VOID    = IRQ_LN_NUM,

#ifdef PLATFORM_SCR1
    IRQ_VEC_NUM    = 16,
#else
    IRQ_VEC_NUM    = 32,
#endif
    IRQ_VEC_VOID   = IRQ_VEC_NUM,
};

// IPIC regs
#ifdef PRIV__1_10
#define IPIC_BASE   0xBF0
#else
#define IPIC_BASE   0x790
#endif

#define IPIC_CISV  (IPIC_BASE + 0)
#define IPIC_CICSR (IPIC_BASE + 1)
#define IPIC_IPR   (IPIC_BASE + 2)
#define IPIC_ISVR  (IPIC_BASE + 3)
#define IPIC_EOI   (IPIC_BASE + 4)
#define IPIC_SOI   (IPIC_BASE + 5)
#define IPIC_IDX   (IPIC_BASE + 6)
#define IPIC_ICSR  (IPIC_BASE + 7)

// Spike-specific: set/get ext irq lines register
#define SPIKE_IPIC_GET_LINES  0x79e
#define SPIKE_IPIC_SET_LINES  0x79f
// RTL-specific: ext irq lines control addr
#if __riscv_xlen == 64
#define RTL_SIM_IRQCTRL 0xFFFFFFFFF0000100
#else
#define RTL_SIM_IRQCTRL SC_SIM_IRQCTRL
#endif // #if __riscv_xlen == 64

#define MK_IRQ_CFG(line, flags, prv) ((flags) | ((line) << IRQ_LN_OFFS) | ((prv) << IRQ_PRV_OFFS))

static inline void irq_setup(size_t irq_num, size_t line, size_t flags)
{
    write_csr(IPIC_IDX, irq_num);
    write_csr(IPIC_ICSR, MK_IRQ_CFG(line, (flags | IRQ_CLEAR_PENDING), IRQ_PRV_M));
}

static inline void m_irq_setup(size_t irq_num, size_t line, size_t flags)
{
    write_csr(M_IPIC_IDX, irq_num);
    write_csr(M_IPIC_ICSR, MK_IRQ_CFG(line, flags, IRQ_PRV_M));
}
static inline void s_irq_setup(size_t irq_num, size_t line, size_t flags)
{
    write_csr(M_IPIC_IDX, irq_num);
    write_csr(M_IPIC_ICSR, MK_IRQ_CFG(line, flags, IRQ_PRV_S));
}

static inline void irq_reset(size_t irq_num)
{
    irq_setup(irq_num, IRQ_LN_VOID, IRQ_CLEAR_PENDING);
}

static inline size_t irq_vect_get(size_t irq_num)
{
    write_csr(IPIC_IDX, irq_num);
    return read_csr(IPIC_ICSR);
}

static inline void irq_vect_set(size_t irq_num, size_t val)
{
    write_csr(IPIC_IDX, irq_num);
    write_csr(IPIC_ICSR, val);
}

static inline void irq_soi(void)
{
    write_csr(IPIC_SOI, 0);
}

static inline void m_irq_soi(void)
{
    write_csr(M_IPIC_SOI, 0);
}

static inline void s_irq_soi(void)
{
    write_csr(S_IPIC_SOI, 0);
}

static inline void irq_eoi(void)
{
    write_csr(IPIC_EOI, 0);
}

static inline void m_irq_eoi(void)
{
    write_csr(M_IPIC_EOI, 0);
}

static inline void s_irq_eoi(void)
{
    write_csr(S_IPIC_SEOI, 0);
}

static inline void irq_enable(size_t irq_num)
{
    write_csr(IPIC_IDX, irq_num);
    size_t state = ( read_csr(IPIC_ICSR) & ~IRQ_CLEAR_PENDING ) | IRQ_ENABLE;
    write_csr(IPIC_ICSR, state);
}

static inline void irq_disable(size_t irq_num)
{
    write_csr(IPIC_IDX, irq_num);
    size_t state = read_csr(IPIC_ICSR) & ~( IRQ_ENABLE | IRQ_CLEAR_PENDING );
    write_csr(IPIC_ICSR, state);
}

static inline void irq_clear_pending(size_t irq_num)
{
    write_csr(IPIC_IDX, irq_num);
    size_t state = read_csr(IPIC_ICSR) | IRQ_CLEAR_PENDING;
    write_csr(IPIC_ICSR, state);
}

static inline size_t irq_pending(void)
{
    return read_csr(IPIC_IPR);
}

static inline size_t m_irq_pending(void)
{
    return read_csr(M_IPIC_IPR);
}

static inline size_t s_irq_pending(void)
{
    return read_csr(S_IPIC_IPR);
}

static inline size_t irq_inservice(void)
{
    return read_csr(IPIC_ISVR);
}

static inline size_t irq_current_vector(void)
{
    return read_csr(IPIC_CISV);
}

static inline size_t irq_current_get(void)
{
    return read_csr(IPIC_CICSR);
}

static inline void irq_current_set(size_t val)
{
    write_csr(IPIC_CICSR, val);
}

#define MIMPID_CSR_READ (read_csr(mimpid))

#ifndef PREDEFINED_IMPID
#define  PREDEFINED_IMPID MIMPID_CSR_READ
#endif // PREDEFINED_IMPID

static inline void irq_set_lines_state(size_t mask)
{
    write_csr(SPIKE_IPIC_SET_LINES, mask);
    ifence();
}

static inline size_t irq_get_lines_state(void)
{
    return read_csr(SPIKE_IPIC_GET_LINES);
}

#endif // SCR_IPIC_H
