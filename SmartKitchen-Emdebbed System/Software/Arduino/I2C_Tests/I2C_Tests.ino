#include <Wire.h>

byte x=0;
byte y=0;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop()
{
    Wire.requestFrom(33,1); // request 1 byte from slave device #2
    if(Wire.available())     //If the request is available
    {
        x = Wire.read();       //Receive the data
        Serial.println(x);
    }
    if(x<255)                     //If the data is less than 255
    {
        if (x==254) { y = 0; }; //P0
        if (x==253) { y = 2; }; //P1
        if (x==247) { y = 8; }; //P3
        if (x==251) { y = 4; }; //P2
    }
    Wire.beginTransmission(32);     //Begin the transmission to PCF8574
    Wire.write(y);                                //Send the data to PCF8574
    Wire.endTransmission();            //End the Transmission
}
