/*
  Button
    - 10K resistor attached to pin 2 from ground

*/

// constants won't change. They're used here to set pin numbers:
// the number of the LED pin
const int LedRot = 12;
const int LedGelb =  11;
const int LedGruen = 10;
const int LedRot2 =  8;
const int LedGruen2 = 7;

const int interruptPin = 2;
volatile int FussG = LOW;


void setup() {
  pinMode(LedRot, OUTPUT);
  pinMode(LedGelb, OUTPUT);
  pinMode(LedGruen, OUTPUT);
  pinMode(LedRot2, OUTPUT);
  pinMode(LedGruen2, OUTPUT);

  pinMode(interruptPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {
  delay(20);
  digitalWrite(LedRot2, HIGH);
  digitalWrite(LedGruen2, LOW);

  if (FussG) {
    delay(2000);
    digitalWrite(LedGelb, HIGH);
    digitalWrite(LedGruen, LOW);
    delay (2000);
    digitalWrite(LedRot, HIGH);
    digitalWrite(LedGelb, LOW);
    delay (2000);
    digitalWrite(LedGruen2, HIGH);
    digitalWrite(LedRot2, LOW);
    delay (5000);
    digitalWrite(LedGruen2, LOW);
    digitalWrite(LedRot2, HIGH);
    digitalWrite(LedGelb, HIGH);
    digitalWrite(LedRot, LOW);
    delay (4000);
    digitalWrite(LedGruen, LOW);

    FussG = LOW;
  }

  else {

    digitalWrite(LedRot, LOW);
    digitalWrite(LedGelb, LOW);
    digitalWrite(LedGruen, HIGH);
    digitalWrite(LedGruen2, LOW);
    digitalWrite(LedRot2, HIGH);


  }

}

void blink() {
  FussG = HIGH;
}
