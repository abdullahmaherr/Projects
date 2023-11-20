/*============================================================================================
 * Module : GPIO
 *
 * File Name : gpio.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 GPIO Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "gpio.h"


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/
void MCAL_GPIO_PinInit(uint8_t PORTx, uint8_t PINx, uint8_t Direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT.
	 */
	if((PINx >= NUM_OF_PINS) || (PORTx >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as Given */
		switch(PORTx)
		{
		case GPIOA_ID:
			if(Direction == GPIO_PIN_OUTPUT)
			{
				SET_BIT(DDRA,PINx);
			}
			else
			{
				CLEAR_BIT(DDRA,PINx);
			}
			break;
		case GPIOB_ID:
			if(Direction == GPIO_PIN_OUTPUT)
			{
				SET_BIT(DDRB,PINx);
			}
			else
			{
				CLEAR_BIT(DDRB,PINx);
			}
			break;
		case GPIOC_ID:
			if(Direction == GPIO_PIN_OUTPUT)
			{
				SET_BIT(DDRC,PINx);
			}
			else
			{
				CLEAR_BIT(DDRC,PINx);
			}
			break;
		case GPIOD_ID:
			if(Direction == GPIO_PIN_OUTPUT)
			{
				SET_BIT(DDRD,PINx);
			}
			else
			{
				CLEAR_BIT(DDRD,PINx);
			}
			break;
		}
	}
}

void MCAL_GPIO_PortInit(uint8_t PORTx, uint8_t Direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT.
	 */
	if(PORTx >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as Given */
		switch(PORTx)
		{
		case GPIOA_ID:
			DDRA = Direction;
			break;
		case GPIOB_ID:
			DDRB = Direction;
			break;
		case GPIOC_ID:
			DDRC = Direction;
			break;
		case GPIOD_ID:
			DDRD = Direction;
			break;
		}
	}
}

uint8_t MCAL_GPIO_ReadPin(uint8_t PORTx, uint8_t a_PinNumber)
{
	uint8_t pin_value = 0;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT.
	 */
	if(( a_PinNumber >= NUM_OF_PINS) || (PORTx >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as Given */
		switch(PORTx)
		{
		case GPIOA_ID:
			if(BIT_IS_SET(PINA,a_PinNumber))
			{
				pin_value = GPIO_SET_PIN;
			}
			else
			{
				pin_value = GPIO_CLEAR_PIN;
			}
			break;
		case GPIOB_ID:
			if(BIT_IS_SET(PINB,a_PinNumber))
			{
				pin_value = GPIO_SET_PIN;
			}
			else
			{
				pin_value = GPIO_CLEAR_PIN;
			}
			break;
		case GPIOC_ID:
			if(BIT_IS_SET(PINC,a_PinNumber))
			{
				pin_value = GPIO_SET_PIN;
			}
			else
			{
				pin_value = GPIO_CLEAR_PIN;
			}
			break;
		case GPIOD_ID:
			if(BIT_IS_SET(PIND,a_PinNumber))
			{
				pin_value = GPIO_SET_PIN;
			}
			else
			{
				pin_value = GPIO_CLEAR_PIN;
			}
			break;
		}
	}

	return pin_value;
}

void MCAL_GPIO_WritePin(uint8_t PORTx, uint8_t a_PinNumber, uint8_t a_Value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT.
	 */
	if((a_PinNumber >= NUM_OF_PINS) || (PORTx >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as Given */
		switch(PORTx)
		{
		case GPIOA_ID:
			if(a_Value == GPIO_SET_PIN)
			{
				SET_BIT(PORTA,a_PinNumber);
			}
			else
			{
				CLEAR_BIT(PORTA,a_PinNumber);
			}
			break;
		case GPIOB_ID:
			if(a_Value == GPIO_SET_PIN)
			{
				SET_BIT(PORTB,a_PinNumber);
			}
			else
			{
				CLEAR_BIT(PORTB,a_PinNumber);
			}
			break;
		case GPIOC_ID:
			if(a_Value == GPIO_SET_PIN)
			{
				SET_BIT(PORTC,a_PinNumber);
			}
			else
			{
				CLEAR_BIT(PORTC,a_PinNumber);
			}
			break;
		case GPIOD_ID:
			if(a_Value == GPIO_SET_PIN)
			{
				SET_BIT(PORTD,a_PinNumber);
			}
			else
			{
				CLEAR_BIT(PORTD,a_PinNumber);
			}
			break;
		}
	}
}

void MCAL_GPIO_TogglePin(uint8_t PORTx, uint8_t a_PinNumber)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT.
	 */
	if((a_PinNumber >= NUM_OF_PINS) || (PORTx >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Toggle the pin value */
		switch(PORTx)
		{
		case GPIOA_ID:
			TOGGLE_BIT(PORTA,a_PinNumber);
			break;
		case GPIOB_ID:
			TOGGLE_BIT(PORTB,a_PinNumber);
			break;
		case GPIOC_ID:
			TOGGLE_BIT(PORTC,a_PinNumber);
			break;
		case GPIOD_ID:
			TOGGLE_BIT(PORTD,a_PinNumber);
			break;
		}
	}
}

uint8_t MCAL_GPIO_ReadPort(uint8_t PORTx)
{
	uint8_t port_value = 0;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS.
	 */
	if(PORTx >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as Given */
		switch(PORTx)
		{
		case GPIOA_ID:
			port_value = PINA;
			break;
		case GPIOB_ID:
			port_value = PINB;
			break;
		case GPIOC_ID:
			port_value = PINC;
			break;
		case GPIOD_ID:
			port_value = PIND;
			break;
		}
	}

	return port_value;
}

void MCAL_GPIO_WritePort(uint8_t PORTx, uint8_t a_Value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS.
	 */
	if(PORTx >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as given */
		switch(PORTx)
		{
		case GPIOA_ID:
			PORTA = a_Value;
			break;
		case GPIOB_ID:
			PORTB = a_Value;
			break;
		case GPIOC_ID:
			PORTC = a_Value;
			break;
		case GPIOD_ID:
			PORTD = a_Value;
			break;
		}
	}
}
