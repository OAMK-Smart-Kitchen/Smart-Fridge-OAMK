/*                Receiver
 For more details see: http://projectsfromtech.blogspot.com/
 
 The Tx sketch makes use of Serial1. This functionality is only found on the Arduino Mega and other 3rd party boards.
 Connect the Tx->Rx1  and Rx ->Tx1 pins with the board running Add_Five_Tx.ino
 Connect the Grounds of the two boards
 
 Receive an integer value over the serial, adds 5 to it,
 and then returns the value to the Tx board
 
 Note: The Tx and Rx boards are just names I chose. The communication is 2-way. 
 Master-slave would probably be a better option.
 */
int val = 0;
int incoming = 0;

void setup()
{
  Serial.begin(115200);

}

void loop()
{
  incoming = Serial.available();
  while (incoming != 0)                 //While there is something to be read
  {
    val = Serial.parseInt();             //Reads integers as integer rather than ASCI. Anything else returns 0
    val = val + 5;
    Serial.print(val);                  //Send the new val back to the Tx 
    incoming = Serial.available();    
  }
}


