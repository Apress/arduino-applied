/*******************************************************************************
 * Sketch name: interrupt switch and LED
 * Description: include interrupt to "override" delay
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int LEDpin = 7;        // LED pin
int switchPin = 3;        // switch pin
volatile int switchState = LOW;      // initial switch state

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  attachInterrupt(1, State, CHANGE);
}

void loop()
{
  Serial.println(millis());     // display time (ms) on Serial Monitor
  delay(1000);        // delay 1s
//  if(digitalRead(switchPin) != switchState) State();        // change of switch state
}

void State()        // can't use switch as a function name
{
  switchState = digitalRead(switchPin);   // update switch state
  if(switchState == HIGH) digitalWrite(LEDpin, !digitalRead(LEDpin));  // turn LED on or off
}

