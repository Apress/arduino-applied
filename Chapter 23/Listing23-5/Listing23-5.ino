/*******************************************************************************
 * Sketch name: DC motors and receiving nRF24L01
 * Description: motor rotation controlled by transmitted joystick value
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
  int right, left;        // structure to contain PWM values
} dataStruct;       //          for the left and right motors
dataStruct data;        // name the structure
int IN1 = 10;       // left motor forward on PWM pins
int IN2 = 9;        //                 backward
int IN3 = 6;        // right motor forward
int IN4 = 5;        //                   backward

void setup()
{
  radio.begin();        // initialise radio
  radio.openReadingPipe(0, addresses[0]); // open receiving pipe
  radio.startListening();     // initialise receive
}

void loop()
{
  if(radio.available())       // signal received
  {
    radio.read(&data,sizeof(data));       // read data values
         if(data.left>0 && data.right>0) motor(data.left, 0, data.right, 0);                 // forward
    else if(data.left<0 && data.right<0) motor(0, -data.left, 0, -data.right);                // backward
    else if(data.left<0 && data.right>0) motor(0, -data.left, data.right, 0);                 // turn left
    else if(data.left>0 && data.right<0) motor(data.left, 0, 0, -data.right);                 // turn right
    else motor(0, 0, 0, 0);                       // stop
  }
}

void motor(int leftF, int leftB, int rightF ,int rightB)    // control motors by PWM
{
  analogWrite(IN1, leftF);      // control pin IN1 left motor forward
  analogWrite(IN2, leftB);      // control pin IN2 left motor backward
  analogWrite(IN3, rightF);       // control pin IN3 right motor forward
  analogWrite(IN4, rightB);       // control pin IN4 right motor backward
}

