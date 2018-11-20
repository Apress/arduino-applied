/*******************************************************************************
 * Sketch name: display letters A, B and C with two shift registers
 * Description: use two 74HC595 shift registers to display letters on 8x8 dot matrix
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 7 - 8x8 dot matrix display
 ******************************************************************************/

// Arduino to display pins 
//int pin[ ] = {19,13,12,9,8,11,7,10,17,16,6,5,15,4,14,3,2};  
            // dot matrix display rows
//int row[ ] = {pin[9],pin[14],pin[8],pin[12],pin[1],pin[7],pin[2],pin[5]};
byte val[53][8] =     
{4,10,17,17,31,17,17,0, // A
15,17,17,15,17,17,15,0, // B
14,17,1,1,1,17,14,0};   // C
int dataPin = 2;          // shift register DATA pin
int latchPin = 3;         // shift register LATCH pin
int clockPin = 4;         // shift register CLOCK pin
unsigned long start;

void setup()
{
  pinMode (dataPin, OUTPUT);               // define shift register DATA pin as output
  pinMode (latchPin, OUTPUT);              // define shift register LATCH pin as output
  pinMode (clockPin, OUTPUT);              // define shift register CLOCK pin as output
//  for (int i=1; i<17; i++) pinMode(pin[i], OUTPUT);   // display pins as output
//  for (int i=0; i<8; i++) digitalWrite(row[i], HIGH);   // set cathodes HIGH, LEDs off
}

void loop()
{
  for (int n=0; n<53; n++)       // display the  letters A, B, C
  {
    start = millis();         // milliseconds elapsed
    while (millis()<start+1000)       // display time for each letter
    for (int r=0; r<8; r++)       // for each row of a letter
    {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, ~(1<<r));
      shiftOut(dataPin, clockPin, MSBFIRST,val[n][r]);  // change display pattern
      digitalWrite(latchPin,HIGH);
//      digitalWrite(row[r], LOW);      // set cathodes LOW, turn LED on
//      delayMicroseconds(200);     // delay between LEDs in a row
//      digitalWrite(row[r], HIGH);     // reset the cathodes to HIGH, LED off
    }
  }
}

