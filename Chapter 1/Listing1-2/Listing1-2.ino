/*******************************************************************************
 * Sketch name: LED brightness and PWM
 * Description: LED brightness changed by PWM with controlled rate of change 
 * Created on:  October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 1 - Introduction
 ******************************************************************************/

int LEDpin = 11;      // define LED pin
int bright = 0;       // initial value for LED brightness
int increm = 5;       // incremental change in PWM frequency
int time = 25;        // define time period between changes

void setup()        // setup function runs once
{
  pinMode(LEDpin, OUTPUT);      // LED pin as output
}

void loop()       // loop function runs continuously
{
  analogWrite(LEDpin, bright);      // set LED brightness with PWM
  delay(time);        // wait for the time period
  bright = bright + increm;     // increment LED brightness
           // reverse increment at brightness = 0 or 255
  if(bright <=0 || bright >= 255) increm = - increm;
}


