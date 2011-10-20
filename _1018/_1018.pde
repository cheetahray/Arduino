/*
   EXcode 15-1
*/
boolean lastState, state = 0;     //1:HIGH  ;  0:LOW
int ledPin = 13; 
int PIRSensor = 2; // PIR 模組訊號
int n = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(PIRSensor, INPUT); // 宣告 PIRSensor狀態為 INPUT
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() 
{
  state = digitalRead(PIRSensor); // 讀取目前狀態
  
  if(lastState != state)
  {
    digitalWrite(ledPin,HIGH);
    if(state==HIGH) Serial.print("A");
   // else Serial.print("B");
   n=0;
    delay(100);
  } else 
    {
      digitalWrite(ledPin,LOW);
      n++;
      if(n>10) Serial.print("N");
      delay(10); 
    }
   lastState = state;
   //delay(500);
}
