/*******************************************************************************
 * Sketch name: Timer1 registers and two events
 * Description: schedule events based on overflow of Timer1 register with pre-scalar
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int LEDpin = 11;        // LED pin

void setup()        // interrupts at 1s and 0.2s later
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  TCCR1A = 0;       // initialise register TCCR1A
  TCCR1B = 0;       // initialise register TCCR1B
  OCR1A = 62500;        // trigger interrupt A at 1s
  OCR1B = 12500;        // trigger interrupt B 200ms later
  TCCR1B |= (1<<CS12) | (1<<WGM12);   // set pre-scalar 256 and CTC mode
  TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);  // enable OCR1A and OCR1B
}

ISR(TIMER1_COMPA_vect)      // interrupt at overflow A
{
  if(millis()<9000) {Serial.print("A ");Serial.println(millis());}
  digitalWrite(LEDpin, HIGH);
}

ISR(TIMER1_COMPB_vect)      // interrupt at overflow B
{
  if(millis()<9000) {Serial.print("B ");Serial.println(millis());}
  digitalWrite(LEDpin, LOW);
}

void loop()       // nothing in void loop() function
{ }

