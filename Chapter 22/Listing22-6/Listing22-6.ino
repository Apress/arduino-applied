/*******************************************************************************
 * Sketch name: light sensor, sound and LED
 * Description: play sound, control LED brightness and display message
 *              dependent on incident light
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

int LDRpin = A0;    // LDR voltage divider
int LEDpin = 9;   // LED on PWM pin
int piezoPin = 13;    // Piezo transducer pin
int duration = 100;    // sound duration (ms)
int LED, LDR, freq;

void setup() 
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  pinMode(piezoPin,OUTPUT);   // define Piezo pin as output
}

void loop() 
{
  LDR = analogRead(LDRpin);     // read LDR
  LED = map(LDR, 0, 500, 255, 0);   // map LDR inversely to LED brightness
  LED = constrain (LED, 0, 255);    // constrain LED brightness
  freq = map(LDR, 0, 900, 262, 494);    // map LDR to sound frequency
  freq = constrain (freq, 262, 494);    // constrain sound frequency
  Serial.print(freq);Serial.print("\t");Serial.print(LDR);
  analogWrite(LEDpin, LED);     // set LED brightness
  tone (piezoPin, freq, duration);    // Piezo pin and frequency defined
  Serial.print("Light intensity is ");    // message to Serial Monitor
  if(LDR >= 750) Serial.println("Bright");
  else if(LDR >= 500) Serial.println("Light");  // display light intensity class
  else if(LDR >= 250) Serial.println("Dim");
  else Serial.println("Dark");
  delay(1000);        // delay 1s
}

