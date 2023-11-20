/*============================================================================================
 * Module : Buzzer
 *
 * File Name : buzzer.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 Buzzer Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"

/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* Configure The Buzzer */

#define BUZZER_PORT				GPIOA_ID
#define BUZZER_PIN				GPIO_PIN0




/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : HAL_BUZZER_GPIO_init.
 * Brief          : Function To Initialize the Buzzer.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																				  */
void HAL_BUZZER_GPIO_init(void);

/**===============================================================================
 * Function Name  : HAL_BUZZER_ON.
 * Brief          : Function To Run the Buzzer.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																				  */
void HAL_BUZZER_ON(void);

/**===============================================================================
 * Function Name  : HAL_BUZZER_OFF.
 * Brief          : Function To Stop the Buzzer.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																				  */
void HAL_BUZZER_OFF(void);

/**===============================================================================
 * Function Name  : HAL_BUZZER_Alarm.
 * Brief          : Function To Run the Buzzer As ALarm.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																				  */
void HAL_BUZZER_Alarm(void);

#endif /* INC_BUZZER_H_ */
