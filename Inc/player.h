/*
 * player.h
 *
 *  Created on: Jun 11, 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef PLAYER_H_
#define PLAYER_H_

struct player2_t{
	int32_t posX, posY, velX, velY, angle, shotType, shotConstant, lives, color;
	int32_t sprite[5][5];
};


//void initPlayer(struct player_t *p, int32_t x, int32_t y);
void initPlayer(struct player2_t *p, int32_t x, int32_t y, int32_t angle, int32_t sprite[5][5], int32_t color);

//void updatePlayer(struct player_t *p, int32_t update);
void updatePlayer(struct player2_t *p, int32_t angle, int32_t throttle);

//void drawPlayer(struct player_t *p);
void drawPlayer(struct player2_t *p);

//void deletePlayer(struct player_t *p);
void deletePlayer(struct player2_t *p);

int32_t joystickApprox(int32_t deg, int32_t throttle);

#endif /* PLAYER_H_ */
