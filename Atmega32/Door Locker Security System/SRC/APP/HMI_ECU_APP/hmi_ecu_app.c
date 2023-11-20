/*============================================================================================
 * File Name : hmi_ecu_app.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of HMI_ECU application.
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "usart.h"
#include "timer1.h"
#include "gpio.h"
#include <util/delay.h>


/*===============================================================================
 *                       		 	Macros			                             *
 ================================================================================*/
#define PASSWORD_LENGTH			5
/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/
static uint8_t password_buffer1[PASSWORD_LENGTH];
static uint8_t password_buffer2[PASSWORD_LENGTH];

vuint8_t g_Timer1_Count = 0;
vuint8_t g_Wrong_Password_Count = 0;
/*===============================================================================
 *     		       		 	USART State Definition 			                     *
 ================================================================================*/
typedef enum
{
	USART_HMI_ECU_READY = 0xFF,
	USART_CONTROL_ECU_READY = 0xFE,
	USART_START_STATE_TRANSISSION = 0xFD,
	USART_PASSWORD_MATCHED = 0xFC,
	USART_PASSWORD_UNMATCHED = 0xCF,
	USART_BACK_TO_WORK = 0xDF,
	USART_CREATE_PASS = 0xEF,
	USART_ENTERED_PASS = 0xFB,
	USART_START_DOOR_OPER = 0xBF
}USART_MESSAGE;

/*===============================================================================
 *     		       		 	ISR Functions Definition 		                     *
 ================================================================================*/

static void TIMER1_ISR(void)
{
	g_Timer1_Count++;
	if(g_Timer1_Count == 2)
	{
		MCAL_TIMER1_setCompareValue_A(23438);/*After 3 Seconds Stop Motor*/
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayString("ENTER THE ROOM");

	}else if(g_Timer1_Count == 3)
	{
		MCAL_TIMER1_setCompareValue_A(58594);
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayString("DOOR IS CLOSEING");	/* CONTROL_ECU Closing The Door */

	}
}

/*===============================================================================
 *                                Application                                    *
 ================================================================================*/

/*********************************CREATE NEW PASSWORD FUNCTION*********************************/
bool HMI_ECU_Create_Password(void)
{
	uint8_t i,state;

	/* Read The New Password From The User */
	HAL_LCD_DisplayString("ENTER NEW PASS");
	HAL_LCD_MoveCursor(1, 0);
	for(i = 0; i < PASSWORD_LENGTH; i++)
	{
		/*Reading The Entered Password and Store it Buffer 1 */
		password_buffer1[i] = HAL_KEYPAD_PressedKey();
		if((password_buffer1[i] >= 0) && (password_buffer1[i] <= 9))
		{
			HAL_LCD_DisplayNumber(password_buffer1[i]);
			_delay_ms(200);
			HAL_LCD_MoveCursor(1, i);
			HAL_LCD_DisplayCharacter('*');
		}
		else		/* The Input Is Not Valid */
		{
			HAL_LCD_ClearScreen();
			return FALSE;
		}
	}
	/* Wait Until Enter Button Being Pressed */
	while(HAL_KEYPAD_PressedKey() != 13);

	/* Read The Repeated New Password From The User */
	HAL_LCD_ClearScreen();
	HAL_LCD_DisplayString("REENTER NEW PASS");
	HAL_LCD_MoveCursor(1, 0);

	for(i = 0; i < PASSWORD_LENGTH; i++)
	{
		password_buffer2[i] = HAL_KEYPAD_PressedKey();
		if(password_buffer2[i] >= 0 && password_buffer2[i] <= 9)
		{
			HAL_LCD_DisplayNumber(password_buffer2[i]);
			_delay_ms(200);
			HAL_LCD_MoveCursor(1, i);
			HAL_LCD_DisplayCharacter('*');
		}
		else			/* The Input Is Not Valid */
		{
			HAL_LCD_ClearScreen();
			return FALSE;
		}
	}

	/* Wait Until Enter Button Being Pressed */
	while(HAL_KEYPAD_PressedKey() != 13);

	/* Sending The Passwords To CONTROL_ECU To Check The Validation */
	HAL_LCD_ClearScreen();
	HAL_LCD_DisplayString("PLEASE WAIT...");


	MCAL_USART_TX(USART_START_STATE_TRANSISSION); /* Start Data Transmission */

	MCAL_USART_TX(USART_CREATE_PASS); /* Select The Operation */

	while(MCAL_USART_RX() != USART_CONTROL_ECU_READY);/* Read CONTROL_ECU State to Start Transmission */

	for(i = 0; i < PASSWORD_LENGTH; i++)
	{
		MCAL_USART_TX(password_buffer1[i]); /* Sending The First Password*/
	}

	while(MCAL_USART_RX() != USART_CONTROL_ECU_READY);/* Read CONTROL_ECU State to Start Transmission */

	for(i = 0; i < PASSWORD_LENGTH; i++)
	{
		MCAL_USART_TX(password_buffer2[i]);/* Sending The Second Password*/
	}

	/* Move To Second Phase */
	state = MCAL_USART_RX();
	if(state == USART_PASSWORD_MATCHED)
	{
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayString("PASS IS SET :)");
		_delay_ms(150);
		HAL_LCD_ClearScreen();
		return TRUE;
	}
	else if(state == USART_PASSWORD_UNMATCHED)
	{
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayString("ERORR... :(");
		_delay_ms(150);
		HAL_LCD_ClearScreen();
	}
	return FALSE;
}

