/*
 * window.h
 *
 *  Created on: 15 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#define X1 1
#define Y1 1
#define X2 255
#define Y2 100

struct window_t{
	uint32_t x1, y1, x2, y2;
};

void initWindow(struct window_t *w, uint32_t xOne, uint32_t yOne, uint32_t xTwo, uint32_t yTwo);

#endif /* WINDOW_H_ */
