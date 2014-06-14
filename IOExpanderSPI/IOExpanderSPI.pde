#define PIN_DATA_OUT 11 // MOSI 
#define PIN_DATA_IN 12 // MISO 
#define PIN_SPI_CLOCK 13 // SCK 
#define PIN_SLAVE_SELECT 10 // SS 
// Op Code 
#define REG_IODIR 0x00 
#define REG_GPIO 0x09 
byte OpcodeRead = B01000001; 
byte OpcodeWrite = B01000000; 
 
void setup () { 
 Serial.begin(9600); 
 pinMode(PIN_DATA_OUT, OUTPUT); 
 pinMode(PIN_DATA_IN, INPUT); 
 pinMode(PIN_SPI_CLOCK, OUTPUT);
 pinMode(PIN_SLAVE_SELECT, OUTPUT); 
 digitalWrite(PIN_SLAVE_SELECT, HIGH); 
 SPCR = (1<<SPE)| (1<<MSTR); 
 setRegister(OpcodeWrite, REG_IODIR, B00000001); 
 setRegister(OpcodeWrite, REG_GPIO, B00000010); 
} 

void loop() { 
 byte buttonState = 0; 
 buttonState = (getRegister(OpcodeRead, REG_GPIO) & B00000001); 
 if (!buttonState) { 
	 setRegister(OpcodeWrite, REG_GPIO, B00000000); 
	 delay(75); 
	 setRegister(OpcodeWrite, REG_GPIO, B00000010); 
 } 
 delay(75); 
}  

byte getRegister(byte targetDeviceOpcode, byte registerAddress) 
{ 
 byte data; 
 digitalWrite(PIN_SLAVE_SELECT, LOW); 
 spi_transfer(targetDeviceOpcode); 
 spi_transfer(registerAddress); 
 data = spi_transfer(0xFF); 
 digitalWrite(PIN_SLAVE_SELECT, HIGH); 
 return data; 
}
 
void setRegister(byte targetDeviceOpcode, byte registerAddress, byte value) { 
 digitalWrite(PIN_SLAVE_SELECT, LOW); 
 spi_transfer(targetDeviceOpcode); 
 spi_transfer(registerAddress); 
 spi_transfer(value); 
 digitalWrite(PIN_SLAVE_SELECT, HIGH); 
}  

char spi_transfer(volatile char data) 
{ 
 SPDR = data; 
 while (!(SPSR & (1<<SPIF))); 
 return SPDR; 
}
