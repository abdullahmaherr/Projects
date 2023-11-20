/*============================================================================================
 * Module : Buzzer
 *
 * File Name : buzzer.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 Buzzer Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "buzzer.h"
#include "gpio.h"
#include <util/delay.h>


/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

/*===============================================================================
 *                            		  MACROS	                                 *
 ================================================================================*/


/*===============================================================================
 *                      Prototype of Private Function                            *
 ================================================================================*/


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void HAL_BUZZER_GPIO_init(void)
{
	/* Configure Buzzers's Pin As Output */
	MCAL_GPIO_PinInit(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_OUTPUT);

	/* Turn Buzzer Off At Beginning */
	MCAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_CLEAR_PIN);
}


void HAL_BUZZER_ON(void)
{
	/* Turn Buzzer ON */
	MCAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_SET_PIN);
}

void HAL_BUZZER_OFF(void)
{
	/* Turn Buzzer OFF */
	MCAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_CLEAR_PIN);
}

void HAL_BUZZER_Alarm(void)
{
	for(int i = 0; i < 3; i++)
	{
		HAL_BUZZER_ON();
		_delay_ms(100);
		HAL_BUZZER_OFF();
		_delay_ms(100);
	}
}

