// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define DS1307_ADDRESS 0x68
byte zero = 0x00;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  setDateTime();
}

byte decToBcd(byte val)
{
   return ( (val/10*16) + (val % 10) );  
}

byte bcdToDec(byte val)
{
   return ( (val/16*10) + (val % 16) );  
}

void printDate()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111);
  int weekDay = bcdToDec(Wire.read());
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());
  Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);  
}

void setDateTime()
{
  byte second = 00;
  byte minute = 18;
  byte hour = 15;
  byte weekDay = 6;
  byte monthDay = 17;
  byte month = 5;
  byte year = 14;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(zero);
  Wire.endTransmission();  
}

void loop()
{
  printDate();   
  delay(1000);  
}
