/*******************************************************************************
 * Sketch name: rotary encode and LED
 * Description: use rotary encoder to control LED brightness
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 9 - Rotary encoder
 ******************************************************************************/

int CLKpin= A0;        // pin A or clock pin
int DTpin= A1;        // pin B or data pin
int SWpin= A2 ;       // switch pin
int LEDpin = 6;       // LED on PWM pin
int bright = 120;       // initial LED value
int fade = 10;        // amount to change LED
int rotate = 0;       // number of rotary turns
int oldA = HIGH;        // status of pin A
int change, result, newA, newB;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  pinMode(SWpin, INPUT_PULLUP);   // switch pin uses internal pull-up resistor
}

void loop()
{
  if(digitalRead(SWpin) == LOW) bright = 0; // switch, active LOW,  turns off the LED
  change = encoder();     // direction of rotation
  rotate = rotate + abs(change);    // number of turns of rotary encoder
  bright = bright + change*fade;    // change LED brightness
  bright = constrain(bright, 0, 255);   // constrain LED brightness
  if(change != 0)
  {
    Serial.print(rotate);Serial.print("\t");    // display number of rotary turns
    Serial.println(bright);     //     and LED brightness
  }
  analogWrite(LEDpin, bright);      // update LED brightness
}

int encoder()       // function to determine direction
{
  result = 0;
  newA = digitalRead(CLKpin);       // state of (CLK) pin A
  newB = digitalRead(DTpin);        // state of (DT) pin B
// falling edge on (CLK) pin A
  if (oldA == HIGH && newA == LOW) result = 2*newB - 1;
  oldA = newA;          // update state of (CLK) pin A
  return result;
}

