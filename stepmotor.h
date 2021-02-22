#define pinA 50
#define pinB 49
#define pinC 51
#define pinD 52

int loc;
int wait;
int stepPins[4] = {pinA, pinB, pinC, pinD};
int Steps[8]={
  0x01,
  0x03,
  0x02,
  0x06,
  0x04,
  0x0C,
  0x08,
  0x09
};



void stepmotor_init() {
  for(int i=0; i<sizeof(stepPins)/sizeof(stepPins[0]); i++) {
    pinMode(stepPins[i], OUTPUT);
    digitalWrite(stepPins[i], LOW);
  }

  loc = 0;
  wait = 1;
}

void inc_loc();
void step_left(int step) {
  for (int i=0; i<step; i++){
    if(Steps[loc&7]&0x01)digitalWrite(pinA, HIGH); else digitalWrite(pinA, LOW);
    if(Steps[loc&7]&0x02)digitalWrite(pinB, HIGH); else digitalWrite(pinB, LOW);
    if(Steps[loc&7]&0x04)digitalWrite(pinC, HIGH); else digitalWrite(pinC, LOW);
    if(Steps[loc&7]&0x08)digitalWrite(pinD, HIGH); else digitalWrite(pinD, LOW);
    inc_loc();
    delay(wait);
     /*digitalWrite(stepPins[loc], HIGH);
     delay(wait);
     digitalWrite(stepPins[loc], LOW);
     inc_loc();*/
  }  
}

void inc_loc() {
  loc++;
  //if (loc == 4) loc = 0;
}

void dec_loc();
void step_right(int step) {
  for (int i=0; i<step; i++){
    if(Steps[loc&7]&0x01)digitalWrite(pinA, HIGH); else digitalWrite(pinA, LOW);
    if(Steps[loc&7]&0x02)digitalWrite(pinB, HIGH); else digitalWrite(pinB, LOW);
    if(Steps[loc&7]&0x04)digitalWrite(pinC, HIGH); else digitalWrite(pinC, LOW);
    if(Steps[loc&7]&0x08)digitalWrite(pinD, HIGH); else digitalWrite(pinD, LOW);
    inc_loc();
    delay(wait);
     /*digitalWrite(stepPins[loc], HIGH);
     delay(wait);
     digitalWrite(stepPins[loc], LOW);
     dec_loc();*/
  }  
}

void dec_loc() {
  loc--;
  if(loc == -1) loc = 3;
}

void half_step_right(int step) {
  for (int i=0; i<step; i++){
    if(Steps[loc&7]&0x01)digitalWrite(pinA, HIGH); else digitalWrite(pinA, LOW);
    if(Steps[loc&7]&0x02)digitalWrite(pinB, HIGH); else digitalWrite(pinB, LOW);
    if(Steps[loc&7]&0x04)digitalWrite(pinC, HIGH); else digitalWrite(pinC, LOW);
    if(Steps[loc&7]&0x08)digitalWrite(pinD, HIGH); else digitalWrite(pinD, LOW);
    inc_loc();
    delay(wait);
    /* digitalWrite(stepPins[loc], HIGH);
     dec_loc();
     digitalWrite(stepPins[loc], HIGH);
     inc_loc();
     delay(wait);
     digitalWrite(stepPins[loc], LOW);
     dec_loc();
     delay(wait);*/
  }  
}

void half_step_left(int step) {
  for (int i=0; i<step; i++){
    if(Steps[loc&7]&0x01)digitalWrite(pinA, HIGH); else digitalWrite(pinA, LOW);
    if(Steps[loc&7]&0x02)digitalWrite(pinB, HIGH); else digitalWrite(pinB, LOW);
    if(Steps[loc&7]&0x04)digitalWrite(pinC, HIGH); else digitalWrite(pinC, LOW);
    if(Steps[loc&7]&0x08)digitalWrite(pinD, HIGH); else digitalWrite(pinD, LOW);
    delay(wait);
   /*  digitalWrite(stepPins[loc], HIGH);
     inc_loc();
     digitalWrite(stepPins[loc], HIGH);
     dec_loc();
     delay(wait);
     digitalWrite(stepPins[loc], LOW);
     inc_loc();
     delay(wait);*/
  }  
}
