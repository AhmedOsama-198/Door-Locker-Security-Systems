 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "uart.h"
#include "avr_registers.h"


void UART_init(UART_CONFIG_TYPE* config)
{

	uint16 ubrr_value = 0;			/* variable to calculate UBRR value from baud rate */

	UCSRA_REG.Byte = 0; 			/* clearing register at first */

	UCSRA_REG.Bits.U2X_bit = 1;		/* enabling double USART transmission speed */

	UCSRB_REG.Byte = 0;				/* clearing register at first */

	UCSRB_REG.Bits.RXEN_bit = 1;	/* Receiver Enable */
	UCSRB_REG.Bits.TXEN_bit = 1;	/* Transmitter Enable */


	/* setting UCSZ2 Bit if char size = 9 */
	if(config -> charSize == _9BIT)
	{
		UCSRB_REG.Bits.UCSZ2_bit = 1;
		config -> charSize = 3;
	}
	else
	{
		UCSRB_REG.Bits.UCSZ2_bit = 0;
	}


	/* setting URSEL bit to write in UCSRC register */
	/* clearing register at first */
	UCSRC_REG.Byte = 0;

	/* configuring stop bit (1 bit or 2 bits) */
	UCSRC_REG.Bits.USBS_bit = config -> stopBit;

	/* configuring parity */
	UCSRC_REG.Byte = (UCSRC_REG.Byte & 0b11001111) | ((config -> parity) << 4);

	/* configuring char size */
	UCSRC_REG.Byte = (UCSRC_REG.Byte & 0b11111001) | ((config -> charSize) << 1);

	/* calculating UBRR value */
	ubrr_value = (uint16)(((F_CPU / ((config -> baudRate) * 8UL))) - 1);


	/* configuring baud rate */
	UBRRH_REG.Bits.UBRRH_bits = ubrr_value >> 8;
	UBRRL_REG.Byte = ubrr_value;


}

void UART_sendByte(uint8 byte)
{
	/* waiting for empty UDR flag */
	while(UCSRA_REG.Bits.UDRE_bit == 0);

	UDR_REG.Byte = byte;	/* sending byte */
}

void UART_sendString(const uint8 *string)
{
	uint8 i = 0;	/* counter variable */

	while(string[i] != '\0')
	{
		UART_sendByte(string[i]);	/* sending byte */
		i++;	/* increamenting counter */
	}
}

uint8 UART_recieveByte(void)
{
	/* waiting for recieving complete flag */
	while(UCSRA_REG.Bits.RXC_bit == 0);

	/* returning recieved byte */
	return UDR_REG.Byte;
}

void UART_recieveString(uint8 *string)
{
	uint8 i = 0;	/* counter variable */

	string[i] = UART_recieveByte();

	while(string[i] != UART_SYMBOL_OF_STRING)
	{
		i++;

		/* recieving string character by character */
		string[i] = UART_recieveByte();
	}

	string[i] = '\0'; /* replacing end character symbol by null */
}
