/*
  Ampelprogramm
*/

// constants won't change. They're used here to set pin numbers:
// the number of the LED pin
const int LedRot = 12;
const int LedGelb =  11;
const int LedGruen = 10;
const int LedRot2 =  8;
const int LedGruen2 = 7;


void setup() {
  pinMode(LedRot, OUTPUT);
  pinMode(LedGelb, OUTPUT);
  pinMode(LedGruen, OUTPUT);
  pinMode(LedRot2, OUTPUT);
  pinMode(LedGruen2, OUTPUT);
 
 
}

void loop() {
  delay(20);
  digitalWrite(LedRot2, HIGH);
  digitalWrite(LedGruen2, LOW);
  digitalWrite(LedGruen, HIGH);
  digitalWrite(LedGelb, LOW);
  digitalWrite(LedRot, LOW);
  delay (10000);
  digitalWrite(LedGruen, LOW);
  digitalWrite(LedGelb, HIGH);
  delay (4000);
  digitalWrite(LedRot, HIGH);
  digitalWrite(LedGelb, LOW);
  delay (2000);
  digitalWrite(LedRot2, LOW);
  digitalWrite(LedGruen2, HIGH);
  delay (5000);
  digitalWrite(LedGelb, HIGH);
  digitalWrite(LedRot, LOW);
  digitalWrite(LedRot2, HIGH);
  digitalWrite (LedGruen2, LOW);
  delay (2000);
  }
