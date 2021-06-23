/*
 * IO.c
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

void initIOJoystick(){
	// On board joystick settings
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// Setting mode register for input pins

	// C0 right
	GPIOC->MODER &= ~(0x00000003 << (0 * 2));
	GPIOC->MODER |= (0x00000000 << (0 * 2));

	// C1 left
	GPIOC->MODER &= ~(0x00000003 << (1 * 2));
	GPIOC->MODER |= (0x00000000 << (1 * 2));

	// A4 up
	GPIOA->MODER &= ~(0x00000003 << (4 * 2));
	GPIOA->MODER |= (0x00000000 << (4 * 2));

	// B0 down
	GPIOB->MODER &= ~(0x00000003 << (0 * 2));
	GPIOB->MODER |= (0x00000000 << (0 * 2));

	// B5 center
	GPIOB->MODER &= ~(0x00000003 << (5 * 2));
	GPIOB->MODER |= (0x00000000 << (5 * 2));
}

void initIOLED(){
	// On board LED settings
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// A9 Blue
	GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));
	GPIOA->OSPEEDR |= (0x00000002 << (9 * 2));
	GPIOA->OTYPER &= ~(0x0001 << (9 * 1)); // Clear output type register
	GPIOA->OTYPER |= (0x0000 << (1)); // Set output type register
	GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
	GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register

	// C7 Green
	GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
	GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));
	GPIOC->OTYPER &= ~(0x0001 << (7 * 1)); // Clear output type register
	GPIOC->OTYPER |= (0x0000 << (1)); // Set output type register
	GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
	GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register

	// B4 Red
	GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
	GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));
	GPIOB->OTYPER &= ~(0x0001 << (4 * 1)); // Clear output type register
	GPIOB->OTYPER |= (0x0000 << (1)); // Set output type register
	GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
	GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register


	GPIOB->ODR &= ~(0x0001 << 4);
	GPIOC->ODR &= ~(0x0001 << 7);
	GPIOA->ODR &= ~(0x0001 << 9);
}


void initSwitches(){
	// Switches for shooting buttons

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	// A5
	GPIOA->MODER &= ~(0x00000003 << (5 * 2));  // Clear mode register
	GPIOA->MODER |= (0x00000000 << (5 * 2));	// Set mode register

	// C4
	GPIOC->MODER &= ~(0x00000003 << (4 * 2));	 // Clear mode register
	GPIOC->MODER |= (0x00000000 << (4 * 2));	// Set mode register

}




int8_t readJoystick(){
	// Reads a value from the on board joystick and returns that value
	int8_t C, U, D, L, R, IO = 0;;

	U = (GPIOA->IDR & (0x0001 << 4));
	D = (GPIOB->IDR & (0x0001 << 0));
	L = (GPIOC->IDR & (0x0001 << 1));
	R = (GPIOC->IDR & (0x0001 << 0));
	C = (GPIOB->IDR & (0x0001 << 5));

	// Center
	if(C != 0){
		IO ^= 1 << 4;
	}

	// Down
	if (D != 0){
		IO ^= 1 << 1;
	}

	// Up
	if (U != 0){
		IO ^= 1 << 0;
	}

	// Left
	if (L != 0){
		IO ^= 1 << 2;
	}

	// Right
	if (R != 0){
		IO ^= 1 << 3;
	}
	return IO;
}

int32_t readSwitches(){
	// Reads the value from shooting buttons and returns value
	int32_t p1, p2, out;

	out = 0;

	p1 = (GPIOA->IDR & (0x0001 << 5));
	p2 = (GPIOC->IDR & (0x0001 << 4));

	// Player one shot check
	if(p1 != 0){
		out += 1;
	}

	// Player two shot check
	if(p2 != 0){
		out += 2;
	}

	out ^= 0x0003;

	return out;
}


void setLED(int8_t R, int8_t G, int8_t B){
	// Set the board LED to red, green og blue
	if(R == 0){
		GPIOB->ODR |= (0x0001 << 4);
	} else {
		GPIOB->ODR &= ~(0x0001 << 4);
	}

	if(G == 0){
		GPIOC->ODR |= (0x0001 << 7);
	} else {
		GPIOC->ODR &= ~(0x0001 << 7);
	}

	if(B == 0){
		GPIOA->ODR |= (0x0001 << 9);
	} else {
		GPIOA->ODR &= ~(0x0001 << 9);
	}
}

int32_t getKey(){
	// Returns a value according to input from PuTTY
	// Function was used in earlier version of the game
	int32_t value = 0;
	char boi = uart_get_char();
	if ('w' == boi){
		value ^= 1 << 0;
	}
	if ('s' == boi){
		value ^= 1 << 1;
	}
	if ('d' == boi){
		value ^= 1 << 2;
	}
	if ('a' == boi){
		value ^= 1 << 3;
	}
	if (' ' == boi){
		value ^= 1 << 4;
	}
	uart_clear();
	return value;
}
