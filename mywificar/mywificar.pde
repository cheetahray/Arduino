/*
 * A simple sketch that uses TCP/IP with Motoduino WiFi Shield.
 */
// Please " #define APP_SOCKAPP " in apps-conf.h

#include <WiShield.h>

//Wireless configuration defines ----------------------------------------
#define WIRELESS_MODE_INFRA   1
#define WIRELESS_MODE_ADHOC   2

//Wireless configuration parameters ----------------------------------------
unsigned char local_ip[]       = {192,168,1,199};  // IP address of WiShield
unsigned char gateway_ip[]     = {192,168,1,1};     // router or gateway IP address
unsigned char subnet_mask[]    = {255,255,255,0}; // subnet mask for the local network
char ssid[] = {"MYWIFI"};    // max 32 bytes
unsigned char security_type    = 0;               // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
// WPA/WPA2 passphrase setting
// Example: password is 12345678
const prog_char security_passphrase[] PROGMEM = {"12345678"};   // max 64 characters

// WEP 128-bit keys setting
// Example: if password is ABCDE, the Hex code is 0x41 0x42 0x43 0x44 0x45 
prog_uchar wep_keys[] PROGMEM = {
   0x41, 0x42, 0x43, 0x44, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Key 0
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Key 1
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Key 2
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Key 3
// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
// End of wireless configuration parameters ----------------------------------------

char recvChar;
char sms[8];
char message[32];

const int Motor_E1 = 5; // Pin ? of L298N     
const int Motor_E2 = 6;  // Pin ? of L298N   
const int Motor_M1 = 7;     // Pin ? of L298N
const int Motor_M2 = 8;    // Pin ? of L298N

struct NetworkPackage
{
   int dataLength; 
   char data[32];
};

NetworkPackage  mNetworkPack;  

void setup()
{
   //set up serial communications
   Serial.begin(9600);
   
   //set up global recvChar to indicate nothing received
   recvChar = NULL;
   WiFi.init();
  // set all color leds as output pins
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);
}

void loop()
{
   if(NULL != recvChar) {
//      Serial.print("Received: ");
//      Serial.print("Length=");
//      Serial.println(mNetworkPack.dataLength);
//      Serial.print("data=");
//      Serial.println(mNetworkPack.data);
      
      if(!strcmp(mNetworkPack.data, "forward"))
        forward(0,0);
      else if(!strcmp(mNetworkPack.data, "back"))
        back(0,0);
      if(!strcmp(mNetworkPack.data, "left"))
        left(0,0);
      if(!strcmp(mNetworkPack.data, "right"))
        right(0,0);
      if(!strcmp(mNetworkPack.data, "stop"))
        motorstop(0,0);
        
      //we have handled the last data receive so clear recvChar so that we don't handle the same data again.
      recvChar = NULL;
   }
   
   WiFi.run();
}

void motorstop(byte flag, byte numOfValues)
{
  digitalWrite( Motor_E1, 0);
  digitalWrite( Motor_E2, 0);
  Serial.println("stop : ");

}

/*
 * Whenever app changes value
 * this function will be called
 */
void forward(byte flag, byte numOfValues)
{
//  analogWrite(ForwardLED, 255);
  Serial.println("forward : ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 255);
  
}

/*
 * Whenever the multicolor lamp app changes the green value
 * this function will be called
 */
void back(byte flag, byte numOfValues)
{
 // analogWrite(BackLED, 255);
  Serial.println("back : ");

  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 255);
   
}

/*
 * Whenever the multicolor lamp app changes the blue value
 * this function will be called
 */
void right(byte flag, byte numOfValues)
{
//  analogWrite(RightLED, 255);
  Serial.println("right : ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 0);
  
}

void left(byte flag, byte numOfValues)
{
//  analogWrite(LeftLED, 255);
  Serial.println("left : ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, 255);
  
}

