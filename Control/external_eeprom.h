 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM memory
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


#include "std_types.h"

/*******************************************************************************
 *                           Definitions    			                       *
 *******************************************************************************/


#define SUCCESS 1
#define ERROR 0


/********************************************************************************/



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/* function that writes byte to in eeprom memory */
uint8 EEPROM_writeByte(uint16 address,uint8 data);

/* function that reads byte to in eeprom memory */
uint8 EEPROM_readByte(uint16 address,uint8 *data);


/********************************************************************************/

#endif /* EXTERNAL_EEPROM_H_ */
