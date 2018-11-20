/*******************************************************************************
 * Sketch name: display letters A, B and C
 * Description: simple display of letters on 8x8 dot matrix display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 7 - 8x8 dot matrix display
 ******************************************************************************/

// Arduino to display pins 
int pin[ ] = {19,13,12,9,8,11,7,10,17,16,6,5,15,4,14,3,2};
            // dot matrix display columns
int col[ ] = {pin[13],pin[3],pin[4],pin[10],pin[6],pin[11],pin[15],pin[16]};
// dot matrix display rows
int row[ ] = {pin[9],pin[14],pin[8],pin[12],pin[1],pin[7],pin[2],pin[5]}; 
byte val[3][8] = {4,10,17,17,31,17,17,0,             // decimal representation of letter A
        15,17,17,15,17,17,15,0,              // decimal representation of letter B
        14,17,1,1,1,17,14,0};            // decimal representation of letter C
unsigned long start;
bool pixel;

void setup()
{
  for (int i=1; i<18; i++) pinMode(pin[i], OUTPUT);   // display pins as output
  for (int i=0;i<8;i++) digitalWrite(col[i], LOW);    // set anodes LOW – turn off
  for (int i=0;i<8;i++) digitalWrite(row[i], HIGH);   // set cathodes HIGH – turn off
}

void loop()
{
  for (int n=0; n<3; n++)     // display the letters A, B, C
  {
    start = millis();       // milliseconds elapsed
    while (millis() < start+1000)     // display time for each letter
    for (int r=0; r<8; r++)
    {
      digitalWrite(row[r], LOW);      // set cathodes to LOW for each row
      for (int c=0; c<8; c++) 
      {
       pixel = bitRead(val[n][r], c);   // read cth bit in rth row of nth letter
        if(pixel == 1) digitalWrite(col[c], HIGH);  // set anode (column) HIGH, LED on
        delayMicroseconds(200);     // delay between LEDs in a row
        digitalWrite(col[c], LOW);      // reset anode to LOW, LED off
      }
      digitalWrite(row[r], HIGH);     // reset cathode to HIGH
    }
  }
}

