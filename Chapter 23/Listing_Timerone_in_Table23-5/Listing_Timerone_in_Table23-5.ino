/*******************************************************************************
 * Sketch name: DC motors and photoelectric encoders Table 23-5
 * Description: motors controlled by interrupts using the TimerOne library
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

#include <TimerOne.h>
float fixTime = 0.5;
float rpm;
int count=0;
int IN1 = 6;
int IN2 = 5;
int slot = 20;

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(500000);
  attachInterrupt(0, counter, RISING);
  Timer1.attachInterrupt(timerISR);
  analogWrite(IN1, 60);
  analogWrite(IN2, 0);
}

void loop()
{ }

void timerISR()
{
  noInterrupts();
  rpm = 60*count/(slot*fixTime);
  Serial.print("rpm = ");
  Serial.println(rpm, 0);
  count = 0;
  interrupts();
}

void counter()
{
  count++;
}

