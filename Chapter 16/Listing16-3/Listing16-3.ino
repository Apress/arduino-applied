/*******************************************************************************
 * Sketch name: ArduDroid app (2)
 * Description: ArduDroid app to control LEDs
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 16 - Bluetooth communication
 ******************************************************************************/

char c;          // character input from ArduDroid app
int val[3];         // command, Arduino pin and pin value
const int bufferSz = 30;      // const int required to define array size
char data[bufferSz];        // alphanumeric data including | and #
int flag = 0;
int index;
int redLED = 3;        // red and green LED pins
int greenLED = 4;


void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  pinMode(redLED, OUTPUT);      // define LED pins as output
  pinMode(greenLED, OUTPUT);

}

void loop()
{
  readSerial();        // function to read control sequence
  if(flag == 1)       // if control sequence read
  {
    switch (val[0])       // switch ... case based on instruction
    {
      case 10:            // turn red or green LED on or off
        digitalWrite(val[1],!digitalRead(val[1]));
        break;
      case 11:
        analogWrite(val[1],val[2]);   // change red LED brightness
        break;
      case 12:
        if(data[0] == 'R') digitalWrite(redLED, HIGH);          // R: turn red LED on
        else if (data[0] == 'G') digitalWrite(greenLED, HIGH);          // G: turn green LED on
        else if (data[0] == 'O')                // O: turn both LEDs off
        {
          digitalWrite(redLED, LOW);
          digitalWrite(greenLED, LOW);
        }
        break;
      default: break;         // default case
    }
  }
  flag = 0;           // reset flag to zero
  for (int i=0; i<10; i++) data[i]='\0';      // overwrite previous data
  index = 0;          // reset data index to zero
}

void readSerial()       // function to read control sequence
{ 
  while (Serial.available()>0)      // when character in Serial buffer
  {
    if(flag == 0)       // new control sequence
    {
      c = Serial.read();      // read character from Serial buffer
      for (int i=0; i<3; i++) val[i]=Serial.parseInt(); // parse three control variables
      flag = 1;       // control sequence read
    }
    c = Serial.read();        // read character from Serial buffer
    delay(5);       // delay 5ms between characters
    if(c != '|' && c != '#') data[index++] = c;   // increment data, add next character
  }
}

