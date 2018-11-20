/*******************************************************************************
 * Sketch name: Message scrolling with MAX7219 modules and ArduDroid app
 * Description: scroll across MAX7219 modules text entered on ArduDroid app
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 16 - Bluetooth communication
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <MD_Parola.h>      // include MD_Parola library
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
int devices = 4;        // number of MAX7219 modules
int CSpin = 10;       // chip select pin for SPI
                       // associate parola with MD_Parola library
MD_Parola parola = MD_Parola(HARDWARE_TYPE, CSpin, devices);  // hardware SPI
int val[3];
int frameDelay = 20;        // initial frame speed
const int bufferSz = 60;      // array must be sized with a const
char message[bufferSz];     // message currently displayed
char newMessage[bufferSz];      // new message to be displayed
char c;         // character input
int index;          // number of characters in message
int flag = 0;

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

void readSerial()        // function to get new message
{
  while (Serial.available()>0)      // when data in Serial buffer
  {
    if(flag == 0)       // new control sequence
    {
      c = Serial.read();      // read character in Serial buffer
      for (int i=0;i<3;i++) val[i] = Serial.parseInt(); // parse 3 integers 12, 99 and 99
      flag = 1;       // control sequence read
    }
    c = Serial.read();        // read character from Serial buffer
    delay(5);       // delay 5ms between characters
    if(c == '+')        // increase speed
    {
      c = Serial.read();      // read end of control sequence
      frameDelay=parola.getSpeed()-5;   // by reducing frame delay
      if(frameDelay < 20) frameDelay = 20;
      Serial.print("Reduce delay to ");
      Serial.println(frameDelay);
      parola.setSpeed(frameDelay);    // change display speed
      flag = 0;       // message unchanged
    }
    else if(c == '-')       // decrease speed
    {
      c = Serial.read();      // read end of control sequence
      frameDelay=parola.getSpeed()+5;   // by increasing frame delay
      Serial.print("Increase delay to ");
      Serial.println(frameDelay);
      parola.setSpeed(frameDelay);
      flag = 0;
    }         // save next char to new message
    else if((c != '|') && (c != '#')) newMessage[index++] = c;  
  }
}

