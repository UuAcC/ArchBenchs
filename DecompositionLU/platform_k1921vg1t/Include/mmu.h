#ifndef SCR_MMU_H
#define SCR_MMU_H

#include "riscv_csr_encoding.h"
#include "mpu.h"

#define MMU_ASID_MASK                       (0x1FF)
#define SPTBR64_ASID_OFF                    (44)
#define SV64_VPN_MASK                       (0x1FF)
#define SV32_VPN_MASK                       (0x3FF)

// software page walker helper registers
#define SCR_CSR_MMU_SWPW_R0                 (0xFD0)
#define SCR_CSR_MMU_SWPW_R1                 (0xFD1)
#if __riscv_xlen == 64
#define SCR_CSR_MMU_SWPW_R2                 (0xFD2)
#endif  // #if __riscv_xlen == 64

//MMU csrs 'n' offsets
#define SCR_CSR_MMU_BASE                    (0xbc0)
#define SCR_CSR_MMU_TLB_PATTR               (SCR_CSR_MMU_BASE + 0)
#define SCR_CSR_MMU_TLB_VADDR               (SCR_CSR_MMU_BASE + 1)
#define SCR_CSR_MMU_TLB_UPDATE              (SCR_CSR_MMU_BASE + 2)
#define SCR_CSR_MMU_TLB_SCAN                (SCR_CSR_MMU_BASE + 3)

/* TLB_UPDATE bits offsets */
#define SCR_CSR_MMU_TLB_UPDATE_TLBI_OFF     (0)
#define SCR_CSR_MMU_TLB_UPDATE_TLBD_OFF     (1)
#define SCR_CSR_MMU_TLB_UPDATE_MP_OFF       (2)
#define SCR_CSR_MMU_TLB_UPDATE_LOCK_OFF     (11)

#define SCR_CSR_MMU_TLB_UPDATE_LOCK_BIT     (1 << SCR_CSR_MMU_TLB_UPDATE_LOCK_OFF)

#define SCR_CSR_MMU_SCAN_TYPE_OFF           (31)

// TLBD related definess
#define MMU_TLBD_ENTRIES                    (32)
#define MMU_TLBD_ENTRIES_LOG                (5)
#define MMU_TLBD_SETS                       (1)
#define MMU_TLBD_WAYS                       (32)
#define MMU_TLBD_SET_OFFSET                 (0)

// TLBI related defines
#define MMU_TLBI_ENTRIES                    (32)
#define MMU_TLBI_ENTRIES_LOG                (5)
#define MMU_TLBI_SETS                       (1)
#define MMU_TLBI_WAYS                       (32)
#define MMU_TLBI_SET_OFFSET                 (0)

//MMU PTE OFFSETS
#define MMU_PTE_GLOBAL_BIT_OFFSET           (5)

#define CSR_ASID_CONTAINER                  sptbr

#define MAX_MMU_ENTRIES                     (1024)


#if !defined (__ASSEMBLER__ )

#include "arch.h"
#include <stdint.h>
#include <stdio.h>

enum pte_type {             // G U X W R
    MMU_PTE_TYPE_SR =   1,  // 0 0 0 0 1
    MMU_PTE_TYPE_SRW =  3,  // 0 0 0 1 1
    MMU_PTE_TYPE_SX =   4,  // 0 0 1 0 0
    MMU_PTE_TYPE_SRX =  5,  // 0 0 1 0 1
    MMU_PTE_TYPE_SWX =  6,  // 0 0 1 1 0
    MMU_PTE_TYPE_SRWX = 7,  // 0 0 1 1 1
    MMU_PTE_TYPE_U    = 8,  // 0 1 0 0 0
    MMU_PTE_TYPE_UR =   9,  // 0 1 0 0 1
    MMU_PTE_TYPE_URW =  11, // 0 1 0 1 1
    MMU_PTE_TYPE_UX =   12, // 0 1 1 0 0
    MMU_PTE_TYPE_URX =  13, // 0 1 1 0 1
    MMU_PTE_TYPE_UWX =  14, // 0 1 1 1 0
    MMU_PTE_TYPE_URWX = 15, // 0 1 1 1 1
    MMU_PTE_TYPE_GSR =   (1 + 16),  // 1 0 0 0 1
    MMU_PTE_TYPE_GSRW =  (3 + 16),  // 1 0 0 1 1
    MMU_PTE_TYPE_GSX =   (4 + 16),  // 1 0 1 0 0
    MMU_PTE_TYPE_GSRX =  (5 + 16),  // 1 0 1 0 1
    MMU_PTE_TYPE_GSRWX = (7 + 16),  // 1 0 1 1 1
    MMU_PTE_TYPE_GUR =   (9 + 16),  // 1 1 0 0 1
    MMU_PTE_TYPE_GURW =  (11 + 16), // 1 1 0 1 1
    MMU_PTE_TYPE_GUX =   (12 + 16), // 1 1 1 0 0
    MMU_PTE_TYPE_GURX =  (13 + 16), // 1 1 1 0 1
    MMU_PTE_TYPE_GURWX = (15 + 16)  // 1 1 1 1 1
};

