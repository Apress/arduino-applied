/*******************************************************************************
 * Sketch name: timed events with millis()
 * Description: schedule event based on time sketch has been running
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int LEDpin = 7;          // LED pin
unsigned long LEDtime = 0;        // event time

void setup()
{
  pinMode(LEDpin, OUTPUT);        // LED pin as OUTPUT
}

void loop()
{
  if(millis()-LEDtime > 1000)       // 1s since event time
  {
    digitalWrite(LEDpin, !digitalRead(LEDpin));   // turn LED on or off
    LEDtime = millis();     // reset time that event last occurred
  }
}

