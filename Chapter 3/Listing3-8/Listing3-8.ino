/*******************************************************************************
 * Sketch name: Hall effect sensor
 * Description: measure rpm and time per revolution with Hall effect sensor
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 3 - Sensors
 ******************************************************************************/

int switchPin = 8;    // hall effect sensor pin
int switchState = LOW;  // set switch to LOW
int revolution = 0;   // number of revolutions
float circum = 2.16;    // tyre circumference
unsigned long time = 0; // time (ms) per revolution
float speed, rpm;
int reading;

void setup()
{
  pinMode(switchPin, INPUT_PULLUP);   // pull-up resistor on hall effect sensor pin
  Serial.begin(9600);     // set baud rate for Serial Monitor
}

void loop()
{
  reading = digitalRead(switchPin);   // read hall switch
  if(reading != switchState)      // switch state changed
  {
    if (reading == HIGH && switchState == LOW)
    {         // update at start of new revolution
      revolution = revolution +1;     // increment number of revolutions
      time = millis() - time;     // time (ms) since last revolution
      speed = 3600.0*circum/time;   // speed calculation in km/h
      rpm = 60000.0/time;     // revolutions per minute
      Serial.print(revolution);Serial.print("\t");  // print number of revolutions
      Serial.print(speed,1);Serial.print("km/h\t"); // print speed to 1DP, " km/h" and tab
      Serial.print(rpm,0);Serial.println("rpm");  // print rpm, "rpm" and a new line
      time = millis();        // update revolution time
    }
    switchState = reading;      // update hall switch state
  } 
}

