#include "keypad.h"
#include "lcd.h"
#include "clock.h"
#include "string.h"

#ifndef statedevice_h
#define statedevice_h


uint16_t SetHour(uint16_t set_hour, char push_key);
uint8_t  SerTemprHum(uint8_t set_par, char push_key);

enum STATEDEVISE { MAIN_LOOP=0, SET_CLK_HOUR, SET_CLK_ALRM1, SET_CLK_ALRM2, SET_CLK_ALRM3, SET_CLK_PERIOD, SET_TMPR_HI,SET_TMPR_LO,SET_HUM_HI,SET_HUM_LO};
STATEDEVISE eStateDevice;
uint8_t pozSet;

void StateDeviceInit() 
{
  eStateDevice = MAIN_LOOP;
  pozSet=0;
}


void StateDeviceSwitch() 
{
  char key = read_key();
  char str[8];
  char tmp;

  if (key)
  {
    switch(eStateDevice) 
    {
      case MAIN_LOOP:
        if (key == 'A') 
        {
          lcd_clear();
          lcd_write(0, 0, "Setup Hour");
          SetTime= GetClock();
          lcd_write_time(1,0,SetTime);
          eStateDevice = SET_CLK_HOUR;
          pozSet=0;
        }else if (key == 'B') 
        {
          lcd_clear();
          lcd_write(0, 0, "Setup Alarm1");
          SetTime= AlarmTime1;
          lcd_write_time(1,0,SetTime);
          eStateDevice = SET_CLK_ALRM1;
          pozSet=0;
        }else if (key == 'C') 
        {
          lcd_clear();
          lcd_write(0, 0, "Temperature high");
          u8SetTemp= u8TempHi;
          lcd.setCursor(0,1);
          lcd.print("T:");
          lcd.print(u8SetTemp);
          lcd.print("C");
          eStateDevice = SET_TMPR_HI;
          pozSet=0;
        }else if (key == 'D') 
        {
          lcd_clear();
          lcd_write(0, 0, "Humidity    high");
          u8SetHum= u8HumHi;
          lcd.setCursor(0,1);
          lcd.print("H:");
          lcd.print(u8SetHum);
          lcd.print("%");
          eStateDevice = SET_HUM_HI;
          pozSet=0;
        }
        
        break;
        
      case SET_CLK_HOUR:
        if ((key >= '0')&&(key <= '9')) 
        {
          SetTime=SetHour(SetTime,key);
          lcd_write_time(1,0,SetTime);
        }else if (key == '*')
        {
          lcd_clear();
          rtc.setTime(SetTime/60,SetTime%60,0);
          eStateDevice = MAIN_LOOP;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      case SET_CLK_ALRM1:
        if ((key >= '0')&&(key <= '9')) 
        {
          SetTime=SetHour(SetTime,key);
          lcd_write_time(1,0,SetTime);
        }else if (key == '*')
        {
          lcd.clear();
          AlarmTime1=SetTime;
          SetTime= AlarmTime2;
          lcd_write_time(1,0,SetTime);
          lcd_write(0, 0, "Setup Alarm2");
          eStateDevice = SET_CLK_ALRM2;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      case SET_CLK_ALRM2:
        if ((key >= '0')&&(key <= '9')) 
        {
          SetTime=SetHour(SetTime,key);
          lcd_write_time(1,0,SetTime);
        }else if (key == '*')
        {
          AlarmTime2=SetTime;
          lcd_clear();
          SetTime= AlarmTime3;
          lcd_write_time(1,0,SetTime);
          lcd_write(0, 0, "Setup Alarm3");
          
          eStateDevice = SET_CLK_ALRM3;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
  
      case  SET_CLK_ALRM3:
        if ((key >= '0')&&(key <= '9')) 
        {
          SetTime=SetHour(SetTime,key);
          lcd_write_time(1,0,SetTime);
        }else if (key == '*')
        {
          lcd_clear();
          AlarmTime3=SetTime;
          SetTime= AlarmPeriodTime;
          lcd_write_time(1,0,SetTime);
          lcd_write(0, 0, "Setup Period");
          eStateDevice = SET_CLK_PERIOD;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      case SET_CLK_PERIOD:
        if ((key >= '0')&&(key <= '9')) 
        {
          SetTime=SetHour(SetTime,key);
          itoa(SetTime /60,str,10);
          lcd_write(1, 0, str);
          lcd_write(1, 2, ":");
          itoa(SetTime %60,str,10);
          lcd_write(1, 3, str);
        }else if (key == '*')
        {
          lcd_clear();
          AlarmPeriodTime=SetTime;
          eStateDevice = MAIN_LOOP;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
      
        break;
        
      case SET_TMPR_HI:
        if ((key >= '0')&&(key <= '9')) 
        {
          u8SetTemp=SerTemprHum(u8SetTemp,key);
          lcd.setCursor(0,1);
          lcd.print("T:");
          lcd.print(u8SetTemp);
          lcd.print("C");
        }else if (key == '*')
        {
          lcd_clear();
          u8TempHi=u8SetTemp;

          lcd_clear();
          lcd_write(0, 0, "Temperature low ");
          u8SetTemp= u8TempLo;
          lcd.setCursor(0,1);
          lcd.print("T:");
          lcd.print(u8SetTemp);
          lcd.print("C");
          eStateDevice = SET_TMPR_LO;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      case SET_TMPR_LO:
        if ((key >= '0')&&(key <= '9')) 
        {
          u8SetTemp=SerTemprHum(u8SetTemp,key);
          lcd.setCursor(0,1);
          lcd.print("T:");
          lcd.print(u8SetTemp);
          lcd.print("C");
        }else if (key == '*')
        {
          lcd_clear();
          u8TempLo=u8SetTemp;
          eStateDevice = MAIN_LOOP;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = SET_TMPR_LO;
        }
        break;
        
      case SET_HUM_HI:
        if ((key >= '0')&&(key <= '9')) 
        {
          u8SetHum=SerTemprHum(u8SetHum,key);
          lcd.setCursor(0,1);
          lcd.print("H:");
          lcd.print(u8SetHum);
          lcd.print("%");
        }else if (key == '*')
        {
          lcd_clear();
          u8HumHi=u8SetHum;

          lcd_clear();
          lcd_write(0, 0, "Humidity    low");
          u8SetHum= u8HumLo;
          lcd.setCursor(0,1);
          lcd.print("H:");
          lcd.print(u8SetHum);
          lcd.print("%");
          eStateDevice = SET_HUM_LO;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      case SET_HUM_LO:
        if ((key >= '0')&&(key <= '9')) 
        {
          u8SetHum=SerTemprHum(u8SetHum,key);
          lcd.setCursor(0,1);
          lcd.print("H:");
          lcd.print(u8SetHum);
          lcd.print("%");
        }else if (key == '*')
        {
          lcd_clear();
          u8HumLo=u8SetHum;

          lcd_clear();

          eStateDevice = MAIN_LOOP;
        }
        else if (key == '#')
        {
          lcd_clear();
          eStateDevice = MAIN_LOOP;
        }
        break;
        
      default:
        break;
    }
  }
}
uint16_t SetHour(uint16_t set_hour, char push_key)
{
  char tmp;
  switch(pozSet)
  {
    case 0:
      if(push_key<'3')
      {
        set_hour=(set_hour%600)+(push_key - '0')*600;
        pozSet=1;
      }
      break;
   case 1: 
      tmp=(set_hour/600);
      Serial.print(tmp);
      if(tmp==2)
      {
          if(push_key<'4')
          {
            set_hour=(set_hour%60)+(push_key - '0')*60+ tmp*600;
            pozSet=2;
          }
      }
      else
      {
        set_hour=(set_hour%60)+(push_key - '0')*60+ tmp*600;
        pozSet=2;
      }
      Serial.print(set_hour);
   break;
   case 2: 
    if(push_key<'6')
    {
      tmp=set_hour/60;
      set_hour=set_hour-(set_hour%60)+(push_key - '0')*10+(set_hour%10);
      pozSet=3;
    }
   break;
   case 3:
    set_hour=set_hour-(set_hour%10)+(push_key - '0');
    pozSet=0;
   break;
  }
  return set_hour;
}

uint8_t  SerTemprHum(uint8_t set_par, char push_key)
{
  switch(pozSet)
  {
    case 0:
      set_par=(set_par%10)+(push_key - '0')*10;
      pozSet=1;
    break;
    case 1:
      set_par=set_par-(set_par%10)+(push_key - '0');
      pozSet=0;
    break;
    default:
      pozSet=0;
    break;
  }
  return set_par;
}
#endif
