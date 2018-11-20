/*******************************************************************************
 * Sketch name: receive then transmit in Table 17-3
 * Description: receive then transmit data structures
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
  float value;
  char text[26];
} dataStruct;
dataStruct data;
int led = 1;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, addresses[0]);
  radio.openWritingPipe(addresses[1]);
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
  }
  delay(500);
  radio.stopListening();
  led = 1-led;
  radio.write(&led, sizeof(led)); 
  delay(500);
}

