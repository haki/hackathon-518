#include "lcd.h"
#include "dht11.h"
#include "stepmotor.h"
#include "keypad.h"
#include "clock.h"
#include "statedevice.h"
#include <SoftwareSerial.h>

#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13

#define FAN_OUT 42
#define HOT_OUT 44

#define ESP_RX 15
#define ESP_TX 14

SoftwareSerial espSerial(ESP_RX, ESP_TX);

boolean bfan_state;
boolean bhot_state;
boolean bstep_mot;
unsigned int OldTime;
unsigned int IntervalTime;
unsigned int Presscaller;

void setup(){
    Serial.begin(115200);
    espSerial.begin(115200);
    
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
    bstep_mot=true;
    IntervalTime=0;
    Presscaller=0;
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
    if(Presscaller<999)Presscaller++;
    else{
      Presscaller=0;
      espSerial.println(u8CurHum);
      //OldTime=0;
    }
    if(Presscaller==500)
    {
      espSerial.println(u8CurTemp);
      //OldTime=0;
    }
    delay(5);
    
    // Fan State Control
    if(!bfan_state )
    {
      if(u8HumHi<=u8CurHum )
      {
        bfan_state=true;
        digitalWrite(FAN_OUT, HIGH);
      }
    }
    else
    {
      if(u8HumLo>=u8CurHum )
      {
        bfan_state=false;
        digitalWrite(FAN_OUT, LOW);
      }
    }

    // Hot State Control
    if(!bhot_state )
    {
      if(u8TempLo>=u8CurTemp)
      {
        bhot_state=true;
        digitalWrite(HOT_OUT, HIGH);
      }
    }
    else
    {
      if(u8TempHi<=u8CurTemp )
      {
        bhot_state=false;
        digitalWrite(HOT_OUT, LOW);
      }
    }

    if(cAlarmPeriodTime>0)
    {
        if(OldTime!=currentTime)
        {
          IntervalTime++;
          if(IntervalTime==AlarmPeriodTime)
          {
            IntervalTime=0;
            lcd_write(1, 10, "Ocupat");
            step_left(1050);
            lcd_write(1, 10, "Astept");
          }
        }
    }
    else
    {
      if((!bstep_mot)&&((currentTime==AlarmTime1)||(currentTime==AlarmTime2)||(currentTime==AlarmTime3)))
      {
        bstep_mot=true;
        lcd_write(1, 10, "Ocupat");
        step_left(1050);
        lcd_write(1, 10, "Astept");
      }
      else
      {
        bstep_mot=false;
      }
    }
    OldTime=currentTime;
  }
}
