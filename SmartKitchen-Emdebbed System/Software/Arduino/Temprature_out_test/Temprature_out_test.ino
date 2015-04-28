int pin = 0;
float readt;
void setup() {
pinMode(pin, INPUT);
Serial.begin(9600);

}
void loop() {
float readt = analogRead(pin);
float Kelvin = (analogRead(pin) - 903.00);
float Celsius = Kelvin-273;
float Fahrenheit=(Celsius)*(9/5)+32;

Serial.println(Kelvin);

delay(1000);
}

