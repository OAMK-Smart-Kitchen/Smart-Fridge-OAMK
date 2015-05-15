#include <Wire.h>
byte iInput = 0;
byte iOutput = 0;
int incomingByte = 0;

#define green 1
#define red 2
#define grbl 3
#define blue 4
#define purple 6
#define white 7


void setup() {

  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  for (int i = 1; i < 8; i++)  {
    Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)
    Wire.write(i);         //Send data to PCF8574 (with the LEDs)
    Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
    delay(1000);
  }

  //incomingByte = Serial.read();
  //Serial.print(incomingByte);
  //delay(1000);

}
