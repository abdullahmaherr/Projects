/*============================================================================================
 * Module : ICU
 *
 * File Name : icu.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32 ICU Driver
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_ICU_H_
#define INC_ICU_H_


/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "atmega32.h"


/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/

typedef enum{
	NO_CLOCK,
	FCPU_CLOCK,
	FCPU_8,
	FCPU_64,
	FCPU_256,
	FCPU_1024
}ICU_Clock_t;

typedef enum{
	FALLING,
	RAISING
}ICU_Edge_t;

typedef struct{
	ICU_Clock_t ICU_Clock;

	ICU_Edge_t ICU_Edge;
}ICU_Config_t;


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/



/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

/**===============================================================================
 * Function Name  : MCAL_ICU_Init.
 * Brief          : Function To Initialize The ICU Mode In Timer1.
 * Parameter (in) : ICU Configuration.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_ICU_Init(const ICU_Config_t *p_ICU_Config);

/**===============================================================================
 * Function Name  : MCAL_ICU_Deinit.
 * Brief          : Function To Deinitialize The ICU Mode In Timer1.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_ICU_Deinit(void);
/**===============================================================================
 * Function Name  : MCAL_ICU_SetCallBack.
 * Brief          : Function To Set The ISR With CallBack Function.
 * Parameter (in) : Handler Function Address.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_ICU_SetCallBack(void(*a_ISR)(void));

/**===============================================================================
 * Function Name  : MCAL_ICU_SetEdgeDetect.
 * Brief          : Function To Set The Required Edge Detection.
 * Parameter (in) : ICU Edge Level Type.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_ICU_SetEdgeDetect(const ICU_Edge_t a_Edge);

/**===============================================================================
 * Function Name  : MCAL_ICU_GetICUValue.
 * Brief          : Function To Get The ICR Value.
 * Parameter (in) : None.
 * Return         : ICR Register Value.
 * Note           : None.																	*/
uint16_t MCAL_ICU_GetICUValue(void);

/**===============================================================================
 * Function Name  : MCAL_ICU_ClearCounter.
 * Brief          : Function To Clear The Timer Counter.
 * Parameter (in) : None.
 * Return         : None.
 * Note           : None.																	*/
void MCAL_ICU_ClearCounter(void);

#endif /* INC_ICU_H_ */
