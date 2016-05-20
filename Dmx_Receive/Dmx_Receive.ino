/*************************************************************************************************************
 *
 * Title			    : Example DMX Receiver
 * Version		    : v 0.3
 * Last updated	            : 07.07.2012
 * Target		    : Arduino mega 2560, Arduino mega 1280, Arduino nano
 * Author                    : Toni Merino - merino.toni at gmail.com
 * Web                       : www.deskontrol.net/blog
 *
 **************************************************************************************************************/
#include <lib_dmx.h>  // comment/uncomment #define USE_UARTx in lib_dmx.h as needed

// This example receive 4 channels from address 1 to 4 and write analog values to PWM pins 2 to 5

// outputs update in main loop


//*********************************************************************************************************
//                        New DMX modes *** EXPERIMENTAL ***
//*********************************************************************************************************
#define    DMX512     (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???

int inState = 0;
int pinState = 0;

const long interval = 5000;   

void setup() 
{
  //　　板子使用 2 pin 為 RS485　控制
  ArduinoDmx0.set_control_pin(2);    // Arduino output pin for MAX485 input/output control (connect to MAX485 pins 2-3) 
  ArduinoDmx0.set_rx_address(1);      // set rx0 dmx start address
  ArduinoDmx0.set_rx_channels(64);     // number of rx channels//　　使用多少頻道
  ArduinoDmx0.init_rx(DMX512);        // starts universe 0 as rx, NEW Parameter DMX mode

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);
  digitalWrite(11,0);

}  //end setup()

int mode(int _1st, int _2nd, int _3rd, int _4th)
{
  if(_1st == 0 && _2nd == 0 && _3rd == 0 && _4th == 0)
    return 0;
  if(_1st == 0 && _2nd == 0 && _3rd == 0 && _4th != 0)
    return 1;
  if(_1st == 0 && _2nd == 0 && _3rd != 0 && _4th == 0)
    return 2;
  if(_1st == 0 && _2nd == 0 && _3rd != 0 && _4th != 0)
    return 3;
  if(_1st == 0 && _2nd != 0 && _3rd == 0 && _4th == 0)
    return 4;
  if(_1st == 0 && _2nd != 0 && _3rd == 0 && _4th != 0)
    return 5;
  if(_1st == 0 && _2nd != 0 && _3rd != 0 && _4th == 0)
    return 6;
  if(_1st == 0 && _2nd != 0 && _3rd != 0 && _4th != 0)
    return 7;
  if(_1st != 0 && _2nd == 0 && _3rd == 0 && _4th == 0)
    return 8;
  if(_1st != 0 && _2nd == 0 && _3rd == 0 && _4th != 0)
    return 9;
  if(_1st != 0 && _2nd == 0 && _3rd != 0 && _4th == 0)
    return 10;
  if(_1st != 0 && _2nd == 0 && _3rd != 0 && _4th != 0)
    return 11;
  if(_1st != 0 && _2nd != 0 && _3rd == 0 && _4th == 0)
    return 12;
  if(_1st != 0 && _2nd != 0 && _3rd == 0 && _4th != 0)
    return 13;
  if(_1st != 0 && _2nd != 0 && _3rd != 0 && _4th == 0)
    return 14;
  if(_1st != 0 && _2nd != 0 && _3rd != 0 && _4th != 0)
    return 15;
    
}

void loop()
{
  
  for (int ii=0; ii<4; ii+=4)
  {
    int ret = mode(ArduinoDmx0.RxBuffer[0], ArduinoDmx0.RxBuffer[1], ArduinoDmx0.RxBuffer[2], ArduinoDmx0.RxBuffer[3]);
    delay(interval-500);
    digitalWrite(8,  ret>>3 );
    ret = ( (ret >= 8) ? (ret - 8) : ret );
    digitalWrite(9,  ret>>2 );
    ret = ( (ret >= 4) ? (ret - 4) : ret );
    digitalWrite(10, ret>>1 );
    ret = ( (ret >= 2) ? (ret - 2) : ret );
    digitalWrite(11, ret);  
    delay(500);
    digitalWrite(8,0);
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);  
  }

}  //end loop()


