/*
 * powerup.h
 *
 *  Created on: 19 Jun 2021
 *      Author: Karl
 */

#ifndef POWERUP_H_
#define POWERUP_H_

struct powerup{

	int32_t x, y, power, alive;

};

void powerupInit(struct powerup *powerup, int32_t x, int32_t y, int32_t power);
void powerupUpdate(struct powerup *powerup, struct player2_t *player);
void checkPowerup(struct powerup *powerup1, struct powerup *powerup2, struct player2_t *player1, struct player2_t *player2);

#endif /* POWERUP_H_ */
