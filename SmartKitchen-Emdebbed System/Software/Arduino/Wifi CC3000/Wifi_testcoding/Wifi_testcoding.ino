
/****************************************************************
M2X_CC3000_Post.ino
Post temperature data to AT&T's M2X
Shawn Hymel @ SparkFun Electronics
August 19, 2014

Manually connects to a WiFi network and an M2X stream. Reads 
temperature data from an HTU21D temperature and posts it to the
M2X stream.

Change AP_SSID, AP_PASSWORD, AP_SECURITY, FEED_ID, STREAM_NAME,
and M2X_KEY to match your WiFi and M2X parameters.

The security mode is defined by one of the following:
WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA, WLAN_SEC_WPA2

Resources:
Include SPI.h, SFE_CC3000.h, SFE_CC3000_Client.h, jsonlite.h,
M2XStreamClient.h, Wire.h, HTU21D.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with Arduino UNO R3

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <jsonlite.h>
#include <M2XStreamClient.h>
#include <Wire.h>
//#include <HTU21D.h>

// Parameters
#define POST_DELAY_MS   10000 // Post to stream every 10 seconds
#define DEGREE_SYMBOL   176   // Degree symbol for Serial.write

// Pins
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno

// Connection info data lengths
#define IP_ADDR_LEN     4   // Length of IP address in bytes

// WiFi Constants
#define AP_SSID         "SmartKitchen"      // SSID of network
#define AP_PASSWORD     "It's all about food!"  // Password of network
#define AP_SECURITY     WLAN_SEC_WPA2 // Security of network
#define TIMEOUT         30000         // Milliseconds

// M2X Constants
#define FEED_ID         "<2a107bdaa38112912c8d2f5597a8969c>"
#define STREAM_NAME     "<Brains of the Smart Fridge!>"
#define M2X_KEY         "<7e0a40b8062639fb00c4edea34da9321>"

// Global Variables
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client client = SFE_CC3000_Client(wifi);
M2XStreamClient m2x_client(&client, M2X_KEY);
//HTU21D sensor;
float temp;
int g_response;

// Setup. Configure HTU21D, WiFi, and M2X.
void setup() {

  g_response = 0;

  // Initialize UART for debugging
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("SparkFun CC3000 - M2X Post"));

  // Initialize HTU21D
  //sensor.begin();

  // Initialize CC3000 (configure SPI communications)
  if ( wifi.init() ) {
    Serial.println(F("CC3000 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during CC3000 init!"));
  }

  // Connect using DHCP
  Serial.print(F("Connecting to SSID: "));
  Serial.println(AP_SSID);
  if(wifi.connect(AP_SSID, AP_SECURITY, AP_PASSWORD, TIMEOUT)) {
    Serial.println(F("Connected!"));
  } else {
    Serial.println(F("Error: Could not connect to AP"));
  }
}

// Main loop. Post sensor readings at regular intervals.
void loop() {

  // Read sensor
  temp = analogRead(0);

  // Print reading to console with degree symbol and 'C'
  Serial.print(F("Temperature: "));
  Serial.print(temp, 2);
  Serial.write(176);
  Serial.println("C");

  // Post data to your stream
  g_response = m2x_client.post(FEED_ID, STREAM_NAME, temp);

  // If we fail to receive a response, stop running
  Serial.print(F("Post response: "));
  Serial.println(g_response);
  if ( g_response == -1 ) {
    while(1);
  }

  // Wait to post to stream again
  delay(POST_DELAY_MS);
}

