/*******************************************************************************
 * Sketch name: determining PID coefficients with a circular buffer
 * Description: circular buffer to minimise noise variation on potentiometer values
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 24 - Robot car
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <RF24.h>       // include RF24 library
RF24 radio(7, 8);       // associate radio with RF24 library
byte addresses[ ][6] = {"12"};
typedef struct        // define a structure
{
  float Kp, Ki, Kd;       // PID coefficients
} dataStruct;
dataStruct data;
#include <Adafruit_GFX.h>     // include Adafruit GFX library
#include <Adafruit_SSD1306.h>   // include Adafruit SSD1306 library
Adafruit_SSD1306 oled(-1);            // associate oled with Adafruit_SSD1306 library
int Kpins[3] = {A3, A6, A7};      // Kp, Ki and Kd potentiometer pins
const int nVal = 10;        // number of values in circular buffer
int val[3][nVal];       // circular buffer for three variables
int value;
int sum[ ] = {0, 0, 0};       // sum of circular buffer values
int n[ ] = {0, 0, 0};       // index of current values in buffer
int minVal = 5;       // minimum deviation from mean
int K[3];         // mean values of circular buffer

void setup()
{
  radio.begin();          // initialise radio 
  radio.openWritingPipe(addresses[0]);      // open transmitting pipe
             // OLED display and I2C address
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();        // clear OLED display
  oled.setTextColor(WHITE);       // set font colour
  oled.setTextSize(1);        // set font size
  oled.display();         // start display instructions
    for (int i=0; i<3; i++)
  {
    for (int j=0; j<nVal; j++) val[i][j] = 0;              // set circular buffer values to zero
  }
}

void loop()
{
    getKvalues();       // function to update circular buffer
    data.Kp = K[0] *40.0/1023;   // Kp (0 to 40) from potentiometer
    data.Ki = K[1] *10.0/1023;   // Ki (0 to 10) from potentiometer
    data.Kd = K[2] *1.0/1023;    // Kd (0 to 1) from potentiometer
    oled.clearDisplay();      // clear OLED display
    oled.setCursor(0,0);      // position cursor at (0, 0)
    oled.print("Kp: ");       // display text and Kp value
    oled.println(data.Kp);      // followed by a carriage return
    oled.print("Ki: ");       // display text and Ki value
    oled.println(data.Ki);
    oled.print("Kd: ");       // display text and Kd value
    oled.print(data.Kd); 
    oled.display();       // start display instructions
    radio.write(&data, sizeof(data));   // transmit Kp and Kd values
    delay(50);
}

void getKvalues()       // function to update circular buffer
{
  for (int i=0; i<3; i++)     // repeat for each PID coefficient
  {
    value = analogRead(Kpins[i]);   // read current potentiometer value
    if(value>0)
    {
      if(abs(value-K[i]) > minVal)      // potentiometer value differs
      {         //     sufficiently from mean value
        sum[i] = sum[i] - val[i][n[i]];   // subtract "oldest" value from buffer
        val[i][n[i]] = value;     // replace "oldest" with current value
        sum[i] = sum[i] + value;      // update circular buffer total
        n[i]++;       // increment index of current value
        if(n[i] > nVal-1) n[i] = 0;     // if at end of circular buffer
      }
    }
    else          // reset circular buffer to zero when
    {         //      potentiometer value is zero
      for (int j=0; j<nVal; j++) val[i][j] = 0;
      sum[i]=0;
    }
    K[i] = sum[i]/nVal;       // mean values of circular buffer
  }
}

