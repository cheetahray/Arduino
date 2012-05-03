#include <SoftEasyTransfer.h>

/*   For Arduino 1.0 and newer, do this:   */
#include <NewSoftSerial.h>
NewSoftSerial mySerial(2,4);

#define DEBUG
#define packetlen 32
//create object
SoftEasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{  
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  char Buffer[packetlen];
};
//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

void setup()
{
  mySerial.begin(9600);
  ET.begin(details(mydata), &mySerial);
  Serial.begin(9600);
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()) 
  {
    //#ifdef DEBUG
    Serial.println(mydata.Buffer);
    //#endif
    ET.sendData();
    memset(mydata.Buffer, 0, packetlen);
  }
  //you should make this delay shorter then your transmit delay or else messages could be lost
  //delay(100);
}
