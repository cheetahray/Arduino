// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define MCP23008_ADDRESS 0x20
#define MCP23008_IODIR 0x00
#define MCP23008_GPIO 0x09
const int buttonPin = 0;

void setup()
{
  MCP23008_begin();
  MCP23008_pinMode(buttonPin, INPUT);
  for(int i = 0; i < 7; i++)
  {
     MCP23008_pinMode((i+1),OUTPUT);  
  }
}


void loop()
{
  if(MCP23008_digitalRead(buttonPin) == LOW)
  {
    for(int i = 0; i < 7; i++)
    {
       TurnOn_LED(1 << i);
       delay(100);  
    }
    TurnOn_LED(0x00);
  }
  delay(200);
}

void TurnOn_LED(char value)
{
   for(int i=0; i<7; i++)
   {
      MCP23008_digitalWrite((i+1), ((value & ( 1<< i)) >> i));
   } 
}

void MCP23008_begin()
{
   Wire.begin();
   Wire.beginTransmission(MCP23008_ADDRESS);
   Wire.write((byte) MCP23008_IODIR);
   Wire.write((byte)0xFF);
   Wire.write((byte)0x00); 
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.write((byte)0x00);
   Wire.endTransmission();
}

void MCP23008_pinMode(uint8_t p, uint8_t d)
{
  uint8_t iodir;
  iodir = read8(MCP23008_IODIR);
  if(d == INPUT)
  {
     iodir |= 1 << p; 
  } 
  else
  {
     iodir &= ~(1 << p); 
  }
  write8(MCP23008_IODIR, iodir);
}

void MCP23008_digitalWrite(uint8_t p, uint8_t d)
{
   uint8_t gpio;
   gpio = readGPIO();
   if(d == HIGH)
   {
      gpio |= 1 << p;
   }  
   else 
   {
      gpio &= ~(1 << p); 
   }  
   writeGPIO(gpio);
}

uint8_t MCP23008_digitalRead(uint8_t p)
{
  return (readGPIO() >> p) & 0x1; 
}

uint8_t readGPIO(void)
{
   return read8(MCP23008_GPIO); 
}

void writeGPIO(uint8_t gpio)
{
   write8(MCP23008_GPIO, gpio);
}

uint8_t read8(uint8_t addr)
{
   Wire.beginTransmission(MCP23008_ADDRESS);
   Wire.write((byte) addr);
   Wire.endTransmission();
   Wire.requestFrom(MCP23008_ADDRESS, 1);
   return Wire.read();  
}

void write8(uint8_t addr, uint8_t data)
{
   Wire.beginTransmission(MCP23008_ADDRESS);
   Wire.write((byte) addr);
   Wire.write((byte) data);
   Wire.endTransmission();  
}
