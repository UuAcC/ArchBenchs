/// @file
/// @brief atomic operations
///
/// @copyright Syntacore, 2015-2017. All rights reserved.
///
/// Syntacore SCR* test
/// @author Mikhail Nefedov <mikhail.nefedov@syntacore.com>
///

#ifndef SCR_ATOMIC_H
#define SCR_ATOMIC_H

#include "cache.h"
#include <stdio.h>


typedef struct {
    volatile size_t lock;
} t_arch_spinlock;

#define __ARCH_SPIN_LOCK_UNLOCKED	{ 0 }

typedef struct {
    volatile size_t lock;
} t_arch_rwlock;


#define __ARCH_RW_LOCK_UNLOCKED		{ 0 }

#define arch_spin_is_locked(x)	((x)->lock != 0)
#ifndef L2_CACHE_EN
#define arch_spin_unlock_wait(x) \
        do { cpu_relax(); cache_invalidate(&(x)->lock, \
            sizeof((x)->lock));} while ((x)->lock)
#else
#define arch_spin_unlock_wait(x) \
        do { cpu_relax(); } while ((x)->lock)
#endif  // #ifndef L2_CACHE_EN


static inline int arch_get_process_id(void)
{
   uint64_t x;
   asm volatile("csrr %0, mhartid" : "=r" (x));
   return (int) x;
}

static volatile size_t barrier1 __attribute__ ((section(".data"))) = 0;
static volatile size_t barrier2 __attribute__ ((section(".data"))) = 0;

static inline void barrier_wait(
    volatile size_t* barrier
  , size_t incr_amount
  , size_t reach
  )
{
#if __riscv_xlen == 64
   asm volatile (
      //"1:                                \n"
      //"lr.d   a0, 0(%0)                  \n"
      //"add    a0, a0, %1                 \n"
      //"sc.d   a0, a0, 0(%0)              \n"
      //"bnez   a0, 1b                     \n"
      "amoadd.d a0, %1, (%0)             \n"
      "2:                                \n"
      "lr.d     a0, 0(%0)                \n"
      "bne    a0, %2, 2b                 \n"
      "fence                             \n"
   : /* output operands */
   : /* input operands */
      "r"(barrier),
      "r"(incr_amount),
      "r"(reach)
   : /* clobbered registers */
      "a0"
   );
#else
   asm volatile (
      //"1:                                \n"
      //"lr.d   a0, 0(%0)                  \n"
      //"add    a0, a0, %1                 \n"
      //"sc.d   a0, a0, 0(%0)              \n"
      //"bnez   a0, 1b                     \n"
      "amoadd.w a0, %1, (%0)             \n"
      "2:                                \n"
      "lr.w     a0, 0(%0)                \n"
      "bne    a0, %2, 2b                 \n"
      "fence                             \n"
   : /* output operands */
   : /* input operands */
      "r"(barrier),
      "r"(incr_amount),
      "r"(reach)
   : /* clobbered registers */
      "a0"
   );
#endif
}

static inline void arch_barrier_up(void)
{
   barrier_wait(&barrier1, 1, NUM_PROCESSES);
   barrier_wait(&barrier2, 1, NUM_PROCESSES);
}

static inline void arch_barrier_down(void)
{
   barrier_wait(&barrier1, -1, 0);
   barrier_wait(&barrier2, -1, 0);
}

static inline void arch_spin_unlock(t_arch_spinlock *lock)
{
#if 1
    asm volatile ("fence" : : : "memory");
    lock->lock = 0;
#else
#if (__riscv_xlen == 64)
    asm volatile (
        "amoswap.d.rl x0, x0, %0"
        : "=A" (lock->lock)
        :: "memory");
#else   // #if (__riscv_xlen == 64)
    asm volatile (
        "amoswap.w.rl x0, x0, %0"
        : "=A" (lock->lock)
        :: "memory");
#endif  // #if (__riscv_xlen == 64)
#endif
}

