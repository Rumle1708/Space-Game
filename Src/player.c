#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "LUT.h"
#include "ansi.h"
#include "math.h"

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
void deletePlayer(struct player_t *p){
	int32_t x, y;
	x = approxShift14(p->posX);
	y = approxShift14(p->posY);
	fgcolor(15);
	gotoxy(x - 1,y);
	printf("   ");
	gotoxy(x,y + 1);
	printf(" ");
	gotoxy(x,y - 1);
	printf(" ");
}

int32_t joystickAprox(int32_t deg, int32_t throttle){


	int32_t out = 0;

	if(throttle > 3000){
		out ^= 1 << 0;
	} else if (throttle < 1000){
		out ^= 1 << 1;
	}

	if(deg > 3000){
		out ^= 1 << 2;
	} else if(deg < 1000){
		out ^= 1 << 3;
	}

	return out;



}

void drawPlayer(struct player_t *p){
	int32_t x, y;
	x = approxShift14(p->posX);
	y = approxShift14(p->posY);
	fgcolor(15);
	gotoxy(x - 1,y);
	printf("%c%c%c", 0xDB, 0xDB, 0xDB);
	gotoxy(x,y + 1);
	printf("%c", 0xDB);
	gotoxy(x,y - 1);
	printf("%c", 0xDB);
	if (-45 < p->angle && p->angle <= 45){
		gotoxy(x - 1,y);
		printf(" ");
	} else if(45 < p->angle && p->angle <= 135){
		gotoxy(x,y - 1);
		printf(" ");
	} else if ((135 < p->angle && p->angle <= 180) || (-135 > p->angle && p->angle >= -180)){
		gotoxy(x + 1,y);
		printf(" ");
	} else {
		gotoxy(x,y + 1);
		printf(" ");
	}
}

void updatePlayer(struct player_t *p, int32_t update){
	deletePlayer(p);



	// Check right turn
	if (CHECK_BIT(update,3)){
		if (p->angle <= -175){
			p->angle = 180;
		} else{
			p->angle -= 5;
		}
	}

	// Check left turn
	if (CHECK_BIT(update,2)){
		if (p->angle >= 175){
			p->angle = -180;
		} else{
			p->angle += 5;
		}
	}

	// Check forward
	if (CHECK_BIT(update,0)){
		p->velX += cosinus(p->angle) >> 4;
		p->velY += sinus(p->angle) >> 5;
	}

	// Check backwards
	if (CHECK_BIT(update,1)){
		p->velX -= cosinus(p->angle) >> 4;
		p->velY -= sinus(p->angle) >> 5;
	}

	if (!CHECK_BIT(update,0) || !CHECK_BIT(update,1) || !CHECK_BIT(update,2) || !CHECK_BIT(update,3)){
		p->velX = FIX14_MULT(p->velX, 0b11111010000000);
		p->velY = FIX14_MULT(p->velY, 0b11111010000000);
	}

	if (CHECK_BIT(update,3)){
			if (p->angle <= -175){
				p->angle = 180;
			} else{
				p->angle -= 1;
			}
	}
		// Check left turn
	if (CHECK_BIT(update,2)){
		if (p->angle >= 175){
			p->angle = -180;
		} else{
			p->angle += 1;
		}
	}

	p->posX += p->velX;
	p->posY += p->velY;

	if ((approxShift14(p->posX) > X2 - 4)){
		p->posX = (X2 - 4) << FIX14_SHIFT;
		p->velX = 0;
	} else if (approxShift14(p->posX) < X1 + 4){
		p->posX = (X1 + 4) << FIX14_SHIFT;
		p->velX = 0;
	} else if (approxShift14(p->posY) > Y2 - 4){
		p->posY = (Y2 - 4) << FIX14_SHIFT;
		p->velY = 0;
	} else if (approxShift14(p->posY) < Y1 + 4){
		p->posY = (Y1 + 4) << FIX14_SHIFT;
		p->velY = 0;
	}
	drawPlayer(p);

	gotoxy(0,0);
	printf("\nposX: ");
	printFix(expand(p->posX));
	printf("\nposY: ");
	printFix(expand(p->posY));
	printf("\nvelX: ");
	printFix(expand(p->velX));
	printf("\nvelY: ");
	printFix(expand(p->velY));
	printf("\nangle: ");
	printf("%ld    ", p->angle);
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
