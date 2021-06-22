/*
 * math.h
 *
 *  Created on: Jun 11, 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef MATH_H_
#define MATH_H_

int32_t approxShift14(int32_t n);

int32_t sinus(int32_t angle);
int32_t cosinus(int32_t angle);
int32_t degCon(int32_t angle);

int32_t expand(int32_t i);
int32_t unexpand(int32_t i);
void printFix(int32_t i);

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

#endif /* MATH_H_ */
