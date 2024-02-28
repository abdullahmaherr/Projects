/*============================================================================================
 * Module : PID
 *
 * File Name : pid.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File of PID Driver
 *
 * Created on: Sep 1, 2023
 =============================================================================================*/

#ifndef INC_PID_H_
#define INC_PID_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "std_types.h"


/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/
typedef struct
{
	float32 Integrator;
	float32 Differentiator;
	float32 PrevError;

}Controller_ConstMem;

typedef struct
{
	/*	Editable User Variables	*/

	/* Controller Gains */
	float32 Kp;
	float32 Ki;
	float32 Kd;

	/* Sample Time Interval */
	float32 T;

	/* Output Limits */
	float32 MinLimit;
	float32 MaxLimit;


	/*	Non Editable User Variables	*/
	Controller_ConstMem ConstVar;

}PID_Controller;


/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/
/**===============================================================================
 * Function Name  : PID_Init().
 * Brief          : Function To Initiate The PID Control.
 * Parameter (in) : Pointer to PID Structure Configuration.
 * Return         : None.
 * Note           : None.                                                                           */
void PID_Init(PID_Controller* PID);

/**===============================================================================
 * Function Name  : PID_Update().
 * Brief          : Function To Update The PID Actuating Signal Value.
 * Parameter (in) : Pointer to PID Structure Configuration.
 * Parameter (in) : The Desired Value.
 * Parameter (in) : The Actual Value.
 * Return         : The PID Actuating Signal Value.
 * Note           : None.                                                                           */
float32 PID_Update(PID_Controller* PID, float32 a_DesiredValue, float32 a_ActualValue);

#endif /* INC_PID_H_ */
