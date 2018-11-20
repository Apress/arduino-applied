/*******************************************************************************
 * Sketch name: screen, servo motor and ultrasonic scanner
 * Description: display "radar" images of nearby objects with ultrasonic scanner
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 13 - Screen displays
 ******************************************************************************/

#include <Adafruit_ST7735.h>    // include the ST7735 library
#include <Adafruit_GFX.h>     // include the GFX library
int TFT_CS = 6;       // screen chip select pin
int DCpin = 9;        // screen DC pin
int RSTpin = 7;       // screen reset pin
                     // associate tft with Adafruit_ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, DCpin, RSTpin);
#include <NewPing.h>      // include ultrasonic sensor library
int trigPin = A1;         // ultrasonic sensor pins
int echoPin = A2;
int maxdist = 50;       // maximum scanning distance
NewPing sonar(trigPin, echoPin, maxdist); // associate sonar with NewPing library
#include <Servo.h>        // include the servo motor library
Servo servo;        // associate servo with Servo library
int servoPin = A0;        // servo motor pin
float radius = 110.0;       // radius of displayed scan arc
int increment = 3;        // incremental change of scan angle
int speed = 30;       // interval (ms) between scans
unsigned int BLACK  = 0x0000;
unsigned int YELLOW = 0xFFE0;
unsigned int LITEYEL = 0xFFF5;    // HEX codes for colours
unsigned int GREEN  = 0x07E0;
unsigned int WHITE  = 0xFFFF;
int angle, x, y, distance, duration;

void setup()
{
  servo.attach(servoPin);     // initialise servo motor
  tft.initR(INITR_BLACKTAB);      // initialize ST735 TFT LCD screen
  tft.fillScreen(BLACK);      // clear screen
  tft.setRotation(3);       // orientate ST7735 TFT LCD screen
  tft.setTextColor(WHITE, BLACK);   // text colour with over-write
  tft.drawRect(0,0,160,128,WHITE);    // draw white frame line
  tft.drawRect(1,1,158,126,WHITE);    // and second frame line
  tft.setTextSize(1);       // set text size
  tft.setCursor(3,3);       // move cursor to position (3, 3)
  tft.print("Distance");      // print text on screen
  tft.setCursor(95,3);
  tft.print("Radius ");
  tft.setCursor(135,3);
  tft.print(maxdist);       // display value of large arc
}

void loop()
{         // function to set up screen
  radar1();                          // anti-clockwise scan
  for (int angle=10; angle<170; angle=angle+increment) radar2(angle);
  radar1();             // clockwise scan
  for (int angle=170; angle>10; angle=angle-increment) radar2(angle);
}

void radar1()
{
  tft.fillRect(2,12,156,114,BLACK);   // clear screen apart from frame
  tft.drawCircle(80,128,radius/2,YELLOW); // draw arc to assist reading image
  tft.drawCircle(80,128,radius,YELLOW);   //     and second arc
}

void radar2(int angle)
{
  servo.write(angle);       // move servo motor to angle
  scan();         // function to measure distance
  delay(speed);       // interval between scans
  x = radius*cos(angle*PI/180);   // calculate scan line
  y = radius*sin(angle*PI/180);
  tft.drawLine(80,128,80+x,128-y,LITEYEL);  // draw line from baseline to arc
  x = x*distance/maxdist;     // calculate position of object
  y = y*distance/maxdist;
  tft.fillCircle(80+x,128-y,2,GREEN);   // draw circle when object detected
}

void scan()
{
  duration = sonar.ping();      // duration of echo
  distance = (duration/2)*0.0343;   // distance measured in cm
  char printOut[4];       // array of characters
  String dist = String(distance);     // convert distance to string
  if(distance<10) dist = " " + dist;    // leading space for values < 10
  dist.toCharArray(printOut, 4);      // convert string to characters
  tft.setCursor(60,3);        // move cursor
  tft.print(printOut);        // display distance on screen
}

