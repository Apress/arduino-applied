/*******************************************************************************
 * Sketch name: weather station
 * Description: stores date and time stamped weather station data on SD card
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 12 - SD card module
 ******************************************************************************/

#include <SD.h>        // include SD library
File file;          // associate file with SD library
String filename = "data.csv";     // filename
#include <DS3231.h>     // include DS3231 library
DS3231 rtc(SDA, SCL);     // associate rtc with DS3231 library
#include <dht.h>        // include dht library
dht DHT;          // associate DHT with dht library
int CSpin = 10;       // chip select pin for SD card
int lightPin = A3;        // light dependent resistor pin
int PCBpin = 6;       // PCB mounted DHT11 pin
int i = 0;          // data record counter
int check, light, temp, humid;
String data, date, time;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  rtc.begin();        // start rtc
  Serial.println("checking SD card");   // check for presence of SD card
  if(SD.begin(CSpin) == 0)
  {
    Serial.println("Card fail");                // return to void setup() if SD card not found
     return;
  }
  Serial.println("Card OK");
  if(SD.exists(filename)>0) SD.remove(filename);    // delete old file
  file = SD.open(filename, FILE_WRITE);   // create new file
  if(file == 1)
  {
    String header = "record, time, light, temp, humid, on ";  // column headers
    header = header + String(rtc.getDateStr());   // ... and date
    file.println(header);       // write column headers to file
    file.close();                  // close file after writing to SD card
  }
  else Serial.println("Couldn't access file");    // file not opened
}

void loop()
{
  i++;            // increase data record counter
  Serial.print("record ");Serial.println(i);        // print record number to Serial Monitor
  light= analogRead(lightPin);        // light intensity reading
  check = DHT.read11(PCBpin);
  temp = DHT.temperature;       // temperature reading
  humid = DHT.humidity;       // humidity reading
  time = rtc.getTimeStr();        // time stamp
    // combine measurements into a string
  data = String(i) + "," + String(time) + "," + String(light);
  data = data + "," + String(temp)+ "," + String(humid);
  file = SD.open(filename, FILE_WRITE);   // open data file before writing
  file.println(data);         // write data string to file
  file.close();                  // close file after writing to SD card
  delay(1000);// delay 1s before next reading
}

