#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "LUT.h"
#include "ansi.h"
#include "math.h"

// Struct for player
struct player_t{
	int32_t posX, posY, velX, velY, angle;
};

struct player2_t{
	int32_t posX, posY, velX, velY, angle, shotType, shotConstant, sector, lives;
	int32_t sprite[5][5];
};


void initPlayer(struct player2_t *p, int32_t x, int32_t y, int32_t angle, int32_t sprite[5][5]){
	p->posX = (x << FIX14_SHIFT);
	p->posY = (y << FIX14_SHIFT);
	p->velX = 0;
	p->velY = 0;
	p->angle = angle;
	p->shotType = 0;
	p->shotConstant = 0;
	p->lives = 3;


	for(int32_t i = 0; i < 5; i++){
		for(int32_t j = 0; j < 5; j++){

			p->sprite[i][j] = sprite[i][j];

		}

	}

}


void deletePlayer(struct player2_t *p){

	for(int32_t i = 0; i < 5; i++){

		for(int32_t j = 0; j < 5; j++){

			if(p->sprite[i][j] != 0){
				int32_t sprite_x = approxShift14(((cosinus(p->angle) * ((i - 2) << 14)) >> 14) - ((sinus(p->angle) * ((j - 2) << 14)) >> 14));

				int32_t sprite_y = approxShift14(((sinus(p->angle) * ((i - 2) << 14)) >> 14) + ((cosinus(p->angle) * ((j - 2) << 14)) >> 14));

				gotoxy(sprite_x + approxShift14(p->posX), sprite_y + approxShift14(p->posY));

				printf(" ");


			}
		}
	}
}


int32_t joystickApprox(int32_t deg, int32_t throttle){

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

/*

// Draws player
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

	// Determine direction of player
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

*/

void drawPlayer(struct player2_t *p){

	// roterer sprite figuren i forhold til spillerens orientering


	for(int32_t i = 0; i < 5; i++){

		for(int32_t j = 0; j < 5; j++){

			if(p->sprite[i][j] != 0){

				int32_t sprite_x = approxShift14(((cosinus(p->angle) * ((i - 2) << 14)) >> 14) - ((sinus(p->angle) * ((j - 2) << 14)) >> 14));

				int32_t sprite_y = approxShift14(((sinus(p->angle) * ((i - 2) << 14)) >> 14) + ((cosinus(p->angle) * ((j - 2) << 14)) >> 14));

				gotoxy(sprite_x + approxShift14(p->posX), sprite_y + approxShift14(p->posY));

				printf("*");


			}
		}
	}
}

/*

// Updates the player according to a user input
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

	// Check if player is out of bounds
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

*/

void updatePlayer(struct player2_t *p, int32_t angle, int32_t throttle){

	deletePlayer(p);

	if(!(p->lives <= 0)){

		int32_t temp_angle = ((((angle - 2048) << 14) * (0x0001 << 5)) >> 14);
			int32_t temp_throttle = ((((throttle - 2048) << 14) * (0x0001 << 1)) >> 16);


			// Joystick deadzone

			if((angle - 2048) > 512 || (angle - 2048) < -512 ){

				p->angle += approxShift14(-temp_angle);

			}


			/*

			if (p->angle >= 175){
				p->angle = -180;
			} else {
				p->angle += 5;
			}

			if (p->angle >= 175){
				p->angle = -180;
			} else {
				p->angle += 1;
			}

			*/

			if((throttle - 2048) > 512){

				p->velX += ((temp_throttle * cosinus(p->angle)) >> 14);
				p->velY += ((temp_throttle * sinus(p->angle)) >> 14);


			} else if((throttle - 2048) < -1536){

				// Breaking

				p->velX = FIX14_MULT(p->velX, 0b11100000000000);
				p->velY = FIX14_MULT(p->velY, 0b11100000000000);


			} else {

				p->velX = FIX14_MULT(p->velX, 0b11111010000000);
				p->velY = FIX14_MULT(p->velY, 0b11111010000000);

			}

			/*


			if(approxShift14(p->velX) > 5){

				p->velX = 5;

			} else if (approxShift14(p->velX) < -5){

				p->velX = -5;

			}

			if(approxShift14(p->velY) > 5){

				p->velY = 5;

			} else if (approxShift14(p->velY) < -5){

				p->velY = -5;

			}

			*/

			if((p->shotType == 0) && p->shotConstant < 4){

				p->shotConstant++;

			} else if((p->shotType == 1) && p->shotConstant < 10){

				p->shotConstant++;

			}

			p->posX += p->velX;
			p->posY += p->velY;

			// Check if player is out of bounds
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


			p->sector = (approxShift14(p->posX) / 7) + ((approxShift14(p->posY) / 7) * 35);


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
			printf("\nlives: ");
			printf("%ld    ", p->lives);



	}

}
