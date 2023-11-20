/*============================================================================================
 * Module : TWI
 *
 * File Name : twi.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 TWI Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/


#ifndef INC_TWI_H_
#define INC_TWI_H_

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
	uint8_t TWI_BitRate;	/* Specifies The TWI Bit Rate */

	uint8_t TWI_Prescaler;	/* Specifies The TWI Prescaler Regarding to @ref Prescaler */

	uint8_t TWI_DeviceAddress; /* Specifies The TWI Device Address */

}TWI_Config_t;

typedef enum{
	NACK,
	ACK
}TWI_Response;
/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/*
 * SCL Frequency = ((F_CPU) / (16 + (2 * TWI_BitRate * (4 ^ TWI_Prescaler) )))
 * For F_CPU = 8Mhz We Get Bit Rate 400Khz if BitRate = 2 and Prescaler is 1 											*/

/* @ref Prescaler */
#define TWI_PRESCALER_1					(0x00)
#define TWI_PRESCALER_4					(0x01)
#define TWI_PRESCALER_16				(0x02)
#define TWI_PRESCALER_64				(0x03)


/*===============================================================================
 *                      			Macros    				                     *
 ================================================================================*/
/* TWSR reflects the status of the TWI logic and the Two-wire Serial Bus*/

#define TWI_START 					0x08 /* A START condition has been transmitted */
#define TWI_REP_START 				0x10 /* A repeated START condition has been transmitted */
#define TWI_SLA_W_ACK               0x18 /* SLA+W has been transmitted, ACK has been received */
#define TWI_SLA_W_NACK 				0x20 /* SLA+W has been transmitted, NACK has been received */
#define TWI_DATA_TR_ACK 			0x28 /* Data byte has been transmitted, ACK has been received */
#define TWI_DATA_TR_NACK			0x30 /* Data byte has been transmitted, NACK has been received */
#define TWI_ARB_LOST				0x38 /* Arbitration lost */

#define TWI_SLA_R_ACK 				0x40 /* SLA+R has been transmitted, ACK has been received */
#define TWI_SLA_R_NACK 				0x48 /* SLA+R has been transmitted, NACK has been received */
#define TWI_DATA_RE_ACK 			0x50 /* Data byte has been received, ACK has been returned */
#define TWI_DATA_RE_NACK			0x58 /* Data byte has been received, NACK has been returned */


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_TWI_Init.
 * Brief          : Function To Initialize The I2C(TWI) Communication Protocol.
 * Parameter (in) : TWI Configuration.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TWI_init(TWI_Config_t *p_TWI_Config);
/**===============================================================================
 * Function Name  : MCAL_TWI_Start.
 * Brief          : Function To Start The I2C(TWI) Communication.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TWI_start(void);
/**===============================================================================
 * Function Name  : MCAL_TWI_Stop.
 * Brief          : Function To Stop The I2C(TWI) Communication.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TWI_stop(void);
/**===============================================================================
 * Function Name  : MCAL_TWI_WriteByte.
 * Brief          : Function To Transmit Byte.
 * Parameter (in) : The Byte To Be Transmitted.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_TWI_writeByte(uint8_t a_data);
/**===============================================================================
 * Function Name  : MCAL_TWI_ReadByte.
 * Brief          : Function To Receive Byte.
 * Parameter (in) : ACK or NACK.
 * Return         : The Received Byte.
 * Note           : None.																	*/
uint8_t MCAL_TWI_readByte(uint8_t a_ack);
/**===============================================================================
 * Function Name  : MCAL_TWI_GetStatus.
 * Brief          : Function To Get The Status Of The Communication.
 * Parameter (in) : None.
 * Return         : The Status Of Communication .
 * Note           : None.																	*/
uint8_t MCAL_TWI_getStatus(void);

#endif /* INC_TWI_H_ */
