/*******************************************************************************
 * Sketch name: scrolling text on LCD
 * Description: text is scrolled across 16x4 LCD 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <LiquidCrystal.h>    // include the LiquidCrystal library
int LCDcol =16;     // number of LCD columns
int LCDrow = 4;     // number of LCD rows
        // associate lcd with LiquidCrystal library
LiquidCrystal lcd(2,3,4,5,6,7) ;  // define LCD pins RS, E and D4 to D7
int first;        // position of first letter in 16 character substring
int last = 0;     // position of last letter in 16 character substring
int row = 1;      // row of LCD to display text
int col;
String text = "The quick brown fox jumps over the lazy dog \
contains every letter of the alphabet.";
void setup()
{
  lcd.begin(LCDcol, LCDrow);    // define LCD dimensions
  text = text + " ";      // add space at end of text as a buffer
}

void loop()
{
  if(last>text.length()+15) last=1; // set first column of substring
  if(last<17) first = 0;      // substring<17 characters, start character =0
    else first = last-16;               // substring>=17 characters, start character = last-16
  if(last>16) col = 0;      // substring>16 characters, start column = 0
    else col = 16-last;     // substring<=16 characters, start column  = last-16
  lcd.setCursor(col,row);   // set cursor position
  lcd.print(text.substring(first, last)); // print substring
  last = last +1;     // increment last
  delay(250);     // delay 250ms
}

