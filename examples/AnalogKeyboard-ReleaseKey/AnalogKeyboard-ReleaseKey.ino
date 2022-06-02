/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab
Example of using the CLASS AnalogKeyboard.
- Release key.
*/
#include <Arduino.h>
#include <ES32Lab.h>

AnalogKeyboard keyboard(P_KEYBOARD);

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void setup() {
  Serial.begin(115200);

}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {
  if(keyboard.release(0)){
    Serial.println("Key 0 - RELASE");
  }
  if(keyboard.release(1)){
    Serial.println("Key 1 - RELASE");
  }
  if(keyboard.release(2)){
    Serial.println("Key 2 - RELASE");
  }
  if(keyboard.release(3)){
    Serial.println("Key 3 - RELASE");
  }
  if(keyboard.release(4)){
    Serial.println("Key 4 - RELASE");
  }
}