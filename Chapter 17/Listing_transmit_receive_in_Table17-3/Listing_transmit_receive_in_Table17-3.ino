/*******************************************************************************
 * Sketch name: transmit then receive in Table 17-3
 * Description: transmit then receive data structures
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
  float value;
  char text[26] = "Transmission";
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
  radio.write(&data, sizeof(data));
  delay(500);
  radio.startListening();
  while(!radio.available());
  radio.read(&led, sizeof(led));
  if(led == 1) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  delay(500);
}

