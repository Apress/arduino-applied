/*******************************************************************************
 * Sketch name: RFID for accessing a secure site
 * Description: identify validity of RFID card and control LEDs
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 11 - Radio frequency identification
 ******************************************************************************/

#include <SPI.h>        // include SPI library
#include <MFRC522.h>      // include MFRC522 library
int RSTpin = 9;       // reset pin for MFRC522
int SDApin = 10;        // serial data pin
MFRC522 mfrc522(SDApin, RSTpin);                // associate mfrc522 with MFRC522 library
int redLED = 4;       // red LED pin
int greenLED = 3;       // green LED pin
int nuid = 1;       // number of valid cards
String uids[20];        // list of valid UIDs – maximum 20
String uid;
int cardOK, pin, piccType;
int cardRead;      // ** for add/delete card sketch

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  SPI.begin();        // initialise SPI bus
  mfrc522.PCD_Init();     // initialise MFRC522
  pinMode (redLED, OUTPUT);   // define LED pins as output
  pinMode (greenLED, OUTPUT);
  uids[0] = "c049275";      // UIDs of valid cards
}

void loop()
{
  if(!mfrc522.PICC_IsNewCardPresent()>0) return;    // wait for a new card
  if(!mfrc522.PICC_ReadCardSerial()>0) return;   // read new card content
  cardID(mfrc522.uid.uidByte, mfrc522.uid.size);    // function to read card UID
  Serial.print("\nCard UID\t");       // print "card UID" and a tab
  Serial.println(uid);          // print card UID
  piccType = mfrc522.PICC_GetType(mfrc522.uid.sak); // card PICC type
  Serial.print("PICC type\t");        // print PICC type
  Serial.println(mfrc522.PICC_GetTypeName(piccType)); // card SAK HEX code
  Serial.print("SAK code\t");       // print "SAK code" and a tab
  Serial.println(mfrc522.uid.sak);      // print SAK HEX code
  cardOK = 0;
  pin = redLED;
  for (int i=0; i<nuid; i++)
  {
    if(uid == uids[i])          // determine if card on valid list
    {
      cardOK = 1;
      pin = greenLED;         // set relevant LED pin
    }
  }         // function to turn on LED and print SAK
  cardResult(mfrc522.uid.uidByte, mfrc522.uid.size);
}

void cardID(byte * buffer, byte bufferSize) // function to read card UID
{
  uid="";         // increment uid with buffer
  for (int i=0; i<bufferSize; i++) uid=uid+String(buffer[i], HEX);
}

void cardResult(byte * buffer, byte bufferSize) // function to turn on LED, print SAK
{
  digitalWrite(pin, HIGH);      // turn on and off relevant LED
  delay(1000);
  digitalWrite(pin, LOW);
  for (int i = 0; i < bufferSize; i++)    // print to Serial Monitor SAK code
  {
    if(buffer[i] <16) Serial.print(" 0");   // with leading "0" for HEX values
    else Serial.print(" ");
    Serial.print(buffer[i], HEX);
  }
  if (cardOK == 1) Serial.println("\tValid");   // print message to Serial Monitor
  else Serial.println("\tInvalid");     // depending on card validity
}

