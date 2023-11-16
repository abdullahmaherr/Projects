/*============================================================================================
 * Module : External Interrupt
 *
 * File Name : exti.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 External Interrupt Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"

/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/
typedef struct
{
	uint8_t EXTI_TriggerCase;	/* Specifies The External Interrupt Trigger Case @ref EXTI_TRIGGER_SELECT */

	uint8_t EXTI_IRQ;			/* Specifies The EXTI Interrupt Request Regarding to  @ref EXTI IRQ Enable/Disable */

	void (*p_EXTI_ISR)(void);

}EXTI_Config_t;


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* @ref EXTI_TRIGGER_SELECT */
#define  EXTI_RISING_FALLING_TRIG 			(0x00U)
#define  EXTI_FALLING_TRIG 					(0x01U)
#define  EXTI_RISING_TRIG					(0x02U)

/*  @ref EXTI IRQ Enable/Disable */
#define EXTI_IRQ_DISABLE					0
#define EXTI_IRQ_ENABLE						1



/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_EXTI_INT0Init.
 * Brief          : Function To Initialization The External Interrupt 0.
 * Parameter (in) : Pointer To The Configuration.
 * Return         : None.
 * Note           : None.																			*/
void MCAL_EXTI_INT0Init(EXTI_Config_t *p_INT0_Config);

/**===============================================================================
 * Function Name  : MCAL_EXTI_INT1Init.
 * Brief          : Function To Initialization The External Interrupt 1.
 * Parameter (in) : Pointer To The Configuration.
 * Return         : None.
 * Note           : None.																			*/
void MCAL_EXTI_INT1Init(EXTI_Config_t *p_INT1_Config);

/**===============================================================================
 * Function Name  : MCAL_EXTI_INT2Init.
 * Brief          : Function To Initialization The External Interrupt 2.
 * Parameter (in) : Pointer To The Configuration.
 * Return         : None.
 * Note           : None.																			*/
void MCAL_EXTI_INT2Init(EXTI_Config_t *p_INT2_Config);



#endif /* INC_EXTI_H_ */
