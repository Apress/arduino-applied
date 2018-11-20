/*******************************************************************************
 * Sketch name: 4-note piano
 * Description: play one of four sounds while switch pressed
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

int Note_G = 392;    // note frequencies (Hz)
int Note_A = 440;
int Note_B = 494;
int Note_C = 523;
int piezoPin = 13;    // Piezo transducer pin
int switch_G = 8; 
int switch_A = 9;   // define switches
int switch_B = 10;
int switch_C = 12;

void setup()
{
  for (int i = 8; i<13; i++) pinMode(i, INPUT_PULLUP);  // pins set HIGH  
}
void loop()
{           // sound on switch press
  while(digitalRead(switch_A) == LOW) tone(piezoPin, Note_A);
  while(digitalRead(switch_B) == LOW) tone(piezoPin, Note_B);
  while(digitalRead(switch_C) == LOW) tone(piezoPin, Note_C);
  while(digitalRead(switch_G) == LOW) tone(piezoPin, Note_G);
  noTone(piezoPin);         // switch off sound
}

