/*
 *
 * SCR5 PLIC driver for K1921VG1T
 *
 * 2025
 *
*/

#include "arch.h"
#include "csr.h"
#include "plic.h"

//-----------------------------------------------------------------------------------------
// defines
#define NULL_IRQ 0

// pointers to handler functions for machine mode
irqfunc* mach_plic_handler[256] __attribute__((section(".data")));
irqfunc* mach_software_int_handler __attribute__((section(".data")));
irqfunc* mach_timer_int_handler __attribute__((section(".data")));

// pointers to handler functions for supervisor mode
irqfunc* supervisor_plic_handler[256] __attribute__((section(".data")));
irqfunc* supervisor_software_int_handler __attribute__((section(".data")));
irqfunc* supervisor_timer_int_handler __attribute__((section(".data")));


//-----------------------------------------------------------------------------------------
/*
 * Set PLIC handler function for isr num
*/

void PLIC_SetIrqHandler (uint8_t target, uint32_t isr_num, irqfunc* func) {
    if(target == Plic_Mach_Target) {
        mach_plic_handler[isr_num] = func;
    } else {
        supervisor_plic_handler[isr_num] = func;
    }
}

/*
 * Set PLIC irq priority
*/

void PLIC_SetPriority (uint32_t isr_num, uint8_t pri) {
    PLIC->SRC_PRI[isr_num] = pri;
}

/*
 * Set PLIC irq mode
*/

void PLIC_SetMode (uint32_t isr_num, Plic_IrqMode_TypeDef mode) {
    PLIC->SRC_MODE[isr_num] = (uint32_t)(mode);
}

/*
 * Enable PLIC irq
*/

void PLIC_IntEnable (uint8_t target, uint32_t isr_num) {
    uint32_t bankNum = isr_num / 32;
    uint32_t bankPos = isr_num - bankNum * 32;
    uint32_t bankVal = PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum];

    //read - modify - write operation

    bankVal |= (1 << bankPos);

    PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum] = bankVal;
}

/*
 * Disable PLIC irq
*/

void PLIC_IntDisable (uint8_t target, uint32_t isr_num) {
    uint32_t bankNum = isr_num / 32;
    uint32_t bankPos = isr_num - bankNum * 32;
    uint32_t bankVal = PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum];

    //read - modify - write operation

    bankVal &= ~(1 << bankPos);

    PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum] = bankVal;
}

/*
 * Get current isr number
*/

uint32_t PLIC_ClaimIrq (uint8_t target) {
    return (uint32_t)(PLIC->PRI_SE[target].START_END);
}

/*
 * Set current isr as completed
*/

void PLIC_ClaimComplete (uint8_t target, uint32_t isrnum) {
    PLIC->PRI_SE[target].START_END = isrnum;
}

/*
 * Set threshold for irqs
*/

void PLIC_SetThreshold(uint8_t target, uint32_t value) {
    PLIC->PRI_SE[target].PRI_TRSHLD = value;
}

/*
 * PLIC Interrupt main handler
*/

void PLIC_MachHandler (void) {
    // handle interrupt
    uint32_t isr_num = PLIC_ClaimIrq(Plic_Mach_Target);
    // check if handler exist
    if (mach_plic_handler[isr_num] != NULL_IRQ) {
        // call isr handler
        mach_plic_handler[isr_num]();
        // set isr completes
        PLIC_ClaimComplete(Plic_Mach_Target, isr_num);
    }
}


//-----------------------------------------------------------------------------------------
/*
 * Set software interrupt handler
*/

void SWINT_SetIrqHandler (uint8_t target, irqfunc* func) {
    if (target == Mach_Target) {
        mach_software_int_handler = func;
    } else {
        supervisor_software_int_handler = func;
    }
}

/*
 * Software interrupt main handler
*/

void SWINT_MachHandler (void) {
    mach_software_int_handler();
}


//-----------------------------------------------------------------------------------------
/*
 * Set Timer interrupt handler
*/

void TIMER_SetIrqHandler (uint8_t target, irqfunc* func) {
    if (target == Mach_Target) {
        mach_timer_int_handler = func;
    } else {
        supervisor_timer_int_handler = func;
    }
}