static inline int arch_spin_trylock(t_arch_spinlock *lock)
{
    size_t tmp = 1, busy;
#if (__riscv_xlen == 64)
        asm volatile (
        "amoswap.d.aq %0, %2, %1;"
        "fence;"
        : "=r" (busy), "+A" (lock->lock)
        : "r" (tmp)
        : "memory");
#else
    asm volatile (
        "amoswap.w.aq %0, %2, %1;"
        "fence;"
        : "=r" (busy), "+A" (lock->lock)
        : "r" (tmp)
        : "memory");
#endif
    return !busy;
}

static inline void arch_spin_lock(t_arch_spinlock *lock)
{
    while (1) {
#ifndef L2_CACHE_EN
        cache_invalidate((void *)&lock->lock, sizeof(lock->lock));
#endif // #ifndef L2_CACHE_EN
        if (arch_spin_is_locked(lock))
            continue;

        if (arch_spin_trylock(lock))
            break;
    }
}

static inline int arch_read_can_lock(t_arch_rwlock *lock)
{
    return lock->lock >= 0;
}

static inline int arch_write_can_lock(t_arch_rwlock *lock)
{
    return lock->lock == 0;
}

/// @todo Total recode!
static inline void arch_read_lock(t_arch_rwlock *lock)
{
    size_t tmp;
    size_t check_point;
#if (__riscv_xlen == 64)
    asm volatile (
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "1: lr.d    %1, %0\n"
        "   bltz    %1, 1b\n"
        "   add     t1, %1, t0;\n"
        "   mv      %1, t1;\n"
        "   sc.d.aq %1, %1, %0\n"
        "   bnez    %1, 1b\n"
        "   ld      %1, %0;\n"
        "   blt     %1, t0, 1f;\n"
        "   li      %1, 0;\n"
        "1: "
        : "+A" (lock->lock), "=&r" (tmp)
        :: "t0", "t1", "memory");
#else  // #if (__riscv_xlen == 64)
    asm volatile (
        "   csrr     t0, mhartid;\n"
        "   addi     t0, t0, 1;\n"
        "1: lr.w     %1, %0\n"
        "   bltz     %1, 1b\n"
        "   add      t1, %1, t0;\n"
        "   mv       %1, t1;\n"
        "   sc.w.aq  %1, %1, %0\n"
        "   bnez     %1, 1b\n"
        "   lw       %1, %0;\n"
        "   blt      %1, t0, 1f;\n"
        "   li       %1, 0;\n"
        "1: "
        : "+A" (lock->lock), "=&r" (tmp)
        :: "t0", "t1", "memory");
#endif  // #if (__riscv_xlen == 64)

    if (tmp) {
        /*sc_printf("Error: arch_read_lock: failed cpu-%d tmp=%p\n", 
            arch_get_process_id(), tmp);*/
    }
}

/// @todo Total recode!
static inline void arch_write_lock(t_arch_rwlock *lock)
{
    size_t tmp;

#if (__riscv_xlen == 64)
    asm volatile (
        "1: lr.d    %1, %0\n"
        "   bnez    %1, 1b\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "   neg     t0, t0;\n"
        "   mv      %1, t0;\n"
        "	sc.d.aq %1, %1, %0\n"
        "	bnez    %1, 1b\n"
        "   ld      %1, %0;\n"
        "   bne     %1, t0, 1f;\n"
        "   li       %1, 0;\n"
        "1: "
        : "+A" (lock->lock), "=&r" (tmp)
        :: "t0", "memory");
#else  // #if (__riscv_xlen == 64)
    asm volatile (
        "1:	lr.w	%1, %0\n"
        "	bnez	%1, 1b\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "   neg     t0, t0;\n"
        "   mv      %1, t0;\n"
        "   sc.w.aq %1, %1, %0\n"
        "   bnez    %1, 1b\n"
        "   lw      %1, %0;\n"
         "   bne     %1, t0, 1f;\n"
        "   li       %1, 0;\n"
        "1: "
        : "+A" (lock->lock), "=&r" (tmp)
        :: "t0", "memory");
#endif  // #if (__riscv_xlen == 64)

    if (tmp) {
        /*sc_printf("Error: arch_write_lock: failed cpu-%d tmp=%p\n", 
            arch_get_process_id(), tmp);*/
    }
}

