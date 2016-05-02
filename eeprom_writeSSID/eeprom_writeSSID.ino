#include <EEPROM.h>

char* ssid = "bellclass\0\0\0\0\0\0\0";
char* password = "noisekitchen\0\0\0\0";
int addr = 0;

void setup()
{
  writessid(480,16);
}

void loop()
{
}

void writessid(int sAddr, int len){
    EEPROM.begin(512);
    for (int gg=0; gg < len; gg++)
        EEPROM.write( sAddr+gg, *(ssid+gg) );
    
    sAddr += 16;
    for (int gg=0; gg < len; gg++)
        EEPROM.write( sAddr+gg, *(password+gg) );
    
    EEPROM.commit(); 

}
