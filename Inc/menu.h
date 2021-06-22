/*
 * menu.h
 *
 *  Created on: 21 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef MENU_H_
#define MENU_H_

void gameMenu();
void configureLevel(struct player2_t *p1, struct player2_t *p2, int32_t sprite[5][5], struct projectile_t *proj, struct powerup *pUp1, struct powerup *pUp2, struct asteroid *asteroid1, struct asteroid *asteroid2);

#endif /* MENU_H_ */
