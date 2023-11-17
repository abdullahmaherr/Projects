/*============================================================================================
 * Module : 7-Segment
 *
 * File Name : seven_segment.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 7-Segment Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"
#include "std_types.h"

/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/* Configure The 7-segment */	/* NOTE : 7-segment is connected in Common Anode   */
#define SEVEN_SEGMENT_PORT					GPIOC_ID	/* Select The Port Where 7-Segment Connected to */
#define SEVEN_SEGMENT_FIRST_PIN				GPIO_PIN0	/* Select The First Pin Where 7-Segment Connected to */
#define SEVEN_SEGMENT_DECODER_IC			SEVEN_SEGMENT_WITH_DECODER	/* Select The Decoder Connection */
																			/* @ref Decoder Connection */


/* @ref Decoder Connection */
#define SEVEN_SEGMENT_WITHOUT_DECODER			0
#define SEVEN_SEGMENT_WITH_DECODER				1


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : HAL_SEVEN_SEGMENT_GPIO_init.
 * Brief          : Function To Initialize the 7-Segment.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : 7-segment is connected in Common Anode.																				  */
void HAL_SEVEN_SEGMENT_GPIO_init(void);

/**===============================================================================
 * Function Name  : HAL_SEVEN_SEGMENT_dispaly.
 * Brief          : Function To Initialize the 7-Segment.
 * Parameter (in) : The desired number to display from 0 to 9.
 * Return         : None.
 * Note           : None.																				  */
void HAL_SEVEN_SEGMENT_dispaly(uint8_t a_Number);

#endif /* INC_SEVEN_SEGMENT_H_ */
