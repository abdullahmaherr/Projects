/*============================================================================================
 * Module : TIMER0
 *
 * File Name : timer0.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 TIMER0 Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_TIMER0_H_
#define INC_TIMER0_H_

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
	uint8_t Timer0_Mode;			/* Specifies The Timer Mode (Normal,CTC) Regarding to  @ref TIMER0 Mode*/

	uint8_t Timer0_Clock;	    /* Specifies The Timer Clock Regarding to  @ref TIMER0 Clock&Prescaler*/

	uint8_t Timer0_IRQ;			/* Specifies The Timer Interrupt Request Regarding to  @ref TIMER0 IRQ Enable/Disable */

	void (*p_Timer0_ISR)(void);	/* SET The Call Back Function That Will Be Called In ISR*/

}TIMER0_Config_t;



/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* @ref TIMER0 Modes */
#define TIMER0_MODE_OVF							(0x80U)
#define TIMER0_MODE_CTC							(0x88U)

/* @ref TIMER0 Clock&Prescaler */
#define TIMER0_CLK_STOP							(0x00U)
#define TIMER0_CLK_PRESCALER_0					(0x01U)
#define TIMER0_CLK_PRESCALER_8					(0x02U)
#define TIMER0_CLK_PRESCALER_64					(0x03U)
#define TIMER0_CLK_PRESCALER_256				(0x04U)
#define TIMER0_CLK_PRESCALER_1024				(0x05U)
#define TIMER0_CLK_EXTERNAL_FAILING				(0x06U)/* To Operate as Counter*/
#define TIMER0_CLK_EXTERNAL_RAISING				(0x07U)/* To Operate as Counter*/

/* @ref TIMER0 IRQ Enable/Disable */
#define TIMER0_IRQ_DISABLE						(0x00U)
#define TIMER0_IRQ_OVF_ENABLE					(0x01U)
#define TIMER0_IRQ_CTC_ENABLE					(0x02U)

/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_TIMER0_Init.
 * Brief          : Function To Initialize Timer0.
 * Parameter (in) : Timer0 Configuration.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_init(const TIMER0_Config_t *p_TIMER0_Config);

/**===============================================================================
 * Function Name  : MCAL_TIMER0_Stop.
 * Brief          : Function To Stop Timer0 Counter.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_stop(void);

/**===============================================================================
 * Function Name  : MCAL_TIMER0_Resume.
 * Brief          : Function To Resume Timer0 Counter.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_Start(void);

/**===============================================================================
 * Function Name  : MCAL_TIMER0_SetCompareValue.
 * Brief          : Function To Set Timer0 Compare Value In CTC Mode.
 * Parameter (in) : Compare Value.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_setCompareValue(uint8_t a_TicksNumber);

/**===============================================================================
 * Function Name  : MCAL_TIMER0_SetCounter.
 * Brief          : Function To Set Timer0 Counter Initial Value.
 * Parameter (in) : Counter Initial Value.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_setCounter(uint8_t a_Counter);

#endif /* INC_TIMER0_H_ */
