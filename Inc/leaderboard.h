/*
 * leaderboard.h
 *
 *  Created on: 22 Jun 2021
 *      Author: Karl
 */

#ifndef LEADERBOARD_H_
#define LEADERBOARD_H_

void printLeaderboard(int32_t p1Wins, int32_t p2Wins, int32_t leaderboard[100][2]);
void updateLeaderboard3(int32_t player, int32_t time, int32_t **leaderboard[100][2]);

#endif /* LEADERBOARD_H_ */
