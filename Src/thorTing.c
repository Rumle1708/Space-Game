/*
 * ThorTing.c
 *
 *  Created on: 13. jun. 2021
 *      Author: Bruger
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "player.h"
#include "main.h"
#include "thorTing.h"
#include "string.h"

void drawAsteroid(struct asteroid *a, int32_t x1, int32_t y1, int32_t size1) {
	fgcolor(15);
		(*a).x = x1;
		(*a).y = y1;
		(*a).size = size1;
		for (int i = 0; i <= 360; i++) {
			gotoxy(approxShift14(cosinus(i)*size1) * 18 / 10 + (*a).x, approxShift14(sinus(i)*size1) + (*a).y);
			printf("%s", "o");
		}
		(*a).vol = (M_PI * 4 / 3 * size1 * size1 * size1) >> 14;
	fgcolor(0);
}

void gravity (struct player2_t *p, struct asteroid a) {
	fgcolor(15);
	const int gravityConst = (1 << FIX14_SHIFT) / 2000; //Tweekes til passende tyngdekraft
	int32_t lang, kort;
	// x og y-koordinater fra spiller til asteroide
	int32_t distX = ((a.x << FIX14_SHIFT) - (*p).posX);
	int32_t distY = ((a.y << FIX14_SHIFT) - (*p).posY);

	int32_t tempX = distX;
	int32_t tempY = distY;

	if (tempX < 0) tempX *= -1;
	if (tempY < 0) tempY *= -1;

	if (distX > distY) {
		lang = tempX;
		kort = tempY;
	} else {
		kort = tempX;
		lang = tempY;
	}
	int32_t distTotal = (lang * 7 / 8 + kort / 2) >> 14; //Approximeret afstand til asteroide
	// enhedskoordinater fra spiller til asteroide

	if (tempX < 0) distX *= -1;
	if (tempY < 0) distY *= -1;

	int32_t deviceVectorX = (distX / distTotal);
	int32_t deviceVectorY = (distY / distTotal);
	// volumen af asteroide
	int32_t vol = a.vol;
	// sætter de hastighedsvektorer som påvirker spilleren fra asteroiden
	(*p).velX += (gravityConst * vol / (distTotal * distTotal) * deviceVectorX) >> FIX14_SHIFT;
	(*p).velY += (gravityConst * vol / (distTotal * distTotal) * deviceVectorY) >> FIX14_SHIFT;

	fgcolor(0);
}

int32_t projDist (struct projectile_t proj, struct asteroid a) {
	int32_t lang, kort;
	// x og y-koordinater fra spiller til asteroide
	int32_t distX = ((a.x << FIX14_SHIFT) - proj.posX);
	int32_t distY = ((a.y << FIX14_SHIFT) - proj.posY);

	if (distX < 0) distX *= -1;
	if (distY < 0) distY *= -1;

	if (distX > distY) {
		lang = distX;
		kort = distY;
	} else {
		kort = distX;
		lang = distY;
	}
	int32_t distTotal = (lang * 7 / 8 + kort / 2) >> 14; //Approximeret afstand til asteroide
	// enhedskoordinater fra spiller til asteroide
	return distTotal;
}

int32_t astDist (struct player2_t p, struct asteroid a) {
	int32_t lang, kort;
	// x og y-koordinater fra spiller til asteroide
	int32_t distX = ((a.x << FIX14_SHIFT) - p.posX);
	int32_t distY = ((a.y << FIX14_SHIFT) - p.posY);

	if (distX < 0) distX *= -1;
	if (distY < 0) distY *= -1;

	if (distX > distY) {
		lang = distX;
		kort = distY;
	} else {
		kort = distX;
		lang = distY;
	}
	int32_t distTotal = (lang * 7 / 8 + kort / 2); //Approximeret afstand til asteroide
	// enhedskoordinater fra spiller til asteroide
	return distTotal;
}

int collisionPlayer (struct player2_t p, struct asteroid a) {
	int c = 0;
	int playerX = p.posX >> 14;
	int playerY = p.posY >> 14;
	int32_t i;

	if (astDist(p,a) < a.size * 2) {
		if (playerX >= a.x && playerY <= a.y) { // første kvadrant
			//printf("er i forste kvadrant");
			for (i = 270; i <= 360; i = i + 3) {
				if (playerX <= (approxShift14(cosinus(i) * a.size * 18 / 10) + a.x) && playerY >= (approxShift14(sinus(i)*a.size) + a.y)) {
					c = 1;
				}
			}
		} else if (playerX < a.x && playerY <= a.y) { // anden kvadrant
			//printf("er i anden kvadrant");
			for (i = 180; i <= 270; i = i + 3) {
				if (playerX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY >= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		} else if (playerX < a.x && playerY > a.y) { // tredje kvadrant
			//printf("er i tredje kvadrant");
			for (i = 90; i <= 180; i = i + 3) {
				if (playerX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY <= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		} else { // fjerde kvadrant
			//printf("er i fjerde kvadrant");
			for (i = 0; i <= 90; i = i + 3) {
				if (playerX <= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY <= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		}
	}

	if (playerX <= X1 || playerX >= X2 || playerY <= Y1 || playerY >= Y2) {
		c = 1;
	}

	return c;
}

int collisionProjectile (struct projectile_t p, struct asteroid a) {
	int c = 0;
	int projectileX = p.posX >> 14;
	int projectileY = p.posY >> 14;
	int32_t i;

	if (projDist(p,a) < a.size * 2) {
		if (projectileX >= a.x && projectileY <= a.y) { // første kvadrant
			//printf("er i forste kvadrant");
			for (i = 270; i <= 360; i = i + 3) {
				if (projectileX <= (approxShift14(cosinus(i) * a.size * 18 / 10) + a.x) && projectileY >= (approxShift14(sinus(i)*a.size) + a.y)) {
					c = 1;
				}
			}
		} else if (projectileX < a.x && projectileY <= a.y) { // anden kvadrant
			//printf("er i anden kvadrant");
			for (i = 180; i <= 270; i = i + 3) {
				if (projectileX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && projectileY >= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		} else if (projectileX < a.x && projectileY > a.y) { // tredje kvadrant
			//printf("er i tredje kvadrant");
			for (i = 90; i <= 180; i = i + 3) {
				if (projectileX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && projectileY <= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		} else { // fjerde kvadrant
			//printf("er i fjerde kvadrant");
			for (i = 0; i <= 90; i = i + 3) {
				if (projectileX <= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && projectileY <= approxShift14(sinus(i)*a.size) + a.y) {
					c = 1;
				}
			}
		}
	}

	if (projectileX <= X1 || projectileX >= X2 || projectileY <= Y1 || projectileY >= Y2) {
		c = 1;
	}

	return c;
}

void titleScreen(char letter[]) {
	int x1 = 10, y1 = 10;

	char	A[Height][Width] ={	"   _/_/  ",
								" _/    _/",
								" _/    _/",
								" _/_/_/_/",
								" _/    _/",
								" _/    _/",
								" _/    _/"},

		B[Height][Width] ={ 	" _/_/_/  ",
								" _/    _/",
								" _/    _/",
								" _/_/_/  ",
								" _/    _/",
								" _/    _/",
								" _/_/_/  "},

		C[Height][Width] ={ 	"   _/_/  ",
								" _/    _/",
								" _/      ",
								" _/      ",
								" _/      ",
								" _/    _/",
								"   _/_/  "},

		D[Height][Width] ={ 	" _/_/_/  ",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/_/_/  "},

		E[Height][Width] ={ 	" _/_/_/_/",
								" _/      ",
								" _/      ",
								" _/_/_/  ",
								" _/      ",
								" _/      ",
								" _/_/_/_/"},

		F[Height][Width] ={ 	" _/_/_/_/",
								" _/      ",
								" _/      ",
								" _/_/_/  ",
								" _/      ",
								" _/      ",
								" _/      "},

		G[Height][Width] ={ 	"   _/_/  ",
								" _/    _/",
								" _/      ",
								" _/  _/_/",
								" _/    _/",
								" _/    _/",
								"   _/_/  "},

		H[Height][Width] ={ 	" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/_/_/_/",
								" _/    _/",
								" _/    _/",
								" _/    _/"},

		I[Height][Width] ={ 	"  _/_/_/ ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"  _/_/_/ "},

		J[Height][Width] ={ 	" _/_/_/_/",
								"       _/",
								"       _/",
								"       _/",
								" _/    _/",
								" _/    _/",
								"   _/_/  "},

		K[Height][Width] ={ 	" _/    _/",
								" _/  _/  ",
								" _/  _/  ",
								" _/_/    ",
								" _/  _/  ",
								" _/   _/ ",
								" _/    _/"},

		L[Height][Width] ={ 	" _/      ",
								" _/      ",
								" _/      ",
								" _/      ",
								" _/      ",
								" _/      ",
								" _/_/_/_/"},

		M[Height][Width] ={ 	" _/    _/",
								" _/_/_/_/",
								" _/ _/ _/",
								" _/ _/ _/",
								" _/    _/",
								" _/    _/",
								" _/    _/"},

		N[Height][Width] ={ 	" _/    _/",
								" _/_/  _/",
								" _/_/  _/",
								" _/ _/ _/",
								" _/  _/_/",
								" _/  _/_/",
								" _/    _/"},

		O[Height][Width] ={ 	"   _/_/  ",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								"   _/_/  "},

		P[Height][Width] ={ 	" _/_/_/  ",
								" _/    _/",
								" _/    _/",
								" _/_/_/  ",
								" _/      ",
								" _/      ",
								" _/      "},

		Q[Height][Width] ={ 	"   _/_/  ",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/  _/_/",
								" _/  _/_/",
								"   _/  _/"},

		R[Height][Width] ={ 	" _/_/_/  ",
								" _/    _/",
								" _/    _/",
								" _/_/_/  ",
								" _/_/    ",
								" _/  _/  ",
								" _/    _/"},

		S[Height][Width] ={ 	"   _/_/_/",
								" _/      ",
								" _/      ",
								"   _/_/  ",
								"       _/",
								"       _/",
								" _/_/_/  "},

		T[Height][Width] ={ 	" _/_/_/_/",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   "},

		U[Height][Width] ={ 	" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								"   _/_/  "},

		V[Height][Width] ={ 	" _/    _/",
								" _/    _/",
								"  _/  _/ ",
								"  _/  _/ ",
								"   _/_/  ",
								"   _/_/  ",
								"    _/   "},

		W[Height][Width] ={ 	" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/    _/",
								" _/ _/ _/",
								" _/ _/ _/",
								"   _/ _/ "},

		X[Height][Width] ={ 	" _/    _/",
								"  _/  _/ ",
								"   _/_/  ",
								"    _/   ",
								"   _/_/  ",
								"  _/  _/ ",
								" _/    _/"},

		Y[Height][Width] ={ 	" _/    _/",
								" _/    _/",
								"  _/  _/ ",
								"    _/   ",
								"    _/   ",
								"    _/   ",
								"    _/   "},

		Z[Height][Width] ={ 	" _/_/_/_/",
								"      _/ ",
								"     _/  ",
								"    _/   ",
								"   _/    ",
								"  _/     ",
								" _/_/_/_/"};


	for (int j1 = 0; j1 <= strlen(letter); j1++) {
		for (int i1 = 0; i1 <= 6; i1++) {
				gotoxy(x1 , y1 + i1);
                if(letter[j1]=='a')
                    printf("%s", A[i1]);
                else if(letter[j1]=='b')
                    printf("%s", B[i1]);
                else if(letter[j1]=='c')
                    printf("%s", C[i1]);
                else if(letter[j1]=='d')
                    printf("%s", D[i1]);
                else if(letter[j1]=='e')
                    printf("%s", E[i1]);
                else if(letter[j1]=='f')
                    printf("%s", F[i1]);
                else if(letter[j1]=='g')
                    printf("%s", G[i1]);
                else if(letter[j1]=='h')
                    printf("%s", H[i1]);
                else if(letter[j1]=='i')
                    printf("%s", I[i1]);
                else if(letter[j1]=='j')
                    printf("%s", J[i1]);
                else if(letter[j1]=='k')
                	printf("%s", K[i1]);
                else if(letter[j1]=='l')
                    printf("%s", L[i1]);
                else if(letter[j1]=='m')
                    printf("%s", M[i1]);
                else if(letter[j1]=='n')
                    printf("%s", N[i1]);
                else if(letter[j1]=='o')
                    printf("%s", O[i1]);
                else if(letter[j1]=='p')
                    printf("%s", P[i1]);
                else if(letter[j1]=='q')
                    printf("%s", Q[i1]);
                else if(letter[j1]=='r')
                    printf("%s", R[i1]);
                else if(letter[j1]=='s')
                    printf("%s", S[i1]);
                else if(letter[j1]=='t')
                    printf("%s", T[i1]);
                else if(letter[j1]=='u')
                    printf("%s", U[i1]);
                else if(letter[j1]=='v')
                    printf("%s", V[i1]);
                else if(letter[j1]=='w')
                    printf("%s", W[i1]);
                else if(letter[j1]=='x')
                    printf("%s", X[i1]);
                else if(letter[j1]=='y')
                    printf("%s", Y[i1]);
                else if(letter[j1]=='z')
                    printf("%s", Z[i1]);
                else if(letter[j1]==' ') {

                }
			}
			x1 = x1 + 10;
			if (x1 % 250 == 0) {
				y1 = y1 + 10;
				x1 = 10;
			}
	}//teks
}
