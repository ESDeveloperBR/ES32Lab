/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Basic commands
*/
#include <Arduino.h>
#include <ES32Lab.h>

TFT_Plus display;
// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************

void setup() {
  display.begin();
  display.setRotation(3);           // Rotacao da tela
  display.fillScreen(TFT_BLUE);     // Fundo da tela
  display.setTextColor(TFT_WHITE);  // Cor do texto
  display.setCursor(10, 30);        // Possicao do cursor
  display.println("ES32Lab");       // Imprime e pula para a proxima linha
  display.print("Version: ");       // Imprime no display e não pula para uma nova linha
  display.println(ES32LAB_VERSION); // Imprime e pula para a proxima linha
  
  delay(4000);
  display.fillScreen(TFT_YELLOW);   // Fundo da tela
  display.setTextColor(TFT_RED);// Cor do texto
  display.setCursor(0, 0);        // Possicao do cursor
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {
  display.println("Hello World");
  delay(2000);
}