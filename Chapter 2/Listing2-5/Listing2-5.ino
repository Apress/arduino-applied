/*******************************************************************************
 * Sketch name: LED and ball switch
 * Description: switch LED on and off with ball switch  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 2 - Switches
 ******************************************************************************/

int switchPin = 8;           // define switch pin
int LEDpin = 4;           // define LED pin
int reading;

void setup()
{
  pinMode(LEDpin,OUTPUT);         // LED pin as output
}

void loop()
{
  reading = digitalRead(switchPin);              // read switch pin
  if(reading == LOW) digitalWrite(LEDpin ,HIGH);           // if ball switch tips-over, turn led on
  else digitalWrite(LEDpin, LOW);   // ball switch not tipped-over, turn led off
}

