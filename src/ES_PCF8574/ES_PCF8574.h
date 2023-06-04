#ifndef ES_PCF8574_H
#define ES_PCF8574_H

#include <Wire.h>
#include <Arduino.h>

#define ES_PCF8574_VERSION "0.2.0 update 06/03/2023"  // mm/dd/yyyy
#define EX0 0
#define EX1 1
#define EX2 2
#define EX3 3
#define EX4 4
#define EX5 5
#define EX6 6
#define EX7 7

class ES_PCF8574 {
  public:
    ES_PCF8574(uint8_t address);
    boolean begin();
    void digitalWrite(uint8_t pin, boolean value);
    uint8_t digitalRead(uint8_t pin);
    boolean btHold(uint8_t pin);
    boolean btPress(uint8_t pin);
    boolean btRelease(uint8_t pin);

  private:
    uint8_t _address;
    uint8_t _value;
    boolean _btPress[8] = {false, false, false, false, false, false, false, false}; // Button pressed starts with "false"
    boolean _btRelease[8] = {true, true, true, true, true, true, true, true}; // The button is released "True"  
};

#endif
