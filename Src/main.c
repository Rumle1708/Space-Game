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

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

#define FIX16_SHIFT 16
#define FIX16_MULT(a,b) (((a)*(b)) >> FIX16_SHIFT)
#define FIX16_DIV(a,b) (((a)<<FIX16_SHIFT)/b)

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
	int32_t count = 0;
	while(1){
		if (global == 1){
			switch(count){
			case 0:
				printf("0");
			break;
			case 1:
				printf("1");
			break;
			case 2:
				printf("2");
			break;
			case 3:
				printf("3");
			break;
			case 4:
				printf("4");
			break;
			case 5:
				printf("5");
			break;
			}
			if(count == 5){
				count = 0;
			} else {
				count++;
			}
			global = 0;
		}

	}
}

