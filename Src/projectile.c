/*
 * projectile.c
 *
 *  Created on: 15 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "player.h"
#include "math.h"
#include "ansi.h"
#include "projectile.h"


void initProjectiles(struct projectile_t *p){
	for(int32_t i = 0; i < ENTITIES; i++){
		p[i].posX = 0;
		p[i].posY = 0;
		p[i].velX = 0;
		p[i].velY = 0;
		p[i].alive = 0;
		p[i].time = 0;

	}
}

void updateProjectiles(struct projectile_t *p){

	fgcolor(1);

	for (int32_t i = 0; i < ENTITIES; i++){
		if(p[i].alive){
			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));

			printf("%c",0x20);

			p[i].posX += p[i].velX;
			p[i].posY += p[i].velY;

			int32_t x = approxShift14(p[i].posX);
			int32_t y = approxShift14(p[i].posY);

			if(p[i].time > 24 || (x < (X1 + 1)) || (x > (X2 - 1)) || (y < (Y1 + 1)) || (y > (Y2 - 1))){

				p[i].alive = 0;
				p[i].time = 0;

			} else {

				gotoxy(x,y);
				printf("%c", 0xCE);
				p[i].time++;

			}
		}
	}

	fgcolor(0);

}

void spawnProjectile(struct projectile_t *p, struct player2_t *player){

	switch(player->shotType){

	case 0:
		if(player->shotConstant == 4){
			for (int32_t i = 0; i < ENTITIES; i++){
				if(!p[i].alive){

					p[i].posX = player->posX + (cosinus(player->angle)*4);
					p[i].posY = player->posY + (sinus(player->angle)*4);

					p[i].velX = (cosinus(player->angle)*4);
					p[i].velY = (sinus(player->angle)*4);

					p[i].alive = 1;

					i = ENTITIES;
					player->shotConstant = 0;


				}

			}

		}

		break;

	case 1:

		if(player->shotConstant == 10){
			for(int32_t n = 0; n < 5; n++){
				for (int32_t i = 0; i < ENTITIES; i++){
					if(!p[i].alive){

						p[i].posX = player->posX + (cosinus(player->angle + ((n - 2) * 7))*4);
						p[i].posY = player->posY + (sinus(player->angle + ((n - 2) * 7))*4);

						p[i].velX = (cosinus(player->angle + ((n - 2) * 7))*4);
						p[i].velY = (sinus(player->angle + ((n - 2) * 7))*4);

						p[i].alive = 1;

						i = ENTITIES;

					}
				}

			}

			player->shotConstant = 0;

		}

		break;

	case 2:

		if(player->shotConstant >= 2){
			for (int32_t i = 0; i < ENTITIES; i++){
				if(!p[i].alive){

					p[i].posX = player->posX + (cosinus(player->angle)*4);
					p[i].posY = player->posY + (sinus(player->angle)*4);

					p[i].velX = (cosinus(player->angle)*4);
					p[i].velY = (sinus(player->angle)*4);

					p[i].alive = 1;

					i = ENTITIES;

					player->shotConstant = 0;

					}

				}

			}

		break;

	}
}

void impactDetection(struct player2_t *player, struct projectile_t *p){

	for(int32_t i = 0; i < ENTITIES; i++){

		if(((approxShift14(p[i].posX) + 4) >= approxShift14(player->posX)) && ((approxShift14(p[i].posX) - 4) <= approxShift14(player->posX)) && ((approxShift14(p[i].posY) + 4) >= approxShift14(player->posY)) && ((approxShift14(p[i].posY) - 4) <= approxShift14(player->posY)) && p[i].alive){

			player->lives--;

			p[i].alive = 0;

			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));

			printf("%c",0x20);

		}

		if(player->lives <= 0){

			i = ENTITIES;

		}
	}

}


