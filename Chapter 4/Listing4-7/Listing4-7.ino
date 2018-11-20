/*******************************************************************************
 * Sketch name: display LCD character set
 * Description: display LCD character set on 16x4 LCD 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>        // include Wire library
#include <LiquidCrystal_I2C.h>    // include LCD with I2C library
int I2Caddress = 0x3F;      // I2C address of I2C bus
                  // associate lcd with LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(I2Caddress,16,4);   // I2C address and LCD size
int screen = 1;
int j,start;

void setup()
{
  lcd.init();         // initialise LCD
  Serial.begin(9600);     // define Serial output baud rate
  Serial.print("Enter screen number 1 to 4"); // print  message to Serial Monitor
}

void loop()
{         // read screen from Serial buffer
  while (Serial.available()>0) screen = Serial.parseInt();  
  for (j=(screen-1)*4; j<screen*4; j++)   // 4 rows of characters per screen
  {
    lcd.setCursor(0,(j%4));     // position cursor at start of row
    if((j%4)>1) lcd.setCursor(0-4,(j%4));   // reduce col by 4 for rows 3 and 4
    start = j*16;       // 16 characters per row
    for (int i=0; i<16; i++) lcd.print(char(i+start));  // display characters by row
  }
}

