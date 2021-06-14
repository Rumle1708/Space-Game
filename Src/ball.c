/*
 * ball.c
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "30010_io.h" 		// Input/output library for this course
#include <stdio.h>
#include "LUT.h"
#include "ansi.h"
#include "vector.h"
#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

struct ball_t{
	int32_t posX, posY, velX, velY;
	int32_t angle;
};

void initBall(struct ball_t *b, int32_t x, int32_t y,  int32_t velX, int32_t velY){
	b->posX = x << FIX14_SHIFT;
	b->posY = y << FIX14_SHIFT;
	b->velX = velX << FIX14_SHIFT;
	b->velY = velY << FIX14_SHIFT;
}

void ballToString(struct ball_t b){
	printf("\nx = ");
	printFix(expand(b.posX));
	printf("\ny = ");
	printFix(expand(b.posY));
	printf("\nvelX = ");
	printFix(expand(b.velX));
	printf("\nvelY = ");
	printFix(expand(b.velY));
}

void ballUpdate(struct ball_t *b){
	gotoxy(b->posX >> FIX14_SHIFT, b->posY >> FIX14_SHIFT);
	printf(" ");
	b->posX += b->velX;
	b->posY += b->velY;
	gotoxy(b->posX >> FIX14_SHIFT, b->posY >> FIX14_SHIFT);
	printf("o");
}

void rotateBall(struct ball_t *b, int32_t angle){
	int32_t tempX = b->velX, tempY = b->velY, temp1, temp2;
	temp1 = cosinus(angle);
	temp2 = sinus(angle);
	b->velX = (FIX14_MULT(tempX,temp1)) - (FIX14_MULT(tempY,temp2));
	b->velY = (FIX14_MULT(tempX,temp2)) + (FIX14_MULT(tempY,temp1));
}

void ballGame(struct ball_t *b,uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	int32_t hit = 0;
	//drawWindowNoTitle(x1,y1,x2,y2,1);
	//drawWindowNoTitle(x1,y2 + 1,x1 + 9,y2 + 3,1);
	gotoxy(x1 + 1,y2 + 2);
	printf("Hits:");
	b->posX = (x1 + 1) << FIX14_SHIFT;
	b->posY = (y1 + 1) << FIX14_SHIFT;
	gotoxy(b->posX >> FIX14_SHIFT, b->posY >> FIX14_SHIFT);
	printf("*");
	while(1){
		if(((b->posX + b->velX) >> FIX14_SHIFT) >= x2){
			b->velX = -b->velX;
			hit++;
			gotoxy(x1 + 7,y2 + 2);
			printf("%ld", hit);
		} else if(((b->posY + b->velY) >> FIX14_SHIFT) >= y2){
			b->velY = -b->velY;
			hit++;
			gotoxy(x1 + 7,y2 + 2);
			printf("%ld", hit);
		} else if(((b->posX + b->velX) >> FIX14_SHIFT) <= x1){
			b->velX = -b->velX;
			hit++;
			gotoxy(x1 + 7,y2 + 2);
			printf("%ld", hit);
		} else if(((b->posY + b->velY) >> FIX14_SHIFT) <= y1){
			b->velY = -b->velY;
			hit++;
			gotoxy(x1 + 7,y2 + 2);
			printf("%ld", hit);
		}
		ballUpdate(b);
	}

}
