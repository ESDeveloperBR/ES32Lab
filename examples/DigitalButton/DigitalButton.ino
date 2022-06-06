/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ederjsantini/TFT_eSPI_ES32Lab

Objective:
Shows all stages of a button:
- Press;
- Release;
- Hold;

Objetivo:
Mostra todos os estágios de um botão:
- Pressionar;
- Soltar;
- Segurar;
*/

#include <Arduino.h>
#include <ES32Lab.h>
DigitalButton testButton;

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);
  testButton.setPino(12);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  if(testButton.press()){
    Serial.println("Button - Press");
  }

  if(testButton.release()){
    Serial.println("Button - Release");
  }
  if(testButton.hold()){
    Serial.println("Button - Hold");
  }

}