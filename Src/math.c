#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "main.h"



// Approximates a fixed point number to the nearest integer
int32_t approxShift14(int32_t n){
	int32_t temp = n;

	n &= ~(0x3FFF);

	//Resets all decimal bits of number

	n >>= FIX14_SHIFT;

	//Shifts real part

	temp &= ~(0xFFFFC000);

	// Resets all non-decimal bits

	if(temp >= 0x2000){
		n++;
	}

	// Checks if decimal part is over 0.5

	return n;
}
