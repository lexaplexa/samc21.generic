/*************************************************************************
 * conf_board.h
 *
 * Created: 31.3.2016 16:10:04
 * Revised: 12.3.2019
 * Author: uidm2956
 * BOARD: TEST_BOX_C1
 *
 * ABOUT:
 * Configuration of board
 *************************************************************************/


#ifndef CONF_BOARD_H_
#define CONF_BOARD_H_

/************************************************************************/
/* BOARD                                                                */
/************************************************************************/
#define TEST_BOX_C1                 /* Board name and version */


/************************************************************************/
/* SYSTEM CLOCK OPTIONS                                                 */
/************************************************************************/
#define F_CPU                       CONF_SOURCE_FREQ*CONF_DPLL_MULTIPLICATION
#define CONF_SOURCE_FREQ            4000000
#define CONF_DPLL_MULTIPLICATION    12
#define CONF_DPLL_CLKREF            1       /* DPLL reference clock (0 - XOSC32K, 1 - XOSC, 2 - GCLK) */
#define GCLK0_OUTPUT_pin            PIN_PA27
#define GCLK0_OUTPUT_pin_mux        MUX_PA27H_GCLK_IO0
#define GCLK0_OUTPUT_msk            PORT_PA27


/************************************************************************/
/* MULTIPLEXER OPTIONS                                                  */
/************************************************************************/
/*----------------------------------------------------------------------*/
/* CAN                                                                  */
/*----------------------------------------------------------------------*/
#define CAN0_PORT                   PORTB
#define CAN0_TX_pin                 PIN_PB22
#define CAN0_TX_pin_mux             MUX_PB22G_CAN0_TX
#define CAN0_TX_msk                 PORT_PB22
#define CAN0_RX_pin                 PIN_PB23
#define CAN0_RX_pin_mux             MUX_PB23G_CAN0_RX
#define CAN0_RX_msk                 PORT_PB23

/*----------------------------------------------------------------------*/
/* TERMINAL                                                             */
/*----------------------------------------------------------------------*/
#define TERM_SERCOM                 SERCOM5
#define TERM_BAUD                   3000000
#define TERM_TX_pin                 PIN_PB16
#define TERM_TX_pin_mux             MUX_PB16C_SERCOM5_PAD0
#define TERM_TX_msk                 PORT_PB16
#define TERM_RX_pin                 PIN_PB17
#define TERM_RX_pin_mux             MUX_PB17C_SERCOM5_PAD1
#define TERM_RX_msk                 PORT_PB17
#define TERM_PAD_IN                 1
#define TERM_PAD_OUT                2

/*----------------------------------------------------------------------*/
/* LIN                                                                  */
/*----------------------------------------------------------------------*/
#define LIN_SERCOM                  SERCOM3
#define LIN_BAUD
#define LIN_TX_pin                  PIN_PA20
#define LIN_TX_msk                  PORT_PA20
#define LIN_TX_pin_mux              MUX_PA20D_SERCOM3_PAD2
#define LIN_RX_pin                  PIN_PA21
#define LIN_RX_msk                  PORT_PA21
#define LIN_RX_pin_mux              MUX_PA21D_SERCOM3_PAD3
#define LIN_PAD_IN                  3
#define LIN_PAD_OUT                 1

/*----------------------------------------------------------------------*/
/* I2C                                                                  */
/*----------------------------------------------------------------------*/
#define I2C_SERCOM                  SERCOM1
#define I2C_BAUD
#define I2C_SDA_pin                 PIN_PA16
#define I2C_SDA_msk                 PORT_PA16
#define I2C_SDA_pin_mux             MUX_PA16C_SERCOM1_PAD0
#define I2C_SCL_pin                 PIN_PA17
#define I2C_SCL_msk                 PORT_PA17
#define I2C_SCL_pin_mux             MUX_PA17C_SERCOM1_PAD1

/*----------------------------------------------------------------------*/
/* K-LINE                                                               */
/*----------------------------------------------------------------------*/
#define KLINE_SERCOM                SERCOM2
#define KLINE_BAUD
#define KLINE_TX_pin                PIN_PA12
#define KLINE_TX_msk                PORT_PA12
#define KLINE_TX_pin_mux            MUX_PA12C_SERCOM2_PAD0
#define KLINE_RX_pin                PIN_PA13
#define KLINE_RX_msk                PORT_PA13
#define KLINE_RX_pin_mux            MUX_PA13C_SERCOM2_PAD1
#define KLINE_PAD_IN                1
#define KLINE_PAD_OUT               2

