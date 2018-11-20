/*******************************************************************************
 * Sketch name: real-time clock module
 * Description: display weekday, date and time and temperature with DS3231 RTC
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 12 - SD card module
 ******************************************************************************/

#include <DS3231.h>      // include DS3231 library
DS3231 rtc(SDA, SCL);     // associate rtc with DS3231 library
Time t;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  rtc.begin();        // start rtc
//  rtc.setDOW(THURSDAY)      // set weekday
//  rtc.setTime(10, 23, 20);      // set the time to hh mm ss
//  rtc.setDate(10, 5, 2018);     // set the date to dd mm yyyy
}

void loop()
{
  Serial.print(rtc.getDOWStr());Serial.print(" ");    // weekday
  Serial.print(rtc.getDateStr());Serial.print(" ");   // date
  Serial.print(rtc.getTimeStr());Serial.print("\t");    // time
  t = rtc.getTime();          // components of date and time
  Serial.print(t.date);Serial.print(" ");     // day
  Serial.print(rtc.getMonthStr());Serial.print(" (month "); // month as text
  Serial.print(t.mon);Serial.print(") ");     // month
  Serial.print(t.year);Serial.print("\t");      // year
  Serial.print(t.hour);Serial.print(":");     // hour
  Serial.print(t.min);Serial.print(":");      // minute
  Serial.print(t.sec);Serial.print("\t");     // second
  Serial.print(rtc.getTemp(),1);Serial.println(" C");   // temperature to 1DP
  delay (1000);
}

