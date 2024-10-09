 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the AVR BUZZER driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "buzzer.h"
#include "gpio.h"


void BUZZER_init(void)
{
	/* setting buzzer pin as output pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	/* disabling buzzer at first */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}

void BUZZER_on(void)
{
	/* enable buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_ON);
}

void BUZZER_off(void)
{
	/* disable buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, BUZZER_OFF);
}
