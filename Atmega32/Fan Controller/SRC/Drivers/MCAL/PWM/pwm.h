/*============================================================================================
 * Module : PWM
 *
 * File Name : pwm.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 PWM Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_PWM_H_
#define INC_PWM_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"


/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/
/* @ref Prescaler */
#define PWM_No_CLK  					(0U)
#define PWM_CLK_PRE_1  					(1U)
#define PWM_CLK_PRE_8  					(2U)
#define PWM_CLK_PRE_64  				(3U)
#define PWM_CLK_PRE_256 				(4U)
#define PWM_CLK_PRE_1024 				(5U)
#define PWM_CLK_EXT_FAILING  			(6U)
#define PWM_CLK_EXT_RAISING  			(7U)

/*@ref Selection of PWM Pin Source For Timer1 */
#define PWM_OC1A 						(0x80U)
#define PWM_OC1B 						(0x20U)
#define PWM_OC1AB 						(0xA0U)

/**===============================================================================
 * Function Name  : MCAL_TIMER0_PWMInit.
 * Brief          : Function To Initialize The Fast PWM Mode In Timer0.
 * Parameter (in) :	Prescaler Regarding to @ref Prescaler.
 * Return         : None.
 * Note           : Timer0 will be used in FAST PWM, Non inverting, F_PWM = (F_CPU)/(256*N) . */
void MCAL_TIMER0_PWMInit(uint8_t a_prescaler);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_PWMInit.
 * Brief          : Function To Initialize The Fast PWM Mode In Timer1.
 * Parameter (in) :  Prescaler Regarding to @ref Prescaler.
 * Parameter (in) :  OC1A or OC1B.
 * Return         : None.
 * Note           : Timer2 will be used in FAST PWM, Non inverting, F_PWM = (F_CPU)/(TOP*N) . */
void MCAL_TIMER1_PWMInit(uint8_t a_prescaler,uint16_t a_top, uint8_t a_pin);

/**===============================================================================
 * Function Name  : MCAL_TIMER2_PWMInit.
 * Brief          : Function To Initialize The Fast PWM Mode In Timer2.
 * Parameter (in) : Prescaler Regarding to @ref Prescaler.
 * Return         : None.
 * Note           : Timer2 will be used in FAST PWM, Non inverting, F_PWM = (F_CPU)/(256*N) . */
void MCAL_TIMER2_PWMInit(uint8_t a_prescaler);

/**===============================================================================
 * Function Name  : MCAL_TIMER0_PWMInit.
 * Brief          : Function To Initialize The Required Duty Cycle.
 * Parameter (in) : The Required Duty Cycle.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER0_PWMSetDuty(uint8_t a_duty);

/**===============================================================================
 * Function Name  : MCAL_TIMER1_PWMInit.
 * Brief          : Function To Initialize The Required Duty Cycle.
 * Parameter (in) : The Required Duty Cycle.
 * Return         : None.
 * Note           : None.																		*/
void MCAL_TIMER1_PWMSetDuty(uint16_t a_duty, uint8_t a_pin);

/**===============================================================================
 * Function Name  : MCAL_TIMER2_PWMInit.
 * Brief          : Function To Initialize The Required Duty Cycle.
 * Parameter (in) : The Required Duty Cycle.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TIMER2_PWMSetDuty(uint8_t a_duty);



#endif /* INC_PWM_H_ */
