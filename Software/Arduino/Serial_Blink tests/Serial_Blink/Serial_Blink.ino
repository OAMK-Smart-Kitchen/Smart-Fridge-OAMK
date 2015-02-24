// Test program Smart-Fridge

int led = 13;
int state;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}


void loop() {
if (Serial.available() > 0) 
{
    if (Serial.peek() == 'c') 
    {
      Serial.read();
      state = Serial.parseInt();
      digitalWrite(led,state);
    }
    while (Serial.available() > 0) 
    {
      Serial.read();
    }
}

}
