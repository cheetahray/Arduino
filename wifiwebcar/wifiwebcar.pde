/*
 * A simple sketch that uses Web Server with Motoduino WiFi Shield.
 */
// Note: Please only define APP_WISERVER in apps-conf.h 
//       

#include <WiServer.h>

const int Motor_E1 = 5; // Pin 5 of Motoduino     
const int Motor_E2 = 6;  // Pin 6 of Motoduino   
const int Motor_M1 = 7;     // Pin 7 of Motoduino
const int Motor_M2 = 8;    // Pin 8 of Motoduino

//1. SPI
//Slave select (SS) : Arduino pin 10 (port B, pin 2)
//Clock (SCK) : Arduino pin 13 (port B, pin 5)
//Master in, slave out (MISO) : Arduino pin 12 (port B, pin 4)
//Master out, slave in (MOSI) : Arduino pin 11 (port B, pin 3)
//2. Interrupt (Uses only one of the following, depending on jumper setting)
//INT0 : Arduino pin 2 (port D, pin 2)
//DIG8 : Arduino pin 8 (port B, pin 0)
//3. Interrupt selection jumper
//Do NOT leave it unconnected, you need select one.
//4. LED Indicator: Arduino pin 9 (port B, pin 1)

// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[]    = {192,168,11,199};   // IP address of WiShield
unsigned char gateway_ip[]  = {192,168,11,1};   // router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0}; // subnet mask for the local network
char ssid[]                 = {"DAC-2F(rear)"};   // max 32 bytes
unsigned char security_type = 2;               // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"yellowsub"};	// max 64 characters

byte sampledata=50;
char link[]="http://motoduino.com/"; //link data

// WEP 128-bit keys
prog_uchar wep_keys[] PROGMEM = { 
	0x61, 0x62, 0x63, 0x64, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 0
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

boolean mainpage()
{
            WiServer.print("<html><head></head>");
          WiServer.print("<body>");
          WiServer.print("<table border= 0>");
          WiServer.print("<tr>");
          WiServer.print("<th>  </th>");
          WiServer.print("<th>");
          WiServer.print("<form  method=get>");
          WiServer.print("<input type=hidden name=V value=F /><br />");
          WiServer.print("<input type=submit value=FORWARD>");
            WiServer.print("</form>");
              WiServer.print("</th><th> </th>");
          WiServer.print("</tr>");
          WiServer.print("<tr><th>");
          WiServer.print("<form  method=get >");
          WiServer.print("<input type=hidden name=V value=L /><br />");
          WiServer.print("<input type=submit value=LEFT>");
          WiServer.print("</form>");
          WiServer.print("</th><th>");
          WiServer.print("<form  method=get >");
          WiServer.print("<input type=hidden name=V value=S /><br />");
          WiServer.print("<input type=submit value=STOP>");
          WiServer.print("</form>");
         WiServer.print("</th><th> ");
          WiServer.print("<form  method=get >");
          WiServer.print("<input type=hidden name=V value=R /><br />");
          WiServer.print("<input type=submit value=RIGHT>");
          WiServer.print("</form>");
          WiServer.print("</th></tr> <tr> <th>  </th> <th> ");
          WiServer.print("<form  method=get >");
          WiServer.print("<input type=hidden name=V value=B /><br />");
          WiServer.print("<input type=submit value=BACKWARD>");
          WiServer.print("</form>");
          WiServer.print(" </th> <th> </th> </tr>");
          WiServer.print("</table>");
          WiServer.print("<br/>");
          WiServer.print("<font color=#888888 size=1>2012 Motoduino Lab.</font><font size=3>");
            WiServer.print("<br /></font><font size=3>http://motoduino.com</font><br />");
          WiServer.print("</body>");
          WiServer.print("</html>");
    
          return true; 
}

boolean  controlpage(char* URL)
{
//    Serial.println(URL);
    if (strcmp(URL, "/") == 0)
    {
          mainpage();  
         return true;
    }
    else
    {
         if(URL[1] == '?')
         {
           if((URL[2] == 'V') && (URL[3] == '='))
           {
              switch(URL[4])
              {
                 case 'F': 
                           forward(0, 0); 
                          break;
                 case 'B': 
                           back(0, 0); 
                          break;
                 case 'L': 
                           left(0, 0); 
                          break;
                 case 'R': 
                           right(0, 0); 
                          break;
                 case 'S': 
                           motorstop(0, 0); 
                          break;
               
              }
             
           }
          mainpage();  
          return true;          
         }      

    }
}

void motorstop(byte flag, byte numOfValues)
{
  digitalWrite( Motor_E1, 0);
  digitalWrite( Motor_E2, 0);
  
  Serial.println("stop : ");
}

void forward(byte flag, byte numOfValues)
{

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 255);

  Serial.println("forward : ");  
}

void back(byte flag, byte numOfValues)
{
  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 255);
  Serial.println("back : ");   
}

void right(byte flag, byte numOfValues)
{
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 255);
  analogWrite( Motor_E2, 0);
  Serial.println("right : ");  
}

void left(byte flag, byte numOfValues)
{
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, 255);
  Serial.println("left : ");  
}

void setup() {
  Serial.begin(9600);
  
  // set all color leds as output pins
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);

  WiServer.init(controlpage);
  
  // Enable Serial output and ask WiServer to generate log messages (optional)
  WiServer.enableVerboseMode(true);
}

void loop(){

  // Run WiServer
  WiServer.server_task();
 
  delay(10);
}

