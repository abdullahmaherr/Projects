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


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/
#define NUM_OF_PORTS           	 4
#define NUM_OF_PINS              8

/* @ref Port Number ID */
#define GPIOA_ID       	         0
#define GPIOB_ID           	     1
#define GPIOC_ID               	 2
#define GPIOD_ID               	 3

/* @ref Pin Number ID */
#define GPIO_PIN0                0
#define GPIO_PIN1                1
#define GPIO_PIN2                2
#define GPIO_PIN3                3
#define GPIO_PIN4                4
#define GPIO_PIN5                5
#define GPIO_PIN6                6
#define GPIO_PIN7                7

#define GPIO_SET_ALL_PIN			 (0xFFu)
#define GPIO_ClEAR_ALL_PIN			 (0x00u)

/* @ref pin Direction if Input or output */
#define GPIO_PIN_INPUT				 0U
#define GPIO_PIN_OUTPUT				 1U

/* @ref port Direction if Input or output */
#define GPIO_PORT_INPUT				 (0x00)
#define GPIO_PORT_OUTPUT			 (0xFF)

/* @ref INT_TRIGGER_SELECT_DEFINE */
#define  INT_RISING_FALLING_TRIG 			0
#define  INT_FALLING_TRIG 					1
#define  INT_RISING_TRIG 					2

/* @ref INT_MASK_DEFINE */
#define INT_MASK_DISABLE					0
#define INT_MASK_ENABLE						1



#define LOGIC_HIGH (1u)
#define LOGIC_LOW (0u)
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



/**===============================================================================
 * Function Name  : MCAL_GPIO_INT0Init.
 * Brief          : Function To Initialization The External Interrupt 0.
 * Parameter (in) : Interrupt Trigger Case.
 * Parameter (in) : Enable/Disable Interrupt Mask.
 * Parameter (in) : Address Of ISR Function .
 * Return         : None.
 * Note           : Must To Enable The Global Interrupt Before Using It.					*/
void MCAL_GPIO_INT0Init(uint8_t a_triggerCase, uint8_t a_IntMask,void (*p_ISR0)(void));

/**===============================================================================
 * Function Name  : MCAL_GPIO_INT1Init.
 * Brief          : Function To Initialization The External Interrupt 1.
 * Parameter (in) : Interrupt Trigger Case.
 * Parameter (in) : Enable/Disable Interrupt Mask.
 * Parameter (in) : Address Of ISR Function .
 * Return         : None.
 * Note           : Must To Enable The Global Interrupt Before Using It.					*/
void MCAL_GPIO_INT1Init(uint8_t a_triggerCase, uint8_t a_IntMask,void (*p_ISR1)(void));

/**===============================================================================
 * Function Name  : MCAL_GPIO_INT2Init.
 * Brief          : Function To Initialization The External Interrupt 2.
 * Parameter (in) : Interrupt Trigger Case.
 * Parameter (in) : Enable/Disable Interrupt Mask.
 * Parameter (in) : Address Of ISR Function .
 * Return         : None.
 * Note           : Must To Enable The Global Interrupt Before Using It.					*/
void MCAL_GPIO_INT2Init(uint8_t a_triggerCase, uint8_t a_IntMask,void (*p_ISR2)(void));


#endif /* INC_GPIO_H_ */
