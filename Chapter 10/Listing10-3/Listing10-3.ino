/*******************************************************************************
 * Sketch name: IR sensor and LCD display
 * Description: display text on LCD based on infrared signal
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 10 - Infrared sensor
 ******************************************************************************/

#include <Wire.h>        // include Wire library
#include <LiquidCrystal_I2C.h>    // include LiquidCrystal_I2C library
#include <IRremote.h>     // include IRremote library
int I2Caddress = 0x3F;      // address of I2C bus
int LCDcol = 16;        // define the number of LCD columns
int LCDrow = 4;       // define the number of LCD rows
          // associate lcd with LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(I2Caddress,LCDcol,LCDrow);  // define LCD address, size
int IRpin = A0;       // IR sensor pin
IRrecv irrecv(IRpin);       // associate irrecv with IRremote library
decode_results reading;     // IRremote reading

void setup()
{
  lcd.init();         // initialise LCD
  irrecv.enableIRIn();      // initialise the IR receiver
}

void loop()
{
  if(irrecv.decode(&reading))     // read the IR signal
  {
    translateIR();        // function to map signal to display string
    irrecv.resume();        // receive the next infrared signal
    delay(1000);        // delay before next IR signal
  }
}

void translateIR()        // function to determine display string
{
  switch(reading.value)     // switch ... case rather than a series
  {         //    of if ... else instructions
// example IR codes
    case 0xFF6897: displ("Outcome "+String(millis()/1000)); break;        // string of millis()
    case 0xFF30CF: displ("Result "+String(reading.value,HEX)); break;       // string of signal
    case 0xFF18E7: displ("Event "+String(reading.value,DEC)); break;
    default: displ("Not valid");      // default display
  }
}

void displ(String s)        // function to display string on LCD
{
  lcd.print(s);       // display string on LCD
  delay(2000);        // delay 2000ms
  lcd.clear();                 // clear LCD display and move cursor to zero position
}

