/*******************************************************************************
 * Sketch name: timed events with millis() and one LED
 * Description: schedule events based on time sketch has been running
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int Atime = 2000;          // time for event A: LED off
int Aevent = LOW;
int Btime = 100;          // time for event B: LED on
int Bevent = HIGH;
unsigned long lastEvent = 0;        // time event last occurred
unsigned long timeNow;        // elapsed time in ms
int LED = 7;          // LED pin

void setup()
{
  pinMode(LED, OUTPUT);       // LED pin as output
}

void loop()
{
  timeNow = millis();
  if(timeNow >= (lastEvent + Atime) && digitalRead(LED) == Aevent) changeLED(Bevent);
  else if(timeNow >= (lastEvent + Btime) && digitalRead(LED) == Bevent) changeLED(Aevent);
}

void changeLED(int event)       // function to turn LED on or off
{
  digitalWrite(LED, event);       // change LED state
  lastEvent = timeNow;              // reset time that event last occurred
}

