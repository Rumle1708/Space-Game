#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
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
#include "main.h"
#include "ADC.h"
#include "player.h"
#include "math.h"

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int main(void){
	// Initialization
	uart_init(115200);
	clrscr();

	initADC();
	initIOJoystick();
	lcd_init();
	initTimer();
	// drawWindowNoTitle(1,1,255,127,1);
	struct player_t p1;
	initPlayer(&p1, 50, 10);

<<<<<<< HEAD
	int32_t x1 = 30, y1 = 20;
	for (int i = 0; i <= 360; i = i + 1) {
		gotoxy(approxShift14(sinus(i)*x1) + 50, approxShift14(cosinus(i)*y1) + 50);
		printf("%s", "o");
	}
=======
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

>>>>>>> branch 'master' of https://github.com/Rumle1708/Game.git
	while(1){
		if (global == 1){
			updatePlayer(&p1, readJoystick());
			global = 0;
		}
	}
}

