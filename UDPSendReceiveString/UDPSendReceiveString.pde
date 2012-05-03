/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <Udp.h> 

#define packetlen 32
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

// the next two variables are set when a packet is received
byte remoteIp[4] = {255,255,255,255};        // holds received packet's originating IP
uint16_t remotePort = 12344;
// buffers for receiving and sending data
//char  ReplyBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  NoiseBuffer[packetlen];// = "Hello";       // a string to send back
//char  RequestBuffer[packetlen];// = "010110011001100110011001100110";
int   count, packetSize;
void setup() 
{
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  byte ip[] = { 192,168,13,177 };
  Ethernet.begin(mac,ip);
  Udp.begin(12345);
  count = 0;
  Serial.begin(9600);
  for (int i=0; i < 30; i++) 
  { 
    pinMode(i+24, INPUT);
  }
}

void loop() 
{
  if (Serial.available() > 0) 
  { 
   // read the incoming byte:
    NoiseBuffer[count++] = Serial.read();
    delay(10);
  }/*
  else if( RequestBuffer[0] != 0 )
  {
    Serial.println("Ray3");
    Serial.println( RequestBuffer );
    Udp.sendPacket( RequestBuffer, remoteIp, remotePort);
    // if there's data available, read a packet
    memset(RequestBuffer,0,packetlen);
    count = 0;
    delay(990);
  }*/
  else if( NoiseBuffer[0] != 0 )
  {
    Serial.println( NoiseBuffer );
    Udp.clear();
    Udp.sendPacket( NoiseBuffer, remoteIp, remotePort);
    // if there's data available, read a packet
    memset(NoiseBuffer,0,packetlen);
    delay(100);
  }/*
  else if( packetSize = Udp.available() )
  {
    Serial.println("Ray4");
    packetSize = packetSize - 8;      // subtract the 8 byte header
    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    // read the packet into packetBufffer and get the senders IP addr and port number
    Udp.readPacket(ReplyBuffer,UDP_TX_PACKET_MAX_SIZE, remoteIp, remotePort);
    Serial.println("Contents:");
    Serial.println(ReplyBuffer);
  }*/
  else
  {
    Serial.println("Ray5");
    for (int i=0; i < 30; i++) 
    {
      int sensorValue = digitalRead(i+24);
      NoiseBuffer[i] = sensorValue + '0';
    }
    NoiseBuffer[30] = 0;
    delay(100);
  }
 
 }



