/*
Author: Eder João Santini
email: ederjsantini@gmail.com
Library Download: https://github.com/ederjsantini/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ederjsantini/TFT_eSPI_ES32Lab
    
Objective:
- Use the "TimeInterval" class that manages the time through the "micros()" command, not stopping the code in execution;

Objetivo:
- Utilizar a classe "TimeInterval" que gerencia o tempo através do comando "micros()", não parando o código em execução;
*/

#include <Arduino.h>
#include <ES32Lab.h>

TimeInterval intervalTest;

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  /*
    boolean TimeInterval::intervalMicros(long microsTime)
    Returns "true" when the time in microseconds has elapsed
    - microsTime: Time in microseconds
  */
  if(intervalTest.intervalMicros(2000000)){  // Execute command every 2000000 microseconds
    Serial.println("It's not stopping the main loop.");
  }
}