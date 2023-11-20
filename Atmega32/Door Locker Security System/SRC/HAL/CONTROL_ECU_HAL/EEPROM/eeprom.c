/*============================================================================================
 * Module : External EEPROM
 *
 * File Name : eeprom.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 External EEPROM Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "twi.h"
#include "eeprom.h"


/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/

uint8_t HAL_EEPROM_writeByte(uint16_t a_address,uint8_t a_data)
{
	/* Starting I2C Communication */
	MCAL_TWI_start();
	if(MCAL_TWI_getStatus() != TWI_START)
		return FAILED;

	/* Send The Device Address */
	MCAL_TWI_writeByte((uint8_t)((0xA0) | ((a_address & 0x0700) >> 7))); /* Sending Most Significant 3-Bits of Byte Address with Device address (Writing)*/
	if(MCAL_TWI_getStatus() != TWI_SLA_W_ACK)
		return FAILED;

	/* Send The Required Memory Location Address */
	MCAL_TWI_writeByte((uint8_t)(a_address));
	if(MCAL_TWI_getStatus() != TWI_DATA_TR_ACK)
		return FAILED;

	/* Send Byte To Store It In The EEPROM */
	MCAL_TWI_writeByte(a_data);
	if(MCAL_TWI_getStatus() != TWI_DATA_TR_ACK)
		return FAILED;

	MCAL_TWI_stop();

	return SUCCEDED;
}


uint8_t HAL_EEPROM_readByte(uint16_t a_address,uint8_t *p_buff)
{
	/* Starting TWI Communication */
	MCAL_TWI_start();
	if(MCAL_TWI_getStatus() != TWI_START)
		return FAILED;

	/* Send The Device Address */
	MCAL_TWI_writeByte((uint8_t)((0xA0) | ((a_address & 0x0700) >> 7))); /* Sending Most Significant 3-Bits of Byte Address with Device address (Writing)*/
	if(MCAL_TWI_getStatus() != TWI_SLA_W_ACK)
		return FAILED;

	/* Send The Required Memory Location Address */
	MCAL_TWI_writeByte((uint8_t)(a_address));
	if(MCAL_TWI_getStatus() != TWI_DATA_TR_ACK)
		return FAILED;

	/* Repeat Starting To Read From EEPROM*/
	MCAL_TWI_start();
	if(MCAL_TWI_getStatus() != TWI_REP_START)
		return FAILED;

	/* Send The Device Address */
	MCAL_TWI_writeByte((uint8_t)((0xA0) | ((a_address & 0x0700) >> 7) | 1)); /* Sending Most Significant 3-Bits of Byte Address with Device address (Reading)*/
	if(MCAL_TWI_getStatus() != TWI_SLA_R_ACK)
		return FAILED;

	/* Reading The Byte With NACK*/
	*p_buff = MCAL_TWI_readByte(NACK);
	if(MCAL_TWI_getStatus() != TWI_DATA_RE_NACK)
		return FAILED;

	MCAL_TWI_stop();

	return SUCCEDED;
}

