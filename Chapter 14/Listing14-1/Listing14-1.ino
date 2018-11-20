/*******************************************************************************
 * Sketch name: RGB LED
 * Description: control colours of RGB LED with incremental changes
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 14 - Sensing colours
 ******************************************************************************/

int redLED = 3;      // LEDs on PWM pins
int greenLED = 5;
int blueLED = 6;
int steps = 63;     // number of increments
int oldR = 0;      // pixel value difference = 255 or 128
int oldG = 0;     //     so steps of size 4 or 2
int oldB = 0;
int incR, incG, incB;     // incremental changes
String colour[ ] = {"White","Red","Lime","Blue","Yellow","Cyan","Magenta","Grey","Maroon",
            "Olive","Green","Purple","Teal","Navy"}; 
int R[ ] = {255, 255,     0,    0, 255,     0,  255, 128, 128, 128,     0, 128,     0,    0};
int G[ ] = {255,     0, 255,    0, 255, 255,     0,  128,     0, 128, 128,     0, 128,    0};
int B[ ] = {255,     0,     0, 255,    0, 255, 255,  128,     0,     0,     0, 128, 128, 128};

void setup()
{ }       // nothing in void setup()

void loop()
{
  int i = random(14);         // randomly select next colour, between 0 and 13
  incR = (R[i]-oldR)/steps;     // calculate the incremental amount
  incG = (G[i]-oldG)/steps;
  incB = (B[i]-oldB)/steps;
  for (int n = 0; n<steps; n++)     // for each incremental change
  {
    analogWrite(redLED, oldR + n*incR);   // change the LED intensity
    analogWrite(greenLED, oldG + n*incG);
    analogWrite(blueLED, oldB + n*incB);
    delay(5000/steps);      // time delay between colour increments
  }
  oldR = R[i];        // update the current colour
  oldG = G[i];
  oldB = B[i];
}

