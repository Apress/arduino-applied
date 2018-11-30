/*******************************************************************************
 * Sketch name: HTML webpage
 * Description: display date and time data from NTP with atmospheric measurements
 *              from BMP280 sensor on a webpage with a button to control the LED
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
#include <Wire.h>       // Wire library
#include <Adafruit_Sensor.h>      // Unified Sensor library
#include <Adafruit_BMP280.h>    // BMP280 library
Adafruit_BMP280 bmp;            // associate bmp with Adafruit_BMP280 library
int BMPaddress = 0x76;      // I2C address of BMP280
int LEDpin = D8;        // LED pin defined with D8
String LEDvalue = "OFF";
#include <NTPtimeESP.h>     // include NTPtime library
// associate NTP with NTPtime library
NTPtime NTP("uk.pool.ntp.org");   // UK server pool for NTPtime
String stringTime, stringDate, stringDay;
String days[ ] = 
          {" ","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String months[ ] = 
          {" ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
strDateTime dateTime;
float temperature, pressure, altitude, BasePressure;
byte hh, mm, ss, month, day, dayofweek;
int yr;

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
  bmp.begin(BMPaddress);      // initialise BMP280 sensor
}

void webpage()        // function to collect data for webpage
{
  button();           // obtain LED button status
  temperature = bmp.readTemperature();      // BMP280 measurements
  pressure = bmp.readPressure()/100.0;      // temperature and pressure
  BasePressure = pressure + 10.0;     // assumed sea level pressure
  altitude = bmp.readAltitude(BasePressure);    // predicted altitude
  getTime();          // obtain date and time
  server.send (200, "text/html", buildPage());    // publish webpage
  delay(1000);          // delay 1000ms
}

void getTime()          // function to get NTP time
{
  dateTime = NTP.getNTPtime(0, 1);      // get date and time
  if(dateTime.valid)
 {
    hh = dateTime.hour;       // extract hour (0 to 24)
    mm = dateTime.minute;       // extract minutes
    ss = dateTime.second;       // extract seconds
    yr = dateTime.year;       // extract year
    month = dateTime.month;       // extract month
    day = dateTime.day;       // extract day (1 to 31)
    dayofweek = dateTime.dayofWeek;     // extract day of week (1 to 7)
    if(ss<10) stringTime = ":0"+String(ss);     // leading zero for seconds <10
    else stringTime = ":"+String(ss);
    if(mm<10) stringTime = String(hh)+":0"+String(mm) + stringTime;
    else stringTime = String(hh)+":"+String(mm) + stringTime;
    stringDate = String(day)+" "+String(months[month])+" "+String(yr);
    stringDay = days[dayofweek];      // convert data to strings
  }
}

void button()         // function of LED button status
{
  if (server.hasArg("LED")) LEDvalue = server.arg("LED");             // read LED button state
  if (LEDvalue == "ON") digitalWrite(LEDpin, HIGH);            // turn LED on or off
  else digitalWrite(LEDpin, LOW);
}

String buildPage()               // function to build webpage
{
  String page = "<!DOCTYPE html><html><head>";    // head section
  page += "<meta http-equiv='refresh' content='1'>";         // webpage refresh rate (s)
  page += "<title>Arduino Applied</title>";
  page += "<style> body {font-family: Arial}";      // define styles
  page += ".button {padding: 15px 15px; font-size: 20px}</style></head>";
  page += "<body><h1>Arduino Applied</h1>";     // body section
  page += "<span style='font-size: 20px'>Time of day</span>"; // data and time
  page += "<ul><li>Time: <span style='font-size:30px'>"+stringTime+"</span></li>";
  page += "<li>Date: "+stringDate+"</li>";
  page += "<li>Day of week: "+stringDay+"</li></ul>";
  page += "<p><span style='font-size: 20px'>Sensor</span></p>"; // sensor readings
  page += "<ul><li>Temperature: ";
  page += "<span style='font-size:30px'>"+String(temperature)+"&deg;C</span></li>";
  page += "<li>Pressure: "+String(pressure)+" hPa</li>";
  page += "<li>Altitude: "+String(altitude)+" m</li></ul>";
  page += "<span style='font-size: 20px'>LED</span>";
  page += "<form action='/' method='post'>";      // LED buttons
  page += "<input type='submit' class='button' name='LED' value='ON'>";
  page += "<span class='checkmark'></span>&emsp;";
  page += "<input type='submit' class='button' name='LED' value='OFF'>";
  page += "<span class='checkmark'></span></form>";
  page += "</body></html>";
  return page;            // return HTML code
}

void loop()
{
  server.handleClient();
}

