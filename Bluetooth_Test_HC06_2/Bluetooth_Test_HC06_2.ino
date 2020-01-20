
char blueToothVal; //Werte sollen per Bluetooth gesendet werden
char lastValue;   //speichert den letzten Status der LED (on/off)
int LedRot = 11;
int LedGelb = 10;
int LedGruen = 9;

void setup() {
  Serial.begin(9600);  //serieller Monitor wird gestartet, Baudrate auf 9600 festgelegt
 
  pinMode(LedRot, OUTPUT);
  pinMode(LedGelb, OUTPUT);
  pinMode(LedGruen, OUTPUT);

  Serial.println("setup:");
}

void loop() {
  if (Serial.available()) //wenn Daten empfangen werden...
  {
    Serial.println("serial available");
    blueToothVal = Serial.read(); //..sollen diese ausgelesen werden
    int c = (int)blueToothVal;
    Serial.println(c);
    switch (c) {
      case 49:
        digitalWrite(LedRot, HIGH);
        Serial.println(F("LED is on"));
        break;
      case 50:
        digitalWrite(LedRot, LOW);
        Serial.println(F("LED is off"));
        break;
      case 51:
        digitalWrite(LedGelb, HIGH);
        Serial.println(F("LED is on"));
        break;
      case 52:
        digitalWrite(LedGelb, LOW);
        Serial.println(F("LED is off"));
        break;
      case 53:
        digitalWrite(LedGruen, HIGH);
        Serial.println(F("LED is on"));
        break;
      case 54:
        digitalWrite(LedGruen, LOW);
        Serial.println(F("LED is off"));
        break;

      default: break;
    }
  }
}
