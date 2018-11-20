/*******************************************************************************
 * Sketch name: 4-digit 7-segment display as timer
 * Description: simple use of 4-digit 7-segment display as timer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 6 - 4-digit 7-segment LED display
 ******************************************************************************/

int pins[ ] = {2,3,4,5,6,7,8};        // LED pins
int digits[ ] = {10,11,12,13};        // digit control pins
int zero[ ] ={1,1,1,1,1,1,0};       // LED states for zero
int one[ ] = {0,1,1,0,0,0,0};       // LED states for one
int two[ ] = {1,1,0,1,1,0,1};
int three[ ] = {1,1,1,1,0,0,1};
int four[ ] = {0,1,1,0,0,1,1};
int five[ ] = {1,0,1,1,0,1,1};
int six[ ] = {1,0,1,1,1,1,1};
int seven[ ] = {1,1,1,0,0,0,0};
int eight[ ] = {1,1,1,1,1,1,1};
int nine[ ] = {1,1,1,1,0,1,1};
int time, n;
int del = 5;          // time delay (ms)

void setup()
{
  for (int i = 0; i<7; i++) pinMode (pins[i], OUTPUT);              // define pins and digits as output
  for (int i = 0; i<4; i++) pinMode (digits[i], OUTPUT);
}

void loop()
{
  time = millis()/1000;       // time is number of seconds
  digit(0);           // digit D1 for thousands
  number(time/1000);        // number to be displayed
  delay(del);
  digit(1);           // digit D2 for hundreds
  number((time%1000)/100);        // modulus(time, 1000)/100
  delay(del);
  digit(2);           // digit D3 for tens
  number((time%100)/10);        // modulus(time, 100)/10
  delay(del);
  digit(3);           // digit D4 for units
  number(time%10);          // modulus(time, 10)
  delay(del);
}

void digit(int d)
{
  for (int i = 0; i<4; i++) digitalWrite(digits[i], 1);   // turn all digits off
  digitalWrite(digits[d], 0);                  // digit pin state is LOW, digit display is on
}

void number(int n)
{
  if        (n==0) for (int i = 0; i<7; i++) digitalWrite(pins[i], zero[i]);             // display zero
  else if (n==1) for (int i = 0; i<7; i++) digitalWrite(pins[i], one[i]);            // display one
  else if (n==2) for (int i = 0; i<7; i++) digitalWrite(pins[i], two[i]);            // display two
  else if (n==3) for (int i = 0; i<7; i++) digitalWrite(pins[i], three[i]);
  else if (n==4) for (int i = 0; i<7; i++) digitalWrite(pins[i], four[i]);
  else if (n==5) for (int i = 0; i<7; i++) digitalWrite(pins[i], five[i]);
  else if (n==6) for (int i = 0; i<7; i++) digitalWrite(pins[i], six[i]);
  else if (n==7) for (int i = 0; i<7; i++) digitalWrite(pins[i], seven[i]);
  else if (n==8) for (int i = 0; i<7; i++) digitalWrite(pins[i], eight[i]);
  else if (n==9) for (int i = 0; i<7; i++) digitalWrite(pins[i], nine[i]);
}

