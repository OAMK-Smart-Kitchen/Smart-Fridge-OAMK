#include <Wire.h>
byte iInput = 0;
byte iOutput = 0;
int incomingByte = 0; 
void setup() {

Wire.begin();
Serial.begin(9600);

}

void loop() {

  Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)
  Wire.write(0);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
   incomingByte = Serial.read();
   Serial.println(incomingByte);
}
