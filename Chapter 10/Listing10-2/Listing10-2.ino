/*******************************************************************************
 * Sketch name: IR signal and LEDs
 * Description: use infrared signals to control switching of LEDs
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 10 - Infrared sensor
 ******************************************************************************/

#include <IRremote.h>  // include IR library
int IRpin = 6;    // IR sensor pin
IRrecv irrecv(IRpin);   // map IR receiver to pin
decode_results reading; // IRremote reading
int redLED = 8;
int amberLED = 9;     // LED pins
int greenLED = 10;
int colour;

void setup()
{
  irrecv.enableIRIn();      // initialise the IR receiver
  pinMode(redLED, OUTPUT);      // define LED pins as output
  pinMode(amberLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  if(irrecv.decode(&reading))     // read the IR signal
  {
    switch(reading.value)     // switch ... case for button signals
    {
      case 0xFF30CF: colour = redLED; break;  // associate IR codes with LED pins
      case 0xFF18E7: colour = amberLED; break;
      case 0xFF7A85: colour = greenLED; break;
    }
    digitalWrite(colour,HIGH);      // turn on and off corresponding LED
    delay(1000);
    digitalWrite(colour,LOW);
  }
  irrecv.resume();        // receive the next infrared signal
  delay(1000);        // delay before next remote control input
}

