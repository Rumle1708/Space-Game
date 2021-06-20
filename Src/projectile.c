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
#include "LUT.h"
#include "math.h"
#include "ansi.h"
#include "projectile.h"

/*
struct projectile_t{
	int32_t posX, posY, velX, velY, alive;
};
*/

void initProjectiles(struct projectile_t *p){
	for(int32_t i = 0; i < ENTITIES; i++){
		p[i].posX = 0;
		p[i].posY = 0;
		p[i].velX = 0;
		p[i].velY = 0;
		p[i].alive = 0;
		p[i].time = 0;
		p[i].sector = 0;

	}
}

void updateProjectiles(struct projectile_t *p){
	for (int32_t i = 0; i < ENTITIES; i++){
		if(p[i].alive){
			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));
			printf(" ");
			p[i].posX += p[i].velX;
			p[i].posY += p[i].velY;

			p[i].sector = (approxShift14(p->posX) / 7) + ((approxShift14(p->posY) / 7) * 35);

			int32_t x = approxShift14(p[i].posX);
			int32_t y = approxShift14(p[i].posY);
			gotoxy(x,y);
			printf("*");
			p[i].time++;
			if(p[i].time > 24 || (x < X1) || (x > X2) || (y < Y1) || (y > Y2)){
				p[i].alive = 0;
				p[i].time = 0;
				gotoxy(x,y);
				printf(" ");
			}
		}
	}
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

						p[i].posX = player->posX + (cosinus(player->angle + ((n - 2) * 15))*4);
						p[i].posY = player->posY + (sinus(player->angle + ((n - 2) * 15))*4);

						p[i].velX = (cosinus(player->angle + ((n - 2) * 15))*4);
						p[i].velY = (sinus(player->angle + ((n - 2) * 15))*4);

						p[i].alive = 1;

						i = ENTITIES;

					}
				}

			}

			player->shotConstant = 0;

		}

		break;

	}
}

void impactDetection(struct player2_t *player, struct projectile_t *p){

	for(int32_t i = 0; i < ENTITIES; i++){



		if((player->sector == p[i].sector) && (p[i].alive)){

			if(((approxShift14(p[i].posX) + 3) >= approxShift14(player->posX)) && ((approxShift14(p[i].posX) -3) <= approxShift14(player->posX)) && ((approxShift14(p[i].posY) + 3) >= approxShift14(player->posY)) && ((approxShift14(p[i].posY) + -3) <= approxShift14(player->posY))){

				player->lives--;

				p[i].alive = 0;

			}

			if(player->lives <= 0){

				i = ENTITIES;

			}
		}



		/*

		if(((approxShift14(p[i].posX) + 3) >= approxShift14(player->posX)) && ((approxShift14(p[i].posX) -3) <= approxShift14(player->posX)) && ((approxShift14(p[i].posY) + 3) >= approxShift14(player->posY)) && ((approxShift14(p[i].posY) + -3) <= approxShift14(player->posY))){

			player->lives--;

			p[i].alive = 0;

		}

		if(player->lives <= 0){

			i = ENTITIES;

		}

		*/

	}

}


