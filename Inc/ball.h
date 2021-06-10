/*
 * ball.h
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef BALL_H_
#define BALL_H_
struct ball_t{
	struct vector_t vel;
	struct vector_t pos;
	int32_t angle;
};

void ballToString(struct ball_t b);
void initBall(struct ball_t *b, int32_t x, int32_t y,  int32_t velX, int32_t velY);
void ballUpdate(struct ball_t *b);
void ballGame(struct ball_t *b,uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif /* BALL_H_ */
