/*******************************************************************************
 * Sketch name: mobile GNSS with screen
 * Description: display positional data on ST7735 screen store data on SD card
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 19 - Global navigation satellite system
 ******************************************************************************/

#include <AltSoftSerial.h>      // include AltSoftSerial library
AltSoftSerial AltSoft;                 // associate AltSoft with AltSoftSerial library
#include <NMEAGPS.h>      // include NeoGPS library
NMEAGPS nmea;       // associate nmea with NMEAGPS library
gps_fix gps;        // associate gps with NMEAGPS library
#include <SPI.h>        // include SPI library
#include <SD.h>       // inclde SD library
String filename;
String basefile = "data";     // default filename is data.csv
bool filefound = false;     // checks if filename exists
int filecount = 0;        // adds number to filename
int SDcount = 0;        // counter to write to SD card
int nsat = 0;       // last number of satellites
float oldlat = 0;       // last latitude
float oldlong = 0;        // last longitude
#include <Adafruit_ST7735.h>    // include the ST7735 library
#include <Adafruit_GFX.h>     // include the GFX library
int TFT_CS = 6;       // screen chip select pin
int RSTpin = 7;       // screen reset pin
int DCpin = 9;        // screen DC pin
int SD_CS = 10;       // SD card chip select pin
             // associate tft with Adafruit_ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, DCpin, RSTpin);
String fill;
String data;        // GPS output converted to string
char text[6];       // string converted to characters

void setup()
{
  tft.initR(INITR_BLACKTAB);      // initialize ST7735 TFT LCD screen
  tft.fillScreen(ST7735_BLACK);   // clear screen
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK); // text colour with over-write
  AltSoft.begin(9600);      // serial connection to GPS module
  if(SD.begin(SD_CS) == 0)      // check for presence of SD card
  {
    printScreen("Card fail", 10, 5, 2);   // return if SD card not found
    return;
  }
  printScreen("Card OK", 10, 5, 2);
  delay(1000);
  filename=basefile+".csv";     // option to delete and replace file
  //if(SD.exists(filename)>0) SD.remove(filename);    // delete existing file
  while (filefound == 0)      // search for file with filename
  {
    if(SD.exists(filename))     // if filename already exists on SD card
    {
      filecount++;        // then increment filename counter
      filename = basefile + String(filecount) + ".csv";   // generate new filename
    }
    else filefound = true;      // file with filename located on SD card
  }
  data = "Time, Latitude, Longitude, Altitude, Speed, Satellites";  // column header
  File file = SD.open(filename, FILE_WRITE);  // open file on SD card
  if(file == 1) file.println(data);     // write header to SD card
  file.close();
  tft.fillScreen(ST7735_BLACK);   // clear screen
  printScreen("Speed & satellites", 9, 5, 1); // print fixed text
  printScreen("Altitude", 8, 50, 1);
  printScreen("Latitude & longitude", 8, 95, 1);
}

void loop()
{
  while (nmea.available(AltSoft))   // GPS data available
  {
    gps = nmea.read();
    if(gps.valid.time) data = String(gps.dateTime.hours) + ":" + 
    String(gps.dateTime.minutes)+ ":" + String(gps.dateTime.seconds);
    else data ="99:99:99";
    if(gps.valid.location) data = data + "," + String(gps.latitude(), 4) + "," + 
    String(gps.longitude(), 4);
    else data = data +",,96";     // default values while waiting for position
    if(gps.valid.altitude) data = data +","+ String(gps.altitude(), 1);
    else data = data +",97";
    if(gps.valid.speed) data = data +","+ String(gps.speed_kph(), 4);
    else data = data +",98";
    if(gps.satellites>0) data = data +","+ String(gps.satellites);
    else data = data +",99";
    SDcount++;
    if(SDcount>4)       // write to SD card every 5 seconds
    {
     File file = SD.open(filename, FILE_WRITE); // write to SD card NEED File declaration
      if(file) file.println(data);      // write data string to file on SD card
      file.close();       // close file on SD card
      SDcount = 0;        // reset counter
    }
    if(gps.speed_kph()<10)      // print speed (kmph)
    {
      fill = " "+ String(gps.speed_kph(), 1);   // convert numbet to string
      fill.toCharArray(text,6);     // convert string to characters
    }
    else String(gps.speed_kph(), 1).toCharArray(text,6);
    printScreen(text, 10, 20, 3);
    if(nsat != gps.satellites)
    {
      if(nsat<10) fill = " "+ String(gps.satellites);
      else fill = String(gps.satellites);   // print satellite number
      fill.toCharArray(text,6);
      printScreen(text, 100, 20, 2);
      nsat = gps.satellites;      // current satellite number
    }
    if(gps.altitude()<100)fill = " "+ String(gps.altitude(), 1);
    else fill = String(gps.altitude(), 1);    // print altitude
    fill.toCharArray(text,6);
    printScreen(text, 10, 65, 3);
    if(abs(oldlat-gps.latitude())>0.1 || abs(oldlat-gps.latitude())>0.1)
    {         // update latitude and longitude
      String(gps.latitude(), 1).toCharArray(text,6);
      printScreen(text, 10, 110, 2);    // print latitude
      String(gps.longitude(), 1).toCharArray(text,6);
      printScreen(text, 70, 110, 2);    // print longitude
      oldlat = gps.latitude();      // current latitude
      oldlong = gps.longitude();      // current longitude
    }
  }
}

void printScreen(char *text, int x, int y, int textSize)    // function to print to screen
{
  tft.setCursor(x, y);
  tft.setTextSize(textSize);
  tft.print(text);
}

