/*
   EXcode 15-1
*/
int ledPin = 13; 

void setup() 
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available() > 0)  
    {
      char D1 = Serial.read();
      if('A' == D1)  //確認起始字元
        {
         Serial.write('A');
       }
       else if('B' == D1)  //確認起始字元
        {
         Serial.write('B');
       }
    }    

   delay(1000); 
}
