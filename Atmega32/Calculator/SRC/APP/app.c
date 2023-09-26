/*============================================================================================
 * File Name : app.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of a Calculator Program
 *
 * Created on: May 1, 2023
 =============================================================================================*/
#include "gpio.h"
#include "lcd.h"
#include "keypad.h"
#include "util/delay.h"

int main(void)
{
	uint8_t input, operation = 0;
	uint32_t number = 0, result = 0;

	/*Initializing LCD 4 Bits Data Mode*/
	HAL_LCD_Init();

	HAL_LCD_DisplayStringRowCol(0,0,"Calculator");
	_delay_ms(2000);

	HAL_LCD_ClearScreen();

	while(1)
	{
		input = HAL_KEYPAD_PressedKey();

		if((input <= 9) && (input >= 0))
		{
			number *= 10;
			number +=((uint32_t)input);
			HAL_LCD_IntgerToString(number);

		}else if((input == '+') || (input == '-') || (input =='*') || (input =='%'))
		{
			operation = input;
			result = number;
			number = 0;
			HAL_LCD_DisplayCharacter(operation);

		}else if((input == '='))
		{
			switch(operation)
			{
			case '+':
				result += number;
				break;
			case '-':
				result -= number;
				break;
			case '*':
				result *= number;
				break;
			case '%':
				result /= number;
				break;
			}

			HAL_LCD_DisplayCharacter('=');

			/*Printing The Result*/
			HAL_LCD_MoveCursor(1,8);
			HAL_LCD_IntgerToString(result);
			_delay_ms(2000);

			HAL_LCD_ClearScreen();

			number = 0; result = 0; operation = 0;
		}else if(input == 13)
		{
			/* Clear all inputs with clearing the displayed numbers and operators*/
			HAL_LCD_ClearScreen();
			number = 0; result = 0; operation = 0;

		}
		_delay_ms(150);
	}
}

