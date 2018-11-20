/*******************************************************************************
 * Sketch name: measure distance with HC-SR04 ultrasonic distance sensor
 * Description: measure distance with the ultrasonic distance sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int trigPin = 6;        // HC-SR04 trigger pin
int echoPin = 7;        // HC-SR04 echo pin
float duration, distance;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(trigPin, OUTPUT);     // define trigger pin as output
}

void loop()
{
  digitalWrite(echoPin, LOW);     // set the echo pin LOW
  digitalWrite(trigPin, LOW);     // set the trigger pin LOW
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);      // set the trigger pin HIGH for 10s
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);    // measure the echo time (s)
  distance = (duration/2.0)*0.0343;   // convert echo time to distance (cm)
  if(distance>400 || distance<2) Serial.println("Out of range");
  else
  {
    Serial.print("Distance : "); Serial.print(distance, 1); Serial.println(" cm");
  }
  delay(500);
}

