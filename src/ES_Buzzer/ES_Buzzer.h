#ifndef __ESBUZZER_h
#define __ESBUZZER_h

#include "Arduino.h"
#include "ES_BuzzerNote.h"

#define ES_BUZZER_VERSION "0.5.2 update 08/08/2024"  // mm/dd/yyyy

class ES_Buzzer {
    private:    
        int8_t _pinBuzzer;
        int8_t _channel;     
        int8_t _pitchPause = 100; 
        
    public:
        ES_Buzzer(int8_t pinBuzzer);
        void begin(int8_t channel = 15);
        void pitch(int8_t percentage);
        void end(int16_t pause);
        void sound(int note, int duration);
        void distortion(int noteFrom, int noteTo);
};

#endif
