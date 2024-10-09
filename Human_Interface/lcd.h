 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the AVR LCD driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"



/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/


/* defining the data bits mode (4 or 8) */
#define LCD_DATA_BITS_MODE 8

/* making sure data bits mode is either 4 or 8 */
#if (LCD_DATA_BITS_MODE != 4 && LCD_DATA_BITS_MODE != 8)

#error "LCD data bits mode must be 4 or 8 "

#endif

/* defining lCD RS PIN port id and pin id */
#define LCD_RS_PORT_ID PORTD_ID
#define LCD_RS_PIN_ID PIN6_ID

/* defining lCD ENABLE PIN port id and pin id */
#define LCD_ENABLE_PORT_ID PORTD_ID
#define LCD_ENABLE_PIN_ID PIN7_ID

/* defining lCD DATABUS port id */
#define LCD_DATABUS_PORT_ID PORTC_ID

#if(LCD_DATA_BITS_MODE==4)

#define LCD_DATABUS_PIN_D4_ID PIN3_ID
#define LCD_DATABUS_PIN_D5_ID PIN4_ID
#define LCD_DATABUS_PIN_D6_ID PIN5_ID
#define LCD_DATABUS_PIN_D7_ID PIN6_ID

#endif


/* defining lCD most used commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/*******************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* function the initializes LCD */
void LCD_init(void);

/* function used to send commands to LCD */
void LCD_sendCommand(uint8 command);

/* function used to display a given character on LCD */
void LCD_displayCharacter(uint8 character);

/* function used to display a given string on LCD */
void LCD_displayString(const uint8 *string);

/* function used to move the cursor to a certain
 *  position regarding rows and cols */
void LCD_moveCursor(uint8 row, uint8 col);

/* function used to move the cursor to a certain 
 * position regarding rows and cols and display
 * a given string in this specific position */
void LCD_displayStringRowColumn(uint8 row, uint8 col,const uint8 *string);

/* function used to clear the screen and automatically 
 * moves the cursor to the first position in LCD */
void LCD_clearScreen(void);

/* function used to convert an integer to a string then display
 * it on the LCD */
void LCD_intgerToString(uint32 num);


/********************************************************************************/



#endif /* LCD_H_ */
