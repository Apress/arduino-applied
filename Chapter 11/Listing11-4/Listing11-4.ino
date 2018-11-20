/*******************************************************************************
 * Sketch name: read and write to contactless card
 * Description: read data on card and write data to contactless card
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
MFRC522::MIFARE_Key key;      // access key
byte blockData[16] = {"ABCDEFGHIJKLMNOP"};  // data to be written
//byte blockData[16] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // reset block to default value
byte blockRead[18];       // to hold the read data
byte blocksz = sizeof(blockRead);
int block, sectorTrail, check;

void setup()
{
  Serial.begin(9600);     // define Serial output baud rate
  SPI.begin();        // initialise SPI bus
  mfrc522.PCD_Init();     // initialise mfrc522
  for (byte i=0; i<6; i++) key.keyByte[i] = 0xFF; // access key set to HEX 0xFF
}

void loop()
{         // print message to Serial Monitor
  Serial.println("Place card or tag beside MFRC522 reader");
  while (!mfrc522.PICC_IsNewCardPresent()) { }; // wait for a new card
  mfrc522.PICC_ReadCardSerial();    // given new card, read card content
  Serial.println("Enter block number");   // print message to Serial Monitor
  while(Serial.available() == 0) { }    // do nothing until entry to serial buffer
  while(Serial.available() >0) block=Serial.parseInt(); // extract block number
  if((block+1)%4==0 || block == 0)    // check if block is sector trailer block
  {
    Serial.print("Cannot write to block ");   // print message to Serial Monitor
    Serial.println(block);      // return to start of void loop()
    return;
  }
  writeBlock(block, blockData);     // function to write data
  Serial.print("\nFinished writing to block "); // print message to Serial Monitor
  Serial.println(block);
  for (block=0; block<64; block++)             // display content of non-sector trailer blocks
  {
    if((block+1) % 4 !=0 && block !=0)    // non-sector trailer blocks
    {
      readBlock(block, blockRead);    // function to read data
      Serial.print("\nBlock  ");      // print block number
      Serial.print(block);Serial.print("\t");
      for (int i=0 ; i<16 ; i++) Serial.write(blockRead[i]);  // print block data
    }
  }
  Serial.println("\n\nFinished reading blocks");       // print message to Serial Monitor
  Serial.println("Enter 1 to continue writing to a card or tag");
  while(Serial.available() == 0) { }         // do nothing until entry to serial buffer
     //extract integer from serial buffer
  while(Serial.available()>0) check=Serial.parseInt();
  mfrc522.PCD_StopCrypto1();        // stop communication to card or tag
}

void writeBlock (int block, byte blockData[ ])    // function to write to block
{
  sectorTrail = 3+4*(block/4);
  check = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
  sectorTrail, &key, &(mfrc522.uid));
  if (check != MFRC522::STATUS_OK) Serial.println(mfrc522.GetStatusCodeName(check));
  check = mfrc522.MIFARE_Write(block, blockData, 16);
  if (check != MFRC522::STATUS_OK) Serial.println(mfrc522.GetStatusCodeName(check));
}

void readBlock (int block, byte blockRead[ ])   // function to read block
{
  sectorTrail = 3+4*(block/4);
  check = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
  sectorTrail, &key, &(mfrc522.uid));
  if (check != MFRC522::STATUS_OK) Serial.println(mfrc522.GetStatusCodeName(check));
  check =  mfrc522.MIFARE_Read(block, blockRead, &blocksz);
  if (check != MFRC522::STATUS_OK) Serial.println(mfrc522.GetStatusCodeName(check));
}

