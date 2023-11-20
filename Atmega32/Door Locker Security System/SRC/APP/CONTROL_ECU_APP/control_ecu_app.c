/*============================================================================================
 * File Name : control_ecu_app.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of CONTROL_ECU application.
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "std_types.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "eeprom.h"
#include "usart.h"
#include "twi.h"
#include "timer1.h"
#include "gpio.h"
#include <util/delay.h>
/*===============================================================================
 *                       		 	Macros			                             *
 ================================================================================*/
#define PASSWORD_LENGTH					5
#define EEPROM_PASSWORD_ADDRESS			0x0300
/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/
static uint8_t password_buffer1[PASSWORD_LENGTH];
static uint8_t password_buffer2[PASSWORD_LENGTH];

vuint8_t g_Timer1_Count = 0;
vuint8_t g_Wrong_Password_Count = 0;
vuint8_t g_Motor_Count = 0;
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

static void TIMER1_ISR_CTC(void)
{
	g_Timer1_Count++;

}

static void TIMER1_ISR_OVF(void)
{
	g_Timer1_Count++;
}
/*===============================================================================
 *                                Application                                    *
 ================================================================================*/

void TIMER_INIT_OVF(void)
{
	/* Timer1 Configuration */
	TIMER1_Config_t timer_config;
	timer_config.Timer1_Mode = TIMER1_MODE_OVF;
	timer_config.Timer1_Clock = TIMER1_CLK_PRESCALER_1024;
	timer_config.Timer1_IRQ = TIMER1_IRQ_OVF_ENABLE;
	timer_config.p_Timer1_ISR = TIMER1_ISR_OVF;

	MCAL_TIMER1_setCounter(0);
	MCAL_TIMER1_init(&timer_config);/* Timer Initialization */
}

void TIMER_INIT_CTC(void)
{
	/* Timer1 Configuration */
	TIMER1_Config_t timer_config;
	timer_config.Timer1_Mode = TIMER1_MODE_CTC;
	timer_config.Timer1_Clock = TIMER1_CLK_PRESCALER_1024;
	timer_config.Timer1_IRQ = TIMER1_IRQ_CTC_A_ENABLE;
	timer_config.p_Timer1_ISR = TIMER1_ISR_CTC;

	MCAL_TIMER1_setCounter(0);
	MCAL_TIMER1_setCompareValue_A(58594);
	MCAL_TIMER1_init(&timer_config);/* Timer Initialization */
}

void CONTROL_ECU_Door(void)
{
	TIMER_INIT_CTC();
	HAL_DCMotor_Rotate(GPIOA_ID, GPIO_PIN0, DCMOTOR_ROT_CW); 	/* Open The Door*/
	MCAL_TIMER1_start();/* Other Door Operation To Be Handled In ISR */

	while(g_Timer1_Count != 5)
	{
		if(g_Timer1_Count == 2)
		{
			/* Wait Until User Enter */
			HAL_DCMotor_Rotate(GPIOA_ID, GPIO_PIN0, DCMOTOR_ROT_STOP);	/* Door Still Open For 3s */
			MCAL_TIMER1_setCompareValue_A(23438);

		}else if(g_Timer1_Count == 3)
		{
			HAL_DCMotor_Rotate(GPIOA_ID, GPIO_PIN0, DCMOTOR_ROT_CCW);	/* Close The Door*/
			MCAL_TIMER1_setCompareValue_A(58594);
		}
	}

	/* Stop Motor */
	HAL_DCMotor_Rotate(GPIOA_ID, GPIO_PIN0, DCMOTOR_ROT_STOP);

	/* Stop Timer */
	MCAL_TIMER1_stop();
	g_Timer1_Count = 0;
}

void CONTROL_ECU_Alarm(void)
{
	TIMER_INIT_OVF();
	HAL_BUZZER_ON();
	MCAL_TIMER1_start();
	while(g_Timer1_Count != 7);

	/* Stop Buzzer */
	HAL_BUZZER_OFF();

	/* Back HMI_ECU To Work */
	MCAL_USART_TX(USART_BACK_TO_WORK);

	/* Stop Timer */
	MCAL_TIMER1_stop();
	g_Timer1_Count = 0;


}

