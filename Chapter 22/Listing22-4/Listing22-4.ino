/*******************************************************************************
 * Sketch name: a series of notes
 * Description: play a series of notes
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

#include "notes.h"        // include reference to notes.h tab
int piezoPin = 12;        // Piezo transducer pin
int tune[ ] = {NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, 
                    NOTE_G4, 0, NOTE_B4, NOTE_C5};
int beats[ ] = {2, 1, 1, 2, 2, 2, 2, 2};    // length of note
int duration;

void setup()
{ }         // nothing in void setup() function

void loop()
{
  for (int i = 0; i < 8; i++)     // play the 8 notes
  {
    duration = 125*beats[i];      // duration of note = 125 or 250ms
    tone(piezoPin, tune[i], duration);    // generate sound
    delay(duration*1.25);   // interval between notes is 1.25note duration
  }
  while(1);       // stop the tune after being played once
}

