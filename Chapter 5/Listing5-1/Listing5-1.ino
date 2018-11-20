/*******************************************************************************
 * Sketch name: 7-segment LED display
 * Description: simple display of numbers 2 and 6 on 7-segment LED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 5 - Seven segment LED display
 ******************************************************************************/

int pinA = 2;  // yellow wire to display LED a
int pinB = 3; // blue wire to display LED b
int pinC = 4; // yellow wire to display LED c
int pinD = 5; // blue wire to display LED d
int pinE = 6; // yellow wire to display LED e
int pinF = 7; // blue wire to display LED f
int pinG = 8; // yellow wire to display LED g

void setup()
{
  pinMode (pinA, OUTPUT);     // define LED pins as output
  pinMode (pinB, OUTPUT);
  pinMode (pinC, OUTPUT);
  pinMode (pinD, OUTPUT);
  pinMode (pinE, OUTPUT);
  pinMode (pinF, OUTPUT);
  pinMode (pinG, OUTPUT);
}
void loop()
{
  digitalWrite(pinA, HIGH);     // display number two
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH); 
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  delay(1000);
  digitalWrite(pinA, HIGH);     // display number six
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  delay(1000);
}

