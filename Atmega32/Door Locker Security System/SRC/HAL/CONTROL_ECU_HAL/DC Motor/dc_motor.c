/*============================================================================================
 * Module : Motors
 *
 * File Name : dc_motor.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of Motors Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/





/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void HAL_DCMotor_GPIO_Init(uint8_t a_Port,uint8_t a_Pin)
{
	/* Configure The Pins of DC Motor as Output in PORTx */
	MCAL_GPIO_PinInit(a_Port, a_Pin, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(a_Port, (a_Pin+1), GPIO_PIN_OUTPUT);
}


void HAL_DCMotor_Rotate(uint8_t a_Port, uint8_t a_Pin, uint8_t a_Direction)
{
	/* Assign The Motor State */
	if(a_Direction == DCMOTOR_ROT_CW)
	{
		MCAL_GPIO_WritePin(a_Port, a_Pin, GPIO_SET_PIN);
		MCAL_GPIO_WritePin(a_Port, (a_Pin+1), GPIO_CLEAR_PIN);
	}
	else if(a_Direction == DCMOTOR_ROT_CCW)
	{
		MCAL_GPIO_WritePin(a_Port, a_Pin, GPIO_CLEAR_PIN);
		MCAL_GPIO_WritePin(a_Port, (a_Pin+1), GPIO_SET_PIN);
	}
	else if(a_Direction == DCMOTOR_ROT_STOP)
	{
		MCAL_GPIO_WritePin(a_Port, a_Pin, GPIO_CLEAR_PIN);
		MCAL_GPIO_WritePin(a_Port, (a_Pin+1), GPIO_CLEAR_PIN);
	}
}


void HAL_DCMotor_Speed(uint8_t a_pwmx,uint8_t a_speed)
{

	switch(a_pwmx)
	{
	case 0:
		MCAL_TIMER0_PWMInit(PWM_CLK_PRE_8);
		MCAL_TIMER0_PWMSetDuty(a_speed);
		break;
	case 1:
		break;
	case 2:
		MCAL_TIMER2_PWMInit(PWM_CLK_PRE_8);
		MCAL_TIMER2_PWMSetDuty(a_speed);
		break;
	default:
		break;
	}

}

