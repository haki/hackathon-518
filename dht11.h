#include "lcd.h"

#ifndef dht11_h
#define dht11_h

#include <DHT.h>

#define DHTPIN 4          // what digital pin we're connected to
#define DHTTYPE DHT11     // DHT11


const uint8_t cu8TempHi = 25;
const uint8_t cu8TempLo = 19;

const uint8_t cu8HumHi = 50;
const uint8_t cu8HumLo = 40;


uint8_t u8TempHi;
uint8_t u8TempLo;
uint8_t u8CurTemp;
uint8_t u8SetTemp;

uint8_t u8HumHi;
uint8_t u8HumLo;
uint8_t u8CurHum;
uint8_t u8SetHum;

DHT dht(DHTPIN, DHTTYPE);

void dht_run();
void dht_init() {
  u8TempLo=cu8TempLo;
  u8TempHi=cu8TempHi;
  u8HumHi = cu8HumHi;
  u8HumLo = cu8HumLo;
  dht.begin();
}

void dht_run() {
    u8CurHum = dht.readHumidity();
    u8CurTemp = dht.readTemperature();
}

#endif
