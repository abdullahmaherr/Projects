/*============================================================================================
 * File Name : app.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of a Calculator Program
 *
 * Created on: April 16, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "gpio.h"
#include "exti.h"
#include "timer1.h"
#include "seven_segment.h"
#include "std_types.h"
#include <util/delay.h>



/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/
volatile uint8_t seconds = 0;    /* Time in Seconds */
volatile uint8_t minutes = 0;   /* Time in Minutes */
volatile uint8_t hours = 0;    /* Time in Hours */


/*===============================================================================
 *                                ISRs		                                     *
 ================================================================================*/
void EXTI0_handler(void)
{
	seconds = 0;
	minutes = 0;
	hours = 0;
}

void EXTI1_handler(void)
{
	MCAL_TIMER1_stop();
}

void EXTI2_handler(void)
{
	MCAL_TIMER1_resume();
}

void Timer1_handler(void)
{
	seconds++;
	if(seconds == 60)
	{
		seconds = 0;
		minutes++;
		if(minutes == 60)
		{
			minutes = 0;
			hours++;
			if(hours == 24)
			{
				seconds = 0;
				minutes = 0;
				hours = 0;
			}
		}
	}
}
/*===============================================================================
 *                                Application                                    *
 ================================================================================*/

void EXTI_INIT(void)
{
	EXTI_Config_t config;

	/* External interrupt0 Configuration */
	config.EXTI_TriggerCase = EXTI_FALLING_TRIG;
	config.EXTI_IRQ = EXTI_IRQ_ENABLE;
	config.p_EXTI_ISR = EXTI0_handler;

	MCAL_EXTI_INT0Init(&config);


	/* External interrupt1 Configuration */
	config.EXTI_TriggerCase = EXTI_RISING_TRIG;
	config.EXTI_IRQ = EXTI_IRQ_ENABLE;
	config.p_EXTI_ISR = EXTI1_handler;

	MCAL_EXTI_INT1Init(&config);

	/* External interrupt2 Configuration */
	config.EXTI_TriggerCase = EXTI_FALLING_TRIG;
	config.EXTI_IRQ = EXTI_IRQ_ENABLE;
	config.p_EXTI_ISR = EXTI2_handler;

	MCAL_EXTI_INT2Init(&config);

}

void TIMER_INIT(void)
{
	TIMER1_Config_t config;
	config.Timer1_Mode = TIMER1_MODE_CTC;
	config.Timer1_Clock = TIMER1_CLK_PRESCALER_64;
	config.Timer1_IRQ = TIMER1_IRQ_CTC_A_ENABLE;
	config.p_Timer1_ISR = Timer1_handler;

	MCAL_TIMER1_setCounter(0);
	MCAL_TIMER1_setCompareValue_A(15625);
	MCAL_TIMER1_init(&config);
}

void GPIO_INIT(void)
{
	/* Configure First 6 Pins of PORTA as output (enable and disenable 7-segment) */
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN0, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN1, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN2, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN3, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN4, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(GPIOA_ID, GPIO_PIN5, GPIO_PIN_OUTPUT);

	/*Disable All at First */
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN0, GPIO_CLEAR_PIN);
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN1, GPIO_CLEAR_PIN);
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN2, GPIO_CLEAR_PIN);
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN3, GPIO_CLEAR_PIN);
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN4, GPIO_CLEAR_PIN);
	MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN5, GPIO_CLEAR_PIN);
}

int main(void)
{
	HAL_SEVEN_SEGMENT_GPIO_init();

	GPIO_INIT();
	EXTI_INIT();
	TIMER_INIT();

	while(1)
	{
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN0, GPIO_SET_PIN);	/* Enable Display on 1st 7-Segment */
		HAL_SEVEN_SEGMENT_dispaly(((seconds % 10 ) & 0x0F));	/* Display Seconds */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN0, GPIO_CLEAR_PIN);/* Disable Display on 1st 7-Segment */


		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN1, GPIO_SET_PIN);  /* Enable Display on 2nd 7-Segment */
		HAL_SEVEN_SEGMENT_dispaly(((seconds / 10) % 10) & 0x0F);/* Display Seconds */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN1, GPIO_CLEAR_PIN);/* Disable Display on 2nd 7-Segment */


		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN2, GPIO_SET_PIN);  /* Enable Display on 3th 7-Segment */
		HAL_SEVEN_SEGMENT_dispaly((minutes % 10 ) & 0x0F);     	/* Display Minutes */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN2, GPIO_CLEAR_PIN);/* Disable Display on 3th 7-Segment */

		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN3, GPIO_SET_PIN);  /* Enable Display on 4th 7-Segment */
		HAL_SEVEN_SEGMENT_dispaly(((minutes / 10) % 10) & 0x0F);/* Display Minutes */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN3, GPIO_CLEAR_PIN);/* Disable Display on 4th 7-Segment */


		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN4, GPIO_SET_PIN);  /* Enable Display on 5th 7-Segment*/
		HAL_SEVEN_SEGMENT_dispaly((hours % 10) & 0x0F);     	/* Display Hours */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN4, GPIO_CLEAR_PIN);/* Disable Display on 5th 7-Segment */



		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN5, GPIO_SET_PIN);  /* Enable Display on 6th 7-Segment*/
		HAL_SEVEN_SEGMENT_dispaly(((hours / 10) % 10) & 0x0F);	/* Display Hours */
		_delay_ms(2);
		MCAL_GPIO_WritePin(GPIOA_ID, GPIO_PIN5, GPIO_CLEAR_PIN);/* Disable Display on 6th 7-Segment */

	}
}
