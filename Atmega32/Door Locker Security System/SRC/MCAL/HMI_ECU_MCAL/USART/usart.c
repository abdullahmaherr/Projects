/*============================================================================================
 * Module : USART
 *
 * File Name : usart.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 USART Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "usart.h"
#include <avr/interrupt.h>

/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

static void (*gp_CallBack)(void) = NULL_PTR;  /* Global Pointer To Assign ISRs */

USART_Config_t g_USART_Config;
/*===============================================================================
 *                       		 ISR Functions  		                         *
 ================================================================================*/
ISR(USART_RXC_vect)
{
	/* Calling Handler of OVF Mode */
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}

ISR(USART_TXC_vect)
{
	/* Calling Handler of OVF Mode */
	if(gp_CallBack != NULL_PTR)
		(*gp_CallBack)();
}

/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

void MCAL_USART_init(USART_Config_t *p_USART_Config)
{
	g_USART_Config = *p_USART_Config;

	/* Configure Interrupt, TXRX Enabled */
	UCSRB = (1<<RXEN) | (1<<TXEN) | (p_USART_Config->USART_IRQ);

	/* Configure Mode, Parity, Stop, Data Bits */
	UCSRC = (1<<URSEL) | (p_USART_Config->USART_Mode) | (p_USART_Config->USART_ParityBit) | (p_USART_Config->USART_StopBits);

	if((p_USART_Config->USART_DataBits) == USART_DATA_BITS_9)
	{
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRB,UCSZ2);
	}else
	{
		UCSRC|= (p_USART_Config->USART_DataBits);
	}

	/*Set Baud Rate*/
	UBRRL = (p_USART_Config->USART_BaudRate);

	/* Assign ISR with C function */
	if(p_USART_Config->USART_IRQ == USART_RTXC_IRQ_DISABLE)
	{
		CLEAR_BIT(UCSRB,RXCIE);
		CLEAR_BIT(UCSRB,TXCIE);
		gp_CallBack = NULL_PTR;
	}else
	{
		gp_CallBack = (p_USART_Config->p_USART_ISR);
		SEI();
	}
}

void MCAL_USART_deinit(void)
{
	/* Return all registers to default values */
	UCSRA &= (~(0x43));
	UCSRB &= (~(0xFD));
	UCSRC = (0x86);
	UBRRL = 0;
}

void MCAL_USART_TX(uint16_t a_data)
{
	/* Polling Mechanism */
	if(g_USART_Config.USART_IRQ == USART_RTXC_IRQ_DISABLE)
	{
		/* Wait Until The Buffer Is Empty */
		while(BIT_IS_CLEAR(UCSRA,UDRE));
	}

	/* At 9 Data Bits */
	if(BIT_IS_SET(UCSRB,UCSZ2))
	{
		WRI_BIT(UCSRB,TXB8,((a_data & (1<<8))>>8));

	}

	UDR = (uint8_t)a_data;
}


uint16_t MCAL_USART_RX(void)
{
	uint16_t buff = 0;

	/* Polling Mechanism */
	if(g_USART_Config.USART_IRQ == USART_RTXC_IRQ_DISABLE)
	{
		/*Wait Until There Are Unread Data is Received*/
		while(BIT_IS_CLEAR(UCSRA,RXC));
	}

	buff = UDR;

	/* At 9 Data Bits */
	if(BIT_IS_SET(UCSRB,UCSZ2))
	{
		buff|= (GET_BIT(UCSRB,RXB8)<<8);
	}

	return buff;
}


void MCAL_USART_sendString(const uint8_t *p_str)
{
	/*Send The String*/
	while(*p_str != '\0')
	{
		MCAL_USART_TX(*p_str);
		p_str++;
	}
}


void MCAL_USART_receiveString(uint8_t *p_str)
{
	uint8_t i = 0;

	/* Receiving The First Byte */
	p_str[i] = MCAL_USART_RX();

	/* Receiving The Rest Bytes */
	while(p_str[i] != '#')
	{
		i++;
		p_str[i] = MCAL_USART_RX();
	}

	/* After Receiving The String Replace The '#' With '\0' */
	p_str[i] = '\0';
}


void MCAL_USART_sendNumber(uint32_t a_num)
{
	/* Accessing The Number Byte By Byte*/
	uint8_t *p_temp =(uint8_t*)(&a_num);

	MCAL_USART_TX(p_temp[0]);
	MCAL_USART_TX(p_temp[1]);
	MCAL_USART_TX(p_temp[2]);
	MCAL_USART_TX(p_temp[3]);
}


uint32_t MCAL_USART_receiveNumber(void)
{
	uint32_t num;
	/* Accessing The Number Byte By Byte*/
	uint8_t *p_temp = (uint8_t*)(&num);

	/* Receiving Byte By Byte */
	p_temp[0]= MCAL_USART_RX();
	p_temp[1]= MCAL_USART_RX();
	p_temp[2]= MCAL_USART_RX();
	p_temp[3]= MCAL_USART_RX();


	return num;
}
