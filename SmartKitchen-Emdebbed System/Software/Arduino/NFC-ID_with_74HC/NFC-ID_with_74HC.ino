#include <Wire.h>
 
byte iInput=0;
byte iOutput=0;
char Send;

// NFC
int incomingByte = 0;   // for incoming serial data
String productID = "";
String tempString = "";
int minLengthID = 40;  // minimale lengte van NFC-tag ID

// NFC-ID's
const String Banana = "1188611854245125125125141153151143159229235";
const String Cucumber = "118150150205245125125125141153151143159229235";
const String Vegetables = "95951741188653153229235095951741188653153229235";
const String Milk = "1185424654237125125125141153151143159229235";
const String Ketchup = "11824610854245125125125141153151143159229235";
const String PhoneTom = "21424618224615024611886235021424618224615024611886235";
const String PhoneHenry = "21424618224615024611886235021424618224615024611886235"; 


void setup()
{
  //Wire.begin();
  Serial.begin(9600);
}
 
void loop()
{
  Wire.beginTransmission(56);  //Begin transmission to PCF8574 to activate RX (address: 111010)
  Wire.write(1);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
  //Send = Serial.read();
 // Serial.print(Send);
  //delay(100);
  // ----- NFC-Tag Detection -----
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 0 && productID.length() >= minLengthID)
    {
      Serial.print("NFC-ID: ");
      // Software on computer will do this in futere (Database)
      if (productID == Banana)
      {
        Serial.println("Banana");
      }
      else if (productID == Cucumber)
      {
        Serial.println("Cucumber");
      }
      else if (productID == Vegetables)
      {
        Serial.println("Box with vegetables");
      }
      else if (productID == Milk)
      {
        Serial.println("Milk");
      }
      else if (productID == Ketchup)
      {
        Serial.println("Ketchup");
      }
      else
      {
        Serial.println(productID);
      }
      productID = "";
    }
    else
    {
      tempString = String(incomingByte);
      productID = productID + tempString;

    }
    }
    // ----- End NFF-Tag detection -----
}
