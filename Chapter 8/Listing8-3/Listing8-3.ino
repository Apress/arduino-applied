/*******************************************************************************
 * Sketch name: servo motot with LDR
 * Description: control servo motor rotation with light dependent resistor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 8 - Servo and stepper motors
 ******************************************************************************/

#include <Servo.h>        // include servo library
Servo servo;        // associate servo with Servo library
int servoPin = 11;        // servo motor pin
int LDRpin = A0;       // LDR on analog pin A1
int maxLDR = 0;       // maximum LDR reading
int reading, maxAngle;

void setup()
{
  servo.attach(servoPin);       // define servo motor pin to servo library
  Serial.begin(9600);     // define Serial output baud rate
}

void loop()
{
  for (int angle=0; angle<190; angle = angle + 10)    // scan from angle 0° to 180°
  {
    servo.write(angle);     // rotate servo motor
    reading = analogRead(LDRpin);   // read light dependent resistor
    if (reading>maxLDR)     // compare reading to maximum
    {
      maxLDR = reading;       // update maximum light reading
      maxAngle = angle;     // update angle of max light reading
    }
    delay(50);        // delay 50ms between LDR readings
  }
  Serial.print("Light source at ");   // print text to Serial Monitor
  Serial.print(maxAngle);     // print angle of incident light
  Serial.println(" degrees");     // print " degrees" to Serial Monitor
  servo.write(maxAngle);      // rotate servo to point at the light source
  delay(1000);        // delay while pointing at light source
  maxLDR=0;       // reset maximum light reading
  servo.write(0);       // rotate to 0°
  delay(500);       // delay 500ms
}

