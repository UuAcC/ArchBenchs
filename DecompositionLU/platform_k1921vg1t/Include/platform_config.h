// @file       <platform_config.h>
// @brief      platform specific configurations
//
// Copyright by Syntacore LLC © 2019. ALL RIGHTS RESERVED. STRICTLY CONFIDENTIAL.
// Information contained in this material is confidential and proprietary to Syntacore LLC
// and its affiliates and may not be modified, copied, published, disclosed, distributed,
// displayed or exhibited, in either electronic or printed formats without written
// authorization of the Syntacore LLC. Subject to License Agreement.
//

#ifndef SCR_PLATFORM_CONFIG_SCR5_H
#define SCR_PLATFORM_CONFIG_SCR5_H

#ifdef PLATFORM
#define PLF_SYS_FREQ SYS_CLK
#define PLF_CPU_FREQ SYS_CLK
#define PLF_RTC_TIMEBASE RTC_HZ

#ifndef PLF_UART_BAUDRATE
#define PLF_UART_BAUDRATE 115200
#endif

#ifndef PLF_UART_CLK
#define PLF_UART_CLK SYS_CLK
#endif

#define LREG lw
#define SREG sw
#define REGBYTES 4

#define REGION_MMCFG_BASE           (0xE0000000)
#define REGION_MMCFG_MASK           (0xFF000000)
#define REGION_MMIO_ADDR            (0xFF000000)
#define REGION_MMIO_MASK            (0xFF000000)

#define PLF_MMIO_BASE               (REGION_MMIO_ADDR)

#define PLF_UART0_IRQ               (0)
#define PLF_UART0_16550
#define PLF_UART0_16550_REG_SHIFT   (0)
#define PLF_UART0_BASE              (0xff000000)

#define PLF_FPGA_IRQ_SRC            (0x5D0000)
#define PLF_FPGA_IRQ_NUM            (21)

#define TIMER_ADDR                  (REGION_MMCFG_BASE)

#define MEM_MTIME_CTRL              (TIMER_ADDR + 0x00)
#define MEM_MTIME_DIV               (TIMER_ADDR + 0x04)
#define MEM_MTIME                   (TIMER_ADDR + 0x08)
#define MEM_MTIMEH                  (TIMER_ADDR + 0x0C)
#define MEM_MTIMECMP                (TIMER_ADDR + 0x10)
#define MEM_MTIMECMPH               (TIMER_ADDR + 0x14)

#define PLF_L2CTL_BASE              (TIMER_ADDR + 0x1000)

#ifdef SCR_EXT_PLIC_BASE_ADDR
#define REGION_PLIC_ADDR (SCR_EXT_PLIC_BASE_ADDR)
#define REGION_PLIC_MASK (~SCR_EXT_PLIC_ADDR_MASK)
#endif

#define PLF_MEM_BASE     (0)
#define PLF_MEM_SIZE     (2*1024*1024U)
#define PLF_MEM_MASK     (0xFFE00000U)
#define PLF_MEM_ATTR     (SCR_MPU_CTRL_MT_WEAKLY | SCR_MPU_CTRL_ALL)

#define PLF_L2C_BANKS     (4)

#else
#error "Error! PLATFORM undefined!"
#endif // #ifdef PLATFORM


#endif // SCR_PLATFORM_CONFIG_SCR5_H
