/******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the TIMER0 AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "timer0.h"

#include "avr_registers.h"
#include "common_macros.h"
#include "gpio.h"
#include <avr/interrupt.h>


static volatile void(*g_callBackPtr)(void) = NULL_PTR;


void TIMER0_init(TIMER0_configType *config)
{

	/* clearing TIMER0 registers */
	TCCR0_REG.Byte = 0;
	TIMSK_REG.Byte &= 0b11111100;


	/* configuring FOC0 bit */
	if(config -> mode == PWM_PHASE_CORRECT || config -> mode == FAST_PWM)
	{
		TCCR0_REG.Bits.FOC0_bit = 0;

		/* setting duty cycle */
		OCR0_REG.Byte = ((config -> outputCompareRegister) / 100) * 255;
	}
	else
	{
		TCCR0_REG.Bits.FOC0_bit = 1;
	}

	if(config -> compareOutputMode != DISCONNECTED)
	{
		/* setting direction of OC0 pin */
		GPIO_setupPinDirection(TIMER0_OUTPUT_COMPARE_PORT_ID,TIMER0_OUTPUT_COMPARE_PIN_ID,PIN_OUTPUT);
	}

	/* configuring wave generation mode */
	TCCR0_REG.Bits.WGM00_bit = GET_BIT((config -> mode),0);
	TCCR0_REG.Bits.WGM01_bit = GET_BIT((config -> mode),1);

	/* configuring compare output mode */
	TCCR0_REG.Byte = (TCCR0_REG.Byte & 0b11001111) | ((config -> compareOutputMode) << 4);

	/* configuring TIMER0 prescaler */
	TCCR0_REG.Byte = (TCCR0_REG.Byte & 0b11111000) | (config -> prescaler);

	/* enable interrupt bit if needed */
	switch(config -> interruptMask)
	{
	case TOIE0_bit:
		TIMSK_REG.Bits.TOIE0_bit = 1;
		break;
	case OCIE0_bit:
		TIMSK_REG.Bits.OCIE0_bit = 1;
		OCR0_REG.Byte = config -> outputCompareRegister;
		break;
	}

	/* setting timer counter initial value */
	TCNT0_REG.Byte = config-> timerCounterRegister;
}

void TIME0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;	/* saving address of call back function */
}

void TIMER0_deInit(void)
{
	/* clearing all TIMER0 registers and bits */
	TCCR0_REG.Byte = 0;
	TIMSK_REG.Byte &= 0b11111100;
	TCNT0_REG.Byte = 0;
	OCR0_REG.Byte = 0;

	/* resetting pointer to point to NULL */
	g_callBackPtr = NULL_PTR;
}


ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();		/* calling call back function */
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();		/* calling call back function */
	}
}
