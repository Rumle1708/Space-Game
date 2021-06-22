#define ESC 0x1B
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include "thorTing.h"
#include "math.h"

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void setRGBColorFG(uint8_t red, uint8_t  green, uint8_t  blue){
	printf("%c[%d;%d;%d;%d;%dm",0x1B, 38, 2, red, green, blue);
}

void setRGBColorBG(uint8_t red, uint8_t  green, uint8_t  blue){
	printf("%c[%d;%d;%d;%d;%dm",0x1B, 48, 2, red, green, blue);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(){
	printf("%c[2J%c[H", 0x1B,0x1B);
}

void clreol(){
	printf("%c[2K", 0x1B);
}

void gotoxy(uint8_t x, uint8_t y){
	printf("%c[%d;%df", 0x1B, y, x);
}

void underline(uint8_t on){
	if (on == 1){
		printf("%c[%dm",0x1B, 04);
	} else {
		printf("%c[%dm",0x1B, 24);
	}
}

void blink(uint8_t on){
	if (on == 1){
		printf("%c[%dm",0x1B, 05);
	} else {
		printf("%c[%dm",0x1B, 25);
	}
}

void moveUp(uint8_t n){
	printf("%c[%dA", 0x1B, n);
}

void moveDown(uint8_t n){
	printf("%c[%dB", 0x1B, n);
}

void moveForward(uint8_t n){
	printf("%c[%dC", 0x1B, n);
}

void moveBack(uint8_t n){
	printf("%c[%dD", 0x1B, n);
}

void drawSquare(uint8_t width, uint8_t height, uint8_t x, uint8_t y){
	int32_t i, j;
	for (i = 0; i < height; i++){
		gotoxy(x,y + i);
		for (j = 0; j < width; j++){
			printf(" ");
		}
	}
}

void drawCircle(int32_t r, int32_t x, int32_t y){
	int32_t i;
	for(i = 0; i < 360; i++){
		gotoxy(approxShift14(2*r*cosinus(i)) + x,approxShift14(r*sinus(i)) + y);
		printf(" ");
	}
}

void drawWindow(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, char title[], uint32_t style){
	uint32_t i;
	int corner1, corner2, corner3, corner4, titleLeft, titleRight, bottom, side;
	if (style == 0){
		corner1 = 0xDA;
		corner2 = 0xBF;
		corner3 = 0xC0;
		corner4 = 0xD9;
		titleLeft = 0xB4;
		titleRight = 0xC3;
		bottom = 0xC4;
		side = 0xB3;
	} else{
		corner1 = 0xC9;
		corner2 = 0xBB;
		corner3 = 0xC8;
		corner4 = 0xBC;
		titleLeft = 0xB9;
		titleRight = 0xCC;
		bottom = 0xCD;
		side = 0xBA;
	}

	// Top
	gotoxy(x1,y1);
	printf("%c", corner1);
	printf("%c", titleLeft);
	bgcolor(7);
	fgcolor(0);
	for (i = 0; i <= strlen(title); i++){
		printf("%c", title[i]);
	}
	for (i = strlen(title); i <= x2 - x1 - 4; i++){
		printf("%c", 0x20);
	}
	bgcolor(0);
	fgcolor(7);
	printf("%c", titleRight);
	printf("%c", corner2);

	// Bund
	gotoxy(x1,y2);
	printf("%c", corner3);
	for (i = 0; i <= x2 - x1 - 2; i++){
		printf("%c", bottom);
	}
	printf("%c", corner4);

	// Venstre side
	gotoxy(x1,y1 + 1);
	for (i = 0; i <= y2 - y1 - 1; i++){
		printf("%c", side);
		gotoxy(x1,y1 + 1 + i);
	}

	// Højre side
	gotoxy(x2,y1 + 1);
	for (i = 0; i <= y2 - y1 - 1; i++){
		printf("%c", side);
		gotoxy(x2,y1 + 1 + i);
	}
}

void drawWindowNoTitle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t style){
	uint32_t i;
	int corner1, corner2, corner3, corner4, bottom, side;
	if (style == 0){
		corner1 = 0xDA;
		corner2 = 0xBF;
		corner3 = 0xC0;
		corner4 = 0xD9;
		bottom = 0xC4;
		side = 0xB3;
	} else{
		corner1 = 0xC9;
		corner2 = 0xBB;
		corner3 = 0xC8;
		corner4 = 0xBC;
		bottom = 0xCD;
		side = 0xBA;
	}

	// Top
	gotoxy(x1,y1);
	printf("%c", corner1);
	for (i = 0; i <= x2 - x1 - 2; i++){
		printf("%c", bottom);
	}
	printf("%c", corner2);

	// Bund
	gotoxy(x1,y2);
	printf("%c", corner3);
	for (i = 0; i <= x2 - x1 - 2; i++){
		printf("%c", bottom);
	}
	printf("%c", corner4);

	// Venstre side
	gotoxy(x1,y1 + 1);
	for (i = 0; i <= y2 - y1 - 1; i++){
		printf("%c", side);
		gotoxy(x1,y1 + 1 + i);
	}

	// Højre side
	gotoxy(x2,y1 + 1);
	for (i = 0; i <= y2 - y1 - 1; i++){
		printf("%c", side);
		gotoxy(x2,y1 + 1 + i);
	}
}

void drawGameTitle(uint32_t x2, uint32_t y2){
	int32_t i, j;

	setRGBColorBG(128,128,128);
	gotoxy(1,y2 + 1);
	for (i = 0; i < 24; i++){
		for (j = 0; j < x2; j++){
			printf(" ");
		}
		printf("\n");
	}

	setRGBColorBG(210,0,0);
	drawSquare(3,2,3,y2 + 3);
	drawSquare(3,2,8,y2 + 3);
	drawSquare(3,2,13,y2 + 3);
	setRGBColorBG(210,210,0);
	drawSquare(3,2,18,y2 + 3);
	drawSquare(3,2,23,y2 + 3);
	drawSquare(3,2,28,y2 + 3);
	setRGBColorBG(0,210,0);
	drawSquare(3,2,33,y2 + 3);
	drawSquare(3,2,38,y2 + 3);
	drawSquare(3,2,43,y2 + 3);
	drawSquare(3,2,48,y2 + 3);

	setRGBColorBG(100,0,0);
	drawCircle(1,14, y2 + 15);
	drawCircle(2,14, y2 + 15);
	drawCircle(3,14, y2 + 15);
	drawCircle(4,14, y2 + 15);
	setRGBColorBG(0,0,0);
	drawCircle(5,14, y2 + 15);

	setRGBColorBG(0,128,0);
	drawCircle(1,40, y2 + 15);
	drawCircle(2,40, y2 + 15);
	drawCircle(3,40, y2 + 15);
	drawCircle(4,40, y2 + 15);
	setRGBColorBG(0,0,0);
	drawCircle(5,40, y2 + 15);

	drawWindowNoTitle(x2 - 60, y2 + 2, x2 - 4, y2 + 22, 0);
	setRGBColorBG(0,128,128);
	drawSquare(55, 19, x2 - 59, y2 + 3);


	setRGBColorBG(0,0,0);
}

