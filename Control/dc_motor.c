/******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC MOTOR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "dc_motor.h"
#include "gpio.h"
#include "avr_registers.h"
#include "timer0.h"


void DcMotor_Init(void)
{
	/* setting two control pins of motor as output pins */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	/* stopping the motor at first */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, DC_MOTOR_STOP);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, DC_MOTOR_STOP);
}


void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{

	switch(state)
	{
	case DC_MOTOR_STOP: 	/* stopping the motor */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);

		TIMER0_deInit();	/* de-initializing timer */
		break;
	case DC_MOTOR_CW:		/* rotating the motor clockwise */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;
	case DC_MOTOR_CCW:		/* rotating the motor counter clockwise */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	}

	/* initializing timer with specific configurations */
	TIMER0_configType timer0Config = {FAST_PWM, NON_INVERTING, PRESCALER_8, NONE, 0, speed};
	TIMER0_init(&timer0Config);

}