uint8_t CONTROL_ECU_Compare_Password(void)
{
	uint8_t i,eeprom_state;

	/* Receive Password */
	MCAL_USART_TX(USART_CONTROL_ECU_READY); /* Start Reception Password */
	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		password_buffer1[i] = MCAL_USART_RX(); /* Receive Password */
	}

	/* Comparing Passwords */
	for(i = 0; i<PASSWORD_LENGTH; i++)	/* Read Password from EEPROM */
	{
		eeprom_state = MCAL_EEPROM_readByte((EEPROM_PASSWORD_ADDRESS+i), &password_buffer2[i]);
	}

	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		if(password_buffer1[i] != password_buffer2[i])
		{
			return USART_PASSWORD_UNMATCHED;
		}
	}
	return USART_PASSWORD_MATCHED;
}

uint8_t CONTROL_ECU_Create_Password(void)
{
	uint8_t i,eeprom_state;

	/* Receive Passwords */
	MCAL_USART_TX(USART_CONTROL_ECU_READY); /* Start Reception First Password */
	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		password_buffer1[i] = MCAL_USART_RX(); /* Receive Password 1*/
	}

	MCAL_USART_TX(USART_CONTROL_ECU_READY); /* Start Reception Second Password */
	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		password_buffer2[i] = MCAL_USART_RX(); /* Receive Password 2*/
	}

	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		if(password_buffer1[i] != password_buffer2[i])
		{
			return USART_PASSWORD_UNMATCHED;
		}
	}

	/*Saving Password in EEPROM*/
	for(i = 0; i<PASSWORD_LENGTH; i++)
	{
		eeprom_state = MCAL_EEPROM_writeByte((EEPROM_PASSWORD_ADDRESS+i), password_buffer1[i]);
		_delay_ms(10);
		password_buffer2[i] = 0;
	}

	return USART_PASSWORD_MATCHED;
}

void CONTROL_ECU_System_Operation(void)
{
	uint8_t state,password_state;

	while(MCAL_USART_RX() != USART_START_STATE_TRANSISSION);

	state = MCAL_USART_RX();	/* Receive The Operation Selection */

	switch (state) {

	case USART_CREATE_PASS:
		/* Create New Password */
		state = CONTROL_ECU_Create_Password();
		MCAL_USART_TX(state);
		break;

	case USART_ENTERED_PASS:
		/* Compare The Password */
		password_state = CONTROL_ECU_Compare_Password();
		MCAL_USART_TX(password_state);/* Send State To Display */

		if(password_state == USART_PASSWORD_MATCHED)
		{
			g_Wrong_Password_Count = 0;

		}else if(password_state == USART_PASSWORD_UNMATCHED)
		{
			g_Wrong_Password_Count++;
			if(g_Wrong_Password_Count == 3)/* Start Unmatched Passwords Operation */
			{
				CONTROL_ECU_Alarm();
			}
		}
		break;

	case USART_START_DOOR_OPER:
		CONTROL_ECU_Door();
		break;

	default:
		break;
	}
}

/******************************INITIALIZATION SYSTEM FUNCTION*********************************/
void CONTROL_ECU_System_init(void)
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

	/* TWI Configuration */
	TWI_Config_t twi_config;
	twi_config.TWI_DeviceAddress = 1;
	twi_config.TWI_BitRate = 0x02;
	twi_config.TWI_Prescaler = TWI_PRESCALER_1;
	MCAL_TWI_init(&twi_config);		/* TWI Initialization */


	HAL_DCMotor_GPIO_Init(GPIOA_ID,GPIO_PIN0);/* DC-Motor Initialization */


	HAL_BUZZER_GPIO_init();		/* Buzzer Initialization */

}

/****************************************MAIN FUNCTION*********************************/
int main(void)
{
	/* Initialize The CONTROL_ECU */
	CONTROL_ECU_System_init();

	while(1)
	{
		CONTROL_ECU_System_Operation();
	}
}
