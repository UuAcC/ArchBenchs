
#ifndef PLATFORM_L1CACHE_SCR4_H
#define PLATFORM_L1CACHE_SCR4_H

#include <stdint.h>

// SCR4 External Architecture Specification v1.0.0, 2023-06-08
// 3.3.4.21. MEM_CTRL_GLOBAL Register [0xBD4] - Memory Regions Control Global Register
// Bits  Name    Access  Reset Description
// 0     L1ICE   RW      0     Instruction cache L1 enable
// 1     L1DCE   RW      0     Data cache L1 enable
// 2     L1ICF   RSW1S   0     Instruction cache L1 flush control.
//                             Setting to 1 starts the cache flush/invalidate procedure.
//                             For read access, defines status of the procedure:
//                             0 - cache flush/invalidate is complete
//                             1 - cache flush/invalidate is in progress
// 3     L1DCF   RSW1S   0     Data cache L1 flush control.
//                             Setting to 1 starts the cache flush/invalidate procedure.
//                             For read access, defines status of the procedure:
//                             0 - cache flush/invalidate is complete
//                             1 - cache flush/invalidate is in progress
#define MEM_CTRL_GLOBAL_L1DCF_Pos           (3)
#define MEM_CTRL_GLOBAL_L1ICF_Pos           (2)
#define MEM_CTRL_GLOBAL_L1DCE_Pos           (1)
#define MEM_CTRL_GLOBAL_L1ICE_Pos           (0)
#define MEM_CTRL_GLOBAL_ENABLE_BOTH_CACHES  ((1 << MEM_CTRL_GLOBAL_L1DCE_Pos) | \
                                             (1 << MEM_CTRL_GLOBAL_L1ICE_Pos)   )

static inline void write_csr_mem_ctrl_global(const uint32_t value) {
  asm volatile ("csrw 0xBD4, %0" : : "rK" (value) : "memory");
}

static inline uint32_t read_csr_mem_ctrl_global() {
  uint32_t value;

  asm volatile ("csrr %0, 0xBD4" : "=r" (value) : : "memory");
  return value;
}

static inline void plf_l1cache_init() {
  // 7.1.4.1. Enabling and Disabling the L1 Caches
  // The setting MEM_CTRL_GLOBAL[L1ICE] or MEM_CTRL_GLOBAL[L1DCE] = 1 enables
  // corresponded L1 cache. After this the cache executes flush-invalidating.
  // During this procedure, the cache couldn’t be accessed for a cacheable transaction.
  // The non-cacheable transaction will be bypassed to memory subsystem.
  write_csr_mem_ctrl_global(MEM_CTRL_GLOBAL_ENABLE_BOTH_CACHES);
}

#endif // PLATFORM_L1CACHE_SCR4_H

