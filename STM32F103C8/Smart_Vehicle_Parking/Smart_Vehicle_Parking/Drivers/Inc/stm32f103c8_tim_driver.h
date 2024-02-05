/*============================================================================================
 * Module : TIMER
 *
 * File Name : stm32f103c8_tim_driver.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of STM32F103C8 TIMER Driver
 *
 * Created on: Sep 1, 2023
 =============================================================================================*/

#ifndef INC_STM32F103C8_TIM_DRIVER_H_
#define INC_STM32F103C8_TIM_DRIVER_H_

/*===============================================================================
 *                                Includes                                       *
 ================================================================================*/
#include "stm32f103c8.h"

/*===============================================================================
 *                            User Type Definitions                              *
 ================================================================================*/


/*===============================================================================
 *                       Macros Configuration References                         *
 ================================================================================*/

/*===============================================================================
 *           		    	   	   Generic Macros  		  	                     *
 ================================================================================*/


/*	TIMER2	*/
#define TIM2_BASE                       		 0x40000000UL


#define TIM2_CNT                              *(volatile uint32_t *)(TIM2_BASE+0x24)
#define TIM2_CR1                              *(volatile uint32_t *)(TIM2_BASE+0x00)
#define TIM2_PSC                              *(volatile uint32_t *)(TIM2_BASE+0x28)
#define TIM2_SR                               *(volatile uint32_t *)(TIM2_BASE+0x10)
#define TIM2_DIER                             *(volatile uint32_t *)(TIM2_BASE+0x0C)
#define TIM2_ARR                              *(volatile uint32_t *)(TIM2_BASE+0x2C)


#define RCC_APB1ENR                           *(volatile uint32_t *)(RCC_BASE+0x1C)
#define RCC_APB2ENR                           *(volatile uint32_t *)(RCC_BASE+0x18)

/*===============================================================================
 *                                	   APIs 		   		                     *
 ================================================================================*/

void Timer2_init(void);
void Delay_us(uint32_t delay);
void Delay_ms(uint32_t delay);


#endif /* INC_STM32F103C8_TIM_DRIVER_H_ */
