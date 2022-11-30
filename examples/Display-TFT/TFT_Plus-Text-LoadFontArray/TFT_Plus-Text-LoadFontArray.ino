/*
Author: Eder Joao Santini
email: esdeveloperbr@gmail.com
Library Download: https://github.com/ESDeveloperBR/ES32Lab

ATTENTION: ES32Lab depends on the library download
  - TFT_eSPI_ES32Lab
    https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab

Example of using the CLASS TFT_Plus
- loadFontArray commands
*/
#include <Arduino.h>
#include <ES32Lab.h>

#include <FontsArray/Final_Frontier_28.h>
#include <FontsArray/Latin_Hiragana_24.h>
#include <FontsArray/NotoSansBold15.h>
#include <FontsArray/NotoSansBold36.h>
#include <FontsArray/NotoSansMonoSCB20.h>
#include <FontsArray/Unicode_Test_72.h>

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
}

// ********************************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ********************************************************************************************************
void loop() {
    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(Final_Frontier_28);
    display.println("Final_Frontier_28");
    delay(3000);

    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(Latin_Hiragana_24);
    display.println("Latin_Hiragana_24");
    delay(3000);
    
    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(NotoSansBold15);
    display.println("NotoSansBold15");
    delay(3000);

    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(NotoSansBold36);
    display.println("NotoSansBold36");
    delay(3000);

    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(NotoSansMonoSCB20);
    display.println("NotoSansMonoSCB20");
    delay(3000);

    display.fillScreen(TFT_BLACK);
    display.setCursor(0, 0);
    display.loadFontArray(Unicode_Test_72);
    display.println("Unicode_Test_72");
    delay(3000);
}