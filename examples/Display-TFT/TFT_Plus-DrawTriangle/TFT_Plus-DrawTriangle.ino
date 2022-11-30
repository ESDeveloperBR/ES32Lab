/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw Triangle
*/
#include <Arduino.h>
#include <ES32Lab.h>

TFT_Plus display;
// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void setup() {
    display.begin();
    display.setRotation(3);           // Screen rotation
    display.fillScreen(TFT_BLUE);     // Fill Screen
    display.setTextColor(TFT_WHITE);
    display.setCursor(10, 30);
    display.println("TFT_Plus Version");
    display.println(TFT_PLUS_VERSION);  // Print the version of the TFT_Plus class
  
    delay(5000);
    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.print("Height: " + String(display.height()));
    display.println(" x Width: " + String(display.width()));

    // -- drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);
    display.drawTriangle(40, 20, 20, 40, 60, 40, TFT_RED);

    // -- fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);
    display.fillTriangle(110, 20, 90, 40, 130, 40, TFT_BLUE);
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
int cont = 0;
int x = 64;
int y = 80;
void loop() {
    display.fillTriangle(80, 72-cont, 60-cont, 92+cont, 100+cont, 92+cont, TFT_YELLOW);
    if(cont < 25){
        cont++;
    }
    delay(50);
}