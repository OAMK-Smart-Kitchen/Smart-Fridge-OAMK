
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
int ReadDelay = 500;

// UserDetection
int duration;                //Stores duration of pulse in
int distance;                // Stores distance
int sensorpin = 7;
int UserDistance = 30;       // in cm 

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
  DetectUser();
  //productID = "";
 /* deviceWrite(Red, MOD2);
  deviceWrite(BrightBlue, MOD1);
  deviceWrite(Read, MOD1_R);
  //readID();
  delay(5000);
  deviceWrite(Red, MOD1);
  deviceWrite(BrightBlue, MOD2);
  deviceWrite(Read, MOD2_R);
  //readID();
  delay(5000); */
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
      productID = boxA;          // Final productID

    }
  }

  for ( int i = 0; i < count;  ++i )    // Clear buffer of chars
  {
    charBuf[i] = (char)0;
  }
  Serial.println(productID);
  //delay(ReadDelay);
}

boolean DetectUser()
{
 pinMode(sensorpin, OUTPUT);
  digitalWrite(sensorpin, LOW);                          // Make sure pin is low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(sensorpin, HIGH);                         // Send a short 10 microsecond high burst on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(sensorpin, LOW);                                  // Send pin low again before waiting for pulse back in
  pinMode(sensorpin, INPUT);
  duration = pulseIn(sensorpin, HIGH);                        // Reads echo pulse in from SRF05 in micro seconds
  distance = duration/58;                                      // Dividing this by 58 gives us a distance in cm
  Serial.print("Seesam says: ");
  if( distance < UserDistance)
  {
    Serial.println("USER DETECTED IN FRONT OF FRIDGE!");
    return true;
  }
  else
  {
  Serial.print("Motion detected on ");                                              // Wait before looping to do it again
  Serial.println(distance);
  return false;
  }
  delay(500);   

}

