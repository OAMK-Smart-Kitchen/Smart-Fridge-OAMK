#include <Wire.h>
byte iInput = 0;
byte iOutput = 0;

void setup() {

Wire.begin();
Serial.begin(9600);

}

void loop() {

  Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)
  Wire.write(1);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
}
