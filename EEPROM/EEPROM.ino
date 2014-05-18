// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
uint8_t _deviceAddress = 0x50;
#define I2C_EEPROM_TIMEOUT 1000
uint32_t _lastWrite;

void setup()
{
  Wire.begin();
  TWBR = 12;
  Serial.begin(115200);
  char addr = 0;
  char WriteData = 0x5a;
  char ReadData;
  writeByte(addr, WriteData);
  Serial.print("WriteData: ");
  Serial.println(WriteData, HEX);
  ReadData = readByte(addr);
  Serial.print("ReadData: ");
  Serial.println(ReadData, HEX);
}

void loop()
{
}

int writeByte(uint16_t address, uint8_t Data)
{
   waitEEReady();
  Wire.beginTransmission(_deviceAddress);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(Data);
  int rv = Wire.endTransmission(_deviceAddress);
  _lastWrite = micros();
  return rv;
}

uint8_t readByte(uint16_t address)
{
   uint8_t rdata;
   waitEEReady();
   Wire.beginTransmission(_deviceAddress);
   Wire.write((int)(address >> 8));
   Wire.write((int)(address & 0xFF));
   Wire.endTransmission();
   Wire.requestFrom(_deviceAddress, (uint8_t) 1);
   while (Wire.available()) 
       rdata = Wire.read();
   return rdata;
}

void waitEEReady()
{
   #define I2C_WRITEDELAY 5000
   while((micros()-_lastWrite) <= I2C_WRITEDELAY)
   {
       Wire.beginTransmission(_deviceAddress);
       int x = Wire.endTransmission();
       if(x == 0)
         break; 
   }   
}