#define MMU_PTE_TYPE_A_BIT          (1 << 5)
#define MMU_PTE_TYPE_D_BIT          (1 << 6)
#define MMU_PTE_TYPE_AD_BITS        (MMU_PTE_TYPE_D_BIT | MMU_PTE_TYPE_A_BIT)

#define CAUSE_TLB_MISS              14

enum tlb_type {
    MMU_TLBD = 0,
    MMU_TLBI = 1
};

enum page_type {
    MMU_PTE_4K_PAGE   = 0,
    MMU_PTE_MEGA_PAGE = 1,
    MMU_PTE_GIGA_PAGE = 2
};

static inline void sfencevma(int va, int asid)
{
    asm volatile ("sfence.vma %0, %1"
                  ::
                  "r"(va),
                  "r"(asid):
                  "memory");
}

static inline void sfencevma_va_x0(size_t asid)
{
    asm volatile ("sfence.vma x0, %0"
                  ::
                  "r"(asid):
                  "memory");
}

static inline void sfencevma_asid_x0(size_t va)
{
    asm volatile ("sfence.vma %0, x0"
                  ::
                  "r"(va):
                  "memory");
}

static inline size_t get_tlb_data_pattr(uint32_t entry)
{
    WRITE_CSR( SCR_CSR_MMU_TLB_SCAN, entry | (1 << 31) );
    return READ_CSR(SCR_CSR_MMU_TLB_PATTR);
}

static inline bool is_tlb_data_entry_valid(uint32_t entry)
{
    size_t attr = get_tlb_data_pattr(entry);
    return (bool)(attr & 0x1);
}

static inline uint32_t get_tlb_instr_pattr(uint32_t entry)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_SCAN, entry);
    return READ_CSR(SCR_CSR_MMU_TLB_PATTR);
}

static inline bool is_tlb_instr_entry_valid(uint32_t entry)
{
    uint32_t attr = get_tlb_instr_pattr(entry);
    return (bool)(attr & 0x1);
}

static inline size_t get_tlb_data_vaddr(uint32_t entry)
{
    WRITE_CSR( SCR_CSR_MMU_TLB_SCAN, entry | (1 << 31) );
    return READ_CSR(SCR_CSR_MMU_TLB_VADDR);
}

static inline uint32_t get_tlb_data_asid(uint32_t entry)
{
    return get_tlb_data_vaddr(entry) & 0x1ff;
}


static inline size_t get_tlb_instr_vaddr(uint32_t entry)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_SCAN, entry);
    return READ_CSR(SCR_CSR_MMU_TLB_VADDR);
}

static inline uint32_t get_tlb_instr_asid(uint32_t entry)
{
    return get_tlb_instr_vaddr(entry) & 0x1ff;
}


