float tempK=0, tempC=0, tempF=0;
 
void setup(){
 
Serial.begin(9600);    //Setup serial to 9600 bps
}
 
void loop(){
 
tempK = analogRead(0) * 0.004882812 * 100;    //Read temperature in Kelvins first
 
tempC = tempK - 273.15;    //Convert from Kelvin to Celsius
 
Serial.print("Celsius: "); Serial.println(tempC);
Serial.println();    
 
delay(1000);   
}
