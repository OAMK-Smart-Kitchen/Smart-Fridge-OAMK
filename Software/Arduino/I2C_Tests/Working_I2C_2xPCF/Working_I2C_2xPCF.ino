#include <Wire.h>
 
byte iInput=0;
byte iOutput=0;
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
 
void loop()
{
  Wire.requestFrom(57,1);// Begin transmission to PCF8574 with the buttons (address: 111001)
  if(Wire.available())   // If bytes are available to be recieved
  {
    iInput = Wire.read();// Read a byte
  }
 
  if(iInput<255)         //If the value less than 255
  {
    if (iInput==254) // P0
    { 
      iOutput = 1; 
    }; 
    if (iInput==253) // P1
    { 
      iOutput = 2; 
    }; 
    if (iInput==251) // P2
    { 
      iOutput = 4; 
          Serial.println("4");
    }; 
    if (iInput==247) // P3
    { 
      iOutput = 8; 
    }; 
  }
  Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)(address: 111000)
  Wire.write(iOutput);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
}
