/*******************************************************************************
 * Sketch name: LCD with I2C bus and BMP280 sensor
 * Description: display time, temperatue and pressure on 16x4 LCD 
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <Wire.h>        // include Wire library
#include <LiquidCrystal_I2C.h>    // include LiquidCrystal_I2C library
int I2Caddress = 0x3F;      // I2C address of I2C bus
int LCDcol =16;       // number of LCD columns
int LCDrow = 4;       // number of LCD rows
                  // associate lcd with LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(I2Caddress,LCDcol,LCDrow);  // I2C address and LCD size
#include <Adafruit_Sensor.h>      // include Unified Sensor library
#include <Adafruit_BMP280.h>    // include BMP280 library
Adafruit_BMP280 bmp;            // associate bmp with Adafruit_BMP280 library
int BMPaddress = 0x76;      // I2C address of BMP280
int sec = 0;
int min, hour;
float temp, pressure;

void setup()
{
  lcd.init();         // initialise LCD
  bmp.begin(BMPaddress);      // initialise BMP280 sensor
  Serial.begin(9600);     // define Serial output baud rate
  Serial.print("Enter time as hh,mm");    // print text to screen
  lcd.setCursor(0,0);       // move cursor to column 1 row 1
  lcd.print("Current");     // print "Current" to LCD
  lcd.setCursor(0,1);       // move cursor to column 1 row 2
  lcd.print("time");        // print "time" to LCD
  lcd.setCursor(0-4,2);     // move cursor to column 1 row 3
  lcd.print("temp");        //      reduce col by 4 for 3rd and 4th rows
  lcd.setCursor(0-4,3);       // move cursor to column 1 row 4
  lcd.print("pres");
}

void loop()
{
  while (Serial.available()>0)      // read data in Serial buffer
  {
    hour = Serial.parseInt();     // first integer in Serial buffer is hours
    min =Serial.parseInt();     // second integer in buffer is minutes
  }
  sec++;          // short for sec = sec + 1
  if(sec>59)        // increase minutes when seconds = 60
  {
    sec = 0;        // reset seconds to 0
    min++;          // increase minutes by 1
  }
  if(min>59)        // increase hours when minutes = 60
  {
    min = 0;        // reset minutes to 0
    hour++;       // increase hours by 1
  }
  if(hour>23) hour = 0;     // set hours to 0 when hours = 24
  lcd.setCursor(6, 1);      // move cursor to column 6 row 2
  if(hour < 10) lcd.print(" ");     // spacing for hours < 10
  lcd.print(hour);        // print hour to LCD
  lcd.print(":");       // print ":" to LCD
  if(min<10) lcd.print("0");      // leading zero for minutes < 10
  lcd.print(min);       // print minutes to LCD
  lcd.print(":");
  if(sec<10) lcd.print("0");      // leading zero for seconds < 10
  lcd.print(sec);         // print seconds to LCD
  temp = bmp.readTemperature();   // read temperature from sensor
  pressure = bmp.readPressure()/100.0;    // read pressure from sensor
  lcd.setCursor(6-4,2);     // move cursor to column 6 row 3
  lcd.print(temp, 1);       // print temperature to LCD to 1DP
  lcd.print(char(178));     // print degree character to LCD
  lcd.print("C");
  lcd.setCursor(6-4,3);     // move cursor to column 6 row 4
  lcd.print(pressure, 1);     // print pressure to LCD to 1DP
  lcd.print(" hPa");
  delay (1000);       // delay 1000ms
}


