#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdio.h>
#include <string.h>
#include "ansi.h"
#include "IO.h"
#include "timer.h"
#include "charset.h"
#include "LCD.h"
#include "player.h"
#include "math.h"
#include "main.h"
#include "projectile.h"
#include "ADC2.h"
#include "powerup.h"
#include "thorTing.h"
#include "menu.h"
#include "leaderboard.h"
#include "playerLives.h"

#define X1 1
#define Y1 1
#define X2 255
#define Y2 100
#define ENTITIES 10

#define ESC 0x1B
#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)


#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int main(void){
	// Initialization
	uart_init(2000000);
	uart_clear();
	clrscr();
	// ESC[?25l
	printf("%c[?%dl", ESC, 25); // Removes cursor

	initSwitches();

	initIOJoystick();

	initIOLED();

	lcd_init();

	setLED(0,1,0);

	initTimer();

	initADC();

	int32_t sprite[5][5] = {
	{0,1,0,1,0},
	{1,1,1,1,1},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}
	};

	int32_t p1Wins = 0, p2Wins = 0;

	int32_t leaderboard[100][2] = {0};

	struct player2_t p1, p2;

	struct projectile_t proj[ENTITIES];

	struct powerup powerup1, powerup2;

	struct asteroid asteroid1, asteroid2;

	clrscr();

	while(1){

		int32_t time = 0;

		clrscr();

		fgcolor(1);

		titleScreen("xwing versus");

		fgcolor(0);

		printLeaderboard(p1Wins, p2Wins, leaderboard);

		configureLevel(&p1, &p2, sprite, &proj, &powerup1, &powerup2, &asteroid1, &asteroid2);

		while((p1.lives > 0) && (p2.lives > 0)){

			if (global != 0){

				if(readJoystick() != 0){

					initBoss();

				}

				int32_t switches = readSwitches();

				switch(switches){
				case 0:
					setLED(0,1,0);
					break;
				case 1:
					setLED(1,0,0);
					break;
				case 2:
					setLED(0,0,1);
					break;
				case 3:
					setLED(1,0,1);
					break;
				}



				if (switches == 3 || switches == 1){
					spawnProjectile(&proj,&p1);
				}

				if (switches == 2 || switches == 3){
					spawnProjectile(&proj,&p2);
				}


				for(int32_t i = 0; i < ENTITIES; i++){

					if((collisionProjectile(proj[i], asteroid1) || collisionProjectile(proj[i], asteroid2)) && proj[i].alive){

						proj[i].alive = 0;
						proj[i].time = 0;

					}

				}


				updateProjectiles(&proj);

				if(asteroid1.size != 0){

					gravity(&p1, asteroid1);

					gravity(&p2, asteroid1);

				}

				if(asteroid2.size != 0){

					gravity(&p1, asteroid2);

					gravity(&p2, asteroid2);

				}


				updatePlayer(&p1, readADC(2), readADC(1));

				updatePlayer(&p2, readADC(4), readADC(3));


				powerupUpdate(&powerup1, &p1);

				powerupUpdate(&powerup2, &p1);

				powerupUpdate(&powerup1, &p2);

				powerupUpdate(&powerup2, &p2);



				impactDetection(&p1, &proj);

				impactDetection(&p2, &proj);



				if(asteroid1.size > 0){

					if(collisionPlayer(p1, asteroid1)){

						p1.lives = 0;
					}

					if(collisionPlayer(p2, asteroid1)){

						p2.lives = 0;

					}

				}

				if(asteroid2.size > 0){

					if(collisionPlayer(p1, asteroid2)){

						p1.lives = 0;

					}

					if(collisionPlayer(p2, asteroid2)){

						p2.lives = 0;

					}

				}


				printLives(p1, 0);

				printLives(p2, 1);


				fflush(stdout);

				time += (1 << 14) / 24;

				gotoxy(10,10);

				/*

				fgcolor(15);

				printFix(expand(time));

				fgcolor(0);

				*/

				global = 0;
			}
		}

		if(p1.lives != 0){

			fgcolor(p1.color);

			titleScreen("player one wins");

			fgcolor(0);

			p1Wins++;

			updateLeaderboard3(1, time ,&leaderboard);

		} else {

			fgcolor(p2.color);

			titleScreen("player two wins");

			gotoxy(10,10);

			printFix(expand(time));

			fgcolor(0);

			p2Wins++;

			updateLeaderboard3(2, time ,&leaderboard);

		}

		int32_t timeTemp = global;

		// time delay

		while(global < (timeTemp + 96)){};

	}
}

