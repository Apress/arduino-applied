/*******************************************************************************
 * Sketch name: display content of file
 * Description: display content of file data.csv stored on SD card
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

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  if(SD.begin(CSpin) == 0)      // check for presence of SD card
  {
    Serial.println("Card fail");                // return to void setup() if SD card not found
    return;
  }
  Serial.println("Card OK");
  file = SD.open(filename);       // open file to read
  while (file.available()>0) Serial.write(file.read());   // display contents of file
  file.close();         // close file after reading
}

void loop()
{ }
