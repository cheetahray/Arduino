/* Welcome to DmxSimple. This library allows you to control DMX stage and
** architectural lighting and visual effects easily from Arduino. DmxSimple
** is compatible with the Tinker.it! DMX shield and all known DIY Arduino
** DMX control circuits.
**
** DmxSimple is available from: http://code.google.com/p/tinkerit/
** Help and support: http://groups.google.com/group/dmxsimple       */

/* To use DmxSimple, you will need the following line. Arduino will
** auto-insert it if you select Sketch > Import Library > DmxSimple. */

#include <DmxSimple.h>

int value = 0;
int channel;
int delayTime = 10;

void setup() {
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(2);
  Serial.begin(9600);
  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(4);
  DmxSimple.write(1, 255);
  DmxSimple.write(2, 255);
  DmxSimple.write(3, 255);
  DmxSimple.write(4, 255);
}

void loop() {
  int c;

  while(!Serial.available())
    ;
  c = Serial.read();
  if ((c>='0') && (c<='9')) 
  {
    value = 10*value + c - '0';
  } 
  else 
  {
    if (c=='t')
    {
      delayTime = value;
    }
    else if (c=='c') 
    {
      channel = value;
    }
    else if (c=='s')
      DmxSimple.write(1, 0);
    else if (c=='o')
    {
      DmxSimple.write(1, 255);
    }
    else if (c=='w') 
    {
      DmxSimple.write(channel, value);
      timeDelay();
    }
    value = 0;
  }
}

void timeDelay() {
  int brightness;
  delayTime = ( (delayTime >> 1) / 235 );
  /* Simple loop to ramp up brightness */
  for (brightness = 15; brightness <= 255; brightness++) {
    
    /* Update DMX channel 1 to new brightness */
    DmxSimple.write(1, brightness);
    
    /* Small delay to slow down the ramping */
    delay(delayTime);
  }
  for (brightness = 255; brightness >= 15; brightness--) {
    
    /* Update DMX channel 1 to new brightness */
    DmxSimple.write(1, brightness);
    
    /* Small delay to slow down the ramping */
    delay(delayTime);
  }
}
