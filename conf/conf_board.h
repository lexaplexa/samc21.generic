/*************************************************************************
 * conf_board.h
 *
 * Created: 28.4.2019 10:21:04
 * Revised: 
 * Author: LeXa
 * BOARD: 
 *
 * ABOUT:
 * Configuration of board
 *************************************************************************/


#ifndef CONF_BOARD_H_
#define CONF_BOARD_H_

/************************************************************************/
/* BOARD                                                                */
/************************************************************************/
#define BOARD_NAME                 /* Board name and version */


/************************************************************************/
/* SYSTEM CLOCK OPTIONS                                                 */
/************************************************************************/
#define F_CPU                       CONF_SOURCE_FREQ*CONF_DPLL_MULTIPLICATION
#define CONF_SOURCE_FREQ            4000000
#define CONF_DPLL_MULTIPLICATION    12
#define CONF_DPLL_CLKREF            1       /* DPLL reference clock (0 - XOSC32K, 1 - XOSC, 2 - GCLK) */


/************************************************************************/
/* MULTIPLEXER OPTIONS                                                  */
/************************************************************************/


#endif /* CONF_BOARD_H_ */