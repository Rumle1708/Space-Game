#ifndef THORTING_H_
#define THORTING_H_

#include "projectile.h"

#define Height 7
#define Width 10

struct asteroid {
	int32_t x, y, size, vol;
};

void drawAsteroid(struct asteroid *a, int32_t x, int32_t y, int32_t size);
void gravity (struct player2_t *p, struct asteroid a);
int collision (struct player2_t p, struct asteroid a /* , struct gameWindow w */);
void titleScreen(char letter[]);
int32_t projDist (struct projectile_t proj, struct asteroid a);
int32_t astDist (struct player2_t p, struct asteroid a);

#endif	// THORTING_H
