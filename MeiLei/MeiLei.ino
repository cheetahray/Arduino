/**
 * Bruno Santos, 2013
 * feiticeir0@whatgeek.com.pt
 * Small code to test DC motors - 2x with a L298 Dual H-Bridge Motor Driver
 * Free to share
 **/
#define FORWARD 4
#define BACKWARD 3
#define COAST 2
#define STOP 1
//Testing the DC Motors
//Define Pins
//Motor A
int enableA = 7;
int Amin = 19;
int Amax = 18;
int pinA1 = 6;
int pinA2 = 5;
int Awhichway = STOP;
unsigned long Atime;

//Motor B
int enableB = 2;
int Bmin = 21;
int Bmax = 20;
int pinB1 = 4;
int pinB2 = 3;
int Bwhichway = STOP;
unsigned long Btime;

int enableC = 8;
int Cmin = 16;
int Cmax = 17;
int pinC1 = 10;
int pinC2 = 9;
int Cwhichway = STOP;
unsigned long Ctime;

//Motor B
int enableD = 13;
int Dmin = 15;
int Dmax = 14;
int pinD1 = 12;
int pinD2 = 11;
int Dwhichway = STOP;
unsigned long Dtime;

//define time for run
// in milliseconds
unsigned long nowtime, difftime;

void setup() {
  Serial.begin (9600);
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (pinA1, OUTPUT);
  pinMode (pinA2, OUTPUT);

  pinMode (enableB, OUTPUT);
  pinMode (pinB1, OUTPUT);
  pinMode (pinB2, OUTPUT);

  pinMode (enableC, OUTPUT);
  pinMode (pinC1, OUTPUT);
  pinMode (pinC2, OUTPUT);

  pinMode (enableD, OUTPUT);
  pinMode (pinD1, OUTPUT);
  pinMode (pinD2, OUTPUT);

  enableMotors();
  forward();

}
//Defining functions so it's more easy
//motor functions
void motorAforward() {
  digitalWrite (pinA1, HIGH);
  digitalWrite (pinA2, LOW);
  Awhichway = FORWARD;
}
void motorBforward() {
  digitalWrite (pinB1, HIGH);
  digitalWrite (pinB2, LOW);
  Bwhichway = FORWARD;
}
void motorCforward() {
  digitalWrite (pinC1, LOW);
  digitalWrite (pinC2, HIGH);
  Cwhichway = FORWARD;
}
void motorDforward() {
  digitalWrite (pinD1, HIGH);
  digitalWrite (pinD2, LOW);
  Dwhichway = FORWARD;
}
void motorAbackward() {
  digitalWrite (pinA1, LOW);
  digitalWrite (pinA2, HIGH);
  Awhichway = BACKWARD;
}
void motorBbackward() {
  digitalWrite (pinB1, LOW);
  digitalWrite (pinB2, HIGH);
  Bwhichway = BACKWARD;
}
void motorCbackward() {
  digitalWrite (pinC1, HIGH);
  digitalWrite (pinC2, LOW);
  Cwhichway = BACKWARD;
}
void motorDbackward() {
  digitalWrite (pinD1, LOW);
  digitalWrite (pinD2, HIGH);
  Dwhichway = BACKWARD;
}
void motorAstop() {
  digitalWrite (pinA1, HIGH);
  digitalWrite (pinA2, HIGH);
  Awhichway = STOP;
}
void motorBstop() {
  digitalWrite (pinB1, HIGH);
  digitalWrite (pinB2, HIGH);
  Bwhichway = STOP;
}
void motorCstop() {
  digitalWrite (pinC1, HIGH);
  digitalWrite (pinC2, HIGH);
  Cwhichway = STOP;
}
void motorDstop() {
  digitalWrite (pinD1, HIGH);
  digitalWrite (pinD2, HIGH);
  Dwhichway = STOP;
}
void motorAcoast() {
  digitalWrite (pinA1, LOW);
  digitalWrite (pinA2, LOW);
  Awhichway = COAST;
}
void motorBcoast() {
  digitalWrite (pinB1, LOW);
  digitalWrite (pinB2, LOW);
  Bwhichway = COAST;
}
void motorCcoast() {
  digitalWrite (pinC1, LOW);
  digitalWrite (pinC2, LOW);
  Cwhichway = COAST;
}
void motorDcoast() {
  digitalWrite (pinD1, LOW);
  digitalWrite (pinD2, LOW);
  Dwhichway = COAST;
}
void motorAon() {
  digitalWrite (enableA, HIGH);
}
void motorBon() {
  digitalWrite (enableB, HIGH);
}
void motorCon() {
  digitalWrite (enableC, HIGH);
}
void motorDon() {
  digitalWrite (enableD, HIGH);
}
void motorAoff() {
  digitalWrite (enableA, LOW);
}
void motorBoff() {
  digitalWrite (enableB, LOW);
}
void motorCoff() {
  digitalWrite (enableC, LOW);
}
void motorDoff() {
  digitalWrite (enableD, LOW);
}

