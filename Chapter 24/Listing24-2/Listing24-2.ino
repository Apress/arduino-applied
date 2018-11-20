/*******************************************************************************
 * Sketch name: PID controller with LDR and LED
 * Description: maintain constant incident light with PID control of LED brightness
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 24 - Robot car
 ******************************************************************************/

#include <PID_v1.h>      // include PID library
double Kp=0;
double Ki=0;        // PID coefficients
double Kd=0;
double input, output, setpoint;     // PID variables
// associate pid with PID_v1 library
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
int PIDtime = 20;       // time (ms) between PID evaluations
int LDRpin = A0;        // LDR pin
int KpPin = A4;       // Kp potentiometer pin
int KiPin = A5;       // Ki potentiometer pin
int LEDpin = 11;        // LED on a PWM pin
unsigned long chkTime;

void setup()
{
  pid.SetMode(AUTOMATIC);     // initiate PID
  pid.SetSampleTime(PIDtime);   // constant PID evaluation time interval
  setpoint = 500;       // constant PID setpoint
  chkTime = millis();
}

void loop()
{
  if(millis()-chkTime > PIDtime)
  {
    Kp = analogRead(KpPin) *3.0/1023;   // Kp (0 to 3) from potentiometer
    Ki = analogRead(KiPin) *15.0/1023;    // Ki (0 to 15) from potentiometer
    input = analogRead(LDRpin);   // read LDR value as PID input
    pid.SetTunings(Kp, Ki, Kd);     // update PID coefficients
    pid.Compute();        // evaluate PID
    analogWrite(LEDpin, output);    // LED brightness as PID output
    chkTime = millis();
  }
}

