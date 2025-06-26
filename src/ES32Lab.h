#ifndef _ES32LAB_h
    #define _ES32LAB_h

    #include <Arduino.h>
    #define ES32LAB_VERSION "0.12.8 update 26/06/2025"   // dd/mm/yyyy

    // ---- Label impresso na ES32Lab ----
    #define P00      0
    #define P01      1
    #define P02      2
    #define P03      3
    #define P04      4
    #define P05      5
    #define P12     12
    #define P13     13
    #define P14     14
    #define P15     15
    #define P16     16
    #define P17     17
    #define P18     18
    #define P19     19 
    #define P21     21
    #define P22     22
    #define P23     23
    #define P25     25
    #define P26     26
    #define P27     27
    #define P32     32
    #define P33     33
    #define P34     34
    #define P35     35
    #define P36     36
    #define P39     39

    // ---- Serial ----
    #define TX0      1
    #define RX0      3

    // ---- i2S ----
    #define LCK     26
    #define DIN     25
    #define BCK     27

    // ---- i2C ----
    #define SDA     21
    #define SCL     22

    // ---- SPI ----
    #define MOSI    23
    #define MISO    19
    #define SCK     18

    // ---- SD ----
    #define CS_SD    5

    // ---- TFT ----
    #define CS_TFT  15
    #define DC_TFT   2
    #define A0_TFT   2
    #define DA_TFT  23
    #define CL_TFT  18

    // ---- Peripherals ----
    #define P_KEYBOARD  33
    #define P_LED_GREEN 17
    #define P_LED_YELLOW 16
    #define P_LED_RED   13
    #define P_LED_BLUE  12
    #define P_POT1      36
    #define P_POT2      39
    #define P_VOLT      34
    #define P_BUZZER    25
    #define P_DAC1      25  // Se a DAC for utilizada como áudio, será o canal L
    #define P_DAC2      26  // Se a DAC for utilizada como áudio, será o canal R


    // ---- Classe da LIB ES32Lab ----
    #include "ES_AnalogKeyboard/ES_AnalogKeyboardb.h"
    #include "ES_Buzzer/ES_Buzzer.h"
    #include "ES_File/ES_File.h"
    #include "ES_TimeInterval/ES_TimeInterval.h"
    #include "ES_DigitalButton/ES_DigitalButton.h"
    #include "ES_TFT/ES_TFT.h"
    #include "ES_PCF8574/ES_PCF8574.h"
    #include "ES_CarControl/ES_CarControl.h"
    #include "ES_Camera/ES_Camera.h"

    class ES32Lab {
        private:    
            //uint8_t  _pinKeyboard;      // Keyboard read pin 
        public:
            ES32Lab();
    };

#endif
