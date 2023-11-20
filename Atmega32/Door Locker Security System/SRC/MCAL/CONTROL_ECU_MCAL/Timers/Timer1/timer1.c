/*============================================================================================
 * Module : Timer1
 *
 * File Name : timer1.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 Timer1 Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "timer1.h"
#include <avr/interrupt.h>


/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

static void (*gp_CallBack)(void) = NULL_PTR;  /* Global Pointer To Assign ISRs */

TIMER1_Config_t g_TIMER1_Config;


/*===============================================================================
 *                       		 ISR Functions  		                         *
 ================================================================================*/
ISR(TIMER1_OVF_vect)
{
	/* Calling Handler of OVF Mode */
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}


ISR(TIMER1_COMPA_vect)
{
	/* Calling Handler of CTC Mode */
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void MCAL_TIMER1_init(const TIMER1_Config_t *p_TIMER1_Config)
{
	g_TIMER1_Config = *p_TIMER1_Config;

	if(p_TIMER1_Config->Timer1_IRQ != TIMER1_IRQ_DISABLE)
	{
		/* Assign ISR with C function */
		gp_CallBack = (p_TIMER1_Config->p_Timer1_ISR);

		/* Clear Flags */
		TIFR |= (0x3C);

		/* Enable Global Interrupt*/
		SEI();
	}

	/*Configure The Interrupt Mask Enable/Disable*/
	TIMSK = (TIMSK & 0xC3) | (p_TIMER1_Config->Timer1_IRQ);

	/*  Configure The Mode of Timer1, Frequency of Timer1 */
	TCCR1A = (0x0C);
	TCCR1B = (p_TIMER1_Config->Timer1_Mode) | (p_TIMER1_Config->Timer1_Clock);
}

void MCAL_TIMER1_start(void)
{
	/* Start Timer1 by Setting Prescaler */
	TCCR1B |= (g_TIMER1_Config.Timer1_Clock);
}

void MCAL_TIMER1_stop(void)
{
	/* Stop Timer1 by Clearing Clock */
	TCCR1B &= (~(0x07));
}


void MCAL_TIMER1_setCompareValue_A(uint16_t a_TicksNumber)
{
	/* Setting The Compare Value */
	OCR1A = a_TicksNumber;
}

void MCAL_TIMER1_setCompareValue_B(uint16_t a_TicksNumber)
{
	/* Setting The Compare Value */
	OCR1B = a_TicksNumber;
}

void MCAL_TIMER1_setCounter(uint16_t a_Counter)
{
	/* Setting The Initial Counter Value */
	TCNT1  = a_Counter;
}


void MCAL_TIMER1_clearFlags(void)
{
	SET_BIT(TIFR,TOV1);
	SET_BIT(TIFR,OCF1A);
	SET_BIT(TIFR,OCF1B);
}


