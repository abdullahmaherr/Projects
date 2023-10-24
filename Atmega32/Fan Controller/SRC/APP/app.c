/*============================================================================================
 * File Name : app.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of a Fan Controller.
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/

#include "std_types.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include "dc_motor.h"
#include "lm35.h"
#include "lcd.h"


/*===============================================================================
 *                                Application                                    *
 ================================================================================*/

int main(void)
{
	uint8_t Temperature;

	/* Initialization of Component */
	HAL_LCD_Init();
	HAL_DCMotor_GPIO_Init(GPIOB_ID, GPIO_PIN0);
	HAL_LM35_ADC_Init();

	HAL_LCD_DisplayStringRowCol(0,1, "FAN CONTROLLER");
	_delay_ms(1000);
	HAL_LCD_ClearScreen();

	HAL_LCD_DisplayStringRowCol(0,0, "Fan Is ");
	HAL_LCD_DisplayStringRowCol(1,0, "Temp. Is ");

	while(1)
	{
		Temperature = HAL_LM35_GetTemp();
		HAL_LCD_MoveCursor(1,10);
		if(Temperature >= 100)
		{
			HAL_LCD_IntgerToString(Temperature);
		}else
		{
			HAL_LCD_IntgerToString(Temperature);
			HAL_LCD_DisplayCharacter(' ');
		}

		if(Temperature < 30)
		{
			HAL_LCD_DisplayStringRowCol(0, 9, "STOP  ");
			HAL_DCMotor_Rotate(GPIOB_ID, GPIO_PIN0, DCMOTOR_ROT_STOP);
			HAL_DCMotor_Speed(PWM0, 0);

		}else if((Temperature >= 30) && (Temperature < 60))
		{
			HAL_LCD_DisplayStringRowCol(0, 9, "RUN_CW");
			HAL_DCMotor_Rotate(GPIOB_ID, GPIO_PIN0, DCMOTOR_ROT_CW);
			HAL_DCMotor_Speed(PWM0, 25);

		}else if((Temperature >= 60) && (Temperature < 90))
		{
			HAL_LCD_DisplayStringRowCol(0, 9, "RUN_CW");
			HAL_DCMotor_Rotate(GPIOB_ID, GPIO_PIN0, DCMOTOR_ROT_CW);
			HAL_DCMotor_Speed(PWM0, 50);

		}else if((Temperature >= 90) && (Temperature < 120))
		{
			HAL_LCD_DisplayStringRowCol(0, 9, "RUN_CW");
			HAL_DCMotor_Rotate(GPIOB_ID, GPIO_PIN0, DCMOTOR_ROT_CW);
			HAL_DCMotor_Speed(PWM0, 75);

		}else if((Temperature >= 120))
		{
			HAL_LCD_DisplayStringRowCol(0, 9, "RUN_CW");
			HAL_DCMotor_Rotate(GPIOB_ID, GPIO_PIN0, DCMOTOR_ROT_CW);
			HAL_DCMotor_Speed(PWM0, 100);
		}
	}
}


