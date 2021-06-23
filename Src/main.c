#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdio.h>
#include <string.h>
#include "ansi.h"
#include "IO.h"
#include "timer.h"
#include "charset.h"
#include "LCD.h"
#include "player.h"
#include "math.h"
#include "main.h"
#include "projectile.h"
#include "ADC2.h"
#include "powerup.h"
#include "thorTing.h"
#include "menu.h"
#include "leaderboard.h"
#include "playerLives.h"

// Constants defining window size
#define X1 1
#define Y1 1
#define X2 255
#define Y2 100

// Maximum number of bullets
#define ENTITIES 10

#define ESC 0x1B

// 18.14 fixed point math macros
#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) (((a)*(b)) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) (((a)<<FIX14_SHIFT)/b)

// Check single bit in value macro
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int main(void){
	// Initialisation of UART
	uart_init(2000000);
	uart_clear();

	// Initialisation of IO
	initSwitches();
	initIOJoystick();
	initIOLED();
	lcd_init();
	initTimer();
	initADC();

	printf("%c[?%dl", ESC, 25); // Removes cursor

	setLED(0,1,0);

	// Player sprite (should resemble an X-wing)
	int32_t sprite[5][5] = {
	{0,1,0,1,0},
	{1,1,1,1,1},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}
	};


	// Structs and value initialisation
	int32_t p1Wins = 0, p2Wins = 0;

	int32_t leaderboard[100][2] = {0};

	struct player2_t p1, p2;

	struct projectile_t proj[ENTITIES];

	struct powerup powerup1, powerup2;

	struct asteroid asteroid1, asteroid2;

	// Start main-while-loop
	while(1){

		int32_t time = 0; // Indicates a rounds duration

		clrscr(); // Clears screen

		fgcolor(1);

		titleScreen("xwing versus"); // Prints title screen

		fgcolor(0);

		printLeaderboard(p1Wins, p2Wins, leaderboard); // Print leaderboard

		configureLevel(&p1, &p2, sprite, &proj, &powerup1, &powerup2, &asteroid1, &asteroid2); // Runs menu and sets up level

		while((p1.lives > 0) && (p2.lives > 0)){
			// Game runs when both players are alive
			if (global != 0){
				// IMPORTANT this if-statement controls the frame-rate/update-rate
				if(readJoystick() != 0){
					// Goes into boss-mode if boss is present
					initBoss();
				}

				int32_t switches = readSwitches();

				switch(switches){
				// Sets RGB-LEDS to blink if user shoots
				case 0:
					setLED(0,1,0);
					break;
				case 1:
					setLED(1,0,0);
					break;
				case 2:
					setLED(0,0,1);
					break;
				case 3:
					setLED(1,0,1);
					break;
				}

				if (switches == 3 || switches == 1){
					// Spawns projectile for player one
					spawnProjectile(&proj,&p1);

				}

				if (switches == 2 || switches == 3){
					// Spawns projectile for player two
					spawnProjectile(&proj,&p2);
				}

				updateProjectiles(&proj,asteroid1,asteroid2); // Updates alive projectile

				movePlayer(&p1, &p2, asteroid1, asteroid2); // Updates and draws player one and two

				checkPowerup(&powerup1, &powerup2, &p1, &p2); // Determines if players got a powerup

				impactDetection(&p1, &proj); // Check player one impact with bullet

				impactDetection(&p2, &proj); // Check player two impact with bullet

				printLives(p1, 0); // Prints number of lives for player one

				printLives(p2, 1); // Prints number of lives for player two

				fflush(stdout); // Empties buffer

				time += (1 << 14) / 24; // Update time

				global = 0; // Reset global
			}
		}

		if(p1.lives != 0){
			// Checks if player one won
			fgcolor(p1.color);

			titleScreen("player one wins");

			fgcolor(0);

			p1Wins++; // Update player score

			updateLeaderboard3(1, time ,&leaderboard);

		} else {

			fgcolor(p2.color);

			titleScreen("player two wins");

			fgcolor(0);

			p2Wins++;  // Update player score

			updateLeaderboard3(2, time ,&leaderboard);

		}

		int32_t timeTemp = global;

		// time delay

		while(global < (timeTemp + 96)){};

	}
}

