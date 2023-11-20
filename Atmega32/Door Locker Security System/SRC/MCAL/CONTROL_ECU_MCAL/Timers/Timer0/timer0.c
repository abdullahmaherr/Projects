/*============================================================================================
 * Module : Timer0
 *
 * File Name : timer0.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 Timer0 Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "timer0.h"
#include <avr/interrupt.h>



/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

static void (*gp_CallBack)(void) = NULL_PTR;  /* Global Pointer To Assign ISRs */

TIMER0_Config_t g_TIMER0_Config;


/*===============================================================================
 *                       		 ISR Functions  		                         *
 ================================================================================*/
ISR(TIMER0_OVF_vect)
{
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}


ISR(TIMER0_COMP_vect)
{
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void MCAL_TIMER0_init(const TIMER0_Config_t *p_TIMER0_Config)
{
	g_TIMER0_Config = *p_TIMER0_Config;

	if(p_TIMER0_Config->Timer0_IRQ != TIMER0_IRQ_DISABLE)
	{
		/* Assign ISR with C function */
		gp_CallBack = p_TIMER0_Config->p_Timer0_ISR;

		/* Clear Flags */
		TIFR |= (0x03);

		/* Enable Global Interrupt */
		SEI();
	}

	/*Configure The Interrupt Mask Enable/Disable*/
	TIMSK = (TIMSK & 0xFC) | (p_TIMER0_Config->Timer0_IRQ);

	/* Configure The Mode of Timer0, Frequency of Timer0 */
	TCCR0 = (p_TIMER0_Config->Timer0_Mode) | (p_TIMER0_Config->Timer0_Clock);
}


void MCAL_TIMER0_stop(void)
{
	/* Stop Timer0 by Clearing Prescaler */
	TCCR0 &= (~(0x07));
}


void MCAL_TIMER0_Start(void)
{
	/* Resume Timer0 by Setting Prescaler */
	TCCR0 |= (g_TIMER0_Config.Timer0_Clock);
}


void MCAL_TIMER0_setCompareValue(uint8_t a_TicksNumber)
{
	/* Setting The Compare Value */
	OCR0 = a_TicksNumber;
}


void MCAL_TIMER0_setCounter(uint8_t a_Counter)
{
	/* Setting The Initial Counter Value */
	TCNT0 = a_Counter;
}


