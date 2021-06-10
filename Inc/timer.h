/*
 * timer.h
 *
 *  Created on: 8 Jun 2021
 *      Author: Mads Rumle Nordstrom
 */

#ifndef TIMER_H_
#define TIMER_H_

void initTimer();
void updateClock();
void splitTime();
void TIM2_IRQHandler(void);


#endif /* TIMER_H_ */
