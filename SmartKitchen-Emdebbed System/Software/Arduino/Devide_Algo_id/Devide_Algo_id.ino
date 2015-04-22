// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
506'th try to get the ID out of the string.
 */

#include <Wire.h>

// NFC
int incomingByte = 0;   // for incoming serial data
String productID = "";
String tempString = "";
int minLengthID = 40;  // minimale lengte van NFC-tag ID
bool acquaintance = false;

char charBuf[100];
bool ReadNFC = true;

// NFC-ID's
const String StartRef = "4852";
const String Banana = "5352706548656557515256481310";
const String Cucumber = "5167706548656557515256481310";
const String Vegetables = "95951741188653153229235095951741188653153229235";
const String Milk = "1185424654237125125125141153151143159229235";
const String Ketchup = "118246147115125159125125141153151143159229235";
const String NokiaID = "1019417886611451252292350101941788661145125229235";
const String PhoneTom = "21424618224615024611886235021424618224615024611886235";
const String PhoneHenry = "21424618224615024611886235021424618224615024611886235";


void setup() {
  // Serials
  Serial.begin(9600);

  //I2C
  Wire.begin();
  Wire.write(0);
}

void loop()
{

  // ----- Switch-control -----
  Wire.beginTransmission(57);  //Begin transmission to PCF8574 to activate RX (address: 111010)
  Wire.write(1);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
  // ----- End Switch-control -----



  // ----- NFC-Tag Detection -----
  if (Serial.available() > 0) {
    //productID = "S";
    //Serial.print(incomingByte);
    for (int i = 0; i <= 100; i++)
    {
      incomingByte = Serial.read();
      tempString = String(incomingByte);
      productID += tempString;
    }
    //productID = productID + "E";
    Serial.println(productID);
 
  productID.toCharArray(charBuf, 100);
  productID = "";
  ReadNFC = false;
  }
  int count = sizeof(charBuf); 

  for (int i = 6; i <= count; i++)
  {
    String a = "";
    String b = "";

    for (int j = 0; j < i; j++)
    {
      a += charBuf[j];
    }
    
    for (int j = 0; j < i; j++)
    {
      if (j+i < count)
      {
      b += charBuf[j + i];
      }
    }
    if(a == b)
    {
      Serial.println(a);
    }
  }
}






