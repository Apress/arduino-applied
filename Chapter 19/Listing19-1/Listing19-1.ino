/*******************************************************************************
 * Sketch name: reading GNSS messages
 * Description: extract position and satellite data from RMC and GGA messages
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 19 - Global navigation satellite system
 ******************************************************************************/

#include <AltSoftSerial.h>      // include AltSoftSerial library
AltSoftSerial AltSoft;                 // associate AltSoft with AltSoftSerial library
String NMEAdata, nmea, val[6], temp[19];  // define string to store data
int rec, lastRow;
  String message[3]={"$GPRMC","$GPGGA","$GPGSV"}; // GPS message labels
//String message[3]={"$GLRMC","$GLGGA","$GLGSV"}; // GLONASS message labels 
// matrix of UTX – CFG – MSG message settings
const unsigned char ublox[ ] PROGMEM = {
181,98,6,1,8,0,240,0,0,0,0,0,0,1,0,36,      // GGA message off
181,98,6,1,8,0,240,1,0,0,0,0,0,1,1,43,      // GLL message off
181,98,6,1,8,0,240,2,0,0,0,0,0,1,2,50,      // GSA message off
181,98,6,1,8,0,240,3,0,0,0,0,0,1,3,57,      // GSV message off
181,98,6,1,8,0,240,4,0,0,0,0,0,1,4,64,      // RMC message off
181,98,6,1,8,0,240,5,0,0,0,0,0,1,5,71,      // VTG message off
181,98,6,1,8,0,240,0,0,1,0,0,0,1,1,41,      // GGA message set on
181,98,6,1,8,0,240,3,0,1,0,0,0,1,4,62,      // GSV message set on
181,98,6,1,8,0,240,4,0,1,0,0,0,1,5,69,      // RMC message set on
  181,98,6,62,36,0,0,0,22,4,0,4,255,0,0,0,0,1,1,1,3,  // GPS and GLONASS both off
     0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,0,0,0,1,163,9,
  181,98,6,62,36,0,0,0,22,4,0,4,255,0,1,0,0,1,1,1,3,  // GPS on
     0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,0,0,0,1,164,37
//181,98,6,62,36,0,0,0,22,4,0,4,255,0,0,0,0,1,1,1,3,  // GLONASS set on
//   0,0,0,0,1,5,0,3,0,0,0,0,1,6,8,255,0,1,0,0,1,164,13 
};

void setup() 
{
  Serial.begin(9600);       // baud rate for Serial Monitor
  AltSoft.begin(9600);                // serial connection to GPS module
  for(int i = 0; i < sizeof(ublox); i++)
  {
    AltSoft.write(pgm_read_byte(ublox+i));  // send message settings to GPS module
    delay(5);
  }
  Serial.println("time, lat, long, altitude, speed, satellite data");   // column headers
  delay(1000);
}

void loop()
{
  NMEAdata = AltSoft.readStringUntil('\n'); // read data until a carriage return
  nmea = NMEAdata.substring(0, 6);    // first 6 characters are message name
  if(nmea == message[0]) rec = 0;   // message name equals $GLRMC
  else if(nmea == message[1]) rec = 1;    //        or $GLGGA
  else if(nmea == message[2])rec = 2;   //        or $GLGSV
  switch (rec)        // use switch … case
  {
    case 0:
      parseMessage(NMEAdata, 7);    // parse GPRMC message, 7 values
      val[0]=temp[0].toInt();   // time
      val[1]= temp[2].toFloat()/100.0;    // latitude
      val[2]= temp[4].toFloat()/100.0;    // longitude
      if(temp[5]="W") val[2]="-"+val[2];
      val[4]= String(temp[6].toFloat()*1.852);  // convert speed in knots to kmph
    break;
    case 1:
      parseMessage(NMEAdata, 9);    // parse GPGGA message, 9 values
      val[3]=temp[8];       // altitude (m)
      val[5]=temp[6];       // number of satellites for fix
    break;
    case 2:
      parseMessage(NMEAdata,19);    // parse GLGSV message
      if(temp[1]=="1")
      {
        val[6]=temp[2];       // number of visible satellites
        for (int i=0; i<6; i++) {Serial.print(val[i]);Serial.print(",");}
        Serial.println();
        for (int i=0;i<6;i++) val[i]="";
      }   
      if(temp[1].toInt()<temp[0].toInt())   // not the last line of data
      {
        for (int i=3;i<19;i++) {Serial.print(temp[i]);Serial.print(",");}
        Serial.println();
      }
      else          // last line of data
      {
        lastRow = 4*(temp[2].toInt()-(temp[1].toInt()-1)*4)+3;
        for (int i=3;i<lastRow;i++) {Serial.print(temp[i]);Serial.print(",");}
        Serial.println();
      }
    break;
    default:   break;
  }
}

void parseMessage(String data, int nval)    // function to parse message
{
  data.replace('*',',');
  int istart, iend;
  iend = 0;
  for (int i=0; i<nval; i++)
  {
    istart = data.indexOf(",", iend);     // istart is location before value
    iend = data.indexOf(",", istart+1);     // iend is location after value
    temp[i] = data.substring(istart+1, iend);
  }
}

