#include <SoftwareSerial.h>

//L293 Connection   
  const int motorA1  = 2;  // Pin  2 of L293
  const int motorA2  = 3;  // Pin  7 of L293
  const int motorB1  = 4;  // Pin 10 of L293
  const int motorB2  = 5;  // Pin 15 of L293

//SR04 Connection
  const int trigPinL = 7;
  const int echoPinL = 8;
  const int trigPinC = 9;
  const int echoPinC = 10;
  const int trigPinR = 11;
  const int echoPinR = 12;

  long durationL;
  int distanceL;
  long durationC;
  int distanceC;
  long durationR;
  int distanceR;
  char state;

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    // Sets the trigPin as an Output
    pinMode(trigPinL, OUTPUT); 
    pinMode(trigPinC, OUTPUT); 
    pinMode(trigPinR, OUTPUT); 
    // Sets the echoPin as an Input
    pinMode(echoPinL, INPUT); 
    pinMode(echoPinC, INPUT); 
    pinMode(echoPinR, INPUT); 

    // Starts the serial communication
    Serial.begin(9600); 
}
 
void loop() {
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = durationL*0.034/2;

  digitalWrite(trigPinC, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinC, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinC, LOW);
  durationC = pulseIn(echoPinC, HIGH);
  distanceC = durationC*0.034/2;

  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = durationR*0.034/2;

  Serial.print(distanceL);
  Serial.print(" ");
  Serial.print(distanceC);
  Serial.print(" ");
  Serial.println(distanceR);

  state='F';
  
  if(distanceC >10 && distanceR <10 && distanceL <10){
   //front
      digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); 
  }
  if(distanceC <10 && distanceR >10 && distanceL <10){
    //right
      digitalWrite(motorA1, LOW ); digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); 
  }
  if(distanceC <10 && distanceR <10 && distanceL >10){
    //left
      digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW ); digitalWrite(motorB2, HIGH); 
  }
  if(distanceC <10 && distanceR <10 && distanceL <10){
    //stop
    digitalWrite(motorA1, LOW); digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW ); digitalWrite(motorB2,LOW); 
  }
  
  if (state == 'F') {
      digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); 
    }
    
 delay(500);
}

