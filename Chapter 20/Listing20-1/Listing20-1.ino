/*******************************************************************************
 * Sketch name: switch and LED
 * Description: illustrate switch not detecting change during delay
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int LEDpin = 7;        // LED pin
int switchPin = 3;        // switch pin
int switchState = LOW;      // initial switch state

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
}

void loop()
{
  Serial.println(millis());     // display time (ms) on Serial Monitor
  delay(1000);        // delay 1s
  if(digitalRead(switchPin) != switchState) State();        // change of switch state
}

void State()        // can't use switch as a function name
{
  switchState = digitalRead(switchPin);   // update switch state
  if(switchState == HIGH) digitalWrite(LEDpin, !digitalRead(LEDpin));  // turn LED on or off
}

