
/* 

Master Module of Smart Fridge
-----------------------------
Made by Tom Mampaey
at 'OAMK University of Applied sciences'
May 2015

The mastermodule controls all the connected slavemodules by I2C-protocol on the two RJ-11 connectors (on right).
It also has a motionsensor port (on left), a temraturesensor and a output port to Wifi (underneath).
The mastermodule is powerd by an 12V 1,5A DC adapter

This code controls all the serial switches on the NFC-readers and converts this data to ID's.
Seven diffrent colors can be dedicated to the RGB-strips of the selected Slave Module.
The converted data will be set in a header before sending over the serial line of the output-port.
*/

// Module adresses:
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
char tempcharBuf[100];
String incomingString = "";
String tempString = "";
boolean ReadNFC = true;
int count = 100;
String productID = "0000";
int ReadDelay = 1000;

int Temprature = 20;        // test value
boolean Available = true;

// UserDetection
int duration;                // Stores duration of pulse in
int distance;                // Stores distance
int sensorpin = 7;
int UserDistance = 30;       // in cm

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  ModuleWrite(Off, MOD1);
  ModuleWrite(Off, MOD2);
  ModuleWrite(Off, MOD3);
  ModuleWrite(Off, MOD4);
  ModuleWrite(Off, MOD5);

  ModuleWrite(Off, MOD1_R);
  ModuleWrite(Off, MOD2_R);
  ModuleWrite(Off, MOD3_R);
  ModuleWrite(Off, MOD4_R);
  ModuleWrite(Off, MOD5_R);
}

void loop()
{
  //VisualRGBCheck();          // Visual knight rider of 7 colors for visual check of connection
  // if (DetectUser()) {}      // Can be interactive, from chaning colors to sending to server (works)
  
  for (int i = MOD1_R ; i <= MOD3_R ; i++)  // Read all the readers. 
  {
    SetMod(i);                            // Select NFC-reader
    readID();
    if (productID != "0000")
    {
      ModuleWrite(Green, i - 5);          // Product detected
      Available = true;
    }
    else
    {
      ModuleWrite(Red, i - 5);            // No product
      Available = false;
    }
    SendToWifi(productID, i, Available, Temprature);

    productID = "0000";
    delay(ReadDelay);
  }
}

// Sends assigned data (color or state of serial switch) to specific Module.
void ModuleWrite(byte txData, int Module_Address)
{
  Wire.beginTransmission(Module_Address);
  Wire.write(txData);
  Wire.endTransmission();
}

// Reads the data and translates it to an ID
void readID()
{
  // ----- NFC-Tag Detection -----
  int LengthCharArr = sizeof(charBuf);
  
  for (int i = 0; i <= LengthCharArr; i++)            // Put incomingbytes in a string of 100 chars
  {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      tempString = String(incomingByte);
      incomingString += tempString;
    }
  }
  
  incomingString.toCharArray(tempcharBuf, LengthCharArr);  // Put incomingString (size 100) in char array (100)
  incomingString = "";

  boolean StartShifting = false;
  int index = 0;
  for (int i = 0; i <= LengthCharArr; i++)
  {
    if (tempcharBuf[i] == '4' && tempcharBuf[i + 1] == '8' && tempcharBuf[i + 2] == '5' && tempcharBuf[i + 3] == '2' && (i + 3) < LengthCharArr) // Shifting array to brand
    {
      StartShifting = true;
    }
    if (StartShifting)
    {
      charBuf[index] = tempcharBuf[i];
      index++;
    }
  }
  
  for (int i = 6; i <= LengthCharArr; i++)     // Devide the char array in 'boxes' (Starting with 6 because ID never is shorter)
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
      if (j + i < LengthCharArr)             // As long as the locations are smaller than the buffersize
      {
        boxB += charBuf[j + i];      // Add the char at the location i + j (starting after chars from box A) 6 -> 12
      }
    }

    // Comparing the boxes
    if (boxA == boxB && boxA != "")
    {
      productID = boxA;    // Final productID
      for ( int i = 0; i < LengthCharArr;  ++i )    // Clear buffer of chars
      {
        charBuf[i] = (char)0;
        tempcharBuf[i] = (char)0;
      }
    }
  }
}
// Puts the variables in headers on the serial line to send out the output port 
void SendToWifi(String iD, int location, boolean Available, int temprature)
{
  char charArray[50];
  String tempStr = "XD" + iD + "DA" + (String)location + "AB" + (String)Available + "BT" + (String)temprature + "TX";

  tempStr.toCharArray(charArray, 50);
  Serial.write(charArray);
}

// Visual knight rider of 7 colors for visual check of connection
void VisualRGBCheck()
{
  int timer = 200;
  for (int count = 0; count < 3; count++) {
    ModuleWrite(Green, MOD1 + count);
    delay(timer);
    ModuleWrite(Red, MOD1 + count);
    delay(timer);
    ModuleWrite(Yellow, MOD1 + count);
    delay(timer);
    ModuleWrite(Blue, MOD1 + count);
    delay(timer);
    ModuleWrite(BrightBlue, MOD1 + count);
    delay(timer);
    ModuleWrite(Purple, MOD1 + count);
    delay(timer);
    ModuleWrite(Green, MOD1 + count);
    delay(timer);
  }
  for (int i = 0; i < 3; i++) {
    for (int count = 0; count < 3; count++) {
      ModuleWrite(Off, 56 + count);
    }
    delay(timer);
    for (int count = 0; count < 3; count++) {
      ModuleWrite(White, 56 + count);
    }
    delay(timer);
  }
}

// Detects users in front of fridge, gives countless options to implement
boolean DetectUser()
{
  pinMode(sensorpin, OUTPUT);
  digitalWrite(sensorpin, LOW);                          // Make pin low before sending a short high to trigger ranging
  delayMicroseconds(2);
  digitalWrite(sensorpin, HIGH);                         // Sends short 10 microsecond high on pin to start ranging
  delayMicroseconds(10);
  digitalWrite(sensorpin, LOW);                          // Set pin low again before waiting for pulse back in
  pinMode(sensorpin, INPUT);
  duration = pulseIn(sensorpin, HIGH);                   // Reads echo pulse in from SRF05 in microseconds
  distance = duration / 58;                              // /58 is distance in cm
  Serial.print("Seesam says: ");
  if ( distance < UserDistance)
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

// Configures the modules correctly to make sure only that module is reading!
void SetMod(int SelectedMod)
{
  switch (SelectedMod) {
    case 61:
      ModuleWrite(Purple, MOD1);
      ModuleWrite(White, MOD2);
      ModuleWrite(White, MOD3);
      ModuleWrite(Off, MOD1_R);
      ModuleWrite(Read, MOD2_R);
      ModuleWrite(Off, MOD3_R);
      break;
    case MOD2_R:
      ModuleWrite(White, MOD1);
      ModuleWrite(Purple, MOD2);
      ModuleWrite(White, MOD3);
      ModuleWrite(Off, MOD1_R);
      ModuleWrite(Off, MOD2_R);
      ModuleWrite(Read, MOD3_R);
      break;

    case MOD3_R:
      ModuleWrite(White, MOD1);
      ModuleWrite(White, MOD2);
      ModuleWrite(Purple, MOD3);
      ModuleWrite(Read, MOD1_R);
      ModuleWrite(Off, MOD2_R);
      ModuleWrite(Off, MOD3_R);
      break;
  }
}

