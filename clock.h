#include "lcd.h"

#ifndef clock_h
#define clock_h

#include <DS3231.h>

#define MaxTime 1440

uint16_t AlarmTime1;
uint16_t AlarmTime2;
uint16_t AlarmTime3;
uint16_t AlarmPeriodTime;

const uint16_t cAlarmTime1= 1;
const uint16_t cAlarmTime2 = 2;
const uint16_t cAlarmTime3 = 3;
const uint16_t cAlarmPeriodTime = 1;

uint8_t alarmMinutes = 0;
uint16_t currentTime = 0;
uint16_t SetTime = 0;

#define SDA 20
#define SCL 21

DS3231  rtc(20, 21);

void ClockInit() {
  AlarmTime1=cAlarmTime1;
  AlarmTime2=cAlarmTime2;
  AlarmTime3=cAlarmTime3;
  AlarmPeriodTime=cAlarmPeriodTime;
  rtc.begin();
}

uint16_t GetClock() {
  Time myTime;
  unsigned int l_time;
  myTime = rtc.getTime();
  l_time =  (unsigned int )myTime.hour * 60 ;
  l_time += myTime.min  ;
  return l_time;
}

#endif
