/*============================================================================================
 * Module : PID
 *
 * File Name : pid.c
 *
 * Author: Abdullah Maher
 *
 * Description : Source File of PID Driver
 *
 * Created on: Sep 1, 2023
 =============================================================================================*/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "pid.h"

/*===============================================================================
 *                            		  MACROS	                                 *
 ================================================================================*/



/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/


/*===============================================================================
 *                        Private Function Prototypes	   		                 *
 ================================================================================*/

/*===============================================================================
 *                              API Definitions                                  *
 ================================================================================*/
/**===============================================================================
 * Function Name  : PID_Init().
 * Brief          : Function To Initiate The PID Control.
 * Parameter (in) : Pointer to PID Structure Configuration.
 * Return         : None.
 * Note           : None.                                                                           */
void PID_Init(PID_Controller* PID)
{
	PID->ConstVar.Integrator = 0.0;
	PID->ConstVar.Differentiator = 0.0;
	PID->ConstVar.PrevError = 0.0;
}

/**===============================================================================
 * Function Name  : PID_Update().
 * Brief          : Function To Update The PID Actuate Signal Value.
 * Parameter (in) : Pointer to PID Structure Configuration.
 * Parameter (in) : The Desired Value.
 * Parameter (in) : The Actual Value.
 * Return         : The PID Actuate Signal Value.
 * Note           : None.                                                                           */
float32 PID_Update(PID_Controller* PID, float32 a_DesiredValue, float32 a_ActualValue)
{
	float32 PIDResult, Error;

	/* Error Signal */
	Error = a_DesiredValue - a_ActualValue;

	/* Integral */
	PID->ConstVar.Integrator += Error;

	/* Derivative */
	PID->ConstVar.Differentiator = Error - PID->ConstVar.PrevError;


	PIDResult = (PID->Kp * Error) + (PID->Ki * PID->ConstVar.Integrator * PID->T) + ((PID->Kd * PID->ConstVar.Differentiator)/PID->T);

	if(PIDResult > PID->MaxLimit)
		PIDResult = PID->MaxLimit;

	if(PIDResult < PID->MinLimit)
		PIDResult = PID->MinLimit;


	PID->ConstVar.PrevError = Error;

	return PIDResult;
}
