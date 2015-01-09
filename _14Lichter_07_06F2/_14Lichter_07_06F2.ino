/*
 //Matti Isan Blind
 //
 //LB Sept-2014
 //
 //
 //
 //"14 Lichter"
 */


//global variables:
boolean debugLed = true;
const int ledPin13 = 13; // the pin that the LED is attached to
boolean debugSerial = false;


//all the main outs
//mega has a lot of tx/rx pins that should be avoided to allow clean comm for serial-port
const int outPins[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 22, 23, 24};//see that it matches outs of mega
int outPinsAll[] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 22, 23, 24, 14, 15};//see that it matches outs of mega
/*
Erklärung:
 //
 Pins Arduino Hardware:
 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 22, 23, 24,     xbee
 Pinnummern im Array zählen einfach hoch inklusive 0:
 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13,     14, 15,
 //
 (Ist für Leuchte zum ansprechen, wie Menschen zählen:
 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,     15, 16,)
 */
const int outPinsLenght = (sizeof(outPins) / sizeof(int));
const int outPinsAllLenght = outPinsLenght + 2; //alle zaehl 2 dazu wegen 2 externen an xbee
unsigned long outPinsAllTimeStamp[outPinsAllLenght];
unsigned int outPinsAllTimeInterval[outPinsAllLenght];
boolean outPinsAllState[outPinsAllLenght];


unsigned long difftime, ivaltime, currentMillis = 0; //variable to hold milliseconds since start/power of arduino till when measured
unsigned long currentMillisLast = currentMillis; //variable to hold milliseconds since start/power of arduino till when measured



void setup() {  // put your setup code here, to run once:
  Serial.begin(9600);// initialize serial communication
  //Serial.flush();

  if(debugLed){
    // initialize the LED13 pin as an output:
    pinMode(ledPin13, OUTPUT);
    digitalWrite(ledPin13, LOW);
  }


  for (int i = 0; i < outPinsLenght; i++) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }


  for (int i = 0; i < outPinsAllLenght; i++) {
    outPinsAllTimeStamp[i] = 0;
    outPinsAllTimeInterval[i] = 0;
    outPinsAllState[i] = LOW;  
  }


  /*
//anfangscheck:
   //alle auf einmal:
   for (int i = 0; i < outPinsAllLenght; i++) {
   digitalWriteE(i, 1500);
   }
   delay(1600);
   */


  checkAllForOff();
  if(debugSerial){
    Serial.println();
    Serial.println("gracefully reached end of setup");
    Serial.println();
  }
  
  digitalWriteE(1, 500);
  difftime[0] = millis();
  ivaltime = 700;
}





