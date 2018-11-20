/*******************************************************************************
 * Sketch name: light dependent resistor and LED
 * Description: light dependent resistor controls LED brightness
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int Vdivid = A0;          // voltage divider analog pin
int LEDpin = 11;          // LED on PWM pin
int thresh = 500;         // threshold light intensity
int reading, bright;

void setup()
{
  pinMode(LEDpin, OUTPUT);        // LED pin as output
}

void loop()
{
  reading = analogRead(Vdivid);     // voltage divider reading
  bright = 0;         // set LED brightness to zero
                       // map reading to LED brightness
  if(reading<thresh) bright = map(reading, 0, thresh, 255, 0);
  analogWrite(LEDpin, bright);        // change LED brightness
  delay(1000);          // delay 1000ms
}

