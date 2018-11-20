/*******************************************************************************
 * Sketch name: timed events with millis() and two LEDs
 * Description: schedule events based on time sketch has been running
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int Atime = 2900;          // time for event A: LED1 off
int Aevent = LOW;
int Btime = 100;          // time for event B: LED1 on
int Bevent = HIGH;
int Ctime = 500;          // time for event C: LED2 off
int Cevent = LOW;
int Dtime = 500;          // time for event D: LED2 on
int Devent = HIGH;
unsigned long lastEvent[ ] = {0, 0};      // time event last occurred
unsigned long timeNow;        // elapsed time in ms
int LED1 = 7;         // LED pins
int LED2 = 8;
int LD;

void setup()
{
  pinMode(LED1, OUTPUT);        // define LED pins as output
  pinMode(LED2, OUTPUT);
}

void loop()
{
  timeNow = millis();
  if(timeNow >= (lastEvent[0] + Atime) && digitalRead(LED1) == Aevent)
changeLED(Bevent, LED1, 1);
  else if(timeNow >= (lastEvent[0] + Btime) && digitalRead(LED1) == Bevent)
  changeLED(Aevent, LED1, 1);
  else if(timeNow >= (lastEvent[1] + Ctime) && digitalRead(LED2) == Cevent)
  changeLED(Devent, LED2, 2);
  else if(timeNow >= (lastEvent[1] + Dtime) && digitalRead(LED2) == Devent)
  changeLED(Cevent, LED2, 2);
}

void changeLED(int event, int LED, int LD)  // function to turn LED on or off
{
  digitalWrite(LED, event);     // change LED state
  lastEvent[LD-1] = timeNow;      // reset time that event last occurred
}

