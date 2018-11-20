/*******************************************************************************
 * Sketch name: LDR and several LEDs
 * Description: light dependent resistor controls the number of LEDs switched on
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int Vdivid = A0;          // voltage divider analog pin
int nLEDs = 5;          // number of LEDs
int LEDpin[ ] = {8, 9, 11 ,12, 13};     // LED pins
int reading, level;

void setup()
{
  for (int i=0; i<5; i++) pinMode(LEDpin[i], OUTPUT); // define LED pins as outputs
}

void loop()
{
  reading = analogRead(Vdivid);       // voltage divider reading
  level = 0;          // set number of LEDs to zero
  level = map(reading, 0, 1023, 0, nLEDs+1);    // map reading to level
  for (int i = 0; i < nLEDs; i++)
  {
    if (i < level) digitalWrite(LEDpin[i], HIGH);   // turn on LED less than level
    else digitalWrite(LEDpin[i],LOW);     //    otherwise turn off LED
  }
  delay(1000);          // delay 1000ms
}


