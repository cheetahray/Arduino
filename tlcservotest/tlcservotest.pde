//From the bildr article: http://bildr.org/2012/03/servos-tlc5940-arduino
//Requires the Tlc5940 library. http://code.google.com/p/tlc5940arduino/downloads/list

#include "Tlc5940.h"
#include "tlc_servos.h"
#include "Tlc5940.h"

#include <SoftEasyTransfer.h>
#include <NewSoftSerial.h>

NewSoftSerial solenoid(5, 7);

#define NUM_TLCS 3
/*
int numberOfServos = 48; //how many servos on the chain?
int IR;
*/
SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{  
  float mux0array[8];
};

SEND_DATA_STRUCTURE mydata;

boolean overlap[8], clockwise;
long count;

void setup()
{
  tlc_initServos();  // Note: this will drop the PWM freqency down to 50Hz.
  Tlc.clear();
  Serial.begin(9600);  
  solenoid.begin(9600);
  ET.begin(details(mydata), &solenoid);
  count = 0;
  clockwise = true;
}

void loop()
{
  memset(overlap,false,8);
  
  if(ET.receiveData()) 
  {
    for (int i=1; i<8; i++)
    {
      if(mydata.mux0array[i] < 75)
      {
         Serial.print(mydata.mux0array[i]);
         overlap[i] = true;
         switch(i)
         {
           case 1:
             for(int j=0; j<=2; j++)
             {
               tlc_setServo(j, 0);
             }
             for(int j=3; j<=5; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=6; j<=8; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 2:
             for(int j=6; j<=8; j++)
             {
               if(false == overlap[1])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=9; j<=11; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=12; j<=14; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 3:
             for(int j=12; j<=14; j++)
             {
               if(false == overlap[2])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=16; j<=18; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=19; j<=21; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 4:
             for(int j=19; j<=21; j++)
             {
               if(false == overlap[3])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=22; j<=24; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=25; j<=27; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 5:
             for(int j=25; j<=27; j++)
             {
               if(false == overlap[4])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=28; j<=30; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=32; j<=34; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 6:
             for(int j=32; j<=34; j++)
             {
               if(false == overlap[5])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=35; j<=37; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=38; j<=40; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
           case 7:
             for(int j=38; j<=40; j++)
             {
               if(false == overlap[6])
                 tlc_setServo(j, 0);
               else
                 tlc_setServo(j, 90);
             }
             for(int j=41; j<=43; j++)
             {
               tlc_setServo(j, 90);
             }
             for(int j=44; j<=46; j++)
             {
               tlc_setServo(j, 180);
             }
           break;
         }
         Serial.println();
      }
      /*
      else
      {
         switch(i)
         {
           case 1:
             for(int j=0; j<=2; j++)
             {
               tlc_setServo(j, 180);
             }
             for(int j=3; j<=5; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=6; j<=8; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 2:
             for(int j=6; j<=8; j++)
             {
               if(false == overlap[1])
                 tlc_setServo(j, 180);
             }
             for(int j=9; j<=11; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=12; j<=14; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 3:
             for(int j=12; j<=14; j++)
             {
               if(false == overlap[2])
               tlc_setServo(j, 180);
             }
             for(int j=16; j<=18; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=19; j<=21; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 4:
             for(int j=19; j<=21; j++)
             {
               if(false == overlap[3])
                 tlc_setServo(j, 180);
             }
             for(int j=22; j<=24; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=25; j<=27; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 5:
             for(int j=25; j<=27; j++)
             {
               if(false == overlap[4])
                 tlc_setServo(j, 180);
             }
             for(int j=28; j<=30; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=32; j<=34; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 6:
             for(int j=32; j<=34; j++)
             {
               if(false == overlap[5])
                 tlc_setServo(j, 180);
             }
             for(int j=35; j<=37; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=38; j<=40; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
           case 7:
             for(int j=38; j<=40; j++)
             {
               if(false == overlap[6])
                 tlc_setServo(j, 180);
             }
             for(int j=41; j<=43; j++)
             {
               tlc_setServo(j, random(0,180));
             }
             for(int j=44; j<=46; j++)
             {
               tlc_setServo(j, 0);
             }
           break;
         }
        
      }
      */
    }
    /*
    if(angle >= 180)
      clockwise = false;
    else if(angle <= 0)
      clockwise = true;
      
    if(false == clockwise)
      angle -= 10;
    else
      angle += 10;
    */
    count = 0;
    Tlc.update();
    delay(500);
  }
  else if (count++ > 450000)
  {
    for(int j=0; j<=46; j++)
    {
      tlc_setServo(j, random(0,180));
    }
    count = 0;
    Tlc.update();
  }  
}  //END LOOP










