
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

// NFC

int incomingByte = 0;         // for incoming serial data
char charBuf[100];
String incomingString = "";
String tempString = "";
int LengthBuffer = 100;
bool ReadNFC = true;
int count = 100;
String productID = "";

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  deviceWrite(Off, MOD1);         
  deviceWrite(Off, MOD2);     
  deviceWrite(Off, MOD3);  
  deviceWrite(Off, MOD4);  
  deviceWrite(Off, MOD5);  
  
  deviceWrite(Off, MOD1_R);  
  deviceWrite(Off, MOD2_R);  
  deviceWrite(Off, MOD3_R);  
  deviceWrite(Off, MOD4_R);  
  deviceWrite(Off, MOD5_R);  
}

void loop()
{
  deviceWrite(Purple, MOD1);         // Set color Green
  deviceWrite(Read, MOD1_R);         // Set color Red
  readID();
}

void deviceWrite(byte txData, int Module_Address)
{
  Wire.beginTransmission(Module_Address);
  Wire.write(txData);
  Wire.endTransmission();
}

void readID()
{
    // ----- NFC-Tag Detection -----

  productID = "S";
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
      productID = boxA;          // Final productID
      
    }
    /*
    else
    {
      productID = "No product found";
    }
    */
  }

  for ( int i = 0; i < count;  ++i )    // Clear buffer of chars
  {
    charBuf[i] = (char)0;
  }
  Serial.println(productID);
  delay(3000);

}
