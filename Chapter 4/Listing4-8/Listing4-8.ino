/*******************************************************************************
 * Sketch name: additional characters
 * Description: create additional characters and dsiplay on 16x4 LCD 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int LCDcol =16;       // number of LCD columns
int LCDrow = 4;       // number of LCD rows
int I2Caddress = 0x3F;       // I2C address of bus
LiquidCrystal_I2C lcd(I2Caddress,LCDcol,LCDrow);       // associate lcd with LiquidCrystal library
byte clock[8] = {0, 14, 21, 23, 17, 14, 0};
byte tick[8] = {0, 1, 3, 22, 28, 8, 0};
byte cross[8] = {0, 27, 14, 4, 14, 27, 0};

void setup()
{
  lcd.init();
  lcd.createChar(0, clock);
  lcd.createChar(1, tick);
  lcd.createChar(2, cross);
  lcd.setCursor(0,0);
  for (int i=0;i<3;i++) lcd.write(i);
}

void loop()
{}
