//Mux_Shield_DigitalOut_Example
//http://mayhewlabs.com/arduino-mux-shield
#include <SoftEasyTransfer.h>
#include <NewSoftSerial.h>

NewSoftSerial solenoid(9, 10);
/*
This example shows how to output high or low on all 48 pins.  To use the analog pins as digital, we use
 pin numbers 14-16 (instead of analog numbers 0-2). 
 
 To simplify this code further, one might use nested for loops or function calls.
 */

//Give convenient names to the control pins
#define CONTROL0 5    //MUX control pin 0 (S3 is connected to Arduino pin 2)
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{  
    float mux0array[8];
};

SEND_DATA_STRUCTURE mydata;

const int ana3 = A3;
const int ana4 = A4;
const int ana5 = A5;

int valA3 = 0;
int valA4 = 0;
int valA5 = 0;

int choose = 1;
int times = 90;

void setup()
{
  //Set MUX control pins to output
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  Serial.begin(9600);
  solenoid.begin(9600);
  ET.begin(details(mydata), &solenoid);
}


void loop()
{
  if(ET.receiveData()) 
  {
    for (int i=1; i<8; i++)
    {
      Serial.print(mydata.mux0array[i]);
    }
  }
  /*
  Serial.print("analog3 = ");
  Serial.print(valA3);
  Serial.print(" analog4 = ");
  Serial.print(valA4);
  Serial.print(" analog5 = ");
  Serial.println(valA5);
  delay(200);
  
  for (int i=1; i<=15; i++){
  mux1(i,20,100);
  }
  for (int i=1; i<=15; i++){
  mux2(i,20,100);
  }
  for (int i=1; i<=15; i++){
  mux3(i,20,100);
  }
  */
  //delay(2000);
  
}

void mux1(int i,int HighTime,int LowTime) { //藍色
  pinMode(14, OUTPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);

  digitalWrite(CONTROL0, (i&15)>>3); //S3
  digitalWrite(CONTROL1, (i&7)>>2);  //S2
  digitalWrite(CONTROL2, (i&3)>>1);  //S1
  digitalWrite(CONTROL3, (i&1));     //S0

  digitalWrite(14, HIGH);
  delay(HighTime);
  digitalWrite(14, LOW);
  delay(LowTime);
}

void mux2(int i,int HighTime,int LowTime) {  //黃色
  pinMode(14, INPUT);
  pinMode(15, OUTPUT);
  pinMode(16, INPUT);

  digitalWrite(CONTROL0, (i&15)>>3); //S3
  digitalWrite(CONTROL1, (i&7)>>2);  //S2
  digitalWrite(CONTROL2, (i&3)>>1);  //S1
  digitalWrite(CONTROL3, (i&1));     //S0

  digitalWrite(15, HIGH);
  delay(HighTime);
  digitalWrite(15, LOW);
  delay(LowTime);
}

void mux3(int i,int HighTime,int LowTime) { //白色
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, OUTPUT);

  digitalWrite(CONTROL0, (i&15)>>3); //S3
  digitalWrite(CONTROL1, (i&7)>>2);  //S2
  digitalWrite(CONTROL2, (i&3)>>1);  //S1
  digitalWrite(CONTROL3, (i&1));     //S0

  digitalWrite(16, HIGH);
  delay(HighTime);
  digitalWrite(16, LOW);
  delay(LowTime);
}





