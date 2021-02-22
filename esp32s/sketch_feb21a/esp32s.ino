#include "config.h"
#include <SoftwareSerial.h>

String lastU="";
String lastT="";

boolean tipData = true;

AdafruitIO_Feed *umeditate = io.feed("umedidate");
AdafruitIO_Feed *temperatura = io.feed("temperatura");

void setup() {
  Serial.begin(115200); 
  
  pinMode (LED_BUILTIN, OUTPUT);
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();

String data = Serial.readString();
  
  if (data.length() >= 1 ) {
   if(tipData) {
      Serial.print("T: ");
      Serial.println(data);
  
      temperatura->save(data);  
      tipData = false;
      
    } else {
      Serial.print("U: ");
      Serial.println(data);
      
      umeditate->save(data);
      tipData = true;
    }  
  }
}
