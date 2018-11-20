/*******************************************************************************
 * Sketch name: reading GNSS messages using the NeoGPS library
 * Description: extract position and satellite data with NeoGPS library
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 19 - Global navigation satellite system
 ******************************************************************************/

// As individual satellite information is required
// edit the file NMEAGPS_cfg, within the src folder of the NeoGPS library,
// and uncomment the lines in Listing 19‒2

#include <AltSoftSerial.h>      // include AltSoftSerial library
AltSoftSerial AltSoft;                 // associate AltSoft with AltSoftSerial library
#include <NMEAGPS.h>      // include NeoGPS library
NMEAGPS nmea;       // associate nmea with NMEAGPS library
gps_fix gps;        // associate gps with NMEAGPS library
int GPS, SBAS, Nsat, count;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  AltSoft.begin(9600);      // serial connection to GPS module
  Serial.println("time, lat, long, altitude, speed, satellite data");   // column headers
  delay(500);
}

void loop()
{
  if (nmea.available(AltSoft))      // GPS data available
  {
    gps = nmea.read();      // latest satellite message
    if(gps.valid.time)        // validated time – every second
    {
      if(gps.dateTime.hours < 10) Serial.print("0");  // leading zeros for time
      Serial.print(gps.dateTime.hours); Serial.print(":");
      if(gps.dateTime.minutes < 10) Serial.print("0");
      Serial.print(gps.dateTime.minutes); Serial.print(":");
      if(gps.dateTime.seconds < 10) Serial.print("0");
      Serial.print(gps.dateTime.seconds); Serial.print(", ");
    }
    if(gps.valid.location)        // validated location
    {
      Serial.print(gps.latitude(), 3); Serial.print(", ");    // latitude and longitude
      Serial.print(gps.longitude(), 3); Serial.print(", ");
    }
    if(gps.valid.altitude) {Serial.print(gps.altitude(), 1);Serial.print(", ");}    // altitude
    if(gps.valid.speed) {Serial.print(gps.speed_kph(), 1);Serial.print(", ");}    // speed
    if(gps.valid.satellites)
    {
      Serial.print(gps.satellites);     // number of satellites for fix
      Serial.print(",");
      GPS = 0;
      SBAS = 0;
      Nsat = 0;
      for (int i=0; i<16; i++)      // max number of visable satellites
      {
        if (nmea.satellites[i].tracked) 
        {
          Nsat++;       // number of tracked satellites
          if (nmea.satellites[i].id <= 32) GPS++;
          else if (nmea.satellites[i].id >32 && nmea.satellites[i].id <= 64) SBAS++;
        }
      }
      Serial.print(Nsat);Serial.print(",");   // display satellite numbers
      Serial.print(GPS);Serial.print(",");
      Serial.println(SBAS);
      count = 0;
      for (int i=0; i<16; i++)
    if (nmea.satellites[i].tracked)   // display only tracked satellites
//      if (nmea.satellites[i].id>0)      // display all visible satellites
      {
        Serial.print(nmea.satellites[i].id);Serial.print(",");
        Serial.print(nmea.satellites[i].elevation);Serial.print(",");
        Serial.print(nmea.satellites[i].azimuth);Serial.print(",");
        Serial.print(nmea.satellites[i].snr);Serial.print(",");
        count++;
        if(count%4==0) Serial.println();
      }
      if(count%4!=0) Serial.println();
    }
  }
}

