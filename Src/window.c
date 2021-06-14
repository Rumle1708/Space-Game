/*
 * window.c
 *
 *  Created on: 15 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#define ESC 0x1B
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"

struct window_t{
	uint32_t x1, y1, x2, y2;
};

void initWindow(struct window_t *w, uint32_t xOne, uint32_t yOne, uint32_t xTwo, uint32_t yTwo){
	w->x1 = xOne;
	w->y1 = yOne;
	w->x2 = xTwo;
	w->y2 = yTwo;
}

