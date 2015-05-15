
#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>

// Pins
#define CC3000_INT      2  
#define CC3000_EN       7   
#define CC3000_CS       10  

// Connection info data lengths
#define IP_ADDR_LEN     4   // Length of IP address in bytes

// Constants
char ap_ssid[] = "SmartKitchen";                  // SSID of network
char ap_password[] = "12345678";          // Password of network
unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
unsigned int timeout = 30000;             // Milliseconds
char server[] = "api.verhofstadt.eu";        // Remote host site

// Global Variables
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client client = SFE_CC3000_Client(wifi);

void setup() {
  
  ConnectionInfo connection_info;
  int i;
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println("-------------------------------------");
  Serial.println("Wifi Module CC3000 - PUT to Server SF");
  Serial.println("-------------------------------------");
  
  // Initialize CC3000 (configure SPI communications)
  if ( wifi.init() ) {
    Serial.println("CC3000 initialization complete");
  } else {
    Serial.println("Something went wrong during CC3000 init!");
  }
  
  // Connect using DHCP
  Serial.print("Connecting to SSID: ");
  Serial.println(ap_ssid);
  if(!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.println("Error: Could not connect to AP");
  }
  
  // Gather connection details and print IP address
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
  
  // Make a TCP connection to remote host
  Serial.print("Performing HTTP PUT of: ");
  Serial.println(server);
  if ( !client.connect(server, 80) ) {
    Serial.println("Error: Could not make a TCP connection");
  }
  /*
  // Make a HTTP GET request (works!)
  client.println("GET /index.html HTTP/1.1");
  client.print("Host: ");
  client.println(server);
  client.println("Connection: close");
  client.println();
  Serial.println();
 
  */
}

void loop() {
  
  // If there are incoming bytes, print them
  if ( client.available() ) {
    //char c = client.read();
   // Serial.print(c);
   Serial.println("beschikbaar");
  }
  
  // If the server has disconnected, stop the client and wifi
  if ( !client.connected() ) {
    Serial.println();
    
    // Close socket
    if ( !client.close() ) {
      Serial.println("Error: Could not close socket");
    }
    
    // Disconnect WiFi
    if ( !wifi.disconnect() ) {
      Serial.println("Error: Could not disconnect from network");
    }
    
    // Do nothing
    Serial.println("Finished WebClient test");
    while(true){
      delay(1000);
    }
  }
}
