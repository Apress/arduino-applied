 /*******************************************************************************
 * Sketch name: square wave with Timer1 fast PWM 8-bit mode
 * Description: square wave with duty cycle controlled by potentiometer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

int PWMpin = 10;        // define PWM pin on Arduino pin 10
int potPin = A0;        // define potentiometer on pin A0

void setup()
{
  pinMode(PWMpin, OUTPUT);      // define PWMpin as OUTPUT
  TCCR1A = 0;         // initialise register TCCR1A
  TCCR1B = 0;         // initialise register TCCR1B
// set compare output mode and set pre-scalar to 1 with Fast PWM 8-bit mode
  TCCR1A |= (1<<WGM10) | (1<<COM1B1);
  TCCR1B |= (1<<CS10)     | (1<<WGM12);
}

void loop()
{
  OCR1B = analogRead(potPin)/4;   // change OCR1B register and duty cycle
}

