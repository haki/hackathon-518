#include "lcd.h"
#include "dht11.h"
#include "stepmotor.h"
#include "keypad.h"
#include "clock.h"
#include "statedevice.h"

#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13

#define FAN_OUT 42
#define HOT_OUT 44

boolean bfan_state;
boolean bhot_state;

void setup(){
    Serial.begin(9600);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(HOT_OUT, OUTPUT);
    pinMode(FAN_OUT, OUTPUT);

    init_keypad();
    
    lcd_init();
    dht_init();
    stepmotor_init();
    ClockInit();
    StateDeviceInit();
    bfan_state=false;
    bhot_state = false;
}

char key;
void loop() 
{
  
  dht_run();
  StateDeviceSwitch();
  if(eStateDevice == MAIN_LOOP)
  {
    lcd.setCursor(0,1);
    lcd.print("H:");
    lcd.print(u8CurHum);
    lcd.print("%");

    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(u8CurTemp);
    lcd.print("C");
    currentTime = GetClock();
    lcd_write_time(0,8,currentTime);
    lcd_write(1, 10, "Astept");
    delay(5);
    
    // Fan State Control
    if(!bfan_state )
    {
      if(u8HumHi>=u8CurHum )
      {
        bfan_state=true;
        digitalWrite(FAN_OUT, HIGH);
      }
    }
    else
    {
      if(u8HumLo<=u8CurHum )
      {
        bfan_state=false;
        digitalWrite(FAN_OUT, LOW);
      }
    }

    // Hot State Control
    if(!bhot_state )
    {
      if(u8TempHi>=u8CurTemp)
      {
        bhot_state=true;
        digitalWrite(HOT_OUT, HIGH);
      }
    }
    else
    {
      if(u8TempLo<=u8CurTemp )
      {
        bhot_state=false;
        digitalWrite(FAN_OUT, LOW);
      }
    }
  }
}
