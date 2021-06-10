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

int main(void){
	// Initialization
	uart_init(115200);
	clrscr();

	initADC();
	initIOJoystick();
	lcd_init();
	drawWindowNoTitle(1,1,192,64,1);
	struct player_t{
		int32_t posX, posY, velX, velY;
	};

	void initPlayer(struct player_t *p, int32_t a, int32_t b){
		p->posX = a;
		p->posY = b;
		p->velX = 0;
		p->velY = 0;
	}

	void movePlayer(struct player_t *p, int8_t move){
		//gotoxy(p->posX,p->posY);
		// printf(" ");
		if(move == 2){
			p->velY += 1;
		}
		if(move == 4){
			p->velX -= 2;
		}
		if(move == 8){
			p->velX += 2;
		}
		if(move == 16){
			p->velY -= 1;
		}
		p->posX += p->velX;
		p->posY += p->velY;
		gotoxy(p->posX,p->posY);
		printf("o");
	}

	struct player_t p1;

	initPlayer(&p1,3,3);

	int8_t move;

	char str[20];

	while(1){
		move = readJoystick();
		movePlayer(&p1,move);
		sprintf(str, "x = %02ld", p1.posX / 2);
		lcd_write_string(str, 0, 0);
		sprintf(str, "y = %02ld", p1.posY);
		lcd_write_string(str, 0, 1);
		for(uint32_t i = 0; i < 500000; i++){}
	}
}

