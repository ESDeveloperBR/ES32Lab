/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab
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