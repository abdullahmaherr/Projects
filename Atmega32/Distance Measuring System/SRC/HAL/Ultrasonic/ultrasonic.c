/*============================================================================================
 * Module : Ultrasonic
 *
 * File Name : ultrasonic.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of Ultrasonic Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/
/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

vuint8_t g_edgeCount = 0;
vuint16_t g_timeHigh = 0;


/*===============================================================================
 *                              Private Function                                *
 ================================================================================*/
/**===============================================================================
 * Function Name  : HAL_Ultrasonic_Trigger.
 * Brief          : Function To Trigger The Ultrasonic To Start Generate Waves.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
static void HAL_Ultrasonic_Trigger(void);

/*===============================================================================
 *                              Handler Definition                               *
 ================================================================================*/
/**===============================================================================
 * Function Name  : Ultrasonic_EdegProcessing.
 * Brief          : CallBack Function To To Be Called In ICU ISR.
 * Note           : None.																						*/
void Ultrasonic_EdegProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/* Clear the timer counter register to start measurements from the detected rising edge */
		MCAL_ICU_ClearCounter();

		/* Detect falling edge */
		MCAL_ICU_SetEdgeDetect(FALLING);

	}else if(g_edgeCount == 2)
	{
		/* Store the time value of echo being high */
		g_timeHigh = MCAL_ICU_GetICUValue();

		/* Detect raising edge */
		MCAL_ICU_SetEdgeDetect(RAISING);
	}
}


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/
void HAL_Ultrasonic_Init(void)
{
	/* Initialize the ICU */
	ICU_Config_t icu_config = {FCPU_8,RAISING};
	MCAL_ICU_Init(&icu_config);

	/* Setup the ICU CallBack Function*/
	MCAL_ICU_SetCallBack(Ultrasonic_EdegProcessing);

	/* Setup The Direction For The Trigger Pin as Output */
	MCAL_GPIO_PinInit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_PIN_OUTPUT);
}


uint16_t HAL_Ultrasonic_ReadDistance(void)
{
	uint16_t distance = 0;

	/* Trigger The Ultrasonic */
	HAL_Ultrasonic_Trigger();

	/*
	  Sound velocity =   340.00 m/s = 34000 cm/s. We know that: Distance = Speed * Time
	  Total Distance = ((34000 * Time of High)/2)  (Total distance is divided by 2 because signal travels from Ultrasonic to object and returns)
	  Time of High = Timer Counter Register * (1/F_timer)
	  */
	distance = (17000 * g_timeHigh)/(F_CPU/8);

	return distance;
}



static void HAL_Ultrasonic_Trigger(void)
{
	/* Trigger The Ultrasonic By Sending a 10us Pulse */
	MCAL_GPIO_WritePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_SET_PIN);
	_delay_us(10);
	MCAL_GPIO_WritePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_CLEAR_PIN);
}