/**********************************ENTER PASSWORD FUNCTION*********************************/
bool HMI_ECU_Enter_Password(void)
{
	uint8_t i,state;

	/* Read The Password From The User */
	HAL_LCD_DisplayString("ENTER PASSWORD");
	HAL_LCD_MoveCursor(1, 0);
	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		/*Reading The Entered Password and Store it Buffer 1 */
		password_buffer1[i] = HAL_KEYPAD_PressedKey();
		if((password_buffer1[i] >= 0) && (password_buffer1[i] <= 9))
		{
			HAL_LCD_MoveCursor(1, i);
			HAL_LCD_DisplayCharacter('*');
			_delay_ms(150);
		}
		else
		{
			HAL_LCD_ClearScreen();
			return FALSE;
		}
	}
	/* Wait Until Enter Button Being Pressed */
	while(HAL_KEYPAD_PressedKey() != 13);

	/* Sending The Passwords To CONTROL_ECU To Check The Validation */
	HAL_LCD_ClearScreen();
	HAL_LCD_DisplayString("PLEASE WAIT...");

	MCAL_USART_TX(USART_START_STATE_TRANSISSION); /* Start Data Transmission */

	MCAL_USART_TX(USART_ENTERED_PASS); /* Select The Operation */

	while(MCAL_USART_RX() != USART_CONTROL_ECU_READY);/* Read CONTROL_ECU State to Start Transmission */
	for(i = 0; i < PASSWORD_LENGTH; i++)
	{
		MCAL_USART_TX(password_buffer1[i]); /* Sending The Password*/
	}

	HAL_LCD_ClearScreen();

	/* Move To Second Phase */
	state = MCAL_USART_RX();
	if(state == USART_PASSWORD_MATCHED)
	{
		return TRUE;
	}
	else if(state == USART_PASSWORD_UNMATCHED)
	{
		return FALSE;
	}

}

/*********************************CHANGE PASSWORD FUNCTION*********************************/
void HMI_ECU_Change_Password(void)
{
	uint8_t password_state;
	password_state = HMI_ECU_Enter_Password();	/* Ask The User Enter The Password */

	if(password_state == TRUE)		/* User Entered Right Password */
	{
		g_Wrong_Password_Count = 0;
		HAL_LCD_DisplayString("CHANGE PASSWORD");
		_delay_ms(1000);
		HAL_LCD_ClearScreen();

		/* Force User To Create Correct Password */
		while(HMI_ECU_Create_Password() != TRUE);

	}
	else if(password_state == FALSE)	/* User Entered Wrong Password */
	{
		g_Wrong_Password_Count++;
		if(g_Wrong_Password_Count == 3) /* User Entered The Password Wrong Three Times */
		{
			HAL_LCD_DisplayString("U R IDIOT");/* Lock The System Until CONTROL_ECU Run It Again */
			while(MCAL_USART_RX() != USART_BACK_TO_WORK); /* Waiting Message From Control_ECU For 1 Min */
			HAL_LCD_ClearScreen();
		}else
		{
			HAL_LCD_DisplayString("WRONG PASSWORD");
			_delay_ms(500);
			HAL_LCD_ClearScreen();
			HMI_ECU_Change_Password();
		}
	}
}

