//  Include following libraries to access IR sensor
#include <IRremote.h>
#include <IRremoteInt.h>

// the number of the LED pin
const int LedRot = 11;
const int LedGelb = 10;
const int LedGruen = 9;
const int LedBlau = 8;

 

int RECV_PIN = 12;          //  The digital pin for the IR-Sensor

IRrecv receiver(RECV_PIN);  //  Create a new receiver object
decode_results results;     //  key code from receiver

void setup() {
  Serial.begin(9600);       //  Setup serial port
  pinMode(LedRot, OUTPUT);
  pinMode(LedGelb, OUTPUT);
  pinMode(LedGruen, OUTPUT);
  pinMode(LedBlau, OUTPUT);
  receiver.enableIRIn();    //  Enable receiver
}

void loop() {
  if(receiver.decode(&results)) {             //  Decode and put code "results"
    Serial.println(results.value, HEX);       //  Print the code as a hexadecimal value

    if (results.value == 0xC5F4A8B0) {          //  Key X1
       digitalWrite(LedRot, HIGH); }
       
    if (results.value == 0xF21169DD) {          //  Key X2
       digitalWrite(LedRot, LOW); }
       
    if (results.value == 0x96C6EC6A) {          //  Key X3
       digitalWrite(LedGelb, HIGH); }
       
    if (results.value == 0x89353C7F) {          //  Key X4
       digitalWrite(LedGelb, LOW); }
        
    receiver.resume();                        //  Continue listening for new signals
  }
}
