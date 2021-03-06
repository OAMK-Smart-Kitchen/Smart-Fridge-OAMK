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

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  //I2C
  Wire.begin();

}

void loop()
{
  // ----- Switch-control -----
  Wire.beginTransmission(58);  //Begin transmission to PCF8574 to activate RX (address: 111010)
  Wire.write(1);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
  // ----- End Switch-control -----
  Wire.requestFrom(57, 1); // Begin transmission to PCF8574 with the buttons

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
    // ----- End Ultrasonic User-detection -----

  }


  // ----- LED-DRIVER -----
  /*Wire.requestFrom(57, 1); // Begin transmission to PCF8574 with the buttons
  if (Wire.available())  // If bytes are available to be recieved
  {
    iInput = Wire.read();// Read a byte
  }*/

  if (iInput < 255)      //If the value less than 255
  {
    // Serial.print("Color detected: ");
    //Serial.print(iInput);
    if (iInput == 254) // P0
    {
      iOutput = 1;
      //Serial.println(" RED");
    };
    if (iInput == 253) // P1
    {
      iOutput = 2;
      //Serial.println(" GREEN");
    };
    if (iInput == 251) // P2
    {
      iOutput = 4;
      Serial.println(" BLUE");
    };
    if (iInput == 247) // P3
    {
      iOutput = 8;
      Serial.println(" OFF");
    };
  }
  Wire.beginTransmission(56);  //Begin transmission to PCF8574 (with the LEDs)
  Wire.write(iOutput);         //Send data to PCF8574 (with the LEDs)
  Wire.endTransmission();      //End Transmission to PCF8574 (with the LEDs)
  // ----- End LED-DRIVER -----

}





