/*******************************************************************************
 * Sketch name: DC motor control with infrared remote control
 * Description: motor rotation controlled by infrared signal
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

#include <IRremote.h>      // include IRemote library
int IRpin = 2;        // IR sensor pin
IRrecv irrecv(IRpin);       // associate irrecv with IRremote library
decode_results reading;     // IRremote reading
int IN1 = 8;        // left motor forward pin
int IN2 = 7;        //     backward pin
int IN3 = 6;        // right motor forward pin
int IN4 = 5;        //       backward pin
int ENA = 9;        // control pin left motor
int ENB = 10;        // control pin right motor

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);     // define motor pins as OUTPUT
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);     // define motor enable pins as OUTPUT
  pinMode(ENB, OUTPUT);
  irrecv.enableIRIn();
}

void loop()
{
  if(irrecv.decode(&reading))      // read the IR signal
  {
    Serial.println(reading.value, HEX);
    switch(reading.value)     // switch … case for button signals
    {
      case 0xC0E014D: direction("forward",500); break;    // move forward
      case 0x9FFCDC4D: direction("backward", 500); break;   // move backward
      case 0x348ADD0F: direction("right", 500); break;    // turn right
      case 0x7E57898D: direction("left", 500); break;     // turn left
      case 0x4B0AA72C: direction("stop", 500); break;   // stop
    }
  irrecv.resume();        // receive the next infrared signal
  }
}

void direction(String direct, int runTime)    // function to set motor direction
{
       if(direct == "forward")  motor(1, 0, 1, 0, "fast"); // both motors forward
  else if(direct == "backward") motor(0, 1, 0, 1, "fast");  // both motors backward
  else if(direct == "right")    motor(1, 0, 0, 1, "slow"); // left forward, right backward
  else if(direct == "left")     motor(0, 1, 1, 0, "slow");  // left backward, right forward
  else if(direct == "stop")     motor(0, 0, 0, 0, " ");   // both motors stop
  delay(runTime);         // run time (ms) for motors
}

void motor(int leftF, int leftB, int rightF ,int rightB, String speed)  // motor function
{
  float bias = 1.0;       // bias on motor speed
  digitalWrite(IN1, leftF);     // control pin IN1 left motor forward
  digitalWrite(IN2, leftB);     // control pin IN2 left motor backward
  digitalWrite(IN3, rightF);      // control pin IN3 right motor forward
  digitalWrite(IN4, rightB);      // control pin IN4 right motor backward
  if(speed == "fast")
  {
    analogWrite(ENA, 100);      // higher speed when moving
    analogWrite(ENB, 100*bias);   // forward or backward
  }
  else
  {
    analogWrite(ENA, 80);     // lower speed when turning
    analogWrite(ENB, 80*bias);      // compensation on right motor
  }
}

