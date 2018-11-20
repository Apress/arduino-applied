/*******************************************************************************
 * Sketch name: control an LED with a webpage function
 * Description: incorporate Listing 25-4 as htmlCode.h
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 25 - Wi-Fi communication
 ******************************************************************************/

#include <ESP8266WiFi.h>      // library to connect to WiFi network
#include <ESP8266WebServer.h>   // library for webserver functionality 
ESP8266WebServer server;    // associate server with ESP8266WebServer library
char* ssid = "xxxx";        // change xxxx to your Wi-Fi ssid
char* password = "xxxx";      // change xxxx to your Wi-Fi password
int LEDpin = D8;        // LED pin D8 or GPIO 15
String LEDvalue = "OFF";
char* buildPage = // must be on three lines
#include "htmlCode.h"  // html code for webpage without comments
;   // line only includes a semi-colon

void setup()
{
  Serial.begin(115200);     // define Serial output at 115200 baud
  WiFi.begin(ssid, password);       // initialise WiFI
  while (WiFi.status() != WL_CONNECTED) delay(500); // wait for WiFi connection
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());     // display IP address of WiFi network
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  server.on("/", webpage);                // run webpage function as webpage loaded
  server.begin();       // initialise server
}

void webpage()        // function to collect data for webpage
{
  button();           // obtain LED button status
  server.send (200, "text/html", buildPage);    // publish webpage
}

void button()         // function of LED button status
{
  if (server.hasArg("LED")) LEDvalue = server.arg("LED");             // read LED button state
  if (LEDvalue == "ON") digitalWrite(LEDpin, HIGH);            // turn LED on or off
  else digitalWrite(LEDpin, LOW);
  delay(1000);  // delay for 1s to retain button colour
}

void loop()
{
  server.handleClient();
}