/// @todo Total recode!
static inline int arch_read_trylock(t_arch_rwlock * lock)
{
    size_t busy, err = 0;

#if (__riscv_xlen == 64)
     asm volatile(
        "   li      %2, 0;\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "1: lr.d    %1, %0\n"
        "   bltz    %1, 1f\n"
        "   add     t1, %1, t0;\n"
        "   mv      %1, t1;\n"
        "   sc.d.aq %1, %1, %0\n"
        "   bnez    %1, 1b\n"
        "   ld      %1, %0;\n"
        "   li      %2, 1;\n"
        "   blt     %1, t0, 1f;\n"
        "   li      %1, 0;\n"
        "   li      %2, 0;\n"
        "1:\n"
        : "+A" (lock->lock), "=&r" (busy), "=&r" (err)
        :: "t0", "t1", "memory");
#else  // #if (__riscv_xlen == 64)
    asm volatile(
        "   li      %2, 0;\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "1: lr.w	%1, %0\n"
        "   bltz	%1, 1f\n"
        "   add     t1, %1, t0;\n"
        "   mv      %1, t1;\n"
        "   sc.w.aq %1, %1, %0\n"
        "   bnez    %1, 1b\n"
        "   lw      %1, %0;\n"
        "   li      %2, 1;\n"
        "   blt     %1, t0, 1f;\n"
        "   li      %1, 0;\n"
        "   li      %2, 0;\n"
        "1:\n"
        : "+A" (lock->lock), "=&r" (busy), "=&r" (err)
        :: "t0", "t1", "memory");
#endif  // #if (__riscv_xlen == 64)
    if (err) {
        /* sc_printf("Error: arch_read_trylock: failed cpu-%d err=%p\n", 
            arch_get_process_id(), err); */
    }
    return !busy;
}

/// @todo Total recode!
static inline int arch_write_trylock(t_arch_rwlock * lock)
{
    size_t busy, err = 0;

#if (__riscv_xlen == 64)
    asm volatile(
        "   li      %2, 0;\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "   neg     t0, t0;\n"
        "1: lr.d    %1, %0\n"
        "   bnez    %1, 1f\n"
        "   mv      %1, t0;\n"
        "   sc.d.aq %1, %1, %0\n"
        "   bnez    %1, 1b;\n"
        "   ld      %1, %0;\n"
        "   bne     %1, t0, 1f;\n"
        "   li      %1, 0;\n"
        "   li      %2, 0;\n"
        "1:\n"
        : "+A" (lock->lock), "=&r" (busy), "=&r" (err)
        :: "t0", "memory");
#else  // #if (__riscv_xlen == 64)
    asm volatile(
        "   li      %2, 0;\n"
        "   csrr    t0, mhartid;\n"
        "   addi    t0, t0, 1;\n"
        "   neg     t0, t0;\n"
        "1: lr.w    %1, %0\n"
        "   bnez    %1, 1f\n"
        "   mv     %1, t0;\n"
        "   sc.w.aq	%1, %1, %0\n"
        "   bnez	%1, 1b\n"
        "   lw      %1, %0;\n"
        "   bne     %1, t0, 1f;\n"
        "   li      %1, 0;\n"
        "   li      %2, 0;\n"
        "1:\n"
        : "+A" (lock->lock), "=&r" (busy), "=&r" (err)
        :: "t0", "memory");
#endif  // #if (__riscv_xlen == 64)

    if (err) {
        /* sc_printf("Error: arch_write_trylock: failed cpu-%d err=%p\n", 
            arch_get_process_id(), err); */
    }
    return !busy;
}

