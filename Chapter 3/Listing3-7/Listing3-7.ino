/*******************************************************************************
 * Sketch name: speed of sound
 * Description: measure speed of sound with HC-SR04 ultrasonic distance sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

#include <NewPing.h>
int pinTrig = 6;
int pinEcho = 7;
int maxdist = 100;   // max distance in cm        maxdist ~ 400-500 cm
int echoTime;
float distance = 15;
NewPing sonar(pinTrig, pinEcho, maxdist);
int tempPin = A0;       // LM35DZ temperature sensor on analog pin A0
float speed, temp, predict;

void setup()
{
  Serial.begin(9600);      // define Serial output baud rate
  analogReference(INTERNAL);    // set ADC voltage to 1.1V rather than 5V
}

void loop() 
{
  echoTime = sonar.ping_median(5);      // median echo time (microsecs)
  speed = distance*2.0*pow(10,4)/echoTime;    // speed of sound (m/s)
  Serial.print(echoTime);Serial.print(" microsecs\t");    // print time and a tab
  Serial.print("speed ");       // print "speed"
  Serial.print(speed,1); Serial.print("\t");      // print speed with 1DP, tab
  temp = (analogRead(tempPin)*110.0)/1023;                 // read temperature
  predict = 331.3 + 0.606 * temp;     // calculate speed of sound
  Serial.print("predict ");
  Serial.print(predict,1);Serial.println(" m/s");   // print prediction with 1DP
  delay(500);
}

