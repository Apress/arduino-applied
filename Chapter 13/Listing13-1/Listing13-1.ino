/*******************************************************************************
 * Sketch name: display shapes and colours
 * Description: display shapes of different colours on ST7735 TFT LCD screen
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 13 - Screen displays
 ******************************************************************************/

#include <Adafruit_ST7735.h>      // include ST7735 library
#include <Adafruit_GFX.h>       // include GTX library
int TFT_CS = 6;         // screen chip select pin
int DCpin = 9;          // screen DC pin
int RSTpin = 7;         // screen reset pin
                     // associate tft with Adafruit_ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, DCpin, RSTpin);
unsigned int BLACK = 0x0000;
unsigned int BLUE = 0x001F;
unsigned int RED = 0xF800;
unsigned int GREEN = 0x07E0;
unsigned int CYAN = 0x07FF;       // HEX codes for colours
unsigned int MAGENTA = 0xF81F;
unsigned int YELLOW = 0xFFE0;
unsigned int WHITE = 0xFFFF;
unsigned int GREY = 0xC618;
String texts[ ] = 
            {"BLUE","RED","GREEN","CYAN","MAGENTA","YELLOW","WHITE","GREY"};
String text;
unsigned int colours[ ] = 
            {BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE, GREY};
unsigned int colour;

void setup()
{
  tft.initR(INITR_BLACKTAB);        // initialize screen
  tft.fillScreen(BLACK);        // fill screen in black
  tft.drawRect(0,0,128,160,WHITE);      // draw white frame line
  tft.drawRect(1,1,126,158,WHITE);      // and second frame line
  tft.setTextSize(2);         // set text size
}

void loop()
{
  tft.fillRect(2,2,124,156,BLACK);                   // clear screen apart from frame
  for (int i=0; i<8; i++)       // for each colour
  {
    colour = colours[i];        // set colour
    text = texts[i];          // set text
    tft.setTextColor(colour);       // set text colour
    tft.setCursor(20, 20 * i + 2);        // position cursor(20, y)
    tft.print(text);          // print colour name
    delay(250);                      // delay 250ms between colours
  }
  delay(500);
  for (int i=0; i<8; i++)       // for each colour
  {
    tft.fillRect(2,2,124,156,BLACK);                   // clear screen apart from frame
    colour = colours[i];
    text = texts[i];
    tft.setCursor(20,25);                 // move cursor position to (20, 25)
    tft.setTextColor(colour);       // set text colour
    tft.print(text);          // print colour name
// draw filled-in triangle
    if ((i+1) % 3 == 0) tft.fillTriangle(20,134,64,55,107,134,colour);
// draw open rectangle
    else if ((i+1) % 2 == 0) tft.drawRect(20,55,88,80,colour);
    else tft.fillCircle(64,95,39,colour);     // draw filled-in circle
    delay(500);
  }
  tft.fillRect(2,2,124,156,BLACK);                   // clear screen apart from frame
  tft.drawLine(2,78,125,78,RED);          // draw horizontal line (x0,y) to (x1, y)
  tft.drawLine(2,80,125,80,RED);  
  tft.drawLine(62,2,62,157,RED);              // draw vertical line (x,y0) to (x, y1)
  tft.drawLine(64,2,64,157,RED);
  delay(500);
}

