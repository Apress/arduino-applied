/*******************************************************************************
 * Sketch name: IR transmitter
 * Description: transmit infrared signals
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 10 - Infrared sensor
 ******************************************************************************/

#include <IRremote.h>      // include IRremote library
long signal[ ] = {0xFF6897, 0xFF30CF, 0xFF18E7, 0xFF7A85, 0xFF10EF};
IRsend irsend;        // associate irsend with IRremote library
int LEDpin = 7;

void setup()        // nothing in void setup function
{
  pinMode(LEDpin, OUTPUT);
}

void loop()
{
  for (int i=0; i<5; i++)     // transmit each of the five signals
  {
    irsend.sendSony(signal[i], 24);   // transmit signal with 24 bit length
    delay(1000);        // delay 1s between signals
  }
}

