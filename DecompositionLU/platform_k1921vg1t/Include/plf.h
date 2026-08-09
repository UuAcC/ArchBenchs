/// @file
/// @brief platform specific configurations

#ifndef SCR_PLATFORM_CONFIG_SCR5_H
#define SCR_PLATFORM_CONFIG_SCR5_H

#ifndef PLF_SYS_CLK
#define PLF_SYS_CLK 25000000 // TODO
#endif

#define PLF_CORE_VARIANT_SCR 5
#define PLF_CORE_VARIANT_SCR5 1
#define PLF_CORE_VARIANT SCR5

#define NUM_PROCESSES 2

#if __riscv_xlen == 32
#define EXPAND32ADDR(x) (x)
#define LREG lw
#define SREG sw
#define REGBYTES 4
#else
#define EXPAND32ADDR(x) (((((x) / 0x80000000) & 1) * 0xffffffff00000000) + (x))
#define LREG ld
#define SREG sd
#define REGBYTES 8
#endif

#define PLF_IMPL_STR "S1252_AUTO"


#define MPU_LAST_ENTRY      (10)
#define MPU_QSPI1_REGION    (9)
#define MPU_QSPI0_REGION    (8)
#define MPU_SDRAM_REGION    (7)
#define MPU_EXT_REGION      (6)
#define MPU_SRAM_REGION     (5)
#define MPU_PERIPH_REGION   (4)
#define MPU_PLIC_REGION     (3)
#define MPU_MMIO_REGION     (2)
#define MPU_MMCFG_REGION    (1)
#define MPU_FLASH_REGION    (0)

#define PLF_FLASH_BASE      (0)
#define PLF_FLASH_SIZE      (4*1024*1024U) + (512*1024U)
#define PLF_FLASH_MASK      (0xFF800000U)
#define PLF_FLASH_ATTR      (SCR_MPU_CTRL_MT_WEAKLY | SCR_MPU_CTRL_ALL)

#define PLF_QSPI0_BASE      (0x10000000)
#define PLF_QSPI0_SIZE      (32*1024*1024U)
#define PLF_QSPI0_MASK      (0xF0000000U)
#define PLF_QSPI0_ATTR      (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_SRAM_BASE       (0x20000000)
#define PLF_SRAM_SIZE       (1024*1024U)
#define PLF_SRAM_MASK       (0xFFF00000U)
#define PLF_SRAM_ATTR       (SCR_MPU_CTRL_MT_WEAKLY | SCR_MPU_CTRL_ALL)

#define PLF_PERIPH_BASE     (0x40000000)
#define PLF_PERIPH_SIZE     (512*1024*1024U)
#define PLF_PERIPH_MASK     (0xE0000000U)
#define PLF_PERIPH_ATTR     (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_AHB_BASE        (0x40000000)
#define PLF_AHB_SIZE        (32*1024*1024U)
#define PLF_AHB_MASK        (0xFE000000U)
#define PLF_AHB_ATTR        (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_APB_BASE        (0x50000000)
#define PLF_APB_SIZE        (32*1024*1024U)
#define PLF_APB_MASK        (0xFE000000U)
#define PLF_APB_ATTR        (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_EXT_BASE        (0x60000000)
#define PLF_EXT_SIZE        (32*1024*1024U)
#define PLF_EXT_MASK        (0xF0000000U)
#define PLF_EXT_ATTR        (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_QSPI1_BASE      (0x60000000)
#define PLF_QSPI1_SIZE      (32*1024*1024U)
#define PLF_QSPI1_MASK      (0xF0000000U)
#define PLF_QSPI1_ATTR      (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define PLF_SDRAM_BASE      (0x80000000)
#define PLF_SDRAM_SIZE      (32*1024*1024U)
#define PLF_SDRAM_MASK      (0xF0000000U)
#define PLF_SDRAM_ATTR      (SCR_MPU_CTRL_MT_STRONG | SCR_MPU_CTRL_ALL)

#define REGION_MMCFG_BASE   (0xE0000000)
#define REGION_MMCFG_MASK   (0xFF000000)
#define REGION_MMIO_ADDR    (0xFF000000)
#define REGION_MMIO_MASK    (0xFF000000)
#define REGION_PLIC_ADDR    (0xFE000000)
#define REGION_PLIC_MASK    (0xFF000000)

#define TIMER_ADDR          (REGION_MMCFG_BASE)

#define MEM_MTIME_CTRL      (TIMER_ADDR + 0x00)
#define MEM_MTIME_DIV       (TIMER_ADDR + 0x04)
#define MEM_MTIME           (TIMER_ADDR + 0x08)
#define MEM_MTIMEH          (TIMER_ADDR + 0x0C)
#define MEM_MTIMECMP        (TIMER_ADDR + 0x10)
#define MEM_MTIMECMPH       (TIMER_ADDR + 0x14)

#define PLF_L2CTL_BASE      (TIMER_ADDR + 0x1000)
#define PLF_L2C_BANKS       (4)

#endif // SCR_PLATFORM_CONFIG_SCR5_H
