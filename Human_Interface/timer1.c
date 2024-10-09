/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the TIMER1 AVR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "timer1.h"
#include "avr_registers.h"
#include <avr/interrupt.h>


static volatile void(*g_callBackPtr)(void) = NULL_PTR;

void TIMER1_init(const Timer1_ConfigType * Config_Ptr)
{

	/* clearing TIMER1 registers */
	TCCR1A_REG.Byte = 0;
	TCCR1B_REG.Byte = 0;

	/* setting FOC1A/B as non PWM mode */
	TCCR1A_REG.Bits.FOC1A_bit = 1;
	TCCR1A_REG.Bits.FOC1B_bit = 1;


	if((Config_Ptr -> mode) == TIMER1_OVERFLOW)
	{
		/* setting wave generation mode as overflow mode */
		TCCR1A_REG.Bits.WGM10_bit = 0;
		TCCR1A_REG.Bits.WGM11_bit = 0;
		TCCR1B_REG.Bits.WGM12_bit = 0;
		TCCR1B_REG.Bits.WGM13_bit = 0;

		/* enable overflow module interrupt bit */
		TIMSK_REG.Bits.TOIE1_bit = 1;
		TIMSK_REG.Bits.OCIE1A_bit = 0;

	}
	else if((Config_Ptr -> mode) == TIMER1_COMPARE)
	{
		/* setting wave generation mode as overflow mode */
		TCCR1B_REG.Bits.WGM12_bit = 1;

		/* setting the compare match value */
		OCR1A_REG.Byte = Config_Ptr -> compareValue;

		/* enable compare match module interrupt bit */
		TIMSK_REG.Bits.OCIE1A_bit = 1;
		TIMSK_REG.Bits.TOIE1_bit = 0;


	}

	/* configuring TIMER1 prescaler */
	TCCR1B_REG.Byte = (TCCR1B_REG.Byte & 0xF8) | (Config_Ptr -> prescaler);

	/* setting timer counter initial value */
	TCNT1_REG.Byte = Config_Ptr -> initialValue;

}

void TIMER1_deInit(void)
{
	/* clearing all TIMER1 registers and bits */
	TCCR1A_REG.Byte = 0;
	TCCR1B_REG.Byte = 0;
	TIMSK_REG.Bits.TOIE1_bit = 0;
	TIMSK_REG.Bits.OCIE1A_bit = 0;
	TCNT1_REG.Byte = 0;
	OCR1A_REG.Byte = 0;

	/* resetting pointer to point to NULL */
	g_callBackPtr = NULL_PTR;
}

void TIMER1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;	/* saving address of call back function */
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();		/* calling call back function */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();		/* calling call back function */
	}
}

