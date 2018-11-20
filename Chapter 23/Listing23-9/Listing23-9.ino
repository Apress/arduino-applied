/*******************************************************************************
 * Sketch name: distance travelled by the robot car
 * Description: photoelectric encoders control the distance travelled
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

int IN1 = 10;        // left wheel forward
int IN2 = 9;        //     backward
int IN3 = 6;        // right wheel forward
int IN4 = 5;        //       backward
float W = 13.0;               // distance (cm) between mid-point of wheels
float d = 6.7;        // diameter (cm) of wheel
int slot = 20;        // number of encoder wheel slots
float turnSlot = slot * W /(4 * d);   // number of slots to turn right/left
float cmSlot = slot/(PI*d);     // number of slots to move one cm
volatile int countR = 0;      // counter for encoder wheel slots
volatile int countL = 0;
int FBspeed = 100;        // forward/backward speed
int LRspeed = 80;       // left/right turn speed

void setup()
{
  attachInterrupt(0, counterR, RISING);   // interrupts to count encoder wheel slots
  attachInterrupt(1, counterL, RISING);   //       passing the photoelectric encoder
}

void loop()
{
  direction("forward",40);      // function to define direction 
  direction("right", 0);      //        and distance (cm)
  direction("forward",30);
  direction("left", 0);
  direction("forward",20);
  direction("left", 0);
  direction("forward",30);
  direction("right", 0);
  direction("forward",50);
  direction("backward",110);
  direction("stop", 0);
  delay(5000);        // delay 5s between movement
}

void direction(String direct, int dist)   // function controlling DC motors
{
  int Nslots;       // number of slots to count
  if(direct == "forward" || direct == "backward") Nslots = dist*cmSlot;
  else if(direct == "right" || direct == "left") Nslots = turnSlot;
  else if(direct == "stop")
  {
    Nslots = 0;
    countL = 1;       // for stop, set counters above slot limit
    countR = 1;
  }
  Serial.println(Nslots);
          if(direct == "forward")    motor(1, 0, 1, 0, FBspeed);  // set motor then count slots
  else if(direct == "backward") motor(0, 1, 0, 1, FBspeed);
  else if(direct == "right")          motor(1, 0, 0, 1, LRspeed);
  else if(direct == "left")            motor(0, 1, 1, 0, LRspeed);  // wait until slot limit reached
  while (countR <= Nslots || countL <= Nslots) { }    //      by both motors
  if(countR > Nslots && countL > Nslots)      // both wheels have moved
  {           //     the required distance
    motor(0, 0, 0, 0, 0);       // reset all variables
    delay(500);
    countR = 0;
    countL = 0;
  }
}

void motor(int leftF, int leftB, int rightF ,int rightB, int cspeed)
{
  analogWrite(IN1, leftF * cspeed);     // forward speed of left motor
  analogWrite(IN2, leftB * cspeed);     // backward speed of left motor
  analogWrite(IN3, rightF * cspeed);      // forward speed of right motor
  analogWrite(IN4, rightB * cspeed);      // backward speed right motor
}

void counterR()         // interrupt to count number of
{           // encoder wheel slots passing
  countR++;         // right wheel encoder.
}

void counterL()         // interrupt to count number of
{           // encoder wheel slots passing
  countL++;         // left wheel encoder.
}

