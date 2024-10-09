/******************************************************************************
 *
 * Application: DOOR LOCK SYSTEM CONTROL ECU
 *
 * File Name: ECU2.c
 *
 * Description: Source file for Door LOCK SYSTEM CONTROL ECU
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "uart.h"
#include "twi.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "timer1.h"
#include "dc_motor.h"
#include "avr_registers.h"
#include <util/delay.h>


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* definitions of handshake protocol between two ECUs */
#define MC2_ASK			0x01
#define MC1_READY		0X02
#define MC1_ASK			0x03
#define MC2_READY		0X04

#define MEMORY_ADDRESS	0x0001	/* memory address of password inside EEPROM external memory */


/********************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


uint8 wrongPassCounter = 0;		/* variable to store how many times user entered wrong password */
uint8 freezeFlag = 0;			/* flag that freezes application when necessary */

/* enum to store all possible application of state */
typedef enum
{
	CREATE_PASS, MAIN_SCREEN, OPEN_DOOR, CHANGE_PASS, DOOR_UNLOCKING, ALARM
}APPLICATION_STATE;


APPLICATION_STATE state = CREATE_PASS;


/********************************************************************************/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* call back function of alarm */
void alarmCallBackFunction(void);

/* call back function of opening door */
void openDoorCallBackFunction(void);

/* function in control of entering wrong password */
void wrongPass(void);

/* function that receive password from ECU1 */
uint8 getPass (void);

/* function used to create password */
void createPass(void);


/********************************************************************************/



/*******************************************************************************
 *                                Main Funciton                                *
 *******************************************************************************/


int main()
{
	/* variable decelerations:
	 * option		--->	  to store selected option from user
	 * twiConfig	--->	  configuration of I2C
	 * uartConfig	--->	  configuration of UART
	 */
	uint8 option;

	TWI_ConfigType twiConfig = {PRESCALER_0, 0x01,0x02};

	UART_CONFIG_TYPE uartConfig = {DISABLE_PARITY, _1BIT, _8BIT, 9600};

	/* initializing UART with certain configurations*/
	UART_init(&uartConfig);

	/* initializing I2C with certain configurations*/
	TWI_init(&twiConfig);

	/* initializing DC-Motor */
	DcMotor_Init();

	/* initializing Buzzer */
	BUZZER_init();

	/* enabling Global interrupt mask bit */
	SREG_REG.Bits.I_Bit = 1;

	while(1)
	{
		/* ECU2 asks ECU1 and waits for its
		 * response then sends current state*/
		UART_sendByte(MC2_ASK);
		while(UART_recieveByte() != MC1_READY);
		UART_sendByte(state);

		switch(state)
		{
		case CREATE_PASS:
			createPass();
			break;

		case MAIN_SCREEN:
		{
			/* ECU2 waits for ECU1 to ask it then respond
			 * then receive the pressed key */
			while(UART_recieveByte() != MC1_ASK);
			UART_sendByte(MC2_READY);
			option = UART_recieveByte();

			if(option == '+')
			{
				/* change state of application to open door */
				state = OPEN_DOOR;
			}
			else if(option == '-')
			{
				/* change state of application to change password */
				state = CHANGE_PASS;
			}
		}
		break;

		case OPEN_DOOR:
		{
			/* receiving password from ECU1 */
			if(getPass() == TRUE)
			{
				/* changing state of application to door unlocking */
				state = DOOR_UNLOCKING;

				wrongPassCounter = 0;	/* clearing wrong pass counter */
			}
			else
			{
				wrongPass();
			}
		}
		break;

		case CHANGE_PASS:
		{
			/* receiving password from ECU1 */
			if(getPass() == TRUE)
			{
				/* changing state of application to create password */
				state = CREATE_PASS;
				wrongPassCounter = 0;	/* clearing wrong pass counter */
			}
			else
			{
				wrongPass();
			}
		}
		break;

		case DOOR_UNLOCKING:
		{
			/* setting a freeze flag to hold application
			 * while door is opening and closing */
			freezeFlag = 1;

			Timer1_ConfigType timer1Config = {0, 10, F_CPU_1024, TIMER1_COMPARE};
			TIMER1_setCallBack(openDoorCallBackFunction);

			/* initializing time with specific configurations */
			TIMER1_init(&timer1Config);

			/* loop until door activity is complete */
			while(freezeFlag == 1);

			/* setting state of application to the main state */
			state = MAIN_SCREEN;
		}
		break;

		case ALARM:
		{
			/* setting a freeze flag to hold application
			 * while alarm is on */
			freezeFlag = 1;
			Timer1_ConfigType timer1Config = {65525, 0, F_CPU_1024, TIMER1_OVERFLOW};
			TIMER1_setCallBack(alarmCallBackFunction);

			/* initializing time with specific configurations */
			TIMER1_init(&timer1Config);

			/* loop until alarm activity is complete */
			while(freezeFlag == 1);

			/* setting state of application to the main state */
			state = MAIN_SCREEN;
		}
		break;
		}/* end switch*/
	}/* end while(1) */
}


