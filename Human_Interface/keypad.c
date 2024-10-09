/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the AVR KEYPAD driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#include "keypad.h"
#include "gpio.h"
#include <util/delay.h>

#if(KEYPAD_NUM_COLS==4)
	#if(STANDARD_KEYPAD==FALSE)
		static uint8 KEYPAD_4X4_Not_Standard_Keypad(uint8 num)
		{
			switch(num)
			{
			case 1:
				return 7;
			case 2:
				return 8;
			case 3:
				return 9;
			case 4:
				return '/';
			case 5:
				return 4;
			case 6:
				return 5;
			case 7:
				return 6;
			case 8:
				return '*';
			case 9:
				return 1;
			case 10:
				return 2;
			case 11:
				return 3;
			case 12:
				return '-';
			case 13:
				return 0;
			case 14:
				return 0;
			case 15:
				return '=';
			case 16:
				return '+';
			}
			return '\0';
		}
	#endif
#endif


#if(KEYPAD_NUM_COLS==3)
	#if(STANDARD_KEYPAD==FALSE)
		static uint8 KEYPAD_4X3_Not_Standard_Keypad(uint8 num)
		{
			switch(num)
			{
			case 1:
				return 7;
			case 2:
				return 8;
			case 3:
				return 9;
			case 4:
				return 4;
			case 5:
				return 5;
			case 6:
				return 6;
			case 7:
				return 1;
			case 8:
				return 2;
			case 9:
				return 3;
			case 10:
				return 0;
			case 11:
				return '.';
			case 12:
				return '=';
					}
				}		
	#elif (STANDARD_KEYPAD==TRUE)
		static uint8 KEYPAD_4X3_Standard_Keypad(uint8 num)
		{
			switch(num)
			{
			case 10:
				return '*';
			case 11:
				return 0;
			case 12:
				return '#';
			default:
				return num;
			}
		}
	#endif
#endif

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col,row;
#ifdef SEVEN_SEGMENT_MULTIPLEXING
	static uint8 num=0;
#endif
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
	
#if(KEYPAD_NUM_COLS == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif
#ifndef SEVEN_SEGMENT_MULTIPLEXING
		while(1)
			{
		#endif
	for(row=0;row<KEYPAD_NUM_ROWS;row++)
	{
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);

		GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0;col<KEYPAD_NUM_COLS;col++)
				{
				if(GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
					{
					#if(KEYPAD_NUM_COLS == 3 && STANDARD_KEYPAD == TRUE)
#ifdef SEVEN_SEGMENT_MULTIPLEXING
							num = KEYPAD_4X3_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
#endif
							return KEYPAD_4X3_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
					#endif							
					#if(KEYPAD_NUM_COLS == 3 && STANDARD_KEYPAD == FALSE)
#ifdef SEVEN_SEGMENT_MULTIPLEXING
							num = KEYPAD_4X3_Not_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
#endif
							return KEYPAD_4X3_Not_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
					#endif
					#if(KEYPAD_NUM_COLS == 4 && STANDARD_KEYPAD == TRUE)
#ifdef SEVEN_SEGMENT_MULTIPLEXING
							num = ((row*KEYPAD_NUM_COLS)+col+1);
#endif
							return ((row*KEYPAD_NUM_COLS)+col+1);
					#endif
					#if(KEYPAD_NUM_COLS == 4 && STANDARD_KEYPAD == FALSE)
#ifdef SEVEN_SEGMENT_MULTIPLEXING
							num =  KEYPAD_4X4_Not_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
#endif
							return KEYPAD_4X4_Not_Standard_Keypad(((row*KEYPAD_NUM_COLS)+col+1));
					#endif
			}
		}
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
		_delay_ms(10);
#ifndef SEVEN_SEGMENT_MULTIPLEXING
		}
#endif
	}
#ifdef SEVEN_SEGMENT_MULTIPLEXING
	return num;
#endif
}

