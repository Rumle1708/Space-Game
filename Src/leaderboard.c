/*
 * leaderboard.c
 *
 *  Created on: 22 Jun 2021
 *      Author: Karl
 */

#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdio.h>
#include <string.h>
#include "ansi.h"


void updateLeaderboard3(int32_t player, int32_t time, int32_t **leaderboard[100][2]){
	// Updates the leaderboard if a new high score is achieved
	for(int32_t i = 0; i < 100; i++){
		if((time < leaderboard[i][0]) || leaderboard[i][0] == 0){
			for(int32_t j = 99; j > i; j--){
				leaderboard[j][0] = leaderboard[j - 1][0];
				leaderboard[j][1] = leaderboard[j - 1][1];
			}
			leaderboard[i][0] = time;
			leaderboard[i][1] = player;
			i = 100;
		}
	}
}



void printLeaderboard(int32_t p1Wins, int32_t p2Wins, int32_t leaderboard[100][2]){
	// Prints leaderboard array on screen
	fgcolor(15);
	gotoxy(110,25);
	printf("Wins:");
	gotoxy(110,27);
	printf("Player 1 wins: %ld", p1Wins);
	gotoxy(110,28);
	printf("Player 2 wins: %ld", p2Wins);

	// Shows highscores of current round
	gotoxy(110,30);
	printf("Highscores:");
	for(int32_t i = 0; i < 100; i++){
		if(leaderboard[i][1] != 0 && leaderboard[i][0] != 0){
			gotoxy(110,32 + i);
			printf("%ld, Player: %ld, Time: ", i + 1, leaderboard[i][1]);
			printFix(expand(leaderboard[i][0]));
		}
	}
	fgcolor(0);
}

