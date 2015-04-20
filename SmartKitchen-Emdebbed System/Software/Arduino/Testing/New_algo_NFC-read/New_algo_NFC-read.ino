// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
 */

// NFC
int incomingByte = 0;   // for incoming serial data
String productID = "";
String tempString = "";
int minLengthID = 40;  // minimale lengte van NFC-tag ID

// NFC-ID's
const String StartRef = "191183";
const String Banana = "1188611854245125125125141153151143159229235";
const String Cucumber = "118150150205245125125125141153151143159229235";
const String Vegetables = "95951741188653153229235095951741188653153229235";
const String Milk = "1185424654237125125125141153151143159229235";
const String Ketchup = "118246147115125159125125141153151143159229235";
const String NokiaID = "1019417886611451252292350101941788661145125229235";
const String PhoneTom = "21424618224615024611886235021424618224615024611886235";
const String PhoneHenry = "21424618224615024611886235021424618224615024611886235";

/*
#define RGB_ADDRESS_M1 57
#define RGB_ADDRESS_M2
#define RGB_ADDRESS_M3
#define RGB_ADDRESS_M4
#define RGB_ADDRESS_M5
*/

// LED - driver
#include <Wire.h>
byte iInput = 0;
byte iOutput = 0;

void setup() {
  // Serials
  Serial.begin(9600);

  //I2C
  Wire.begin();
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
    incomingByte = Serial.read();
    /*if (productID == StartRef)
    {
      Serial.print("NFC-ID: ");
      // Software on computer will do this in futere (Database) /*
      if (productID == Banana)
      {
        Serial.println("Banana");
      }
      else if (productID == Cucumber)
      {
        Serial.println("Cucumber");
        iOutput = 2;
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
        iOutput = 1;
      }
      else if (productID == NokiaID)
      {
        Serial.println("Why is there a Nokia in your fridge?");
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
*/
Serial.print(incomingByte);

/*tempString = String(incomingByte);
productID = productID + tempString;
if (productID == StartRef)
    {Serial.println('YES');}
*/
}


}





