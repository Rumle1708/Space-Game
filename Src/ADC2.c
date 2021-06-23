/*
 * ADC2.c
 *
 *  Created on: 14 Jun 2021
 *      Author: Karl
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

void initADC(){

	// Enable clocks for input pins

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB;

	// Pin A6

	GPIOA->MODER &= ~(0x00000003 << (6 * 2));	// Clear mode register
	GPIOA->MODER |= (0x00000000 << (6 * 2)); 	// Set mode register
	GPIOA->PUPDR &= ~(0x00000003 << (6 * 2));	// Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (6 * 2));	// Set push/pull register

	// Pin A7

	GPIOA->MODER &= ~(0x00000003 << (7 * 2));	// Clear mode register
	GPIOA->MODER |= (0x00000000 << (7 * 2));	// Set mode register
	GPIOA->PUPDR &= ~(0x00000003 << (7 * 2));	// Clear push/pull register
	GPIOA->PUPDR |= (0x00000002 << (7 * 2));	// Set push/pull register

	// Pin B1

	GPIOB->MODER &= ~(0x00000003 << (1 * 2));	// Clear mode register
	GPIOB->MODER |= (0x00000000 << (1 * 2));	// Set mode register
	GPIOB->PUPDR &= ~(0x00000003 << (1 * 2));	// Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (1 * 2));	// Set push/pull register

	// Pin B11

	GPIOB->MODER &= ~(0x00000003 << (11 * 2));	// Clear mode register
	GPIOB->MODER |= (0x00000000 << (11 * 2));	// Set mode register
	GPIOB->PUPDR &= ~(0x00000003 << (11 * 2));	// Clear push/pull register
	GPIOB->PUPDR |= (0x00000002 << (11 * 2));	// Set push/pull register


	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration

	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish

	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)

	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}


uint32_t readADC(uint32_t channel){
	// Function selecting which channel of ADC to read input 1 to 4
	switch(channel){
	case 1:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_1Cycles5);
		break;
	case 2:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_1Cycles5);
		break;
	case 3:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_1Cycles5);
		break;
	case 4:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_1Cycles5);
		break;
	}

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	return ADC_GetConversionValue(ADC1); // Read the ADC value
}
