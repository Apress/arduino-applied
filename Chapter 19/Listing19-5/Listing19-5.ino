/*******************************************************************************
 * Sketch name: logging GNSS data with an SD card
 * Description: extend Listing 19-3 to store positional data on SD card
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
#include <SD.h>       // include SD library
File file;          // associate file with SD library
String filename = "data.csv";     // filename
int CSpin = 10;       // chip select pin for SD card
int i = 0;          // data record counter
String header, data, hr, mn, s;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  if(SD.begin(CSpin) == 0)      // check for presence of SD card
  {
    Serial.println("Card fail");      // return if SD card not found
    return;
  }
  Serial.println("Card OK");
  if(SD.exists(filename)) SD.remove(filename);  // delete existing file
  file = SD.open(filename, FILE_WRITE); // create new file
  if(file == 1)       // file opened
  {
    header = "Time, Latitude, Longitude, Altitude, Speed, Satellites";  // column headers
    file.println(header);               // write column headers to SD card
    file.close();                 // close file after writing to SD card
  }
  else Serial.println("Couldn't access file");  // file not opened
  AltSoft.begin(9600);      // serial connection to GPS module
}

void loop()
{
  while (nmea.available(AltSoft))   // GPS data available
  {
    i++;          // increase data record counter
    Serial.print("record ");Serial.println(i);    // print record number to Serial Monitor
    gps = nmea.read();      // latest satellite message
    hr = String(gps.dateTime.hours);    // leading zeros for time
    if(gps.dateTime.hours<10) hr = "0"+hr;
    mn = String(gps.dateTime.minutes);
    if(gps.dateTime.minutes<10) mn="0"+mn;
    s = String(gps.dateTime.seconds);
    if(gps.dateTime.seconds<10) s="0"+s;
    data = hr + mn+ s;      // create string of readings
    data = data + "," + String(gps.latitude(),4) + "," + String(gps.longitude(),4);
    data = data + "," + String(gps.altitude(),1) + "," + String(gps.speed_kph(), 1);
    data = data + "," + String(gps.satellites);
    file = SD.open(filename, FILE_WRITE); // open file on SD card
    file.println(data);       // write data to SD card
    file.close();       // close file on SD card
  }
}

