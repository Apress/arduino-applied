/*******************************************************************************
 * Sketch name: updated void loop
 * Description: control servo motor rotation with potentiometer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 8 - Servo and stepper motors
 ******************************************************************************/

#include <Servo.h>        // include Servo library
Servo servo;        // associate servo with Servo library
int servoPin = 11;        // servo motor pin
int potPin = A1;      // potentiometer pin
int reading, angle;

void setup()
{
  servo.attach(servoPin);     // define servo motor pin to Servo library
}

void loop()
{
  reading = analogRead(potPin);             // potentiometer voltage
  angle = map(reading, 0, 1023, 5, 175);    // map voltage to angle
  servo.write(angle);             // move servo to angle
  delay(10);             // delay 10ms
}


