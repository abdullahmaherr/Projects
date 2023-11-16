/*============================================================================================
 * Module : ATmega32
 *
 * File Name : ATmega32.h
 *
 * Author: Abdullah Maher
 *
 * Description : Header File Of ATmega32
 *
 * Created on: May 1, 2023
 =============================================================================================*/

#ifndef INC_ATMEGA32_H_
#define INC_ATMEGA32_H_


/*===============================================================================
 *                                Includes                                       *
 ===============================================================================*/
#include "avr/io.h"

/*===============================================================================
 *           		   Global Interrupt Enable/Disable Macros 	 	             *
 ================================================================================*/
/*The AVR Instruction To Enable Global Interrupt */
#define SEI()			__asm__ __volatile__("sei" ::)

/*The AVR Instruction To Disable Global Interrupt */
#define CLI()			__asm__ __volatile__("cli" ::)

/*===============================================================================
 *           		    	   	   Generic Macros  		  	                     *
 ================================================================================*/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define NULL_PTR ((void*)0)

/* Set a Specific Bit in any Register*/
#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/* Clear a Specific Bit in any Register*/
#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT)))

/* Toggle a Specific Bit in any Register*/
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))

/* Check if a Specific Bit in any Register is Set*/
#define BIT_IS_SET(REG,BIT) ((REG) & (1<<BIT))

/* Check if a Specific Bit in any Register is Cleared*/
#define BIT_IS_CLEAR(REG,BIT) (!((REG) & (1<<BIT)))

/*Get Specific BIT Value*/
#define GET_BIT(REG,BIT) ((REG & (1<<BIT)) >> BIT)

/* Rotate The Register Right By a specific Numbers Of Rotates*/
#define ROR(REG,NUM) ((REG >> NUM) | (REG << (8-NUM)))

/* Rotate The Register Right By a specific Numbers Of Rotates*/
#define ROL(REG,NUM) ((REG << NUM) | (REG >> (8-NUM)))

/* Write a Specific Value on BIT*/
#define WRI_BIT(REG,BIT,DATA) ((REG) = (REG & (~(1<<BIT))) | (DATA<<BIT))


#endif /* INC_ATMEGA32_H_ */