/*
 * Timer interrupt main handler
*/

void TimerINT_MachHandler (void) {
    mach_timer_int_handler();
}


//-----------------------------------------------------------------------------------------
/*
 * PLIC trap handler
*/

void trap_handler (uint32_t mcause_value, uint32_t mepc_value, uint32_t stack_pointer) {
    if ((mcause_value & TRAP_CAUSE_INTERRUPT_FLAG) == 0) {
        // handle exceptions
        switch (mcause_value & TRAP_CAUSE_EXCEPT_MASK) {
            case TRAP_CAUSE_EXC_FETCH_ALIGN  : exception_instruction_misalign(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_FETCH_ACCESS : exception_instruction_access_fault(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_ILLEGAL      : exception_instruction_illegal(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_BREAKPOINT   : exception_breakpoint(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_LOAD_ALIGN   : exception_load_misalign(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_LOAD_ACCESS  : exception_load_access_fault(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_STORE_ALIGN  : exception_store_misalign(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_STORE_ACCESS : exception_store_access_fault(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_UECALL       : exception_ecall_from_u_mode(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_SECALL       : exception_ecall_from_s_mode(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_MECALL       : exception_ecall_from_m_mode(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_FETCH_PAGE   : exception_fetch_page_fault(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_LOAD_PAGE    : exception_load_page_fault(mepc_value, stack_pointer); break;
            case TRAP_CAUSE_EXC_STORE_PAGE   : exception_store_page_fault(mepc_value, stack_pointer); break;
            default                          : exception_unknown(mcause_value, mepc_value, stack_pointer); break;
        }
        	while(1){};
    } else {
        // handle interrupts
        switch (mcause_value & TRAP_CAUSE_EXCEPT_MASK) {
            case TRAP_CAUSE_INT_SSOFT : SWINT_MachHandler(); break;
            case TRAP_CAUSE_INT_MSOFT : SWINT_MachHandler(); break;
            case TRAP_CAUSE_INT_STIME : TimerINT_MachHandler(); break;
            case TRAP_CAUSE_INT_MTIME : TimerINT_MachHandler(); break;
            case TRAP_CAUSE_INT_SEXT  : PLIC_MachHandler(); break;
            case TRAP_CAUSE_INT_MEXT  : PLIC_MachHandler(); break;
            default                   : exception_unknown(mcause_value, mepc_value, stack_pointer); break;
        }
    }
}

//-----------------------------------------------------------------------------------------
/*
 * Exceptions trap handlers (can be redefined in user code)
*/

static void default_exception_instruction_misalign(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_instruction_misalign(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_instruction_misalign")));

static void default_exception_instruction_access_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_instruction_access_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_instruction_access_fault")));

static void default_exception_instruction_illegal(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_instruction_illegal(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_instruction_illegal")));

static void default_exception_breakpoint(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_breakpoint(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_breakpoint")));

static void default_exception_load_misalign(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_load_misalign(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_load_misalign")));

static void default_exception_load_access_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_load_access_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_load_access_fault")));

static void default_exception_store_misalign(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_store_misalign(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_store_misalign")));

static void default_exception_store_access_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_store_access_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_store_access_fault")));

static void default_exception_ecall_from_u_mode(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_ecall_from_u_mode(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_ecall_from_u_mode")));

static void default_exception_ecall_from_s_mode(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_ecall_from_s_mode(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_ecall_from_s_mode")));

static void default_exception_ecall_from_m_mode(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_ecall_from_m_mode(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_ecall_from_m_mode")));

static void default_exception_fetch_page_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_fetch_page_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_fetch_page_fault")));

static void default_exception_load_page_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_load_page_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_load_page_fault")));

static void default_exception_store_page_fault(__attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_store_page_fault(uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_store_page_fault")));

static void default_exception_unknown(__attribute__ ((unused)) uint32_t mcause_value, __attribute__ ((unused)) uint32_t mepc_value, __attribute__ ((unused)) uint32_t stack_pointer) {
    while (1) {};
}
void exception_unknown(uint32_t mcause_value, uint32_t mepc_value, uint32_t stack_pointer) __attribute__((weak, alias("default_exception_unknown")));
