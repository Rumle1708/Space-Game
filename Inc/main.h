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

#define M_PI

volatile int32_t global;


#endif /* MAIN_H_ */
