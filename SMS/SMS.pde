#include <NewSoftSerial.h>  //Include the NewSoftSerial library to send serial commands to the cellular module.
#include <string.h>         //Used for string manipulations

char bytes[160], *cptr, result;
boolean readyBreak, cnmi, parsepdu;  
NewSoftSerial cell(2,3);  //Create a 'fake' serial port. Pin 2 is the Rx pin, pin 3 is the Tx pin.

void setup()
{
  //Initialize serial ports for communication.
  Serial.begin(9600);
  cell.begin(9600);
  bytes[0] = 0;
  cptr = bytes;
  readyBreak = cnmi = parsepdu = false;
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
      else if (strncmp(bytes, "+CMT:",5) == 0 )
      {
        parsepdu = true;
      }
      else if ( strncmp(bytes, "OK",2) == 0 )
      {
        if(true == cnmi)
        {
          cnmi = false;
          Serial.println("at+cmgf=1");
          cell.println("at+cmgf=1");
        }    
      }
      else if(true == parsepdu)
      {
        parsepdu = false;
        /*
        PDU pdu;
        pdu.setpdu(cptr);
        Serial.print(cptr);
        
        if (!pdu.parse())
        {
          Serial.print("PDU parsing failed. Error: ");
          Serial.println(pdu.getError());
          return;
        }
        
        Serial.print("PDU: ");
        Serial.println(pdu.getPDU());
        Serial.print("SMSC: ");
        Serial.println(pdu.getSMSC());
        Serial.print("Sender: ");
        Serial.println(pdu.getNumber());
        Serial.print("Sender Number Type: ");
        Serial.println(pdu.getNumberType());
        Serial.print("Date: ");
        Serial.println(pdu.getDate());
        Serial.print("Time: ");
        Serial.println(pdu.getTime());
        Serial.print("UDH Type: ");
        Serial.println(pdu.getUDHType());
        Serial.print("UDH Data: ");
        Serial.println(pdu.getUDHData());
        Serial.print("Message: ");
        Serial.println(pdu.getMessage());
        */
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
