#ifndef THORTING_H_
#define THORTING_H_

#define Height 7
#define Width 10

struct gravity {
	int32_t x, y;
};

struct asteroid {
	int32_t x, y, size, vol;
};

void drawAsteroid(struct asteroid *a, int32_t x, int32_t y, int32_t size);
void gravity (struct player2_t *a, struct asteroid p);
int collision (struct player_t p, struct asteroid a /* , struct gameWindow w */);
void titleScreen(char letter[]);

#endif	// THORTING_H
