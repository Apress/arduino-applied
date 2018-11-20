/*******************************************************************************
 * Sketch name: I2C addresses
 * Description: display I2C address of connected devices  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>        // include Wire library
int device = 0;       // set device counter to 0

void setup()
{
  Serial.begin (9600);      // set Serial output baud rate
  Wire.begin();       // start I2C bus
  for (int i=8; i<127; i++)     // scan through channels 8 to 126
  {
    Wire.beginTransmission (i);     // transmit to device at address i
    if (Wire.endTransmission () == 0)   // device response to transmission
    {
      Serial.print("Address 0x");     // print to screen "Address 0x"
      Serial.println(i, HEX);     // print to screen I2C address in HEX
      device++;       // increment device count
      delay(10);        // delay 10ms
    }
  }
  Serial.print(device);     // print to screen device count
  Serial.println(" device found");    // print to screen " device found"
}

void loop()
{ }

