/*******************************************************************************
 * Sketch name: Numbers zero to nine in Table 5.2
 * Description: use shift register to display zero to nine on 7-segment LED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 5 - Seven segment LED display
 ******************************************************************************/

int clockPin = 2;    // shift register CLOCK pin
int latchPin = 3;    // shift register LATCH pin
int dataPin = 4;    // shift register DATA pin
int num[ ] = {63,6,91,79,102,109,125,7,127,111};  // representation of numbers 0 to 9

void setup()
{
  pinMode (clockPin, OUTPUT);               // define shift register CLOCK pin as output
  pinMode (latchPin, OUTPUT);              // define shift register LATCH pin as output
  pinMode (dataPin, OUTPUT);               // define shift register DATA pin as output
}

void loop()
{
  for (int i=0; i<10; i++)    // for each number 0 to 9
  {
    digitalWrite(latchPin, LOW);     // set the latch to LOW
    shiftOut(dataPin,clockPin,MSBFIRST,num[i]);    // LED states as a number
    digitalWrite(latchPin, HIGH);     // change number pattern
    delay(1000);      // delay 1s
  }
}

