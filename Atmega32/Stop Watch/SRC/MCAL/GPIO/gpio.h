/*============================================================================================
 * Module : GPIO
 *
 * File Name : gpio.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 GPIO Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"

/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/
typedef enum
{
	GPIOA_ID,
	GPIOB_ID,
	GPIOC_ID,
	GPIOD_ID
}GPIO_PORT_ID_t;

typedef enum
{
	GPIO_PIN0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
}GPIO_PIN_ID_t;

typedef enum
{
	GPIO_ClEAR_PORT = 0x00,
	GPIO_SET_PORT = 0xFF

}GPIO_PORT_VALUE_t;

typedef enum
{
	GPIO_CLEAR_PIN,
	GPIO_SET_PIN
}GPIO_PIN_VALUE_t;

typedef enum
{
	GPIO_PIN_INPUT,
	GPIO_PIN_OUTPUT
}GPIO_PIN_Direction_t;

typedef enum
{
	GPIO_PORT_INPUT,
	GPIO_PORT_OUTPUT = 0xFF
}GPIO_PORT_Direction_t;
/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/
#define NUM_OF_PORTS           	 4
#define NUM_OF_PINS              8


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_GPIO_PinInit.
 * Brief          : Function To Initialize a Pin in PORTx.
 * Parameter (in) : Pin Configuration.
 * Return         : None.
 * Note           : None																	*/
void MCAL_GPIO_PinInit(uint8_t PORTx, uint8_t PINx, uint8_t Direction);

/**===============================================================================
 * Function Name  : MCAL_GPIO_ReadPin.
 * Brief          : Function To Read a Pin in PORTx.
 * Parameter (in) : PORTx is Port ID.
 * Parameter (in) : The Pin To Be Read.
 * Return         : Value Of Pin if LOGIC_HIGH or LOGIC_LOW.
 * Note           : None																	*/
uint8_t MCAL_GPIO_ReadPin(uint8_t PORTx, uint8_t a_PinNumber);

/**===============================================================================
 * Function Name  : MCAL_GPIO_WritePin.
 * Brief          : Function To Write on a Pin in PORTx.
 * Parameter (in) : PORTx is Port ID.
 * Parameter (in) : The Pin To Write On it.
 * Return         : None.
 * Note           : None																	*/
void MCAL_GPIO_WritePin(uint8_t PORTx, uint8_t a_PinNumber, uint8_t a_Value);

/**===============================================================================
 * Function Name  : MCAL_GPIO_ReadPort.
 * Brief          : Function To Read PORTx, x could be A,B,C or D.
 * Parameter (in) : PORTx is Port ID to Read it.
 * Return         : Value Of Port.
 * Note           : None																	*/
uint8_t MCAL_GPIO_ReadPort(uint8_t PORTx);

/**===============================================================================
 * Function Name  : MCAL_GPIO_WritePort.
 * Brief          : Function To Write on PORTx, x could be A,B,C or D.
 * Parameter (in) : PORTx is Port ID.
 * Parameter (in) : The value To Write it.
 * Return         : None.
 * Note           : None																	*/
void MCAL_GPIO_WritePort(uint8_t PORTx, uint8_t a_Value);

/**===============================================================================
 * Function Name  : MCAL_GPIO_PortInit.
 * Brief          : Function To Initialization a PORTx.
 * Parameter (in) : PORT Configuration.
 * Return         : None.
 * Note           : None																	*/
void MCAL_GPIO_PortInit(uint8_t PORTx, uint8_t Direction);


#endif /* INC_GPIO_H_ */
