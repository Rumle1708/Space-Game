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
	initPlayer(&p1, 8736, 12);

	int32_t x1 = 30, y1 = 20;
	for (int i = 0; i <= 360; i = i + 1) {
		gotoxy(approxShift14(sinus(i)*x1) + 50, approxShift14(cosinus(i)*y1) + 50);
		printf("%s", "o");
	}
	while(1){
		if (global == 1){

			global = 0;
		}
	}
}

