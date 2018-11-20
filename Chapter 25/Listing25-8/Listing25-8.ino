/*******************************************************************************
 * Sketch name: alarm, LED and light intensity
 * Description: trigger an alarm if ambiant light increases and send an email
 *              and/or text notification over Wi-Fi
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 25 - Wi-Fi communication
 ******************************************************************************/

#include <CayenneMQTTESP8266.h>    // Cayenne MQTT library
char ssid[] = "xxxx";       // change xxxx to your Wi-Fi ssid
char wifipass[] = "xxxx";     // change xxxx to your Wi-Fi password
char username[] = "xxxx";     // change xxxx to your Cayenne username
char mqttpass[] = "xxxx";     // change xxxx to your Cayenne password
char clientID[] = "xxxx";     // change xxxx to your Cayenne client identity
int LEDpin = 15;          // LED pin GPIO 15 or D8
int alarmPin = 13;        // alarm pin GPIO 13 or D7
int LDRpin = A0;          // LDR on pin A0
int flashPin = 2;       // flashing LED pin GPIO 2 
int reading, alarm;
int interval = 2000;        // 2s interval between LDR readings
unsigned long LDRtime = 0;

void setup()
{
  Serial.begin(9600);         // initiate Cayenne MQTT
  Cayenne.begin(username, mqttpass, clientID, ssid, wifipass);
  pinMode(LEDpin, OUTPUT);        // define LED pins as output
  pinMode(alarmPin, OUTPUT);
  pinMode(flashPin, OUTPUT);
  alarm = 0;            // set alarm as "OFF"
}

void loop()
{
  Cayenne.loop();         // Cayenne loop() function
  if(millis()-LDRtime>interval)
  {
    LDRtime = millis();
    reading = analogRead(LDRpin);
    // if alarm ON, then send LDR reading to Cayenne on channel V1, otherwise send zero
    if (alarm == 1) Cayenne.virtualWrite(V1, reading, "lum", "lux");
    else Cayenne.virtualWrite(V1, 0, "lum", "lux");
    delay(20);
  }
    digitalWrite(flashPin, LOW);      // LED GPIO 2 active LOW
    delay(10);            // flash to indicate power on
    digitalWrite(flashPin, HIGH);
}

CAYENNE_IN(0)           // Cayenne virtual channel 0
{
  digitalWrite(LEDpin, getValue.asInt()); // get LED status
}
CAYENNE_IN(3)           // Cayenne virtual channel 3
{
  alarm = getValue.asInt();       // get alarm state
  digitalWrite(alarmPin, alarm);
}

