// Smart Fridge
// Tom Mampaey
/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
This int will be sended serial to the computer and the he will compare it with the numbers in the database.
 */

// NFC
int incomingByte = 0;   // for incoming serial data
int productID = 0;      

// Ultrasonic
#define echoPin 7 
#define trigPin 8 
#define LEDPin 13 

int maximumRange = 100; 
int minimumRange = 0; 
long duration, distance; 

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
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 0)
    {
      Serial.print("NFC-ID: ");
      // Software on computer will do this in futere (Database)
      switch (productID) {
      case 2207: //Yellow
        Serial.println("Banana");
        break;
      case 2371: //Red
        Serial.println("Hamburger");
        break;
      case 2454: //Green
        Serial.println("Cucumber");
        break;
      case 2367://White
        Serial.println("Milk");
        break;
      case 2295:
        Serial.println("Soda");
        break;
      case 1254: // Big Nokia
        Serial.println("Soup");
        break;
      default: 
        Serial.println(productID);
      }
      productID = 0;
    }
    else
    {
      productID = incomingByte + productID;
    }

    // ----- End NFF-Tag detection -----

    // ----- Ultrasonic User-detection -----
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 

    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    //Convert to cm based on speed of sound.
    distance = duration/58.2;

    if (distance >= maximumRange || distance <= minimumRange){
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
    }
}
  




