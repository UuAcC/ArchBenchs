/*
 *
 * SCR5 PLIC driver header for "S1252AUTO"
 *
 * created by DVS
 * rewrite by M.A.Terekhov
 *
 * 2024
 *
*/

#ifndef _PLIC_H
#define _PLIC_H


#include <stdint.h>

//-----------------------------------------------------------------------------------------
/*
 * Registers of PLIC module
*/
 
typedef struct {
    uint32_t INTEN_BANK[32];                    // offset 0x0 - 0x7c
} PLIC_INTEN_Bank_TypeDef;

typedef struct {
    uint32_t PRI_TRSHLD;
    uint32_t START_END;
    uint32_t Reserved0 [1022];
} PLIC_PRI_SE_TypeDef;

typedef struct {
    uint32_t SRC_PRI[1024];                     // 0 - 0xffc
    uint32_t INT_PEND[32];                      // 0x1000 - 0x107c
    uint32_t Reserved0 [992];                   // 0x1080 - 0x1fff
    PLIC_INTEN_Bank_TypeDef INTEN_TARGET[64];   // 0x2000 - 0x3ffc
    uint32_t Reserved1 [503808];                // 0x4000 - 0x1efffc
    uint32_t SRC_MODE  [1024];                  // 0x1f0000 - 0x1f0ffc
    uint32_t Reserved2 [15360];                 // 0x1f1000 - 1ffffc
    PLIC_PRI_SE_TypeDef PRI_SE[64];             // 0x200000 -0x23fffc
    uint32_t Reserved3 [3605501];               // 0x240000 - 0xffffff
} PLIC_TypeDef;

enum Plic_Target {
    Plic_Mach_Target = 0x0,
    Plic_SuperVisor_Target
};

enum SW_Target {
    Mach_Target = 0x0,
    SuperVisor_Target
};

typedef enum {
    PLIC_IRQMODE_OFF = 0x0,
    PLIC_IRQMODE_HILEVEL,
    PLIC_IRQMODE_LOLEVEL,
    PLIC_IRQMODE_RISEDGE,
    PLIC_IRQMODE_FALEDGE,
    PLIC_IRQMODE_TWOEDGE
} Plic_IrqMode_TypeDef;


typedef void irqfunc (void);

void PLIC_SetIrqHandler (uint8_t target, uint32_t isr_num, irqfunc* func);
void PLIC_SetPriority (uint32_t isr_num, uint8_t pri);
void PLIC_SetThreshold(uint8_t target, uint32_t value);
void PLIC_SetMode (uint32_t isr_num, Plic_IrqMode_TypeDef mode);
void PLIC_IntEnable (uint8_t target, uint32_t isr_num);
void PLIC_IntDisable (uint8_t target, uint32_t isr_num);
void PLIC_MachHandler(void);
uint32_t PLIC_ClaimIrq (uint8_t target);
void PLIC_ClaimComplete (uint8_t target, uint32_t isrnum);

void SWINT_SetIrqHandler(uint8_t target, irqfunc* func);
void SWINT_MachHandler(void);

void TIMER_SetIrqHandler(uint8_t target, irqfunc* func);
void TimerINT_MachHandler(void);

void trap_handler(uint32_t mcause_value, uint32_t mepc_value, uint32_t stack_pointer);

void exception_instruction_misalign(uint32_t mepc_value, uint32_t stack_pointer);
void exception_instruction_access_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_instruction_illegal(uint32_t mepc_value, uint32_t stack_pointer);
void exception_breakpoint(uint32_t mepc_value, uint32_t stack_pointer);
void exception_load_misalign(uint32_t mepc_value, uint32_t stack_pointer);
void exception_load_access_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_store_misalign(uint32_t mepc_value, uint32_t stack_pointer);
void exception_store_access_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_ecall_from_u_mode(uint32_t mepc_value, uint32_t stack_pointer);
void exception_ecall_from_s_mode(uint32_t mepc_value, uint32_t stack_pointer);
void exception_ecall_from_m_mode(uint32_t mepc_value, uint32_t stack_pointer);
void exception_fetch_page_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_load_page_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_store_page_fault(uint32_t mepc_value, uint32_t stack_pointer);
void exception_unknown(uint32_t mcause_value, uint32_t mepc_value, uint32_t stack_pointer);


#define PLIC_BASE              (0xFE000000UL)
#define PLIC                   ((PLIC_TypeDef                *) PLIC_BASE)

#define PLIC_SOURCES            SCR_EXT_PLIC_SOURCES
#define PLIC_TARGETS            SCR_EXT_PLIC_TARGETS
#define PLIC_BANKS              ((PLIC_SOURCES+1)/32)
#define PLIC_PRI_LVLS           SCR_EXT_PLIC_PRI_LVLS
#define PLIC_MAX_SOURCES        (1023)
#define PLIC_MAX_TARGETS        (64)
#define PLIC_MAX_BANKS          (32)

#define PLIC_PRIORITY_OFS       (0x0)
#define PLIC_MODE_OFS           (0x1F0000)
#define PLIC_IP_OFS             (0x1000)
#define PLIC_IE_OFS             (0x2000)
#define PLIC_THR_CC_OFS         (0x200000)
#define PLIC_STEP               (0x4)
#define PLIC_TGT_THR_STEP       (0x1000)
#define PLIC_TGT_IE_STEP        (0x80)

#define PLIC_MODE_OFF           (0)
#define PLIC_MODE_LVL_HI        (1)
#define PLIC_MODE_LVL_LO        (2)
#define PLIC_MODE_EDGE_RISE     (3)
#define PLIC_MODE_EDGE_FALL     (4)
#define PLIC_MODE_EDGE_DUAL     (5)

#if __riscv_xlen == 64
#define CAUSE_MEI               (0x800000000000000BULL)
#define CAUSE_SEI               (0x8000000000000009ULL)
#else
#define CAUSE_MEI               (0x8000000B)
#define CAUSE_SEI               (0x80000009)

#endif

#endif
