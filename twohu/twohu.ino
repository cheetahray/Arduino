#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
//#include <EEPROM.h>
//#include <string.h>
//#include <ESP8266WebServer.h>

//設定機器編號 241~248
const char* num = "243";
//設定類別
char type[] = "drum";

//ESP8266WebServer server(80);
// wifi connection variables
char ssid[] = "bellclass\0\0\0\0\0\0\0";
char password[] = "noisekitchen\0\0\0\0";
IPAddress ip(192, 168, 12, atoi(num));
IPAddress gateway(192, 168, 12, 254);
IPAddress subnet(255, 255, 254, 0);
char ssid_AP[] = "bellclass_\0\0\0\0\0\0";
char password_AP[] = "noisekitchen_\0\0\0";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 6666;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

bool doopen;
bool reopen;
bool miopen;
bool faopen;
bool soopen;
bool laopen;
bool tiopen;
bool DOopen;
long dotime;
long retime;
long mitime;
long fatime;
long sotime;
long latime;
long titime;
long DOtime;
int doduration;
int reduration;
int miduration;
int faduration;
int soduration;
int laduration;
int tiduration;
int DOduration;

char bass[] = "Bass Drum ";
char snare[] = "Snare ";
char midtom[] = "TomTom - Mid ";
char snareside[] = "Snare Side ";

void ioPortSetting();
void readssid(int sAddr, int len);
boolean connectWifi();
boolean connectUDP();
void handleRoot();
void SaveWifi();
void recieveData();
void readMySong();
void writessid(int sAddr, int len);
void playNote(int value, int velocity);
void recordEnd();
void playMySong(int value);

void setup() {
  Serial.begin(115200);
  ioPortSetting(); //設定IO
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  wifiConnected = connectWifi();

  /*
  //AP MODE
    WiFi.mode(WIFI_AP);
    strcat(ssid_AP, num);
    strcat(password_AP, num);
    WiFi.softAP(ssid_AP, password_AP);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.print("ssid: ");
    Serial.println(ssid_AP);
    Serial.print("password: ");
    Serial.println(password_AP);
    Serial.println("HTTP server started");
    wifiConnected = true;
   */

  if (wifiConnected) {
    udpConnected = connectUDP();
  }
}

void loop() {
  if (wifiConnected) {
    recieveData(); //收udp資料
  }
}

// connect to UDP – returns true if successful or false if not
boolean connectUDP() {
  boolean state = false;
  Serial.println("");
  Serial.println("Connecting to UDP");

  if (UDP.begin(localPort) == 1) {
    Serial.println("Connection successful");
    state = true;
  } else {
    Serial.println("Connection failed");
  }
  return state;
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;
  //判斷是否為 bellclass
  if (strcmp(ssid, "bellclass") == 0) {
    WiFi.config(ip, gateway, subnet);
    Serial.println(ip);
  }
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  i = 0;
  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}

void ioPortSetting() {
  pinMode(RX, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, INPUT);
  pinMode(D8, OUTPUT);
}

//接收UDP資料
void recieveData() {
  if (wifiConnected) {
    if (udpConnected) {

      // if there’s data available, read a packet
      int packetSize = UDP.parsePacket();

      if (packetSize) {
        //char raybuf[8];
        //Serial.print("Received packet of size ");
        //Serial.println(packetSize);
        // read the packet into packetBufffer
        UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        //sprintf(raybuf, "%d", packetBuffer[1]);
        //Serial.println(raybuf);
        int mydu = (packetBuffer[3] << 8) + packetBuffer[2];
        //Serial.println(mydu); 
        playNote(packetBuffer[0], mydu);
      }
      
      if(doopen == true && millis() - dotime > doduration)
      {
          doopen = false;
          //Serial.print(bass);
          //Serial.println("Down");
          digitalWrite(D0, LOW);
      }
      if(reopen == true && millis() - retime > reduration)
      {
          reopen = false;
          //Serial.print(snare);
          //Serial.println("1 Down");
          digitalWrite(D1, LOW);
      }      
      if(miopen == true && millis() - mitime > miduration)
      {
          miopen = false;
          //Serial.print(snareside);
          //Serial.println("Down");
          digitalWrite(D2, LOW);
      }
      if(faopen == true && millis() - fatime > faduration)
      {
          faopen = false;
          //Serial.println("Down");
          digitalWrite(D3, LOW);
      }
      if(soopen == true && millis() - sotime > soduration)
      {
          soopen = false;
          //Serial.print(snare);
          //Serial.println("2 Down");
          digitalWrite(D4, LOW);
      }
      if(laopen == true && millis() - latime > laduration)
      {
          laopen = false;
          //Serial.print(midtom);
          //Serial.println("Down");
          digitalWrite(D5, LOW);
      }
      if(tiopen == true && millis() - titime > tiduration)
      {
          tiopen = false;
          //Serial.println("Down");
          digitalWrite(D6, LOW);
      }
      if(DOopen == true && millis() - DOtime > DOduration)
      {
          DOopen = false;
          //Serial.println("Down");
          digitalWrite(D8, LOW);
      }
    }
  }
}

//音符敲擊
void playNote(int value, int velocity) {
  char pin;
  bool upup = false;
  switch (value) {
    case 127:
      pin = D0;
      //Serial.print(bass);
      dotime = millis();
      doduration = velocity;
      doopen = true;
      upup = true;
      break;
    case 143:
      if(reopen == false)
      {
        pin = D1;
        //Serial.print(snare);
        //Serial.print("1 ");
        retime = millis();
        reduration = velocity;
        reopen = true;
      }
      /*
      else if(soopen == false)
      {
        pin = D4;
        Serial.print(snare);
        Serial.print("2 ");
        sotime = millis();
        soduration = velocity;
        soopen = true;
      }
      */
      upup = true;
      break;
    case 159:
      pin = D2;
      //Serial.print(snareside);
      mitime = millis();
      miduration = velocity;
      miopen = true;
      upup = true;
      break;
    case 175:
      pin = D3;
      //Serial.print("FA ");
      fatime = millis();
      faduration = velocity;
      faopen = true;
      upup = true;
      break;
    case 191:
      pin = D4;
      //Serial.print("SO ");
      sotime = millis();
      soduration = velocity;
      soopen = true;
      upup = true;
      break;
    case 207:
      pin = D5;
      //Serial.print(midtom);
      latime = millis();
      laduration = velocity;
      laopen = true;
      upup = true;
      break;
    case 223:
      pin = D6;
      //Serial.print("SI ");
      titime = millis();
      tiduration = velocity;
      tiopen = true;
      upup = true;
      break;
    case 239:
      pin = D8;
      //Serial.print("DO2 ");
      DOtime = millis();
      DOduration = velocity;
      DOopen = true;
      upup = true;
      break;
  }
  if(true == upup)
  {
      //Serial.println("UP");
      digitalWrite(pin, HIGH);
  }
}

void DigitalOut(char notePin) {
  digitalWrite(notePin, HIGH);
  delay(100);
  digitalWrite(notePin, LOW);
}
