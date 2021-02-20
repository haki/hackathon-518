#ifndef keypad_h
#define keypad_h
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

boolean state = true;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {19,22, 24, 26}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {25, 27, 29, 31}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

char read_key();
void init_keypad() {
  Serial.begin(9600);
}

char read_key() {
  return keypad.getKey();
}
#endif
