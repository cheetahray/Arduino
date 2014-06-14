#include <SPI.h>
#define CHANNEL_A false
#define CHANNEL_B true
#define GAIN_LOW false
#define GAIN_HIGH true
boolean gainA;
boolean gainB;
boolean shutdownA;
boolean shutdownB;
unsigned int cspin = 10;

void setup()
{
	begin();
	setGain(CHANNEL_A, GAIN_HIGH);
	shutdown(CHANNEL_A,false);
	shutdown(CHANNEL_B,true);	
}

void loop()
{
	static unsigned int volts;
	setVoltage(CHANNEL_A, volts&0x0fff);
	volts += 100;	
}

void begin()
{
	shutdownA = false;
	shutdownB = false;
	gainA = false;
	gainB = false;
	pinMode(cspin, OUTPUT);
	digitalWrite(cspin, HIGH);
	SPI.begin();
}

void setGain(bool chan, bool gain)
{
	if(chan == CHANNEL_A)
	{
		gainA = gain;
	}
	else
	{
		gainB = gain;
	}
}

void shutdown(bool chan, bool sd)
{
	if(chan == CHANNEL_A)
	{
		shutdownA = sd;
	}
	else
	{
		shutdownB = sd;
	}
}

void setVoltage(bool channel, unsigned int mv)
{
	unsigned int command;
	if(channel == CHANNEL_A)
	{
		command = 0x0000;
		command |= shutdownA ? 0x0000:0x1000;
		command |= gainA ? 0x0000:0x2000;
		command |= (mv & 0x0FFF);
		SPI.setDataMode(SPI_MODE0);
		digitalWrite(cspin,LOW);
		SPI.transfer(command >> 8);
		SPI.transfer(command & 0xFF);
		digitalWrite(cspin, HIGH);
	}
	else
	{
		command = 0x8000;
		command |= shutdownB ? 0x0000:0x1000;
		command |= gainB ? 0x0000:0x2000;
		command |= (mv & 0x0FFF);
		SPI.setDataMode(SPI_MODE0);
		digitalWrite(cspin, LOW);
		SPI.transfer(command >> 8);
		SPI.transfer(command & 0xFF);
		digitalWrite(cspin, HIGH);
	}
}	
