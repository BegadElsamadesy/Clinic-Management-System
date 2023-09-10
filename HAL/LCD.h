/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: header file for the AVR LCD driver
 *
 * Author: Begad Elsamadesy
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"

/**********************************************************************************************
 									pin & ports configurations
 **********************************************************************************************/
#define LCD_DATA_BITS_MODE	8

#define LCD_RS_PORT_ID						PORTB_ID
#define LCD_RS_PIN_ID						PIN0_ID

#define LCD_ENABLE_PORT_ID					PORTB_ID
#define LCD_ENABLE_PIN_ID					PIN1_ID

#define LCD_DB_PORT_ID						PORTA_ID

#if(LCD_DATA_BITS_MODE==4)
#define LCD_DB4_PIN_ID              	    PIN3_ID
#define LCD_DB5_PIN_ID						PIN4_ID
#define LCD_DB6_PIN_ID						PIN5_ID
#define LCD_DB7_PIN_ID                 		PIN6_ID
#endif

/**********************************************************************************************
 											commands
 **********************************************************************************************/

#define LCD_CLEAR_SCREEN					0x01
#define LCD_SHIFT_CURSOR_LEFT				0x04
#define LCD_SHIFT_CURSOR_RIGHT				0x06
#define LCD_CURSOR_OFF						0x0C
#define LCD_CURSOR_ON						0x0E
#define LCD_BIT4_LINE2						0x28
#define LCD_BIT4_LINE2_INIT1 				0x33
#define LCD_BIT4_LINE2_INIT2  				0x32
#define LCD_BIT8_LINE2						0x38
#define LCD_SET_CURSOR_LOCATION        	    0x80

/*********************************************************************************************
									function prototypes
 *********************************************************************************************/

void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(char *Str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,char *Str);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);

#endif /* LCD_H_ */
