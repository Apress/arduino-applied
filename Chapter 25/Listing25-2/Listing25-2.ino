/*******************************************************************************
 * Sketch name: void LED() function
 * Description: extend Listing 25-1 to control built-in and external LEDs
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
int LEDpin = 16;  // built-in LED on GPIO 16
int LED2pin = D8;  // second LED on pin D8 or GPIO 15

void setup()
{
  Serial.begin(115200);     // define Serial output at 115200 baud
  WiFi.begin(ssid, password);       // initialise WiFI
  while (WiFi.status() != WL_CONNECTED) delay(500); // wait for WiFi connection
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());     // display IP address of WiFi network
  server.on("/",message);                // message function when webpage loaded
  server.begin();         // initialise server
  server.on("/LED", LED);      // turn LED on or off when website loads
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  pinMode(LED2pin, OUTPUT);      // LED2 pin as output
}

void message()          // function for main webpage
{
  String msg = "webserver connected";     // define msg as string
  server.send (200, "text/plain",msg);      // send response with plain text
}

void LED()
{
  digitalWrite(LEDpin, !digitalRead(LEDpin));    // turn built-in LED on or off
  digitalWrite(LED2pin, !digitalRead(LEDpin));   // turn LED2 on or off
  String msg;         // define msg as string
  if (digitalRead(LEDpin) == HIGH) msg = "LEDs off"; // GPIO16 active LOW
  else msg = "LEDs on";
  server.send(200,"text/plain", msg);     // send response in plain text
}

void loop()
{
  server.handleClient();      // manage incoming HTTP requests
}

