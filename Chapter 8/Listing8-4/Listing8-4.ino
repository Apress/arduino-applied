/*******************************************************************************
 * Sketch name: stepper motor with Stepper library
 * Description: move stepper motor and change motor speed
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 8 - Servo and stepper motors
 ******************************************************************************/

#include <Stepper.h>      // include Stepper library
int blue = 12;
int pink = 11;        // coil activation order on ULN2003
int yellow = 10;        // blue, pink, yellow, orange
int orange = 9;
int steps = 2038;       // steps per revolution
          // associate stepper with Stepper library
Stepper stepper(steps, blue, yellow, pink, orange);   // coil pairing order
int direct = 1;         // direction of rotation
int revTime;
float secs, revs;

void setup()
{
  Serial.begin(9600);                    // define Serial output baud rate
  Serial.println("rpm     time(s) revs");     // print header to Serial Monitor
}

void loop()
{
  for (int i = 2; i<19; i=i+2)                     // motor speed from 2 to 18 rpm
  {
    stepper.setSpeed(i);        // set motor speed (rpm)
    direct = -direct;         // change direction of rotation
    revTime = millis();       // set start time (ms)
    stepper.step(direct * steps/2);     // move number of steps
    revTime = millis()-revTime;       // time for half revolution (ms)
    delay(500);         // delay 0.5s
    secs = revTime/1000.0;        // time (s) to move steps
    revs = i*secs/60.0;       // check number of revolutions
    Serial.print(i);Serial.print("\t");     // print speed on Serial Monitor
    Serial.print(secs);Serial.print("\t");      // print time
    Serial.println(revs,3);       // print number of revolutions
  }
}

