#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdio.h>
#include <string.h>
#include "LUT.h"
#include "ansi.h"
#include "vector.h"
#include "ball.h"
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
	printf("%c[?%dl", ESC, 25);

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

	struct player2_t p1, p2;

	struct projectile_t proj[ENTITIES];

	struct powerup powerup1, powerup2;

	struct asteroid asteroid1, asteroid2;



	while(1){

		configureLevel(&p1, &p2, sprite, &proj, &powerup1, &powerup2, &asteroid1, &asteroid2);

		while((p1.lives > 0) && (p2.lives > 0)){

			if (global != 0){

				setLED(0,1,0);

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



				updateProjectiles(&proj);

				//gravity(&p1, asteroid);

				updatePlayer(&p1, readADC(2), readADC(1));

				updatePlayer(&p2, readADC(4), readADC(3));

				powerupUpdate(&powerup1, &p1);

				//powerupUpdate(&powerup2, &p1);

				powerupUpdate(&powerup1, &p2);

				//powerupUpdate(&powerup2, &p2);

				impactDetection(&p1, &proj);

				impactDetection(&p2, &proj);

				/*

				if(collision(p1, asteroid)){

					p1.lives = 0;

				}

				*/

				fflush(stdout);
				global = 0;
			}
		}


		/*	Add endgame screen here;
		 *
		 *
		 *
		 */

		if(p1.lives != 0){

			fgcolor(p1.color);

			titleScreen("player one wins");

			fgcolor(0);

		} else {

			fgcolor(p2.color);

			titleScreen("player two wins");

			fgcolor(0);

		}
	}
}

