// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define I2CADDR 0x60

PROGMEM int FullSine[32] = {
   2048,2447,2831,3185,3495,3750,
   3939,4056,4095,4056,3939,3750,
   3495,3185,2831,2447,2048,1648,
   1265,910,  600, 345, 156,  39,
   0,    39,  156, 356, 600, 910,
   1264, 1648
};

void setup()
{
  //Wire.begin();
}

void setVoltage(int output)
{
   char twbrback = TWBR;
   TWBR = ((F_CPU / 400000L) - 16) / 2;
   Wire.beginTransmission(I2CADDR);
   Wire.write(0x40);
   Wire.write(output/ 16);
   Wire.write((output % 16) << 4);
   Wire.endTransmission();
   TWBR = twbrback; 
}

void loop()
{
  int i;
  for(i = 0; i< 32; i++)
  {m,
     setVoltage(pgm_read_word(&(FullSine[i])));
     delay(analogRead(A0)/4);  
  }  
  
}
