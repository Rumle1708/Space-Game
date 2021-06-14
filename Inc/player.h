/*
 * player.h
 *
 *  Created on: Jun 11, 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef PLAYER_H_
#define PLAYER_H_

struct player_t{
	int32_t posX, posY, velX, velY;
};
void initPlayer(struct player_t *p, int32_t x, int32_t y);
void updatePlayer(struct player_t *p, int32_t update);
void drawPlayer(struct player_t *p);

#endif /* PLAYER_H_ */
