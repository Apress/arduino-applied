/*******************************************************************************
 * Sketch name: rotary encode and stepper motor
 * Description: use rotary encoder to control movement of stepper motor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 9 - Rotary encoder
 ******************************************************************************/

#include <AccelStepper.h>      // include stepper library
int blue = 12;        // coil activation order on ULN2003
int pink = 11;        // blue, pink, yellow, orange
int yellow = 10;
int orange = 9;
int fullstep = 4;       // number of coil activation stages
int halfstep = 8;       // with full-step and half-step
int coil = fullstep;        // set number of coil activation stages
                  // associate stepper with AccelStepper library
AccelStepper stepper(coil, blue, yellow, pink, orange); // coil pairing order
int stepperTarget = 500;      // initial position for stepper motor
int stepperChange = 200;                    // number of steps to move stepper motor
int CLKpin= A0;       // rotary encoder pin A
int DTpin= A1;        // pin B
int SWpin= A2 ;       // switch
int rotate = 0;       // number of rotary encoder turns
int oldA = HIGH;        // status of pin A
int direct = 1;       // direction of rotation
int LEDpin = 6;       // LED on PWM pin
int bright = 60;        // initial LED value
int fade = 25;        // amount to change LED
int change, result, newA, newB;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(SWpin, INPUT_PULLUP);     // switch pin uses internal pull-up resistor
  stepper.setMaxSpeed(700);     // maximum speed of stepper motor
  stepper.setAcceleration(600);   // acceleration rate (steps/s2)
}

void loop()
{
  if(digitalRead(SWpin) == LOW)
  {
    stepperTarget = 0;      // switch repositions stepper motor
    bright = 0;       // and turns off the LED
  }
  change = encoder();     // determine direction of rotary encoder
  rotate = rotate + abs(change);    // number of rotary encoder turns
// move stepper motor to new position
  stepperTarget = stepperTarget + change * stepperChange;
  stepperTarget = constrain(stepperTarget, 0, 2037);    // constrain position
  bright = bright + change*fade;      // change LED brightness
  bright = constrain(bright, 0, 255);     // constrain LED brightness
  if(change != 0)
  {
    Serial.print(rotate);Serial.print("\t");      // display number of rotary turn
    Serial.print(bright);Serial.print("\t");      // display LED brightness
    Serial.println(stepperTarget);      // and new target position
  }
  analogWrite(LEDpin, bright);      // update LED brightness
  stepper.moveTo(direct*stepperTarget/2);   // move to new target position
  if (stepper.distanceToGo() == 0) direct=-direct;    // reverse direction
  stepper.run();                      // instruct stepper motor to move
}

int encoder()                     // function to determine direction
{
  result = 0;
  newA = digitalRead(CLKpin);       // state of (CLK) pin A
  newB = digitalRead(DTpin);        // state of (DAT) pin B
// falling edge on (CLK) pin A
  if (oldA == HIGH && newA == LOW) result = 2*newB - 1;
  oldA = newA;          // update state of (CLK) pin A
  return result;
}

