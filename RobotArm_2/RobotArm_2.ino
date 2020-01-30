#include <Servo.h>

Servo middle, left, right, claw ;  // erzeugt 4 "servo" Objekte

int middlePin = A1;  // Middle Pot Analog Input Pin
int leftPin = A0;  // Left Pot Analog Input Pin
int rightPin = A2;  // Right Pot Analog Input Pin
int clawPin = A3;  // Claw Pot Analog Input Pin


int middleValue[4] = {90, 90, 90, 90}; // Middle Pot Value
int leftValue[4] = {90, 90, 90, 90}; // Left Pot Value
int rightValue[4] = {90, 90, 90, 90}; // Right Pot Value
int clawValue[4] = {90, 90, 90, 90}; // Claw Pot Value

int pos = 0;  // Servo-Position

char blueToothVal; //Werte sollen per Bluetooth gesendet werden


void setup()
{
  Serial.begin(9600);
  middle.attach(5);  // "Middle" Servo wird an pin 11 angeschlossen
  left.attach(10);  // attaches the servo on pin 10 to the left object
  right.attach(9);  // attaches the servo on pin 9 to the right object
  claw.attach(6);  // attaches the servo on pin 6 to the claw object
}

void loop()
{
  // Read the Pot Values
  middleValue[0] = analogRead(middlePin);
  leftValue[0] = analogRead(leftPin);
  rightValue[0] = analogRead(rightPin);
  clawValue[0] = analogRead(clawPin);

  // Convert to values between 0 and 180 for the servos
  middleValue[0] = map(middleValue[0], 0, 1023, 0, 180) ;
  leftValue[0] = map(leftValue[0], 0, 1023, 0, 180) ;
  rightValue[0] = map(rightValue[0], 0, 1023, 0, 180) ;
  clawValue[0] = map(clawValue[0], 0, 1023, 0, 180) ;
 /*   Serial.println("left middle right claw: ");
    Serial.print(leftValue[0]);
    Serial.print("     ");

    Serial.print(middleValue[0]);
    Serial.print("     ");

    Serial.print(rightValue[0]);
    Serial.print("     ");

    Serial.println(clawValue[0]);
  */
  if (Serial.available()) //wenn Daten empfangen werden...
  {
    Serial.println("serial available");
    blueToothVal = Serial.read(); //..sollen diese ausgelesen werden
    int c = (int)blueToothVal - 48;
    Serial.println(c);
    switch (c) {
      case 1:

        middleValue[c] = middleValue[0]; // Middle Pot Value
        leftValue[c] = leftValue[0]; // Left Pot Value
        rightValue[c] = rightValue[0]; // Right Pot Value
        clawValue[c] = clawValue[0]; // Claw Pot Value

        break;
      case 2:
        pos = 1;
        break;
      case 3:
        middleValue[c] = middleValue[0]; // Middle Pot Value
        leftValue[c] = leftValue[0]; // Left Pot Value
        rightValue[c] = rightValue[0]; // Right Pot Value
        clawValue[c] = clawValue[0]; // Claw Pot Value

        break;
      case 4:
        pos = 3;
        break;
      case 5:

        break;
      case 6:
        pos = 0;
        break;

      default: break;
    }
  }




  // Write values to servos
  middle.write(middleValue[pos]); // Middle servo position
  left.write(leftValue[pos]); // Left servo position
  right.write(rightValue[pos]); // Right servo position
  claw.write(clawValue[pos]); // Claw servo position

  delay(20); // Short Delay
}
