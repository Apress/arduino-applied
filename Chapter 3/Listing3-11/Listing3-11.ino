/*******************************************************************************
 * Sketch name: infrared distance sensor
 * Description: measure distance with TCRT500 infrared distance sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int IRpin = A0;          // IR sensor pin
int threshPin = 7;          // threshold pin
int reading, thresh;

void setup()
{
  Serial.begin(9600);         // set Serial Monitor baud rate
}

void loop()
{
  reading = analogRead(IRpin);               // read IR sensor pin
  thresh = 1-digitalRead(threshPin);               // read threshold pin
  Serial.print("Distance: ");                // print "Distance: to Serial Monitor
  Serial.print(reading);Serial.print("\t");              // print IR sensor value and a tab
  Serial.print("Threshold : ");Serial.println(thresh);             // print "Threshold" and value
  delay(1000);                   // delay 1s
}


