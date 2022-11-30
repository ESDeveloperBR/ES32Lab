/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab
    
Objective:
- Use the "TimeInterval" class that manages the time through the "intervalMillis()" command, not stopping the code in execution;

Objetivo:
- Utilizar a classe "TimeInterval" que gerencia o tempo através do comando "intervalMillis()", não parando o código em execução;
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
    boolean TimeInterval::intervalMillis(long millisTime)
    Returns "true" when the time in milliseconds has elapsed
    - millisTime: Time in milliseconds
  */
  if(intervalTest.intervalMillis(2000)){  // Execute command every 2000 milliseconds
    Serial.println("It's not stopping the main loop.");
  }

}