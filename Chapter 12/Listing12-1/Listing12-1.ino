/*******************************************************************************
 * Sketch name: micro SD card module with sensors
 * Description: write to SD card every 5s the temmperature and light intensity
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 12 - SD card module
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <SD.h>       // include SD library
File file;          // associate file with SD library
String filename = "data.csv";     // filename
int CSpin = 10;       // chip select pin
int lightPin = A0;        // LDR light intensity pin
int tempPin = A1;       // temperature sensor pin
int i = 0;          // data record counter
int light;
float temp;
String data;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  Serial.println("checking SD card");   // print message to Serial Monitor
  if(SD.begin(CSpin) == 0)      // check for presence of SD card
  {
    Serial.println("Card fail");                // return to void setup() if SD card not found
    return;
  }
  Serial.println("Card OK");
  if(SD.exists(filename)>0) SD.remove(filename);    // delete existing file
  file = SD.open(filename, FILE_WRITE);   // create new file
  if(file == 1)         // file opened
  {
    String header = "i, light, temp";   // create column headers
    file.println(header);     // write column header to SD card
    file.close();       // close file after writing to SD card
  }
  else Serial.println("Couldn't access file");  // file not opened
}

void loop()
{
  i++;          // increase data record counter
  Serial.print("record ");Serial.println(i);    // print record number to Serial Monitor
  light = analogRead(lightPin);     // light reading
  temp = (500.0*analogRead(tempPin))/1023;  // temp reading referenced to 5V
  data = String(i) + "," + String(light) + "," + String(temp);     // create string from readings
  file = SD.open(filename, FILE_WRITE); // open data file before writing
  file.println(data);       // write data string to file
  file.close();       // close file after writing to SD card
  delay(5000);        // delay 5s before next reading
}

