Arduino M2X API Client
=====================

The Arduino library is used to send/receive data to/from [AT&amp;T's M2X service](https://m2x.att.com/) from [Arduino](http://www.arduino.cc/) based devices.

**NOTE**: Unless stated otherwise, the following instructions are specific to [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno) board. If you are using other boards, the exact steps may vary.


Getting Started
==========================
1. Signup for an [M2X Account](https://m2x.att.com/signup).
2. Obtain your _Master Key_ from the Master Keys tab of your [Account Settings](https://m2x.att.com/account) screen.
3. Create your first [Data Source Blueprint](https://m2x.att.com/blueprints) and copy its _Feed ID_.
4. Review the [M2X API Documentation](https://m2x.att.com/developer/documentation/overview).
5. Obtain an Arduino with built in wifi or ethernet, or a separate wifi or ethernet shield and [set it up](http://arduino.cc/en/Guide/HomePage). These docs were written for an [__Arduino Uno__](http://arduino.cc/en/Main/arduinoBoardUno) with a wifi or ethernet shield but the instructions can be adapted for other Arduino models.

Please consult the [M2X glossary](https://m2x.att.com/developer/documentation/glossary) if you have questions about any M2X specific terms.

How to Install the library
==========================

This library depends on [jsonlite](https://github.com/citrusbyte/jsonlite), the installation steps are as follows:

1. Clone the [jsonlite](https://github.com/citrusbyte/jsonlite) repository.

   **NOTE**: Since we are now using the old v1.1.2 API(we will migrate to the new API soon), please use the fork version of jsonlite listed above instead of the original one.

2. Open the Arduino IDE, click `Sketch->Import Library...->Add Library...`, then navigate to `amalgamated/jsonlite` folder in the cloned jsonlite repository. The jsonlite library will be imported to Arduino this way.

   **NOTE**: If you cloned the jsonlite library, there will be 3 folders named jsonlite:
   * `jsonlite`: the repo folder
   * `jsonlite/jsonlite`: the un-flattened jsonlite source folder
   * `jsonlite/amalgamated/jsonlite`: the flattened jsonlite source for arduino

   The last one here should be the one to use, the first 2 won't work!
3. Use the instructions outlined in Step 2 above to import the `M2XStreamClient` library in the current folder.
4. Now you can find M2X examples under `File->Examples->M2XStreamClient`
5. Enjoy coding!

Hardware Setup
==============

Board Setup
-----------

The Arduino website has a very good [tutorial](http://arduino.cc/en/Guide/HomePage) on setting up the Arduino board. It contains detailed instructions on how to install the Arduino IDE, sets up your board for initial testing. Feel free to proceed to the [Arduino site](http://arduino.cc/en/Guide/HomePage) to get a basic idea on Arduino.

Wifi/Ethernet Shield Setup
--------------------------

If you are using an [Arduino Yun](http://arduino.cc/en/Main/ArduinoBoardYun) board instead of an [Arduino Uno](http://arduino.cc/en/Main/ArduinoBoardUno) board, you can skip this section since the Yun board already has Wifi adapter on board.

To send data to the AT&amp;T M2X service, or receive data from the AT&amp;T M2X service, your Arduino board needs a connection to the Internet. Hence an Arduino [Wifi Shield](http://arduino.cc/en/Main/ArduinoWiFiShield) or [Ethernet Shield](http://arduino.cc/en/Main/ArduinoEthernetShield) is needed to give your board the power to connect to the Internet. To install the shield, hook the shield on your Arduino board — you can use the pins on the shield the same way as the real pins on the Arduino boards.

Sensor Setup
------------

Different sensors can be hooked up to an Arduino board to provide different properties including temperatures, humidity, etc. You can use a breadboard as well as wires to connect different sensors to your Arduino. For detailed tutorial on connecting different sensors, please refer to the Arduino [Examples page](http://arduino.cc/en/Tutorial/HomePage).

3G Shield Setup
------------

If you are using a 3G GSM/GPRS shield with your Arduino, the [M2X Arduino SIMCOM module](https://github.com/attm2x/m2x-arduino-simcom) can be used to connect your device to the AT&T cellular data network.


Variables used in Examples
==========================

In order to run the given examples, different variables need to be configured. We will walk through those variables in this section.

Network Configuration
---------------------

If you are using a Wifi Shield, the following variables need configuration:

```
char ssid[] = "<ssid>";
char pass[] = "<WPA password>";
```

Just fill in the SSID and password of the Wifi hotspot, you should be good to go.

For an Ethernet Shield, the following variables are needed:

```
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,17);
```

For a newer Ethernet Shield, the MAC address should be printed on a sticker on the shield. However, some sold Ethernet Shields have no MAC address shown on the board. In this case, you can use any MAC address, as long as it is not conflicted with another network device within the same LAN.

The IP address here is only used when DHCP fails to give a valid IP address. It is recommended, though not required, to provide a unique IP address here.

M2X API Key
-----------

Once you [register](https://m2x.att.com/signup) for an AT&amp;T M2X account, an API key is automatically generated for you. This key is called a _Primary Master Key_ and can be found in the _Master Keys_ tab of your [Account Settings](https://m2x.att.com/account). This key cannot be edited nor deleted, but it can be regenerated. It will give you full access to all APIs.

However, you can also create a _Data Source API Key_ associated with a given Data Source(Feed), you can use the Data Source API key to access the streams belonging to that Data Source.

You can customize this variable in the following line in the examples:

```
char m2xKey[] = "<M2X access key>";
```

Feed ID
-------

A feed is associated with a data source, it is a set of data streams, such as streams of locations, temperatures, etc. The following line is needed to configure the feed used:

```
char feedId[] = "<feed id>";
```

Stream Name
------------

A stream in a feed is a set of timed series data of a specific type(i,e. humidity, temperature), you can use the M2XStreamClient library to send stream values to M2X server, or receive stream values from M2X server. Use the following line to configure the stream if needed:

```
char streamName[] = "<stream name>";
```

Using the M2XStreamClient library
=========================

The M2X Arduino library can be used with both Wifi connection and Ethernet connection. For a Wifi connection, use the following code:

```
WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);
```

For an Ethernet connection, use the following code:

```
EthernetClient client;
M2XStreamClient m2xClient(&client, m2xKey);
```

If you are using an [Arduino Yun](http://arduino.cc/en/Main/ArduinoBoardYun) board specifically, you should use the following code:

```
YunClient client;
M2XStreamClient m2xClient(&client, m2xKey);
```

In the M2XStreamClient, 4 types of API functions are provided here:

* `send`: Send stream value to M2X server
* `receive`: Receive stream value from M2X server
* `updateLocation`: Send location value of a feed to M2X server
* `readLocation`: Receive location values of a feed from M2X server

Returned values
---------------

For all those functions, the HTTP status code will be returned if we can fulfill a HTTP request. For example, `200` will be returned upon success, `401` will be returned if we didn't provide a valid M2X API Key.

Otherwise, the following error codes will be used:

```
static const int E_NOCONNECTION = -1;
static const int E_DISCONNECTED = -2;
static const int E_NOTREACHABLE = -3;
static const int E_INVALID = -4;
static const int E_JSON_INVALID = -5;
```

Post stream value
-----------------

The following functions can be used to post value to a stream, which belongs to a feed:

```
template <class T>
int post(const char* feedId, const char* streamName, T value);
```

Here we use C++ templates to generate functions for different types of values, feel free to use values of `float`, `int`, `long` or even `const char*` types here.

Post multiple values
--------------------

M2X also supports posting multiple values to multiple streams in one call, use the following function for this:

```
template <class T>
int postMultiple(const char* feedId, int streamNum,
                 const char* names[], const int counts[],
                 const char* ats[], T values[]);
```

Please refer to the comments in the source code on how to use this function, basically, you need to provide the list of streams you want to post to, and values for each stream.

Fetch stream value
------------------

Since Arduino board contains very limited memory, we cannot put the whole returned string in memory, parse it into JSON representations and read what we want. Instead, we use a callback-based mechanism here. We parse the returned JSON string piece by piece, whenever we got a new stream value point, we will call the following callback functions:

```
void (*stream_value_read_callback)(const char* at,
                                   const char* value,
                                   int index,
                                   void* context);

```

The implementation of the callback function is left for the user to fill in, you can read the value of the point in the `value` argument, and the timestamp of the point in the `at` argument. We even pass the index of this this data point in the whole stream as well as a user-specified context variable to this function, so as you can perform different tasks on this.

To read the stream values, all you need to do is calling this function:

```
int fetchValues(const char* feedId, const char* streamName,
                stream_value_read_callback callback, void* context,
                const char* startTime = NULL, const char* endTime = NULL,
                const char* limit = NULL);
```

Besides the feed ID and stream name, only the callback function and a user context needs to be specified. Optional filtering parameters such as start time, end time and limits per call can also be used here.

Update Datasource Location
--------------------------

You can use the following function to update the location for a data source(feed):

```
template <class T>
int updateLocation(const char* feedId, const char* name,
                   T latitude, T longitude, T elevation);
```

Different from stream values, locations are attached to feeds rather than streams.

The reasons we are providing templated function is due to floating point value precision: on most Arduino boards, `double` is the same as `float`, i.e., 32-bit (4-byte) single precision floating number. That means only 7 digits in the number is reliable. When we are using `double` here to represent latitude/longitude, it means only 5 digits after the floating point is accurate, which means we can represent as accurate to ~1.1132m distance using `double` here. If you want to represent cordinates that are more specific, you need to use strings here.

Read Datasource Location
------------------------

Similar to reading stream values, we also use callback functions here. The only difference is that different parameters are used in the function:

```
void (*location_read_callback)(const char* name,
                               double latitude,
                               double longitude,
                               double elevation,
                               const char* timestamp,
                               int index,
                               void* context);

```

For memory space consideration, now we only provide double-precision when reading locations. An index of the location points is also provided here together with a user-specified context.

The API is also slightly different, in that the stream name is not needed here:

```
int readLocation(const char* feedId, location_read_callback callback,
                 void* context);

```

Delete Values
-------------

You can use the following function to delete values within a stream by providing a `from` and `end` date/time:

```
int deleteValues(const char* feedId, const char* streamName, 
                 const char* from, const char* end);
```

The timestamps `from` and `end` need to be in an ISO 8601 format: yyyy-mm-ddTHH:MM:SS.SSSZ. Note the Z for Zulu time.

Examples
========

We provide a series of examples that will help you get an idea of how to use the `M2XStreamClient` library to perform all kinds of tasks.

Note that the examples may apply to certain types of boards. For example, the ones with `Uno` in the name apply to `Arduino Uno` boards, while the ones with `Yun` apply to `Arduino Yun` boards.

Note that the examples contain fictionary variables, and that they need to be configured as per the instructions above before running on your Arduino board. Each of the examples here also needs either a Wifi Shield or an Ethernet Shield hooked up to your device.

In the `UnoPost`, `EthernetUnoPost` and `YunPost`, a temperature sensor, a breadboard and 5 wires are also needed to get temperature data, you need to wire the board like [this](http://cl.ly/image/3M0P3T1A0G0l) before running the code.

After you have configured your variables and the board, plug the Arduino board into your computer via a Micro-USB cable, click `Verify` in the Arduino IDE, then click `Upload`, and the code should be uploaded to the board. You can check all the outputs in the `Serial Monitor` of the Arduino IDE.

UnoPost
-------

This example shows how to post temperatures to M2X server. Before running this, you need to have a valid M2X Key, a feed ID and a stream name. The Arduino board needs to be configured like [this](http://cl.ly/image/3M0P3T1A0G0l). In this example, we are using an [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno) board. If you are using other boards, keep in mind that we are reading from `A0` in the code, the wiring should be similar to this one shown in the illustration.

UnoPostMultiple
---------------

This example shows how to post multiple values to multiple streams in one API call.

UnoFetchValues
--------------

This example reads stream values from M2X server. And prints the stream data point got to Serial interface. You can find the actual values in the Arduino `Serial Monitor`.

EthernetUnoPost
---------------

This one is similar to the `UnoPost`, except that EthernetClient is used instead of WifiClient. If you are using an Ethernet Shield instead of a Wifi Shield, you can use this example.

EthernetUnoReceive
------------------

This one is similar to the `UnoReceive`, except that EthernetClient is used instead of WifiClient.

UnoUpdateLocation
-----------------

This one sends location data to M2X server. Idealy a GPS device should be used here to read the cordinates, but for simplicity, we just use pre-set values here to show how to use the API.

UnoReadLocation
---------------

This one reads location data of a feed from M2X server, and prints them to Serial interfact. You can check the output in the `Serial Monitor` of the Arduino IDE.

UnoDelete
---------

This example shows how to delete values within a stream by providing a date/time range.

YunPost
-------

This example works like `YunPost`, except that it works on an [Arduino Yun](http://arduino.cc/en/Main/ArduinoBoardYun) board instead of an [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno) board.

LICENSE
=======

This library is released under the MIT license. See [`M2XStreamClient/LICENSE`](M2XStreamClient/LICENSE) for the terms.
