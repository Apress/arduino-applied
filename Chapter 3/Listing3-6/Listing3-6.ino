/*******************************************************************************
 * Sketch name: ultrasonic distance sensor and NewPing library
 * Description: measure distance with HC-SR04 ultrasonic distance sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

#include <NewPing.h>      // include NewPing library
int trigPin = 6;        // trigger pin
int echoPin = 7;        // echo pin
int maxdist = 100;        // set maximum scan distance
int echoTime;       // echo time
float distance;       // distance
NewPing sonar(trigPin, echoPin, maxdist); // associate sonar with NewPing library

void setup()
{
  Serial.begin(9600); // set baud rate for Serial Monitor
}

void loop() 
{
  echoTime = sonar.ping();      // echo time (s)
  distance = (echoTime/2.0)*0.0343;   // distance between sensor and target
  Serial.print("echo time: ");      // print text "echo time: "
  Serial.print(echoTime);     // print echo time
  Serial.print(" microsecs\t");     // print text " microsecs" and tab
  Serial.print("distance: ");     // print text "distance: "
  Serial.print(distance,2);      // print distance with 2 DP
  Serial.println(" cm");      // " cm" followed by a new line
  delay(500);
}

