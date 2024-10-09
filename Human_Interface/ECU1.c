/******************************************************************************
 *
 * Application: DOOR LOCK SYSTEM HUMAN INTERFACE ECU
 *
 * File Name: ECU1.c
 *
 * Description: Source file for Door LOCK SYSTEM HUMAN INTERFACE ECU
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "util/delay.h"
#include "avr_registers.h"
#include "timer1.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* definitions of handshake protocol between two ECUs */
#define MC2_ASK			0x01
#define MC1_READY		0X02
#define MC1_ASK			0x03
#define MC2_READY		0X04


/********************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/


uint8 freezeFlag = 0;		/* flag that freezes application when necessary */


/* enum to store all possible application of state */
typedef enum
{
	CREATE_PASS, MAIN_SCREEN, OPEN_DOOR, CHANGE_PASS, DOOR_UNLOCKING, ALARM, WAITING
}APPLICATION_STATE;


/********************************************************************************/




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* call back function of alarm */
void alarmCallBackFunction(void);

/* call back function of opening door */
void openDoorCallBackFunction(void);

/* function that send password to ECU2 */
void sendPass(void);

/* function used to create password */
void createPass(void);


/********************************************************************************/



/*******************************************************************************
 *                                Main Funciton                                *
 *******************************************************************************/
int main()
{
	/* variable decelerations:
	 * state  		--->	 to store state of application
	 * key			---> 	 to store selected option from user
	 * uartConfig	---> 	 configuration of UART
	 */
	APPLICATION_STATE state;

	uint8 key;

	UART_CONFIG_TYPE uartConfig = {DISABLE_PARITY, _1BIT, _8BIT, 9600};

	/* initializing UART with certain configurations*/
	UART_init(&uartConfig);

	/* initializing LCD */
	LCD_init();

	/* enabling Global interrupt mask bit */
	SREG_REG.Bits.I_Bit = 1;

	while(1)
	{
		/* ECU1 waits for ECU2 to ask it then respond
		 * then receive the state of application */
		while(UART_recieveByte() != MC2_ASK);
		UART_sendByte(MC1_READY);
		state = UART_recieveByte();

		switch(state)
		{
		case CREATE_PASS:

			createPass();
			state = WAITING;	/* changing state to waiting state */
			break;

		case MAIN_SCREEN:
		{
			LCD_clearScreen();
			LCD_displayString((uint8*)"+:Open Door");
			LCD_displayStringRowColumn(1,0,(uint8*)"-:Change Password");

			while(1)
			{
				/* loop until user press one of the two options */
				key = KEYPAD_getPressedKey();
				_delay_ms(500);	/* delay for keypad */

				if(key == '+' || key == '-')
					break;
			}
			/* ECU1 asks ECU2 and waits for its
			 * response then sends the pressed key*/
			UART_sendByte(MC1_ASK);
			while(UART_recieveByte() != MC2_READY);
			UART_sendByte(key);
		}
		state = WAITING;	/* changing state to waiting state */
		break;

		case OPEN_DOOR:
		{
			sendPass();
		}
		state = WAITING;	/* changing state to waiting state */
		break;

		case CHANGE_PASS:
		{
			sendPass();
		}
		state = WAITING;	/* changing state to waiting state */
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
		}
		state = WAITING;	/* changing state to waiting state */
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

			/* setting state of application to the main state */
			while(freezeFlag == 1);
		}
		state = WAITING;	/* changing state to waiting state */
		break;

		case WAITING:
			/* do nothing */
			break;
		}/* end switch */
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

		/* displaying required message on LCD */
		LCD_clearScreen();
		LCD_displayString((uint8*)"Unlocking Door");
	}
	else if(tick == 6)
	{
		/* displaying required message on LCD */
		LCD_clearScreen();
		LCD_displayString((uint8*)"Door is open");
	}
	else if(tick == 7)
	{
		/* displaying required message on LCD */
		LCD_clearScreen();
		LCD_displayString((uint8*)"Locking Door");
	}
	else if(tick == 12)
	{
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

		/* displaying required message on LCD */
		LCD_clearScreen();
		LCD_displayString((uint8*)"ERROR!!!!");
	}
	if(tick == 7)
	{
		tick = 0;				/* clear interrupt counter */

		freezeFlag = 0;			/* clear freeze flag */

		TIMER1_deInit();		/* de-initializing timer */
	}
}

/********************************************************************************/

void sendPass (void)
{
	uint8 password[5];	/* variable to store password from KEYPAD */

	LCD_clearScreen();
	LCD_displayString((uint8*)"Plz Enter Pass:");
	LCD_moveCursor(1,0);

	for(uint8 i = 0; i < 5; i++)
	{
		password[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);	/* delay for keypad */
	}

	/* waiting for user to press enter key */
	while(KEYPAD_getPressedKey() != '=');
	for(uint8 i = 0; i < 5 ; i++)
	{
		/* ECU1 asks ECU2 and waits for its
		 * response then sends the pressed key*/
		UART_sendByte(MC1_ASK);
		while(UART_recieveByte() != MC2_READY);
		UART_sendByte(password[i]);
	}
}

/********************************************************************************/

void createPass(void)
{
	uint8 password[5],repass[5];

	LCD_clearScreen();
	LCD_displayString((uint8*)"Plz Enter Pass:");
	LCD_moveCursor(1,0);
	for(uint8 i = 0; i < 5 ; i++)
	{
		/* 5 number password is saved from
		 * KEYPAD in local variable array and
		 * displayed as (*) on LCD*/
		password[i] = KEYPAD_getPressedKey();

		LCD_displayCharacter('*');

		_delay_ms(500);	/* delay for keypad */
	}

	/* waiting for user to press enter key */
	while(KEYPAD_getPressedKey() != '=');

	LCD_clearScreen();
	LCD_displayString((uint8*)"Plz re-enter the");
	LCD_moveCursor(1,0);
	LCD_displayString((uint8*)"same Pass: ");

	_delay_ms(500);	/* delay for keypad */
	for(uint8 i = 0; i < 5; i++)
	{
		/* 5 number password is saved from
		 * KEYPAD in local variable array and
		 * displayed as (*) on LCD*/
		repass[i] = KEYPAD_getPressedKey();

		LCD_displayCharacter('*');

		_delay_ms(500);	/* delay for keypad */
	}

	/* waiting for user to press enter key */
	while(KEYPAD_getPressedKey() != '=');

	for(uint8 i = 0; i < 5; i++)
	{
		/* ECU1 asks ECU2 and waits for its
		 * response then sends the 2 passwords*/
		UART_sendByte(MC1_ASK);
		while(UART_recieveByte() != MC2_READY);
		UART_sendByte(password[i]);

		UART_sendByte(MC1_ASK);
		while(UART_recieveByte() != MC2_READY);
		UART_sendByte(repass[i]);
	}
}


/********************************************************************************/
