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
#define BITS sizeof(int32_t) * 8
#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

int main(void){
	// Initialization
	uart_init(115200);
	clrscr();

	initADC();
	lcd_init();
	uint32_t V1, V2;
	char str[20];
	drawWindowNoTitle(1,1,192,64,1);
	gotoxy(50,30);
	printf("Hej med dig");
	while(1){
		V1 = readADC(1);
		sprintf(str, "Channel 1 = %02ld V", V1);
		//printf("%s\n V", str);
		lcd_write_string(str, 0, 0);
		V2 = readADC(2);
		sprintf(str, "Channel 2 = %02ld V", V2);
		//printf("%s\n V", str);
		lcd_write_string(str, 0, 1);
		lcd_write_string(" ", 0, 2);
		lcd_write_string(" ", 0, 3);
		for(int i = 0; i < 500000; i++){}
	}
}

