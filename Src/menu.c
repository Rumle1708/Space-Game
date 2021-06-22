/*
 * menu.c
 *
 *  Created on: 21 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"
#include "LCD.h"
#include "IO.h"
#include "ansi.h"
#include "player.h"
#include "projectile.h"

void printHelp(){
	printf("Putty settings:\n");
	printf("Baudrate: 115200\n");
	printf("Columns: 256\n");
	printf("Rows: 100\n");
	printf("Font size: 3\n");
	printf("\n");
	printf("\n");
	printf("System requirements:\n");
	printf(" \n");
}

int32_t gameMenu(){
	// Choose level:
	int32_t state = 0, i = 0, IO = 0;
	while(!(CHECK_BIT(IO,3))){
		if (global >= 12){
			i = 0;
			switch (state){
			case 0:
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("> Asteroids", 0, 1);
				lcd_write_string("  Star Destruction", 0, 2);
				lcd_write_string("  Black Hole", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){
					state++;
				} else if (CHECK_BIT(i,0)){
					state = 2;
				} else if (CHECK_BIT(i,4)){
					state = 3;
					IO ^= 1 << 0; // Foerste bit er taendt for level 1
				}
				break;
			case 1:
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("  Asteroids", 0, 1);
				lcd_write_string("> Star Destruction", 0, 2);
				lcd_write_string("  Black Hole", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){
					state++;
				} else if (CHECK_BIT(i,0)){
					state--;
				} else if (CHECK_BIT(i,4)){
					state = 3;
					IO ^= 1 << 1; // Anden bit er taendt for level 2
				}
				break;
			case 2:
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("  Asteroids", 0, 1);
				lcd_write_string("  Star Destruction", 0, 2);
				lcd_write_string("> Black Hole", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){
					state = 0;
				} else if (CHECK_BIT(i,0)){
					state--;
				} else if (CHECK_BIT(i,4)){
					state = 3;
					IO ^= 1 << 2; // Tredje bit er taendt for level 3
				}
				break;
			case 3:
				lcd_write_string("Do you need help?", 0, 0);
				lcd_write_string("> No", 0, 1);
				lcd_write_string("  Yes", 0, 2);
				lcd_write_string("", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1) || CHECK_BIT(i,0)){
					state = 4;
				} else if (CHECK_BIT(i,4)){
					state = 6;
				}
				break;
			case 4:
				lcd_write_string("Do you need help?", 0, 0);
				lcd_write_string("  No", 0, 1);
				lcd_write_string("> Yes", 0, 2);
				lcd_write_string("", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1) || CHECK_BIT(i,0)){
					state = 3;
				} else if (CHECK_BIT(i,4)){
					state = 5;
				}
				break;
			case 5:
				lcd_write_string("Help is displayed", 0, 0);
				lcd_write_string("on terminal.", 0, 1);
				lcd_write_string("Press any key", 0, 2);
				lcd_write_string("to continue!", 0, 3);
				printHelp();
				while (i == 0){
					i = readJoystick();
				}
				state = 6;
				break;
			case 6:
				lcd_write_string("", 0, 0);
				lcd_write_string("", 0, 1);
				lcd_write_string("", 0, 2);
				lcd_write_string("", 0, 3);
				clrscr();
				drawGameTitle(X2,Y2);
				drawWindowNoTitle(X1,Y1,X2,Y2,1);
				IO ^= 1 << 3;
				break;
			}

			global = 0;
		}
	}

	return IO;
}

void configureLevel(struct player2_t *p1, struct player2_t *p2, int32_t sprite[5][5], struct projectile_t *proj, struct powerup *pUp){
	int32_t i = gameMenu();
	if (CHECK_BIT(i,0)){
		initPlayer(p1, 50, 10, 0, sprite,1);
		initPlayer(p2, 100, 10, 180, sprite,2);
		powerupInit(pUp, 100, 50, 1);
	} else if (CHECK_BIT(i,1)){
		initPlayer(p1, 10, 10, 0, sprite,1);
		initPlayer(p2, 250, 80, 180, sprite,2);
		powerupInit(pUp, 100, 50, 1);
	} else {
		initPlayer(p1, 50, 10, 0, sprite,1);
		initPlayer(p2, 100, 10, 180, sprite,2);
		powerupInit(pUp, 100, 50, 1);
	}

	initProjectiles(proj);
}
