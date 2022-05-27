/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  Project: ES32-LAB
  Author: Eder Joao Santini
  GitHub: https://github.com/ederjsantini

  Objective:
  - Alternately flashing the LEDs: Green (GPIO17), yellow (GPIO16), red (GPIO13), blue (GPIO12);
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

#include <Arduino.h>
#include <ES32Lab.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  pinMode(P_LED_GREEN , OUTPUT);
  pinMode(P_LED_YELLON, OUTPUT);
  pinMode(P_LED_RED   , OUTPUT);
  pinMode(P_LED_BLUE  , OUTPUT);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);
  delay(500);
  digitalWrite(P_LED_YELLON, HIGH);
  delay(500);
  digitalWrite(P_LED_RED, HIGH);
  delay(500);
  digitalWrite(P_LED_BLUE, HIGH);
  delay(500);

  digitalWrite(P_LED_GREEN, LOW);
  delay(500);
  digitalWrite(P_LED_YELLON, LOW);
  delay(500);
  digitalWrite(P_LED_RED, LOW);
  delay(500);
  digitalWrite(P_LED_BLUE, LOW);
  delay(500);
}