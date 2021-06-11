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


int main(void){
	// Initialization
	uart_init(115200);
	clrscr();
	global = 0;

	initADC();
	initIOJoystick();
	lcd_init();
	initTimer();
	// drawWindowNoTitle(1,1,255,127,1);
	struct player_t p1;
	initPlayer(&p1, 8736, 12);
	/*

	printFix(expand(p1.posX));
	printf("\n");


	printFix(expand(p1.posY));

	*/

	printf("%ld", approxShift14(p1.posX + 0x00002000));
	while(1){
		if (global == 1){

			global = 0;
		}

	}
}