static inline void create_tlb_data_entry(size_t vpn, size_t ppn, 
    uint32_t pg_sz, uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_VADDR, vpn << 12);
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE, (1 << SCR_CSR_MMU_TLB_UPDATE_TLBD_OFF) |
                                   (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline void create_tlb_data_entry_lock(size_t vpn, size_t ppn, 
    uint32_t pg_sz, uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_VADDR, vpn << 12);
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE, 
            (1 << SCR_CSR_MMU_TLB_UPDATE_TLBD_OFF) |
            SCR_CSR_MMU_TLB_UPDATE_LOCK_BIT |
            (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline void create_tlb_instr_entry(size_t vpn, size_t ppn, 
    uint32_t pg_sz, uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_VADDR, vpn << 12);
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE, 
            (1 << SCR_CSR_MMU_TLB_UPDATE_TLBI_OFF) |
            (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline void create_tlb_instr_entry_lock(size_t vpn, size_t ppn, 
    uint32_t pg_sz, uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_VADDR, vpn << 12);
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE, 
            (1 << SCR_CSR_MMU_TLB_UPDATE_TLBI_OFF) |
            SCR_CSR_MMU_TLB_UPDATE_LOCK_BIT | 
            (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline void create_tlb_both_entry(size_t vpn, size_t ppn, uint32_t pg_sz, 
    uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_VADDR, vpn << 12);
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE, (1 << SCR_CSR_MMU_TLB_UPDATE_TLBI_OFF) |
                                      (1 << SCR_CSR_MMU_TLB_UPDATE_TLBD_OFF) |
                                   (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline void create_tlb_entry_hw_update(size_t ppn, size_t pg_sz, 
    uint32_t attrs)
{
    WRITE_CSR(SCR_CSR_MMU_TLB_PATTR, (ppn << 10) | (attrs << 1) | 1);
    WRITE_CSR(SCR_CSR_MMU_TLB_UPDATE,
        (pg_sz << SCR_CSR_MMU_TLB_UPDATE_MP_OFF));
}

static inline int check_tlb_data_entry(size_t ppn, size_t attr, 
    uint32_t entry_num)
{
    size_t rd_attr, rd_ppn, rd_vpn;

    rd_attr = get_tlb_data_pattr(entry_num);
    rd_ppn = rd_attr >> 10;
    rd_attr >>= 1;
    rd_attr &= 0xF;
    rd_vpn = get_tlb_data_vaddr(entry_num) >> 12;
    if ((uint32_t)rd_attr != (attr & 0xF)) {
        return -1;
    }
    if (ppn != rd_ppn) {
        return -2;
    }
    if (ppn != rd_vpn) {
        return -3;
    }
    return 0;
}

static inline int check_tlb_instr_entry(size_t ppn, uint32_t attr, 
    uint32_t entry_num)
{
    size_t rd_attr, rd_ppn, rd_vpn;

    rd_attr = get_tlb_instr_pattr(entry_num);
    rd_ppn = rd_attr >> 10;
    rd_attr >>= 1;
    rd_attr &= 0xF;
    rd_vpn = get_tlb_instr_vaddr(entry_num) >> 12;
    if ((uint32_t)rd_attr != (attr & 0xC)) {
        return -1;
    }
    if (ppn != rd_ppn) {
        return -2;
    }
    if (ppn != rd_vpn) {
        return -3;
    }
    return 0;
}

static inline size_t get_asid_mask(void)
{
#if __riscv_xlen == 64
    return SPTBR64_ASID >> SPTBR64_ASID_OFF;
#else
    return SPTBR32_ASID >> SPTBR32_ASID_OFF;
#endif
}

static inline void write_asid(size_t asid)
{
    size_t new_val = READ_CSR(CSR_ASID_CONTAINER);
#if __riscv_xlen == 64
    new_val &= ~SPTBR64_ASID;
    new_val |= (asid << SPTBR64_ASID_OFF) & SPTBR64_ASID;
#else
    new_val &= ~SPTBR32_ASID;
    new_val |= (asid << SPTBR32_ASID_OFF) & SPTBR32_ASID;
#endif  // #if __riscv_xlen == 64
    WRITE_CSR(CSR_ASID_CONTAINER, new_val);
}

static inline size_t read_asid(void)
{
    size_t val = READ_CSR(CSR_ASID_CONTAINER);
#if __riscv_xlen == 64
    val &= SPTBR64_ASID;
    val = val >> SPTBR64_ASID_OFF;
#else
    val &= SPTBR32_ASID;
    val = val >> SPTBR32_ASID_OFF;
#endif  // #if __riscv_xlen == 64
    return val;
}

static inline void detect_mmu_num_entries(int *mmu_tlbd_entries, 
    int *mmu_tlbi_entries)
{
    int entry;

    for (entry = 0; entry < MAX_MMU_ENTRIES; entry++) {
        int read_back_val;
        WRITE_CSR(SCR_CSR_MMU_TLB_SCAN, entry | (1 << 31));
        read_back_val = READ_CSR(SCR_CSR_MMU_TLB_SCAN) & ~(1U << 31);
        if (read_back_val != entry) {
            break;
        }
    }
    *mmu_tlbd_entries = entry;
    //sc_printf("mmu_tlbd_entries = %d\n", *mmu_tlbd_entries);

    for (entry = 0; entry < MAX_MMU_ENTRIES; entry++) {
        int read_back_val;
        WRITE_CSR(SCR_CSR_MMU_TLB_SCAN, entry);
        read_back_val = READ_CSR(SCR_CSR_MMU_TLB_SCAN) & ~(1U << 31);
        if (read_back_val != entry) {
#if 0
            sc_printf("TLBD: %X %X\n", read_back_val, entry);
#endif  // 0
            break;
        }
    }
    *mmu_tlbi_entries = entry;
    //sc_printf("mmu_tlbi_entries = %d\n", *mmu_tlbi_entries);
}

#endif  // #if !defined (__ASSEMBLER__ )

#endif  // SCR_MMU_H
