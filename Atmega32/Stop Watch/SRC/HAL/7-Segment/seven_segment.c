/*============================================================================================
 * Module : 7-Segment
 *
 * File Name : seven_segment.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File Of ATmega32 7-Segment Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "seven_segment.h"
#include "gpio.h"

/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/

/*===============================================================================
 *                            		  MACROS	                                 *
 ================================================================================*/
#if(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITH_DECODER)

#define INSERTION(x)	((x == GPIOA_ID)? PORTA : (x == GPIOB_ID)? PORTB : (x == GPIOC_ID)? PORTC : (x == GPIOC_ID)? PORTD : 0)

#endif
/*===============================================================================
 *                      Prototype of Private Function                            *
 ================================================================================*/

#if(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITHOUT_DECODER)
/**===============================================================================
 * Function Name  : DisplayNumber.
 * Brief          : Function To Make Delay.
 * Parameter (in) : The Desired Number.
 * Return         : Number to Display.
 * Note           : None																				*/
static uint8_t DisplayNumber(uint8_t number);
#endif

/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/
void HAL_SEVEN_SEGMENT_GPIO_init(void)
{

#if(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITHOUT_DECODER)

	/* initialize The Pins as Output */
	MCAL_GPIO_PortInit(SEVEN_SEGMENT_PORT, GPIO_PORT_OUTPUT);

	/* Turn The 7-segment off at First */
	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT, GPIO_SET_PORT);

#elif(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITH_DECODER)

	/* initialize The Pins as Output */
	MCAL_GPIO_PinInit(SEVEN_SEGMENT_PORT, SEVEN_SEGMENT_FIRST_PIN, GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+1), GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+2), GPIO_PIN_OUTPUT);
	MCAL_GPIO_PinInit(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+3), GPIO_PIN_OUTPUT);

	/* Turn The 7-segment off at First */
	MCAL_GPIO_WritePin(SEVEN_SEGMENT_PORT, SEVEN_SEGMENT_FIRST_PIN, GPIO_SET_PIN);
	MCAL_GPIO_WritePin(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+1), GPIO_SET_PIN);
	MCAL_GPIO_WritePin(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+2), GPIO_SET_PIN);
	MCAL_GPIO_WritePin(SEVEN_SEGMENT_PORT, (SEVEN_SEGMENT_FIRST_PIN+3), GPIO_SET_PIN);

#endif

}

void HAL_SEVEN_SEGMENT_dispaly(uint8_t a_Number)
{

#if(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITHOUT_DECODER)

	/* Get Number Value To Display */
	uint8_t number = DisplayNumber(a_Number);

	/* Display on 7-segment */
	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT,number);

#elif(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITH_DECODER)

	/* Display on 7-segment */
	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT, ((INSERTION(SEVEN_SEGMENT_PORT) & (~(0x0F<<SEVEN_SEGMENT_FIRST_PIN))) | ((a_Number<<SEVEN_SEGMENT_FIRST_PIN) & (0x0F<<SEVEN_SEGMENT_FIRST_PIN))));

#endif
}

#if(SEVEN_SEGMENT_DECODER_IC == SEVEN_SEGMENT_WITHOUT_DECODER)

static uint8_t DisplayNumber(uint8_t number)
{
	switch(number)
	{
	case 0:
		return 0x7E;
		break;
	case 1:
		return 0x0C;
		break;
	case 2:
		return 0xB6;
		break;
	case 3:
		return 0x9E;
		break;
	case 4:
		return 0xCC;
		break;
	case 5:
		return 0xDA;
		break;
	case 6:
		return 0xFA;
		break;
	case 7:
		return 0x0E;
		break;
	case 8:
		return 0xFE;
		break;
	case 9:
		return 0xCE;
		break;
	default:
		return 0;
	}
}

#endif
