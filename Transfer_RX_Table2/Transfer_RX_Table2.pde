#include <SoftEasyTransfer.h>

/*   For Arduino 1.0 and newer, do this:   */
#include <NewSoftSerial.h>
NewSoftSerial mySerial(0,1);

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

int shift = 2;
int pos[3] = {8,0,13};
int rnd[3] = {0,0,0};
int last[3] = {0,0,0};
boolean occupied[3] = {false, false, false};

void setup()
{
  memset(mydata.Buffer, 0, packetlen);
  for(int ii = 0; ii < 3 ; ii++)
  {
    pinMode(ii+shift, OUTPUT);  
    occupied[ii] = false;
  }    
  mySerial.begin(9600);
  ET.begin(details(mydata), &mySerial);
  Serial.begin(9600);
}

void raywrite(int pin, int data, int delayy, int pin2, int data2, int delayy2, int pin3, int data3, int delayy3)
{
  if(0 == last[pin-shift] && 1 == data)
  {
      /*
      Serial.print(pin);
      Serial.print(data);
      Serial.println(delayy);
      */
      digitalWrite(pin, data);   // set the LED on
  }
  if(0 == last[pin2-shift] && 1 == data2)
  {
      /*
      Serial.print(pin2);
      Serial.print(data2);
      Serial.println(delayy2);
      */
      digitalWrite(pin2, data2);   // set the LED on
  }
  if(0 == last[pin3-shift] && 1 == data3)
  {
      /*
      Serial.print(pin3);
      Serial.print(data3);
      Serial.println(delayy3);
      */
      digitalWrite(pin3, data3);   // set the LED on
  }
  delay(delayy);
  if(0 == last[pin-shift] && 1 == data)
  {
      digitalWrite(pin, LOW);    // set the LED off
  }
  last[pin-shift] = data;
  delay(delayy2);
  if(0 == last[pin2-shift] && 1 == data2)
  {
      digitalWrite(pin2, LOW);    // set the LED off
  }
  last[pin2-shift] = data2;
  delay(delayy3);
  if(0 == last[pin3-shift] && 1 == data3)
  {
      digitalWrite(pin3, LOW);    // set the LED off
  }
  last[pin3-shift] = data3;
}

void loop()
{
  //check and see if a data packet has come in. 
  if(ET.receiveData()) 
  {
    //#ifdef DEBUG
    //Serial.println(mydata.Buffer);
    for(int ii = 0; ii < 3; ii++)
      rnd[ii] = random(7,9);
    
    int raypin[3];

    for(int ii = 0; ii < 3 ; ii++)
    {
      if(true == occupied[ii])
        continue;
      else if( min( min(rnd[0],rnd[1]), rnd[2]) == rnd[ii])
      {
        occupied[ii] = true;
        raypin[0] = ii;
        break;
      }  
    }    
    
    for(int ii = 0; ii < 3 ; ii++)
    {
      if(true == occupied[ii])
        continue;
      else if( max( max(rnd[0],rnd[1]), rnd[2]) == rnd[ii])
      {
        occupied[ii] = true;
        raypin[2] = ii;
        break;
      }  
    }

    for(int ii = 0; ii < 3 ; ii++)
    {
      if(false == occupied[ii])
      {
        occupied[ii] = true;
        raypin[1] = ii;
        break;
      }  
    }    
    
    raywrite(raypin[0]+shift, mydata.Buffer[pos[raypin[0]]]-'0', rnd[raypin[0]],raypin[1]+shift, mydata.Buffer[pos[raypin[1]]]-'0', rnd[raypin[1]] - rnd[raypin[0]],raypin[2]+shift, mydata.Buffer[pos[raypin[2]]]-'0', rnd[raypin[2]] - rnd[raypin[1]]);   // set the LED on
    
    memset(mydata.Buffer, 0, packetlen);
    for(int ii = 0; ii < 3 ; ii++)
    {
       occupied[ii] = false;
    }    
  }
  
}
