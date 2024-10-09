 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the AVR KEYPAD driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/


/* if this define is true that means that 
 * keypad is a standard keypad */
#define STANDARD_KEYPAD FALSE


#define KEYPAD_NUM_ROWS 	4
#define KEYPAD_NUM_COLS 	4


#define KEYPAD_ROW_PORT_ID 				PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID  		PIN0_ID


#define KEYPAD_COL_PORT_ID 				PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID 		PIN4_ID


#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH


/* if this define is kept in code 
 * the while(1) in the keypad.c file will be removed 
 * as in multiplexing the code must not be stuck in a loop
 * as multiplexing is always switching on and off the 7-segment
 * to make them appear on at the same time */

/*#define SEVEN_SEGMENT_MULTIPLEXING*/


/*******************************************************************************/




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* fucntion that finds the pressed the key and 
 * returns its value according to the keypad type */
uint8 KEYPAD_getPressedKey(void);


/*******************************************************************************/
#endif /* KEYPAD_H_ */
