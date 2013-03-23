#define cdelay 10
#define udelay 1

int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        
char oldmotor, nowmotor;
 
void setup() 
{
    Serial.begin(9600);
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
} 
 
void loop() 
{ 
  int value;
  if(Serial.available())
  { 
    nowmotor = Serial.read();
    if(oldmotor != nowmotor)
    {  
      oldmotor = nowmotor;
      switch(nowmotor)
      {
        case 'd':
          for(value = 0 ; value <= 255; value++) 
          { 
            digitalWrite(M1,LOW);   
            digitalWrite(M2, LOW);       
            analogWrite(E1, value);   //PWM Speed Control
            //analogWrite(E2, value);   //PWM Speed Control
            delay(cdelay);
          }
        
          //delay(5000); 
        
          for(value = 255 ; value >= 0; value--) 
          { 
            digitalWrite(M1,LOW);   
            digitalWrite(M2, LOW);       
            analogWrite(E1, value);   //PWM Speed Control
            //analogWrite(E2, value);   //PWM Speed Control
            delay(cdelay);
          }
        break;
      
        case 'u':
          for(value = 0 ; value <= 255; value++) 
          { 
            digitalWrite(M1,HIGH);   
            digitalWrite(M2, HIGH);       
            analogWrite(E1, value);   //PWM Speed Control
            //analogWrite(E2, value);   //PWM Speed Control
            delay(udelay);
          }
        
          //delay(5000); 
        
          for(value = 255 ; value >= 0; value--) 
          { 
            digitalWrite(M1,HIGH);   
            digitalWrite(M2, HIGH);       
            analogWrite(E1, value);   //PWM Speed Control
            //analogWrite(E2, value);   //PWM Speed Control
            delay(udelay);
          }
        break;
      }
    }
  }
}
