#ifndef __ESBUZZER_h
#define __ESBUZZER_h

#include "Arduino.h"
#include "ES_BuzzerNote.h"
#include <driver/ledc.h>

#define ES_BUZZER_VERSION "0.7.5 update 03/27/2025"  // mm/dd/yyyy

class ES_Buzzer {
    private:   
        int8_t  _pinBuzzer;     // Buzzer pin | Pino do buzzer
        int8_t  _channel;       // Uses the last available channel by default (LEDC_CHANNEL_7) | Utiliza o último canal disponível por padrão (LEDC_CHANNEL_7)
        uint8_t _duty = 50;     // Duty cycle default 50% | Duty cycle padrão 50%
        uint8_t _speed = 100;   // Playback speed percentage (100% = original speed) | Fator percentual de tempo (100% = tempo original)
        uint8_t _pitch = 100;   // Pitch adjustment percentage (100% = normal) | Fator de ajuste da frequência das notas (100% = normal)

    public:
        ES_Buzzer(int8_t pinBuzzer = 25);
        void begin(int8_t channel = 7);
        void sound(int note, int duration);
        void end(int16_t pause = 0);

        void setVolume(int pecentage);
        int getVolume();

        void setSpeed(int percentage);
        int getSpeed();

        void setPitch(int percentage);
        int getPitch();

        void setPitchAndSpeed(int percentage);
};

#endif
