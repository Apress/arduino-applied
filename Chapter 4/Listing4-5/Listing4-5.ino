/*******************************************************************************
 * Sketch name: cursor position on 16x4 LCD
 * Description: demsonstrate starting address on third and fourth row of 16x4 LCD 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>        // include Wire library
#include <LiquidCrystal_I2C.h>    // include LiquidCrystal_I2C
int I2Caddress = 0x3F;      // address of I2C bus
int LCDcol =16;       // number of LCD columns
int LCDrow = 4;       // number of LCD rows
LiquidCrystal_I2C lcd(I2Caddress,LCDcol,LCDrow);

void setup()
{
  lcd.init();         // initialize the lcd 
}

void loop()
{
  for (int col=0; col<16; col++)
  {
  lcd.clear();        // clear the LCD
  lcd.setCursor(col,0);     // first row
  lcd.print("A");
  lcd.setCursor(col,1);     // second row
  lcd.print("B");
  lcd.setCursor(col-4,2);     // reduce col by 4 in the third row
  lcd.print("C");
  lcd.setCursor(col-4,3);     // reduce col by 4 in the fourth row
  lcd.print("D");
  delay(500);
  }
}

