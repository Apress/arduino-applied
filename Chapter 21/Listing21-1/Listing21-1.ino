/*******************************************************************************
 * Sketch name: sleep mode with avr/sleep module
 * Description: microcontroller in sleep mode with interrupt to "wake"
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 21 - Power saving
 ******************************************************************************/

#include <avr/sleep.h>      // include avr/sleep library
int LEDpin = 11;
int wakePin = 2;        // pin connected to interrupt 0

void setup()
{
  pinMode(LEDpin, OUTPUT);      // LED pin as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);   // turn off built-in LED
}

void loop()
{
  delay(500);
  digitalWrite(LEDpin, LOW);      // turn LED on and off after sleep mode
  sleep();          // function to set sleep mode
}

void sleep()
{
  attachInterrupt(0, wake, RISING);   // interrupt wake function
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // define sleep mode
 //sleep_enable();        // set sleep enable bit
 //sleep_cpu();       // initiate sleep
  sleep_mode();              // set sleep enable bit, initiate sleep and reset
  // sketch resumes here when interrupt triggered
 //sleep_disable();       // reset sleep enable bit
  detachInterrupt(0);       // effectively debounces switch interrupt
}

void wake()       // wake interrupt function
{
  digitalWrite(LEDpin, HIGH);      // turn LED on
}

