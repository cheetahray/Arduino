/*
   EXcode 15-1
*/
int ledPin = 13; 
int NCount;
void setup() 
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  NCount = 0;
}

void loop() 
{
  if(Serial.available() > 0)  
  {
    char D1;
    while('N' == ( D1 = Serial.read() ) )  //確認起始字元
    {
      if(NCount++ > 10)
      {
        NCount = 0;
       Serial.flush();
      }
      digitalWrite(ledPin, LOW);
    }
    if('A' == D1)  //確認起始字元
    {
      digitalWrite(ledPin, HIGH);
      Serial.write('A');
      Serial.flush();
    }
  }
  delay(100);
}
