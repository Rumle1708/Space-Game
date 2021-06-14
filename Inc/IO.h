/*
 * IO.h
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef IO_H_
#define IO_H_

void initIOJoystick();
void initIOLED();
int32_t readJoystick();
void setLED(int32_t R, int32_t G, int32_t B);
int32_t getKey();

#endif /* IO_H_ */
