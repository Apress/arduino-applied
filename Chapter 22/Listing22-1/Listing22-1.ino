/*******************************************************************************
 * Sketch name: piezo transducer
 * Description: repeated sound of fixed frequency and duration
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 22 - Sound and sound waves
 ******************************************************************************/

int piezoPin = 6;        // define PWM pin for piezo transducer
float freq = 440;       // sound frequency (Hz)
int duration = 50;        // duration of sound (ms)
int interval = 500;        // sound duration plus pause (ms)
int pause;
int gap = 1000;
int reps = 5;    
int cycles = (duration*freq)/pow(10,3); // number of cycles for sound duration (s)
int timeHigh = pow(10,6)/(2.0*freq);    // time (microsecs) that square wave is HIGH

void setup()
{
  pinMode(piezoPin, OUTPUT);      // define piezo pin as output
  pause = interval-duration;        // pause between sounds
}

void loop()
{
  for (int j=0; j<reps; j++)
  {
    for (int i=0; i<cycles+1; i++)        // number of cycles per sound
    {
      digitalWrite(piezoPin, !digitalRead(piezoPin));   // square wave HIGH or LOW
      delayMicroseconds(timeHigh);
    }
    delay(pause);
  }
  delay(gap);

  for (int j=0; j<reps; j++)
  { 
    tone(piezoPin, freq, duration);        // sound frequency
    delay(interval);          // sound duration + pause
  }
  delay(gap);

  for (int j=0; j<reps; j++)
  {
    analogWrite(piezoPin, 64);      // analogWrite with 50% duty cycle
    delay(duration);        // duration of sound
    analogWrite(piezoPin, 0);     // no sound
    delay(pause);       // pause between sounds
  }
  delay(gap);
}


