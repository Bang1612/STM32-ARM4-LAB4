/*
 * clock.h
 *
 *  Created on: Nov 30, 2024
 *      Author: MY PC
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#define NORMAL 0
#define CALIBRATE 1
#define SET_ALARM 2

extern int counter;
#include "lcd.h"
#include "ds3231.h"
#include "button.h"
#include "software_timer.h"

extern uint8_t cal_hour;
extern uint8_t cal_min;
extern uint8_t cal_sec;
extern uint8_t cal_date;
extern uint8_t cal_day;
extern uint8_t cal_month;
extern uint8_t cal_year;

extern uint8_t al_hours;
extern uint8_t al_min;
extern uint8_t al_sec;

void fsm(uint16_t status);
void CalibrateInit();
#endif /* INC_CLOCK_H_ */
