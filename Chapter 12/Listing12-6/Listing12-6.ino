/*******************************************************************************
 * Sketch name: display contents of SD card
 * Description: display content(directories and file names) of SD card
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 12 - SD card module
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <SD.h>       // include SD library
File file;          // associate file with SD library
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
  file = SD.open("/");        // open SD directory of file information
  list(file, 0);        // function to display file information
}

void loop()       // nothing in void loop() function
{ }

void list(File direct, int nfiles)      // function to display file information
{
  while (1)
  {
    File entry =  direct.openNextFile();    // next file in directory
    if (entry == 0) break;      // stop at end of directory
    if (entry.isDirectory())
    {
      Serial.print(entry.name());Serial.println("\tis a directory");     
      list(entry, nfiles+1); // only list details of files
    }
    else
    {
      Serial.print(entry.name());Serial.print("\t");  // display file name
      Serial.println(entry.size());     // display file size (bytes)
    }
    entry.close();
  }
}

