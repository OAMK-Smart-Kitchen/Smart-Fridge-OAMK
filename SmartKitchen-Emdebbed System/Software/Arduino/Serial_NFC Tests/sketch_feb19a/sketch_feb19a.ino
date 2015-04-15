// Smart Fridge
// Tom Mampaey

/*
Test-code to detect and convert the ID of an NFC-tag too a usable int.
*/

int incomingByte = 0;   // for incoming serial data
int productID = 0;

void setup() {
        Serial.begin(9600);    
}
void loop() {

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
                       case 2295: // Big Nokia
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
        }
}
