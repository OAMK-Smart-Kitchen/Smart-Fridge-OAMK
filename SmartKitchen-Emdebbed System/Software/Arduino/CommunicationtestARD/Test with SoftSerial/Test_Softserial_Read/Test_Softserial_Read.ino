#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);

void setup()
{
  mySerial.begin(9600);
}

void loop()
{
  char c = mySerial.read();
}
