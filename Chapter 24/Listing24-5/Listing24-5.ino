/*******************************************************************************
 * Sketch name: balancing robot
 * Description: balance using quaternion values from accelerometer and gyroscope
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 24 - Robot car
 ******************************************************************************/

#include <I2Cdev.h> // include I2Cdev library
#include <MPU6050_6Axis_MotionApps20.h> // include MPU6050 library
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include <Wire.h> // include Wire library
#endif
MPU6050 mpu;     // associate mpu with MPU6050 library
uint8_t mpuIntStatus; // MPU-6050 interrupt status
volatile bool mpuInterrupt = false; // if MPU-6050 interrupt is HIGH
bool DMPinit = false; // DMP initialisation status
uint8_t DMPstatus; // device status (0 = success, !0 = error)
uint16_t fifoPacket; // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount; // count of bytes in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

int I2Caddress = 0x68;       // I2C address of MPU-6050
#include <SPI.h>            // include SPI library
#include <RF24.h>           // include RF24 library
RF24 radio(7, 8);           // associate radio with RF24 library
byte addresses[ ][6] = {"12"}; 
typedef struct              // define a structure
{
  float K1, K2, K3;             // transmitted PID coefficients
} dataStruct;
dataStruct data;
float Kp = 0, Ki = 0, Kd = 0;   // PID coefficients
int pidTime = 20; // interval between PID evaluatons (ms)
unsigned long chkTime = 0;
int IN1 = 10;            // left wheel forward PWM pin
int IN2 = 9;            //        backward
int IN3 = 6;            // right wheel forward
int IN4 = 5;           //          backward
int inputLimit = 25;     // limit on pitch angle (-25, 25)
int outMin = 60; // minimum output to turn on motors
int LEDpin = 3;
float qw = 0, qx = 0, qy = 0, qz = 0, pitch;  // quaternion values from MPU-6050
float integral = 0;
float input, output, setpoint, error, lastError, derivative, pTime, sumsquare;
int mSpeed;

void setup()
{
  Serial.begin(115200);     // set baud rate to 115200
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin(); // initialise I2C
    Wire.setClock(400000); // set I2C clock speeed to 400kHz (default is 100kHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true); // library for fast I2C access
  #endif
  mpu.initialize(); // initialise mpu and set DMPstatus variable
  DMPstatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(10);    
  mpu.setYGyroOffset(-20);   // gyro X, Y and Z and accelZ offsets
  mpu.setZGyroOffset(100);  // from IMU_Zero in MPU6050 library
  mpu.setZAccelOffset(1730);
  if (DMPstatus == 0)    // DMP initialised
  {
    mpu.setDMPEnabled(true);    // start Digital Motion Processor (DMP) of MPU-6050
    attachInterrupt(0, DMPdataReady, RISING);    // interrupt on GY-521 module
    mpuIntStatus = mpu.getIntStatus();
    DMPinit = true;    // DMP initialised
    fifoPacket = mpu.dmpGetFIFOPacketSize();   // expected DMP packet size
  }
  else Serial.print("DMP initialization failed");
  radio.begin();   // initialise radio 
  radio.openReadingPipe(0, addresses[0]); // open reading pipe
  radio.startListening();
  motor(0, 0, 0, 0);  // initialise motor to zero
  pinMode(LEDpin, OUTPUT);
  setpoint = 2;  // setpoint angle with robot balanced
  integral = 0;
  pTime = pidTime/1000.0; // PID evaluation time (s)
  delay(1000);
}

void loop()
{
  while (!mpuInterrupt && fifoCount < fifoPacket)    // MPU interrupt or extra packet available
  {
    if(millis()-chkTime > pidTime) // PID evaluation
    {
      if(radio.available()) // transmitted data available
        {
          radio.read(&data,sizeof(data));
          Kp = data.K1;  // update PID coefficients
          Ki = data.K2;
          Kd = data.K3;
         digitalWrite(LEDpin, !digitalRead(LEDpin)); // flash LED to denote received transmission
        }
      pitch = -asin(2.0*(qx*qz-qw*qy))*180/PI;     // pitch angle
      input = constrain(-pitch, -inputLimit, inputLimit); // constrain pitch angle
      error = setpoint - input;         // PID error component     
      integral = constrain(integral,-255,255) + error*Ki*pTime; // PID integral component
      derivative = (error - lastError)/pTime; // PID derivative component
      lastError = error; // update last error
      output = Kp*error + constrain(integral,-255,255) + Kd*derivative; // PID output
      mSpeed = constrain(output, -255,255);     // maximum motor speed of 255 
      if(mSpeed > outMin) motor(mSpeed, 0, mSpeed, 0);    // set motor direction and speed
      else if(mSpeed < -outMin) motor(0, -mSpeed, 0, -mSpeed);
      else motor(0, 0, 0, 0); // if output low, motor speed is zero    
      chkTime=millis();    
    }
  }
  fifoCount = mpu.getFIFOCount();    // get current FIFO count
  mpuInterrupt = false;   // reset interrupt flag
  mpuIntStatus = mpu.getIntStatus();    // get INT_STATUS byte
  if (bitRead(mpuIntStatus,4) == 1 || fifoCount == 1024)   // check for overflow, INT_STATUS fifth bit 5 = 1, bits [0, 1, 2 ...]
  {
    mpu.resetFIFO();    // reset FIFO
    Serial.println("FIFO overflow");
  }
  else if(bitRead(mpuIntStatus,1) == 1)   // check for DMP data ready interrupt, INT_STATUS second bit = 1, bits [0, 1, 2 ...]
  {
    while (fifoCount < fifoPacket) fifoCount = mpu.getFIFOCount();   // wait for correct available data length
    mpu.getFIFOBytes(fifoBuffer, fifoPacket);   // read a packet from FIFO
    fifoCount -= fifoPacket;   // track FIFO count if there is > 1 packet available
    qw = ((fifoBuffer[0] << 8) | fifoBuffer[1]);    //  quaternion values
    qx = ((fifoBuffer[4] << 8) | fifoBuffer[5]); // from MPU6050_6Axis_MotionApps20.h
    qy = ((fifoBuffer[8] << 8) | fifoBuffer[9]); // lines 123-127 and 611-614
    qz = ((fifoBuffer[12] << 8) | fifoBuffer[13]);
    qw = qw/16384.0; // divide quaternion values by 2^14
    qx = qx/16384.0;
    qy = qy/16384.0;
    qz = qz/16384.0;     
  }
}

void motor(int leftF, int leftB, int rightF ,int rightB)        // control motors
{
  float bias = 1.0;
  analogWrite(IN1, leftF*bias); // bias left or right motor speed is required
  analogWrite(IN2, leftB*bias);
  analogWrite(IN3, rightF);
  analogWrite(IN4, rightB);
}

void DMPdataReady() // interrupt from MPU-6050
{
  mpuInterrupt = true;
}
