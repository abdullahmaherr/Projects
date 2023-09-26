/*============================================================================================
 * Module : LCD
 *
 * File Name : lcd.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of LCD Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/
#include "lcd.h"
#include "gpio.h"
#include"atmega32.h"


/*===============================================================================
 *                      Prototype of Private Function                            *
 ================================================================================*/
/**===============================================================================
 * Function Name  : delay_ms.
 * Brief          : Function To Make Delay.
 * Parameter (in) : delay time.
 * Return         : None.
 * Note           : None																				*/
static void delay_ms(uint32_t delay);


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void HAL_LCD_Init(void)
{
	/* Configure RS Pin */
	MCAL_GPIO_PinInit(LCD_RS_PORT, LCD_RS_PIN,GPIO_PIN_OUTPUT);

	/* Configure E Pin */
	MCAL_GPIO_PinInit(LCD_E_PORT,LCD_E_PIN, GPIO_PIN_OUTPUT);

	delay_ms(20);/*Delay for Processing*/

#if(LCD_DATA_BITS_MODE == 8)

	/* Configure the data port as output port */
	MCAL_GPIO_PortInit(LCD_DATA_PORT, GPIO_PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	HAL_LCD_SendCommand(LCD_CMD_FUNCTION_8BIT_2LINES);

#elif(LCD_DATA_BITS_MODE == 4)

	/* Configure 4 pins in the data port as output pins */
	MCAL_GPIO_PinInit(LCD_DATA_PORT,LCD_DB4_PIN, GPIO_PIN_OUTPUT);

	MCAL_GPIO_PinInit(LCD_DATA_PORT,LCD_DB5_PIN, GPIO_PIN_OUTPUT);

	MCAL_GPIO_PinInit(LCD_DATA_PORT,LCD_DB6_PIN, GPIO_PIN_OUTPUT);

	MCAL_GPIO_PinInit(LCD_DATA_PORT,LCD_DB7_PIN, GPIO_PIN_OUTPUT);

	HAL_LCD_SendCommand(0x02);
	delay_ms(1);
	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	HAL_LCD_SendCommand(LCD_CMD_FUNCTION_4BIT_2LINES);

#endif

	delay_ms(1);/*Delay for Processing*/
	HAL_LCD_SendCommand(LCD_CMD_ENTRY_MODE);
	delay_ms(1);/*Delay for Processing*/
	HAL_LCD_SendCommand(LCD_CMD_BEGIN_AT_FIRST_ROW);
	delay_ms(1);/*Delay for Processing*/
	HAL_LCD_SendCommand(LCD_CMD_DISP_ON_CURSOR_BLINK);

}


void HAL_LCD_SendCommand(uint8_t a_command)
{
	delay_ms(5);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_LOW);/*RS = 0 Send Command Mode */
	delay_ms(1);/*Delay for Processing*/

	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */
	delay_ms(1);/*Delay for Processing*/

#if(LCD_DATA_BITS_MODE == 8)
	MCAL_GPIO_WritePort(LCD_DATA_PORT, a_command);
#elif(LCD_DATA_BITS_MODE == 4)

	/*Send Most 4 Bit*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(a_command,4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(a_command,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(a_command,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(a_command,7));

	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);/* Disable LCD E=0 */
	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */

	/*Send Least 4 Bit*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(a_command,0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(a_command,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(a_command,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(a_command,3));
#endif

	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);/* Disable LCD E=0 */
	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */
}

void HAL_LCD_DisplayCharacter(uint8_t a_data)
{
	delay_ms(5);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_HIGH);/*RS = 1 Data Mode */
	delay_ms(1);/*Delay for Processing*/

	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */
	delay_ms(1);/*Delay for Processing*/

#if(LCD_DATA_BITS_MODE == 8)
	MCAL_GPIO_WritePort(LCD_DATA_PORT, a_data);
#elif(LCD_DATA_BITS_MODE == 4)

	/*Send Most 4 Bit*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(a_data,4));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(a_data,5));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(a_data,6));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(a_data,7));

	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);/* Disable LCD E=0 */
	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */

	/*Send Least 4 Bit*/
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(a_data,0));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(a_data,1));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(a_data,2));
	MCAL_GPIO_WritePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(a_data,3));
#endif

	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);/* Disable LCD E=0 */
	delay_ms(1);/*Delay for Processing*/
	MCAL_GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);/* Enable LCD E=1 */
}

void HAL_LCD_DisplayString(const uint8_t * p_str)
{
	uint8_t count = 0;

	while((*p_str) != '\0')
	{
		count++;
		HAL_LCD_DisplayCharacter((*p_str));
		p_str++;

		if(count == 16)
		{
			HAL_LCD_MoveCursor(1,0);
		}
		else if(count == 32)
		{
			HAL_LCD_ClearScreen();
			HAL_LCD_MoveCursor(0,0);
			count = 0;
		}
	}
}

void HAL_LCD_MoveCursor(uint8_t a_row,uint8_t a_col)
{
	uint8_t lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(a_row)
	{
	case 0:
		lcd_memory_address=a_col;
		break;
	case 1:
		lcd_memory_address=a_col+0x40;
		break;
	case 2:
		lcd_memory_address=a_col+0x10;
		break;
	case 3:
		lcd_memory_address=a_col+0x50;
		break;
	}

	/* Move the LCD cursor to this specific address */
	HAL_LCD_SendCommand((lcd_memory_address | LCD_CMD_BEGIN_AT_FIRST_ROW));
}

void HAL_LCD_DisplayStringRowCol(uint8_t a_row,uint8_t a_col,const uint8_t * p_str)
{
	HAL_LCD_MoveCursor(a_row, a_col);
	HAL_LCD_DisplayString(p_str);
}

void HAL_LCD_ClearScreen(void)
{
	HAL_LCD_SendCommand(LCD_CMD_CLEAR_SCREEN);
}

void HAL_LCD_IntgerToString(uint32_t a_data)
{
	uint8_t buffer[16];
	itoa(a_data,buffer,10); /*The function ltoa() converts the long integer value from val into an ASCII representation*/
	HAL_LCD_DisplayString(buffer);
}

static void delay_ms(uint32_t delay)
{
	uint32_t i, j;
	for (i = 0; i < delay; i++)
	{
		for (j = 0; j < 255; j++);
	}
}
