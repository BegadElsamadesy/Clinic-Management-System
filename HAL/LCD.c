 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the AVR LCD driver
 *
 * Author: Begad Elsamadesy
 *
 *******************************************************************************/
#include "gpio.h"
#include <util/delay.h>
#include "std_types.h"
#include "LCD.h"

void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, PIN_OUTPUT);

#if((LCD_DATA_BITS_MODE==8))
	GPIO_setupPortDirection(LCD_DB_PORT_ID, PORT_OUTPUT);
	_delay_ms(20);
	LCD_sendCommand(LCD_BIT8_LINE2);
#elif ((LCD_DATA_BITS_MODE==4))
	GPIO_setupPinDirection(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);
	LCD_sendCommand(LCD_BIT4_LINE2_INIT1);
	LCD_sendCommand(LCD_BIT4_LINE2_INIT2);
	LCD_sendCommand(LCD_BIT4_LINE2);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if ((LCD_DATA_BITS_MODE==4))
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,4));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,5));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,6));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));
	_delay_ms(1);
#elif((LCD_DATA_BITS_MODE==8))
	GPIO_writePort(LCD_DB_PORT_ID,command);
	_delay_ms(1);
#endif
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(PORTC_ID, character);
	_delay_ms(1);
#if ((LCD_DATA_BITS_MODE==4))
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(character,4));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(character,5));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(character,6));
	GPIO_writePin(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(character,7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));
	_delay_ms(1);
#elif((LCD_DATA_BITS_MODE==8))
	GPIO_writePort(LCD_DB_PORT_ID, character);
	_delay_ms(1);
#endif
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayString(char *Str)
{
	uint8 i=0;
	while(Str[i]!='\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_meomry_address;
	switch (row)
	{
	case 0:
		lcd_meomry_address=col;
		break;
	case 1:
		lcd_meomry_address=col+0x40;
		break;
	case 2:
		lcd_meomry_address=col+0x10;
		break;
	case 3:
		lcd_meomry_address=col+0x50;
		break;
	}
	LCD_sendCommand(lcd_meomry_address|LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,char *Str)
{
	LCD_moveCursor(row, col);
	LCD_displayString(Str);
}

void LCD_intgerToString(int data)
{
char buff[16];				/* String to hold the ascii result */
itoa(data,buff,10);			/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
LCD_sendCommand(LCD_CLEAR_SCREEN);
}
