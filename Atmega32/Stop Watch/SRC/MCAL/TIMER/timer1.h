/*============================================================================================
 * Module : TIMER1
 *
 * File Name : timer1.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 TIMER1 Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_TIMER1_H_
#define INC_TIMER1_H_

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
	uint8_t Timer1_Mode;			/* Specifies The Timer Mode (Normal,CTC) Regarding to  @ref TIMER1 Mode*/

	uint8_t Timer1_Clock;	   		/* Specifies The Timer Clock Regarding to  @ref TIMER1 Clock&Prescaler*/

	uint8_t Timer1_IRQ;				/* Specifies The Timer Interrupt Request Regarding to  @ref TIMER1 IRQ Enable/Disable */

	void (*p_Timer1_ISR)(void);		/* SET The Call Back Function That Will Be Called In ISR */

}TIMER1_Config_t;


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* @ref TIMER1 Mode*/
#define TIMER1_MODE_OVF						(0x00U)
#define TIMER1_MODE_CTC						(0x08U)

/* @ref TIMER1 Clock&Prescaler */
#define TIMER1_CLK_STOP						(0x00U)
#define TIMER1_CLK_PRESCALER_0				(0x01U)
#define TIMER1_CLK_PRESCALER_8				(0x02U)
#define TIMER1_CLK_PRESCALER_64				(0x03U)
#define TIMER1_CLK_PRESCALER_256			(0x04U)
#define TIMER1_CLK_PRESCALER_1024			(0x05U)
#define TIMER1_CLK_EXTERNAL_FAILING			(0x06U)/* To Operate as Counter*/
#define TIMER1_CLK_EXTERNAL_RAISING			(0x07U)/* To Operate as Counter*/

/* @ref TIMER1 IRQ Enable/Disable */
#define TIMER1_IRQ_DISABLE					(0x00U)
#define TIMER1_IRQ_OVF_ENABLE				(0x04U)
#define TIMER1_IRQ_CTC_ENABLE				(0x18U)
#define TIMER1_IRQ_CTC_A_ENABLE				(0x10U)
#define TIMER1_IRQ_CTC_B_ENABLE				(0x08U)

/* Specifies the compare register 1 or 2 in CTC mode*/
#define TIMER1_COMPARE_VALUE_A			(1)
#define TIMER1_COMPARE_VALUE_B			(2)

/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_TIMER1_Init.
 * Brief          : Function To Initialize Timer1.
 * Parameter (in) : Timer1 Configuration.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_init(const TIMER1_Config_t *p_TIMER1_Config);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_Stop.
 * Brief          : Function To Stop Timer1 Counter.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_stop(void);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_Resume.
 * Brief          : Function To Resume Timer1 Counter.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_resume(void);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_SetCompareValue.
 * Brief          : Function To Set Timer1 Compare Value In CTC Mode.
 * Parameter (in) : Compare Value.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_setCompareValue_A(uint16_t a_TicksNumber);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_SetCompareValue.
 * Brief          : Function To Set Timer1 Compare Value In CTC Mode.
 * Parameter (in) : Compare Value.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_setCompareValue_B(uint16_t a_TicksNumber);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_SetCounter.
 * Brief          : Function To Set Timer1 Counter Initial Value.
 * Parameter (in) : Counter Initial Value.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_setCounter(uint16_t a_Counter);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_ClearFlags.
 * Brief          : Function To Clear All Flags.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER1_clearFlags(void);


#endif /* INC_TIMER1_H_ */