void loop() {  // put your main code here, to run repeatedly:
  currentMillis = millis();//handover current time into variable
  //overflow check, almost impossible but here:
  if(currentMillis < currentMillisLast){
    //reset stuff
    for (int i = 0; i < outPinsAllLenght; i++) {
      outPinsAllTimeStamp[i] = 0;
    }
  }
  currentMillisLast = currentMillis;



  //alle haendisch eingestellt:
  if(currentMillis - difftime[0] > ivaltime)
  {
    digitalWriteE(2, 500);
    difftime[0] = difftime[1] = currentMillis; 
    ivaltime += 700;
  }
  if(currentMillis - difftime[1] > 1400)
  {
    digitalWriteE(1, 500);
    difftime = currentMillis; 
  }
  delay(700); 
  digitalWriteE(11, 125);
  delay(300); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(11, 125);
  delay(300); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(11, 500);
  delay(300); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(10, 125);
  delay(300); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(1000); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(11, 3000);
  delay(50); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(13, 1000);
  delay(50); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(4, 125);
  delay(125); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(4, 125);
  delay(125); 
  digitalWriteE(12, 2000);
  delay(50); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(1, 125);
  delay(125); 
  digitalWriteE(2, 125);
  delay(125); 
  digitalWriteE(4, 1000);
  delay(125); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(7, 3000);
  delay(50); 
  digitalWriteE(8, 4000);
  delay(250);  
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(4, 4000);
  delay(50); 
  digitalWriteE(0, 3000);
  delay(250);  
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(3, 4000);
  delay(50); 
  digitalWriteE(6, 2000);
  delay(250);  
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(7, 3000);
  delay(50); 
  digitalWriteE(4, 2000);
  delay(250);  
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(9, 175);
  delay(175); 
  digitalWriteE(8, 200);
  delay(175); 
  digitalWriteE(7, 175);
  delay(175); 
  digitalWriteE(5, 400);
  delay(200); 
  digitalWriteE(6, 175);
  delay(175); 
  digitalWriteE(5, 400);
  delay(200); 
  digitalWriteE(6, 175);
  delay(175); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(0, 4000);
  delay(50); 
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(50);
  digitalWriteE(6, 2000);
  delay(250);  
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(3, 3000);
  delay(50); 
  digitalWriteE(7, 2000);
  delay(250);  
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(1, 2000);
  delay(50); 
  digitalWriteE(0, 3500);
  delay(250);  
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 400);
  delay(125); 
  digitalWriteE(6, 175);
  delay(175); 
  digitalWriteE(5, 400);
  delay(125); 
  digitalWriteE(6, 175);
  delay(175); 
  digitalWriteE(9, 175);
  delay(175); 
  digitalWriteE(8, 200);
  delay(125); 
  digitalWriteE(7, 175);
  delay(500); 
  digitalWriteE(12, 500);
  delay(50); 
  digitalWriteE(5, 800);
  delay(50); 
  digitalWriteE(6, 900);
  delay(5000); 
   digitalWriteE(0, 200);
  delay(100); 
  digitalWriteE(1, 200);
  delay(100); 
  digitalWriteE(2, 200);
  delay(100); 
  digitalWriteE(3, 200);
  delay(100); 
  digitalWriteE(11, 1000);
  delay(50); 
  digitalWriteE(4, 200);
  delay(100); 
  digitalWriteE(5, 200);
  delay(100); 
  digitalWriteE(9, 200);
  delay(100); 
  digitalWriteE(8, 200);
  delay(100); 
  digitalWriteE(7, 200);
  delay(100); 
  digitalWriteE(6, 200);
  delay(100); 
  digitalWriteE(5, 200);
  delay(100); 
  digitalWriteE(4, 200);
  delay(100); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(15, 8000);
  delay(10000); 
  digitalWriteE(6, 2000);
  delay(250);  
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(50);
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(10, 2000);
  delay(50); 
  digitalWriteE(7, 1500);
  delay(250);  
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10);
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(8, 500);
  delay(10);
  digitalWriteE(3, 500);
  delay(700); 
  digitalWriteE(2, 3000);
  delay(50); 
  digitalWriteE(4, 4000);
  delay(250);  
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(8, 500);
  delay(10); 
   digitalWriteE(0, 200);
  delay(100); 
  digitalWriteE(1, 200);
  delay(100); 
  digitalWriteE(2, 200);
  delay(100); 
  digitalWriteE(3, 200);
  delay(100); 
  digitalWriteE(11, 1000);
  delay(50); 
  digitalWriteE(6, 200);
  delay(100); 
  digitalWriteE(5, 200);
  delay(100); 
  digitalWriteE(4, 200);
  delay(100); 
  digitalWriteE(8, 200);
  delay(100); 
  digitalWriteE(7, 200);
  delay(100); 
  digitalWriteE(6, 200);
  delay(100); 
  digitalWriteE(5, 200);
  delay(100); 
  digitalWriteE(4, 200);
  delay(100); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(50);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(8, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(12, 7000);
  delay(7000); 
  digitalWriteE(3, 6000);
  delay(3000);
  digitalWriteE(7, 8000);
  delay(9000);
  digitalWriteE(5, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(4, 200);
  delay(125); 
  digitalWriteE(3, 300);
  delay(200); 
  digitalWriteE(4, 200);
  delay(125); 
  digitalWriteE(5, 200);
  delay(125); 
  digitalWriteE(6, 200);
  delay(125); 
  digitalWriteE(7, 300);
  delay(50); 
  digitalWriteE(8, 200);
  delay(125); 
  digitalWriteE(13, 1000);
  delay(5000); 
  digitalWriteE(4, 200);
  delay(600); 
  digitalWriteE(10, 2000);
  delay(4000); 
  digitalWriteE(0, 1000);
  delay(400); 
  digitalWriteE(9, 1000);
  delay(400); 
  digitalWriteE(8, 1000);
  delay(50); 
  digitalWriteE(4, 500);
  delay(50); 
  digitalWriteE(5, 500);
  delay(400); 
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(7, 500);
  delay(700);   
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 2000);
  delay(50);
  digitalWriteE(9, 2000);
  delay(50);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(700);
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(7, 500);
  delay(700);   
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(12, 4000);
  delay(3000); 
  digitalWriteE(4, 4000);
  delay(3000);
  digitalWriteE(7, 8000);
  delay(9000);
  digitalWriteE(0, 500);
  delay(700);   
  digitalWriteE(1, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(9, 3000);
  delay(4000); 
  digitalWriteE(0, 1000);
  delay(600); 
  digitalWriteE(15, 4000);
  delay(6000); 
  digitalWriteE(1, 200);
  delay(50); 
  digitalWriteE(0, 300);
  delay(50); 
  digitalWriteE(9, 300);
  delay(50); 
  digitalWriteE(8, 200);
  delay(125); 
  digitalWriteE(4, 200);
  delay(125); 
  digitalWriteE(5, 200);
  delay(125); 
  digitalWriteE(6, 125);
  delay(125); 
  digitalWriteE(7, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(8, 125);
  delay(125); 
  digitalWriteE(7, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(6, 125);
  delay(125); 
  digitalWriteE(7, 125);
  delay(125); 
  digitalWriteE(8, 125);
  delay(125); 
  digitalWriteE(11, 3000);
  delay(500); 
  digitalWriteE(14, 8000);
  delay(8000); 
  digitalWriteE(3, 5000);
  delay(2000);
  digitalWriteE(0, 6000);
  delay(4000);
  digitalWriteE(8, 8000);
  delay(9000);
  digitalWriteE(4, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(5, 125);
  delay(125); 
  digitalWriteE(6, 125);
  delay(125); 
  digitalWriteE(4, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(5, 125);
  delay(125); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(6, 125);
  delay(125); 
  digitalWriteE(7, 125);
  delay(125); 
  digitalWriteE(4, 125);
  delay(125); 
  digitalWriteE(3, 125);
  delay(125); 
  digitalWriteE(5, 1000);
  delay(125); 
  digitalWriteE(6, 500);
  delay(700); 
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(7, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);   
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(11, 3000);
  delay(500); 
  digitalWriteE(14, 4000);
  delay(6000); 
  digitalWriteE(4, 5000);
  delay(2000);
  digitalWriteE(2, 6000);
  delay(4000);
  digitalWriteE(6, 8000);
  delay(9000);
  digitalWriteE(7, 500);
  delay(700);
  digitalWriteE(1, 3000);
  delay(100);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(9, 500);
  delay(200); 
  digitalWriteE(11, 600);
  delay(500); 
  digitalWriteE(0, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(3, 500);
  delay(600); 
  digitalWriteE(10, 125);
  delay(100); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(9, 1000);
  delay(700); 
  digitalWriteE(8, 1000);
  delay(700); 
  digitalWriteE(6, 1500);
  delay(5000); 
  digitalWriteE(3, 500);
  delay(10);
  digitalWriteE(11, 500);
  delay(50);
  digitalWriteE(10, 500);
  delay(50);
  digitalWriteE(9, 500);
  delay(50);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(50);
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(8, 2000);
  delay(100);
  digitalWriteE(1, 3000);
  delay(100);
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(7, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);   
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(3, 500);
  delay(10); 
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(7, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(10);
  digitalWriteE(6, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(10); 
  digitalWriteE(0, 500);
  delay(10); 
  digitalWriteE(5, 500);
  delay(10); 
  digitalWriteE(4, 500);
  delay(700);
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700); 
  digitalWriteE(7, 500);
  delay(200); 
  digitalWriteE(11, 600);
  delay(500); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(3, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(0, 500);
  delay(600); 
  digitalWriteE(10, 500);
  delay(100); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(5, 1000);
  delay(700); 
  digitalWriteE(6, 1000);
  delay(700); 
  digitalWriteE(3, 1500);
  delay(5000);
  digitalWriteE(3, 500);
  delay(10);
  digitalWriteE(7, 500);
  delay(10); 
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(1, 2000);
  delay(1000);
  digitalWriteE(8, 1500);
  delay(1000);
  digitalWriteE(0, 1700);
  delay(1000);
  digitalWriteE(6, 2300);
  delay(5000);
  digitalWriteE(0, 3400);
  delay(1000);
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(11, 1000);
  delay(50);
  digitalWriteE(10, 1000);
  delay(50);
  digitalWriteE(9, 1000);
  delay(50);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(8, 500);
  delay(700);  
  digitalWriteE(4, 3000);
  delay(1000);
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(1, 4000);
  delay(1000);
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(8, 500);
  delay(700);  
  digitalWriteE(5, 4000);
  delay(1000);
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700); 
  digitalWriteE(7, 500);
  delay(700);  
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(11, 2000);
  delay(50);
  digitalWriteE(10, 2000);
  delay(50);
  digitalWriteE(9, 2000);
  delay(50);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(3, 500);
  delay(50);
  digitalWriteE(0, 500);
  delay(700);    
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(11, 1000);
  delay(2000);
  digitalWriteE(10, 1000);
  delay(2000);
  digitalWriteE(9, 2000);
  delay(1500);
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(2, 500);
  delay(700);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(3, 500);
  delay(700);  
  digitalWriteE(7, 500);
  delay(700); 
  digitalWriteE(2, 1000);
  delay(300);  
  digitalWriteE(6, 500);
  delay(700);  
  digitalWriteE(7, 1000);
  delay(500); 
  digitalWriteE(2, 500);
  delay(200);  
  digitalWriteE(6, 500);
  delay(200);  
  digitalWriteE(3, 500);
  delay(200);  
  digitalWriteE(2, 500);
  delay(200);  
  digitalWriteE(6, 500);
  delay(200);  
  digitalWriteE(3, 500);
  delay(200);  
  digitalWriteE(7, 500);
  delay(200); 
  digitalWriteE(3, 500);
  delay(700);
  digitalWriteE(2, 500);
  delay(700); 
  digitalWriteE(1, 500);
  delay(700); 
  digitalWriteE(0, 500);
  delay(200); 
  digitalWriteE(11, 600);
  delay(500); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(4, 500);
  delay(700); 
  digitalWriteE(5, 500);
  delay(700); 
  digitalWriteE(6, 500);
  delay(700); 
  digitalWriteE(7, 500);
  delay(600); 
  digitalWriteE(10, 500);
  delay(100); 
  digitalWriteE(8, 500);
  delay(700); 
  digitalWriteE(0, 500);
  delay(700); 
  digitalWriteE(2, 1000);
  delay(700); 
  digitalWriteE(9, 1000);
  delay(700); 
  digitalWriteE(3, 1500);
  delay(3000);
  
}




void digitalWriteE(int leuchte, char what){
}
void digitalWriteE(int leuchte, int interval){
  currentMillis = millis();//handover current time into variable

  if(outPinsAllState[leuchte] == LOW){
    //2. MAKE potentially ON:
    if( (leuchte) == 14 ){      //for receiver 1:
      Serial.print('1'); // send '1' for HIGH
      if(debugSerial){
        Serial.print(outPinsAll[leuchte]);
        Serial.println(", HIGH");
      }
      if(debugLed){
        digitalWrite(ledPin13, HIGH);
      }
    }
    else if( (leuchte) == 15 ){      //for receiver 2:
      Serial.print('2'); // send '2' for HIGH
      if(debugSerial){
        Serial.print(outPinsAll[leuchte]);
        Serial.println(", HIGH");
      }
      if(debugLed){
        digitalWrite(ledPin13, HIGH);
      }
    }
    else{

      if(debugSerial){
        Serial.print(outPinsAll[leuchte]);
        Serial.println(", HIGH");
      }
      digitalWrite(outPins[(leuchte)], HIGH);

    }
  }


  //1. HANDOVER:
  if(interval > 0){
    if(debugSerial){
      Serial.print("in interval > 0, interval = ");
      Serial.println(interval);
    }
    //update stuff in memory
    outPinsAllTimeStamp[(leuchte)] = currentMillis;
    outPinsAllTimeInterval[(leuchte)] = interval;
    outPinsAllState[(leuchte)] = HIGH;
    if(debugSerial){
      Serial.print("set stuff for leuchte ");
      Serial.println(leuchte);
    }
  }
  /*
  else if(interval == 0){
   if(debugSerial){
   Serial.println("interval == 0");
   }
   //nur hight oder low oder vielleicht digitalWrite(pin, FLIP); 
   }
   */

  checkAllForOff();

}


void checkAllForOff(){
  if(debugSerial){
    //Serial.println("in checkAllForOff()");
  }
  currentMillis = millis();//handover current time into variable

  //3. CHECK ALL IF TIME IS OVER AND NOW TO TURN OFF:
  for(int i=0; i<outPinsAllLenght; i++){
    //wenn von irgendeiner leuchte die Zeit um is für das folgende aus:
    if(outPinsAllState[i] != LOW){
      if(currentMillis - outPinsAllTimeStamp[i] > outPinsAllTimeInterval[i]){
        outPinsAllState[i] = LOW;
        if(debugSerial){
          Serial.print("turn off true for ");
          Serial.println(i);
        }
        //handle diffrent cases:
        if(outPinsAll[i] == 14){      //for receiver 1:
          Serial.print('L'); // send 'L' for LOW
          if(debugLed){
            digitalWrite(ledPin13, LOW);
          }
          if(debugSerial){
            Serial.print(outPinsAll[i]);
            Serial.println(", LOW");
          }
        }
        else if(outPinsAll[i] == 15){      //for receiver 2:
          Serial.print('O'); // send an 'O' for LOW
          if(debugLed){
            digitalWrite(ledPin13, LOW);
          }
          if(debugSerial){
            Serial.print(outPinsAll[i]);
            Serial.println(", LOW");
          }
        }
        else{
          digitalWrite(outPinsAll[i], LOW);
          if(debugSerial){
            Serial.print(outPinsAll[i]);
            Serial.println(", LOW");
          }
        }

      }
    }
  }
}


/*
//CODE for receiver 1
 
 const int ledPin13 = 13; // the pin that the LED is attached to
 int incomingByte;      // a variable to read incoming serial data into
 
 boolean debug = false;
 
 void setup() {
 // initialize serial communication:
 Serial.begin(9600);
 
 // initialize the LED pin as an output:
 pinMode(ledPin13, OUTPUT);
 digitalWrite(ledPin13, LOW);
 
 
 delay(1000);
 
 if(debug){
 //give sign for start:
 for(int i=0, t=500; i<5; i++){
 digitalWrite(ledPin13, HIGH);
 delay(t - i*100);
 digitalWrite(ledPin13, LOW);
 delay(t - i*100);
 }
 }
 }
 
 void loop() {
 // see if there's incoming serial data:
 if (Serial.available() > 0) {
 // read the oldest byte in the serial buffer:
 incomingByte = Serial.read();
 // if it's ASCII... '1', turn on the LED:
 if (incomingByte == '1') {
 digitalWrite(ledPin13, HIGH);
 } 
 // if it's ASCII... 'L', turn off the LED: L for LOW
 if (incomingByte == 'L') {
 digitalWrite(ledPin13, LOW);
 }
 }
 }
 */





/*
 //CODE for receiver 2
 
 const int ledPin13 = 13; // the pin that the LED is attached to
 int incomingByte;      // a variable to read incoming serial data into
 
 boolean debug = false;
 
 void setup() {
 // initialize serial communication:
 Serial.begin(9600);
 
 // initialize the LED pin as an output:
 pinMode(ledPin13, OUTPUT);
 digitalWrite(ledPin13, LOW);
 
 
 delay(1000);
 
 if(debug){
 //give sign for start:
 for(int i=0, t=500; i<5; i++){
 digitalWrite(ledPin13, HIGH);
 delay(t - i*100);
 digitalWrite(ledPin13, LOW);
 delay(t - i*100);
 }
 }
 }
 
 void loop() {
 // see if there's incoming serial data:
 if (Serial.available() > 0) {
 // read the oldest byte in the serial buffer:
 incomingByte = Serial.read();
 // if it's ASCII... '2', turn on the LED:
 if (incomingByte == '2') {
 digitalWrite(ledPin13, HIGH);
 } 
 // if it's ASCII... 'O', turn off the LED: O for Off
 if (incomingByte == 'O') {
 digitalWrite(ledPin13, LOW);
 }
 }
 }
 
 */






































