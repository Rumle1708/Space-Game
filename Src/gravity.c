#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include "main.h"
#include <string.h>
#include <math.h>

struct gravity {
	int16_t x, y;
};

struct gravity *g;

void force (*g, asteroid) {
	const int gravityConst = 10; //Tweekes senere til at finde passende tyngdekraft
	int32_t dist = sqrt((asteroid.x - player.x)^2 + (asteroid.y - player.y)^2); //Afstand til astroide
	// x og y-koordinater fra spiller til asteroide
	int32_t a = (asteroid.x - player.x) << 14;
	int32_t b = (asteroid.y - player.y) << 14;
	// enhedskoordinater fra spiller til asteroide
	int32_t deviceVectorX = FIX14_DIV(a,dist) >> 14;
	int32_t deviceVectorY = FIX14_DIV(b,dist) >> 14;
	// volumen af asteroide
	int32_t vol = 4/3 * M_PI * (asteroid.size)^3;
	// sætter de hastighedsvektorer som påvirker spilleren fra asteroiden
	(*g).x = gravityConst * vol / dist^2 * deviceVectorX;
	(*g).y = gravityConst * vol / dist^2 * deviceVectorY;
}
