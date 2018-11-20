/*******************************************************************************
 * Sketch name: LED switch
 * Description: turns LED on or off when switch is pressed or not pressed  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 2 - Switches
 ******************************************************************************/

int switchPin = 8;          // define switch pin
int LEDpin = 4;         // define LED pin
int reading;          // define reading as integer

void setup()
{
  pinMode(LEDpin, OUTPUT);       // LED pin as output
}

void loop()
{
  reading = digitalRead(switchPin);     // read switch pin
  digitalWrite(LEDpin, reading);                     // turn LED on if switch is HIGH
}           // turn LED off if switch is LOW

