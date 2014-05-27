// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9,900,2100);  // attaches the servo on pin 9 to the servo object 
  //myservo.write(0);
  myservo.writeMicroseconds(1500);      
  delay(500);
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 2100; pos += 10)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos' 
    delay(20);                       // waits 15ms for the servo to reach the position 
  }
  
  for(pos = 2100; pos>=0; pos-=10)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos' 
    delay(20);                       // waits 15ms for the servo to reach the position 
  } 
} 
