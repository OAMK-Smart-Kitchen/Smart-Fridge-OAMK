// Testing to send NFC-ID from reader to SC16IS750 over I2C to PC


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
  Wire.requestFrom(72,6);// Adres 1001 0001 (last 1 to READ) Hex is 0x91, Read 6 bytes (ID min 43 chars)
  if(Wire.available())   // If bytes are available to be recieved
  {
    iInput = Wire.read();// Read a byte
    Serial.print(iInput);
  }
}
