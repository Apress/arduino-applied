/*******************************************************************************
 * Sketch name: stepper motor with Accelstepper library
 * Description: move stepper motor and change motor speed with fixed accelaration
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
int halfstep = 8;       //        with full-step and half-step
int coil = halfstep;        // set to full-step or to half-step
                  // associate stepper with AccelStepper library
AccelStepper stepper(coil, blue, yellow, pink, orange);       // coil pairing order
int steps = (coil/4)*2038;      // number of steps per revolution
long last = 0;
int lag = 500;        //time (ms) interval for display
int direct = 1;       // direction of rotation
float rpm, speed, oldspeed, accel;
int nsteps;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  stepper.setMaxSpeed((coil/4)*700);    // max speed 700 or 1400 steps/s
  stepper.setAcceleration(600);   // acceleration rate (steps/s2)
  Serial.println("steps   rpm     accel");    // print header to Serial Monitor
}

void loop()
{
  stepper.moveTo(direct*steps/2);   // move to position ±1019 or ±2038
  if(stepper.distanceToGo()==0) direct = -direct;       // change direction of rotation
  if(millis()>last + lag)     // lag time elapsed since last print
  {
    speed = stepper.speed();      // current motor speed (steps/s)
    nsteps = speed*lag/pow(10,3);   // steps/s taken during lag time
    Serial.print(nsteps);Serial.print("\t");    // display number of steps and a tab
    rpm = 60.0*speed/steps;      // derive rpm
    Serial.print(rpm,2);Serial.print("\t");   // display rpm to 2DP on Serial Monitor
    accel = (speed - oldspeed)*1000.0/lag;  // derived acceleration rate (steps/s2)
    Serial.println(accel,0);      // display acceleration
    oldspeed = speed;     // update speed value
    last = millis();        // update last print time
  }
  stepper.run();        // update motor to move to new position
}

