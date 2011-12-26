/*
   EXcode 15-1
*/
boolean state =0;     //1:HIGH  ;  0:LOW
int ledPin = 13; 
int PIRSensor = 2; // PIR ????

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(PIRSensor, INPUT); // ?? PIRSensor??? INPUT
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() 
{
  state = digitalRead(PIRSensor); // ??????
  digitalWrite(ledPin, state);
  if (HIGH == state)
  {
    Serial.print("A");
  }
  else 
  {
    Serial.print("N");
  }
  delay(1000); 
  
}