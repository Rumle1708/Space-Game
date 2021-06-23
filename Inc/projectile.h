/*
 * projectile.h
 *
 *  Created on: 15 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_
#define ENTITIES 10

struct projectile_t {
	int32_t posX, posY, velX, velY, alive, time;
};

#include "thorTing.h"

void initProjectiles(struct projectile_t *p);
void spawnProjectile(struct projectile_t *p, struct player2_t *player);
void updateProjectiles(struct projectile_t *p, struct asteroid asteroid1, struct asteroid asteroid2);
void impactDetection(struct player2_t *player, struct projectile_t *p);

#endif /* PROJECTILE_H_ */
