// =====================================================================
//
//	Exported by Cearn's excellut v1.0
//	(comments, kudos, flames to daytshen@hotmail.com)
//
// =====================================================================
#include "30010_io.h" 		// Input/output library for this course
#ifndef LUT_H
#define LUT_H
int32_t sinus(int32_t angle);
int32_t cosinus(int32_t angle);
int32_t degCon(int32_t angle);
int32_t expand(int32_t i);
int32_t unexpand(int32_t i);
void printFix(int32_t i);

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

#endif	// LUT_H
