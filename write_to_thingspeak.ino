/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#ifndef STASSID
#define STASSID "Mate9"
#define STAPSK  "ed66abe688e"
#endif

unsigned long myChannelNumber = 892519;
const char * myWriteAPIKey = "DZYQO0UVSRNY49LL";

const char* ssid     = STASSID;
const char* password = STAPSK;
WiFiClient clientt;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(clientt);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  ThingSpeak.setField(1, 60);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 

  // Close the connection
  Serial.println();
  Serial.println("closing connection");

  delay(2000); // execute once every 5 minutes, don't flood remote service
}
