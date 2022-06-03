/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ederjsantini/TFT_eSPI_ES32Lab

  - JPEGDecoder
    https://github.com/ederjsantini/JPEGDecoder_ES32Lab

Example of using the CLASS AnalogKeyboard.
- Hold down key.
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

  if(keyboard.hold(0)){
    Serial.println("Key 0 - HOLD");
  }
  if(keyboard.hold(1)){
    Serial.println("Key 1 - HOLD");
  }
  if(keyboard.hold(2)){
    Serial.println("Key 2 - HOLD");
  }
  if(keyboard.hold(3)){
    Serial.println("Key 3 - HOLD");
  }
  if(keyboard.hold(4)){
    Serial.println("Key 4 - HOLD");
  }

}