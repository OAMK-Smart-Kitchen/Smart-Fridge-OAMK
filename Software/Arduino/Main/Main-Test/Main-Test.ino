// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
 */

// NFC
int incomingByte;   // for incoming serial data
String productID;
String tempString;
int minLengthID = 40;  // minimale lengte van NFC-tag ID

// NFC-ID's
const String Banana 1188611854245125125125141153151143159229235;
const String Cucumber 1188611854245125125125141153151143159229235;
  //NFC-ID
  enum Products {Banana,Cucumber,Tomato};


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

}

void loop()
{
  // ----- NFC-Tag Detection -----

  if (Serial.available() > 0 ) {
    incomingByte = Serial.read();
    if (incomingByte == 0 && productID.length() >= minLengthID)
    {
        Products product = 
      //Serial.println(productID);

      Serial.print("NFC-ID: ");
      // Software on computer will do this in futere (Database)
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
      Serial.println(productID);
      productID = "";
    }
    else
    {
      tempString = String(incomingByte);
      productID = productID + tempString;
    }


    // ----- End NFF-Tag detection -----
    /*
        // ----- Ultrasonic User-detection -----
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

        delay(500);
        // ----- Ultrasonic User-detection -----
    */
  }

}





