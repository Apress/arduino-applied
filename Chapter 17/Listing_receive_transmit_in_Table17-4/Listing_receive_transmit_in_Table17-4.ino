/*******************************************************************************
 * Sketch name: receive then transmit in Table 17-4
 * Description: receive then transmit data structures with potentiometer reading
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 17 - Wireless communication
 ******************************************************************************/

#include <SPI.h>
#include <RF24.h>
RF24 radio(7, 8);
byte addresses[ ][6] = {"12", "14"}; 
typedef struct
{
  int number = 1;
  int angle;
  float value;
  char text[26];
} dataStruct;
dataStruct data;
int led = 1;
#include <Servo.h>        // include the servo motor library
Servo servo;        // associate servo with Servo library
int servoPin = 4;       // servo motor pin


void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, addresses[0]);
  radio.openWritingPipe(addresses[1]);
  servo.attach(servoPin);      // initialise servo motor
}

void loop()
{
  radio.startListening();
  if(radio.available())
  {
    radio.read(&data, sizeof(data));
    Serial.print(data.text);Serial.print("\t");
    Serial.print(data.number);Serial.print("\t");
    Serial.println(data.value);
    servo.write(data.angle);        // rotate servo motor
  }
  delay(500);
  radio.stopListening();
  led = 1-led;
  radio.write(&led, sizeof(led)); 
  delay(500);
}

