/*******************************************************************************
 * Sketch name: MAX7219 speed and potentiometer
 * Description: control scrolling speed across MAX7219 modules with potentiometer
 *              for text entered on Bluetooth Terminal HC-05 app
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 16 - Bluetooth communication
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <MD_Parola.h>      // include MD_Parola library
//#include <MD_MAX72xx.h>    // include MD_MAX72xx library
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
int devices = 4;        // number of MAX7219 modules
int CSpin = 10;       // chip select pin for SPI
                       // associate parola with MD_Parola library
MD_Parola parola = MD_Parola(HARDWARE_TYPE, CSpin, devices);  // hardware SPI
int frameDelay = 20;        // initial frame speed
const int bufferSz = 60;      // array must be sized with a const
char message[bufferSz];     // message currently displayed
char newMessage[bufferSz];      // new message to be displayed
char c;         // character input
int index;          // number of characters in message
int flag = 0;
int potPin = A5;   // potentiometer pin

void setup()
{
  Serial.begin(9600);     // set baud rate for Serial Monitor
  parola.begin();       // start MD_Parola
  parola.displayClear();
  parola.displaySuspend(false);
  parola.displayScroll(message, PA_LEFT, PA_SCROLL_LEFT, frameDelay);
  strcpy(message, "Enter message");   // copies text to message
// use buttons to change message speed
  Serial.println("Send + to speed up or - to slow down");
  Serial.println("\nType a message to scroll"); // display message on Serial Monitor
}

void loop()
{
  newSpeed();           // function to change speed
  readSerial();         // function to get new message
  if(flag == 1)         // new message
  {
    for (int i=index;i<bufferSz-1;i++) newMessage[i]= '\0'; // replace with null character
    strcpy(message, newMessage);                 // copy newMessage to message
    Serial.print("Message: ");Serial.println(message);      // display message on Serial Monitor
    flag = 0;         // reset flag and index
    index = 0;
  }
    if (parola.displayAnimate()) parola.displayReset(); // scroll message
}

void readSerial()       // function to get new message
{
  while (Serial.available()>0)      // when data in Serial buffer
  {
    c = Serial.read();        // read character from Serial buffer
    if ((c == '\n') || (index >= bufferSz-2)) flag = 1; // new line at end of new message
    else
    {
      delay(5);       // delay 5ms between characters
      newMessage[index++] = c;    // save next char to new message
      flag = 0;
    }
  }
}

void newSpeed()        // function to set the speed
{
  frameDelay = map(analogRead(potPin), 0, 1023, 20, 100);
  constrain(frameDelay, 20, 100);   // constrain speed: 20 to 100
  parola.setSpeed(frameDelay);    // speed is the delay between frames
}


