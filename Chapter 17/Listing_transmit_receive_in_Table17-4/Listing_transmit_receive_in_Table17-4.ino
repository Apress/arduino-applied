/*******************************************************************************
 * Sketch name: transmit then receive in Table 17-4
 * Description: transmit then receive data structures with potentiometer reading
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
  int number;
  int angle;
  float value;
  char text[24] = "Transmission";
} dataStruct;
dataStruct data;
int led;
int ledPin = 5;

void setup()
{
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  radio.stopListening();
  data.number = data.number+1;
  data.value = data.value+0.1;
  int potent = analogRead(A0);
  data.angle = map(potent, 0, 1023, 0, 180);
  radio.write(&data, sizeof(data));
  delay(500);
  radio.startListening();
  while(!radio.available());
  radio.read(&led, sizeof(led));
  if(led == 1) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  delay(500);
}

