/*******************************************************************************
 * Sketch name: Cayenne, ESP8266 with LED, LDR and BMP280 sensor
 * Description: display on Cayenne website or app BMP280 measurements, 
 *              a time counter and a button to control a LED over Wi-Fi
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
#include <Adafruit_Sensor.h>    // include Adafruit_Sensor library
#include <Adafruit_BMP280.h>    // include Adafruit_BMP280 library
Adafruit_BMP280 bmp;      // associate bmp with Adafruit_BMP280 library
int LEDpin = D8;          // LED pin
int LDRpin = A0;          // light dependent resistor pin
int flashPin = 2;       // flashing LED pin GPIO 2
unsigned long count = 0;
int interval = 2000;        // 2s interval between MQTT messages
unsigned long lastTime = 0;
float temp, pressure, BasePressure, altitude;
int light;

void setup()
{
  bmp.begin(0x76);        // initiate bmp with I2C address
              // initiate Cayenne MQTT
  Cayenne.begin(username, mqttpass, clientID, ssid, wifipass);
  pinMode(LEDpin, OUTPUT);      // define LED pins as output
  digitalWrite(LEDpin, LOW);
  pinMode(flashPin, OUTPUT);
}

void loop()
{
  Cayenne.loop();         // Cayenne loop() function
  if(millis()-lastTime > interval)
  {
    temp = bmp.readTemperature();   // BMP280 temperature and pressure
    pressure = bmp.readPressure()/100.0;
    BasePressure = pressure + 10.0;   // assumed sea level pressure
    altitude = bmp.readAltitude(BasePressure);  // predicted altitude (m)
    light = analogRead(LDRpin);     // ambient light intensity
    light = constrain(light, 0, 1023);    // constrain light reading
    count++;            // increment counter
    if(count>99) count = 0;
    digitalWrite(flashPin, LOW);      // turn flashing LED on then off
    delay(10);
    digitalWrite(flashPin, HIGH);
     // send readings to Cayenne on virtual channels 
    Cayenne.virtualWrite(V1, temp, "temp", "c");  // define temperature reading 
          // channel2 is flashPin so V2 is not used to avoid confusion
    Cayenne.virtualWrite(V3, pressure, "bp", "pa");// define pressure reading
    Cayenne.virtualWrite(V4, altitude);
    Cayenne.virtualWrite(V5, light, "lum", "lux");// define luminosity reading
    Cayenne.virtualWrite(V6, count);
    lastTime=millis();        // update time
  }
}

CAYENNE_IN(0)           // Cayenne virtual channel 0
{
  digitalWrite(LEDpin, getValue.asInt()); // turn LED on or off
}

