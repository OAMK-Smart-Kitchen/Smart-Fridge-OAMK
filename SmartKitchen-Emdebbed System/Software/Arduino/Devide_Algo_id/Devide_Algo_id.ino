// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
506'th try to get the ID out of the string.
 */

#include <Wire.h>

// NFC

int incomingByte = 0;         // for incoming serial data
char charBuf[100];
String incomingString = "";
String tempString = "";
int LengthBuffer = 100;
bool ReadNFC = true;
int count = 100;
String productID = "";

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
  Wire.beginTransmission(57);        //Begin transmission to PCF8574 to activate RX-switch (address: 111001)
  Wire.write(1);                     //Send data to PCF8574 to activate the switch
  Wire.endTransmission();            //End Transmission to PCF8574
  // ----- End Switch-control -----


  // ----- NFC-Tag Detection -----

  //productID = "S";
  for (int i = 0; i <= LengthBuffer; i++)            // Put incomingbytes in a string of 100 chars
  {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      tempString = String(incomingByte);
      incomingString += tempString;
    }
    //productID = productID + "E";

  }
  incomingString.toCharArray(charBuf, LengthBuffer);  // Put incomingString (size 100) in char array (100)
  incomingString = "";
  int count = sizeof(charBuf);

  for (int i = 6; i <= count; i++)     // Devide the char array in 'boxes' (Starting with 6 because ID never is shorter)
  {


    String boxA = "";
    String boxB = "";


    // Box A
    for (int j = 0; j < i; j++)       // Make the first box bigger every round by adding the first chars starting from char 0 -> 6
    {
      boxA += charBuf[j];             // Add the char at location J (Start: 0 -> 6 and increments each round)
    }

    // Box B
    for (int j = 0; j < i; j++)      // Make the second box bigger every round by adding the chars starting from char 6 -> 12
    {
      if (j + i < count)             // As long as the locations are smaller than the buffersize
      {
        boxB += charBuf[j + i];      // Add the char at the location i + j (starting after chars from box A) 6 -> 12
      }
    }

    // Comparing the boxes
    if (boxA == boxB && boxA != "")
    {
      productID = boxA;
      Serial.println(productID);
    }
  }
  Serial.println(productID);
  for ( int i = 0; i < count;  ++i )    // Clear buffer of chars
  {
    charBuf[i] = (char)0;
  }
}






