/*
 * LCD.c
 *
 *  Created on: 12 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "ansi.h"
#include "math.h"
#include "thorTing.h"
#include "player.h"

void initPlayer(struct player2_t *p, int32_t x, int32_t y, int32_t angle, int32_t sprite[5][5], int32_t color){
	// Initialises player struct with values in argument
	p->posX = (x << FIX14_SHIFT);
	p->posY = (y << FIX14_SHIFT);
	p->velX = 0;
	p->velY = 0;
	p->angle = angle;
	p->shotType = 0;
	p->shotConstant = 0;
	p->lives = 3;
	p->color = color;

	// Sets player sprite
	for(int32_t i = 0; i < 5; i++){
		for(int32_t j = 0; j < 5; j++){
			p->sprite[i][j] = sprite[i][j];
		}
	}
}


void deletePlayer(struct player2_t *p){
	// Deletes drawn player according to their position and angle
	for(int32_t i = 0; i < 5; i++){
		for(int32_t j = 0; j < 5; j++){
			if(p->sprite[i][j] != 0){
				// Vector rotation
				int32_t sprite_x = approxShift14(((cosinus(p->angle) * ((i - 2) << 14)) >> 14) - ((sinus(p->angle) * ((j - 2) << 14)) >> 14));

				int32_t sprite_y = approxShift14(((sinus(p->angle) * ((i - 2) << 14)) >> 14) + ((cosinus(p->angle) * ((j - 2) << 14)) >> 14));

				gotoxy(sprite_x + approxShift14(p->posX), sprite_y + approxShift14(p->posY));

				printf("%c",0x20); // Prints blank space
			}
		}
	}
}


void drawPlayer(struct player2_t *p){
	// Draws player according to their position and angle
	fgcolor(p->color); // Sets text color to player color
	for(int32_t i = 0; i < 5; i++){
		for(int32_t j = 0; j < 5; j++){
			if(p->sprite[i][j] != 0){
				// Vector rotation
				int32_t sprite_x = approxShift14(((cosinus(p->angle) * ((i - 2) << 14)) >> 14) - ((sinus(p->angle) * ((j - 2) << 14)) >> 14));

				int32_t sprite_y = approxShift14(((sinus(p->angle) * ((i - 2) << 14)) >> 14) + ((cosinus(p->angle) * ((j - 2) << 14)) >> 14));

				gotoxy(sprite_x + approxShift14(p->posX), sprite_y + approxShift14(p->posY));

				printf("%c", 0xDB); // Prints solid square
			}
		}
	}
	fgcolor(0);
}



void updatePlayer(struct player2_t *p, int32_t angle, int32_t throttle){
	// Updates player structs value according to input from joystick
	deletePlayer(p); // Deletes current player sprite on screen
	if(!(p->lives <= 0)){ // Check if player is alive

		int32_t temp_angle = ((((angle - 2048) << 14) * (0x0001 << 6)) >> 14); // Scale input so game feels smooth and responsive
		int32_t temp_throttle = ((((throttle - 2048) << 14) * (0x0001 << 1)) >> 16); // Scale input so game feels smooth and responsive

		if((angle - 2048) > 512 || (angle - 2048) < -512 ){
			// Joystick deadzone
			p->angle += approxShift14(-temp_angle);
		}

		if((throttle - 2048) > 512){
			// Updates player velocity
			p->velX += ((temp_throttle * cosinus(p->angle)) >> 14);
			p->velY += ((temp_throttle * sinus(p->angle)) >> 14);
		} else if((throttle - 2048) < -1536){
			// Breaks player
			p->velX = FIX14_MULT(p->velX, 0b11100000000000);
			p->velY = FIX14_MULT(p->velY, 0b11100000000000);
		} else {
			// Deaccelerates player slowly
			p->velX = FIX14_MULT(p->velX, 0b11111010000000);
			p->velY = FIX14_MULT(p->velY, 0b11111010000000);
		}

		// Updates players position according to velocity
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

		drawPlayer(p); // Draws a new player sprite

		// Updates players shot constant and shot type
		if((p->shotType == 0) && p->shotConstant < 4){
			p->shotConstant++;
		} else if((p->shotType == 1) && p->shotConstant < 10){
			p->shotConstant++;
		} else if((p->shotType == 2) && p->shotConstant < 2){
				p->shotConstant++;

		}

	} else {
		for(int32_t i = 0; i < 5; i++){
			for(int32_t j = 0; j < 5; j++){
				gotoxy(i-2, j-2);
				printf(" ");
			}
		}
	}
}

void movePlayer(struct player2_t *p1, struct player2_t *p2, struct asteroid asteroid1, struct asteroid asteroid2){
	// Moves player one and two according to gravitational pull from asteroids
	if(asteroid1.size != 0){

		gravity(p1, asteroid1);

		gravity(p2, asteroid1);

		if(collisionPlayer(p1, asteroid1)){

			p1->lives = 0;

		}

		if(collisionPlayer(p2, asteroid1)){

			p2->lives = 0;
		}
	}

	if(asteroid2.size != 0){

		gravity(p1, asteroid2);

		gravity(p2, asteroid2);

		if(collisionPlayer(p1, asteroid2)){

			p1->lives = 0;

		}

		if(collisionPlayer(p2, asteroid2)){

			p2->lives = 0;

		}

	}
	updatePlayer(p1, readADC(2), readADC(1)); // Updates player one
	updatePlayer(p2, readADC(4), readADC(3)); // Updates player two
}
