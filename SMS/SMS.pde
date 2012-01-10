#include <NewSoftSerial.h>  //Include the NewSoftSerial library to send serial commands to the cellular module.
#include <string.h>         //Used for string manipulations

#define ledstr 560
#define smnum 4 

char bytes[280], *pStop, *cptr, result, phoneNum[20], smstext[1120], b[ledstr], temp[3];
boolean readyBreak, cnmi, parsepdu, conti[3], cmgf, cmgd;  
NewSoftSerial cell(2,3);  //Create a 'fake' serial port. Pin 2 is the Rx pin, pin 3 is the Tx pin.
unsigned long myTime;
int gd, howmany;

void transLED(int lenstr)
{
  for(int   i=0;   i < lenstr;   i++)   
  { 
    strncpy(temp,   &(smstext[i*2]),   2); 
    b[i]   =   (unsigned   char)strtol(temp,   &pStop,   16); 
  }
}

void setup()
{
  //Initialize serial ports for communication.
  Serial.begin(9600);
  cell.begin(9600);
  smstext[0] = phoneNum[0] = bytes[0] = temp[2] = 0;
  cptr = bytes;
  readyBreak = cnmi = parsepdu = conti[0] = conti[1] = conti[2] = cmgf = cmgd = false;
  gd = 1;
  howmany = 0;
}

void loop()
{
  if ( cell.available() > 0 )
  {
    result = cell.read();
    Serial.print(result);
    *cptr++ = result;
    if(true == readyBreak && 10 == result)
    {
      *(cptr-2) = 0;
      cptr = bytes;
      if (strncmp(bytes, "+SIND: 4",9) == 0 )
      {
        cnmi = true;
        Serial.println("at+cnmi=2,2");
        cell.println("at+cnmi=2,2");
      }
      else if (strncmp(bytes, "+CMT: ",6) == 0 )
      {
        parsepdu = true;
        char * pch = strtok (bytes+6,",");
        for (int ii = 0; ii < 5; ii++)
        {
          switch(ii)
          {
            case 0:
              if ( 0 == smstext[0] || strncmp(phoneNum, pch, 20) == 0 )
              {
                conti[0] = true;
              }
              else
              {
                conti[0] = false;
              }
              //Serial.println(pch);
              strncpy(phoneNum, pch, 20);
            break;
            case 3:
              if( 0 == smstext[0] || ( millis() - myTime < 30000 ) )
              {
                conti[1] = true;
              }
              else
              {
                conti[1] = false;
              }
              //Serial.println(pch);
              myTime = millis();
            break;              
            case 4:
              if ( strncmp(pch, "134", 3) == 0 )
              {
                conti[2] = true;
              }
              else
              {
                conti[2] = false;
              }
              //Serial.println(pch);
            break;
            default:
              //Serial.println(pch);
            break;
          }
          //Serial.println(pch);
          pch = strtok (NULL, ",");
        }
      }
      else if ( strncmp(bytes, "OK",2) == 0 )
      {
        if(true == cnmi)
        {
          cnmi = false;
          Serial.println("at+cmgf=1");
          cell.println("at+cmgf=1");
          cmgd = true;
        }    
        else if(true == cmgd)
        {
           Serial.print("at+cmgd=");
           Serial.println(gd);
           cell.print("at+cmgd=");
           cell.println(gd);
           gd++;
           if(gd > smnum)
           {
             cmgd = false;
             gd = 1;
           }
        }
      }
      else if ( strncmp(bytes, "+CMS ERROR: ",12) == 0 )
      {
          if(true == cmgd)
          {
             Serial.print("at+cmgd=");
             Serial.println(gd);
             cell.print("at+cmgd=");
             cell.println(gd);
             gd++;
          }
          if(gd > smnum)
          {
            gd = 1;
            cmgd = false;
          }
      }
      else if ( strncmp(bytes, "+CME ERROR: ",12) == 0 )
      {
          if(true == cmgd)
          {
             Serial.print("at+cmgd=");
             Serial.println(gd);
             cell.print("at+cmgd=");
             cell.println(gd);
             gd++;
          }
          if(gd > smnum)
          {
            gd = 1;
            cmgd = false;
          }
      }
      else if(true == parsepdu)
      {
        parsepdu = false;
        strncat(smstext, bytes, 280);
        howmany++;
        if(false == conti[0] || false == conti[1] || false == conti[2] || howmany > smnum)
        {
          Serial.println(smstext);
          //transLED or sendLED?
          cmgd = true;
          Serial.println("AT");
          cell.println("AT");
          smstext[0] = phoneNum[0] = 0;
        }        
      }
    }
    if(13 == result)
    {
      readyBreak = true;
    }
  }

  //If a character is coming from the terminal to the Arduino...
  if(Serial.available() >0)
  {
    result=Serial.read();  //Get the character coming from the terminal
    cell.print(result);    //Send the character to the cellular module.
  }
   
}
