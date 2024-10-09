/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the TIMER1 AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef TIMER1_H_
#define TIMER1_H_


#include "std_types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


typedef enum{
	NO_CLOCK, F_CPU_1, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Timer1_Prescaler;

typedef enum{
	TIMER1_OVERFLOW, TIMER1_COMPARE = 4
}Timer1_Mode;


/* structure to hold configuration of timer */
typedef struct
{
	uint16 initialValue;
	uint16 compareValue;

	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;


/********************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* function that initializes TIMER1 with specific configuration */
void TIMER1_init(const Timer1_ConfigType * Config_Ptr);

/* function the de-initializes TIMER1 and resets all its registers */
void TIMER1_deInit(void);

/* function used to set call back function */
void TIMER1_setCallBack(void(*a_ptr)(void));


/********************************************************************************/


#endif /* TIMER1_H_ */
