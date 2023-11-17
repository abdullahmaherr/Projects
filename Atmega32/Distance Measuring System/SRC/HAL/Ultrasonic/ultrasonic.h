/*============================================================================================
 * Module : Ultrasonic
 *
 * File Name : ultrasonic.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of Ultrasonic Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"


/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/

/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/
/* Select The Trigger Pin */
#define ULTRASONIC_TRIG_PORT		GPIOB_ID
#define ULTRASONIC_TRIG_PIN			GPIO_PIN5


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : HAL_UltraSonic_Init.
 * Brief          : Function To Initialize The Ultrasonic.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void HAL_Ultrasonic_Init(void);

/**===============================================================================
 * Function Name  : HAL_Ultrasonic_ReadDistance.
 * Brief          : Function To Get The Distance.
 * Parameter (in) : None.
 * Return         : The Determined Distance.
 * Note           : None.																	*/
uint16_t HAL_Ultrasonic_ReadDistance(void);


#endif /* INC_ULTRASONIC_H_ */
