/*******************************************************************************
 * Sketch name: sound sensor
 * Description: detect sound above threshold with LM393 sound sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int soundPin = 11;    // sound sensor pin
int LEDpin = 5;   // LED pin
int detected = LOW;   // sound detect state to LOW
unsigned long detectTime; // time sound detected
int lag = 1000;    // time between sounds (ms)
int sound;

void setup ()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  pinMode(LEDpin, OUTPUT);      // LED pin as output
}

void loop ()
{
  sound = digitalRead(soundPin);    // read sound pin
  if (sound == LOW)       // sound detected with LOW, not HIGH
  {
    detectTime = millis();      // start time of new sound
    if (detected == LOW)      // if currently no sound      
    {
      Serial.print("new SOUND");Serial.print("\t"); // print "new SOUND" and tab
      detected = HIGH;      // update sound detect state to HIGH
      digitalWrite(LEDpin, detected);   // turn LED on
    }
  }
  else if (sound == HIGH)     // no sound detected
  {         // continuous sound no longer detected
    if(detected == HIGH && (millis()-detectTime) > lag) 
    {
      Serial.println("now quiet");      // print "now quiet" with a new line
      detected = LOW;     // update sound detect state to LOW
      digitalWrite(LEDpin, detected);   // turn LED off
    }
  }
}

