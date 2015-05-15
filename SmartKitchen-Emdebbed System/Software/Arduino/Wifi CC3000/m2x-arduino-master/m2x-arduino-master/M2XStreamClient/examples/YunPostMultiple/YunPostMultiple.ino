#include <jsonlite.h>
#include <Console.h>
#include <YunClient.h>

#include "M2XStreamClient.h"

char feedId[] = "<feed id>"; // Feed you want to post to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char incomingByte;      // a variable to read incoming Console data into

// Values to post, for simplicity, we just use predefined data here
const char *streamNames[] = { "temperature", "humidity" };
int counts[] = { 2, 1 };
const char *ats[] = { "2013-11-11T11:11:11Z", NULL, NULL };
double values[] = { 23.75, 24.125, 6.375 };

YunClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Bridge.begin();   // Initialize Bridge
  Console.begin();  // Initialize Console

  // Wait for the Console port to connect
  while(!Console);

  Console.println("type T to post multiple stream data to m2x");

}

void loop() {
  // see if there's incoming Console data:
  if (Console.available() > 0) {
    // read the oldest byte in the Console buffer:
    incomingByte = Console.read();
    Console.println(incomingByte);

    // if the user presses 'T', post the data to m2x
    if (incomingByte == 'T') {
      int response = m2xClient.postMultiple(feedId, 2, streamNames,
                                            counts, ats, values);
      Console.print("M2x client response code: ");
      Console.println(response);
    }
  }
}
