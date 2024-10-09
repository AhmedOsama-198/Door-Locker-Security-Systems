/******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC MOTOR driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/


#define DC_MOTOR_PORT_ID			PORTB_ID

#define DC_MOTOR_IN1_PIN_ID			PIN4_ID
#define DC_MOTOR_IN2_PIN_ID			PIN5_ID
#define DC_MOTOR_ENABLE_PIN_ID		PIN3_ID


/********************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


typedef enum
{
	DC_MOTOR_STOP,DC_MOTOR_CW,DC_MOTOR_CCW
}DcMotor_State;

/********************************************************************************/



/*******************************************************************************
 *                               Function Prototypes                           *
 *******************************************************************************/


/* function that initializes the motor */
void DcMotor_Init(void);

/* function that control the motor rotation direction and speed */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


/********************************************************************************/


#endif /* DC_MOTOR_H_ */
