/*******************************************************************************
 * Sketch name: Bluetooth Terminal HC-05 app
 * Description: Bluetooth Terminal HC-05 app to control LEDs
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 16 - Bluetooth communication
 ******************************************************************************/

int redLED = 3;        // LED pins
int greenLED = 4;
char c;         // command letter input

void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  pinMode(redLED, OUTPUT);      // define LED pins as OUTPUT
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  while (Serial.available()>0)     // when data in Serial buffer
  {
    c = Serial.read();        // read character from Serial buffer
    switch (c)        // use switch…case for options
    {
    case 'R':
      digitalWrite(redLED, HIGH);   // red LED on
      Serial.println("red LED on");   // and print message to Serial
      break;
    case 'G':
      digitalWrite(greenLED, HIGH);   // green LED on
      Serial.println("green LED on");
      break; 
    case 'O':
      digitalWrite(redLED, LOW);    // Both LEDs off
      digitalWrite(greenLED, LOW); 
      Serial.println("both LEDs off");
      break; 
    default: break;       // Instruction letter other than R, G or O
    }
  }
}

