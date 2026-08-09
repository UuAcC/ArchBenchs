/*==============================================================================
 * Управление периферией на плате NIIET-DEV-K1921VG1T
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

//-- Includes ------------------------------------------------------------------
#include "bsp.h"

//-- Private variables ---------------------------------------------------------
static volatile uint32_t btn_press_event = 0;

//-- Functions -----------------------------------------------------------------
void BSP_LED_Init()
{
	RCU->CGCFGAHB_bit.LED_PORT_EN = 1;
	RCU->RSTDISAHB_bit.LED_PORT_EN = 1;
	LED_PORT->OUTENSET = LEDS_MSK;
	LED_PORT->DATAOUTSET = LEDS_MSK;
}

void BSP_LED_Toggle(uint32_t leds)
{
	LED_PORT->DATAOUTTGL = leds;
}

void BSP_LED_On(uint32_t leds)
{
	LED_PORT->DATAOUTCLR = leds;
}

void BSP_LED_Off(uint32_t leds)
{
	LED_PORT->DATAOUTSET = leds;
}

void BSP_Btn_Init()
{
	// todo
}

uint32_t BSP_Btn_IsPressed()
{
    if (btn_press_event) {
        btn_press_event = 0;
        return 1;
    } else
        return 0;
}

void BSP_SRAM_Init()
{
	uint16_t tmp;

	//Adr[0:7] : D8-D15
	RCU->CGCFGAHB_bit.SDRAM_ADR_0_7_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_ADR_0_7_PORT_EN = 1;
	SDRAM_ADR_0_7_PORT->ALTFUNCNUM1 |= SDRAM_ADR_0_7_ALTFUNCNUM1;
	SDRAM_ADR_0_7_PORT->ALTFUNCSET = SDRAM_ADR_0_7_PIN_MSK;
	//Adr[8:12] : E0-E4
	RCU->CGCFGAHB_bit.SDRAM_ADR_8_12_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_ADR_8_12_PORT_EN = 1;
	SDRAM_ADR_8_12_PORT->ALTFUNCNUM0 |= SDRAM_ADR_8_12_ALTFUNCNUM0;
	SDRAM_ADR_8_12_PORT->ALTFUNCSET = SDRAM_ADR_8_12_PIN_MSK;

	//Data[0:15] : G0-G15
	RCU->CGCFGAHB_bit.SDRAM_DATA_0_15_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_DATA_0_15_PORT_EN = 1;
	SDRAM_DATA_0_15_PORT->ALTFUNCNUM0 = SDRAM_DATA_0_15_ALTFUNCNUM0;
	SDRAM_DATA_0_15_PORT->ALTFUNCNUM1 = SDRAM_DATA_0_15_ALTFUNCNUM1;
	SDRAM_DATA_0_15_PORT->ALTFUNCSET = SDRAM_DATA_0_15_PIN_MSK;
	//Data[16:31] : F0-F15
	RCU->CGCFGAHB_bit.SDRAM_DATA_16_31_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_DATA_16_31_PORT_EN = 1;
	SDRAM_DATA_16_31_PORT->ALTFUNCNUM0 = SDRAM_DATA_16_31_ALTFUNCNUM0;
	SDRAM_DATA_16_31_PORT->ALTFUNCNUM1 = SDRAM_DATA_16_31_ALTFUNCNUM1;
	SDRAM_DATA_16_31_PORT->ALTFUNCSET = SDRAM_DATA_16_31_PIN_MSK;
	//BA : E5-E6
	RCU->CGCFGAHB_bit.SDRAM_BA_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_BA_PORT_EN = 1;
	SDRAM_BA_PORT->ALTFUNCNUM0 |= SDRAM_BA_ALTFUNCNUM0;
	SDRAM_BA_PORT->ALTFUNCSET = SDRAM_BA_PIN_MSK;
	//DQ : E12-E15
	RCU->CGCFGAHB_bit.SDRAM_DQ_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_DQ_PORT_EN = 1;
	SDRAM_DQ_PORT->ALTFUNCNUM1 |= SDRAM_DQ_ALTFUNCNUM1;
	SDRAM_DQ_PORT->ALTFUNCSET = SDRAM_DQ_PIN_MSK;
	//WE : E8
	RCU->CGCFGAHB_bit.SDRAM_WE_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_WE_PORT_EN = 1;
	SDRAM_WE_PORT->ALTFUNCNUM1 |= SDRAM_WE_ALTFUNCNUM1;
	SDRAM_WE_PORT->ALTFUNCSET = SDRAM_WE_PIN_MSK;
	//CAS : E10
	RCU->CGCFGAHB_bit.SDRAM_CAS_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_CAS_PORT_EN = 1;
	SDRAM_CAS_PORT->ALTFUNCNUM1 |= SDRAM_CAS_ALTFUNCNUM1;
	SDRAM_CAS_PORT->ALTFUNCSET = SDRAM_CAS_PIN_MSK;
	//RAS : E9
	RCU->CGCFGAHB_bit.SDRAM_RAS_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_RAS_PORT_EN = 1;
	SDRAM_RAS_PORT->ALTFUNCNUM1 |= SDRAM_RAS_ALTFUNCNUM1;
	SDRAM_RAS_PORT->ALTFUNCSET = SDRAM_RAS_PIN_MSK;
	//CS : E11
	RCU->CGCFGAHB_bit.SDRAM_CS_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_CS_PORT_EN = 1;
	SDRAM_CS_PORT->ALTFUNCNUM1 |= SDRAM_CS_ALTFUNCNUM1;
	SDRAM_CS_PORT->ALTFUNCSET = SDRAM_CS_PIN_MSK;
	//CLK : D7
	RCU->CGCFGAHB_bit.SDRAM_CLK_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_CLK_PORT_EN = 1;
	SDRAM_CLK_PORT->ALTFUNCNUM0 |= SDRAM_CLK_ALTFUNCNUM0;
	SDRAM_CLK_PORT->ALTFUNCSET = SDRAM_CLK_PIN_MSK;
	//CKE : E7
	RCU->CGCFGAHB_bit.SDRAM_CKE_PORT_EN = 1;
	RCU->RSTDISAHB_bit.SDRAM_CKE_PORT_EN = 1;
	SDRAM_CKE_PORT->ALTFUNCNUM0 |= SDRAM_CKE_ALTFUNCNUM0;
	SDRAM_CKE_PORT->ALTFUNCSET = SDRAM_CKE_PIN_MSK;

	//SDRAM CLK CONFIG
	RCU->CGCFGAPB0_bit.SDRAMEN = 1;
	RCU->RSTDISAPB0_bit.SDRAMEN = 1;
	SIU -> EMMUXCTRL_bit.SDRAMEN = 1;
	RCU->SDRAMCFG_bit.CLKSEL = 0; // PLL0
	RCU->SDRAMCFG_bit.CLKEN = 1;
	RCU->SDRAMCFG_bit.DIVN = 0;
	RCU->SDRAMCFG_bit.DIVEN = 1;
	//Delay 100us
	tmp=1200;
	while(tmp--) __asm("NOP");
	RCU->SDRAMCFG_bit.RSTDIS = 1;

	//SDRAM Mode CONFIG
	SDRAM->MODE_bit.OPMODE = 0;
	SDRAM->MODE_bit.WBMODE = 0; // Режим пакетной записи. 0 - выключен
	SDRAM->MODE_bit.BURST_TYPE = 0; // Тип пакета. 0 - последовательный
	SDRAM->MODE_bit.BURST_LENGTH = 0; // Длина пакета - 1.
	SDRAM->MODE_bit.CAS_LATENCY = 2; //Задержка CAS. Задержка в тактовых циклах между регистрацией команды чтения
									 //и доступностью первого фрагмента выходных данных

	//SDRAM Control CONFIG
	SDRAM->CONTROL = 0;
	SDRAM->CONTROL_bit.COLUMN_WIDTH = 1; // Количество разрядов для адресации столбцов. 3 - 11 бит
	SDRAM->CONTROL_bit.DATA_WIDTH = 0; // Ширина данных SDRAM памяти (размер слова данных). 0 - 32 бита
	SDRAM->CONTROL_bit.REQ_DEPTH = 3; // Сколько запросов должен содержать внутренний буфер
	SDRAM->CONTROL_bit.SLOW_BUS = 0; // бит должен быть установлен, если системная тактовая частота меньше частоты SDRAM

	//SDRAM Refresh CONFIG
	SDRAM->REFRESH_bit.RF_MAX = 2; // Максимальное количество строк, обновляемых за один раз
	SDRAM->REFRESH_bit.RF_TIME = 120; // Период между командами автоматического обновления, выдаваемыми контроллером

	SDRAM->CONTROL_bit.ENABLE = 1; // Бит включения SDRAM контроллера
	while (SDRAM -> STATUS  == 0) {};
}

//-- IRQ handlers --------------------------------------------------------------
void BTN_IRQ_HANDLER()
{
    BTN_PORT->INTSTATUS = BTN_PIN_MSK;
    btn_press_event = 1;
}
