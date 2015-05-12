
// B00000000 Off
// B00000001 Green
// B00000010 Red
// B00000011 Yellow
// B00000100 Blue
// B00000101 Bright Blue
// B11111110 Purple
// B11111111 White

// Adresses:
#define  MOD1  56
#define  MOD2  57
#define  MOD3  58
#define  MOD4  59
#define  MOD5  60
#define  MOD1_R  61
#define  MOD2_R  62
#define  MOD3_R  63
#define  MOD4_R  64
#define  MOD5_R  65

// Colors:
#define Off B00000000
#define Read B00000001
#define Green B00000001
#define Red B00000010
#define Yellow B00000011
#define Blue B00000100
#define BrightBlue B00000101
#define Purple B11111110
#define White B11111111


#include <Wire.h>

void setup()
{
  Wire.begin();
  deviceWrite(B00000000, MOD1);          // Set all LEDs on
  deviceWrite(B00000000, MOD2);          // Set all LEDs on
}

void loop()
{
  deviceWrite(B00000000, MOD1_R);         // Set color Green
  //deviceWrite(B00000010, MOD2);         // Set color Red
  delay(1000);
  //deviceWrite(B00000001, MOD2);         // Set color Green
  deviceWrite(B00000001, MOD1_R);         // Set color Red
  delay(1000);
}

void deviceWrite(byte txData, int Module_Address)
{
  Wire.beginTransmission(Module_Address);
  Wire.write(txData);
  Wire.endTransmission();
}
