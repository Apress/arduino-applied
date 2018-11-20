/*******************************************************************************
 * Sketch name: LED switch with debounce time
 * Description: switch debounced by checking switch status after time delay
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 2 - Switches
 ******************************************************************************/

int switchPin = 8;          // define switch pin
int LEDpin = 4;         // define LED pin
int reading;          // define reading as an integer
int switchState = LOW;        // set switch state to LOW
int LEDState = LOW;       // set LED state to LOW

void setup()
{
  pinMode(LEDpin, OUTPUT);      // LED pin as output
}

void loop()
{
  reading = digitalRead(switchPin);       // read switch pin
  if(reading != switchState)                     // if state of switch has changed
  {
    delay(50);          // debounce time of 50ms
    reading = digitalRead(switchPin);     // read switch pin again
    if(reading != switchState)        // compare switch state again
    {
      if (reading == HIGH && switchState == LOW) LEDState =!LEDState;
       digitalWrite(LEDpin, LEDState);
       switchState = reading;
    }
  }
}


