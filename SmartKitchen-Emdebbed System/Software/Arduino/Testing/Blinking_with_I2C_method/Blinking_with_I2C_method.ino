
// B00000000 Off
// B00000001 Green
// B00000010 Red
// B00000011 Yellow
// B00000100 Blue
// B00000101 Bright Blue
// B11111110 Purple
// B11111111 White


#define  MOD1  56
#define  MOD2  57
 
#include <Wire.h>
 
void setup()
{
  Wire.begin();                   
  deviceWrite(B11111111, MOD1);          // Set all LEDs on
  deviceWrite(B11111111, MOD2);          // Set all LEDs on
}
 
void loop()
{
  deviceWrite(B00000001, MOD1);         // Set color Green                 
  deviceWrite(B00000010, MOD2);         // Set color Red
  delay(1000);          
  deviceWrite(B00000001, MOD2);         // Set color Green                 
  deviceWrite(B00000010, MOD1);         // Set color Red
  delay(1000);  
}
 
void deviceWrite(byte txData, int Module_Address)
{
  Wire.beginTransmission(Module_Address);
  Wire.write(txData);
  Wire.endTransmission();
}
