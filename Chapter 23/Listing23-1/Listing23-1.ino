/*******************************************************************************
 * Sketch name: route defined in sketch
 * Description: motor rotation set for fixed time periods
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

int IN1 = 8;        // left motor forward pin
int IN2 = 7;        //     backward pin
int IN3 = 6;        // right motor forward pin
int IN4 = 5;        //       backward pin
int ENA = 9;        // control pin left motor
int ENB = 10;        // control pin right motor

void setup()
{
  pinMode(IN1, OUTPUT);     // define motor pins as OUTPUT
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);     // define motor enable pins as OUTPUT
  pinMode(ENB, OUTPUT);
}

void loop()
{
  direction("forward",1500);      // move forward for 1500ms
  direction("right",500);     // turn right for 500ms
  direction("forward",1000);
  direction("left",500);      // turn left for 500ms
  direction("forward",1500);
  direction("left",500);
  direction("forward",1000);
  direction("right",500);
  direction("forward",1500);
  direction("backward",4500);       // move backward for 4500ms
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

