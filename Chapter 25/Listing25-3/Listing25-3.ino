/*******************************************************************************
 * Sketch name: ESP8266 with LED, LDR and BMP280 sensor
 * Description: display requested measurement on webpage
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
#include <Wire.h>       // include Wire library
#include <Adafruit_Sensor.h>      // include Unified Sensor library
#include <Adafruit_BMP280.h>    // include BMP280 library
Adafruit_BMP280 bmp;            // associate bmp with Adafruit_BMP280 library
int BMPaddress = 0x76;      // I2C address of BMP280
float reading;
String letter, msg;

void setup()
{
  Serial.begin(115200);     // define Serial output at 115200 baud
  WiFi.begin(ssid, password);     // initialise WiFI
  while (WiFi.status() != WL_CONNECTED) delay(500); // wait for WiFi connection
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());     // display IP address of WiFi network
  server.on("/BMP", BMP);                 // display temperature, pressure or altitude
  server.begin();       // initialise server
  bmp.begin(BMPaddress);      // initialise BMP280 sensor
}

void BMP()        // function for /BMP webpage
{            // looks for string "sensor=" in URL with value: T, P or A
  letter = server.arg("sensor");                   // T entered on browser, read temperature
  if(letter == "T") reading = bmp.readTemperature();
// P entered on browser, read pressure
  else if(letter == "P") reading = bmp.readPressure()/100.0;
  else if(letter == "A")      // A entered on browser, read altitude
  {
    reading = 10.0 + bmp.readPressure()/100.0;  // assumed sea level pressure
    reading = bmp.readAltitude(reading);    // predicted altitude
  }
  msg = letter +": "+ String(reading);    // string "T" or "P" or "A" and reading
  server.send(200,"text/plain", msg);   // activated by /BMP?sensor=T   or
}         //                     /BMP?sensor=P   or
//                     /BMP?sensor=A
void loop()
{
  server.handleClient();
}

