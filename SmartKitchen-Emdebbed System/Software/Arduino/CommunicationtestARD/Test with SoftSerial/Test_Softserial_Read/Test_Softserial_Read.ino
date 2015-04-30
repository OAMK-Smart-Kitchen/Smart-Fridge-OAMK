int incomingByte;   // for incoming serial data

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop()
{
  // read the incoming byte:
  incomingByte = Serial.read();

  // say what you got:
  Serial.print("I received: ");
  Serial.println((char)incomingByte);

}

