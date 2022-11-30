/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw String
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

    // -- drawString(const char *string, int32_t x, int32_t y);
    display.drawString("drawString", 10, 20);

    // -- drawString(const char *string, int32_t x, int32_t y, uint8_t font);
    display.drawString("drawString", 10, 30, 2);

    // -- drawRightString(const char *string, int32_t x, int32_t y, uint8_t font);
    display.drawRightString("drawRightString", 160, 52, 1);

    // -- drawCentreString(const char *string, int32_t x, int32_t y, uint8_t font);
    display.drawCentreString("drawCentreString", 80, 70, 1);

    // -- drawCentreScreenString(const char *string, int32_t y, uint8_t font);
    display.drawCentreScreenString("drawCentreScreenString", 85, 2);

    // -- drawRightScreenString(const char *string, int32_t y, uint8_t font);
    display.drawRightScreenString("drawRightScreenString", 110, 1);

}
// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {

}