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

// Reading from Master Module
char incommingByte;
String incommingString;
char charArray[150];
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
  }
  else {
    Serial.print("Failed to connect with: ");
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

void loop()
{
  if (Serial1.available())
  {
    incommingByte = Serial1.read();
    incommingString.concat(incommingByte);
    incommingString.toCharArray(charArray, 150);
  }

  if (!initComplete)
  {
    CheckInit();
  }
  else
  {
    data = "{\"IdNFC\":\"" + GetId(); + "\",\"Address\":\"" + GetAddress(); + "\",\"Available\":\"" + GetAvailability(); + "\"}"; // Constructing Json to PUT
    //    data = "{\"IdNFC\":\"" + GetId(); + "\",\"Address\":\"" + GetAddress(); + "\",\"Available\":\"" + (String)Available + "\"}";
    dataReceived = true;

    /*
    NFC_ID = GetId();
    Address = GetAddress();
    Availability = GetAvailability();
    Temprature = GetTemprature();
     Serial.println(NFC_ID);
     Serial.println(Address);
     Serial.println(Availability);
     Serial.println(Temprature);
     */
  }
  if (dataReceived)
  {
    if (client.connect(server, 80))
    {
      if (client.connected())
      {
        client.println("PUT /service/Hardware/Product HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.print("Content-Length: ");
        client.println(data.length()); // deleting quotes
        client.println("Cache-Control: no-cache");
        //client.println("Connection: keep-alive");
        //client.println("Content-Type: text/plain; charset=utf-8");
        //client.println("Content-Transfer-Encoding: base64");
        //client.println("Accept-Encoding: gzip, deflate, sdch");
        client.println("Content-Type: application/json");
        client.println();
        client.println(data);
        //client.println("{\"IdNFC\":\"48525352706548656557515256481310\",\"Address\":\"0156\",\"Available\":\"true\"}");
        delay(3000);
      }
      //client.stop();
    }
    else
    {
      Serial.println("Error: Could not make TCP connection");
    }
    /*
    for (int i = 0; i < 20; i++)
    {
      char c = client.read();
      Serial.print(c);
    }
    */

    if ( client.available() )  // If there are incoming bytes, read them.
    {
      char z = client.read();
      Serial.print(z);
    }
    dataReceived = false;
  }
  else
  {
    if (client.connected()) {
      client.stop();	// DISCONNECT FROM THE SERVER}
    }
  }
}
void CheckInit()
{
  int count = 0;
  for (int i = 0; i < sizeof(charArray); i++)
  {
    if (charArray[i] == 'X')
    {
      count++;
    }
  }
  if (count >= 2)
  {
    initComplete = true;
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
