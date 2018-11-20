/*******************************************************************************
 * Sketch name: display numbers zero, one, two and seven
 * Description: PWM to control LED brightness of numbers on 7-segment LED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 5 - Seven segment LED display
 ******************************************************************************/

int LEDpin[ ] = {9,10,11,5,6,7,8};  // define LED pins with PWM for LEDs a, b and c
int one[ ] =   {0,72,72,0,0,0,0};   // LED brightness to display number one
int two[ ] =   {1,1,0,1,1,0,1};   // LED states to display number two
int three[ ] = {1,1,1,1,0,0,1};
int four[ ] =  {0,1,1,0,0,1,1};
int five[ ]  = {1,0,1,1,0,1,1};
int six[ ] =   {1,0,1,1,1,1,1};
int seven[ ] = {109,109,109,0,0,0,0}; // LED brightness to display number seven
int eight[ ] = {1,1,1,1,1,1,1};
int nine[ ] =  {1,1,1,1,0,1,1};
int zero[ ] =  {1,1,1,1,1,1,0};

void setup()
{
  for (int i = 0; i<7; i++) pinMode (LEDpin[i], OUTPUT);  // define LED pins as OUTPUT
}

void loop()
{
  for (int i = 0; i<7; i++) digitalWrite(LEDpin[i],0);    // turn off all LEDs
  delay(10);
  for (int i = 0; i<3; i++) analogWrite(LEDpin[i], one[i]); // display number one
  delay(1000);
  for (int i = 0; i<7; i++) digitalWrite(LEDpin[i], two[i]);  // display number two
  delay(1000);
  for (int i = 0; i<7; i++) digitalWrite(LEDpin[i],0);    // turn off all LEDs
  delay(10);
  for (int i = 0; i<3; i++) analogWrite(LEDpin[i], seven[i]);   // display number seven
  delay(1000);
  for (int i = 0; i<7; i++) digitalWrite(LEDpin[i], zero[i]); // display number zero
  delay(1000); // delay 1s
}

