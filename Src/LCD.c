/*
 * LCD.c
 *
 *  Created on: 9 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "charset.h"
#include <string.h>

// hej

void lcd_write_string(char str[], int32_t slice, uint8_t line){
	uint8_t buffer[512];
	int32_t i, j;
	/*
	for (i = line*128; i < (1 + line)*128; i++){
		buffer[i] = 0x00;
	}
	*/

	for(i = 0; i < strlen(str); i++){
		for (j = 0; j < 5; j++){
			buffer[(line*128) + (5*i+j) + slice] = character_data[str[i] - 0x20][j];
		}
	}

	for(i = strlen(str) * 5 + (line*128); i < 512; i++){
		buffer[i] = 0x00;
	}
	lcd_push_buffer(buffer);
}
