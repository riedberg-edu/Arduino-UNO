#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#include <AFMotor.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// fuer Neopixel
#define neopix_PIN 2
#define AnzahlLEDs 4
#define rot 1
#define green 2
#define white 3
#define blau 4
#define VorneRechts 0
#define VorneLinks 1
#define HintenLinks 3
#define HintenRechts 2

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define IR_RECV_PIN  9
#define Servo_PIN 10

// für die Car Hardware Identifikation
#define car_decode_pin_0 A3
#define car_decode_pin_1 A4
#define car_decode_pin_2 A5

int carIdent = 0;
int carSpeedL = 180;  // initial speed of car >=0 to <=255
int carSpeedR = 180;
int forwardRightDelay = 0;
boolean remoteOn = true;

#define maximum_distance 200

IRrecv irrecv(IR_RECV_PIN);
decode_results results;
unsigned long val;
unsigned long preMillis;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(AnzahlLEDs, neopix_PIN, NEO_GRB + NEO_KHZ800);

AF_DCMotor motor_links(4);
AF_DCMotor motor_rechts(3);

int distance = 100;
NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function

Servo servo_motor; //our servo name

#include <ir_robot_car.h>

void carHardwareconfig (int car) {
  carSpeedL = 180;
  carSpeedR = 180;
  switch (car) {
    case 0:
      break;
    case 1:
      IR_Remote_DEV = IR_Remote_DEV_Makeblock;
      Serial.println("Leo");
      carSpeedL = 210;
      carSpeedR = 230;
      break;
    case 2:
      break;
    case 3:
      carSpeedL = 180;
      IR_Remote_DEV = IR_Remote_DEV_Pinnacle;
      Serial.println("Schüler 3");
      break;
    case 4:
      IR_Remote_DEV = IR_Remote_DEV_Technisat;
      Serial.println("Schüler 4");
      carSpeedL = 210;
      carSpeedR = 230;
      break;
    case 5:
      IR_Remote_DEV = IR_Remote_DEV_Technisat;
      Serial.println("Schüler 5");
      break;
    case 6:
      IR_Remote_DEV = IR_Remote_DEV_Eleego;
      Serial.println("Schüler 6");
      forwardRightDelay = 50;
      break;
    case 7:
      IR_Remote_DEV = IR_Remote_DEV_Pinnacle;
      carSpeedR = 210;
      Serial.println("Eric");
      break;

    default: break;
  };
}




void setup() {
  Serial.begin(19200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


  pinMode (car_decode_pin_0, INPUT_PULLUP);
  pinMode (car_decode_pin_1, INPUT_PULLUP);
  pinMode (car_decode_pin_2, INPUT_PULLUP);


  // car identifizieren:
  if (digitalRead(car_decode_pin_0)) {
    carIdent = 1;
  }
  if (digitalRead(car_decode_pin_1)) {
    carIdent = carIdent + 2;
  }
  if (digitalRead(car_decode_pin_2)) {
    carIdent = carIdent + 4;
  }

  Serial.println(carIdent);
  carHardwareconfig (carIdent);
  irConfig (IR_Remote_DEV);

  servo_motor.attach(Servo_PIN); //our servo pin

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
  
  motor_links.setSpeed(carSpeedL);
  motor_rechts.setSpeed(carSpeedR);
  motor_links.run(RELEASE);
  motor_rechts.run(RELEASE);
  
}

void Lampensteuerung(int position, int Farbe)
{
  uint32_t c;
  int intensi = 1;
  switch (Farbe)
  {
    case rot:
      {
        Serial.println("rot");
        //    c= strip.Color(255, 0, 0);
        //    strip.setPixelColor(0, (strip.Color(0, 0, 255)), 50); // Red
        //   strip.setPixelColor(0, c); // Red

        strip.setPixelColor(position, 255, 0, 0, intensi); // Red
        break;
      }
    case green:
      {
        Serial.println("green");
        strip.setPixelColor(position, 0, 255, 0, intensi); // green
        break;
      }
    case white:
      {
        Serial.println("white");
        strip.setPixelColor(position, 255, 255, 255, intensi); // weiss
        break;
      }
    case blau:
      {
        Serial.println("blau");
        strip.setPixelColor(position, 0, 0, 255, intensi); // blau
        break;
      }
    default:
      {
        Serial.println("break");
        strip.setPixelColor(2, (strip.Color(255, 0, 0), intensi)); // Red
        break;
      }
  }
  strip.show();
}



void automatikBetrieb()
{
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 50) {
    stopp();
    delay(300);
    back();
    delay(400);
    stopp();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft) {
      turnRight();
      stopp();
    }
    else {
      turnLeft();
      stopp();
    }
  }
  else {
    forward();
  }
  distance = readPing();
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("DistanceLeft: ");
  Serial.println(distanceLeft);
  Serial.print("DistanceRight: ");
  Serial.println(distanceRight);
}



void loop() {
  if (irrecv.decode(&results)) {
    preMillis = millis();
    val = results.value;
    Serial.println(val, HEX);
    irrecv.resume();

 //   calibrateCarspeed(val);

    if (val == auto_on) {
      remoteOn = false;
    }
    if (val == auto_off) {
      remoteOn = true;
    }
    if ((val == vor) or (val == vor2)) {
      forward();
    }
    if ((val == zurueck) or (val == zurueck2)) {
      back();
    }
    if ((val == links) or (val == links2)) {
      left();
    }
    if ((val == rechts) or (val == rechts2)) {
      right();
    }
    if ((val == stoppen) or (val == stoppen2)) {
      stopp();
      remoteOn = true;
    }
  }
  else {
    if (millis() - preMillis > 500) {
      stopp();
      preMillis = millis();
    }
  }

  if (!remoteOn) {
    automatikBetrieb();
  }
}

void forward() {

//  Lampensteuerung(VorneRechts, white);
//  Lampensteuerung(VorneLinks, white);
  motor_links.run(FORWARD);
  motor_links.setSpeed(carSpeedL);
  motor_rechts.run(FORWARD);
  motor_rechts.setSpeed(carSpeedR);

  Serial.println("go forward!");
}
void back() {

//  Lampensteuerung(HintenRechts, rot);
//  Lampensteuerung(HintenLinks, rot);
  motor_links.run(BACKWARD);
  motor_links.setSpeed(carSpeedL);
  motor_rechts.run(BACKWARD);
  motor_rechts.setSpeed(carSpeedR);

  Serial.println("go back!");
}
void left() {
//  Lampensteuerung(VorneLinks, rot);
  motor_links.run(BACKWARD);
  motor_links.setSpeed(carSpeedL);
  motor_rechts.run(FORWARD);
  motor_rechts.setSpeed(carSpeedR);
  Serial.println("go left!");
}
void right() {

//  Lampensteuerung(VorneRechts, rot);
  motor_links.run(FORWARD);
  motor_links.setSpeed(carSpeedL);
  motor_rechts.run(BACKWARD);
  motor_rechts.setSpeed(carSpeedR);
  Serial.println("go right!");
}
void stopp() {

  strip.clear();
  strip.show();

  motor_links.run(RELEASE);
  motor_rechts.run(RELEASE);

//  Serial.println("STOP!");
}


int lookRight() {
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft() {
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void turnRight() {
  right();
  delay(250);
  forward();
}

void turnLeft() {
  left();
  delay(250);
  forward();
}
