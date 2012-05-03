#include <SoftEasyTransfer.h>

/*   For Arduino 1.0 and newer, do this:   */
#include <NewSoftSerial.h>
NewSoftSerial mySerial(9,10);

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
int ar[] = {
  3,4,5,6,7,19,18};

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  mySerial.begin(9600);
  ET.begin(details(mydata), &mySerial);
  Serial.begin(9600);

  for(int i = 0; i < 7; i++)
    pinMode(ar[i], OUTPUT); //OUTPUT的pin腳為array的數列

}

void loop() 
{

  if(ET.receiveData()) 
  {
#ifdef DEBUG
    Serial.println(mydata.Buffer);
#endif
    //ET.sendData();

    for( int i=0; i<7; i++) 
      digitalWrite(ar[i], mydata.Buffer[i+15]-'0');   // set the LED on

    memset(mydata.Buffer, 0, packetlen);
  }  

  /*
  int rnd1 = random(7);
   int rnd = ar[rnd1];
   int rnd2 = random(1,4)*200;
   for( int i=0; i<8; i++) {
   digitalWrite(ar[i], HIGH);   // set the LED on
   delay(rnd2);
   digitalWrite(ar[i], LOW);   // set the LED on
   delay(rnd2);
   }
   
   
   digitalWrite(rnd, HIGH);   // set the LED on
   delay(random(2)*100);              // wait for a second
   digitalWrite(rnd, LOW);    // set the LED off
   delay(random(2)*500);              // wait for a second
   */
}

