#include <jsonlite.h>
#include <Console.h>
#include <YunClient.h>

#include "M2XStreamClient.h"

char feedId[] = "<feed id>"; // Feed you want to fetch values from
char streamName[] = "<stream name>"; // Stream you want to fetch values from
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char incomingByte;      // a variable to read incoming Console data into

YunClient client;
M2XStreamClient m2xClient(&client, m2xKey);

// Callback function used to process fetched data
void on_data_point_found(const char* at, const char* value, int index, void* context) {
  Console.print("Found a data point, index:");
  Console.println(index);
  Console.print("At:");
  Console.println(at);
  Console.print("Value:");
  Console.println(value);
}

void setup() {
  Bridge.begin();   // Initialize Bridge
  Console.begin();  // Initialize Console

  // Wait for the Console port to connect
  while(!Console);

  Console.println("type T to fetch temperature data from m2x");
}

void loop() {
  // see if there's incoming Console data:
  if (Console.available() > 0) {
    // read the oldest byte in the Console buffer:
    incomingByte = Console.read();
    Console.println(incomingByte);

    // if the user presses 'T', post the temperature to m2x
    if (incomingByte == 'T') {
      int response = m2xClient.fetchValues(feedId, streamName, on_data_point_found, NULL);
      Console.print("M2x client response code: ");
      Console.println(response);
    }
  }
}
