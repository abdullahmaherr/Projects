/*============================================================================================
 * Module : USART
 *
 * File Name : usart.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 USART Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_USART_H_
#define INC_USART_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"


/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/

typedef struct
{
	uint8_t USART_Mode;			/* Specifies The USART Mode (Sync,Async) Regarding to @ref USART Mode*/

	uint8_t USART_BaudRate;		/* Specifies The USART BaudRate Regarding to @ref BaudRate Mode*/

	uint8_t USART_DataBits;		/* Specifies The USART DataBits Regarding to @ref DataBits Mode*/

	uint8_t USART_StopBits;		/* Specifies The USART StopBits Regarding to @ref StopBits Mode*/

	uint8_t USART_ParityBit;	/* Specifies The USART ParityBit Regarding to @ref ParityBit Mode*/

	uint8_t USART_IRQ;	/* Specifies The USART Interrupt Mask Regarding to  @ref USART Interrupt Enable/Disable */

	void(*p_USART_ISR)(void);	/* SET The Call Back Function That Will Be Called In ISR */

}USART_Config_t;


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* Sent By The Receiver To Inform The Transmitter To Start */
#define RX_READY 0x10

/* @ref USART Mode */
#define USART_ASYNC_MODE		(0x00U)
#define USART_SYNC_MODE			(0x40U)

/* @ref BaudRate Mode */
/* Note: F_CPU = 8Mhz, U2X = 0 */
#define USART_BAUD_RATE_2400				207
#define USART_BAUDE_RATE_4800				103
#define USART_BAUDE_RATE_9600				51
#define USART_BAUDE_RATE_14400				34
#define USART_BAUDE_RATE_19200				25
#define USART_BAUDE_RATE_28800				16
#define USART_BAUDE_RATE_38400				12
#define USART_BAUDE_RATE_57600				8
#define USART_BAUDE_RATE_76800				6
#define USART_BAUDE_RATE_1152000			3
#define USART_BAUDE_RATE_230400				1
#define USART_BAUDE_RATE_250000				1
#define USART_BAUDE_RATE_500000				0

/*@ref DataBits Mode*/
#define USART_DATA_BITS_5					(0x00U)
#define USART_DATA_BITS_6					(0x02U)
#define USART_DATA_BITS_7					(0x04U)
#define USART_DATA_BITS_8					(0x06U)
#define USART_DATA_BITS_9					(0x09U)

/*@ref ParityBit Mode*/
#define USART_PARITY_BIT_NONE				(0x00U)
#define USART_PARITY_BIT_EVEN				(0x20U)
#define USART_PARITY_BIT_ODD				(0x30U)

/*@ref StopBits Mode*/
#define USART_STOP_BIT_1					(0x00U)
#define USART_STOP_BIT_2					(0x08U)

/* @ref USART Interrupt Enable/Disable */
#define USART_RTXC_IRQ_DISABLE				(0x00)/* Polling Mechanism Enabled */
#define USART_RXC_IRQ_ENABLE				(0x80)
#define USART_TXC_IRQ_ENABLE				(0x40)
#define USART_RTXC_IRQ_ENABLE				(0xC0)


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_USART_Init.
 * Brief          : Function To Initialize The UART.
 * Parameter (in) : Pin Configuration.
 * Return         : None.
 * Note           : Asynchronous TX at Raising RX at Failing
  	  	  	  	    The Recommended Baud Rate 9600 															*/
void MCAL_USART_init(USART_Config_t *p_USART_Config);

/**===============================================================================
 * Function Name  : MCAL_USART_Deinit.
 * Brief          : Function To Uninitialize The UART.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																 */
void MCAL_USART_deinit(void);

/**===============================================================================
 * Function Name  : MCAL_USART_TX.
 * Brief          : Function To Transmit The Data .
 * Parameter (in) : Data to Transmit it.
 * Return         : None.
 * Note           : None.																		*/
void MCAL_USART_TX(uint16_t a_data);

/**===============================================================================
 * Function Name  : MCAL_USART_RX.
 * Brief          : Function To Receive The UART.
 * Parameter (in) : None.
 * Return         : The Received Data.
 * Note           : None.																			*/
uint16_t MCAL_USART_RX(void);

/**===============================================================================
 * Function Name  : MCAL_USART_sendString.
 * Brief          : Function To Send String By Using The UART.
 * Parameter (in) : The String To Send It.
 * Return         : None.
 * Note           : Add '#' At The End Of Your String To Inform The Receiver The End Of Your String	*/
void MCAL_USART_sendString(const uint8_t *p_str);

/**===============================================================================
 * Function Name  : MCAL_USART_receiveString.
 * Brief          : Function To Receive String By Using The UART.
 * Parameter (in) : The Pointer To String buffer.
 * Return         : None.
 * Note           : Receiving String With '#' At The End OF The String.								*/
void MCAL_USART_receiveString(uint8_t *p_str);

/**===============================================================================
 * Function Name  : MCAL_USART_sendNumber.
 * Brief          : Function To Send Number By Using The UART.
 * Parameter (in) : The Number To Send It.
 * Return         : None.
 * Note           : None																	*/
void MCAL_USART_sendNumber(uint32_t a_num);

/**===============================================================================
 * Function Name  : MCAL_USART_receiveNumber.
 * Brief          : Function To Receive Number By Using The UART.
 * Parameter (in) : None.
 * Return         : The Received Number.
 * Note           : None.																	*/
uint32_t MCAL_USART_receiveNumber(void);


#endif /* INC_USART_H_ */
