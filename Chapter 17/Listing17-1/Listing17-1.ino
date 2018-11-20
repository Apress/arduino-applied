/*******************************************************************************
 * Sketch name: channel scanning
 * Description: scan transmission channles for activity
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 17 - Wireless communication
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <RF24.h>       // include RF24 library
RF24 radio(7, 8);       // associate radio with RF24 library
const int nChan = 126;      // 126 channels available
int chan[nChan];        // store counts per channel
int nScan = 100;        // number of scans per channel
int scan;

void setup()
{
  Serial.begin(9600);       // define Serial output baud rate
  radio.begin();        // start radio
}

void loop()
{
  for (int i=0;i<nChan;i++)     // for each channel
  {
    chan[i] = 0;        // reset counter
    for (scan=0; scan<nScan; scan++)    // repeat scanning
    {
      radio.setChannel(i);      // define channel
      radio.startListening();
      delayMicroseconds(128);     // listen for 128s
      radio.stopListening();
      if(radio.testCarrier()>0) chan[i]=chan[i]+1;  // a carrier on the channel
    }
  }       // format in HEX for values up to 16 rather than 10
  for (int i=0; i<nChan; i++) Serial.print(chan[i], HEX);
  Serial.print("\n");       // carriage return
}

