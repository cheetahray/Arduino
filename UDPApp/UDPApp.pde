/*
 * UDP endpoint
 *
 * A simple UDP endpoint example using the WiShield 1.0
 */

#include <WiShield.h>
#define packetlen 32
// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[]    = {192,168,2,67};   // IP address of WiShield
unsigned char gateway_ip[]  = {192,168,2,1};   // router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0}; // subnet mask for the local network
char ssid[]                 = {"DAC-2F(Workshop)"};   // max 32 bytes
unsigned char security_type = 2;               // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"yellowsub"};	// max 64 characters

// WEP 128-bit keys
prog_uchar wep_keys[] PROGMEM = { 
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
};

// setup the wireless mode; infrastructure - connect to AP; adhoc - connect to another WiFi device
#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
// End of wireless configuration parameters ----------------------------------------
const int Motor_E1 = 5; // Pin ? of L298N     
const int Motor_E2 = 6;  // Pin ? of L298N   
const int Motor_M1 = 7;     // Pin ? of L298N
const int Motor_M2 = 8;    // Pin ? of L298N
char message[packetlen];

void setup()
{
	//set up serial communications
   Serial.begin(9600);
   WiFi.init();
   pinMode(Motor_M1, OUTPUT);
   pinMode(Motor_M2, OUTPUT);
}

void loop()
{
  if(message[0] != 0)
    {
      Serial.print(message);
      
      if(!strncmp(message, "forward", packetlen))
        forward(0,0);
      else if(!strncmp(message, "back", packetlen))
        back(0,0);
      else if(!strncmp(message, "left", packetlen))
        left(0,0);
      else if(!strncmp(message, "right", packetlen))
        right(0,0);
      else if(!strncmp(message, "stop", packetlen))
        motorstop(0,0);
    
      message[0] = 0;
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
