/*******************************************************************************
 * Sketch name: display motor speeds on OLED
 * Description: extend Listing 23-6 to include OLED displa of motor speeds
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

#include<Wire.h>        // include Wire library
int I2Caddress = 0x68;      // I2C address of MPU-6050
float accelX, accelY, accelZ;     // values from MPU-6050
float roll, pitch, sumsquare;
#include <SPI.h>        // include SPI library
#include <RF24.h>       // include RF24 library
RF24 radio(7, 8);       // associate radio with RF24 library
byte addresses[ ][6] = {"12"};
typedef struct        // define a structure
{
  int right, left;        // PWM values for the DC motors
} dataStruct;
dataStruct data;
int minPWM = 50;        // minimum PWM value
int FB, LR;
int LRscalar = 1;       // scalar for accelerometer sensitivity
#include <Adafruit_GFX.h>      // include Adafruit GFX library
#include <Adafruit_SSD1306.h>   // include Adafruit SSD1306 library
Adafruit_SSD1306 oled(-1);   // associate display with Adafruit_SSD1306 library
int FBspeed, LRspeed;

void setup()
{
  Serial.begin(9600);
  Wire.begin();       // initiate I2C bus
  Wire.beginTransmission(I2Caddress);   // transmit to device at I2Caddress
  Wire.write(0x6B);       // PWR_MGMT_1 register
  Wire.write(0);        // set to zero to wake up MPU-6050
  Wire.endTransmission(1);      // end of transmission
  radio.begin();        // initialise radio 
  radio.openWritingPipe(addresses[0]);    // open transmitting pipe
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // OLED display and I2C address
  oled.clearDisplay();        // clear OLED display
  oled.setTextColor(WHITE);      // set font colour
  oled.setTextSize(2);       // set font size
  oled.display();          // start display instructions
}

void loop()
{
  Wire.beginTransmission(I2Caddress);   // transmit to device at I2Caddress
  Wire.write(0x3B);       // start reading from register 0x3B
  Wire.endTransmission(0);      // transmission not finished
  Wire.requestFrom(I2Caddress,6,true);    // request data from 6 registers
  accelX=Wire.read()<<8|Wire.read();    // combine AxHigh and AxLow values
  accelY=Wire.read()<<8|Wire.read();    // combine AyHigh and AyLow values
  accelZ=Wire.read()<<8|Wire.read();    // combine AzHigh and AzLow values
  accelX = accelX/pow(2,14);
  accelY = accelY/pow(2,14);      // scale X, Y and Z measurements
  accelZ = accelZ/pow(2,14);
  sumsquare = sqrt(accelX*accelX+accelY*accelY+accelZ*accelZ);
  accelX = accelX/sumsquare;
  accelY = accelY/sumsquare;      // adjusted accelerometer measurements
  accelZ = accelZ/sumsquare;
  roll = atan2(accelY, accelZ)*180/PI;    // roll angle
  pitch = -asin(accelX)*180/PI;     // pitch angle
  LR = map(pitch, -90, 90, -255, 255);    // tilt module left or right
  FB = map(roll, -90, 90, -255, 255);   // tilt module forward or backward 
  data.left = FB + LR/LRscalar;     // sum of scaled readings
  data.right = FB - LR/LRscalar;    // difference of scaled readings
  data.left = constrain(data.left, -255, 255);  // constrain PWM values (-255, 255)
  data.right = constrain(data.right, -255, 255);
  if(abs(data.left) < minPWM) data.left = 0;  // zero PWM value < minimum value
  if(abs(data.right) < minPWM) data.right = 0;
  radio.write(&data, sizeof(data));   // transmit PWM values
  delay(50);        // delay 50ms
  FBspeed = data.left;      // create variable without "dot"
  LRspeed = data.right;
  oled.clearDisplay();     // clear OLED display
  oled.setCursor(0,0);       // position cursor at (0, 0)
  oled.print("left: ");      // display text and motor speed
  oled.println(FBspeed);       //    followed by a carriage return
  oled.print("right: ");     // display text and motor speed
  oled.print(LRspeed);
  oled.display();        // start display instructions
}

