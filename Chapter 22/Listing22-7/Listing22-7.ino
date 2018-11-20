 /*******************************************************************************
 * Sketch name: electro-Theremin
 * Description: imitate an electro-Theremin
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

#include <toneAC.h>  // include toneAC library
int LDRFpin = A2;   // LDR for frequency
int LDRVpin = A3;   // LDR for volume
int LDRF, LDRV, freq, volume;

void setup()
{ }     // nothing in void setup() function

void loop() 
{
  LDRF = analogRead(LDRFpin);   // LDR for frequency
  LDRV = analogRead(LDRVpin);   // LDR for volume
  freq = map(LDRF, 0, 900, 523, 1047);    // map sound frequency C5 to C6
  freq = constrain (freq, 523, 1047);   // constrain sound frequency
  volume = map(LDRV, 0, 900, 0, 10);    // map LDRV to volume
  volume = constrain (volume, 0, 10);   // constrain volume
  toneAC (freq, volume, 0);     // play sound with frequency and volume
}

