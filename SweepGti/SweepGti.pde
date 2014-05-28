// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#define rayval2 1000
#define raydelay 15

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int out1Pin = 7; // LED connected to digital pin 13
int out2Pin = 11; // LED connected to digital pin 13
int in1Pin = 8;   // pushbutton connected to digital pin 7 
int in2Pin = 10;   // pushbutton connected to digital pin 7 
int pos = 0;    // variable to store the servo position 
int val1,val2;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  /*
  while(pos <= 180)
  {
    myservo.write(pos++);              // tell servo to go to position in variable 'pos' 
    delay(raydelay);     
  }
  */
  pinMode(out1Pin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(out2Pin, OUTPUT);      // sets the digital pin 13 as output
  pinMode(in1Pin, INPUT);      // sets the digital pin 7 as input
  pinMode(in2Pin, INPUT);      // sets the digital pin 7 as input
  digitalWrite(out1Pin, HIGH);    // sets the LED to the button's value
  digitalWrite(out2Pin, HIGH);    // sets the LED to the button's value
  Serial.begin(9600);
  myservo.write(pos);
} 
 
 
void loop() 
{ 
  //Serial.print(digitalRead(in2Pin));
  //Serial.println(val2);
  
  if(HIGH == digitalRead(in2Pin))
  {
    if(val2 > rayval2)
      val2 = rayval2;
    else
      val2++;
  }
  else
  {
    val2 = 0; 
  }
  
  if(LOW == digitalRead(in1Pin))
  {
    Serial.println("open");
    for(pos = myservo.read(); pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(raydelay);                       // waits 15ms for the servo to reach the position 
    }
  }
  else if(rayval2 == val2)
  {
    Serial.println("close");
    for(pos = myservo.read(); pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(raydelay);                       // waits 15ms for the servo to reach the position 
    }
  }
  
} 