/*********************************DOOR OPTIONS FUNCTION*********************************/
void HMI_ECU_Door_Operations(void)
{
	uint8_t password_state;
	password_state = HMI_ECU_Enter_Password();	/* Ask The User Enter The Password */

	if(password_state == TRUE) /* User Entered The Right Password */
	{
		g_Wrong_Password_Count = 0;
		HAL_LCD_DisplayString("WELCOME...");
		_delay_ms(1000);
		HAL_LCD_ClearScreen();

		MCAL_USART_TX(USART_START_STATE_TRANSISSION);
		MCAL_USART_TX(USART_START_DOOR_OPER);	/* Select Door Operation State */

		HAL_LCD_DisplayString("DOOR IS OPENING");	/* CONTROL_ECU Opening The Door */
		MCAL_TIMER1_start();
		while(g_Timer1_Count != 5);/* Wait Until Door Operation Is Done */

		MCAL_TIMER1_stop();
		MCAL_TIMER1_setCounter(0);
		g_Timer1_Count = 0;
	}
	else if(password_state == FALSE)	/* User Entered Wrong Password */
	{
		g_Wrong_Password_Count++;
		if(g_Wrong_Password_Count == 3) /* User Entered The Password Wrong Three Times */
		{
			HAL_LCD_DisplayString("U R IDIOT");/* Lock The System Until CONTROL_ECU Run It Again */
			while(MCAL_USART_RX() != USART_BACK_TO_WORK); /* Waiting Message From Control_ECU For 1 Min */
			HAL_LCD_ClearScreen();
		}else
		{
			HAL_LCD_DisplayString("WRONG PASSWORD");
			_delay_ms(500);
			HAL_LCD_ClearScreen();
			HMI_ECU_Door_Operations();
		}
	}
}

/**********************************SYSTEM OPTIONS FUNCTION*********************************/
void HMI_ECU_System_Options(void)
{
	uint8_t option;
	HAL_LCD_DisplayStringRowCol(0, 0, "+ : OPEN DOOR");
	HAL_LCD_DisplayStringRowCol(1, 0, "- : CHANGE PASS");

	option = HAL_KEYPAD_PressedKey(); /* Read The Selected Option From The User */

	switch (option) {
	case '+':		/*The User Choice IS Open The Door */
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayStringRowCol(0, 0, "UR SELECTION IS");
		HAL_LCD_DisplayStringRowCol(1, 0, "OPEN DOOR ;)");
		_delay_ms(1000);
		HAL_LCD_ClearScreen();

		HMI_ECU_Door_Operations();

		break;

	case '-':		/* The User Choice IS Change The Password */
		HAL_LCD_ClearScreen();
		HAL_LCD_DisplayStringRowCol(0, 0, "UR SELECTION IS");
		HAL_LCD_DisplayStringRowCol(1, 0, "CHANGE PASS ;)");
		_delay_ms(1000);
		HAL_LCD_ClearScreen();

		HMI_ECU_Change_Password();

		break;
	}
}

/******************************INITIALIZATION SYSTEM FUNCTION*********************************/
void HMI_ECU_System_init(void)
{
	/* USART Configuration */
	USART_Config_t usart_config;

	usart_config.USART_Mode = USART_ASYNC_MODE;
	usart_config.USART_BaudRate = USART_BAUDE_RATE_9600;
	usart_config.USART_DataBits = USART_DATA_BITS_8;
	usart_config.USART_ParityBit = USART_PARITY_BIT_EVEN;
	usart_config.USART_StopBits = USART_STOP_BIT_1;
	usart_config.USART_IRQ = USART_RTXC_IRQ_DISABLE;
	usart_config.p_USART_ISR = NULL_PTR;

	MCAL_USART_init(&usart_config);/* USART Initialization */

	/* Timer1 Configuration */
	TIMER1_Config_t timer_config;

	timer_config.Timer1_Mode = TIMER1_MODE_CTC;
	timer_config.Timer1_Clock = TIMER1_CLK_PRESCALER_1024;
	timer_config.Timer1_IRQ = TIMER1_IRQ_CTC_A_ENABLE;
	timer_config.p_Timer1_ISR = TIMER1_ISR;

	MCAL_TIMER1_setCounter(0);
	MCAL_TIMER1_setCompareValue_A(58594);

	MCAL_TIMER1_init(&timer_config);/* Timer Initialization */

	/* LCD Initialization */
	HAL_LCD_Init();
	HAL_LCD_DisplayString("  DOOR LOCKER");
	HAL_LCD_MoveCursor(1, 0);
	HAL_LCD_DisplayString("SECURITY SYSTEM");
	_delay_ms(1000);
	HAL_LCD_ClearScreen();
}

/****************************************MAIN FUNCTION*********************************/
int main(void)
{
	/* Initialize The HMI_ECU */
	HMI_ECU_System_init();

	/* Force User To Create Correct Password */
	while(HMI_ECU_Create_Password() != TRUE);

	while(1)
	{
		HAL_LCD_ClearScreen();
		HMI_ECU_System_Options(); /* Start The System */
	}

}
