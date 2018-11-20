/*******************************************************************************
 * Sketch name: display on LCD characters entered on keyboard
 * Description: display on LCD characters entered on keyboard 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>        // include Wire library
#include <LiquidCrystal_I2C.h>    // include LiquidCrystal_I2C library
int I2Caddress = 0x3F;      // address of I2C bus
int LCDcol =16;       // number of LCD columns
int LCDrow = 4;       // number of LCD rows
                  // associate lcd with LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(I2Caddress,LCDcol,LCDrow);  // I2C address and LCD size

void setup()
{
  lcd.init();         // initialize LCD
  Serial.begin(9600);     // define Serial output baud rate
}

void loop()
{
  if (Serial.available()>0)     // if data in Serial input buffer
  {
    lcd.clear();          // clear the LCD
    while (Serial.available()>0) lcd.write(Serial.read());  // read, display input buffer
  }
}

