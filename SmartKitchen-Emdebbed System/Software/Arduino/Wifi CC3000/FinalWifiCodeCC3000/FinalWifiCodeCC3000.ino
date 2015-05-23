/*----------------------------------
* SEND PRODUCT INFORMATION TO SERVER
* ----------------------------------
* Tom Mampaey 3PBA-EA OAMK OULU FINLAND
*
* Gets Product information from MASTER-board SmartFridge
* Sends it to the server using WiFi
* Based on the GET-request Arduino example of WebClient SFE
*/

#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>

// Pins
#define CC3000_INT 2   // Needs to be an interrupt pin 
#define CC3000_EN  7   // Digital pin
#define CC3000_CS  10  // cs pin (best 10 on uno)

// Connection info data lengths
#define IP_ADDR_LEN 4   // Length of IP address in bytes

// Internet settings (constants)
char ap_ssid[] = "SmartKitchen";          // SSID of network
char ap_password[] = "12345678";          // Password of network
unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
unsigned int timeout = 30000;             // Milliseconds
char server[] = "api.verhofstadt.eu";     // Remote host site
String data = " ";
int led = 50;

// Reading from Master Module
char incommingByte;
String incommingString;
char charArray[80];
boolean initComplete = false;
boolean dataReceived = false;
String NFC_ID = "";
String Address = "";
String Availability = "";
String Temprature = "";

// Global Variables
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client client = SFE_CC3000_Client(wifi);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW);

  ConnectionInfo connection_info;
  int i;
  // Initialize Serial port
  Serial.println("----------------------------------");
  Serial.println("SmartFridge CC3000 - PUT to Server");
  Serial.println("----------------------------------");

  // Initialize CC3000 (configure SPI communications)
  if ( wifi.init() ) {
    Serial.println("CC3000 initialization complete");
  } else {
    Serial.println("Error: CC3000 initialization incomplete");
  }

  // Connect using DHCP
  Serial.print("Connecting to SSID: ");
  Serial.println(ap_ssid);
  if (!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.println("Error: Could not connect to AP");
  }

  // Connection details and print IP address
  if ( !wifi.getConnectionInfo(connection_info) ) {
    Serial.println("Error: Could not obtain connection details");
  } else {
    Serial.print("IP Address: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.println();
  }

  // Make TCP connection to remote host
  Serial.print("Performing HTTP PUT to: ");
  Serial.println(server);

  client.connect(server, 80);
  if (client.connected()) { //initiate connection
    Serial.print("Connected to: ");
    digitalWrite(led, HIGH);
  }
  else {
    Serial.print("Failed to connect with: ");
    digitalWrite(led, LOW);
  }
  Serial.println(server);

  /*
    // Make a HTTP GET request (works!)
    client.println("GET /service/exercises HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    Serial.println(); */
}
String inData = "";

void loop()
{
  inData = "";

  if (Serial1.available())
  {
    delay(100); //allows all serial sent to be received together
    while (Serial1.available())
    {
      char recieved = Serial1.read();
      inData += recieved;
    }
  }

  if (!inData.equals(""))
  {
    inData.toCharArray(charArray, 100);

    //Constructing Json to PUT
    String ID = GetId();
    String Address = GetAddress();
    String Available = GetAvailability();
    String temprature = GetTemprature();
    data = "{\"IdNFC\":\"" + ID  + "\",\"Address\":\"" + Address + "\",\"Available\":\"" + Available + "\",\"TemperatureFridge\":\"" + temprature + "\"}";
    SendToServer(data);
  }
}

String GetContentByFilterOn(char filter)
{
  bool readd = false;
  bool stopread = false;
  String content = "";

  for (int i = 0; i < sizeof(charArray); i++)
  {
    if (stopread)
    {
      return content;
    }

    if (readd)
    {
      if (charArray[i] != filter)
      {
        content.concat(charArray[i]);
      }
    }

    if (charArray[i] == filter)
    {
      readd = !readd;
      if (readd == false)
      {
        stopread = true;
      }
    }
  }
}

void SendToServer(String data)
{
  if (client.connect(server, 80))
  {
    if (client.connected())
    {
      client.println("PUT /service/Hardware/Product HTTP/1.1");
      delay(5);
      client.print("Host: ");
      client.println(server);
      delay(5);
      client.print("Content-Length: ");
      client.println(data.length());             // deleting quotes
      delay(5);
      client.println("Cache-Control: no-cache");
      delay(5);
      //client.println("Connection: keep-alive");
      //client.println("Content-Type: text/plain; charset=utf-8");
      //client.println("Content-Transfer-Encoding: base64");
      //client.println("Accept-Encoding: gzip, deflate, sdch");
      client.println("Content-Type: application/json");
      delay(5);
      client.println();
      delay(5);
      client.println(data);
      Serial.println(data);
            for (int i = 0; i < 50; i++){
          char c = client.read();
          Serial.print(c);
      }

      client.stop();
      //delay(2000);
    }
  }
  else
  {
    Serial.println("Time-out: Could not make TCP connection");
    //client.stop();
    client.connect(server, 80);
  }
}

String GetHeader()
{
  return GetContentByFilterOn('X');    // Filer NFC-ID by data between 'D'
}
String GetId()
{
  return GetContentByFilterOn('D');    // Filer NFC-ID by data between 'D'
}
String GetAddress()
{
  return GetContentByFilterOn('A');    // Filer Address by data between 'A'
}
String GetAvailability()
{
  return GetContentByFilterOn('B');    // Filer Availability by data between 'B'
}
String GetTemprature()
{
  return GetContentByFilterOn('T');    // Filer Temprature by data between 'T'
}
