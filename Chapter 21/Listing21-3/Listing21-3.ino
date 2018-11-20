/*******************************************************************************
 * Sketch name: power saving with PIR sensor interrupt
 * Description: microcontroller in sleep mode with motion activated interrupt to wake
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 21 - Power saving
 ******************************************************************************/

#include <LowPower.h>      // include LowPower library
int LEDpin = 11;        // LED pin
int PIRpin = 2;         // interrupt on pin 2 (INT0 or interrupt 0)
int detect = 0;       // movement flag

void setup()
{
//  Serial.begin(9600);     // Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
//  pinMode(LED_BUILTIN, OUTPUT);     // turn off built-in LED
}

void loop()
{
  if(detect == 1)       // if movement detected
  {
    delay(3000);       // delay 30s as LED is ON
    digitalWrite(LEDpin, LOW);      // turn LED off
    delay(1000);        // delay 1s
  }
  detect = 0;       // reset movement flag
  digitalWrite(LEDpin, LOW);      // turn LED off
  for (int i = 0; i<4; i++)
  {           // four steps for turning LED
    digitalWrite(LEDpin, !digitalRead(LEDpin));     //      on and off twice
    delay(1000);          // LED on or off for 1s
  }
  sleep();          // call sleep function
}

void sleep()        // sleep function
{
//  Serial.println("sleep");      // print message to Serial Monitor
//  delay(10);        // time required to print before sleep
  attachInterrupt(0, wake, RISING);     // interrupt pin, wake function and mode
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);            // power down
  detachInterrupt(0);       // detach interrupt
}

void wake()       // wake interrupt function
{
//  Serial.println("Movement detected");    // print message to Serial Monitor
  digitalWrite(LEDpin, HIGH);     // turn LED on
  detect = 1;       // set movement flag
}

