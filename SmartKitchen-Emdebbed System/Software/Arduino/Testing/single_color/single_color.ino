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
    Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)
    Wire.write(3);         //Send data to PCF8574 (with the LEDs)
    Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
    
//      Wire.beginTransmission(57);  //Begin transmission to PCF8574 (with the LEDs)
//    Wire.write(2);         //Send data to PCF8574 (with the LEDs)
//    Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)

}
