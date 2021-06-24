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
#include "thorTing.h"
#include "projectile.h"

void initProjectiles(struct projectile_t *p){
	// Initialises array of projectiles to a value different from NULL
	for(int32_t i = 0; i < ENTITIES; i++){
		p[i].posX = 0;
		p[i].posY = 0;
		p[i].velX = 0;
		p[i].velY = 0;
		p[i].alive = 0;
		p[i].time = 0;
	}
}

void updateProjectiles(struct projectile_t *p, struct asteroid asteroid1, struct asteroid asteroid2){
	// Updates alive projectiles
	fgcolor(11);
	for (int32_t i = 0; i < ENTITIES; i++){ // Runs through all projectiles
		if(p[i].alive){ // Check if alive
			// Deletes previous projectile position
			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));
			printf("%c",0x20);

			// Updates projectile position
			p[i].posX += p[i].velX;
			p[i].posY += p[i].velY;

			// Approximates position once to save computer power
			int32_t x = approxShift14(p[i].posX);
			int32_t y = approxShift14(p[i].posY);

			if(p[i].time > 24 || (x < (X1 + 1)) || (x > (X2 - 1)) || (y < (Y1 + 1)) || (y > (Y2 - 1)) || collisionProjectile(&p[i],asteroid1) || collisionProjectile(&p[i],asteroid2)){
				// Check if projectile should be alive by time alive and position
				p[i].alive = 0;
				p[i].time = 0;
			} else {
				// Prints projectile if alive
				gotoxy(x,y);
				printf("%c", 0xCE);
				p[i].time++; // Increments the projectiles time alive
			}
		} else {
			// Deletes projectile if not alive
			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));
			printf("%c",0x20);
		}
	}
	fgcolor(0);
}

void spawnProjectile(struct projectile_t *p, struct player2_t *player){
	// Spawns a new projectile for a player
	switch(player->shotType){
	// Switch statement for the type of shot / powerup of player
	case 0: // Default shot type
		if(player->shotConstant == 4){ // Checks if player has a bullet ready
			for (int32_t i = 0; i < ENTITIES; i++){
				if(!p[i].alive){ // Checks if there is an available entity
					// Set projectile x and y velocity and position according to player angle and position
					p[i].posX = player->posX + (cosinus(player->angle)*4);
					p[i].posY = player->posY + (sinus(player->angle)*4);
					p[i].velX = (cosinus(player->angle)*4);
					p[i].velY = (sinus(player->angle)*4);
					p[i].alive = 1; // Sets projectile status
					i = ENTITIES; // Breaks for loop
					player->shotConstant = 0; // Sets player to reload
				}
			}
		}
		break;
	case 1: // Shotgun shot type
		if(player->shotConstant == 10){ // Checks if player has a bullet ready
			for(int32_t n = 0; n < 5; n++){ // Spawns five different projectiles
				for (int32_t i = 0; i < ENTITIES; i++){
					if(!p[i].alive){ // Checks if there is an available entity
						// Set projectile x and y velocity and position according to player angle and position
						// Projectile angle is determined by n
						p[i].posX = player->posX + (cosinus(player->angle + ((n - 2) * 7))*4);
						p[i].posY = player->posY + (sinus(player->angle + ((n - 2) * 7))*4);
						p[i].velX = (cosinus(player->angle + ((n - 2) * 7))*4);
						p[i].velY = (sinus(player->angle + ((n - 2) * 7))*4);
						p[i].alive = 1; // Sets projectile status
						i = ENTITIES; // Breaks for loop
					}
				}
			}
			player->shotConstant = 0; // Sets player to reload
		}
		break;
	case 2: // Chain gun shot type
		if(player->shotConstant >= 2){ // Checks if player has a bullet ready
			for (int32_t i = 0; i < ENTITIES; i++){
				if(!p[i].alive){ // Checks if there is an available entity
					// Set projectile x and y velocity and position according to player angle and position
					p[i].posX = player->posX + (cosinus(player->angle)*4);
					p[i].posY = player->posY + (sinus(player->angle)*4);
					p[i].velX = (cosinus(player->angle)*4);
					p[i].velY = (sinus(player->angle)*4);
					p[i].alive = 1; // Sets projectile status
					i = ENTITIES; // Breaks for loop
					player->shotConstant = 0; // Sets player to reload
					}
				}
			}
		break;
	}
}

void impactDetection(struct player2_t *player, struct projectile_t *p){
	// Function to check if player has impacted with a projectile
	for(int32_t i = 0; i < ENTITIES; i++){
		// Check for all projectiles
		if(((approxShift14(p[i].posX) + 4) >= approxShift14(player->posX)) && ((approxShift14(p[i].posX) - 4) <= approxShift14(player->posX)) && ((approxShift14(p[i].posY) + 4) >= approxShift14(player->posY)) && ((approxShift14(p[i].posY) - 4) <= approxShift14(player->posY)) && p[i].alive){
			// Check if projectile is alive and positions are similar
			player->lives--; // Updates player lives
			p[i].alive = 0; // Updates projectile status

			// Deletes projectile
			gotoxy(approxShift14(p[i].posX),approxShift14(p[i].posY));
			printf("%c",0x20);
		}
		if(player->lives <= 0){
			// Stops for loop if player is dead
			i = ENTITIES;
		}
	}
}


