/*******************************************************************************
 * Sketch name: infrared signal
 * Description: read infrared signal and display hexadecimal code of signal
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 10 - Infrared sensor
 ******************************************************************************/

#include <IRremote.h>       // include IRremote library
int IRpin = 6;        // IR sensor pin
IRrecv irrecv(IRpin);       // associate irrecv with IRremote library
decode_results reading;     // IRremote reading

void setup()
{
  Serial.begin(9600);       // set baud rate for Serial Monitor
  irrecv.enableIRIn();      // initialise the IR receiver
}

void loop()
{
  if(irrecv.decode(&reading))     // read pulsed signal
  {
    Serial.print("0x");       // print leading 0x for hexadecimal
    Serial.println(reading.value, HEX);   // print HEX code to Serial Monitor
    irrecv.resume();        // receive the next infrared signal
  }
  delay(1000);        // delay before next remote control input
}

