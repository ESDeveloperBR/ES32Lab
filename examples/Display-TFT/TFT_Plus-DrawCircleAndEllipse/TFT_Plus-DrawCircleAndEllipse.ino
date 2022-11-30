/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw circle and ellipse
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

    // -- drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color);
    display.drawCircle(20, 40, 15, TFT_YELLOW);

    // -- drawCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, uint32_t color);
    display.drawCircleHelper(60, 40, 15, 1, TFT_RED);
    display.drawCircleHelper(60, 40, 15, 2, TFT_BLUE);
    display.drawCircleHelper(60, 40, 15, 4, TFT_BROWN);
    display.drawCircleHelper(60, 40, 15, 8, TFT_GREEN);

    // -- fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
    display.fillCircle(100, 40, 15, TFT_PURPLE);

    // -- fillCircleHelper(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color);
    display.fillCircleHelper(20, 80, 15, 1, 10, TFT_BLUE);
    display.fillCircleHelper(20, 80, 15, 2, 10, TFT_YELLOW);

    display.fillCircleHelper(90, 80, 15, 1, 20, TFT_GREEN);
    display.fillCircleHelper(90, 80, 15, 2, 20, TFT_RED);

    // -- drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color);
    display.drawEllipse(30, 115, 25, 10, TFT_DARKGREEN);

    // -- fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color);
    display.fillEllipse(100, 115, 25, 10, TFT_CYAN);

}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {

}