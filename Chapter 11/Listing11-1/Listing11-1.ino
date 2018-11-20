/*******************************************************************************
 * Sketch name: content of MIFARE contactless card
 * Description: read and display content of MIFARE contactless card
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 11 - Radio frequency identification
 ******************************************************************************/

#include <SPI.h>    // include SPI library
#include <MFRC522.h> // include MFRC522 library
int RSTpin = 9;   // reset pin for MFRC522
int SDApin = 10;    // serial data pin
          // associate mfrc522 with MFRC522 library
MFRC522 mfrc522(SDApin, RSTpin);

void setup()
{
  Serial.begin(9600); // Serial output at 9600 baud
  SPI.begin();    // initialise SPI bus
  mfrc522.PCD_Init(); // initialise card reader
}

void loop()
{
  if(!mfrc522.PICC_IsNewCardPresent()>0) return;    // wait for a new card
  if(!mfrc522.PICC_ReadCardSerial()>0) return;    // read card content
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));    // print to Serial Monitor
}

