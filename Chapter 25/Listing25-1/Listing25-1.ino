/*******************************************************************************
 * Sketch name: connect to Wi-Fi network and update webpage
 * Description: connect to Wi-Fi network and update webpage
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 25 - Wi-Fi communication
 ******************************************************************************/

#include <ESP8266WiFi.h>      // library to connect to WiFi network
#include <ESP8266WebServer.h>   // library for webserver functionality 
ESP8266WebServer server;        // declare webserver
char* ssid = "xxxx";        // change xxxx to your Wi-Fi ssid
char* password = "xxxx";      // change xxxx to your Wi-Fi password

void setup()
{
  Serial.begin(115200);     // define Serial output at 115200 baud
  WiFi.begin(ssid, password);       // initialise WiFI
  while (WiFi.status() != WL_CONNECTED) delay(500); // wait for WiFi connection
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());     // display IP address of WiFi network
  server.on("/", message);                // message function when webpage loaded
  server.begin();         // initialise server
}

void message()          // function for main webpage
{
  String msg = "webserver connected";     // define msg as string
  server.send (200, "text/plain", msg);      // send response with plain text
}

void loop()
{
  server.handleClient();      // manage incoming HTTP requests
}

