/*******************************************************************************
 * Sketch name: DC motors and photoelectric encoders Table 23-5
 * Description: motors controlled by interrupts using the millis function
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 23 - DC motors
 ******************************************************************************/

unsigned long Atime = 0;
int fixTime = 500;
float chkTime;
float rpm;
volatile int count = 0;
int IN1 = 6;
int IN2 = 5;
int slot = 20;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, counter, RISING);
  analogWrite(IN1, 60);
  analogWrite(IN2, 0);
}

void loop()
{
  if (millis() - Atime >= fixTime)
  {
    noInterrupts();
    chkTime = (millis() - Atime)/1000.0;
    rpm = 60*count/(slot*chkTime);
    Serial.print("rpm = ");
    Serial.println(rpm, 0);
    count = 0;
    Atime = millis();
    interrupts();
  }
}

void counter()
{
  count++;
}

