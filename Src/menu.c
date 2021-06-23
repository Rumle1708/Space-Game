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
#include "powerup.h"
#include "thorTing.h"

void printHelp(){
// Prints help screen
	clrscr();
	fgcolor(15);
	// Recommended PuTTY setting
	printf("Putty settings:\n");
	printf("Baudrate: 115200\n");
	printf("Columns: 256\n");
	printf("Rows: 100\n");
	printf("Font size: 3\n");
	fgcolor(0);
}

int32_t gameMenu(){
	// Choose level:
	int32_t state = 0, i = 0, IO = 0;
	while(!(CHECK_BIT(IO,3))){
		if (global >= 12){ // Delay of 0.5 seconds to reduced scroll speed
			i = 0;
			switch (state){
			// Menu is build similar to a state machine
			case 0:
				// Map selection
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("> Asteroid", 0, 1);
				lcd_write_string("  Star Destruction", 0, 2);
				lcd_write_string("  Deep space", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){ // Next state
					state++;
				} else if (CHECK_BIT(i,0)){ // Previous state
					state = 2;
				} else if (CHECK_BIT(i,4)){ // Help state
					state = 3;
					IO ^= 1 << 0; // Foerste bit er taendt for level 1
				}
				break;
			case 1:
				// Map selection
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("  Asteroid", 0, 1);
				lcd_write_string("> Star Destruction", 0, 2);
				lcd_write_string("  Deep space", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){ // Next state
					state++;
				} else if (CHECK_BIT(i,0)){ // Previous state
					state--;
				} else if (CHECK_BIT(i,4)){ // Help state
					state = 3;
					IO ^= 1 << 1; // Anden bit er taendt for level 2
				}
				break;
			case 2:
				// Map selection
				lcd_write_string("Choose level:", 0, 0);
				lcd_write_string("  Asteroid", 0, 1);
				lcd_write_string("  Star Destruction", 0, 2);
				lcd_write_string("> Deep space", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1)){ // Next state
					state = 0;
				} else if (CHECK_BIT(i,0)){ // Previous state
					state--;
				} else if (CHECK_BIT(i,4)){ // Help state
					state = 3;
					IO ^= 1 << 2; // Tredje bit er taendt for level 3
				}
				break;
			case 3:
				// Help state
				lcd_write_string("Do you need help?", 0, 0);
				lcd_write_string("> No", 0, 1);
				lcd_write_string("  Yes", 0, 2);
				lcd_write_string("", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1) || CHECK_BIT(i,0)){  // Next state
					state = 4;
				} else if (CHECK_BIT(i,4)){ // Final state
					state = 6;
				}
				break;
			case 4:
				// Help state
				lcd_write_string("Do you need help?", 0, 0);
				lcd_write_string("  No", 0, 1);
				lcd_write_string("> Yes", 0, 2);
				lcd_write_string("", 0, 3);
				while (i == 0){
					i = readJoystick();
				}
				if (CHECK_BIT(i,1) || CHECK_BIT(i,0)){  // Next state
					state = 3;
				} else if (CHECK_BIT(i,4)){ // Final state
					state = 5;
				}
				break;
			case 5:
				// Help display state
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
				// Clears LCD
				lcd_write_string("", 0, 0);
				lcd_write_string("", 0, 1);
				lcd_write_string("", 0, 2);
				lcd_write_string("", 0, 3);
				clrscr();
				// Draws game window and UI
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

void configureLevel(struct player2_t *p1, struct player2_t *p2, int32_t sprite[5][5], struct projectile_t *proj, struct powerup *pUp1, struct powerup *pUp2, struct asteroid *asteroid1, struct asteroid *asteroid2){
	// Configures map according to choosen map in gameMenu() and initialises all structs according to map
	int32_t i = gameMenu();
	if (CHECK_BIT(i,0)){

		// Asteroid map

		initPlayer(p1, 50, 10, 0, sprite,1);
		initPlayer(p2, 100, 10, 180, sprite,2);

		powerupInit(pUp1, 75, 20, 1);
		powerupInit(pUp2, 150, 75, 2);

		drawAsteroid(asteroid1, 100, 50, 20);
		drawAsteroid(asteroid2, 0, 0, 0);

	} else if (CHECK_BIT(i,1)){

		// Star Destroyer map

		initPlayer(p1, 50, 10, 0, sprite,1);
		initPlayer(p2, 200, 80, 180, sprite,2);

		powerupInit(pUp1, 100, 40, 1);
		powerupInit(pUp2, 100, 80, 2);

		drawAsteroid(asteroid1, 200, 20, 15);
		drawAsteroid(asteroid2, 100, 60, 10);


	} else {

		// Deep Space map

		initPlayer(p1, 50, 10, 0, sprite,1);
		initPlayer(p2, 200, 80, 180, sprite,2);

		powerupInit(pUp1, 100, 50, 1);
		powerupInit(pUp2, 150, 20, 2);

		drawAsteroid(asteroid1, 0, 0, 0);
		drawAsteroid(asteroid2, 0, 0, 0);

	}

	initProjectiles(proj);
}

void initBoss(){
	//  Prints boring text on screen to trick unexpected visits from boss
	global = 0;
	bgcolor(7);
	fgcolor(0);
	clrscr();
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis sollicitudin eleifend diam ultrices semper. Phasellus efficitur id leo sed\n");
	printf("viverra. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Sed eget fringilla tellus. Quisque\n");
	printf("euismod viverra dui ac sagittis. Nullam dictum euismod dui sed luctus. Nulla sodales vulputate vulputate. Curabitur consectetur dapibus\n");
	printf("nunc, consequat malesuada purus rhoncus nec. Aliquam sem felis, congue id diam sed, porttitor tincidunt nunc. Duis ante purus, \n");
	printf("fermentum vitae vulputate ac, tincidunt vitae dui. Morbi tristique tempus purus, a tincidunt tellus lacinia in. Etiam a nisi malesuada, finibus\n");
	printf("ex at, finibus purus. Integer ac nisi vitae ex faucibus euismod. Suspendisse dapibus diam eu pellentesque tempor. In fermentum et lectus \n");
	printf("sit amet gravida.\n");
	printf("\n");
	printf("\n");
	lcd_write_string("Press reset on board", 0, 0);
	lcd_write_string("when boos is no", 0, 1);
	lcd_write_string("longer present.", 0, 2);
	lcd_write_string("", 0, 3);

	bgcolor(0);

	fflush(stdout);
	while (1);
}
