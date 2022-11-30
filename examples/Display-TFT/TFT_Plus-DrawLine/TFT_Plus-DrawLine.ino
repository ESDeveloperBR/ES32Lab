/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- Draw line
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
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
int x, y;
void loop() {
    // ------ drawPixel ------------------
    display.drawPixel(x, y, TFT_WHITE);
    x++;
    y++;
        
    // ------ drawLine -------------------
    display.drawLine(35, 40, 100, 5, TFT_RED);

    // -- drawFastVLine: The drawFastVLine method prints a line vertically -------------------
    display.drawFastVLine(20, 50, 40, TFT_BLUE);

    // -- drawFastHLine: The drawFastHLine method prints a line horizontal -------------------
    display.drawFastHLine(20, 50, 40, TFT_GREEN);

    delay(500);
}