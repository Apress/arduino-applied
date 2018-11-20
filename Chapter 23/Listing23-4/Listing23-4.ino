/*******************************************************************************
 * Sketch name: joystick and transmitting nRF24L01
 * Description: transmitted joystick value by nRF24L01 module
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <RF24.h>       // include RF24 library
RF24 radio(7, 8);       // associate radio with RF24 library
byte addresses[ ][6] = {"12"};
typedef struct        // define a structure
{
  int right, left;        // to contain PWM values for the
} dataStruct;       // left and right motors
dataStruct data;        // name the structure
int LRpin = A5;              // Uno A4 (horizontal) left-right (X-axis)
int FBpin = A6;              // Uno A3 (vertical) forward-backward (Y-axis)
int LR, FB;
int minPWM = 50;        // minimum PWM value
int LRscalar = 2;       // scalars for joystick sensitivity
int FBscalar = 2;

void setup()
{
 radio.begin();       // initialise radio 
 radio.openWritingPipe(addresses[0]);   // open transmitting pipe
}

void loop()
{
  LR = map(analogRead(LRpin), 0, 1023, -255, 255);  // joystick left = 0
  FB = map(analogRead(FBpin), 0, 1023, 255, -255);  // joystick forward = 0
  data.left = FB/FBscalar + LR/LRscalar;      // sum of scaled readings
  data.right = FB/FBscalar - LR/LRscalar;   // difference of scaled readings
  data.left = constrain(data.left, -255, 255);          // constrain PWM values (-255, 255)
  data.right = constrain(data.right, -255, 255);
  if(abs(data.left) < minPWM) data.left = 0;         // zero PWM value < minimum value
  if(abs(data.right) < minPWM) data.right = 0;
  radio.write(&data, sizeof(data));     // transmit PWM values
  delay(50);          // delay 50ms
}

