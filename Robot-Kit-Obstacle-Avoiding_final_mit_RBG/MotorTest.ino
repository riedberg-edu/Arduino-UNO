#include <Servo.h>          //Servo motor library. This is standard library

// L298N control pins
const int LeftMotorForward = 9; //9;
const int LeftMotorBackward = 8; //6;
const int RightMotorForward = 6; //10;
const int RightMotorBackward = 7; //11;
const int PMWRight = 5; //3;
const int PMWLeft = 10; //5;

/* Anschluss an Arduino:
5 gelb
6 grün
7 blau
8 orange
9 rot
10 weiß
*/

Servo servo_motor; //our servo name

void setup(){

  pinMode(PMWRight, OUTPUT);
  pinMode(PMWLeft, OUTPUT);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);

  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
 
  delay(2000);
 
}

void loop(){

  moveStop();
  delay (5000);
 
  moveForward();
  delay(2000);
 
  moveStop();
  delay (2000);
 
  moveBackward();
  delay (2000);
 
  moveStop();
  delay (2000);
 
  turnLeft();
  delay (2000);

  moveStop();
  delay (2000);

  turnRight();
  delay (2000);
}

 

 

void moveStop(){
   // set speed to 150 out 255
  analogWrite(PMWRight, 200);
   // set speed to 150 out 255
  analogWrite(PMWLeft, 120);
 
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);

  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
 
  delay(1500);
 
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
 
 
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
 
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(1500);
 
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
 
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
