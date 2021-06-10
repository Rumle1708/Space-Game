/*
 * vector.c
 *
 *  Created on: 7 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "30010_io.h"
#include "LUT.h"

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b))>>FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

struct vector_t{
	int32_t x, y;
};

void initVector(struct vector_t *v, int32_t a, int32_t b){
	v->x = a << FIX14_SHIFT;
	v->y = b << FIX14_SHIFT;
}

void vecToString(struct vector_t v){
	printf("\nx = ");
	printFix(expand(v.x));
	printf("\ny = ");
	printFix(expand(v.y));
}

void rotateVector(struct vector_t *v, int32_t angle){
	int32_t tempX = v->x, tempY = v->y, temp1, temp2;
	temp1 = cosinus(angle);
	temp2 = sinus(angle);
	v->x = (FIX14_MULT(tempX,temp1)) - (FIX14_MULT(tempY,temp2));
	v->y = (FIX14_MULT(tempX,temp2)) + (FIX14_MULT(tempY,temp1));
}
