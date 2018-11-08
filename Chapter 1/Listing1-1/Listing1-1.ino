/*******************************************************************************
 * Sketch name: Sketch to blink an LED
 * Description: Blinks an LED on pin 11
 * Created on:  October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 1 - Introduction
 ******************************************************************************/

int LEDpin = 11;        // define LEDpin with integer value 11
void setup()        // setup function runs once
{
  pinMode(LEDpin, OUTPUT);      // define LEDpin as output
}

void loop()       // loop function runs continuously
{
  digitalWrite(LEDpin, HIGH);     // set pin state HIGH to turn LED on
  delay(1000);        // wait for a second = 1000 ms
  digitalWrite(LEDpin, LOW);      // set pin state LOW to turn LED off
  delay(1000);
}

