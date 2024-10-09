 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the AVR BUZZER driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/


/* Define orientation of buzzer */
#define BUZZER_PORT_ID		PORTB_ID
#define BUZZER_PIN_ID		PIN0_ID

#define BUZZER_ON			LOGIC_HIGH
#define BUZZER_OFF 			LOGIC_LOW


/*******************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* function that initializes buzzer */
void BUZZER_init(void);

/* activate buzzer */
void BUZZER_on(void);

/* disable buzzer */
void BUZZER_off(void);


/********************************************************************************/


#endif /* BUZZER_H_ */
