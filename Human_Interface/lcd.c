/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the AVR LCD driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "lcd.h"
#include <util/delay.h>
#include "gpio.h"
#include "common_macros.h"
#include <stdlib.h>

void LCD_init(void)
{
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, PIN_OUTPUT);

	_delay_ms(20);


#if(LCD_DATA_BITS_MODE == 4)
	
	GPIO_setupPinDirection(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D4_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D5_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D7_ID, PIN_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
	
#elif(LCD_DATA_BITS_MODE == 8)
	
	GPIO_setupPortDirection(LCD_DATABUS_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	
#endif
	
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D4_ID, GET_BIT(command,4));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D5_ID, GET_BIT(command,5));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D6_ID, GET_BIT(command,6));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D7_ID, GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D4_ID, GET_BIT(command,0));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D5_ID, GET_BIT(command,1));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D6_ID, GET_BIT(command,2));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D7_ID, GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	
#elif(LCD_DATA_BITS_MODE == 8)
	
	GPIO_writePort(LCD_DATABUS_PORT_ID, command);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	
#endif
}

void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)

	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D4_ID, GET_BIT(character,4));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D5_ID, GET_BIT(character,5));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D6_ID, GET_BIT(character,6));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D7_ID, GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D4_ID, GET_BIT(character,0));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D5_ID, GET_BIT(character,1));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D6_ID, GET_BIT(character,2));
	GPIO_writePin(LCD_DATABUS_PORT_ID, LCD_DATABUS_PIN_D7_ID, GET_BIT(character,3));

	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 8)

	GPIO_writePort(LCD_DATABUS_PORT_ID, character);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	
#endif

}

void LCD_displayString(const uint8 * string)
{
	uint8 i = 0;
	while(string[i] != '\0')
	{
		LCD_displayCharacter(string[i]);
		i++;
	}
}

void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 lcd_memory_address;
	switch(row)
	{
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col+0x40;
		break;
	case 2:
		lcd_memory_address = col+0x10;
		break;
	case 3:
		lcd_memory_address = col+0x50;
		break;
	}
	LCD_sendCommand(LCD_SET_CURSOR_LOCATION | lcd_memory_address);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 * string)
{
	LCD_moveCursor(row,col);
	LCD_displayString(string);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_intgerToString(uint32 num)
{
	uint8 buff[16];
	itoa(num, buff, 10);
	LCD_displayString(buff);
}
