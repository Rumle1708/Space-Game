/*
 * main.h
 *
 *  Created on: 9 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef MAIN_H_
#define MAIN_H_

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

#define X1 1
#define Y1 1
#define X2 255
#define Y2 100
#define ENTITIES 10

#define M_PI (3141 << 14) / 1000

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

volatile int32_t global;


#endif /* MAIN_H_ */
