#include <jsonlite.h>
#include <Console.h>
#include <YunClient.h>

#include "M2XStreamClient.h"

char feedId[] = "<feed id>"; // Feed you want to post locations to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char incomingByte;      // a variable to read incoming Console data into

// For simplicity, predefined data are used here
char name[] = "<location name>"; // Name of current location of datasource
double latitude = 37.97884;
double longitude = 57.54787; // Ideally, those values should be read from a GPS
double elevation = 11;

YunClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Bridge.begin();   // Initialize Bridge
  Console.begin();  // Initialize Console

  // Wait for the Console port to connect
  while(!Console);

  Console.println("type T to post location to m2x");
}

void loop() {
  // see if there's incoming Console data:
  if (Console.available() > 0) {
    // read the oldest byte in the Console buffer:
    incomingByte = Console.read();
    Console.println(incomingByte);

    // if the user presses 'T', post the temperature to m2x
    if (incomingByte == 'T') {
      int response = m2xClient.updateLocation(feedId, name, latitude,
                                              longitude, elevation);
      Console.print("M2x client response code: ");
      Console.println(response);
    }
  }
}
