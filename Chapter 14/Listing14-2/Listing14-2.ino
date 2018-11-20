/*******************************************************************************
 * Sketch name: colour recognition sensor
 * Description: calibrate then use colour recognition sensor to scan objects
 *              with output displayed on ST7735 TFT LCS screen
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 14 - Sensing colours
 ******************************************************************************/

#include <Adafruit_ST7735.h>      // include ST7735 library
#include <Adafruit_GFX.h>       // include GFX library
int TFT_CS = 6;         // screen chip select pin
int DCpin = 9;          // screen DC pin
int RSTpin = 7;         // screen reset pin
             // associate tft with Adafruit_ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, DCpin, RSTpin);
unsigned int BLACK = 0x0000;      // HEX code for black colour
int S2 = A4;          // colour sensor pins
int S3 = A5;
int OUT = A3;
int calibrate = 0;
byte R, G, B, Rlow, Rhigh, Glow, Ghigh, Blow, Bhigh;

void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  pinMode(S2, OUTPUT);      // sensor pins S2 and S3 as output
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);      // sensor pin OUT as input
  tft.initR(INITR_BLACKTAB);      // initialize screen
  tft.fillScreen(BLACK);      // fill screen in black
  Serial.println("Select Newline option on Serial Monitor");  // print instructions to
  Serial.println("Calibrate WHITE, <enter> when ready");  //       Serial Monitor
}

void loop()
{
  if (calibrate == 0)       // calibrate white image
  {
    while (Serial.available()>0)      // wait for <enter> to be pressed
    {
      if(Serial.read() == '\n')     // white calibration on <enter>
      {
        Rlow = scan(LOW, LOW);    // red filter scan of white image
        Glow = scan(HIGH, HIGH);    // green filter scan of white image
        Blow = scan(LOW, HIGH);   // blue filter scan of white image
        Serial.println("WHITE calibration complete");
        Serial.println("to calibrate BLACK, <enter> when ready");
        calibrate = 1;        // flag WHITE has been calibrated
      }
    }
  }
  else if (calibrate == 1)      // calibrate black image
  {
    while (Serial.available()>0)      // wait for <enter> to be pressed
    {
      if(Serial.read() == '\n')       // black calibration on <enter>
      {
        Rhigh = scan(LOW, LOW);   // red filter scan of black image
        Ghigh = scan(HIGH, HIGH);     // green filter scan of black image
        Bhigh = scan(LOW, HIGH);    // blue filter scan of black image
        Serial.println("BLACK calibration complete");
        calibrate = 2;        // flag BLACK has been calibrated
        Serial.println("<enter> when ready for colour scan"); 
      }
    }
  }
  else if(calibrate == 2)
  {
    while (Serial.available()>0)      // wait for <enter> to be pressed
    {
      if(Serial.read() == '\n')     // start scan on <enter>
      {
        R = scan(LOW, LOW);     // red filter scan of image
        R = map(R, Rlow, Rhigh, 255, 0);    // scale red filter scan to low-high range
        G = scan(HIGH, HIGH);     // green filter scan of image
        G = map(G, Glow, Ghigh, 255, 0);                 // scale green filter scan to low-high range
        B = scan(LOW, HIGH);      // blue filter scan of image
        B = map(B, Blow, Bhigh, 255, 0);    // scale blue filter scan to low-high range
        unsigned int RGB = convertRGB(R,G,B); // convert to 16bit colour
        tft.fillRect(20,60,88,80,RGB);                 // fill screen rectangle with scanned colour
      }
    }
  }
}

int scan(int level2, int level3)      // function to scan image
{
  digitalWrite(S2, level2);     // set colour sensor pins
  digitalWrite(S3, level3);
  unsigned int val = 0;     // 1000 scans of image
  for (int i=0; i<1000; i++) val = val + pulseIn(OUT, LOW); 
  val = val/1000.0;       // average of 1000 scans
  return val;
}

unsigned int convertRGB(byte r, byte g, byte b)
{       // convert three 8 bit numbers to 16 bit number
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

