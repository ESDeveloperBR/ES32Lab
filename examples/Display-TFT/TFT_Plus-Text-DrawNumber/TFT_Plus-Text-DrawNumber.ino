/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw Number
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

    // -- drawNumber(long intNumber, int32_t x, int32_t y);
    display.drawNumber(5+5, 50, 20);

    // -- drawNumber(long intNumber, int32_t x, int32_t y, uint8_t font);
    display.drawNumber(10+5, 50, 30, 2);

    float floatNum = 5.0 / 2;
    // -- drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y);
    display.drawFloat(floatNum, 2, 50, 70);

    // -- drawFloat(float floatNumber, uint8_t decimal, int32_t x, int32_t y);
    display.drawFloat((4.1234 * 2), 3, 50, 80, 2);
}
// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {

}