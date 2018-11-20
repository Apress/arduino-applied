/*******************************************************************************
 * Sketch name: infrared sensor
 * Description: detect infrared signal with VS1838B infrared sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

#include <IRremote.h>       // include IRremote library
int IRpin = 12;       // IR sensor pin
IRrecv irrecv(IRpin);       // associate irrecv with IRremote library
decode_results reading;     // IRremote variable reading
int LEDpin = 4;       // LED pin

void setup()
{
  Serial.begin(9600);       // set baud rate for Serial Monitor
  irrecv.enableIRIn();      // start the infrared receiver
  pinMode(LEDpin, OUTPUT);      // LED pin as output
}

void loop()
{
  if(irrecv.decode(&reading))     // read pulsed signal
  {
         if(reading.decode_type == NEC) Serial.print("NEC: ");    // NEC IR signal
    else if(reading.decode_type == SONY) Serial.print("Sony: ");  // Sony IR signal
    else if(reading.decode_type == RC5)  Serial.print("RC5: "); // RC5 IR signal
    else if(reading.decode_type == RC6)  Serial.print("RC6: "); // RC6 IR signal
    else if(reading.decode_type == AIWA_RC_T501)  Serial.print("AIWA_RC_T501: "); // AIWA_RC_T501 signal
    else if(reading.decode_type == DENON)  Serial.print("DENON: "); // DENON signal     
    else if(reading.decode_type == DISH)  Serial.print("DISH: "); // DISH signal   
    else if(reading.decode_type == JVC)  Serial.print("JVC: "); // JVC signal     
    else if(reading.decode_type == LG)  Serial.print("LG: "); // LG signal    
    else if(reading.decode_type == MITSUBISHI)  Serial.print("MITSUBISHI: "); // MITSUBISHI signal
    else if(reading.decode_type == PANASONIC)  Serial.print("PANASONIC: "); // Panasonic signal
    else if(reading.decode_type == SAMSUNG)  Serial.print("SAMSUNG: "); // SAMSUNG signal
    else if(reading.decode_type == SANYO)  Serial.print("SANYO: "); // SANYO signal
    else if(reading.decode_type == SHARP)  Serial.print("SHARP: "); // SHARP signal    
    else if(reading.decode_type == WHYNTER)  Serial.print("WHYNTER: "); // WHYNTER signal     
    else Serial.print("Other: ");
    Serial.print(reading.value, HEX);   // display device type and HEX code
    Serial.print("\tBits: ");     //    on Serial Monitor
    Serial.println(reading.bits);     // display number of IR signal bits
    digitalWrite(LEDpin, HIGH);     // turn LED on
    delay(100);        // delay before next IR signal
    digitalWrite(LEDpin, LOW);     // turn LED off
    irrecv.resume();        // receive the next infrared signal
  }
}

