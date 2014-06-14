#define CS_PIN 10
#define CLOCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12

void setup()
{
	Serial.begin(9600);
	pinMode(CS_PIN, OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(MOSI_PIN, OUTPUT);
	pinMode(MISO_PIN, INPUT);	
}

void loop()
{
	float val = readADC(0);
	Serial.println(val);
	Serial.println((val*5.0)/1024);
	delay(500);	
}

int readADC(int adcnum)
{
	digitalWrite(CS_PIN, HIGH);
	digitalWrite(CLOCK_PIN, LOW);
	digitalWrite(CS_PIN,LOW);
	int commandout = adcnum;
	commandout |= 0x18;
	commandout <<= 3;
	for(int i=0; i<5; i++)
	{
		if (commandout & 0x80)
			digitalWrite(MOSI_PIN, HIGH);
		else
			digitalWrite(MOSI_PIN, LOW);
		commandout <<= 1;
		digitalWrite(CLOCK_PIN, HIGH);
		digitalWrite(CLOCK_PIN, LOW);		
	}
	int adcout = 0;
	for(int i=0; i<12; i++)
	{
		digitalWrite(CLOCK_PIN, HIGH);
		digitalWrite(CLOCK_PIN, LOW);
		adcout <<= 1;
		if(digitalRead(MISO_PIN))
			 adcout |= 0x1;
	}
	digitalWrite(CS_PIN, HIGH);
	adcout >>= 1;
	return adcout;
}
