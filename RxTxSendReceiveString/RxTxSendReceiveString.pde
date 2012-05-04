/*
  UDPSendReceive.pde:
 This sketch receives UDP message strings, prints them to the serial port
 and sends an "acknowledge" string back to the sender
 
 A Processing sketch is included at the end of file that can be used to send 
 and received messages for testing with a computer.
 
 created 21 Aug 2010
 by Michael Margolis
 
 This code is in the public domain.
 */
#include <SPI.h>
#include <SoftEasyTransfer.h>

/*   For Arduino 1.0 and newer, do this:   */
#include <NewSoftSerial.h>

NewSoftSerial mySerial(14, 16);

#define base 20
#define DEBUG
#define packetlen 32
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  char  Buffer[packetlen];
};
SEND_DATA_STRUCTURE mydata;

const int analogInPin = A0, onoffInPin = A2;
const int motorPWM = 10;
int dir = 9;

int outputVal = 0, lastVal = 0;
int action = 5;

int count, delayy;
int raypin[30] ={29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
               //30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1
               
boolean whitebreak;
               
void setup() {
  // start the Ethernet and UDP:
  whitebreak = false;
  count = delayy = 0;
  for (int i=0; i < 30; i++) 
  { 
    pinMode(i+base, INPUT);
  }
  pinMode(dir, OUTPUT);
  pinMode(motorPWM, OUTPUT);
  mySerial.begin(9600);
  //start the library, pass in the data details and the name of the serial port.
  ET.begin(details(mydata), &mySerial);
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0 && false == whitebreak) 
  {
    // read the incoming byte:
    mydata.Buffer[count] = Serial.read();
    if(' ' == mydata.Buffer[count])
    {
      mydata.Buffer[count] = 0;
      if(count < 10)
      {
         delayy = atoi(mydata.Buffer);
         //Serial.println(delayy);
         count = -1;
      }
      else
      {
         for(int ii = 15; ii < 30; ii++)
         {
           mydata.Buffer[ii] = '0';
         }
         whitebreak = true;
      }
    }
    count++;
    delay(2);
  }
  else if (outputVal != lastVal) 
  {
      digitalWrite(dir, HIGH);
      analogWrite(motorPWM, outputVal);
      lastVal = outputVal;
  } 
  else if( 0 != mydata.Buffer[packetlen >> 1] )
  {
    //Serial.println( mydata.Buffer );
    ET.sendData();
    // if there's data available, read a packet
    if(true == whitebreak && delayy % 50 == 0)
    {
      delay(delayy>>1);
      memset(mydata.Buffer,'0',30);
      ET.sendData();
      delay(delayy>>1);  
    }
    memset(mydata.Buffer,0,packetlen);
    count = 0;
    whitebreak = false;
  }
  else if( map( analogRead(onoffInPin) , 0, 1023, 0, 254) > action )
  {
      int sensorVal = analogRead(analogInPin);
      outputVal = map(sensorVal, 0, 1023, 0, 254);
      if( outputVal < action)
      {
        analogWrite(motorPWM, 0);
        memset(mydata.Buffer,'0',30);
        //Serial.println( mydata.Buffer );
        delayy = 1000;
      }
      else
      {
        for (int i=0; i < 30; i++) 
        {
          int sensorValue = digitalRead(i+base);
          mydata.Buffer[raypin[i]] = sensorValue + '0';
        }
        delayy = 0;
      }
  }  
  else
  {
    analogWrite(motorPWM, 0);
    memset(mydata.Buffer,'0',30);
    //Serial.println( mydata.Buffer );
    delayy = 1000; 
  }
}


/*
  Processing sketch to run with this example
 =====================================================
 
 // Processing UDP example to send and receive string data from Arduino 
 // press any key to send the "Hello Arduino" message
 
 
 import hypermedia.net.*;
 
 UDP udp;  // define the UDP object
 
 
 void setup() {
 udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000
 //udp.log( true ); 		// <-- printout the connection activity
 udp.listen( true );           // and wait for incoming message  
 }
 
 void draw()
 {
 }
 
 void keyPressed() {
 String ip       = "192.168.1.177";	// the remote IP address
 int port        = 8888;		// the destination port
 
 udp.send("Hello World", ip, port );   // the message to send
 
 }
 
 void receive( byte[] data ) { 			// <-- default handler
 //void receive( byte[] data, String ip, int port ) {	// <-- extended handler
 
 for(int i=0; i < data.length; i++) 
 print(char(data[i]));  
 println();   
 }
 */