/********************************************************************************/



/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/


void openDoorCallBackFunction(void)
{
	static uint8 tick = 0;
	tick++;		/* Increment interrupt counter */

	if(tick == 1)
	{
		/* configuring timer with compare mood to
		 * generate an interrupt request every 3 seconds */
		Timer1_ConfigType timer1Config = {0, 23438, F_CPU_1024, TIMER1_COMPARE};
		TIMER1_init(&timer1Config);

		DcMotor_Rotate(DC_MOTOR_CW,100);	/* motor rotating clockwise with maximum speed */
	}
	else if(tick == 6)
	{
		DcMotor_Rotate(DC_MOTOR_STOP,0);	/* motor stop */
	}
	else if(tick == 7)
	{
		DcMotor_Rotate(DC_MOTOR_CCW,100);	/* motor rotating counter clockwise with maximum speed */
	}
	else if(tick == 12)
	{
		DcMotor_Rotate(DC_MOTOR_STOP,0);	/* motor stop */

		tick = 0;				/* clear interrupt counter */

		freezeFlag = 0;			/* clear freeze flag */

		TIMER1_deInit();		/* de-initializing timer */
	}
}

/********************************************************************************/

void alarmCallBackFunction(void)
{
	static uint8 tick = 0;
	tick++;		/* Increment interrupt counter */

	if(tick == 1)
	{
		/* configuring timer with compare mood to
		 * generate an interrupt request every 8 seconds */
		Timer1_ConfigType timer1Config = {0, 0, F_CPU_1024, TIMER1_OVERFLOW};
		TIMER1_init(&timer1Config);

		BUZZER_on();	/* enabling buzzer */
	}
	if(tick == 7)
	{
		BUZZER_off();			/* disabling buzzer */

		tick = 0;				/* clear interrupt counter */

		freezeFlag = 0;			/* clear freeze flag */

		TIMER1_deInit();		/* de-initializing timer */
	}
}

/********************************************************************************/

void wrongPass(void)
{
	wrongPassCounter++;		/* Incrementing wrong password counter */

	/* if counter reaches 3 which is the maximum number
	 * of wrong password input change state into alarm state */
	if(wrongPassCounter == 3)
	{
		state = ALARM;
		wrongPassCounter = 0;
	}
}

/********************************************************************************/

uint8 getPass (void)
{
	/*variable decelerations
	 * pass		---> to store password received from used
	 * real		---> to store real password fetched from EEPROM memory
	 * passwordMatch	---> flag of password match
	 */
	uint8 pass[5],real[5],passwordMatch = TRUE;
	for(uint8 i = 0; i < 5; i++)
	{
		/* ECU2 waits for ECU1 to ask it then respond
		 * then receive the two passwords */
		while(UART_recieveByte() != MC1_ASK);
		UART_sendByte(MC2_READY);
		pass[i] = UART_recieveByte();

		/* get saved password from memory */
		EEPROM_readByte(MEMORY_ADDRESS+i,&real[i]);
		_delay_ms(15);

		if(real[i] != pass[i])	/* comparing two passwords */
		{
			passwordMatch = FALSE;
		}
	}
	return passwordMatch;
}

/********************************************************************************/

void createPass(void)
{
	/* variable declerations
	 * pass 		---> 	  to store password sent from user
	 * repass		--->	  to store re-entred password sent from user
	 * unMatch		--->	  flag that is set when password don't match
	 */
	uint8 pass[5],repass[5],unMatch = FALSE;;
	for(uint8 i = 0; i < 5; i++){
		/* ECU2 waits for ECU1 to ask it then respond
		 * then receive the two passwords */
		while(UART_recieveByte() != MC1_ASK);
		UART_sendByte(MC2_READY);
		pass[i] = UART_recieveByte();

		while(UART_recieveByte() != MC1_ASK);
		UART_sendByte(MC2_READY);
		repass[i] = UART_recieveByte();

		/* check if two password don't match */
		if(repass[i] != pass[i])
		{
			unMatch = TRUE;	 /* setting un-match flag */
		}
	}
	/* check on state of match flag */
	if(unMatch == FALSE)
	{
		/* if match save password in
		 * external memory and set state to main */
		for(uint8 i = 0; i < 5; i++)
		{
			EEPROM_writeByte(MEMORY_ADDRESS+i,pass[i]);
			_delay_ms(15);
		}

		state = MAIN_SCREEN;
	}
	else
	{
		/* begin the create password process from the beginning */
		state = CREATE_PASS;

		unMatch = FALSE;	/* clearing flag*/
	}
}


/********************************************************************************/
