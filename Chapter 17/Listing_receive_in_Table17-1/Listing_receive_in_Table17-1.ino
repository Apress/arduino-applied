/*******************************************************************************
 * Sketch name: receive in Table 17-1
 * Description: receive transmitted data structure and display data
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 17 - Wireless communication
 ******************************************************************************/

#include <SPI.h>
#include <RF24.h> 
RF24 radio(7, 8);
byte addresses[ ][6] = {"12"};
typedef struct
{
  int number; 
  float value;
  char text[26];
} dataStruct;
dataStruct data;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, addresses[0]);
  radio.startListening();
}

void loop()
{
  if(radio.available())
  {
    radio.read(&data, sizeof(data));
    Serial.print(data.text);Serial.print("\t");
    Serial.print(data.number);Serial.print("\t");
    Serial.println(data.value);
  }
}

