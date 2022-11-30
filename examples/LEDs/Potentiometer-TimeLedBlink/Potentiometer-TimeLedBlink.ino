/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab
    
Objective:
- Alternately flashing the LEDs: Green (GPIO17), yellow (GPIO16), red (GPIO13), blue (GPIO12);
- Adjustment of the activation speed of LEDs by potentiometers;
*/

#include <Arduino.h>
#include <ES32Lab.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);
  pinMode(P_LED_GREEN , OUTPUT);
  pinMode(P_LED_YELLON, OUTPUT);
  pinMode(P_LED_RED   , OUTPUT);
  pinMode(P_LED_BLUE  , OUTPUT);

  pinMode(P_POT1, INPUT);
  pinMode(P_POT2, INPUT);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  int onTimer;
  onTimer = map(analogRead(P_POT1), 0, 4095, 1, 1000);

  int offTimer;
  offTimer = map(analogRead(P_POT2), 0, 4095, 1, 1000);

  Serial.print("onTime: ");
  Serial.print(onTimer);
  Serial.print(" offTimer:");
  Serial.println(offTimer);

  digitalWrite(P_LED_GREEN, HIGH);
  delay(onTimer);
  digitalWrite(P_LED_YELLON, HIGH);
  delay(onTimer);
  digitalWrite(P_LED_RED, HIGH);
  delay(onTimer);
  digitalWrite(P_LED_BLUE, HIGH);
  delay(onTimer);

  digitalWrite(P_LED_GREEN, LOW);
  delay(offTimer);
  digitalWrite(P_LED_YELLON, LOW);
  delay(offTimer);
  digitalWrite(P_LED_RED, LOW);
  delay(offTimer);
  digitalWrite(P_LED_BLUE, LOW);
  delay(offTimer);
}