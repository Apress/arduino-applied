/*******************************************************************************
 * Sketch name: stepper motor and potentiometer
 * Description: control stepper motor rotation with potentiometer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 8 - Servo and stepper motors
 ******************************************************************************/

#include <AccelStepper.h>      // include Accelstepper library
int blue = 12;
int pink = 11;        // coil activation order on ULN2003
int yellow = 10;        // blue, pink, yellow, orange
int orange = 9;
int fullstep = 4;       // number of coil activation stages
int coil = fullstep;        // set number of coil activation stages
                  // associate stepper with AccelStepper library
AccelStepper stepper(coil, blue, yellow, pink, orange); // coil pairing order
int steps = (coil/4)*2038;      // number of steps per revolution
int potPin = A1;       // potentiometer pin
int LEDpin = 6;       // LED on PWM pin
unsigned long revTime = 0;
float rpmMin = 10.0;      // minimum and maximum speed in rpm
float rpmMax = 21.0;
float speedMin = rpmMin*steps/60.0;     //         and in steps/s
float speedMax = rpmMax*steps/60.0;
float rpm;
int reading, speed, bright;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  stepper.setMaxSpeed(1500);      // set maximum speed (step/s)
}

void loop()
{
  reading = analogRead(potPin);   // potentiometer voltage
// map voltage to speed (step/s)
  speed = map(reading, 0, 1023, speedMin, speedMax);
  bright = map(reading, 0, 1023, 0, 255);   // map voltage to LED brightness
  analogWrite(LEDpin, bright);      // set LED brightness with PWM
  stepper.move(256);      // move the internal motor 256 steps
  stepper.setSpeed(speed);      // set the internal motor speed
  stepper.runSpeed();     // run the stepper motor
  if((stepper.currentPosition() % steps)==0)  // on each complete revolution
  {
    revTime = millis()-revTime;     // time (ms) for one revolution
    rpm = stepper.speed()*60.0/steps;   // stepper motor rpm
    Serial.print(revTime);      // print revolution time to Serial Monitor
    Serial.print(" ms\t\t");      // print "ms " and two tabs
    Serial.print(rpm, 2);     // print rpm with 2DP
    Serial.print(" rpm\t");     // print " rpm" and a tab
    Serial.print(stepper.speed(),0);    // print stepper motor speed with 0DP
    Serial.println(" steps/s");     // print " steps/s" and a new line
    delay(2);       // delay 2ms to prevent duplicates
    revTime=millis();       // update revolution start time
  }
}

