/*******************************************************************************
 * Sketch name: incrementing filename
 * Description: increment dataN.csv filename when storing file on SD card
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 12 - SD card module
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <SD.h>       // include SD library
File file;          // associate file with SD library
int CSpin = 10;       // chip select pin for SD card
String filename;
String basefile = "data";     // default filename is data.csv
bool filefound = false;
int filecount = 0;        // for incrementing filename
int count = 0;
String data;        // data to write to SD card

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  if(SD.begin(CSpin) == 0)
  {
    Serial.println("Card fail");                  // return to void loop() if SD card not found
   return;
  }
  Serial.println("Card OK");
  filename=basefile + ".csv";     // generate filename
  // if(SD.exists(filename)>0) SD.remove(filename);         // delete and replace file on SD card
  while (filefound == 0)      // search for file with filename
  {
    if(SD.exists(filename)>0)     // if filename already exists on SD card,
    {
      filecount++;        // then increment filename counter
      filename = basefile + String(filecount) + ".csv";   // generate new filename
    }
    else filefound = true;                 // flag file with filename located on SD card
  }
  file = SD.open(filename, FILE_WRITE); // open file on SD card
  if(file == 1)
  {
    Serial.print(filename);Serial.println(" created");
    data = "Count";       // column header
    file.println(data);       // write column header to file on SD card
    file.close();       // close file after writing to SD card
  }
  else Serial.println("Couldn't access file");  // file not opened
}

void loop()
{
  count = count + 1;        // incremental counter
  data = String(count);     // convert counter to string
  File file = SD.open(filename, FILE_WRITE);  // open file on SD card
  if(file == 1) file.println(data);     // write data string to file on SD card
  file.close();       // close file on SD card
  delay(1000);        // delay 1s before next count
}

