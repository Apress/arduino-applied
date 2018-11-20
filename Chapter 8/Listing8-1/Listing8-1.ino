/*******************************************************************************
 * Sketch name: servo motor
 * Description: move servo motor clockwise and anti-clockwise incrementally
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 8 - Servo and stepper motors
 ******************************************************************************/

#include <Servo.h>        // include Servo library
Servo servo;        // associate servo with Servo library
int servoPin = 11;        // servo motor pin

void setup()
{
  servo.attach(servoPin);     // define servo motor pin to Servo library
}

void loop()
{
  for (int i=0; i<19; i++)
  {
    servo.write(10 * i);      // rotate to angles 0, 10, 20 … 180
    delay(500);       // delay 500ms between movements
  }
  for (int i=8; i>=0; i--)
  {
    servo.write(20 * i);      // rotate to angles 160, 140 … 0
    delay(500);       // delay 500ms between movements
  }
}

