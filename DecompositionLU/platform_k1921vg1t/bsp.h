/*==============================================================================
 * Определения для периферии платы NIIET-DEV-K1921VG1T
 *------------------------------------------------------------------------------
 * НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
 *==============================================================================
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2025 АО "НИИЭТ"
 *==============================================================================
 */

#ifndef BSP_H
#define BSP_H

#ifdef __cplusplus
extern "C" {
#endif

//-- Includes ------------------------------------------------------------------
#include "K1921VG1T.h"
#include <stdint.h>

//-- Defines -------------------------------------------------------------------
//LEDs
#define LED_PORT GPIOC
#define LED_PORT_EN GPIOCEN
#define LED_PIN_MSK 0xF000
#define LED0_POS 12
#define LED1_POS 13
#define LED2_POS 14
#define LED3_POS 15
#define LED0_MSK (1 << LED0_POS)
#define LED1_MSK (1 << LED1_POS)
#define LED2_MSK (1 << LED2_POS)
#define LED3_MSK (1 << LED3_POS)
#define LEDS_MSK 0xF000

//Button USER
#define BTN_PORT GPIOB
#define BTN_PORT_EN GPIOBEN
#define BTN_IRQ_N GPIOB_IRQn
#define BTN_IRQ_HANDLER GPIOB_IRQHandler
#define BTN_PIN_POS 3
#define BTN_PIN_MSK (1 << BTN_PIN_POS)

//SDRAM
#define SDRAM_ADR_0_7_PORT 		GPIOD
#define SDRAM_ADR_0_7_PORT_EN 	GPIODEN
#define SDRAM_ADR_0_7_PIN_MSK	0xFF00
#define SDRAM_ADR_0_7_ALTFUNCNUM1	0x22222222

#define SDRAM_ADR_8_12_PORT 	GPIOE
#define SDRAM_ADR_8_12_PORT_EN 	GPIOEEN
#define SDRAM_ADR_8_12_PIN_MSK	0x001F
#define SDRAM_ADR_8_12_ALTFUNCNUM0	0x00022222

#define SDRAM_DATA_0_15_PORT 	GPIOG
#define SDRAM_DATA_0_15_PORT_EN GPIOGEN
#define SDRAM_DATA_0_15_PIN_MSK	0xFFFF
#define SDRAM_DATA_0_15_ALTFUNCNUM0	0x22222222
#define SDRAM_DATA_0_15_ALTFUNCNUM1	0x22222222

#define SDRAM_DATA_16_31_PORT 		GPIOF
#define SDRAM_DATA_16_31_PORT_EN 	GPIOFEN
#define SDRAM_DATA_16_31_PIN_MSK	0xFFFF
#define SDRAM_DATA_16_31_ALTFUNCNUM0	0x22222222
#define SDRAM_DATA_16_31_ALTFUNCNUM1	0x22222222

#define SDRAM_BA_PORT 		GPIOE
#define SDRAM_BA_PORT_EN 	GPIOEEN
#define SDRAM_BA_PIN_MSK	0x0060
#define SDRAM_BA_ALTFUNCNUM0	0x02200000

#define SDRAM_DQ_PORT 		GPIOE
#define SDRAM_DQ_PORT_EN 	GPIOEEN
#define SDRAM_DQ_PIN_MSK	0xF000
#define SDRAM_DQ_ALTFUNCNUM1	0x22220000

#define SDRAM_WE_PORT 		GPIOE
#define SDRAM_WE_PORT_EN 	GPIOEEN
#define SDRAM_WE_PIN_MSK	0x0100
#define SDRAM_WE_ALTFUNCNUM1	0x0002

#define SDRAM_CAS_PORT 		GPIOE
#define SDRAM_CAS_PORT_EN 	GPIOEEN
#define SDRAM_CAS_PIN_MSK	0x0400
#define SDRAM_CAS_ALTFUNCNUM1	0x0200

#define SDRAM_RAS_PORT 		GPIOE
#define SDRAM_RAS_PORT_EN 	GPIOEEN
#define SDRAM_RAS_PIN_MSK	0x0200
#define SDRAM_RAS_ALTFUNCNUM1	0x0020

#define SDRAM_CS_PORT 		GPIOE
#define SDRAM_CS_PORT_EN 	GPIOEEN
#define SDRAM_CS_PIN_MSK	0x0800
#define SDRAM_CS_ALTFUNCNUM1	0x2000

#define SDRAM_CLK_PORT 		GPIOD
#define SDRAM_CLK_PORT_EN 	GPIODEN
#define SDRAM_CLK_PIN_MSK	0x0080
#define SDRAM_CLK_ALTFUNCNUM0	0x20000000

#define SDRAM_CKE_PORT 		GPIOE
#define SDRAM_CKE_PORT_EN 	GPIOEEN
#define SDRAM_CKE_PIN_MSK	0x0080
#define SDRAM_CKE_ALTFUNCNUM0	0x20000000

//-- Functions -----------------------------------------------------------------
void BSP_LED_Init(void);
void BSP_LED_On(uint32_t leds);
void BSP_LED_Off(uint32_t leds);
void BSP_LED_Toggle(uint32_t leds);
void BSP_Btn_Init(void);
void BSP_SRAM_Init(void);
uint32_t BSP_Btn_IsPressed(void);

inline uint32_t BSP_SDRAM_Read(uint32_t addr)
{
    return *(volatile uint32_t*)(MEM_SDRAM_BASE + addr);
}
inline void BSP_SDRAM_Write(uint32_t addr, uint32_t data)
{
    *(volatile uint32_t*)(MEM_SDRAM_BASE + addr) = data;
}

#ifdef __cplusplus
}
#endif

#endif // BSP_H
