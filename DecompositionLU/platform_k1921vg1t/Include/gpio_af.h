// AFn - Alternative Function n (1..4)

#ifndef GPIO_AF_H_DEFINED
  #define GPIO_AF_H_DEFINED

  #define GPIO_ALTFUNCNUM_WIDTH  (4)
  #define GPIO_OUTMODE_WIDTH     (2)
  #define GPIO_PULLMODE_WIDTH    (2)

  #define GPIO_OUTMODE_PIN_PP    (0)  /*!< Push-pull output */
  #define GPIO_OUTMODE_PIN_OD    (1)  /*!< Open drain output */
  #define GPIO_OUTMODE_PIN_OS    (2)  /*!< Open source output */

  #define GPIO_AF1               (1)
  #define GPIO_AF2               (2)
  #define GPIO_AF3               (3)
  #define GPIO_AF4               (4)

  // SYSTEM
  #define GPIOA_AF2_CLKOUT_OFFSET        ( 2)
  #define GPIOD_AF1_CLKOUT_OFFSET        ( 6)
  #define GPIOA_AF2_EXTPLLCLK_OFFSET     ( 3)
  #define GPIOD_AF1_EXTPLLCLK_OFFSET     ( 7)

  void Connect_CLKOUT_GPIOA_AF2(void);
  void Connect_CLKOUT_GPIOD_AF1(void);
  void Connect_EXTPLLCLK_GPIOA_AF2(void);
  void Connect_EXTPLLCLK_GPIOD_AF1(void);

  // UART
  #define GPIOB_AF3_UART_TX_0_OFFSET     ( 1)
  #define GPIOB_AF3_UART_TX_1_OFFSET     ( 5)
  #define GPIOB_AF3_UART_TX_2_OFFSET     ( 9)
  #define GPIOB_AF3_UART_TX_3_OFFSET     (13)
  #define GPIOE_AF1_UART_TX_4_OFFSET     ( 1)
  #define GPIOG_AF3_UART_TX_4_OFFSET     ( 5)
  #define GPIOE_AF1_UART_TX_5_OFFSET     ( 3)
  #define GPIOG_AF3_UART_TX_5_OFFSET     ( 7)
  #define GPIOE_AF1_UART_TX_6_OFFSET     ( 9)
  #define GPIOF_AF3_UART_TX_6_OFFSET     ( 5)
  #define GPIOE_AF1_UART_TX_7_OFFSET     (11)
  #define GPIOF_AF3_UART_TX_7_OFFSET     ( 7)
  #define GPIOB_AF3_UART_RX_0_OFFSET     ( 0)
  #define GPIOB_AF3_UART_RX_1_OFFSET     ( 4)
  #define GPIOB_AF3_UART_RX_2_OFFSET     ( 8)
  #define GPIOB_AF3_UART_RX_3_OFFSET     (12)
  #define GPIOE_AF1_UART_RX_4_OFFSET     ( 0)
  #define GPIOG_AF3_UART_RX_4_OFFSET     ( 4)
  #define GPIOE_AF1_UART_RX_5_OFFSET     ( 2)
  #define GPIOG_AF3_UART_RX_5_OFFSET     ( 6)
  #define GPIOE_AF1_UART_RX_6_OFFSET     ( 8)
  #define GPIOF_AF3_UART_RX_6_OFFSET     ( 4)
  #define GPIOE_AF1_UART_RX_7_OFFSET     (10)
  #define GPIOF_AF3_UART_RX_7_OFFSET     ( 6)

  void Connect_UART0_GPIOB_AF3(void);
  void Connect_UART1_GPIOB_AF3(void);
  void Connect_UART2_GPIOB_AF3(void);
  void Connect_UART3_GPIOB_AF3(void);
  void Connect_UART4_GPIOE_AF1(void);
  void Connect_UART4_GPIOG_AF3(void);
  void Connect_UART5_GPIOE_AF1(void);
  void Connect_UART5_GPIOG_AF3(void);
  void Connect_UART6_GPIOE_AF1(void);
  void Connect_UART6_GPIOF_AF3(void);
  void Connect_UART7_GPIOE_AF1(void);
  void Connect_UART7_GPIOF_AF3(void);

  // LIN
  #define GPIOB_AF3_LIN_TX_0_OFFSET      ( 3)
  #define GPIOB_AF3_LIN_TX_1_OFFSET      ( 7)
  #define GPIOB_AF3_LIN_TX_2_OFFSET      (11)
  #define GPIOB_AF3_LIN_TX_3_OFFSET      (15)
  #define GPIOE_AF1_LIN_TX_4_OFFSET      ( 5)
  #define GPIOF_AF3_LIN_TX_4_OFFSET      ( 1)
  #define GPIOE_AF1_LIN_TX_5_OFFSET      ( 7)
  #define GPIOF_AF3_LIN_TX_5_OFFSET      ( 3)
  #define GPIOE_AF1_LIN_TX_6_OFFSET      (13)
  #define GPIOG_AF3_LIN_TX_6_OFFSET      (13)
  #define GPIOE_AF1_LIN_TX_7_OFFSET      (15)
  #define GPIOG_AF3_LIN_TX_7_OFFSET      (15)
  #define GPIOB_AF3_LIN_RX_0_OFFSET      ( 2)
  #define GPIOB_AF3_LIN_RX_1_OFFSET      ( 6)
  #define GPIOB_AF3_LIN_RX_2_OFFSET      (10)
  #define GPIOB_AF3_LIN_RX_3_OFFSET      (14)
  #define GPIOE_AF1_LIN_RX_4_OFFSET      ( 4)
  #define GPIOF_AF3_LIN_RX_4_OFFSET      ( 0)
  #define GPIOE_AF1_LIN_RX_5_OFFSET      ( 6)
  #define GPIOF_AF3_LIN_RX_5_OFFSET      ( 2)
  #define GPIOE_AF1_LIN_RX_6_OFFSET      (12)
  #define GPIOG_AF3_LIN_RX_6_OFFSET      (12)
  #define GPIOE_AF1_LIN_RX_7_OFFSET      (14)
  #define GPIOG_AF3_LIN_RX_7_OFFSET      (14)

  void Connect_LIN0_GPIOB_AF3(void);
  void Connect_LIN1_GPIOB_AF3(void);
  void Connect_LIN2_GPIOB_AF3(void);
  void Connect_LIN3_GPIOB_AF3(void);
  void Connect_LIN4_GPIOE_AF1(void);
  void Connect_LIN4_GPIOF_AF3(void);
  void Connect_LIN5_GPIOE_AF1(void);
  void Connect_LIN5_GPIOF_AF3(void);
  void Connect_LIN6_GPIOE_AF1(void);
  void Connect_LIN6_GPIOG_AF3(void);
  void Connect_LIN7_GPIOE_AF1(void);
  void Connect_LIN7_GPIOG_AF3(void);

  // SPI
  #define GPIOA_AF1_SPI_RX_0_OFFSET      ( 2)
  #define GPIOC_AF3_SPI_RX_0_OFFSET      (10)
  #define GPIOA_AF1_SPI_RX_1_OFFSET      ( 6)
  #define GPIOC_AF3_SPI_RX_1_OFFSET      (14)
  #define GPIOA_AF1_SPI_RX_2_OFFSET      (10)
  #define GPIOD_AF3_SPI_RX_2_OFFSET      (14)
  #define GPIOA_AF1_SPI_RX_3_OFFSET      (14)
  #define GPIOE_AF3_SPI_RX_3_OFFSET      (14)
  #define GPIOB_AF2_SPI_RX_4_OFFSET      ( 2)
  #define GPIOF_AF3_SPI_RX_4_OFFSET      (10)
  #define GPIOB_AF2_SPI_RX_5_OFFSET      ( 6)
  #define GPIOF_AF3_SPI_RX_5_OFFSET      (14)
  #define GPIOB_AF2_SPI_RX_6_OFFSET      (10)
  #define GPIOE_AF3_SPI_RX_6_OFFSET      ( 2)
  #define GPIOB_AF2_SPI_RX_7_OFFSET      (14)
  #define GPIOA_AF1_SPI_TX_0_OFFSET      ( 3)
  #define GPIOC_AF3_SPI_TX_0_OFFSET      (11)
  #define GPIOA_AF1_SPI_TX_1_OFFSET      ( 7)
  #define GPIOC_AF3_SPI_TX_1_OFFSET      (15)
  #define GPIOA_AF1_SPI_TX_2_OFFSET      (11)
  #define GPIOD_AF3_SPI_TX_2_OFFSET      (15)
  #define GPIOA_AF1_SPI_TX_3_OFFSET      (15)
  #define GPIOE_AF3_SPI_TX_3_OFFSET      (15)
  #define GPIOB_AF2_SPI_TX_4_OFFSET      ( 3)
  #define GPIOF_AF3_SPI_TX_4_OFFSET      (11)
  #define GPIOB_AF2_SPI_TX_5_OFFSET      ( 7)
  #define GPIOF_AF3_SPI_TX_5_OFFSET      (15)
  #define GPIOB_AF2_SPI_TX_6_OFFSET      (11)
  #define GPIOE_AF3_SPI_TX_6_OFFSET      ( 3)
  #define GPIOB_AF2_SPI_TX_7_OFFSET      (15)
  #define GPIOA_AF1_SPI_CLK_0_OFFSET     ( 0)
  #define GPIOC_AF3_SPI_CLK_0_OFFSET     ( 8)
  #define GPIOA_AF1_SPI_CLK_1_OFFSET     ( 4)
  #define GPIOC_AF3_SPI_CLK_1_OFFSET     (12)
  #define GPIOA_AF1_SPI_CLK_2_OFFSET     ( 8)
  #define GPIOD_AF3_SPI_CLK_2_OFFSET     (12)
  #define GPIOA_AF1_SPI_CLK_3_OFFSET     (12)
  #define GPIOE_AF3_SPI_CLK_3_OFFSET     (12)
  #define GPIOB_AF2_SPI_CLK_4_OFFSET     ( 0)
  #define GPIOF_AF3_SPI_CLK_4_OFFSET     ( 8)
  #define GPIOB_AF2_SPI_CLK_5_OFFSET     ( 4)
  #define GPIOF_AF3_SPI_CLK_5_OFFSET     (12)
  #define GPIOB_AF2_SPI_CLK_6_OFFSET     ( 8)
  #define GPIOE_AF3_SPI_CLK_6_OFFSET     ( 0)
  #define GPIOB_AF2_SPI_CLK_7_OFFSET     (12)
  #define GPIOA_AF1_SPI_FSS_0_OFFSET     ( 1)
  #define GPIOC_AF3_SPI_FSS_0_OFFSET     ( 9)
  #define GPIOA_AF1_SPI_FSS_1_OFFSET     ( 5)
  #define GPIOC_AF3_SPI_FSS_1_OFFSET     (13)
  #define GPIOA_AF1_SPI_FSS_2_OFFSET     ( 9)
  #define GPIOD_AF3_SPI_FSS_2_OFFSET     (13)
  #define GPIOA_AF1_SPI_FSS_3_OFFSET     (13)
  #define GPIOE_AF3_SPI_FSS_3_OFFSET     (13)
  #define GPIOB_AF2_SPI_FSS_4_OFFSET     ( 1)
  #define GPIOF_AF3_SPI_FSS_4_OFFSET     ( 9)
  #define GPIOB_AF2_SPI_FSS_5_OFFSET     ( 5)
  #define GPIOF_AF3_SPI_FSS_5_OFFSET     (13)
  #define GPIOB_AF2_SPI_FSS_6_OFFSET     ( 9)
  #define GPIOE_AF3_SPI_FSS_6_OFFSET     ( 1)
  #define GPIOB_AF2_SPI_FSS_7_OFFSET     (13)

  void Connect_SPI0_GPIOA_AF1(void);
  void Connect_SPI0_GPIOC_AF3(void);
  void Connect_SPI1_GPIOA_AF1(void);
  void Connect_SPI1_GPIOC_AF3(void);
  void Connect_SPI2_GPIOA_AF1(void);
  void Connect_SPI2_GPIOD_AF3(void);
  void Connect_SPI3_GPIOA_AF1(void);
  void Connect_SPI3_GPIOE_AF3(void);
  void Connect_SPI4_GPIOB_AF2(void);
  void Connect_SPI4_GPIOF_AF3(void);
  void Connect_SPI5_GPIOB_AF2(void);
  void Connect_SPI5_GPIOF_AF3(void);
  void Connect_SPI6_GPIOB_AF2(void);
  void Connect_SPI6_GPIOE_AF3(void);
  void Connect_SPI7_GPIOB_AF2(void);

  // I2S
  #define GPIOC_AF2_I2S_BCLKT_0_OFFSET   ( 9)
  #define GPIOA_AF3_I2S_BCLKT_1_OFFSET   ( 8)
  #define GPIOC_AF2_I2S_LRCLKT_0_OFFSET  (10)
  #define GPIOA_AF3_I2S_LRCLKT_1_OFFSET  ( 9)
  #define GPIOC_AF2_I2S_BCLKR_0_OFFSET   (11)
  #define GPIOA_AF3_I2S_BCLKR_1_OFFSET   (10)
  #define GPIOC_AF2_I2S_LRCLKR_0_OFFSET  (12)
  #define GPIOA_AF3_I2S_LRCLKR_1_OFFSET  (11)
  #define GPIOC_AF2_I2S_SDI_0_OFFSET     (13)
  #define GPIOA_AF3_I2S_SDI_1_OFFSET     (12)
  #define GPIOC_AF2_I2S_SDO_0_OFFSET     (14)
  #define GPIOA_AF3_I2S_SDO_1_OFFSET     (13)
  #define GPIOC_AF2_I2S_MCLK_0_OFFSET    (15)
  #define GPIOA_AF3_I2S_MCLK_1_OFFSET    (14)

  void Connect_I2S0_GPIOC_AF2(void);
  void Connect_I2S1_GPIOA_AF3(void);

  // I2C
  #define GPIOD_AF2_I2C_SDA_0_OFFSET     ( 2)
  #define GPIOF_AF1_I2C_SDA_0_OFFSET     ( 6)
  #define GPIOB_AF1_I2C_SDA_1_OFFSET     (14)
  #define GPIOD_AF2_I2C_SDA_1_OFFSET     ( 0)
  #define GPIOD_AF2_I2C_SCL_0_OFFSET     ( 3)
  #define GPIOF_AF1_I2C_SCL_0_OFFSET     ( 7)
  #define GPIOB_AF1_I2C_SCL_1_OFFSET     (15)
  #define GPIOD_AF2_I2C_SCL_1_OFFSET     ( 1)

  void Connect_I2C0_GPIOD_AF2(void);
  void Connect_I2C0_GPIOF_AF1(void);
  void Connect_I2C1_GPIOD_AF2(void);
  void Connect_I2C1_GPIOB_AF1(void);

  // CAN
  #define GPIOA_AF3_CAN_TX_0_OFFSET      ( 1)
  #define GPIOD_AF1_CAN_TX_0_OFFSET      ( 9)
  #define GPIOA_AF3_CAN_TX_1_OFFSET      ( 3)
  #define GPIOD_AF1_CAN_TX_1_OFFSET      (11)
  #define GPIOA_AF3_CAN_TX_2_OFFSET      ( 5)
  #define GPIOD_AF1_CAN_TX_2_OFFSET      (13)
  #define GPIOA_AF3_CAN_TX_3_OFFSET      ( 7)
  #define GPIOD_AF1_CAN_TX_3_OFFSET      (15)
  #define GPIOB_AF1_CAN_TX_4_OFFSET      ( 1)
  #define GPIOG_AF3_CAN_TX_4_OFFSET      ( 1)
  #define GPIOB_AF1_CAN_TX_5_OFFSET      ( 3)
  #define GPIOG_AF3_CAN_TX_5_OFFSET      ( 3)
  #define GPIOB_AF1_CAN_TX_6_OFFSET      ( 5)
  #define GPIOG_AF3_CAN_TX_6_OFFSET      ( 9)
  #define GPIOB_AF1_CAN_TX_7_OFFSET      ( 7)
  #define GPIOG_AF3_CAN_TX_7_OFFSET      (11)
  #define GPIOA_AF3_CAN_RX_0_OFFSET      ( 0)
  #define GPIOD_AF1_CAN_RX_0_OFFSET      ( 8)
  #define GPIOA_AF3_CAN_RX_1_OFFSET      ( 2)
  #define GPIOD_AF1_CAN_RX_1_OFFSET      (10)
  #define GPIOA_AF3_CAN_RX_2_OFFSET      ( 4)
  #define GPIOD_AF1_CAN_RX_2_OFFSET      (12)
  #define GPIOA_AF3_CAN_RX_3_OFFSET      ( 6)
  #define GPIOD_AF1_CAN_RX_3_OFFSET      (14)
  #define GPIOB_AF1_CAN_RX_4_OFFSET      ( 0)
  #define GPIOG_AF3_CAN_RX_4_OFFSET      ( 0)
  #define GPIOB_AF1_CAN_RX_5_OFFSET      ( 2)
  #define GPIOG_AF3_CAN_RX_5_OFFSET      ( 2)
  #define GPIOB_AF1_CAN_RX_6_OFFSET      ( 4)
  #define GPIOG_AF3_CAN_RX_6_OFFSET      ( 8)
  #define GPIOB_AF1_CAN_RX_7_OFFSET      ( 6)
  #define GPIOG_AF3_CAN_RX_7_OFFSET      (10)

  void Connect_CAN0_GPIOA_AF3(void);
  void Connect_CAN0_GPIOD_AF1(void);
  void Connect_CAN1_GPIOA_AF3(void);
  void Connect_CAN1_GPIOD_AF1(void);
  void Connect_CAN2_GPIOA_AF3(void);
  void Connect_CAN2_GPIOD_AF1(void);
  void Connect_CAN3_GPIOA_AF3(void);
  void Connect_CAN3_GPIOD_AF1(void);
  void Connect_CAN4_GPIOB_AF1(void);
  void Connect_CAN4_GPIOG_AF3(void);
  void Connect_CAN5_GPIOB_AF1(void);
  void Connect_CAN5_GPIOG_AF3(void);
  void Connect_CAN6_GPIOB_AF1(void);
  void Connect_CAN6_GPIOG_AF3(void);
  void Connect_CAN7_GPIOB_AF1(void);
  void Connect_CAN7_GPIOG_AF3(void);

  // USB
  #define GPIOF_AF4_USB0_DATA_0_OFFSET   ( 0)
  #define GPIOF_AF4_USB0_DATA_1_OFFSET   ( 1)
  #define GPIOF_AF4_USB0_DATA_2_OFFSET   ( 2)
  #define GPIOF_AF4_USB0_DATA_3_OFFSET   ( 3)
  #define GPIOF_AF4_USB0_DATA_4_OFFSET   ( 4)
  #define GPIOF_AF4_USB0_DATA_5_OFFSET   ( 5)
  #define GPIOF_AF4_USB0_DATA_6_OFFSET   ( 6)
  #define GPIOF_AF4_USB0_DATA_7_OFFSET   ( 7)
  #define GPIOB_AF4_USB1_DATA_0_OFFSET   ( 7)
  #define GPIOB_AF4_USB1_DATA_1_OFFSET   ( 8)
  #define GPIOB_AF4_USB1_DATA_2_OFFSET   ( 9)
  #define GPIOB_AF4_USB1_DATA_3_OFFSET   (10)
  #define GPIOB_AF4_USB1_DATA_4_OFFSET   (11)
  #define GPIOB_AF4_USB1_DATA_5_OFFSET   (12)
  #define GPIOB_AF4_USB1_DATA_6_OFFSET   (13)
  #define GPIOB_AF4_USB1_DATA_7_OFFSET   (14)
  #define GPIOF_AF4_USB0_CLK_OFFSET      ( 8)
  #define GPIOF_AF4_USB0_RESET_OFFSET    ( 9)
  #define GPIOF_AF4_USB0_XCVRSELECT0_OFFSET (10)
  #define GPIOF_AF4_USB0_XCVRSELECT1_OFFSET (11)
  #define GPIOF_AF4_USB0_TERMSELECT_OFFSET (12)
  #define GPIOF_AF4_USB0_SUSPENDM_OFFSET (13)
  #define GPIOF_AF4_USB0_OPMODE0_OFFSET (14)
  #define GPIOF_AF4_USB0_OPMODE1_OFFSET (15)
  #define GPIOG_AF4_USB0_LINESTATE0_OFFSET ( 0)
  #define GPIOG_AF4_USB0_LINESTATE1_OFFSET ( 1)
  #define GPIOG_AF4_USB0_TXVALID_OFFSET  ( 2)
  #define GPIOG_AF4_USB0_TXREADY_OFFSET  ( 3)
  #define GPIOG_AF4_USB0_RXACTIVE_OFFSET ( 4)
  #define GPIOG_AF4_USB0_RXVALID_OFFSET  ( 5)
  #define GPIOG_AF4_USB0_RXERROR_OFFSET  ( 6)
  #define GPIOG_AF4_USB0_VBUSVALID_OFFSET ( 7)
  #define GPIOG_AF4_USB0_CHRGVBUS_OFFSET ( 8)
  #define GPIOG_AF4_USB0_DISCHRGVBUS_OFFSET ( 9)
  #define GPIOG_AF4_USB0_DPPULLDOWN_OFFSET (10)
  #define GPIOG_AF4_USB0_DMPULLDOWN_OFFSET (11)
  #define GPIOG_AF4_USB0_IDPULLUP_OFFSET (12)
  #define GPIOG_AF4_USB0_HOSTDISCONNECT_OFFSET (13)
  #define GPIOB_AF4_USB1_CLK_OFFSET      (15)
  #define GPIOC_AF4_USB1_RESET_OFFSET    ( 0)
  #define GPIOC_AF4_USB1_XCVRSELECT0_OFFSET ( 1)
  #define GPIOC_AF4_USB1_XCVRSELECT1_OFFSET ( 2)
  #define GPIOC_AF4_USB1_TERMSELECT_OFFSET ( 3)
  #define GPIOC_AF4_USB1_SUSPENDM_OFFSET ( 4)
  #define GPIOC_AF4_USB1_OPMODE0_OFFSET ( 5)
  #define GPIOC_AF4_USB1_OPMODE1_OFFSET ( 6)
  #define GPIOC_AF4_USB1_LINESTATE0_OFFSET ( 7)
  #define GPIOC_AF4_USB1_LINESTATE1_OFFSET ( 8)
  #define GPIOC_AF4_USB1_TXVALID_OFFSET  ( 9)
  #define GPIOC_AF4_USB1_TXREADY_OFFSET  (10)
  #define GPIOC_AF4_USB1_RXACTIVE_OFFSET (11)
  #define GPIOC_AF4_USB1_RXVALID_OFFSET  (12)
  #define GPIOC_AF4_USB1_RXERROR_OFFSET  (13)
  #define GPIOC_AF4_USB1_VBUSVALID_OFFSET (14)
  #define GPIOC_AF4_USB1_CHRGVBUS_OFFSET (15)
  #define GPIOD_AF4_USB1_DISCHRGVBUS_OFFSET ( 0)
  #define GPIOD_AF4_USB1_DPPULLDOWN_OFFSET ( 1)
  #define GPIOD_AF4_USB1_DMPULLDOWN_OFFSET ( 2)
  #define GPIOD_AF4_USB1_IDPULLUP_OFFSET ( 3)
  #define GPIOD_AF4_USB1_HOSTDISCONNECT_OFFSET ( 4)

  void Connect_USB0_AF4(void);
  void Connect_USB1_AF4(void);

  // PWM
  #define GPIOA_AF2_PWM_A_0_OFFSET       ( 4)
  #define GPIOC_AF1_PWM_A_0_OFFSET       ( 0)
  #define GPIOA_AF2_PWM_A_1_OFFSET       ( 6)
  #define GPIOC_AF1_PWM_A_1_OFFSET       ( 2)
  #define GPIOA_AF2_PWM_A_2_OFFSET       ( 8)
  #define GPIOC_AF1_PWM_A_2_OFFSET       ( 4)
  #define GPIOA_AF2_PWM_A_3_OFFSET       (10)
  #define GPIOC_AF1_PWM_A_3_OFFSET       ( 6)
  #define GPIOA_AF2_PWM_A_4_OFFSET       (12)
  #define GPIOC_AF1_PWM_A_4_OFFSET       ( 8)
  #define GPIOA_AF2_PWM_A_5_OFFSET       (14)
  #define GPIOC_AF1_PWM_A_5_OFFSET       (10)
  #define GPIOG_AF1_PWM_A_6_OFFSET       ( 0)
  #define GPIOG_AF1_PWM_A_7_OFFSET       ( 2)
  #define GPIOG_AF1_PWM_A_8_OFFSET       ( 4)
  #define GPIOG_AF1_PWM_A_9_OFFSET       ( 6)
  #define GPIOG_AF1_PWM_A_10_OFFSET      ( 8)
  #define GPIOG_AF1_PWM_A_11_OFFSET      (10)
  #define GPIOG_AF1_PWM_A_12_OFFSET      (12)
  #define GPIOG_AF1_PWM_A_13_OFFSET      (14)
  #define GPIOD_AF1_PWM_A_14_OFFSET      ( 0)
  #define GPIOE_AF3_PWM_A_14_OFFSET      ( 6)
  #define GPIOD_AF1_PWM_A_15_OFFSET      ( 2)
  #define GPIOE_AF3_PWM_A_15_OFFSET      ( 4)
  #define GPIOA_AF2_PWM_B_0_OFFSET       ( 5)
  #define GPIOC_AF1_PWM_B_0_OFFSET       ( 1)
  #define GPIOA_AF2_PWM_B_1_OFFSET       ( 7)
  #define GPIOC_AF1_PWM_B_1_OFFSET       ( 3)
  #define GPIOA_AF2_PWM_B_2_OFFSET       ( 9)
  #define GPIOC_AF1_PWM_B_2_OFFSET       ( 5)
  #define GPIOA_AF2_PWM_B_3_OFFSET       (11)
  #define GPIOC_AF1_PWM_B_3_OFFSET       ( 7)
  #define GPIOA_AF2_PWM_B_4_OFFSET       (13)
  #define GPIOC_AF1_PWM_B_4_OFFSET       ( 9)
  #define GPIOA_AF2_PWM_B_5_OFFSET       (15)
  #define GPIOC_AF1_PWM_B_5_OFFSET       (11)
  #define GPIOG_AF1_PWM_B_6_OFFSET       ( 1)
  #define GPIOG_AF1_PWM_B_7_OFFSET       ( 3)
  #define GPIOG_AF1_PWM_B_8_OFFSET       ( 5)
  #define GPIOG_AF1_PWM_B_9_OFFSET       ( 7)
  #define GPIOG_AF1_PWM_B_10_OFFSET      ( 9)
  #define GPIOG_AF1_PWM_B_11_OFFSET      (11)
  #define GPIOG_AF1_PWM_B_12_OFFSET      (13)
  #define GPIOG_AF1_PWM_B_13_OFFSET      (15)
  #define GPIOD_AF1_PWM_B_14_OFFSET      ( 1)
  #define GPIOE_AF3_PWM_B_14_OFFSET      ( 7)
  #define GPIOD_AF1_PWM_B_15_OFFSET      ( 3)
  #define GPIOE_AF3_PWM_B_15_OFFSET      ( 5)
  #define GPIOC_AF1_PWM_TZ_0_OFFSET      (12)
  #define GPIOC_AF1_PWM_TZ_1_OFFSET      (13)
  #define GPIOC_AF1_PWM_TZ_2_OFFSET      (14)
  #define GPIOC_AF1_PWM_TZ_3_OFFSET      (15)
  #define GPIOD_AF1_PWM_TZ_4_OFFSET      ( 5)
  #define GPIOE_AF3_PWM_TZ_5_OFFSET      ( 8)
  #define GPIOD_AF1_PWM_SYNC_OFFSET      ( 4)

  void Connect_PWM0_GPIOA_AF2(void);
  void Connect_PWM0_GPIOC_AF1(void);
  void Connect_PWM1_GPIOA_AF2(void);
  void Connect_PWM1_GPIOC_AF1(void);
  void Connect_PWM2_GPIOA_AF2(void);
  void Connect_PWM2_GPIOC_AF1(void);
  void Connect_PWM3_GPIOA_AF2(void);
  void Connect_PWM3_GPIOC_AF1(void);
  void Connect_PWM4_GPIOA_AF2(void);
  void Connect_PWM4_GPIOC_AF1(void);
  void Connect_PWM5_GPIOA_AF2(void);
  void Connect_PWM5_GPIOC_AF1(void);
  void Connect_PWM6_GPIOG_AF1(void);
  void Connect_PWM7_GPIOG_AF1(void);
  void Connect_PWM8_GPIOG_AF1(void);
  void Connect_PWM9_GPIOG_AF1(void);
  void Connect_PWM10_GPIOG_AF1(void);
  void Connect_PWM11_GPIOG_AF1(void);
  void Connect_PWM12_GPIOG_AF1(void);
  void Connect_PWM13_GPIOG_AF1(void);
  void Connect_PWM14_GPIOD_AF1(void);
  void Connect_PWM14_GPIOE_AF3(void);
  void Connect_PWM15_GPIOD_AF1(void);
  void Connect_PWM15_GPIOE_AF3(void);
  void Connect_PWM_TZ0_GPIOC_AF1(void);
  void Connect_PWM_TZ1_GPIOC_AF1(void);
  void Connect_PWM_TZ2_GPIOC_AF1(void);
  void Connect_PWM_TZ3_GPIOC_AF1(void);
  void Connect_PWM_TZ4_GPIOD_AF1(void);
  void Connect_PWM_TZ5_GPIOE_AF3(void);
  void Connect_PWM_SYNC_GPIOD_AF1(void);

  // TMR
  #define GPIOA_AF3_TMR_IO_0_OFFSET      (15)
  #define GPIOB_AF1_TMR_IO_0_OFFSET      (12)
  #define GPIOB_AF1_TMR_IO_1_OFFSET      (13)
  #define GPIOC_AF3_TMR_IO_1_OFFSET      ( 2)
  #define GPIOC_AF3_TMR_IO_2_OFFSET      ( 3)
  #define GPIOF_AF1_TMR_IO_2_OFFSET      ( 8)
  #define GPIOC_AF3_TMR_IO_3_OFFSET      ( 4)
  #define GPIOF_AF1_TMR_IO_3_OFFSET      ( 9)
  #define GPIOC_AF3_TMR_IO_4_OFFSET      ( 5)
  #define GPIOF_AF1_TMR_IO_4_OFFSET      (10)
  #define GPIOD_AF3_TMR_IO_5_OFFSET      ( 0)
  #define GPIOF_AF1_TMR_IO_5_OFFSET      (11)
  #define GPIOD_AF3_TMR_IO_6_OFFSET      ( 1)
  #define GPIOD_AF2_TMR_IO_6_OFFSET      ( 6)
  #define GPIOF_AF1_TMR_IO_6_OFFSET      (12)
  #define GPIOD_AF3_TMR_IO_7_OFFSET      ( 2)
  #define GPIOF_AF1_TMR_IO_7_OFFSET      (13)
  #define GPIOD_AF3_TMR_IO_8_OFFSET      ( 3)
  #define GPIOF_AF1_TMR_IO_8_OFFSET      (14)
  #define GPIOD_AF3_TMR_IO_9_OFFSET      ( 4)
  #define GPIOF_AF1_TMR_IO_9_OFFSET      (15)
  #define GPIOC_AF2_TMR_IO_10_OFFSET     ( 6)
  #define GPIOD_AF3_TMR_IO_10_OFFSET     ( 5)
  #define GPIOC_AF3_TMR_IO_11_OFFSET     ( 0)
  #define GPIOC_AF2_TMR_IO_11_OFFSET     ( 7)
  #define GPIOC_AF3_TMR_IO_12_OFFSET     ( 1)
  #define GPIOC_AF2_TMR_IO_12_OFFSET     ( 8)
  #define GPIOD_AF2_TMR_IO_13_OFFSET     ( 7)
  #define GPIOE_AF3_TMR_IO_13_OFFSET     ( 9)
  #define GPIOA_AF2_TMR_IO_14_OFFSET     ( 0)
  #define GPIOE_AF3_TMR_IO_14_OFFSET     (10)
  #define GPIOA_AF2_TMR_IO_15_OFFSET     ( 1)
  #define GPIOE_AF3_TMR_IO_15_OFFSET     (11)

  void Connect_TMR0_GPIOA_AF3(void);
  void Connect_TMR0_GPIOB_AF1(void);
  void Connect_TMR1_GPIOB_AF1(void);
  void Connect_TMR1_GPIOC_AF3(void);
  void Connect_TMR2_GPIOC_AF3(void);
  void Connect_TMR2_GPIOF_AF1(void);
  void Connect_TMR3_GPIOC_AF3(void);
  void Connect_TMR3_GPIOF_AF1(void);
  void Connect_TMR4_GPIOC_AF3(void);
  void Connect_TMR4_GPIOF_AF1(void);
  void Connect_TMR5_GPIOD_AF3(void);
  void Connect_TMR5_GPIOF_AF1(void);
  void Connect_TMR6_GPIOD_AF3(void);
  void Connect_TMR6_GPIOD_AF2(void);
  void Connect_TMR6_GPIOF_AF1(void);
  void Connect_TMR7_GPIOD_AF3(void);
  void Connect_TMR7_GPIOF_AF1(void);
  void Connect_TMR8_GPIOD_AF3(void);
  void Connect_TMR8_GPIOF_AF1(void);
  void Connect_TMR9_GPIOD_AF3(void);
  void Connect_TMR9_GPIOF_AF1(void);
  void Connect_TMR10_GPIOC_AF2(void);
  void Connect_TMR10_GPIOD_AF3(void);
  void Connect_TMR11_GPIOC_AF3(void);
  void Connect_TMR11_GPIOC_AF2(void);
  void Connect_TMR12_GPIOC_AF3(void);
  void Connect_TMR12_GPIOC_AF2(void);
  void Connect_TMR13_GPIOD_AF2(void);
  void Connect_TMR13_GPIOE_AF3(void);
  void Connect_TMR14_GPIOA_AF2(void);
  void Connect_TMR14_GPIOE_AF3(void);
  void Connect_TMR15_GPIOA_AF2(void);
  void Connect_TMR15_GPIOE_AF3(void);

  // ACMP
  #define GPIOB_AF1_ACMP_O_0_OFFSET      ( 8)
  #define GPIOC_AF3_ACMP_O_0_OFFSET      ( 6)
  #define GPIOB_AF1_ACMP_O_1_OFFSET      ( 9)
  #define GPIOC_AF3_ACMP_O_1_OFFSET      ( 7)
  #define GPIOB_AF1_ACMP_O_2_OFFSET      (10)
  #define GPIOD_AF2_ACMP_O_2_OFFSET      ( 4)
  #define GPIOB_AF1_ACMP_O_3_OFFSET      (11)
  #define GPIOD_AF2_ACMP_O_3_OFFSET      ( 5)

  void Connect_ACMP0_GPIOB_AF1(void);
  void Connect_ACMP0_GPIOC_AF3(void);
  void Connect_ACMP1_GPIOB_AF1(void);
  void Connect_ACMP1_GPIOC_AF3(void);
  void Connect_ACMP2_GPIOB_AF1(void);
  void Connect_ACMP2_GPIOD_AF2(void);
  void Connect_ACMP3_GPIOB_AF1(void);
  void Connect_ACMP3_GPIOD_AF2(void);

  // QSPI
  #define GPIOD_AF3_QSPI_IO0_0_OFFSET    ( 8)
  #define GPIOF_AF1_QSPI_IO0_0_OFFSET    ( 2)
  #define GPIOC_AF2_QSPI_IO0_1_OFFSET    ( 2)
  #define GPIOD_AF3_QSPI_IO1_0_OFFSET    ( 9)
  #define GPIOF_AF1_QSPI_IO1_0_OFFSET    ( 3)
  #define GPIOC_AF2_QSPI_IO1_1_OFFSET    ( 3)
  #define GPIOD_AF3_QSPI_IO2_0_OFFSET    (10)
  #define GPIOF_AF1_QSPI_IO2_0_OFFSET    ( 4)
  #define GPIOC_AF2_QSPI_IO2_1_OFFSET    ( 4)
  #define GPIOD_AF3_QSPI_IO3_0_OFFSET    (11)
  #define GPIOF_AF1_QSPI_IO3_0_OFFSET    ( 5)
  #define GPIOC_AF2_QSPI_IO3_1_OFFSET    ( 5)
  #define GPIOD_AF3_QSPI_CLK_0_OFFSET    ( 6)
  #define GPIOF_AF1_QSPI_CLK_0_OFFSET    ( 0)
  #define GPIOC_AF2_QSPI_CLK_1_OFFSET    ( 0)
  #define GPIOD_AF3_QSPI_FSS_0_OFFSET    ( 7)
  #define GPIOF_AF1_QSPI_FSS_0_OFFSET    ( 1)
  #define GPIOC_AF2_QSPI_FSS_1_OFFSET    ( 1)

  void Connect_QSPI0_GPIOD_AF3(void);
  void Connect_QSPI0_GPIOF_AF1(void);
  void Connect_QSPI1_GPIOC_AF2(void);

  // EXTMEM
  #define GPIOG_AF2_EXTMEM_DATA_0_OFFSET ( 0)
  #define GPIOG_AF2_EXTMEM_DATA_1_OFFSET ( 1)
  #define GPIOG_AF2_EXTMEM_DATA_2_OFFSET ( 2)
  #define GPIOG_AF2_EXTMEM_DATA_3_OFFSET ( 3)
  #define GPIOG_AF2_EXTMEM_DATA_4_OFFSET ( 4)
  #define GPIOG_AF2_EXTMEM_DATA_5_OFFSET ( 5)
  #define GPIOG_AF2_EXTMEM_DATA_6_OFFSET ( 6)
  #define GPIOG_AF2_EXTMEM_DATA_7_OFFSET ( 7)
  #define GPIOG_AF2_EXTMEM_DATA_8_OFFSET ( 8)
  #define GPIOG_AF2_EXTMEM_DATA_9_OFFSET ( 9)
  #define GPIOG_AF2_EXTMEM_DATA_10_OFFSET (10)
  #define GPIOG_AF2_EXTMEM_DATA_11_OFFSET (11)
  #define GPIOG_AF2_EXTMEM_DATA_12_OFFSET (12)
  #define GPIOG_AF2_EXTMEM_DATA_13_OFFSET (13)
  #define GPIOG_AF2_EXTMEM_DATA_14_OFFSET (14)
  #define GPIOG_AF2_EXTMEM_DATA_15_OFFSET (15)
  #define GPIOF_AF2_SDR_DATA16_OFFSET    ( 0)
  #define GPIOF_AF2_SDR_DATA17_OFFSET    ( 1)
  #define GPIOF_AF2_SDR_DATA18_OFFSET    ( 2)
  #define GPIOF_AF2_SDR_DATA19_OFFSET    ( 3)
  #define GPIOD_AF2_EXTMEM_ADDR_0_OFFSET ( 8)
  #define GPIOD_AF2_EXTMEM_ADDR_1_OFFSET ( 9)
  #define GPIOD_AF2_EXTMEM_ADDR_2_OFFSET (10)
  #define GPIOD_AF2_EXTMEM_ADDR_3_OFFSET (11)
  #define GPIOD_AF2_EXTMEM_ADDR_4_OFFSET (12)
  #define GPIOD_AF2_EXTMEM_ADDR_5_OFFSET (13)
  #define GPIOD_AF2_EXTMEM_ADDR_6_OFFSET (14)
  #define GPIOD_AF2_EXTMEM_ADDR_7_OFFSET (15)
  #define GPIOE_AF2_EXTMEM_ADDR_8_OFFSET ( 0)
  #define GPIOE_AF2_EXTMEM_ADDR_9_OFFSET ( 1)
  #define GPIOE_AF2_EXTMEM_ADDR_10_OFFSET ( 2)
  #define GPIOE_AF2_EXTMEM_ADDR_11_OFFSET ( 3)
  #define GPIOE_AF2_EXTMEM_ADDR_12_OFFSET ( 4)
  #define GPIOE_AF2_EMC_ADDR13_SDR_BA0_OFFSET ( 5)
  #define GPIOE_AF2_EMC_ADDR14_SDR_BA1_OFFSET ( 6)
  #define GPIOE_AF2_EMC_ADDR15_SDR_CKE_OFFSET ( 7)
  #define GPIOE_AF2_EMC_ADDR16_SDR_WEN_OFFSET ( 8)
  #define GPIOE_AF2_EMC_ADDR17_SDR_RASN_OFFSET ( 9)
  #define GPIOE_AF2_EMC_ADDR18_SDR_CASN_OFFSET (10)
  #define GPIOE_AF2_EMC_ADDR19_SDR_CSN_OFFSET (11)
  #define GPIOE_AF2_EMC_ADDR20_SDR_DQ0_OFFSET (12)
  #define GPIOE_AF2_EMC_ADDR21_SDR_DQ1_OFFSET (13)
  #define GPIOE_AF2_EMC_ADDR22_SDR_DQ2_OFFSET (14)
  #define GPIOE_AF2_EMC_ADDR23_SDR_DQ3_OFFSET (15)
  #define GPIOF_AF2_EMC_CEN0_SDR_DATA20_OFFSET ( 4)
  #define GPIOF_AF2_EMC_CEN1_SDR_DATA21_OFFSET ( 5)
  #define GPIOF_AF2_EMC_CEN2_SDR_DATA22_OFFSET ( 6)
  #define GPIOF_AF2_EMC_CEN3_SDR_DATA23_OFFSET ( 7)
  #define GPIOF_AF2_EMC_CEN4_SDR_DATA24_OFFSET ( 8)
  #define GPIOF_AF2_EMC_CEN5_SDR_DATA25_OFFSET ( 9)
  #define GPIOF_AF2_EMC_CEN6_SDR_DATA26_OFFSET (10)
  #define GPIOF_AF2_EMC_CEN7_SDR_DATA27_OFFSET (11)
  #define GPIOF_AF2_EMC_WEN_SDR_DATA28_OFFSET (12)
  #define GPIOF_AF2_EMC_LBN_SDR_DATA29_OFFSET (13)
  #define GPIOF_AF2_EMC_UBN_SDR_DATA30_OFFSET (14)
  #define GPIOF_AF2_EMC_OEN_SDR_DATA31_OFFSET (15)

  void Connect_EXTMEM_AF2(uint32_t useSDRAM);

  // ETH
  #define GPIOE_AF4_GMII_TXD_0_OFFSET    ( 0)
  #define GPIOE_AF4_GMII_TXD_1_OFFSET    ( 1)
  #define GPIOE_AF4_GMII_TXD_2_OFFSET    ( 2)
  #define GPIOE_AF4_GMII_TXD_3_OFFSET    ( 3)
  #define GPIOE_AF4_GMII_TXD_4_OFFSET    ( 4)
  #define GPIOE_AF4_GMII_TXD_5_OFFSET    ( 5)
  #define GPIOE_AF4_GMII_TXD_6_OFFSET    ( 6)
  #define GPIOE_AF4_GMII_TXD_7_OFFSET    ( 7)
  #define GPIOD_AF4_GMII_GTX_CLK_OFFSET  (15)
  #define GPIOD_AF4_GMII_TXCLK_OFFSET    (10)
  #define GPIOD_AF4_GMII_TXEN_OFFSET     (11)
  #define GPIOD_AF4_GMII_TXER_OFFSET     (12)
  #define GPIOD_AF4_GMII_CRS_OFFSET      (13)
  #define GPIOD_AF4_GMII_COL_OFFSET      (14)
  #define GPIOD_AF4_GMII_MDC_OFFSET      ( 6)
  #define GPIOD_AF4_GMII_MDIO_OFFSET     ( 5)
  #define GPIOE_AF4_GMII_RXD_0_OFFSET    ( 8)
  #define GPIOE_AF4_GMII_RXD_1_OFFSET    ( 9)
  #define GPIOE_AF4_GMII_RXD_2_OFFSET    (10)
  #define GPIOE_AF4_GMII_RXD_3_OFFSET    (11)
  #define GPIOE_AF4_GMII_RXD_4_OFFSET    (12)
  #define GPIOE_AF4_GMII_RXD_5_OFFSET    (13)
  #define GPIOE_AF4_GMII_RXD_6_OFFSET    (14)
  #define GPIOE_AF4_GMII_RXD_7_OFFSET    (15)
  #define GPIOD_AF4_GMII_RXDV_OFFSET     ( 8)
  #define GPIOD_AF4_GMII_RXER_OFFSET     ( 9)
  #define GPIOD_AF4_GMII_RXCLK_OFFSET    ( 7)

  void Connect_ETH_AF4(void);


#endif // GPIO_AF_H_DEFINED
