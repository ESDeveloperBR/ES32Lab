/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab
    
Objective:
- Simple reading of potentiometers 1, 2 and printing on serial terminal
*/

#include <Arduino.h>
#include <ES32Lab.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);

  pinMode(P_POT1, INPUT);
  pinMode(P_POT2, INPUT);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  int pot1 = analogRead(P_POT1);
  int pot2 = analogRead(P_POT2);

  Serial.print("pot1: ");
  Serial.print(pot1);
  Serial.print(" pot2:");
  Serial.println(pot2);

  delay(500);
}