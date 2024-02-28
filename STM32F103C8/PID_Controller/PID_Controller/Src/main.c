/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdullah Maher
 * @brief          : Main program body
 *******************************************************************************/

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/

#include "stm32f103c8.h"
#include "stm32f103c8_rcc_driver.h"
#include "stm32f103c8_exti_driver.h"
#include "stm32f103c8_gpio_driver.h"
#include "stm32f103c8_timer_driver.h"
#include "pid.h"

/*===============================================================================
 *                            		  MACROS	                                 *
 ================================================================================*/

#define PRESCALER 8000
#define MAX_SPEED 1000


/*===============================================================================
 *                              Global Variables                                 *
 ================================================================================*/
vsint32_t PID_Res = 0;
vsint32_t Position = 0;


/*===============================================================================
 *                                	   ISR 		   		               	 	     *
 ================================================================================*/
void EncoderISR(void)
{
	sint32_t b = MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN5);

	if(b > 0)
		Position--;
	else
		Position++;
}

/*===============================================================================
 *                                Application 		   		                     *
 ================================================================================*/
int main(void)
{
	MCAL_RCC_initSYSClk();

	EXTI_PinConfig_t exti_cfg;
	exti_cfg.EXTIx_Pin = EXTI4PA4;
	exti_cfg.EXTI_TriggerCase = EXTI_RISING_TRIG;
	exti_cfg.EXTI_IRQ = EXTI_IRQ_ENABLE;
	exti_cfg.p_EXTI_ISR_CallBack = EncoderISR;
	MCAL_EXTI_GPIO_Init(&exti_cfg);

	GPIO_PinConfig_t gpio_cfg;
	gpio_cfg.GPIO_PinNumber = GPIO_PIN5;
	gpio_cfg.GPIO_Mode = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(GPIOA, &gpio_cfg);

	PID_Controller pid;
	pid.Kp = 60.0;
	pid.Ki = 0.01;
	pid.Kd = 10.0;
	pid.T = 1;
	pid.MaxLimit = MAX_SPEED;
	pid.MinLimit = -MAX_SPEED;
	PID_Init(&pid);



    /* Loop forever */
	while(1)
	{
		PID_Res = PID_Update(&pid, 200, Position);
		if(PID_Res > 0)
		{
			MCAL_Tim_PWM(TIM1, CHANNEL3, 0, MAX_SPEED, PRESCALER);
			MCAL_Tim_PWM(TIM1, CHANNEL1, PID_Res, MAX_SPEED, PRESCALER);

		}else if(PID_Res < 0)
		{
			MCAL_Tim_PWM(TIM1, CHANNEL3, -PID_Res, MAX_SPEED, PRESCALER);
			MCAL_Tim_PWM(TIM1, CHANNEL1, 0, MAX_SPEED, PRESCALER);

		}else
		{
			MCAL_Tim_PWM(TIM1, CHANNEL3, 0, MAX_SPEED, PRESCALER);
			MCAL_Tim_PWM(TIM1, CHANNEL1, 0, MAX_SPEED, PRESCALER);
		}
	}
}
