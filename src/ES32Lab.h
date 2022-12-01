#ifndef _ES32LAB_h
    #define _ES32LAB_h

    #include <Arduino.h>
    #define ES32LAB_VERSION "0.7.9 update 01/12/2022"   // dd/mm/yyyy

    #define P_KEYBOARD      33
    #define P_LED_GREEN     17
    #define P_LED_YELLON    16
    #define P_LED_RED       13
    #define P_LED_BLUE      12
    #define P_POT1          36
    #define P_POT2          39
    #define P_VOLTAGE_SENSOR 34
  
    #define P_BUZZER        25
    #define P_DAC1          25  // Se a DAC for utilizada como audío, será o canal L
    #define P_DAC2          26  // Se a DAC for utilizada como audío, será o canal R
    //Pinos de conexão do ESP32-I2S e o módulo I2S/DAC CJMCU 1334
    #define P_I2S_DOUT      25  // Azul
    #define P_I2S_LRC       26  // Verde
    #define P_I2S_BCLK      27  // Laranja

    #define P_SDA           21
    #define P_SCL           22

    #define P_TX0           1
    #define P_RX0           3
    #define P_TX2           17
    #define P_RX2           16

    #define P_MOSI          23
    #define P_MISSO         19
    #define P_SCK           18
    #define P_SD_CS         5
    
    #include "AnalogKeyboard/AnalogKeyboardb.h"
    #include "BuzzerESP/BuzzerESP.h"
    #include "FileManager/FileManager.h"
    #include "TimeInterval/TimeInterval.h"
    #include "DigitalButton/DigitalButton.h"
    #include "TFT_Plus/TFT_Plus.h"

    class ES32Lab {
        private:    
            //uint8_t  _pinKeyboard;      // Keyboard read pin 
        public:
            ES32Lab();
    };

#endif
