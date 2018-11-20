/*******************************************************************************
 * Sketch name: scrolling text on 8x8 dot matrix display
 * Description: use two 74HC595 shift registers to scroll text on 8x8 dot matrix
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 7 - 8x8 dot matrix display
 ******************************************************************************/

#include "letters.h"          // include letter data
int dataPin = 2;          // shift register DATA pin
int latchPin = 3;         // shift register LATCH pin
int clockPin = 4;         // shift register CLOCK pin
byte cols[8];
char data;
int n;
unsigned long start;

void setup()
{
  Serial.begin(9600);                // define Serial output baud rate
  pinMode (dataPin, OUTPUT);               // define shift register DATA pin as output
  pinMode (latchPin, OUTPUT);              // define shift register LATCH pin as output
  pinMode (clockPin, OUTPUT);              // define shift register CLOCK pin as output
}

void loop()
{
  while (Serial.available()>0)      // message read from Serial Monitor
  {
    data=Serial.read();     // message read one letter at a time
    Serial.print(data);
          // decimal representation of letter
    for (int lett=0; lett<63 ;lett++) if(data == letters[lett]) n=lett;
    for (int i=0; i<8;i++)      // convert row to column orientation
    {
      cols[i]=0;        // change to column orientation
      for (int j=0; j<8; j++) cols[i]= cols[i] + (bitRead(val[n][j],i)<<j);
    }
    for (int t=0;t<12;t++)      // move character through 12 shifts
    {         // across the 88 dot matrix display
      start = millis();       // elapsed time (ms)
      while (millis() - start <60)      // 60 ms to display character
      for (int c=0; c<8; c++)     // display with column scanning
      {
        if(8+c-t>0) 
        {
          digitalWrite(latchPin,LOW);           // change display pattern
          shiftOut(dataPin, clockPin, MSBFIRST,~cols[c]);
          shiftOut(dataPin, clockPin, MSBFIRST, (1<<7+c-t));       // shift by one column
          digitalWrite(latchPin,HIGH);
        }
      }
    }
  }
}

