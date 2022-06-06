/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ederjsantini/TFT_eSPI_ES32Lab

Objective:
- Flashing the green LED repeatedly
*/

#include <Arduino.h>
#include <ES32Lab.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  pinMode(P_LED_GREEN , OUTPUT);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);
  delay(500);

  digitalWrite(P_LED_GREEN, LOW);
  delay(500);
}