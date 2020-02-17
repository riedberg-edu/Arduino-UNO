/*
  BlinkLed

  eine LED wird wiederholt ein- und ausgeschaltet
 
*/
int LedRot = 8;  // Anschluss 8 des Arduino Boards benutzen

// Die setup function wird zu Beginn einmal ausgeführt
void setup() {
  // initialisiert digital pin LedRot als output.
  pinMode(LedRot, OUTPUT);
}

// Die loop function wird ständig wiederholt
void loop() {
  digitalWrite(LedRot, HIGH);   // schaltet LedRot ein
  delay(1000);                       // warten
  digitalWrite(LedRot, LOW);    // schaltet LedRot aus
  delay(1000);                       // warten
}


