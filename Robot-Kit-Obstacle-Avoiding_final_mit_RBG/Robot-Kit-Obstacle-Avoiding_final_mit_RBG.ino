#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RGB_PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, RGB_PIN, NEO_GRB + NEO_KHZ800);

//our L298N control pins
const int LeftMotorForward = 7; // 9;
const int LeftMotorBackward = 8; 
const int RightMotorForward = 11; // 6; 
const int RightMotorBackward = 9; // 7; 
const int PWMRight = 6; 
const int PWMLeft = 5; // 

#define carSpeed 150  // initial speed of car >=0 to <=255

/* Anschluss an Arduino:
3 gelb
6 grün
7 blau
8 lia
9 grau
10 weiß
*/

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

////////// IR REMOTE CODES //////////
#define Auto 2700
#define AutoOff 652
#define F 3363236978 // FORWARD
#define B 3380014599 // BACK
#define L 2239869123  // LEFT
#define R 2860788123  // RIGHT
#define S 2475633871 // STOP
#define UNKNOWN_F 2605695303    // FORWARD
#define UNKNOWN_B 2588917682  // BACK
#define UNKNOWN_L 1932877326  // LEFT
#define UNKNOWN_R 1311958330   // RIGHT
#define UNKNOWN_S 3493298410  // STOP
 
#define RECV_PIN  12
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;
unsigned long preMillis;
 

#define maximum_distance 200
boolean goesForward = false;
boolean remoteOn = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){
  Serial.begin(9600);
  pinMode(PWMRight, OUTPUT);
  pinMode(PWMLeft, OUTPUT);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  digitalWrite(PWMRight, HIGH);
  digitalWrite(PWMLeft, HIGH);

  servo_motor.attach(13); //our servo pin

  servo_motor.write(90);
  delay(2000);

  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  stopp();
  irrecv.enableIRIn();  
}

void automatikBetrieb(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

    // set speed to 150 out 255
  analogWrite(PWMRight, 200);
   // set speed to 150 out 255
  analogWrite(PWMLeft, 200);
 

  if (distance <= 50){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}



void loop(){
  if (irrecv.decode(&results)){ 
    preMillis = millis();
    val = results.value;
    Serial.println(val);
    irrecv.resume();
    switch(val){
      case Auto: remoteOn = false; break;
      case AutoOff: remoteOn = true; break;
      case F: 
      case UNKNOWN_F: 
        forward(); break;
      case B: 
      case UNKNOWN_B: back(); break;
      case L: 
      case UNKNOWN_L: left(); break;
      case R: 
      case UNKNOWN_R: right();break;
      case S: 
      case UNKNOWN_S: 
        stopp(); 
        break;
      default: break;
    }
  }
  else{
    if(millis() - preMillis > 500){
      stopp();
      preMillis = millis();
    }
  }
  
  if (!remoteOn) {
    automatikBetrieb();  }
}

 void forward(){ 
  digitalWrite(PWMLeft,HIGH);
  digitalWrite(PWMRight,HIGH);
  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(RightMotorForward,HIGH);
  Serial.println("go forward!");
}
void back(){
  digitalWrite(PWMLeft,HIGH);
  digitalWrite(PWMRight,HIGH);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,HIGH);
  digitalWrite(RightMotorForward,LOW);
  Serial.println("go back!");
}
void left(){
  analogWrite(PWMLeft,carSpeed);
  analogWrite(PWMRight,carSpeed);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(RightMotorForward,HIGH); 
  Serial.println("go left!");
}
void right(){
  analogWrite(PWMLeft,carSpeed);
  analogWrite(PWMRight,carSpeed);
  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,HIGH);
  digitalWrite(RightMotorForward,LOW);
  Serial.println("go right!");
}
void stopp(){
  digitalWrite(PWMLeft, LOW);
  digitalWrite(PWMRight, LOW);
  Serial.println("STOP!");  
}


int lookRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){

     // set speed to 150 out 255
  analogWrite(PWMRight, 200);
   // set speed to 150 out 255
  analogWrite(PWMLeft, 200);
  
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

void moveForward2(){

  if(!goesForward){

    goesForward=true;
    
//    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
//    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

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
  
  delay(250);
  
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

  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
