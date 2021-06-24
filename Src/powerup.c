/*
 * powerup.c
 *
 *  Created on: 19 Jun 2021
 *      Author: Karl
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "ansi.h"
#include "math.h"
#include "player.h"

struct powerup{
	// Struct for powerup
	int32_t x, y, power, alive;
};

void powerupInit(struct powerup *powerup, int32_t x, int32_t y, int32_t power){
	// Initialises a powerup with a position and type
	powerup->x = x;
	powerup->y = y;
	powerup->power = power;
	powerup->alive = 1;

	// Powerup color
	switch(powerup->power){
		case 1:
			fgcolor(11);
			break;
		case 2:
			fgcolor(6);
			break;
	}

	// Draw powerup
	gotoxy(x-1,y);
	printf("#");
	gotoxy(x,y+1);
	printf("#");
	gotoxy(x+1,y);
	printf("#");
	gotoxy(x,y-1);
	printf("#");
	fgcolor(0);
}

void powerupUpdate(struct powerup *powerup, struct player2_t *player){
	// Updates power and checks if player has same position as powerup
	if(((powerup->x + 10) >= approxShift14(player->posX)) && ((powerup->x - 10) <= approxShift14(player->posX)) && ((powerup->y + 10) >= approxShift14(player->posY)) && ((powerup->y - 10) <= approxShift14(player->posY)) && (powerup->alive == 1)){
		player->shotType = powerup->power;	// Changes players shot type
		powerup->alive = 0;	// Removes powerup from map

		// Deletes powerup form map
		gotoxy(powerup->x-1,powerup->y);
		printf(" ");
		gotoxy(powerup->x,powerup->y+1);
		printf(" ");
		gotoxy(powerup->x+1,powerup->y);
		printf(" ");
		gotoxy(powerup->x,powerup->y-1);
		printf(" ");
		fgcolor(0);
	}
}

void checkPowerup(struct powerup *powerup1, struct powerup *powerup2, struct player2_t *player1, struct player2_t *player2){
	// Function to check both powerup on map for both players
	powerupUpdate(powerup1, player1);
	powerupUpdate(powerup2, player1);
	powerupUpdate(powerup1, player2);
	powerupUpdate(powerup2, player2);
}

