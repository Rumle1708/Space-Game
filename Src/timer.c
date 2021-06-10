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

void initTimer(){
	// clock = 24 MHz???
	RCC->APB1ENR |= RCC_APB1Periph_TIM2;
	TIM2->CR1 = 0x0000;
	TIM2->ARR = 0x027F; //0x027F
	TIM2->PSC = 0x03E8;
	TIM2->CR1 = 0x0001;
	TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
	NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void updateClock(){
	if (seconds == 60){
		seconds = 0;
		minutes++;
	}
	if (minutes == 60){
		hours++;
	}
	gotoxy(2,2);
	printf("Time since start: %ld:%ld:%ld ", hours, minutes, seconds);
}

void TIM2_IRQHandler(void) {
//Do whatever you want here, but make sure it doesn’t take too much time!

	centiseconds++;
	if (centiseconds == 10){
		centiseconds = 0;
		seconds++;
		// updateClock();
		//printf("o");
	}
	flag = 1;
	updateClock();
	TIM2->SR &= ~0x0001; // Clear interrupt bit
}

void splitTime(){
	gotoxy(2,3);
	printf("Split time 1:     %ld:%ld:%ld", hours, minutes, seconds);
	centiseconds = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
	gotoxy(2,2);
	printf("Time since start: %ld:%ld:%ld ", hours, minutes, seconds);
}

