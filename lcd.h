#ifndef lcd_h
#define lcd_h
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

void lcd_init() {
    lcd.begin(16, 2);
}

void lcd_write(int x, int y, String text) {
  lcd.setCursor(y, x);
  lcd.print(text);
}

void lcd_write_time(int x, int y, unsigned int time_num)
{
  char str[6];
  str[0]=time_num/600+'0';
  str[1]=(time_num%600)/60+'0';
  str[2]=':';
  str[3]=(time_num%60)/10+'0';
  str[4]=(time_num%10)+'0';
  str[5]=0;
  lcd.setCursor(y, x);
  lcd.print(str);
}

void lcd_clear()
{
  lcd.setCursor(0,0);
  lcd.print("                                ");
}

#endif
