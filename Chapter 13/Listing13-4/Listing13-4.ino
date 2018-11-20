/*******************************************************************************
 * Sketch name: drawing on ILI9341 TFT LCD display
 * Description: draw patterns with different colours on touch-screen 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 13 - Screen displays
 ******************************************************************************/

#include <Adafruit_GFX.h>      // include Adafruit GFX library
#include <Adafruit_ILI9341.h>     // include Adafruit ILI9341 library
#include <URTouch.h>      // include URTouch library
int tftCLK  = 13;       // clock (SCL)
int tftMISO = 12;       // MISO  (SDA/SDO - serial data output)
int tftMOSI = 11;       // MOSI  (SDI - serial data input)
int tftCS = 10; 
int tftDC = 9;
int tftRST = 8;
     // associate tft with Adafruit ILI9341 library and define pins
Adafruit_ILI9341 tft = Adafruit_ILI9341(tftCS, tftDC, tftMOSI, tftCLK, tftRST, tftMISO);
int tsCLK = 7; 
int tsCS = 6; 
int tsDIN = 5;        // data input (~MOSI)
int tsD0 = 4;       // data output (~MISO)     
int tsIRQ = 3; 
URTouch ts(tsCLK, tsCS, tsDIN, tsD0, tsIRQ);  // associate ts with URTouch library
int radius = 2;       // radius of "paintbrush"
int setRot = 3;       // portrait 0 or 2, landscape = 1 or 3
unsigned int colour;
int x, y, tx, ty;

void setup()
{
  tft.begin();        // initialise TFT LCD screen
  tft.setRotation(setRot);      // set touch screen orientation
  ts.InitTouch();       // initialise touch screen
  ts.setPrecision(PREC_MEDIUM);   // set touch screen precision
  clear();          // function to clear screen
}
 
void loop()
{
  while(ts.dataAvailable())     // when touch screen pressed
  {
    ts.read();        // read (x,y) co-ordinates
    x = ts.getX();
    y = ts.getY();   
    if(x != -1 && y != -1)      // when contact with screen
    {         //              (-1  is no contact)
      if(setRot == 0) {tx = 240-y; ty = 320-x;}
      else if(setRot == 1) {tx = 320-x; ty = y;}  // transform (x,y) co-ordinates
      else if(setRot == 2) {tx = y; ty = x;}
      else if(setRot == 3) {tx = x; ty = 240-y;}
      if(tx<20 && tx>0)     // choose colour from palette
      {
             if(ty>75 && ty<95)  colour = ILI9341_RED;   
        else if(ty>100 && ty<120) colour = ILI9341_YELLOW;
        else if(ty>125 && ty<145) colour = ILI9341_GREEN;
        else if(ty>150 && ty<170) colour = ILI9341_BLUE;
        else if(ty>175 && ty<195) colour = ILI9341_WHITE; 
        else if(ty>215) clear();        // clear screen
        if(ty>75 && ty<195) tft.fillCircle(10, 50, 10, colour); // display chosen colour
      }
      if(tx>20) tft.fillCircle(tx, ty, radius, colour);   // paint colour on touch screen
    }
  }
}

void clear()
{
  tft.fillScreen(ILI9341_BLACK);          // available colours listed in Adafruit_ILI9341.h
  tft.setTextColor(ILI9341_GREEN);      // set text colour
  tft.setTextSize(2);         // set text size
  tft.setCursor(110,5);       // position cursor middle-top
  tft.print("Paintpot");    
  tft.fillRect(0,75,20,20,ILI9341_RED);     // display colour palette
  tft.fillRect(0,100,20,20,ILI9341_YELLOW);
  tft.fillRect(0,125,20,20,ILI9341_GREEN);
  tft.fillRect(0,150,20,20,ILI9341_BLUE);
  tft.fillRect(0,175,20,20,ILI9341_WHITE);
  tft.drawCircle(10,225,10,ILI9341_WHITE);    // draw "clear" circle
  tft.setCursor(25,217);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("clear");
  colour = ILI9341_WHITE;       // default colour
}

