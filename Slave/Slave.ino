/*
   EXcode 15-1
*/
int ledPin = 13; 
int PIRSensor = 2; // PIR 模組訊號

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(PIRSensor, INPUT); // 宣告 PIRSensor狀態為 INPUT
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() 
{
  boolean state = digitalRead(PIRSensor); // 讀取目前狀態
  if (HIGH == state)
  {
    Serial.print("A");
  }
  else 
  {
    Serial.print("N");
  }
  digitalWrite(ledPin, state);
  delay(150); 
}