/*----------------------------------------------------------------------*/
/* EXTERNAL FLASH                                                       */
/*----------------------------------------------------------------------*/
#define SPI_FLASH_SERCOM            SERCOM4
#define SPI_FLASH_BAUD              12000000
#define SPI_FLASH_MISO_pin          PIN_PB15
#define SPI_FLASH_MISO_pin_mux      MUX_PB15C_SERCOM4_PAD3
#define SPI_FLASH_MISO_msk          PORT_PB15
#define SPI_FLASH_SCK_pin           PIN_PB13
#define SPI_FLASH_SCK_pin_mux       MUX_PB13C_SERCOM4_PAD1
#define SPI_FLASH_SCK_msk           PORT_PB13
#define SPI_FLASH_CS_pin            PIN_PB14
#define SPI_FLASH_CS_pin_mux        MUX_PB14C_SERCOM4_PAD2
#define SPI_FLASH_CS_msk            PORT_PB14
#define SPI_FLASH_MOSI_pin          PIN_PB12
#define SPI_FLASH_MOSI_pin_mux      MUX_PB12C_SERCOM4_PAD0
#define SPI_FLASH_MOSI_msk          PORT_PB12
#define SPI_FLASH_PAD_IN            3
#define SPI_FLASH_PAD_OUT           0

/*----------------------------------------------------------------------*/
/* BUTTONS                                                              */
/*----------------------------------------------------------------------*/
#define BUT_ENC_LEFT_A_pin          PIN_PB31
#define BUT_ENC_LEFT_A_msk          PORT_PB31
#define BUT_ENC_LEFT_A_pin_mux      MUX_PB31A_EIC_EXTINT15
#define BUT_ENC_LEFT_A_extint       15
#define BUT_ENC_LEFT_B_pin          PIN_PB30
#define BUT_ENC_LEFT_B_msk          PORT_PB30
#define BUT_ENC_LEFT_B_pin_mux      MUX_PB30A_EIC_EXTINT14
#define BUT_ENC_LEFT_B_extint       14
#define BUT_ENC_LEFT_PUSH_pin       PIN_PB00
#define BUT_ENC_LEFT_PUSH_msk       PORT_PB00
#define BUT_ENC_LEFT_PUSH_pin_mux   MUX_PB00A_EIC_EXTINT0
#define BUT_ENC_LEFT_PUSH_extint    0
#define BUT_ENC_RIGHT_A_pin         PIN_PB02
#define BUT_ENC_RIGHT_A_msk         PORT_PB02
#define BUT_ENC_RIGHT_A_pin_mux     MUX_PB02A_EIC_EXTINT2
#define BUT_ENC_RIGHT_A_extint      2
#define BUT_ENC_RIGHT_B_pin         PIN_PB01
#define BUT_ENC_RIGHT_B_msk         PORT_PB01
#define BUT_ENC_RIGHT_B_pin_mux     MUX_PB01A_EIC_EXTINT1
#define BUT_ENC_RIGHT_B_extint      1
#define BUT_ENC_RIGHT_PUSH_pin      PIN_PB03
#define BUT_ENC_RIGHT_PUSH_msk      PORT_PB03
#define BUT_ENC_RIGHT_PUSH_pin_mux  MUX_PB03A_EIC_EXTINT3
#define BUT_ENC_RIGHT_PUSH_extint   3
#define BUT_ENC_msk                 BUT_ENC_LEFT_A_msk|BUT_ENC_LEFT_B_msk|BUT_ENC_LEFT_PUSH_msk|BUT_ENC_RIGHT_A_msk|BUT_ENC_RIGHT_B_msk|BUT_ENC_RIGHT_PUSH_msk
#define BUT_ENC_pin_mux             0

