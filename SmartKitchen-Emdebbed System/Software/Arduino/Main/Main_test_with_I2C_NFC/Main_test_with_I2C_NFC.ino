// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
 */

// I2C
#include <Wire.h>
byte iInput=0;
byte iOutput=0;

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


// Ultrasonic
#define echoPin 7
#define trigPin 8
#define LEDPin 13

int maximumRange = 100;
int minimumRange = 0;
long duration, distance;
boolean readSensor = true;

void setup() {
  // Serials
  Serial.begin(9600);
  
  //I2C
  Wire.begin();

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);

}

void loop()
{
  // ----- I2C Bus Protocol -----
    Wire.requestFrom(72,5);// Adres 1001 0001 (last 1 to READ) Hex is 0x91, Read 6 bytes (ID min 43 chars)

  // ----- NFC-Tag Detection -----
  if(Wire.available() >0) // If bytes are available to be recieved
  {
    incomingByte = Wire.read();
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

      /* switch (productID) {
          case "rf": //Yellow
            Serial.println("Banana");
            break;
          case "fr": //Red
            Serial.println("Hamburger");
            break;
          case "fe": //Green
            Serial.println("Cucumber");
            break;
          case "frgr"://White
            Serial.println("Box with vegetables");
            break;
          case "efef": //Black
            Serial.println("Milk");
            break;
          default:
            Serial.println(productID);

        }*/
      productID = "";
      //readSensor == true;
    }
    else
    {
      tempString = String(incomingByte);
      productID = productID + tempString;
    }
    // ----- End NFF-Tag detection -----
    
    
    
    /*
            // ----- Ultrasonic User-detection -----
            if(readSensor == true)
            {
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);

            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);

            digitalWrite(trigPin, LOW);
            duration = pulseIn(echoPin, HIGH);

            //Convert to cm based on speed of sound.
            distance = duration / 58.2;

            if (distance >= maximumRange || distance <= minimumRange) {
              Serial.println("Nobody in front of fridge");
              digitalWrite(LEDPin, LOW);
            }
            else {
              Serial.print("User detected on: ");
              Serial.println(distance);
              digitalWrite(LEDPin, HIGH);
            }

            delay(500); */
    //}
    // ----- Ultrasonic User-detection -----

  }

}





