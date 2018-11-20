/*******************************************************************************
 * Sketch name: reset GNSS message settings
 * Description: reset message settings before use of NeoGPS library
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 19 - Global navigation satellite system
 ******************************************************************************/

#include <AltSoftSerial.h>      // include AltSoftSerial library
AltSoftSerial AltSoft;                 // associate AltSoft with AltSoftSerial library
// matrix of UTX – CFG – MSG message settings
const unsigned char ublox[ ] PROGMEM = {
181,98,6,1,8,0,240,0,0,0,0,0,0,1,0,36,      // GGA message off
181,98,6,1,8,0,240,1,0,0,0,0,0,1,1,43,      // GLL message off
181,98,6,1,8,0,240,2,0,0,0,0,0,1,2,50,      // GSA message off
181,98,6,1,8,0,240,3,0,0,0,0,0,1,3,57,      // GSV message off
181,98,6,1,8,0,240,4,0,0,0,0,0,1,4,64,      // RMC message off
181,98,6,1,8,0,240,5,0,0,0,0,0,1,5,71,      // VTG message off
181,98,6,1,8,0,240,0,0,1,0,0,0,1,1,41,      // GGA message on
181,98,6,1,8,0,240,1,0,1,0,0,0,1,2,48,      // GLL message on
181,98,6,1,8,0,240,2,0,1,0,0,0,1,3,55,      // GSA message on
181,98,6,1,8,0,240,3,0,1,0,0,0,1,4,62,      // GSV message on
181,98,6,1,8,0,240,4,0,1,0,0,0,1,5,69,      // RMC message on
181,98,6,1,8,0,240,5,0,1,0,0,0,1,6,76,      // VTG message on
  181,98,6,62,36,0,0,0,22,4,0,4,255,0,0,0,0,1,1,1,3,  // GPS and GLONASS both off
     0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,0,0,0,1,163,9,
  181,98,6,62,36,0,0,0,22,4,0,4,255,0,1,0,0,1,1,1,3,  // GPS on
     0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,0,0,0,1,164,37
//181,98,6,62,36,0,0,0,22,4,0,4,255,0,0,0,0,1,1,1,3,  // GLONASS on
//   0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,1,0,0,1,164,13 
};

void setup() 
{
  Serial.begin(9600);     // baud rate for Serial Monitor
  AltSoft.begin(9600);      // serial connection to GPS module
  for(int i = 0; i < sizeof(ublox); i++)
  {
    AltSoft.write(pgm_read_byte(ublox+i));  // send message settings to GPS module
    delay(5);
  }
  Serial.println("NMEA messages all on");
}

void loop()       // nothing in void loop function
{ }

