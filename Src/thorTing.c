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
	(*a).x = x1;
	(*a).y = y1;
	(*a).size = size1;
	for (int i = 0; i <= 360; i++) {
		gotoxy(approxShift14(sinus(i)*size1)*1.8 + (*a).x, approxShift14(cosinus(i)*size1) + (*a).y);
		printf("%s", "o");
	}
	FIX14_MULT(4 >> FIX14_SHIFT,3 >> FIX14_SHIFT);
	(*a).vol = FIX14_MULT(FIX14_MULT(FIX14_DIV(4 >> FIX14_SHIFT,3 >> FIX14_SHIFT),M_PI),FIX14_MULT(FIX14_MULT((*a).size >> FIX14_SHIFT,(*a).size >> FIX14_SHIFT),(*a).size >> FIX14_SHIFT)) << 14;
} // 4/3*pi*size^3

void gravity (struct asteroid a, struct player_t p, struct gravity *g) {
	const int gravityConst = FIX14_DIV(4 << FIX14_SHIFT,10 << FIX14_SHIFT); //Tweekes til passende tyngdekraft
	int32_t lang, kort;
	// x og y-koordinater fra spiller til asteroide
	int32_t distX = (a.x - p.posX) << FIX14_SHIFT;
	int32_t distY = (a.y - p.posY) << FIX14_SHIFT;
	if (distX > distY) {
		lang = distX;
		kort = distY;
	} else {
		kort = distX;
		lang = distY;
	}
	int32_t distTotal = FIX_MULT(lang,FIX14_DIV(7 << FIX14_SHIFT,8 << FIX14_SHIFT)) + FIX14_DIV(kort,2 << FIX14_SHIFT); //Approximeret afstand til asteroide
	// enhedskoordinater fra spiller til asteroide
	int32_t deviceVectorX = FIX14_DIV(distX,distTotal);
	int32_t deviceVectorY = FIX14_DIV(distY,distTotal);
	// volumen af asteroide
	int32_t vol = a.vol >> 14;
	// sætter de hastighedsvektorer som påvirker spilleren fra asteroiden
	(*g).x = approxShift14(FIX14_MULT(FIX14_DIV(FIX14_MULT(gravityConst,vol),FIX14_MULT(FIX14_MULT(distTotal,distTotal),9)),deviceVectorX));
	(*g).y = approxShift14(FIX14_MULT(FIX14_DIV(FIX14_MULT(gravityConst,vol),FIX14_MULT(FIX14_MULT(distTotal,distTotal),9)),deviceVectorY));
}


int collision (struct player_t p, struct asteroid a, struct gameWindow w) {
	int c = 0;
	int32_t i;
	if (p.posX >= a.x && p.posY <= a.y) { // første kvadrant
		for (i = 0; i <= 90; i++) {
			if (p.posX <= approxShift14(sinus(i)*a.size)*1.6 + a.x && p.posY >= approxShift14(cosinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	} else if (p.posX < a.x && p.posY <= a.y) { // anden kvadrant
		for (i = 90; i <= 180; i++) {
			if (p.posX >= approxShift14(sinus(i)*a.size)*1.6 + a.x && p.posY >= approxShift14(cosinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	} else if (p.posX < a.x && p.posY > a.y) { // tredje kvadrant
		for (i = 180; i <= 270; i++) {
			if (p.posX >= approxShift14(sinus(i)*a.size)*1.6 + a.x && p.posY <= approxShift14(cosinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	} else { // fjerde kvadrant
		for (i = 270; i <= 360; i++) {
			if (p.posX <= approxShift14(sinus(i)*a.size)*1.6 + a.x && p.posY <= approxShift14(cosinus(i)*a.size) + a.y) {
				c = 1;
			}
		}
	}
	if (p.posX <= w.x1 || p.posX >= w.x2 || p.posY <= w.y1 || p.posY >= w.y2) {
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
						" _/_   _/"},

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
				"  _/ _/  ",
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
                	for (int count = 0; count <= 50000; count++)
                		if (count == 0) {
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
