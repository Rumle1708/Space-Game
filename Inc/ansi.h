/*
 * ansi.h
 *
 *  Created on: 7 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#ifndef _ANSI_H_
#define _ANSI_H_
void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void drawWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char title[], uint8_t style, struct gameWindow *w);
void drawWindowNoTitle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t style);
void moveUp(uint8_t n);
void moveDown(uint8_t n);
void moveForward(uint8_t n);
void moveBack(uint8_t n);
#endif /* _ANSI_H_ */