/*----------------------------------------------------------------------*/
/* DISPLAY                                                              */
/*----------------------------------------------------------------------*/
#define DISP_D0_pin                 PIN_PA04
#define DISP_D0_msk                 PORT_PA04
#define DISP_D1_pin                 PIN_PA05
#define DISP_D1_msk                 PORT_PA05
#define DISP_D2_pin                 PIN_PA06
#define DISP_D2_msk                 PORT_PA06
#define DISP_D3_pin                 PIN_PA07
#define DISP_D3_msk                 PORT_PA07
#define DISP_D4_pin                 PIN_PA08
#define DISP_D4_msk                 PORT_PA08
#define DISP_D5_pin                 PIN_PA09
#define DISP_D5_msk                 PORT_PA09
#define DISP_D6_pin                 PIN_PA10
#define DISP_D6_msk                 PORT_PA10
#define DISP_D7_pin                 PIN_PA11
#define DISP_D7_msk                 PORT_PA11
#define DISP_CS_pin                 PIN_PB06
#define DISP_CS_msk                 PORT_PB06
#define DISP_WR_pin                 PIN_PA18
#define DISP_WR_msk                 PORT_PA18
#define DISP_A0_pin                 PIN_PB08
#define DISP_A0_msk                 PORT_PB08
#define DISP_RES_pin                PIN_PB09
#define DISP_RES_msk                PORT_PB09
#define DISP_DATA_msk               DISP_D0_msk|DISP_D1_msk|DISP_D2_msk|DISP_D3_msk|DISP_D4_msk|DISP_D5_msk|DISP_D6_msk|DISP_D7_msk
#define DISP_PORT_DATA_OUTCLR       REG_PORT_OUTCLR0
#define DISP_PORT_DATA_OUTSET       REG_PORT_OUTSET0
#define DISP_PORT_CMD_OUTCLR        REG_PORT_OUTCLR1
#define DISP_PORT_CMD_OUTSET        REG_PORT_OUTSET1

/*----------------------------------------------------------------------*/
/* ILLUMINATION (DISPLAY)                                               */
/*----------------------------------------------------------------------*/
#define ILLU_TIMER_COUNTER          TC0
#define ILLU_PWM_FREQ               120
#define ILLU_PWM_pin                PIN_PA23
#define ILLU_PWM_msk                PORT_PA23
#define ILLU_PWM_pin_mux            MUX_PA23E_TC0_WO1
#define ILLU_RED_EN_pin             PIN_PA22
#define ILLU_RED_EN_msk             PORT_PA22
#define ILLU_GREEN_EN_pin           PIN_PA24
#define ILLU_GREEN_EN_msk           PORT_PA24
#define ILLU_WHITE_EN_pin           PIN_PA25
#define ILLU_WHITE_EN_msk           PORT_PA25

/*----------------------------------------------------------------------*/
/* DAC                                                                  */
/*----------------------------------------------------------------------*/
#define DAC_VOUT_pin                PIN_PA02
#define DAC_VOUT_msk                PORT_PA02
#define DAC_VOUT_pin_mux            MUX_PA02B_DAC_VOUT
#define DAC_ADC_VREFA_pin           PIN_PA03
#define DAC_ADC_VREFA_msk           PORT_PA03
#define DAC_ADC_VREFA_pin_mux       MUX_PA03B_DAC_VREFP

/*----------------------------------------------------------------------*/
/* DEBUG PINS                                                           */
/*----------------------------------------------------------------------*/
#define PROCESS_MEASURE_msk         PORT_PA02
#define process_measure_on()        REG_PORT_OUTCLR0 = PROCESS_MEASURE_msk
#define process_measure_off()       REG_PORT_OUTSET0 = PROCESS_MEASURE_msk


/************************************************************************/
/* MODULE OPTIONS                                                       */
/************************************************************************/
/*----------------------------------------------------------------------*/
/* CAN                                                                  */
/*----------------------------------------------------------------------*/
#define CAN_DATA_FIELD_SIZE         8
#define CAN_TX_FIFO_SIZE            4
#define CAN_RX_FIFO0_SIZE           20
#define CAN_RX_FIFO1_SIZE           4
#define CAN_RX_FILTER_STD_SIZE      1
#define CAN_RX_FILTER_EXT_SIZE      1
#define CAN_NBIT_TIMING_NBRP        5       /* Nominal baud rate prescaler */
#define CAN_NBIT_TIMING_NTSEG1      9       /* Nominal time segment 1 (before sample point) */
#define CAN_NBIT_TIMING_NTSEG2      4       /* Nominal time segment 2 (after sample point) */

/*----------------------------------------------------------------------*/
/* CAN SIMULATION                                                       */
/*----------------------------------------------------------------------*/
#define CAN_SIM_BUFFER_SIZE         10
#define CAN_SIM_INC_COUNTER_MS      10

/*----------------------------------------------------------------------*/
/* TERMINAL                                                             */
/*----------------------------------------------------------------------*/
#define TERM_SERCOM_IRQn            SERCOM5_IRQn
#define REG_TERM_DATA               REG_SERCOM5_SPI_DATA
#define REG_TERM_INTFLAG            REG_SERCOM5_SPI_INTFLAG

#define TERM_BUFFER_SIZE            512



#endif /* CONF_BOARD_H_ */