#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>
#include <string.h>
#include <ESP8266WebServer.h>

//設定機器編號 1~100
const char* num = "1";
//設定類別
char type[] = "bell";

ESP8266WebServer server(80);
// wifi connection variables
char* ssid = "bellclass\0\0\0\0\0\0\0";
char* password = "noisekitchen\0\0\0\0";
IPAddress ip(192, 168, 13, atoi(num));
IPAddress gateway(192, 168, 13, 254);
IPAddress subnet(255, 255, 255, 0);
char ssid_AP[] = "bellclass_\0\0\0\0\0\0";
char password_AP[] = "noisekitchen_\0\0\0";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

bool ensemble = false; //合奏模式
bool record = false; //錄音模式
bool playSong = false; //撥放模式
int addr, val = 0; //EEPROM
int btn1State, btn2State = 0; //按鈕狀態

void setup() {
	Serial.begin(115200);
	ioPortSetting(); //設定IO
	btn1State = digitalRead(D7);
	WiFi.disconnect();
	WiFi.softAPdisconnect();
  
  if (btn1State == HIGH) {
    //WIFI MODE
	WiFi.mode(WIFI_AP_STA);
    //ssid = "bellclass\0\0\0\0\0\0\0";
    //password = "noisekitchen\0\0\0\0";
    readssid(480, 16);
    wifiConnected = connectWifi();
  } else {
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
	}

	if (wifiConnected) {
		udpConnected = connectUDP();
	}

	server.on("/", handleRoot);
	server.on("/set", SaveWifi);
	server.begin();
}

void loop() {
	if (wifiConnected) {
		recieveData(); //收udp資料
		if (false) { //(!playSong) {
			btn2State = digitalRead(RX);
			if (btn2State == HIGH) {
				//Serial.println(btn2State);
				if (!playSong and !record and !ensemble)
					playSong = true;
			} else {
				//Serial.print(btn2State);
				//Serial.print(" ");
			}
		} else if (false)
			readMySong();
		//delay(10);
	}
	server.handleClient();
}

void handleRoot() {
	char temp[] =
			"<html> \
<head> \
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' /> \
<title>wifi</title> \
</head> \
<body bgcolor='#666666' text='#FFFFFF'> \
<form name='form1' method='post' action='http://192.168.4.1/set'> \
<p> \
<label for='wifi' style='font-size:28px'>Wifi&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</label> \
<input type='text' name='wifi' id='wifi'  maxlength='16'> \
</p> \
<p> \
<label for='passwd'  style='font-size:28px'>Password&nbsp;&nbsp;</label> \
<input type='text' name='passwd' id='passwd' maxlength='16'> \
</p> \
<p style='margin-top:25px'> \
<input type='submit' style='font-weight: bold;font-size:24px; color: #FFF; background-color: #79B53D; border:5px ridge' name='send' id='send' value='Set'> \
</p> \
</form> \
</body> \
</html>";
	server.send(200, "text/html", temp);
}

