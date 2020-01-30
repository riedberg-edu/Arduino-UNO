// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(4);
int speed = 200;
int d = 3000;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(speed);

  Serial.println("RELEASE");
  motor.run(RELEASE);
  delay (d);
}

void loop() {
  uint8_t i;
  Serial.println(' ');
  Serial.println("FORWARD");
  motor.run(FORWARD);
  motor.setSpeed(speed);
  delay(d);

  Serial.println("RELEASE");
  motor.run(RELEASE);
  delay(d);
  
  Serial.println("BRAKE");
  motor.run(BRAKE);
  delay(d);


  Serial.println("BACKWARD");
  motor.run(BACKWARD);
  motor.setSpeed(speed);
  delay(d);

 Serial.println("BRAKE");
  motor.run(BRAKE);
  delay(d+5000);



  Serial.println("RELEASE");
  motor.run(RELEASE);
  delay(d);

  delay (20000);
}
