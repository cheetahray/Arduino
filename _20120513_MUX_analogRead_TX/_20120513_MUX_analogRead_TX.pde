#include <SoftEasyTransfer.h>
#include <NewSoftSerial.h>

NewSoftSerial solenoid(11, 12);


#define CONTROL0 5    
#define CONTROL1 4
#define CONTROL2 3
#define CONTROL3 2

#define VOLTS_PER_UNIT    .0049F        // (.0049 for 10 bit A-D)
float volts;
float proxSens;
float cm;

SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{  
    float    mux0array[8];
};

SEND_DATA_STRUCTURE mydata;


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
  
  //This for loop is used to scroll through and store the 16 inputs on the FIRST multiplexer
  for (int i=1; i<8; i++)
  {
    //The following 4 commands set the correct logic for the control pins to select the desired input
    //See the Arduino Bitwise AND Reference: http://www.arduino.cc/en/Reference/BitwiseAnd
    //See the Aruino Bitshift Reference: http://www.arduino.cc/en/Reference/Bitshift
    digitalWrite(CONTROL0, (i&15)>>3); 
    digitalWrite(CONTROL1, (i&7)>>2);  
    digitalWrite(CONTROL2, (i&3)>>1);  
    digitalWrite(CONTROL3, (i&1));     

    proxSens = analogRead(0);
    volts = (float)proxSens * VOLTS_PER_UNIT; // ("proxSens" is from analog read)
    //inches = 23.897 * pow(volts,-1.1907); //calc inches using "power" trend line from Excel
    mydata.mux0array[i] = 60.495 * pow(volts,-1.1904); 
  
  }

  //The following lines are for printing out results of array0
  Serial.print("mux0array: ");
  for (int i=1; i<8; i++)
  {
    Serial.print(mydata.mux0array[i]);
    Serial.print("-");
  }
  Serial.println();  //line feed
  ET.sendData();
  delay(100);
}

