/******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the TIMER0 AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"



/*******************************************************************************
 *                               	Definitions                                *
 *******************************************************************************/


#define TIMER0_OUTPUT_COMPARE_PORT_ID		PORTB_ID
#define TIMER0_OUTPUT_COMPARE_PIN_ID		PIN3_ID


/********************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


typedef enum
{
	OVERFLOW, PWM_PHASE_CORRECT, CTC, FAST_PWM
}TIMER0_modeOfOperation;

typedef enum
{
	DISCONNECTED, TOGGLE, CLEAR, SET, NON_INVERTING = 2, INVERTING
}TIMER0_compreOutputMode;

typedef enum
{
	NO_CLOCK, PRESCALER_1, PRESCALER_8, PRESCALER_64, PRESCALER_256, PRESCALER_1024
}TIMER0_prescaler;

typedef enum
{
	NONE, TOIE0_bit, OCIE0_bit
}TIMER0_interrupt;


/* structure to hold configuration of timer */
typedef struct
{
	TIMER0_modeOfOperation mode;
	TIMER0_compreOutputMode	compareOutputMode;
	TIMER0_prescaler prescaler;
	TIMER0_interrupt interruptMask;

	uint8 timerCounterRegister;
	uint8 outputCompareRegister;

}TIMER0_configType;


/********************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* function that initializes TIMER0 with specific configuration */
void TIMER0_init(TIMER0_configType *config);

/* function the de-initializes TIMER0 and resets all its registers */
void TIMER0_deInit(void);

/* function used to set call back function */
void TIME0_setCallBack(void(*a_ptr)(void));

/********************************************************************************/

#endif /* TIMER0_H_ */
