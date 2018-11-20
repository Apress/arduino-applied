/*******************************************************************************
 * Sketch name: temperature and time display
 * Description: control temperature and time display with one 74HC595 shift register
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 6 - 4-digit 7-segment LED display
 ******************************************************************************/

int dataPin = 2;          // shift register DATA pin
int latchPin = 3;         // shift register LATCH pin
int clockPin = 4;         // shift register CLOCK pin
int digits[ ] = {10,11,12,13};        // four digit pins
int numbers[ ] = {63,6,91,79,102,109,125,7,127,111};  // "values" of numbers 0 to 9
int del = 5;          // delay after turning digit on
int tempPin = A5;         // temperature sensor pin
int duration = 5000;          // display duration
unsigned long start;
int time, n, temp, reading;

void setup()
{
  pinMode (dataPin, OUTPUT);               // define shift register DATA pin as output
  pinMode (latchPin, OUTPUT);              // define shift register LATCH pin as output
  pinMode (clockPin, OUTPUT);              // define shift register CLOCK pin as output
  for (int i = 0; i<4; i++) pinMode (digits[i], OUTPUT);  // four digit pins as output
  analogReference (INTERNAL);   // set ADC voltage to 1.1V rather than 5V
}

void loop()
{
  start = millis();       // milliseconds elapsed
  while (millis()-start<duration)     // first duration, display time
  {
    time = millis()/1000;     // time in elapsed seconds
    digit(0, time/1000, 0);     // digit D1 for thousands
    digit(1, (time%1000)/100, 0);   // digit D2 for hundreds
    digit(2, (time%100)/10, 0);     // digit D3 for tens
    digit(3, time%10, 0);     // digit D4 for units
  }
  reading = analogRead(tempPin);    // temperature reading
  temp = 10.0*(reading*110.0)/1023.0;   // multiplier to get decimal place
          // second duration, display temperature
  while (millis()-start>duration && millis()-start<2*duration)
  {
    digit(1, (temp%1000)/100, 0);   // digit D2 for tens
    digit(2, (temp%100)/10, 1);     // digit D3 for units 1 for DP
    digit(3, temp%10, 0);     // digit D4 for decimal places
  }
}

void digit(int d, int n, int DP)
{
  for (int i = 0; i<4; i++) digitalWrite(digits[i], 1);   // turn all digits off, digit states are HIGH
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numbers[n]+DP*128); // add 128 for DP
  digitalWrite(latchPin, HIGH);       // change display pattern
  digitalWrite(digits[d], 0);       // turn digit on, digit state LOW
  delay(del);         // delay del (ms)
}

