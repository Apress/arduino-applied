/*******************************************************************************
 * Sketch name: timed events with Timer1
 * Description: schedule event based on overflow of Timer1 register
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

#include <TimerOne.h>      // include TIimerOne library
int LEDpin = 11;        // LED pin
int PWMpin = 9;       // must be pin 9 or 10
int freq = 20;       // frequency of 20Hz
unsigned long sec = pow(10,6);    // setup one second
unsigned long interval;
volatile int count = 0;
int countCopy, oldCount;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  interval = sec/(2*freq);      // define time period
  Timer1.initialize(interval);      // initialize timer
  Timer1.pwm(PWMpin, 0.5*1024);   // PWM duty cycle (50%)
  Timer1.attachInterrupt(LED);      // ISR as timer overflow interrupt
}

void loop()
{
  noInterrupts();       // stop the interrupt
  countCopy = count/2;      // make copy of counter
  interrupts();         // restart the interrupt
  if(countCopy > oldCount) Serial.println(countCopy); // display count
  oldCount = countCopy;       // update count
}

void LED()
{
  digitalWrite(LEDpin, !digitalRead(LEDpin)); // change LED status
  count = count + 1;        // increment counter
}

