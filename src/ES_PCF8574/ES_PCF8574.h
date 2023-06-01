#ifndef ES_PCF8574_H
#define ES_PCF8574_H

#include <Wire.h>
#include <Arduino.h>

#define ES_PCF8574_VERSION "0.1.1 update 06/01/2023"  // mm/dd/yyyy
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

  private:
    uint8_t _address;
    uint8_t _value;
};

#endif
