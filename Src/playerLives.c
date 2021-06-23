/*
 * playerLives.c
 *
 *  Created on: 23 Jun 2021
 *      Author: Karl
 */

#include "stm32f30x_conf.h"
#include "30010_io.h"
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "ansi.h"


void printLives(struct player2_t p, int32_t pos){

	fgcolor(p.color);

	if(pos){
		// Player 2

		switch(p.lives){
		case 0:
			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(238 + i,5 + j);

					printf("%c",0x20);

				}
			}


			// Heart 2

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(243 + i,5 + j);

					printf("%c",0x20);

				}
			}

			// Heart 3

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(248 + i,5 + j);

					printf("%c",0x20);

				}
			}

			break;
		case 1:

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(238 + i,5 + j);

					printf("#");

				}
			}


			// Heart 2

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(243 + i,5 + j);

					printf("%c",0x20);

				}
			}

			// Heart 3

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(248 + i,5 + j);

					printf("%c",0x20);

				}
			}

			break;
		case 2:

			// Heart 1

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(238 + i,5 + j);

					printf("%c", 0xDB);

				}
			}


				// Heart 2

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(243 + i,5 + j);

					printf("%c", 0xDB);

				}
			}

				// Heart 3

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(248 + i,5 + j);

					printf("%c",0x20);

				}
			}

			break;
		case 3:

			// Heart 1

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(238 + i,5 + j);

					printf("%c", 0xDB);

				}
			}


			// Heart 2

			for(int32_t i = 0; i <= 3; i++){
				for(int32_t j = 0; j <= 3; j++){

					gotoxy(243 + i,5 + j);

					printf("%c", 0xDB);

				}
			}

			// Heart 3

			for(int32_t i = 0; i <= 3; i++){
					for(int32_t j = 0; j <= 3; j++){

					gotoxy(248 + i,5 + j);

					printf("%c", 0xDB);

				}
			}

			break;

		}

	} else {
		switch(p.lives){
				case 0:
					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(5 + i,5 + j);

							printf("%c",0x20);

						}
					}


					// Heart 2

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(10 + i,5 + j);

							printf("%c",0x20);

						}
					}

					// Heart 3

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(15 + i,5 + j);

							printf("%c",0x20);

						}
					}
					break;
				case 1:

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(5 + i,5 + j);

							printf("%c", 0xDB);

						}
					}


					// Heart 2

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(10 + i,5 + j);

							printf("%c",0x20);

						}
					}

					// Heart 3

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(15 + i,5 + j);

							printf("%c",0x20);

						}
					}

					break;
				case 2:

					// Heart 1

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(5 + i,5 + j);

							printf("%c", 0xDB);

						}
					}


						// Heart 2

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(10 + i,5 + j);

							printf("%c", 0xDB);

						}
					}

						// Heart 3

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(15 + i,5 + j);

							printf("%c",0x20);

						}
					}

					break;
				case 3:

					// Heart 1

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(5 + i,5 + j);

							printf("%c", 0xDB);

						}
					}


					// Heart 2

					for(int32_t i = 0; i <= 3; i++){
						for(int32_t j = 0; j <= 3; j++){

							gotoxy(10 + i,5 + j);

							printf("%c", 0xDB);

						}
					}

					// Heart 3

					for(int32_t i = 0; i <= 3; i++){
							for(int32_t j = 0; j <= 3; j++){

							gotoxy(15 + i,5 + j);

							printf("%c", 0xDB);

						}
					}

					break;

				}

	}


	fgcolor(0);

}
