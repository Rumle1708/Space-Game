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


#define X1 1
#define Y1 1
#define X2 245
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
	initIOJoystick();
	initTimer();
	initADC();

	int32_t sprite[5][5] = {
	{0,1,0,1,0},
	{1,1,1,1,1},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}
	};

	struct player2_t p1;

	struct player2_t p2;

	initPlayer(&p1, 50, 10, 0, sprite);

	initPlayer(&p2, 200 , 50, -180, sprite);

	struct projectile_t proj[ENTITIES];

	initProjectiles(&proj);

	struct powerup powerup;

	powerupInit(&powerup, 100, 50, 1);


	/*
	void drawWeirdShit(int32_t r){
		r <<= FIX14_SHIFT;
		int32_t i, x, y;
		for(i = 0; i < 360; i++){
			int32_t x2 = FIX14_MULT(r,cosinus(i));
			int32_t y2 = FIX14_MULT(r,sinus(i));
			x = approxShift14(x2*4);
			y = approxShift14(y2*4);
			gotoxy(2*x + 100,y + 64);
			printf("o");
		}
	}

	void drawCircle(int32_t r, int32_t x, int32_t y){
		int32_t i;
		for(i = 0; i < 360; i++){
			gotoxy(approxShift14(2*r*cosinus(i)) + x,approxShift14(r*sinus(i)) + y);
			printf("snof");
		}
	}
	*/
	while(1){
		if (global == 1){

			/*

			updatePlayer(&p1,joystickApprox(readADC(1),readADC(2)));

			*/

			if (readJoystick() == 16){
				spawnProjectile(&proj,&p1);
			}

			/*

			if (player 2 shot){
				spawnProjectile(&proj,&p2);
			}


			*/

			updateProjectiles(&proj);

			updatePlayer(&p1, readADC(2), readADC(1));

			updatePlayer(&p2, 2048, 2048);

			powerupUpdate(&powerup, &p1);

			//powerupUpdate(&powerup, &p2);

			impactDetection(&p1, &proj);

			impactDetection(&p2, &proj);


			fflush(stdout);
			global = 0;
		}
	}
}

