//From the bildr article: http://bildr.org/2012/03/servos-tlc5940-arduino
//Requires the Tlc5940 library. http://code.google.com/p/tlc5940arduino/downloads/list

#include "Tlc5940.h"
#include "tlc_servos.h"
#include "Tlc5940.h"

#include <SoftEasyTransfer.h>
#include <NewSoftSerial.h>

NewSoftSerial solenoid(5, 7);

#define NUM_TLCS 3

int numberOfServos = 48; //how many servos on the chain?
int IR;

SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{  
  float mux0array[8];
};

SEND_DATA_STRUCTURE mydata;

void setup(){
  tlc_initServos();  // Note: this will drop the PWM freqency down to 50Hz.
  //Tlc.init();
  Serial.begin(9600);  
  solenoid.begin(9600);
  ET.begin(details(mydata), &solenoid);
  delay(100);  
}

void loop()
{

  if(ET.receiveData()) 
  {
    for (int i=1; i<8; i++)
    {
      Serial.println(mydata.mux0array[i]);
    }
  }
  /*
  int direction = 1;
  for (int channel = 0; channel < NUM_TLCS * 16; channel += direction) {

    Tlc.clear();

    if (channel == 0) {
      direction = 1;
    } 
    else {
      tlc_setServo(channel - 1, 0);
      //Tlc.set(channel - 1, 1000);
    }


    for(int i = 0; i<numberOfServos; i++){

      for (int angle = 180; angle >= 0; angle-= 1) {
        tlc_setServo(i, angle);
        Tlc.update();
        delay(3);
      }
      for (int angle = 0; angle < 180; angle+= 1) {
        tlc_setServo(i, angle);
        Tlc.update();
        delay(3);
      }

      //delay(300);

    }

    if (channel != NUM_TLCS * 16 - 1) {
      tlc_setServo(channel + 1, 0);
      //Tlc.set(channel + 1, 1000);
    } 
    else {
      direction = -1;
    }

    // Tlc.update() sends the data to the TLCs.  This is when the LEDs will actually change. 
    Tlc.update();

    //delay(75);
  } */
}  //END LOOP










