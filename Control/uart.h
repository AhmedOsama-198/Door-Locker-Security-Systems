 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* symbol to symbolize the end of string sent by transmitter */
#define UART_SYMBOL_OF_STRING  '#'


/********************************************************************************/



/*******************************************************************************
 *                              Type Declerations                              *
 *******************************************************************************/


/* enum to configure PARITY */
typedef enum{
	DISABLE_PARITY,EVEN_PARITY=2,ODD_PARITY
}UART_PARITY_SELECT;

/* enum to configure how many stop bits */
typedef enum{
	_1BIT,_2BIT
}UART_STOP_BIT_SELECT;

/* enum to configure how many char received/transmitted */
typedef enum{
	_5BIT,_6BIT,_7BIT,_8BIT,_9BIT=7
}UART_CHARACTER_SIZE_SELECT;

/* structre to hold configurations ans pass it to init function */
typedef struct{
	UART_PARITY_SELECT parity;
	UART_STOP_BIT_SELECT stopBit;
	UART_CHARACTER_SIZE_SELECT charSize;
	uint32 baudRate;
}UART_CONFIG_TYPE;


/********************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* function that initializes the UART */
void UART_init(UART_CONFIG_TYPE* config);

/* function that sends a byte using UART */
void UART_sendByte(uint8 byte);

/* function that sends a string using UART */
void UART_sendString(const uint8 *string);

/* function that recieve string using UART */
void UART_recieveString(uint8 *string);

/* function that recieve byte using UART (POLLING TECHNIQUE)*/
uint8 UART_recieveByte(void);

/* function that recieve a sring using UART (POLLING TECHNIQUE) */
void UART_recieveString(uint8 *string);


/********************************************************************************/


#endif /* UART_H_ */
