// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================
#ifndef THORTING_H_
#define THORTING_H_

#define Height 7
#define Width 10

struct gameWindow {
	int8_t x1, y1, x2, y2;
};

struct gravity {
	int32_t x, y;
};

struct asteroid {
	int32_t x, y, size, vol;
};

void drawAsteroid(struct asteroid *a, int32_t x, int32_t y, int32_t size);
void gravity (struct asteroid a, struct player_t p, struct gravity *g);
int collision (struct player_t p, struct asteroid a, struct gameWindow w);
void titleScreen(char letter[]);

#endif	// THORTING_H

//teks
