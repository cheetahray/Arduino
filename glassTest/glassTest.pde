#define RELAY 13

void setup() {
  Serial.begin(9600);
  pinMode(RELAY,OUTPUT);
}

void loop() 
{
  if(Serial.available())
  { 
    char now = Serial.read();
    if(now == '1')
    {
      digitalWrite(RELAY, HIGH);
    }
    else
    {
      digitalWrite(RELAY, LOW);
    }
    Serial.flush();
    delay(100);
  }
}
