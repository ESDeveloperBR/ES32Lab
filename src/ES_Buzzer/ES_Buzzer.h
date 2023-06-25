#ifndef __ESBUZZER_h
#define __ESBUZZER_h

#include "Arduino.h"
#include "ES_BuzzerNote.h"

class ES_Buzzer {
    private:    
        int _pinBuzzer;
        int _channel;
        int _pause;
        
    public:
        ES_Buzzer(int pinBuzzer, int channel = 0);
        void begin(int pause);
        void end(int pause);
        void sound(int note, int duration);
        void distortion(int noteFrom, int noteTo);
};

#endif