void SaveWifi() {

	for (int gg = 0; gg < 16; gg++) {
		*(ssid + gg) = 0;
		*(password + gg) = 0;
	}

	strncpy(ssid, server.arg(0).c_str(), 16);
	strncpy(password, server.arg(1).c_str(), 16);

	writessid(480, 16);

	server.send(200, "text/html",
			"<html> \
<head> \
<meta http-equiv='Content-Type' content='text/html; charset=utf-8' /> \
<title>wifi</title> \
</head> \
<body bgcolor='#666666' text='#FFFFFF'> \
<p style='font-size:28px'>Set Wifi already.</p> \
</body> \
</html> \
");

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
		//Serial.println(ip);
	}
	WiFi.begin(ssid, password);
	Serial.println("");
	Serial.println("Connecting to WiFi");

	// Wait for connection
	Serial.print("Connecting");
	while (WiFi.status() != WL_CONNECTED) {
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid, password);
		delay(500);
		Serial.print(".");
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
				//Serial.print("Received packet of size ");
				//Serial.println(packetSize);
				// read the packet into packetBufffer
				UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

				String str;
				for (int i = 0; i < packetSize; i++) {
					str += packetBuffer[i];
				}
				//Serial.println(str);

				if (str == "249 3") {
					if (!ensemble) {
						if (record)
							recordEnd();
						ensemble = true;
						Serial.println("Announce Start!");
					}
				} else if (str == "249 2") {
					if (ensemble) {
						ensemble = false;
						Serial.println("Announce End!");
					}
				} else if (str == "R") {        //錄音模式
					if (!ensemble and !record)
						recordStart();
					//Serial.println(packetBuffer);
				} else if (str == "Q") {        //結束錄音
					if (record)
						recordEnd();
					//Serial.println(packetBuffer);
				} else if (str == "WHO") {
					//Serial.println("WHO");
					UDP.beginPacket(UDP.remoteIP(), localPort);
					UDP.write(type);
					UDP.endPacket();
				} else {
					int value = atoi(packetBuffer);
					if (record)
						writeData(value);
					if (!playSong)
						playNote(value);
					//Serial.print("value:");
					//Serial.println(value);
				}

				for (int gg = 0; gg < UDP_TX_PACKET_MAX_SIZE; gg++) {
					packetBuffer[gg] = 0;
				}
			}
		}
	}
}

//將樂譜寫入EEPROM
void writeData(int val) {
	EEPROM.write(addr, val);
	addr = addr + 1;
	//強制結束錄譜
	if (addr == 479)
		recordEnd();
}
//開始錄譜
void recordStart() {
	Serial.println("");
	Serial.println("Recording.....");
	EEPROM.begin(512);
	record = true;
	playSong = false;
	addr = val = 0;
	writeData(0);
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
//讀取wifiAP帳密
void readssid(int sAddr, int len) {
	EEPROM.begin(512);
	for (int gg = 0; gg < len; gg++) {
		val = EEPROM.read(sAddr);
		sAddr++;
		*(ssid + gg) = val;
	}
	for (int gg = 0; gg < len; gg++) {
		val = EEPROM.read(sAddr);
		sAddr++;
		*(password + gg) = val;
	}
	Serial.println(ssid);
	Serial.println(password);
}
//寫入wifiAP帳密
void writessid(int sAddr, int len) {
	EEPROM.begin(512);
	for (int gg = 0; gg < len; gg++)
		EEPROM.write(sAddr + gg, *(ssid + gg));

	sAddr += 16;
	for (int gg = 0; gg < len; gg++)
		EEPROM.write(sAddr + gg, *(password + gg));

	EEPROM.commit();

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
			waittime = 7000 + (value - 111) * 100;
		} else if (value >= 95) {
			waittime = 6000 + (value - 95) * 100;
		} else if (value >= 79) {
			waittime = 5000 + (value - 79) * 100;
		} else if (value >= 63) {
			waittime = 4000 + (value - 63) * 100;
		} else if (value >= 47) {
			waittime = 3000 + (value - 47) * 100;
		} else if (value >= 31) {
			waittime = 2000 + (value - 31) * 100;
		} else if (value >= 15) {
			waittime = 1000 + (value - 15) * 100;
		} else {
			waittime = value * 100;
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
//音符敲擊
void playNote(int value) {
	int a = value - 127;
	if (a >= 0) {
		char pin;
		switch (a) {
		case 0:
			pin = D0;
			Serial.print("DO ");
			break;
		case 16:
			pin = D1;
			Serial.print("RE ");
			break;
		case 32:
			pin = D2;
			Serial.print("ME ");
			break;
		case 48:
			pin = D3;
			Serial.print("FA ");
			break;
		case 64:
			pin = D4;
			Serial.print("SO ");
			break;
		case 80:
			pin = D5;
			Serial.print("LA ");
			break;
		case 96:
			pin = D6;
			Serial.print("SI ");
			break;
		case 112:
			pin = D8;
			Serial.print("DO2 ");
			break;
		}
		DigitalOut(pin);
	}
}

void DigitalOut(char notePin) {
	digitalWrite(notePin, HIGH);
	delay(20);
	digitalWrite(notePin, LOW);
}
