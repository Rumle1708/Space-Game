/*
 * timer.c
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "ansi.h"
#include "LCD.h"
#include "main.h"

void initTimer(){
	RCC->APB1ENR |= RCC_APB1Periph_TIM2;
	TIM2->CR1 = 0x0000;
	TIM2->ARR = 0x002A; // 42
	TIM2->PSC = 0xFA00; // 64000
	TIM2->CR1 = 0x0001;
	TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
	NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void TIM2_IRQHandler(void) {
	global ^= (1 << 0);
	TIM2->SR &= ~0x0001; // Clear interrupt bit
}

