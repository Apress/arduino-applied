/*******************************************************************************
 * Sketch name: Hall effect sensor and DC motor speed
 * Description: Hall effect sensor and potentiometer to measure and control motor speed
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

int hallPin = 4;        // hall effect switch pin
int hallState = LOW;        // set state to LOW
int IN3 = 6;        // motor forward pin
int IN4 = 5;        //           backward pin
int ENB = 3;        // motor enable pin
int potPin = A6;        // potentiometer pin
unsigned long time = 0;     // time (ms) per revolution
float hallrpm;
int reading, speed;

void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  pinMode(hallPin, INPUT_PULLUP);   // pull-up resistor on hall effect switch pin
  pinMode(IN3, OUTPUT);     // define motor pins as OUTPUT
  pinMode(IN4, OUTPUT);
  digitalWrite(IN3,1);        // set motor to forward rotation
  digitalWrite(IN4,0);
}

void loop()
{
  reading = analogRead(potPin);   // read potentiometer
  speed = map(reading, 0, 1023, 0, 255);    // map potentiometer value
  analogWrite(ENB,speed);     // set motor speed
  reading = digitalRead(hallPin);   // read hall switch
  if(reading != hallState)      // hall switch state changed
  {
    if (reading == HIGH && hallState == LOW)  // start of new revolution
    {
      time = millis() - time;     // time (ms) since last revolution
      hallrpm = 60000.0/time;     // revolutions per minute  
      Serial.print(speed);Serial.print("\t");   // display potentiometer value
      Serial.println(hallrpm,0);      // display motor speed (rpm)
      time = millis();        // update revolution time 
    }
    hallState = reading;       // update hall switch state
  } 
}

