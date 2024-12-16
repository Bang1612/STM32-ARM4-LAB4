/*
 * clock.c
 *
 *  Created on: Nov 30, 2024
 *      Author: MY PC
 */

#include "clock.h"
int counter=0;
int temp=0;
int flag=0;
 uint8_t cal_hour;
 uint8_t cal_min;
 uint8_t cal_sec;
 uint8_t cal_date;
 uint8_t cal_day;
 uint8_t cal_month;
 uint8_t cal_year;

 uint8_t al_hours;
 uint8_t al_min;
 uint8_t al_sec;
char* update_value[6] = {"seconds", "minutes", "hours", "days", "months", "years"};
void CalibrateInit(){
	cal_hour=ds3231_hours;
	cal_min=ds3231_min;
	cal_sec=ds3231_sec;
	cal_day=ds3231_day;
	cal_date=ds3231_date;
	cal_month=ds3231_month;
	cal_year=ds3231_year;
}

void ChangeValue(int val){
	switch(val){
	case 0:
		cal_sec++;
		if(cal_sec > 59) cal_sec=0;
		break;
	case 1:
		cal_min++;
		if(cal_min > 59) cal_min=0;
		break;
	case 2:
		cal_hour++;
		if(cal_hour > 23) cal_hour =0;
		break;
	case 3:
		cal_day++;
		cal_date++;
		if(cal_day >28){
			if(cal_month ==2){
				if(cal_year%4 !=0){
					cal_day=1;
				}
				else{
					if(cal_day >29) cal_day=0;
				}
			}
		}
		else if(cal_month==4 || cal_month==6 || cal_month==9 || cal_month==11){
			if(cal_day > 30) cal_day=0;
		}
		else{
			if(cal_day>31) cal_day=0;
		}
		if(cal_date>8) cal_date=2;

		break;
	case 4:
		cal_month++;
		if(cal_month>12) cal_month=1;
		break;
	case 5:
		cal_year++;
		break;
	default:
		break;
	}
}

void ApplyChange(){
		ds3231_Write(ADDRESS_SEC, cal_sec);
		ds3231_Write(ADDRESS_MIN, cal_min);
		ds3231_Write(ADDRESS_HOUR, cal_hour);
		ds3231_Write(ADDRESS_DAY, cal_day);
		ds3231_Write(ADDRESS_DATE, cal_date);
		ds3231_Write(ADDRESS_MONTH, cal_month);
		ds3231_Write(ADDRESS_YEAR, cal_year);
}

void ChangeAlarm(){
	switch (counter) {
	case 0:
		al_sec++;
		if(al_sec > 59) al_sec=0;
		break;
	case 1:
		al_min++;
		if(al_min >59) al_min=0;
		break;
	case 2:
		al_hours++;
		if(al_hours >23) al_hours=0;
		break;
	default:
		break;
	}
}

void fsm(uint16_t status){
	switch(status){
	case NORMAL:
		ds3231_ReadTime();
		displayTime();
		lcd_StrCenter(10, 20, "NORMAL", BLUE, YELLOW, 16, 0);
		if (ds3231_hours == al_hours && ds3231_min == al_min
				&& ds3231_sec == al_sec) {
			flag=1;
		}
		if(flag){
			lcd_StrCenter(10, 60, "ALARM", RED, YELLOW, 16, 0);
		}
		if(button_count[0] || button_count[14]){
			flag=0;
		}
		break;
	case CALIBRATE:
		char title[50] ="Updating ";
		strcat(title, update_value[counter]);
		strcat(title,"...");
		if (button_count[3] == 1) {
			ChangeValue(counter);
		}

		if (button_count[3] == 40) {
			setTimer3(200);
			ChangeValue(counter);
		}
		if (flag_timer3 && button_count[3] > 40) {
			setTimer3(200);
			ChangeValue(counter);
		}



		if(button_count[12] == 1){
			ApplyChange();
			counter++;
			ds3231_ReadTime();
			if(counter>5) counter =0;

		}
		lcd_StrCenter(10, 20, title, BLUE, YELLOW, 16, 0);
		break;
	case SET_ALARM:
		if (button_count[3] == 1) {
			ChangeAlarm(counter);
		}

		if (button_count[3] == 40) {
			setTimer3(200);
			ChangeAlarm(counter);
		}
		if (flag_timer3 && button_count[3] > 40) {
			setTimer3(200);
			ChangeAlarm(counter);
		}
		if(button_count[12] == 1){
			counter++;
			if(counter>2) counter =0;
		}
		lcd_StrCenter(10, 20, "SET ALARM", BLUE, YELLOW, 16, 0);
		break;
	default:
		break;
	}
}




