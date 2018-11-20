/*******************************************************************************
 * Sketch name: transmit in Table 17-1
 * Description: transmit data structure
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 17 - Wireless communication
 ******************************************************************************/

#include <SPI.h>
#include <RF24.h>
#include <printf.h>
RF24 radio(7, 8);
byte addresses[ ][6] = {"12"};
typedef struct
{
  int number;
  float value;
  char text[26] = "Transmission";
} dataStruct;
dataStruct data;

void setup()
{
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  printf_begin();
  Serial.begin(9600);
}

void loop()
{
  data.number = data.number+1;
  data.value = data.value+0.1;
  radio.write(&data, sizeof(data));
  radio.printDetails(); 
  delay(1000);
}

