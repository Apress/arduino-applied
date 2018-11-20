/*******************************************************************************
 * Sketch name: display brightness dependent on incident light
 * Description: shift register with PWM to control display brightness on 7-segment LED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 5 - Seven segment LED display
 ******************************************************************************/

int clockPin = 2;        // shift register CLOCK pin
int latchPin = 3;       // shift register LATCH pin
int dataPin = 4;        // shift register DATA pin
int num[ ] = {63,6,91,79,102,109,125,7,127,111};  // representation of numbers 0 to 9
int Vdivid = A5;        // voltage divider pin
int PWMpin = 11;        // shift register OE pin used for PWM
int reading, bright;

void setup()
{
  pinMode (clockPin, OUTPUT);              // define shift register CLOCK pin as output
  pinMode (latchPin, OUTPUT);              // define shift register LATCH pin as output
  pinMode (dataPin, OUTPUT);               // define shift register DATA pin as output
}

void loop()
{
  for (int i=0; i<10; i++)        // for each number 0 to 9
  {
    reading = analogRead(Vdivid);     // voltage divider reading
    bright = map(reading, 0, 1023, 255, 0);              // map reading to LED brightness
    analogWrite(PWMpin, bright);      // change LED brightness
    digitalWrite(latchPin, LOW);        // set the latch to LOW
    shiftOut(dataPin,clockPin,MSBFIRST,num[i]);   // LED states as a number
    digitalWrite(latchPin, HIGH);     // change number pattern
    delay(1000);          // delay 1s
  }
}

