#include <SimpleTimer.h>


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
char tempcharBuf[100];
String incomingString = "";
String tempString = "";
bool ReadNFC = true;
int count = 100;
String productID = "0000";
int ReadDelay = 1000;

int Temprature = 20;
boolean Available = true;

// UserDetection
int duration;                //Stores duration of pulse in
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

  // VisualRGBCheck();
  if (DetectUser())
  {
    ModuleWrite(White, MOD1);
    ModuleWrite(Blue, MOD2);
    ModuleWrite(White, MOD3);
  }
  else 
  {
  ModuleWrite(Off, MOD1);
  ModuleWrite(Yellow, MOD2);
  ModuleWrite(Red, MOD3);
  }
              /*
              for (int i = MOD1_R ; i <= MOD3_R ; i++)
              {
                SetMod(i);
                readID();
                if (productID != "0000")
                {
                  ModuleWrite(Green, i - 5);
                  Available = true;
                }
                else
                {
                  ModuleWrite(Red, i - 5);
                  Available = false;
                }
                SendToWifi(productID, i, Available, Temprature);

                productID = "0000";
                delay(ReadDelay);
              }
              */
}

void ModuleWrite(byte txData, int Module_Address)
{
  Wire.beginTransmission(Module_Address);
  Wire.write(txData);
  Wire.endTransmission();
}

void readID()
{
  // ----- NFC-Tag Detection -----
  int LengthCharArr = sizeof(charBuf);
  //productID = "S";
  for (int i = 0; i <= LengthCharArr; i++)            // Put incomingbytes in a string of 100 chars
  {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      tempString = String(incomingByte);
      incomingString += tempString;
    }
    //productID = productID + "E";

  }
  incomingString.toCharArray(tempcharBuf, LengthCharArr);  // Put incomingString (size 100) in char array (100)
  incomingString = "";

  boolean StartShifting = false;
  int index = 0;
  for (int i = 0; i <= LengthCharArr; i++)
  {
    if (tempcharBuf[i] == '4' && tempcharBuf[i + 1] == '8' && tempcharBuf[i + 2] == '5' && tempcharBuf[i + 3] == '2' && (i + 3) < LengthCharArr) // Shifting array
    {
      StartShifting = true;
    }
    if (StartShifting)
    {
      charBuf[index] = tempcharBuf[i];
      index++;
    }
  }
  //charBuf = tempcharBuf;
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
  //delay(ReadDelay);
}

void SendToWifi(String iD, int location, boolean Available, int temprature)
{
  char charArray[50];
  String tempStr = "XD" + iD + "DA" + (String)location + "AB" + (String)Available + "BT" + (String)temprature + "TX";
  tempStr.toCharArray(charArray, 50);
  Serial.write(charArray);
}

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
  distance = duration / 58;                                    // Dividing this by 58 gives us a distance in cm
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

