#define ESC 0x1B
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include <string.h>

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
	printf("%c[%d;%dH", 0x1B, y, x);
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

void drawWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[], uint8_t style){
	uint8_t i;
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

void drawWindowNoTitle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t style){
	uint8_t i;
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
