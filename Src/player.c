#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"

struct player_t{
	int32_t posX, posY, velX, velY;
};

void initPlayer(struct player_t *p, int32_t x, int32_t y){
	p->posX = (x << FIX14_SHIFT);
	p->posY = (y << FIX14_SHIFT);
	p->velX = 0;
	p->velY = 0;
}

void updatePlayer(struct player_t *p, int32_t x, int32_t y){
	p->velX += x;
	p->velY += y;
	p->posX += p->velX;
	p->posY += p->velY;
}

/*
void printFix(int32_t i) {
	// Prints a signed 16.16 fixed point number
	if ((i & 0x80000000) != 0) { // Handle negative numbers
		printf("-");
		i = ~i + 1;
	}
	printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
	// Print a maximum of 4 decimal digits to avoid overflow
}
*/


void drawPlayer(struct player_t *p){

}
