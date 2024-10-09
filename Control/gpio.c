/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#include "gpio.h"
#include "avr_registers.h"


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
		{
			switch(pin_num)
			{
			case 0:
				DDRA_REG.Bits.Bit0 = direction;
				break;
			case 1:
				DDRA_REG.Bits.Bit1 = direction;
				break;
			case 2:
				DDRA_REG.Bits.Bit2 = direction;
				break;
			case 3:
				DDRA_REG.Bits.Bit3 = direction;
				break;
			case 4:
				DDRA_REG.Bits.Bit4 = direction;
				break;
			case 5:
				DDRA_REG.Bits.Bit5 = direction;
				break;
			case 6:
				DDRA_REG.Bits.Bit6 = direction;
				break;
			case 7:
				DDRA_REG.Bits.Bit7 = direction;
				break;
			}
			break;
		}
		case PORTB_ID:
		{
			switch(pin_num)
			{
			case 0:
				DDRB_REG.Bits.Bit0 = direction;
				break;
			case 1:
				DDRB_REG.Bits.Bit1 = direction;
				break;
			case 2:
				DDRB_REG.Bits.Bit2 = direction;
				break;
			case 3:
				DDRB_REG.Bits.Bit3 = direction;
				break;
			case 4:
				DDRB_REG.Bits.Bit4 = direction;
				break;
			case 5:
				DDRB_REG.Bits.Bit5 = direction;
				break;
			case 6:
				DDRB_REG.Bits.Bit6 = direction;
				break;
			case 7:
				DDRB_REG.Bits.Bit7 = direction;
				break;
			}
			break;
		}
		case PORTC_ID:
		{
			switch(pin_num)
			{
			case 0:
				DDRC_REG.Bits.Bit0 = direction;
				break;
			case 1:
				DDRC_REG.Bits.Bit1 = direction;
				break;
			case 2:
				DDRC_REG.Bits.Bit2 = direction;
				break;
			case 3:
				DDRC_REG.Bits.Bit3 = direction;
				break;
			case 4:
				DDRC_REG.Bits.Bit4 = direction;
				break;
			case 5:
				DDRC_REG.Bits.Bit5 = direction;
				break;
			case 6:
				DDRC_REG.Bits.Bit6 = direction;
				break;
			case 7:
				DDRC_REG.Bits.Bit7 = direction;
				break;
			}
			break;
		}
		case PORTD_ID:
		{
			switch(pin_num)
			{
			case 0:
				DDRD_REG.Bits.Bit0 = direction;
				break;
			case 1:
				DDRD_REG.Bits.Bit1 = direction;
				break;
			case 2:
				DDRD_REG.Bits.Bit2 = direction;
				break;
			case 3:
				DDRD_REG.Bits.Bit3 = direction;
				break;
			case 4:
				DDRD_REG.Bits.Bit4 = direction;
				break;
			case 5:
				DDRD_REG.Bits.Bit5 = direction;
				break;
			case 6:
				DDRD_REG.Bits.Bit6 = direction;
				break;
			case 7:
				DDRD_REG.Bits.Bit7 = direction;
				break;
			}
			break;
		}
		}
	}
}


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
		{
			switch(pin_num)
			{
			case 0:
				PORTA_REG.Bits.Bit0 = value;
				break;
			case 1:
				PORTA_REG.Bits.Bit1 = value;
				break;
			case 2:
				PORTA_REG.Bits.Bit2 = value;
				break;
			case 3:
				PORTA_REG.Bits.Bit3 = value;
				break;
			case 4:
				PORTA_REG.Bits.Bit4 = value;
				break;
			case 5:
				PORTA_REG.Bits.Bit5 = value;
				break;
			case 6:
				PORTA_REG.Bits.Bit6 = value;
				break;
			case 7:
				PORTA_REG.Bits.Bit7 = value;
				break;
			}
			break;
		}
		case PORTB_ID:
		{
			switch(pin_num)
			{
			case 0:
				PORTB_REG.Bits.Bit0 = value;
				break;
			case 1:
				PORTB_REG.Bits.Bit1 = value;
				break;
			case 2:
				PORTB_REG.Bits.Bit2 = value;
				break;
			case 3:
				PORTB_REG.Bits.Bit3 = value;
				break;
			case 4:
				PORTB_REG.Bits.Bit4 = value;
				break;
			case 5:
				PORTB_REG.Bits.Bit5 = value;
				break;
			case 6:
				PORTB_REG.Bits.Bit6 = value;
				break;
			case 7:
				PORTB_REG.Bits.Bit7 = value;
				break;
			}
			break;
		}
		case PORTC_ID:
		{
			switch(pin_num)
			{
			case 0:
				PORTC_REG.Bits.Bit0 = value;
				break;
			case 1:
				PORTC_REG.Bits.Bit1 = value;
				break;
			case 2:
				PORTC_REG.Bits.Bit2 = value;
				break;
			case 3:
				PORTC_REG.Bits.Bit3 = value;
				break;
			case 4:
				PORTC_REG.Bits.Bit4 = value;
				break;
			case 5:
				PORTC_REG.Bits.Bit5 = value;
				break;
			case 6:
				PORTC_REG.Bits.Bit6 = value;
				break;
			case 7:
				PORTC_REG.Bits.Bit7 = value;
				break;
			}
			break;
		}
		case PORTD_ID:
		{
			switch(pin_num)
			{
			case 0:
				PORTD_REG.Bits.Bit0 = value;
				break;
			case 1:
				PORTD_REG.Bits.Bit1 = value;
				break;
			case 2:
				PORTD_REG.Bits.Bit2 = value;
				break;
			case 3:
				PORTD_REG.Bits.Bit3 = value;
				break;
			case 4:
				PORTD_REG.Bits.Bit4 = value;
				break;
			case 5:
				PORTD_REG.Bits.Bit5 = value;
				break;
			case 6:
				PORTD_REG.Bits.Bit6 = value;
				break;
			case 7:
				PORTD_REG.Bits.Bit7 = value;
				break;
			}
			break;
		}
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
		{
			switch(pin_num)
			{
			case 0:
				pin_value = PINA_REG.Bits.Bit0;
				break;
			case 1:
				pin_value = PINA_REG.Bits.Bit1;
				break;
			case 2:
				pin_value = PINA_REG.Bits.Bit2;
				break;
			case 3:
				pin_value = PINA_REG.Bits.Bit3;
				break;
			case 4:
				pin_value = PINA_REG.Bits.Bit4;
				break;
			case 5:
				pin_value = PINA_REG.Bits.Bit5;
				break;
			case 6:
				pin_value = PINA_REG.Bits.Bit6;
				break;
			case 7:
				pin_value = PINA_REG.Bits.Bit7;
				break;
			}
			break;
		}
		case PORTB_ID:
		{
			switch(pin_num)
			{
			case 0:
				pin_value = PINB_REG.Bits.Bit0;
				break;
			case 1:
				pin_value = PINB_REG.Bits.Bit1;
				break;
			case 2:
				pin_value = PINB_REG.Bits.Bit2;
				break;
			case 3:
				pin_value = PINB_REG.Bits.Bit3;
				break;
			case 4:
				pin_value = PINB_REG.Bits.Bit4;
				break;
			case 5:
				pin_value = PINB_REG.Bits.Bit5;
				break;
			case 6:
				pin_value = PINB_REG.Bits.Bit6;
				break;
			case 7:
				pin_value = PINB_REG.Bits.Bit7;
				break;
			}
			break;
		}
		case PORTC_ID:
		{
			switch(pin_num)
			{
			case 0:
				pin_value = PINC_REG.Bits.Bit0;
				break;
			case 1:
				pin_value = PINC_REG.Bits.Bit1;
				break;
			case 2:
				pin_value = PINC_REG.Bits.Bit2;
				break;
			case 3:
				pin_value = PINC_REG.Bits.Bit3;
				break;
			case 4:
				pin_value = PINC_REG.Bits.Bit4;
				break;
			case 5:
				pin_value = PINC_REG.Bits.Bit5;
				break;
			case 6:
				pin_value = PINC_REG.Bits.Bit6;
				break;
			case 7:
				pin_value = PINC_REG.Bits.Bit7;
				break;
			}
			break;
		}
		case PORTD_ID:
		{
			switch(pin_num)
			{
			case 0:
				pin_value = PIND_REG.Bits.Bit0;
				break;
			case 1:
				pin_value = PIND_REG.Bits.Bit1;
				break;
			case 2:
				pin_value = PIND_REG.Bits.Bit2;
				break;
			case 3:
				pin_value = PIND_REG.Bits.Bit3;
				break;
			case 4:
				pin_value = PIND_REG.Bits.Bit4;
				break;
			case 5:
				pin_value = PIND_REG.Bits.Bit5;
				break;
			case 6:
				pin_value = PIND_REG.Bits.Bit6;
				break;
			case 7:
				pin_value = PIND_REG.Bits.Bit7;
				break;
			}
			break;
		}
		}
	}

	return pin_value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			DDRA_REG.Byte = direction;
			break;
		case PORTB_ID:
			DDRB_REG.Byte = direction;
			break;
		case PORTC_ID:
			DDRC_REG.Byte = direction;
			break;
		case PORTD_ID:
			DDRD_REG.Byte = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			PORTA_REG.Byte = value;
			break;
		case PORTB_ID:
			PORTB_REG.Byte = value;
			break;
		case PORTC_ID:
			PORTC_REG.Byte = value;
			break;
		case PORTD_ID:
			PORTD_REG.Byte = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA_REG.Byte;
			break;
		case PORTB_ID:
			value = PINB_REG.Byte;
			break;
		case PORTC_ID:
			value = PINC_REG.Byte;
			break;
		case PORTD_ID:
			value = PIND_REG.Byte;
			break;
		}
	}

	return value;
}
