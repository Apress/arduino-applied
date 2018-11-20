/*******************************************************************************
 * Sketch name: control sequence of ArduDroid app
 * Description: display control sequences of ArduDroid app
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

void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
}

void loop()
{
  readSerial();       // function to read control sequence
  if(flag == 1)       // if control sequence read
  {
    for (int i=0; i<3; i++)
    {
      Serial.print(val[i]);Serial.print(" ");   // display three control variables
    }
    for (int i=0; i<bufferSz; i++) Serial.print(data[i]);   // display alphanumeric data
    Serial.println("");
  }
  flag = 0;         // reset flag for new control sequence
  for (int i=0; i<bufferSz; i++) data[i]='\0';    // overwrite data with null character
  index = 0;        // reset data index to zero
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