// Movement functions
void forward () {
  motorAforward();
  motorBforward();
  motorCforward();
  delay(1000);
  motorDforward();
}
/*
 void backward (int duration) {
 motorAbackward();
 motorBbackward();
 delay (duration);
 }
 void left (int duration) {
 motorAbackward();
 motorBforward();
 delay (duration);
 }
 void right (int duration) {
 motorAforward();
 motorBbackward();
 delay (duration);
 }
 void coast (int duration) {
 motorAcoast();
 motorBcoast();
 delay (duration);
 }
 void breakRobot (int duration) {
 motorAstop();
 motorBstop();
 delay (duration);
 }
 */

void disableMotors() {
  motorAoff();
  motorBoff();
  motorCoff();
  motorDoff();
}
void enableMotors() {
  motorAon();
  motorBon();
  motorCon();
  motorDon();
}

void loop() {

  nowtime = millis();
  
  difftime = nowtime - Dtime;
  if(digitalRead(Dmax) == true)
  {
    if(Dwhichway != STOP && difftime > 1000)
    {
      Dtime = nowtime;
      motorDstop();
    }
    else
    {
      motorDbackward();  
    }
  }
  else if(digitalRead(Dmin) == true)
  {
    if(Dwhichway != STOP && difftime > 1000 )
    {
      Dtime = nowtime;
      motorDstop();
    }
    else
    {
      motorDforward();  
    }
  }
  else if(Dwhichway == COAST && difftime > 300)
  {
    switch(random(BACKWARD, FORWARD))
    {
    case BACKWARD:
      motorDbackward();
      break;
    case FORWARD:
      motorDforward();
      break;
    }  
  }
  else if( difftime > 2000 )
  {
    Dtime = nowtime;
    motorDcoast();
  }

  difftime = nowtime - Ctime;
  if(digitalRead(Cmax) == true)
  {
    if(Cwhichway != STOP && difftime > 1000)
    {
      Ctime = nowtime;
      motorCstop();
    }
    else
    {
      motorCbackward();  
    }
  }
  else if(digitalRead(Cmin) == true)
  {
    if(Cwhichway != STOP && difftime > 1000 )
    {
      Ctime = nowtime;
      motorCstop();
    }
    else
    {
      motorCforward();  
    }
  }
  else if(Cwhichway == COAST && difftime > 300)
  {
    switch(random(BACKWARD, FORWARD))
    {
    case BACKWARD:
      motorCbackward();
      break;
    case FORWARD:
      motorCforward();
      break;
    }  
  }
  else if( difftime > 2000 )
  {
    Ctime = nowtime;
    motorCcoast();
  }

  difftime = nowtime - Btime;
  if(digitalRead(Bmax) == true)
  {
    //Serial.println("Bmax");
    if(Bwhichway != STOP && difftime > 1000)
    {
      Btime = nowtime;
      motorBstop();
    }
    else
    {
      motorBbackward();  
    }
  }
  else if(digitalRead(Bmin) == true)
  {
    Serial.println("Bmin");
    if(Bwhichway != STOP && difftime > 1000)
    {
      Btime = nowtime;
      motorBstop();
    }
    else
    {
      motorBforward();  
    }
  }
  else if(Bwhichway == COAST && difftime > 300)
  {
    switch(random(BACKWARD, FORWARD))
    {
    case BACKWARD:
      motorBbackward();
      break;
    case FORWARD:
      motorBforward();
      break;
    }  
  }
  else if( difftime > 2000 )
  {
    Btime = nowtime;
    motorBcoast();
  }

  difftime = nowtime - Atime;
  if(digitalRead(Amax) == true)
  {
    Serial.println("Amax");
    if(Awhichway != STOP && difftime > 1000)
    {
      Atime = nowtime;
      motorAstop();
    }
    else
    {
      motorAbackward();  
    }
  }
  else if(digitalRead(Amin) == true)
  {
    Serial.println("Amin");
    if(Awhichway != STOP && difftime > 1000)
    {
      Atime = nowtime;
      motorAstop();
    }
    else
    {
      motorAforward();  
    }
  }
  else if(Awhichway == COAST && difftime > 300)
  {
    switch(random(BACKWARD, FORWARD))
    {
    case BACKWARD:
      motorAbackward();
      break;
    case FORWARD:
      motorAforward();
      break;
    }  
  }
  else if( difftime > 2000 )
  {
    Atime = nowtime;
    motorAcoast();
  }
  
  //Forward for 1,5s
  /*
        Serial.println ("forward...");
   forward (1500);
   if (millis() > running) {
   play = false;
   Serial.println ("Falsing");
   }
   */

  //disable motors
  //disableMotors();
}




