/*******************************************************************************
 * Sketch name: OLED display
 * Description: display text and numbers on OLED display
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 13 - Screen displays
 ******************************************************************************/

#include <Adafruit_GFX.h>      // include Adafruit GFX library
#include <Adafruit_SSD1306.h>   // include Adafruit SSD1306 library
              // associate oled with Adafruit_SSD1306 library
Adafruit_SSD1306 oled(-1);      // no need to define Reset pin
 
void setup()
{         // OLED display and I2C address
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();      // clear OLED display
  oled.setTextColor(WHITE);     // set font colour
  oled.setTextSize(2);      // set font size (1, 2 3 or 4)
  oled.setCursor(0,0);      // position cursor at (0, 0)
  oled.println("Arduino");      // print text with carriage return
  oled.print("Applied");     // starting on new line print text
  oled.display();       // start display instructions
  delay(2000);        // delay 2s

  oled.clearDisplay();
  oled.setTextSize(1);      // font size 1 characters 68 pixels
  oled.setCursor(0,0);
  oled.println("Arduino");
  oled.print("Applied");
  oled.setCursor(45,16);      // position cursor at (x, y)
  oled.print("Arduino");      // at top left hand corner of text
  oled.setCursor(45,24);
  oled.print("Applied");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(3);      // font size 3 characters 1824 pixels
  oled.setCursor(0,8);      // maximum of 7 characters per row
  oled.print("1234567");
  oled.display();
}

void loop()         // nothing in void loop() function
{ }

