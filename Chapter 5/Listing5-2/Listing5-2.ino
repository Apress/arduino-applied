/*******************************************************************************
 * Sketch name: 7-segment LED display
 * Description: efficient display of numbers 2 and 6 on 7-segment LED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 5 - Seven segment LED display
 ******************************************************************************/

int LEDs[ ] = {2,3,4,5,6,7,8};      // define LED pins
int two[ ]  = {1,1,0,1,1,0,1};   // LED states to display number two
int six[ ] = {1,0,1,1,1,1,1};     // LED states to display number six

void setup()
{         // define LED pins as OUTPUT
  for (int i = 0; i<7; i++) pinMode (LEDs[i], OUTPUT);
}

void loop()
{
  for (int i = 0; i<7; i++) digitalWrite(LEDs[i], two[i]);    // display number two
  delay(1000);          // delay 1s
  for (int i = 0; i<7; i++) digitalWrite(LEDs[i], six[i]);    // display number six
  delay(1000);
}

