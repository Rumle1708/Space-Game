/*
 * player.h
 *
 *  Created on: Jun 11, 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef PLAYER_H_
#define PLAYER_H_

struct player_t{
	int32_t posX, posY, velX, velY, angle;
};

struct player2_t{
	int32_t posX, posY, velX, velY, angle, shotType, shotConstant;
	int32_t sprite[5][5];
};


void initPlayer(struct player_t *p, int32_t x, int32_t y);
void initPlayer2(struct player2_t *p, int32_t x, int32_t y, int32_t sprite[5][5]);

void updatePlayer(struct player_t *p, int32_t update);
void updatePlayer2(struct player2_t *p, int32_t angle, int32_t throttle);

void drawPlayer(struct player_t *p);
void drawPlayer2(struct player2_t *p);

void deletePlayer(struct player_t *p);
void deletePlayer2(struct player2_t *p);

int32_t joystickApprox(int32_t deg, int32_t throttle);

#endif /* PLAYER_H_ */
