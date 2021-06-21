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

/*

void drawAsteroid(struct asteroid *a, int32_t x1, int32_t y1, int32_t size1) {
		(*a).x = x1;
		(*a).y = y1;
		(*a).size = size1;
		for (int i = 0; i <= 360; i++) {
			gotoxy(approxShift14(cosinus(i)*size1)*1.8 + (*a).x, approxShift14(sinus(i)*size1) + (*a).y);
			printf("%s", "o");
		}
		(*a).vol = ((M_PI * 4 / 3 * size1 * size1 * size1) >> 14);
}

void gravity (struct player2_t *p, struct asteroid a) {
	const int gravityConst = (4 << FIX14_SHIFT) / 10; //Tweekes til passende tyngdekraft
	int32_t lang, kort;
	// x og y-koordinater fra spiller til asteroide
	int32_t distX = (a.x << FIX14_SHIFT) - p->posX;
	int32_t distY = (a.y << FIX14_SHIFT) - p->posY;
	if (distX < 0) distX *= -1;
	if (distY < 0) distY *= -1;
	if (distX > distY) {
		lang = distX;
		kort = distY;
	} else {
		kort = distX;
		lang = distY;
	}
	int32_t distTotal = (lang * 7 / 8 + kort / 2) >> FIX14_SHIFT; //Approximeret afstand til asteroide
	// enhedskoordinater fra spiller til asteroide
	int32_t deviceVectorX = (distX / distTotal);
	int32_t deviceVectorY = (distY / distTotal);
	// volumen af asteroide
	int32_t vol = a.vol;
	// sætter de hastighedsvektorer som påvirker spilleren fra asteroiden

	gotoxy(0,10);
	printFix(expand((deviceVectorX)));

	gotoxy(0,11);
	printFix(expand((deviceVectorY)));

	gotoxy(0,12);
	printf("%d", distTotal);



	p->velX += (gravityConst * vol / (distTotal * distTotal * 9) * (deviceVectorX >> 14));

	p->velY += (gravityConst * vol / (distTotal * distTotal * 9) * (deviceVectorY >> 14));

	gotoxy(0,15);
	printFix(expand(((gravityConst * vol / (distTotal * distTotal * 9) * deviceVectorX)) >> 14));

	gotoxy(0,16);
	printFix(expand(((gravityConst * vol / (distTotal * distTotal * 9) * deviceVectorY)) >> 14));
}



int collision (struct player_t p, struct asteroid a , struct gameWindow w ) {
	int c = 0;
	int playerX = p.posX >> 14;
	int playerY = p.posY >> 14;
	int32_t i;
	if (playerX >= a.x && playerY <= a.y) { // første kvadrant
		//printf("er i forste kvadrant");
		for (i = 270; i <= 360; i++) {
			if (playerX <= (approxShift14(cosinus(i) * a.size * 18 / 10) + a.x) && playerY >= (approxShift14(sinus(i)*a.size) + a.y)) {
				c = 1;
			}
		}
	} else if (playerX < a.x && playerY <= a.y) { // anden kvadrant
		//printf("er i anden kvadrant");
		for (i = 180; i <= 270; i++) {
			if (playerX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY >= approxShift14(sinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	} else if (playerX < a.x && playerY > a.y) { // tredje kvadrant
		//printf("er i tredje kvadrant");
		for (i = 90; i <= 180; i++) {
			if (playerX >= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY <= approxShift14(sinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	} else { // fjerde kvadrant
		//printf("er i fjerde kvadrant");
		for (i = 0; i <= 90; i++) {
			if (playerX <= approxShift14(cosinus(i) * a.size * 18 / 10) + a.x && playerY <= approxShift14(sinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	}

	if (playerX <= X1 || playerX >= X2 || playerY <= Y1 || playerY >= Y2) {
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
                	for (int count = 0; count <= 500000; count++)
                		if (count == 500000) {
                			x1 = 0;
                		}
                }
			}
			x1 = x1 + 10;
			if (x1 % 250 == 0) {
				y1 = y1 + 10;
				x1 = 10;
			}
	}//teks
}

*/
