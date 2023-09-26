/*============================================================================================
 * Module : KEYPAD
 *
 * File Name : keypad.h
 *
 * Author: Abdullah Maher
 *
 * Description : Headder File Of KEYPAD Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "gpio.h"

/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/*Static Configuration of Number Of Rows and Columns Could Be 4x4 Or 4x3*/
#define KEYPAD_NUM_ROW 		4
#define KEYPAD_NUM_COL	 	4 /*COLS Will Be 3 in 3x4*/

/*Static Configuration Of Rows Port and Pins*/
#define KEYPAD_ROW_PORT_ID  		GPIOB_ID
#define KEYPAD_ROW_FIRST_PIN_ID		GPIO_PIN4

/*Static Configuration Of Columns Port and Pins*/
#define KEYPAD_COL_PORT_ID  		GPIOD_ID
#define KEYPAD_COL_FIRST_PIN_ID		GPIO_PIN2

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : HAL_KEYPAD_PressedKey.
 * Brief          : Function To Get The Pressed Key.
 * Parameter (in) : None.
 * Return         : The Pressed Key Location.
 * Note           : None*/
uint8_t HAL_KEYPAD_PressedKey(void);


#endif /* INC_KEYPAD_H_ */
