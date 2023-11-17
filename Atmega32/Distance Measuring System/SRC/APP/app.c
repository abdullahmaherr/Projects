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
#include "ultrasonic.h"
#include "lcd.h"
#include <util/delay.h>

/*===============================================================================
 *                                Application                                    *
 ================================================================================*/

int main(void)
{
	uint16_t distance = 0;

	/* Enable Global Interrupt */
	SEI();

	/* Enable LCD */
	HAL_LCD_Init();
	HAL_LCD_DisplayString("Distance =    cm");
	HAL_LCD_MoveCursor(0,11);

	/* Enable Ultrasonic */
	HAL_Ultrasonic_Init();

	while(1)
	{
		distance = HAL_Ultrasonic_ReadDistance();

		if(distance >= 100)
		{
			HAL_LCD_IntgerToString(distance);

		}else if(distance < 100)
		{
			HAL_LCD_IntgerToString(distance);
			HAL_LCD_DisplayCharacter(' ');
		}

		_delay_ms(10);
	}
}
