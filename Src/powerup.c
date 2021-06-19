/*
 * powerup.c
 *
 *  Created on: 19 Jun 2021
 *      Author: Karl
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "LUT.h"
#include "ansi.h"
#include "math.h"
#include "player.h"

struct powerup{

	int32_t x, y, power, alive;

};

void powerupInit(struct powerup *powerup, int32_t x, int32_t y, int32_t power){

	powerup->x = x;
	powerup->y = y;
	powerup->power = power;
	powerup->alive = 1;

	gotoxy(x,y);

	printf("█");


}

void powerupUpdate(struct powerup *powerup, struct player2_t *player){

	if(((powerup->x + 10) >= approxShift14(player->posX)) && ((powerup->x - 10) <= approxShift14(player->posX)) && ((powerup->y + 10) >= approxShift14(player->posY)) && ((powerup->y - 10) <= approxShift14(player->posY)) && (powerup->alive == 1)){

		player->shotType = 1;

		powerup->alive = 0;

	}

}
