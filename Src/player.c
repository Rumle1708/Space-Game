#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "LUT.h"

struct player_t{
	int32_t posX, posY, velX, velY, angle;
};

void initPlayer(struct player_t *p, int32_t x, int32_t y){
	p->posX = (x << FIX14_SHIFT);
	p->posY = (y << FIX14_SHIFT);
	p->velX = 0;
	p->velY = 0;
	p->angle = 0;
}

void updatePlayer(struct player_t *p, int32_t update){

	// Check right turn
	if (CHECK_BIT(update,3)){
		p->angle += 5;
	}

	// Check left turn
	if (CHECK_BIT(update,2)){
		p->angle -= 5;
	}

	// Check forward
	if (CHECK_BIT(update,0)){
		p->velX += cosinus(p->angle) >> 4;
		p->velY += sinus(p->angle) >> 4;
	}

	// Check backwards
	if (CHECK_BIT(update,1)){
		p->velX -= cosinus(p->angle) >> 4;
		p->velY -= sinus(p->angle) >> 4;
	}

	p->posX += p->velX;
	p->posY += p->velY;
	/*
	printf("\nposX: ");
	printFix(expand(p->posX));
	printf("\nposY: ");
	printFix(expand(p->posY));
	printf("\nvelX: ");
	printFix(expand(p->velX));
	printf("\nvelY: ");
	printFix(expand(p->velY));
	printf("\nangle: ");
	printf("%ld", p->angle);
	printf("\n");
	printf("\n");
	printf("\n");
	*/
	drawPlayer(p);
}

void drawPlayer(struct player_t *p){
	gotoxy(approxShift14(p->posX),approxShift14(p->posY));
	printf("o");
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
