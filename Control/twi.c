/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "twi.h"
#include "avr_registers.h"

void TWI_init(TWI_ConfigType *config)
{
	TWBR_REG.Byte = config -> bit_rate;
	TWSR_REG.Byte = config -> prescaler;

	TWAR_REG.Byte = config -> address;	/* set address */

	TWCR_REG.Bits.TWEN_bit = 1;			/* enable TWI */
}

void TWI_start()
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = 0b00000100;
	TWCR_REG.Bits.TWSTA_bit = 1;
	TWCR_REG.Bits.TWINT_bit = 1;

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(TWCR_REG.Bits.TWINT_bit == 0);
}

void TWI_stop()
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = 0b00000100;
	TWCR_REG.Bits.TWSTO_bit = 1;
	TWCR_REG.Bits.TWINT_bit = 1;
}

void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR_REG.Byte = data;

	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = 0b00000100;
	TWCR_REG.Bits.TWINT_bit = 1;

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(TWCR_REG.Bits.TWINT_bit == 0);
}

uint8 TWI_readByteWithACK()
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = 0b00000100;
	TWCR_REG.Bits.TWEA_bit = 1;
	TWCR_REG.Bits.TWINT_bit = 1;

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(TWCR_REG.Bits.TWINT_bit == 0);

    /* Read Data */
	return TWDR_REG.Byte;
}

uint8 TWI_readByteWithNACK()
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = 0b00000100;
	TWCR_REG.Bits.TWINT_bit = 1;

    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(TWCR_REG.Bits.TWINT_bit == 0);

    /* Read Data */
	return TWDR_REG.Byte;
}

uint8 TWI_getStatus()
{
	uint8 status;

	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR_REG.Byte & 0xF8;
	return status;
}
