/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw rectangle
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

    // -- Draw Rectangle -----------------------
    display.drawRect(10, 20, 35, 35, TFT_MAGENTA);

    // -- Round corner rectangle ---------------------------
    display.drawRoundRect(50, 20, 35, 35, 5, TFT_RED);

    // -- Create a rectangle with round corner fill --------
    display.fillRoundRect(90, 20, 35, 35, 5, TFT_PURPLE);

    // -- Vertical gradient rectangle fill -----------------
    display.fillRectVGradient(10, 70, 35, 35, TFT_WHITE, TFT_BLUE);

    // -- Horizontal gradient rectangle fill -----------------
    display.fillRectHGradient(55, 70, 35, 35, TFT_WHITE, TFT_BLUE);
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {

}