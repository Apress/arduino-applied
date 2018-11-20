/*******************************************************************************
 * Sketch name: LCD and temperature sensor
 * Description: display temperature and time on 16x4 LCD  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 4 - Liquid crystal display
 ******************************************************************************/

#include <LiquidCrystal.h>      // include the LiquidCrystal library
int LCDcol =16;       // number of LCD columns
int LCDrow = 4;       // number of LCD rows
          // associate lcd with LiquidCrystal library
LiquidCrystal lcd (2,3,4,5,6,7);      // define LCD pins RS, E and D4 to D7
int tempPin = A0;       // LM35 temperature sensor pin
int time = 0;
int reading;
float temp;

void setup()
{
  lcd.begin(LCDcol, LCDrow);      // define LCD dimensions
  lcd.setCursor(0,0);       // move cursor to start of first row
  lcd.print("LCD to display");      // print first row "LCD to display"
  lcd.setCursor(0,1);       // move cursor to start of second row
  lcd.print("time and temp");     // print second row "time and temp"
  lcd.setCursor(3,2);                   // move cursor to insert "secs" on third row
  lcd.print(" secs");
  lcd.setCursor(5,3);       // move cursor to insert "C" in fourth row
  lcd.print(" C");
  analogReference(INTERNAL);    // set ADC voltage to 1.1V rather than 5V
//  int contrast = 9;      // PWM pin for contrast
//  pinMode(contrast, OUTPUT);    // define contrast pin as OUTPUT
//  analogWrite(9, 80);     // 80% duty cycle
}

void loop()
{
  lcd.setCursor(0,2);       // move cursor to start of third row
  if(time < 100) lcd.print(" ");      // spacing for 10s < time <100s
  if(time < 10) lcd.print(" ");     // spacing for time < 10s
  lcd.print(time);        // print time (s)
  time++;         // increment time
  reading = analogRead(tempPin);    // read temperature from sensor
  temp = (reading * 110.0)/1023;    // convert to Celsius given 1.1V range
  lcd.setCursor(0,3);       // move cursor to start of fourth row
  lcd.print(temp);        // print temperature
  if(time>999) time = 0;      // reset time to zero
  delay (1000);       // delay 1000ms
}

