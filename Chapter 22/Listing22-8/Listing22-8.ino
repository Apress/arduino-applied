 /*******************************************************************************
 * Sketch name: square wave with PWM
 * Description: square wave with duty cycle controlled by potentiometer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

#include <PWM.h>        // include PWM library
unsigned long freq =10000;     // required frequency (Hz)
int potPin = A0;        // potentiometer pin
int PWMpin = 10;        // use pin 9 or 10 (Timer1)
int setFreq;

void setup()
{
  pinMode(PWMpin, OUTPUT);    // define PWMpin as OUTPUT
  InitTimersSafe();       // does not impact Timer0
  setFreq = SetPinFrequencySafe(PWMpin, freq);  // does not impact Timer0
}

void loop()
{
  pwmWrite(PWMpin, analogRead(potPin)/4);   // output square wave with duty
}

