
/* Virtuino Bluetooth example 1 without library (Completed code)
 * All the necessary code is included in this sketch
 * Supported boards: UNO, NANO, MINI and any other board with Software Serial connection
 * Example name = "Bluetooth example via Software serial port"
 * Created by Ilias Lamprou
 * Updated Jun 09 2019
 * This is the minimum code
 * Download latest Virtuino android app from the link: https://play.google.com/store/apps/details?id=com.virtuino_automations.virtuino
 */

// Code to use SoftwareSerial
#include <SoftwareSerial.h>
SoftwareSerial bluetoothSerial =  SoftwareSerial(2,3);   // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to bluetooth module TX pin   -  connect the arduino TX pin to bluetooth module RX pin.  

String inputBuffer = "";        // a String to store the incoming data

#define V_memorySize 32         // Virtuino V memory size (default is 32). You can increase it to 99 or to decrease it in case you want to reduce the memory
float V_memory[V_memorySize];   // create an array to store the V memory variables. This array will synchronized with Virtuino V memory

#define DV_memorySize 32        // Virtuino DV memory size (default is 32). You can increase it to 99 or to decrease it in case you want to reduce the memory
int DV_memory[DV_memorySize];   // create an array to store the DV memory variables. This array will synchronized with Virtuino DV memory

#define textVariablesCount 2
String textVariable[textVariablesCount];   // array with variables for storing the incoming from Virtuino text.
unsigned long t=0;


int oldState=-1;
int pwm_value=0;      // temp variable
//=================================================== setup
//===================================================
void setup() {
  // initialize serial:
  Serial.begin(9600);
  bluetoothSerial.begin(9600);    // This has to be the same with the bluetooth module serial baud rate
  
  inputBuffer.reserve(200); // reserve 200 bytes for the inputBuffer:
  pinMode(13,OUTPUT);       // On Virtuino panel add a switch to control this pin
  pinMode(6,INPUT);         // Connect a switch to this pin
  vMemoryWrite(5,23.45);    // Example: how to write an initial value to V memory 5. On Virtuino add a value display to V5 to read this value
  dvMemoryWrite(3,12);      // Example: how to write an initial value to DV memory 3. On Virtuino add a value display to DV3 to read this value
}

//=================================================== setup
//===================================================
void loop() {
  virtuinoRun();    // serial handler

  //-- example on how to send sensor values every 3 seconds to Virtuino
  if (millis()-t>3000) {    // every 3 seconds send the sensors' values to the Virtuino app
      vMemoryWrite(0,random(100));     // replace with your sensor variable. Write the sensor value to V memory 0
      dvMemoryWrite(0,random(100));    // replace with your sensor variable. Write the sensor value to DV memory 0
      t=millis();
  }

  //-- example on how to read a variable from Virtuino
   //-- example on how to read a variable from Virtuino
  if (oldState!=vMemoryRead(6)) {   // check if the state of the V6 has changed
    if (vMemoryRead(6)==1){ 
     // do something  
     Serial.println("V6=1");  // check the value of a Virtual pin
     sendCommand('M',0, "I love Virtuino");   // reply with a message
    }
    else {Serial.println("V6=0");}// do something else 
    oldState=vMemoryRead(6);   // store the last state
  }

  
  vDelay(1000);    // use this vDelay instead of the default delay()
}





//=================================================== onCommandReceived
//===================================================
/*This void is called every time the Virtuino app wants to enable or disable pin or to write values to variables
 */
void onCommandReceived(char type, int pin, String data){
  Serial.println("onCommandReceived: "+String(type)+" "+String(pin)+" "+data);
  switch (type){
    case 'V' :     // type: V memory  
         if ((pin>=0) & (pin<V_memorySize)) V_memory[pin]=data.toFloat();   // V0
    break;
    case 'D' :    // type: DV memory 
         if ((pin>=0) & (pin<DV_memorySize)) DV_memory[pin]=data.toInt();   // DV0
    break;
    case 'Q' :    // type: digital IO 
        if (data.toInt()==1) digitalWrite(pin,HIGH); 
        else digitalWrite(pin,LOW);
    break;
    case 'O' :    // type: PWM
        analogWrite(pin,data.toInt());
    break;
    case 'T' :    // type: Text
       if ((pin>=0) || (pin<textVariablesCount)) { 
         String s=data;
         s.replace("%21","!"); // the text charactes ! and $ are encoded on the received text
         s.replace("%24","$");
         textVariable[pin]=s;     
       }
    break;
    case 'C' : onConnected();
                data="My firmware code";   // Send a firmware code to the Virtuino app
      break;
  
    
  }
  sendCommand(type,pin,data);    // If the 'confirmation' option on the server settings is enable the code has to send a reply with the same command 
}

