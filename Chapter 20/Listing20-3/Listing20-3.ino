/*******************************************************************************
 * Sketch name: rotary encoder with LED in interrupt
 * Description: include interrupt to detect all turns of rotary encoder
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int DTpin= 9;        // pin B or data pin
int SWpin= 2 ;        // switch pin
int LEDpin = 11;        // LED on PWM pin
volatile int bright = 120;      // initial LED value
int fade = 10;        // amount to change LED
int rotate = 0;       // number of rotary turns
volatile int SW = 0;
volatile int change;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  pinMode(SWpin, INPUT_PULLUP);   // switch pin uses internal pull-up resistor
  attachInterrupt(1, encoder, FALLING);   // detect change in rotary encoder
  attachInterrupt(0, turnOff, FALLING);   // detect switch change
}

void loop()
{
  rotate = rotate + abs(change);    // number of turns of rotary encoder
  bright = bright + change*fade;    // change LED brightness
  bright = constrain(bright, 0, 255);   // constrain LED brightness
  if(change != 0)
  {
    Serial.print(rotate);Serial.print("\t");    // display number of rotary turns
    Serial.println(bright);     //     and LED brightness
  }
  analogWrite(LEDpin, bright);      // update LED brightness
  change = 0;       // reset change
  delay(3000);        // delay to verify interrupt functioning
}

void encoder()        // interrupt to detect rotations
{
  int newB = digitalRead(DTpin);    // state of (DAT) pin B
  change = change + (2*newB - 1);          // number of changes and direction of rotation
}

void turnOff()        // interrupt for switch
{
  bright = 0;
  analogWrite(LEDpin, bright);
}

