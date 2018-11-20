/*******************************************************************************
 * Sketch name: IR emitter and receiver
 * Description: determine distance between infrared emitter and receiver
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 10 - Infrared sensor
 ******************************************************************************/

int IRpin = A5;          // IR receiver pin
int reading, dist;

void setup()
{
  Serial.begin(9600);       // set Serial Monitor baud rate
}

void loop()
{
  reading = analogRead(IRpin);      // reading from IR receiver
  if (reading<970) dist = 605*pow(reading, -0.53);    // convert reading to distance
  else dist =409 - 0.406 * reading;
  Serial.print(reading);Serial.print("\t");     // print reading, tab and
  Serial.println(dist);           //     distance to Serial Monitor
  delay(100);         // delay between readings
}