//=================================================== onConnected
//===================================================
//This void is called every time the Virtuino app is connected with the bluetooth module
void onConnected(){
  Serial.println("Connected");
  sendCommand('M',0, "Hello Virtuino");     // Send a message to the Virtuino app
                                            // The app will show the text as Toast message
  //sendCommand('V',2, 128);                // You can send from here some variables as starting values
}

//=================================================== onCommandReceivedForInfo
//===================================================
/*This void is called every time the Virtuino app wants to read the state of the digital IOs,
  variables, sensors, analog inputs, PWM pins
  You have to send a replay with the correct value or nothing
  V = V memory (float)
  D = DV memory (int)
  Q = Input or output state (0 or 1)
  A = Analog input value 
  O = Analog output value 
  T = text value
  C = on connected state
  */

void onCommandReceivedForInfo(char type, int pin){
  Serial.println("onCommandReceivedForInfo type="+String(type)+"  pin="+String(pin));
  switch (type){
    case 'V' :     // type: V memory 
        if ((pin>=0) & (pin<V_memorySize)) sendCommand('V',pin,String(V_memory[pin]));   // V1
    break;
    case 'D' :    // type: D memory 
         if ((pin>=0) & (pin<DV_memorySize)) sendCommand('D',pin, String(DV_memory[pin]));   // V1
    break;
    case 'A' :    // type: A analog input
        if (pin==0) sendCommand('A',pin, String (analogRead(A0)));   // A0
        else if (pin==1) sendCommand(type,pin,String(analogRead(A1)));   // A1
        else if (pin==2) sendCommand(type,pin,String(analogRead(A2)));   // A2
        // else if (pin==3) ...
        
    break;
    case 'Q' :    // type: digital IO 
        sendCommand('Q',pin, String (digitalRead(pin)));   // return the state of a digital pin
    break;
     case 'O' :    // type: PWM
          pwm_value = pulseIn(pin, HIGH);  // return the value of a pwm pin.  Avoid to use this code for PWM. Prefer to store the PWM value to a variable. 
          pwm_value = pwm_value /7.85;
          if ((pwm_value==0) & (digitalRead(pin)==HIGH)) pwm_value=255;
          sendCommand('O',pin, String (pwm_value));   // return the state of a PWM
    break;
 case 'T' :
        if ((pin>=0) || (pin<textVariablesCount)) { 
        String s=textVariable[pin];
        s.replace("!","%21"); // in case the textVariable contains the charactes ! or $ you have to encode them before the sending
        s.replace("$","%24");
        sendCommand('T',pin,s);      
        }
        
    break;
    
  }
 }

//=================================================== sendCommand
/* Call this void every time you want to send data to Virtuino app
 * Avoid to call this void on every cycle of void loop. 
 * Type can be a char like V, D, Q, A, O
 * V = V memory (float)
 * D = DV memory (int)
 * Q = Input or output state (0 or 1)
 * O = Analog output value (0-255)
 */
void sendCommand(char type, int pin, String data){
  bluetoothSerial.print('!');
  bluetoothSerial.print(type);
  if (pin<10) bluetoothSerial.print('0');
  bluetoothSerial.print(String(pin));
  bluetoothSerial.print('=');
  bluetoothSerial.print(data);
  bluetoothSerial.print('$');
}

//=================================================== virtuinoRun
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run on every cycle of void loop, so using delay inside loop can
  delay response. 
*/
void virtuinoRun(){
  while (bluetoothSerial.available()) {
    char inChar = (char)bluetoothSerial.read();
    Serial.print(inChar);
    if (inChar=='!') inputBuffer = "";
    else if (inChar=='$') {
      char type=inputBuffer.charAt(0);
      if (inputBuffer.charAt(3)=='='){
        int pin = inputBuffer.substring(1,3).toInt();
        if (inputBuffer.charAt(4)=='?') {
          onCommandReceivedForInfo(type,pin);
        }
        else onCommandReceived(type,pin,inputBuffer.substring(4));
      }
      inputBuffer = "";
      break;
    }
    else inputBuffer += inChar;
  }
}
//====================================================== vDelay
/* Use this void instead of the default Delay 
 * This void doesn't block the communication 
 */
void vDelay(int milliseconds){
   unsigned long m=millis();
   while (millis()-m<milliseconds) virtuinoRun();
}

//=====================================================
void vMemoryWrite(int pin,float value){
  if ((pin>=0) & (pin<V_memorySize)) V_memory[pin]=value; 
}
//=====================================================
float vMemoryRead(int pin){
  if ((pin>=0) & (pin<V_memorySize)) return V_memory[pin]; 
  else return 0;
}
//=====================================================
void dvMemoryWrite(int pin,int value){
  if ((pin>=0) & (pin<DV_memorySize)) DV_memory[pin]=value; 
}
//=====================================================
float dvMemoryRead(int pin){
  if ((pin>=0) & (pin<DV_memorySize)) return DV_memory[pin]; 
  else return 0;
}



