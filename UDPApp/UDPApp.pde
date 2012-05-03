/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */
#include <WiShield.h>

#define DEBUG
#define packetlen 32
// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[]    = {192,168,13,167};   // IP address of WiShield
unsigned char gateway_ip[]  = {192,168,13,1};   // router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0}; // subnet mask for the local network
char ssid[]                 = {"NoiseKitchen"};   // max 32 bytes
unsigned char security_type = 2;               // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"NoiseIsFree"};	// max 64 characters

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

char message[packetlen];

int ar[] = {3,4,5,6,7,19,18};

void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
   for( int i=0; i<8; i++) 
        pinMode(ar[i], OUTPUT);   // set the LED on
  
   Serial.begin(9600);
  
   WiFi.init();
}

void loop() {

  if(message[0] != 0)
    {
      #ifdef DEBUG
      Serial.println(message);
      #endif
      for( int i=0; i<8; i++) 
        digitalWrite(ar[i], message[i+16]-'0');   // set the LED on
    
      message[0] = 0;
    }  
	WiFi.run();

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
