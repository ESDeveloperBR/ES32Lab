#ifndef __ESBUZZER_h
#define __ESBUZZER_h

#include "Arduino.h"
#include "ES_BuzzerNote.h"

#define ES_BUZZER_VERSION "0.5.0 update 07/03/2023"  // mm/dd/yyyy

class ES_Buzzer {
    private:    
        u_int8_t _pinBuzzer;
        u_int8_t _channel;     
        u_int8_t _pitchPause = 100; 
        
    public:
        ES_Buzzer(u_int8_t pinBuzzer);
        void begin(u_int8_t channel = 15);
        void pitch(u_int8_t percentage);
        void end(u_int16_t pause);
        void sound(int note, int duration);
        void distortion(int noteFrom, int noteTo);
};

#endif
