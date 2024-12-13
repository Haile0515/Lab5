/*
 * timerSetting.h
 *
 *  Created on: Sep 25, 2024
 *      Author: ADMIN
 */
#include "main.h"

#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_

extern int timer1_flag;
extern int timer2_flag;

void setTimer1(int duration);
void setTimer2(int duration);

void timerRun();

#endif /* INC_SOFTWARETIMER_H_ */
