/*============================================================================================
 * Module : ICU
 *
 * File Name : icu.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 ICU Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "icu.h"
#include <avr/interrupt.h>

/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

static void (*gp_CallBack)(void) = NULL_PTR;


/*===============================================================================
 *                       		 ISR Functions  		                         *
 ================================================================================*/
ISR(TIMER1_CAPT_vect)
{
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}

/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void MCAL_ICU_Init(const ICU_Config_t *p_ICU_Config)
{
	/* Configure ICP1/PD6 as Input */
	CLEAR_BIT(DDRD,PD6);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for ICR Register */
	ICR1 = 0;

	/* Configure Normal Mode, Non PWM, Selected Edge, Selected Clock */
	TCCR1A = (0x0C);
	TCCR1B = (TCCR1B & (0X38)) | ((p_ICU_Config->ICU_Edge)<<6) | (p_ICU_Config->ICU_Clock);

	/* Enable The ICU Interrupt */
	TIMSK |= (1<<TICIE1);
}


void MCAL_ICU_Deinit(void)
{
	/* Assign All Timer1 Registers With The Default Value */
	TCCR1A = 0;
	TCCR1B = 0;
	ICR1 = 0;
	TCNT1 = 0;

	/* Disable The ICU Interrupt */
	TIMSK &= ~(1<<TICIE1);

	/* Clear The CallBack Function */
	gp_CallBack = NULL_PTR;
}


void MCAL_ICU_SetCallBack(void(*a_ISR)(void))
{
	/* Assign The CallBack Function With Handler Address */
	gp_CallBack = a_ISR;
}


void MCAL_ICU_SetEdgeDetect(const ICU_Edge_t a_Edge)
{
	/* Assign The ICES1 Bit With Required Edge */
	WRI_BIT(TCCR1B,ICES1,a_Edge);
}


uint16_t MCAL_ICU_GetICUValue(void)
{
	return ICR1;
}


void MCAL_ICU_ClearCounter(void)
{
	TCNT1 = 0;
}
