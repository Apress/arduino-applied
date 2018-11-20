 /*******************************************************************************
 * Sketch name: square wave with Timer1 fast PWM mode
 * Description: square wave with duty cycle controlled by potentiometer
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

int PWMpin = 10;        // define PWM pin on Arduino pin 10
int potPin = A0;        // define potentiometer on pin A0
unsigned long freq = 50000;     // required square wave frequency
int prescalar = 1;        // define pre-scalar
int overflow;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(PWMpin, OUTPUT);    // define PWMpin as OUTPUT
  TCCR1A = 0;       // initialise register TCCR1A
  TCCR1B = 0;       // initialise register TCCR1B
        // set compare output mode and set pre-scalar to 1 with Fast PWM mode
  TCCR1A |= (1<<WGM10) | (1<<WGM11)  | (1<<COM1B1);
  TCCR1B |= (1<<CS10)     | (1<<WGM12)  | (1<<WGM13);
  overflow = F_CPU / (freq*prescalar);    // Timer1 overflow value
  Serial.println(overflow);     // print Timer1 overflow value
  OCR1A = overflow-1;     // counter starts at zero
}

void loop()
{         // change OCR1B register and duty cycle
  OCR1B = map(analogRead(potPin),0,1023,0,overflow);
}

