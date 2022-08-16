/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 05/31/20222
*/

#ifndef _ANALOGKEYBOARD_h
#define _ANALOGKEYBOARD_h

#include <Arduino.h>

#define ANALOGKEYBOARD_VERSION "0.3.5 date 16/08/2022" // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe AnalogKeyboard >>>>>>>>>>>>>>
class AnalogKeyboard {
    private:    
        uint8_t  _pinKeyboard;      // Keyboard read pin 
        uint16_t _addressKey[5];    // Key analog address
        boolean  _keyPress[5] = {false, false, false, false, false};      // Checks if the key is pressed
        boolean  _keyRelease[5] = {true, true, true, true, true};      // Checks if the key is release
        uint8_t  _readingAccuracy;  // Reading accuracy over established analog values
    
    public:
        AnalogKeyboard(uint8_t pinKeyboard, uint16_t addressKey0 = 0, uint16_t addressKey1 = 870, uint16_t addressKey2 = 1657, uint16_t addressKey3 = 2457, uint16_t addressKey4 = 3322, uint8_t readingAccuracy = 21 );
        boolean hold(uint8_t key);
        boolean press(uint8_t key);
        boolean release(uint8_t key);

};
#endif
