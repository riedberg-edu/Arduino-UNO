#include <Servo.h>

Servo Drehen, left, right, Zange ;  // Creates 4 "servo objects"

int DrehenPin = A1;  // Drehen Pot Analog Input Pin
int leftPin = A0;  // Left Pot Analog Input Pin
int rightPin = A2;  // Right Pot Analog Input Pin
int ZangePin = A3;  // Zange Pot Analog Input Pin


int DrehenValue[5] = {90, 90, 90, 90, 90}; // Drehen Pot Value
int leftValue[5] = {90, 90, 90, 90, 90}; // Left Pot Value
int rightValue[5] = {90, 90, 90, 90, 90}; // Right Pot Value
int ZangeValue[5] = {90, 90, 90, 90, 90}; // Zange Pot Value

int pos = 0;  // Servo-Position

/*
   pos 0 ist Ausgangsstellung
   pos 1 für Stellung 1 Speicher
   pos 2 für Potistellung
   pos 3 für Stellung 2 Speicher
   pos 4 für letzte Stellung
*/
int Ausgangsstellung = 0;
int Stellung1 = 1;
int Stellung2 = 3;
int Potistellung = 2;
int letzteStellung = 4;



char blueToothVal; //Werte sollen per Bluetooth gesendet werden


void setup()
{
  Serial.begin(9600);
  Drehen.attach(5);  // attaches the servo on pin 11 to the Drehen object
  left.attach(10);  // attaches the servo on pin 10 to the left object
  right.attach(9);  // attaches the servo on pin 9 to the right object
  Zange.attach(6);  // attaches the servo on pin 6 to the Zange object
  pos = Potistellung;
}

void loop()
{
  // Read the Pot Values
  DrehenValue[Potistellung] = analogRead(DrehenPin);
  leftValue[Potistellung] = analogRead(leftPin);
  rightValue[Potistellung] = analogRead(rightPin);
  ZangeValue[Potistellung] = analogRead(ZangePin);

  // Convert to values between 0 and 180 for the servos
  DrehenValue[Potistellung] = map(DrehenValue[Potistellung], 0, 1023, 180, 0) ;
  leftValue[Potistellung] = map(leftValue[Potistellung], 0, 1023, 0, 180) ;
  rightValue[Potistellung] = map(rightValue[Potistellung], 0, 1023, 0, 180) ;
  ZangeValue[Potistellung] = map(ZangeValue[Potistellung], 0, 1023, 0, 180) ;




  /*   Serial.println("left Drehen right Zange: ");
     Serial.print(leftValue[0]);
     Serial.print("     ");

     Serial.print(DrehenValue[0]);
     Serial.print("     ");

     Serial.print(rightValue[0]);
     Serial.print("     ");

     Serial.println(ZangeValue[0]);
  */
  if (Serial.available()) //wenn Daten empfangen werden...
  {
    Serial.println("serial available");
    blueToothVal = Serial.read(); //..sollen diese ausgelesen werden
    int c = (int)blueToothVal - 48;
    Serial.println(c);
    switch (c) {
      case 1:
        DrehenValue[Stellung1] = DrehenValue[Potistellung]; // Drehen Pot Value
        leftValue[Stellung1] = leftValue[Potistellung]; // Left Pot Value
        rightValue[Stellung1] = rightValue[Potistellung]; // Right Pot Value
        ZangeValue[Stellung1] = ZangeValue[Potistellung]; // Zange Pot Value
        break;
      case 2:
        pos = Stellung1;
        break;
      case 3:
        DrehenValue[Stellung2] = DrehenValue[Potistellung]; // Drehen Pot Value
        leftValue[Stellung2] = leftValue[Potistellung]; // Left Pot Value
        rightValue[Stellung2] = rightValue[Potistellung]; // Right Pot Value
        ZangeValue[Stellung2] = ZangeValue[Potistellung]; // Zange Pot Value
        break;
      case 4:
        pos = Stellung2;
        break;
      case 5:
        pos = Potistellung;
        break;
      case 6:
        pos = Ausgangsstellung;
        break;
      default: break;
    }
  }

 /* Serial.print("Poti:     ");
  Serial.print(leftValue[2]);
  Serial.print("   ");
  Serial.print(DrehenValue[2]);
  Serial.print("   ");
  Serial.print(rightValue[2]);
  Serial.print("   ");
  Serial.println(ZangeValue[2]);
*/
  // Write values to servos

  if (DrehenValue[pos] > DrehenValue[letzteStellung]) {
    DrehenValue[letzteStellung] += 1;
  };
  if (DrehenValue[pos] < DrehenValue[letzteStellung]) {
    DrehenValue[letzteStellung] -= 1;
  };

  if (leftValue[pos] > leftValue[letzteStellung]) {
    leftValue[letzteStellung] += 1;
  };
  if (leftValue[pos] < leftValue[letzteStellung]) {
    leftValue[letzteStellung] -= 1;
  };

  if (rightValue[pos] > rightValue[letzteStellung]) {
    rightValue[letzteStellung] += 1;
  };
  if (rightValue[pos] < rightValue[letzteStellung]) {
    rightValue[letzteStellung] -= 1;
  };

  Drehen.write(DrehenValue[letzteStellung]); // Drehen servo position
  left.write(leftValue[letzteStellung]); // Left servo position
  right.write(rightValue[letzteStellung]); // Right servo position
  Zange.write(ZangeValue[Potistellung]); // Zange servo position

/*
  Serial.print("Ziel:     ");
  Serial.print(leftValue[4]);
  Serial.print("   ");
  Serial.print(DrehenValue[4]);
  Serial.print("   ");
  Serial.print(rightValue[4]);
  Serial.print("   ");
  Serial.println(ZangeValue[2]);
  Serial.println("   ");
*/
  //  Drehen.write(90); // Drehen servo position
  //  left.write(90); // Left servo position
  //  right.write(90); // Right servo position
  //  Zange.write(90); // Zange servo position

  delay (20); // Short Delay
}
