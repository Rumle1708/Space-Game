/*
 * vector.h
 *
 *  Created on: 7 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#ifndef VECTOR_H_
#define VECTOR_H_

struct vector_t{
	int32_t x, y;
};

void initVector(struct vector_t *v, int32_t x, int32_t y);
void vecToString(struct vector_t v);
void rotateVector(struct vector_t *v, int32_t angle);

#endif /* VECTOR_H_ */
