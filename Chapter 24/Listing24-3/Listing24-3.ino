/*******************************************************************************
 * Sketch name: PID controller with variable setpoint
 * Description: maintain constant incident light with PID control of LED brightness
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 24 - Robot car
 ******************************************************************************/

float Kp=0;
float Ki=0;        // PID coefficients
float Kd=0;
float input, output, setpoint;     // PID variables
int PIDtime = 20;       // time (ms) between PID evaluations
int LDRpin = A0;        // LDR pin
int setPin = A4;       // setpoint potentiometer pin
int KiPin = A5;       // Ki potentiometer pin
int LEDpin = 11;        // LED on a PWM pin
unsigned long chkTime;
float pTime, error, lastError, integral, derivative;

void setup()
{
  pTime = PIDtime/1000.0; // PID evaluation time (s)
  chkTime = millis();
}

void loop()
{
  if(millis()-chkTime > PIDtime)
  {
    setpoint = analogRead(setPin);  // setpoint from potentiometer
    Ki = analogRead(KiPin)*15.0/1023;  // Ki (0 to 15) from potentiometer
    input = analogRead(LDRpin); // read LDR value as PID input
    error = setpoint-input; // PID error
    integral = constrain(integral,0,255) + error*Ki*pTime; // PID integral and error
    derivative = (error - lastError)/pTime;  // PID derivative
    lastError = error; // retain last error
    output = Kp*error + constrain(integral,0,255) + Kd*derivative; // evaluate PID output
    output = constrain(output, 0, 255);  // constrain PID output
    analogWrite(LEDpin, output); // LED brightness is PID output
    chkTime = millis(); // reset time to next PID evaluation
  }
}

