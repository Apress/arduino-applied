/*******************************************************************************
 * Sketch name: Timer1 registers
 * Description: schedule an event based on overflow of Timer1 register with pre-scalar
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 20 - Interrupts and timed events
 ******************************************************************************/

int LEDpin = 11;        // LED pin

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  pinMode(LEDpin, OUTPUT);      // LED pin as output
  TCCR1A = 0;       // initialise register TCCR1A
  TCCR1B = 0;       // initialise register TCCR1B
  TCNT1 = 65511;       // define TCNT1 in setup and ISR
  TCCR1B |= (1<<CS12);      // set pre-scalar to 256    
  TIMSK1 |= (1<<TOIE1);     // enable Timer1 overflow interrupt
}

ISR(TIMER1_OVF_vect)      // interrupt at Timer1 overflow
{
  TCNT1 = 65511;       // define TCNT1 in setup and ISR
//  if(millis()<9000) Serial.println(millis());   // print interrupt times (ms)
  digitalWrite(LEDpin, !digitalRead(LEDpin)); // turn LED on or off
}

void loop()       // nothing in void loop() function
{}

