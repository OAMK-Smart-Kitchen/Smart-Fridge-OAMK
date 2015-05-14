String incomingByte = "";   // for incoming serial data
char character;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop()
{
  // read the incoming byte:
  if(Serial.available()) {
  character = Serial.read();
  incomingByte.concat(character); // Combines, or concatenates strings 
  //Serial.print((char)incomingByte);
  }
  
    if (incomingByte != "") {
    Serial.println(incomingByte);
  }

}