/// @todo Total recode!
static inline void arch_read_unlock(t_arch_rwlock * lock)
{
    size_t retval; 
#if (__riscv_xlen == 64)
    asm volatile(
        "csrr        t0, mhartid;\n"
        "addi        t0, t0, 1;\n"
        "neg         t0, t0;\n"
        "amoadd.d.rl %1, t0, %0"
        : "+A" (lock->lock), "=&r" (retval)
        : : "t0", "memory");
#else  // #if (__riscv_xlen == 64)
    asm volatile(
        "csrr        t0, mhartid;\n"
        "addi        t0, t0, 1;\n"
        "neg         t0, t0;\n"
        "amoadd.w.rl %1, t0, %0"
        : "+A" (lock->lock), "=&r" (retval)
        : : "t0", "memory");
#endif  // #if (__riscv_xlen == 64)

    if ((long)retval < 0) {
#if 0
        sc_printf("Error: arch_read_unlock: failed cpu-%d addr=%p val=%d\n", 
            arch_get_process_id(), &(lock->lock), retval);
#endif
    }
}

static inline void arch_write_unlock(t_arch_rwlock * lock)
{
#if (__riscv_xlen == 64)
    asm volatile (
        "amoswap.d.rl x0, x0, %0"
        : "=A" (lock->lock)
        :: "memory");
#else   // #if (__riscv_xlen == 64)
    asm volatile (
        "amoswap.w.rl x0, x0, %0"
        : "=A" (lock->lock)
        :: "memory");
#endif  // #if (__riscv_xlen == 64)
}

// atomic primitives

typedef struct atomic_t {
    volatile size_t counter;
} atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

/**
 * atomic_read - read atomic variable
 * @param v pointer of type atomic_t
 *
 * Atomically reads the value of v.
 */
static inline size_t atomic_read(const atomic_t *v)
{
    return *((volatile size_t *)(&(v->counter)));
}

/**
 * atomic_set - set atomic variable
 * @param v pointer of type atomic_t
 * @param i required value
 *
 * Atomically sets the value of v to i.
 */
static inline void atomic_set(atomic_t *v, size_t i)
{
    v->counter = i;
}

/**
 * atomic_add - add integer to atomic variable
 * @param i integer value to add
 * @param v pointer of type atomic_t
 *
 * Atomically adds @i to @v.
 * @todo Total recode!
 */
static inline void atomic_add(size_t i, atomic_t *v)
{
#if (__riscv_xlen == 64)
    asm volatile (
        "amoadd.d zero, %1, %0"
        : "+A" (v->counter)
        : "r" (i));
#else   // #if (__riscv_xlen == 64)
    asm volatile (
        "amoadd.w zero, %1, %0"
        : "+A" (v->counter)
        : "r" (i));
#endif  // #if (__riscv_xlen == 64)
}

/**
 * atomic_add_return - add integer to atomic variable
 * @param i integer value to add
 * @param v pointer of type atomic_t
 *
 * Atomically adds @i to @v and returns the result
 * @todo Total recode!
 */
static inline size_t atomic_add_return(size_t i, atomic_t *v)
{
    size_t c;
#if (__riscv_xlen == 64)
    asm volatile (
        "amoadd.d %0, %2, %1"
        : "=r" (c), "+A" (v->counter)
        : "r" (i));
#else   // #if (__riscv_xlen == 64)
    asm volatile (
        "amoadd.w %0, %2, %1"
        : "=r" (c), "+A" (v->counter)
        : "r" (i));
#endif  // #if (__riscv_xlen == 64)
    return (c + i);
}

static inline size_t atomic_add_return_32(size_t i, atomic_t *v)
{
    size_t c;
    asm volatile (
        "amoadd.w %0, %2, %1"
        : "=r" (c), "+A" (v->counter)
        : "r" (i));
    return (c + i) & 0x0FFFFFFFFULL;;
}

static inline size_t atomic_xchg(atomic_t *v, size_t n)
{
    size_t c;
#if (__riscv_xlen == 64)
    asm volatile (
        "amoswap.d %0, %2, %1"
        : "=r" (c), "+A" (v->counter)
        : "r" (n));
#else
    asm volatile (
        "amoswap.w %0, %2, %1"
        : "=r" (c), "+A" (v->counter)
        : "r" (n));
#endif
    return c;
}

#endif  // SCR_ATOMIC_H
