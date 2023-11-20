/*============================================================================================
 * Module : External EEPROM
 *
 * File Name : eeprom.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 External EEPROM Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"

/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/

typedef enum
{
	FAILED,
	SUCCEDED
}EEPROM_Status;

/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : HAL_EEPROM_WriteByte.
 * Brief          : Function To Write Byte on The External EEPROM.
 * Parameter (in) : Address.
 * Parameter (in) : The Byte To Write It.
 * Return         : Status.
 * Note           : None.																	*/
uint8_t HAL_EEPROM_writeByte(uint16_t a_address,uint8_t a_data);

/**===============================================================================
 * Function Name  : HAL_EEPROM_ReadByte.
 * Brief          : Function To Read Byte From The External EEPROM.
 * Parameter (in) : Address.
 * Parameter (in) : Pointer To Buffer.
 * Return         : Status.
 * Note           : None.																	*/
uint8_t HAL_EEPROM_readByte(uint16_t a_address,uint8_t *p_buff);

#endif /* INC_EEPROM_H_ */
