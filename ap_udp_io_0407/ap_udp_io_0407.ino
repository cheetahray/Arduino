#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>

// wifi connection variables
const char* ssid = "dac_public";
const char* password = "dac_public";
const char* ssid_AP = "rayray";
const char* password_AP = "pearl123";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

bool record = false;//錄音模式
bool playSong = false;//撥放模式
int addr, val = 0; //EEPROM
int btn1State, btn2State = 0; //按鈕狀態

void setup() {
  Serial.begin(115200);
  ioPortSetting();//設定IO
  btn1State = digitalRead(D0);
  if (btn1State == HIGH) {
    wifiConnected = connectWifi();
  } else {
    //AP MODE
    Serial.println("HIGH");
    WiFi.softAP(ssid_AP, password_AP);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    wifiConnected = true;
  }
  
  if (wifiConnected) {
      udpConnected = connectUDP();
      //playSong = true;
  }    
}

void loop() {
  recieveData(); //收udp資料
  btn2State = digitalRead(D10);
  if (btn2State == HIGH) {
    digitalWrite(BUILTIN_LED, LOW);
    if (!playSong and !record) playSong = true;
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  if (playSong) readMySong();
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
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
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
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}

void ioPortSetting() {
  pinMode(D0, INPUT);
  //pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, INPUT);
}

//接收UDP資料
void recieveData() {
  if (wifiConnected) {
    if (udpConnected) {
      // if there’s data available, read a packet
      int packetSize = UDP.parsePacket();
      if (packetSize)
      {
        //Serial.print("Received packet of size ");
        //Serial.println(packetSize);
        
        // read the packet into packetBufffer
        UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        //Serial.println(packetBuffer);
        char str = packetBuffer[0];
        switch (str)
        {
          case 'R':
            if (!record) recordStart();
            //Serial.println(packetBuffer);
            break;
          case 'Q':
            if (record) recordEnd();
            //Serial.println(packetBuffer);
            break;
          default:
            int value = atoi(packetBuffer);
            if (record)  writeData(value);
            if (!playSong) playNote(value);
            //Serial.print("value:");
            //Serial.println(value);
            for (int gg = 0; gg < UDP_TX_PACKET_MAX_SIZE; gg++)
            {
              packetBuffer[gg] = 0;
            }
            break;
        }
      }
    }
  }
}

//寫入EEPROM
void writeData(int val) {
  EEPROM.write(addr, val);
  addr = addr + 1;
  //強制結束錄譜
  if (addr == 511) recordEnd();
}
//開始錄譜
void recordStart() {
  Serial.println("");
  Serial.println("Recording.....");
  EEPROM.begin(512);
  record = true;
  playSong = false;
  addr=val=0;
}
//結束錄譜
void recordEnd() {
  record = false;
  EEPROM.write(addr, 255);
  EEPROM.commit();
  addr = 0;
  val = 0;
  Serial.println("");
  Serial.println("Recording Stop");
}

//讀取樂譜資料
void readMySong() {
  playSong = true;
  EEPROM.begin(512);
  val = EEPROM.read(addr);
  playMySong(val);

  addr = addr + 1;

  if (addr == 511 or val == 255) {
    playSong = false;
    addr = val = 0;
  }
}

//撥放樂譜資料
void playMySong(int value) {
  if (value >= 255) { //結束演奏
    playSong = false;
    addr = val = 0;
  } else if (value >= 127) { //彈奏
    Serial.print(addr);
    Serial.print("\t");
    Serial.print(val, DEC);
    Serial.print("\t");
    Serial.print("play: ");
    playNote(value);
    Serial.println();
  } else { //等待
    int waittime;
    if (value >= 111) {
      waittime = 7000 + (value - 109) * 100 ;
    } else if (value >= 95) {
      waittime = 6000 + (value - 94) * 100 ;
    } else if (value >= 79) {
      waittime = 5000 + (value - 78) * 100 ;
    } else if (value >= 63) {
      waittime = 4000 + (value - 63) * 100 ;
    } else if (value >= 47) {
      waittime = 3000 + (value - 46) * 100 ;
    } else if (value >= 31) {
      waittime = 2000 + (value - 31) * 100 ;
    } else if (value >= 15) {
      waittime = 1000 + (value - 15) * 100 ;
    } else {
      waittime = (value+1) * 100 ;
    }
    Serial.print(addr);
    Serial.print("\t");
    Serial.print(val, DEC);
    Serial.print("\t");
    Serial.print("waittime: ");
    Serial.print(waittime);
    Serial.println();
    delay(waittime);
  }
}

void playNote(int value) {
  int a = value - 127;
  char pin;
  switch (a) {
    case 0:
      pin=D2;
      Serial.print("DO ");
      break;
    case 16:
      pin=D3;
      Serial.print("RE ");
      break;
    case 32:
      pin=D4;
      Serial.print("ME ");
      break;
    case 48:
      pin=D5;
      Serial.print("FA ");
      break;
    case 64:
      pin=D6;
      Serial.print("SO ");
      break;
    case 80:
      pin=D7;
      Serial.print("LA ");
      break;
    case 96:
      pin=D8;
      Serial.print("SI ");
      break;
    case 112:
      pin=D9;
      Serial.print("DO2");
      break;
  }
  DigitalOut(pin);
}

void DigitalOut(char notePin) {
  digitalWrite(notePin, HIGH);
  delay(10);
  digitalWrite(notePin, LOW);
}
