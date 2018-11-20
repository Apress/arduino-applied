/*******************************************************************************
 * Sketch name: PIR sensor
 * Description: detect movement with HR-SC501 passive infrared sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int PIRpin = 11;          // PIR sensor pin
int LEDpin = 8;         // LED pin
int PIRstate = LOW;         // set PIR state to LOW
int reading;
unsigned long detectTime;       // time lag on PIR sensor
float moveTime;

void setup()
{
  Serial.begin(9600);       // set Serial Monitor baud rate
  pinMode(LEDpin, OUTPUT);        // LED pin as output
}

void loop()
{
  reading = digitalRead(PIRpin);      // read PIR pin
  if (reading == HIGH && PIRstate == LOW)   // PIR detected new movement
  {
    Serial.print("New movement detected");    // print to Serial Monitor
    detectTime = millis();        // time of movement
    PIRstate = HIGH;          // update PIR state to HIGH
    digitalWrite(LEDpin, PIRstate);     // turn LED on
  }
  else if (reading == LOW && PIRstate == HIGH)                 // movement no longer detected
  {
    moveTime = millis() - detectTime;     // duration of movement
    moveTime = moveTime/1000.0;
    Serial.print(" and lasted for ");     // print to Serial Monitor
    Serial.print(moveTime,1);       // print detect time (s) with 1DP
    Serial.println(" seconds");       // print text with a new line
    PIRstate = LOW;         // update PIR state to LOW
    digitalWrite(LEDpin, PIRstate);// turn LED off
  }
}


