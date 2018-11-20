/*******************************************************************************
 * Sketch name: DHT11 sensors
 * Description: measure temperature and humidity with DHT11 sensor  
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

#include <dht.h>        // include dht library
dht DHT;          // associate DHT with dht library
int DHTpin = 12;        // DHT11 unit on pin 12
int PCBpin = 7;       // PCB mounted DHT11 on pin 7
int check;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
}

void loop()
{
  check = DHT.read11(DHTpin);   // read DHT11 sensor on DHTpin
  Serial.print("DHT11 Unit temp: ");    // print text followed by a space
  Serial.print(DHT.temperature,0);    // temperature reading, integer only
  Serial.print("\thumidity: ");     // print tab then text
  Serial.println(DHT.humidity,0);   // humidity reading, integer only

  check = DHT.read11(PCBpin);   // repeat for the DHT11 on PCB
  Serial.print("DHT11 PCB temp: ");
  Serial.print(DHT.temperature,0);
  Serial.print("\thumidity: ");
  Serial.println(DHT.humidity,0);
  delay(1000);        // delay one second
}

