#include <Arduino.h>
#include <ES32Lab.h>

TFT_eSPI tft = TFT_eSPI();
// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************

void setup() {
  Serial.begin(115200);
  
  tft.begin();
  tft.setRotation(3);         // Rotacao da tela
  tft.fillScreen(TFT_BLUE);   // Fundo da tela
  tft.setTextColor(TFT_WHITE);// Cor do texto
  tft.setCursor(10, 30);      // Possicao do cursor
  tft.println("ES32Lab");   // Imprime e pula para a proxima linha
  tft.print("Version: ");     // Imprime no display e não pula para uma nova linha
  tft.println(ES32LAB_VERSION);   // Imprime e pula para a proxima linha
  
  delay(4000);
  tft.fillScreen(TFT_YELLOW);   // Fundo da tela
  tft.setTextColor(TFT_RED);// Cor do texto
  tft.setCursor(0, 0);        // Possicao do cursor
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {
  tft.println("Hello World");
  delay(2000);
}