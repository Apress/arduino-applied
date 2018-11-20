/*******************************************************************************
 * Sketch name: debounced LED switch with continue delay
 * Description: switch debounced by checking for no change in switch state  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 2 - Switches
 ******************************************************************************/

int switchPin = 8;         // define switch pin
int LEDpin = 4;         // define LED pin
int reading;        // define reading as an integer
int switchState = LOW;      // set switch state to LOW
int LEDState = LOW;       // set LED state to LOW
unsigned long switchTime;     // define time as unsigned long
int lastSwitch = LOW;     // set last switch press in debounce time
int debounceTime = 50;       // define debounce time in ms

void setup()
{
  pinMode(LEDpin, OUTPUT);    // LED pin as output
}

void loop()
{
  reading = digitalRead(switchPin);                // read switch pin
  if(reading != lastSwitch)               // if reading different from last reading
  {
    switchTime = millis();               // time switch state change in debounce time
    lastSwitch  = reading;               // update last switch state
  }                  // is switch state the same for required time
  if((millis() - switchTime) > debounceTime)
  {
    if(reading !=switchState)
    {
      if (reading == HIGH && switchState == LOW) LEDState =!LEDState;
      digitalWrite(LEDpin, LEDState);
      switchState = reading;
    }
  }
}

