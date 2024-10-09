/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"



/*******************************************************************************
 *                     			 Definitions                                   *
 *******************************************************************************/


#define TWI_MY_ADDRESS	  0b00000010 /* My address */

#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/********************************************************************************/



/*******************************************************************************
 *                     		Type Declerations                                  *
 *******************************************************************************/


typedef enum{
	PRESCALER_0, PRESCALER_4, PRESCALER_16, PRESCALER_64
}TWI_prescaler;

/* structure to hold TWI configurations */
typedef struct{
	TWI_prescaler prescaler;
	uint16 address;
	uint16 bit_rate;
}TWI_ConfigType;


/********************************************************************************/



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/* function that initializes I2C with specific configurations */
void TWI_init(TWI_ConfigType *config);

/* function that sends start bit */
void TWI_start();

/* function that sends stop bit */
void TWI_stop();

/* functio that sends byte using I2C */
void TWI_writeByte(uint8 data);

/* function that reads byte and reply with ACK */
uint8 TWI_readByteWithACK();

/* function that reads the last byte with NOT-ACK */
uint8 TWI_readByteWithNACK();

/* function that return status */
uint8 TWI_getStatus();


/********************************************************************************/



#endif /* TWI_H_ */
