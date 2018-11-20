/*******************************************************************************
 * Sketch name: GY-521 module
 * Description: determine object's orientation with GY-521 module
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

#include<Wire.h>        // include Wire library
int I2Caddress = 0x68;      // I2C address of the MPU-6050
int frontLED = 13;
int backLED = 11;       // define LED pins
int rightLED = 12;
int leftLED = 10;
float accelX,accelY,accelZ;     // accelerometer measurements
float roll, pitch, sumsquare;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(frontLED, OUTPUT);
  pinMode(backLED, OUTPUT);   // define LED pins as OUTPUT
  pinMode(rightLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  Wire.begin();       // initiate I2C bus
  Wire.beginTransmission(I2Caddress);   // transmit to device at I2Caddress
  Wire.write(0x6B);       // PWR_MGMT_1 register
  Wire.write(0);        // set to zero wakes up MPU-6050
  Wire.endTransmission(1);      // end of transmission
}

void loop()
{
  Wire.beginTransmission(I2Caddress);   // transmit to device at I2Caddress
  Wire.write(0x3B);       // start reading from register 0x3B
  Wire.endTransmission(0);      // transmission not finished
  Wire.requestFrom(I2Caddress,6,true);    // request data from 6 registers
  accelX=Wire.read()<<8|Wire.read();    // combine AxHigh and AxLow values
  accelY=Wire.read()<<8|Wire.read();    // combine AyHigh and AyLow values
  accelZ=Wire.read()<<8|Wire.read();    // combine AzHigh and AzLow values
  accelX = accelX/pow(2,14);
  accelY = accelY/pow(2,14);      // scale X, Y and Z measurements
  accelZ = accelZ/pow(2,14);
  sumsquare = sqrt(accelX*accelX+accelY*accelY+accelZ*accelZ);
  accelX = accelX/sumsquare;
  accelY = accelY/sumsquare;      // adjusted accelerometer measurements
  accelZ = accelZ/sumsquare;
  roll = atan2(accelY, accelZ)*180/PI;    // roll angle
  pitch = -asin(accelX)*180/PI;     // pitch angle
  LEDs();         // function to control LEDS
}

void LEDs()       // function to control LEDs
{
  int front = LOW;
  int back = LOW;       // turn off all LEDs
  int right = LOW;
  int left = LOW;
  if(roll>10) right = HIGH;     // right or left LEDS with roll angle
  else if(roll< -10) left = HIGH;
  if(pitch>10) front = HIGH;      // front or back LEDs with pitch angle
  else if(pitch< -10) back = HIGH;
  digitalWrite(frontLED, front);      // if value = HIGH, LED on
  digitalWrite(backLED, back);      // if value = LOW, LED off
  digitalWrite(rightLED, right);
  digitalWrite(leftLED, left);
  delay(500);
}

