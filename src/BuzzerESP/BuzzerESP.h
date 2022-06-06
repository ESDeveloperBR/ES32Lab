#ifndef __BUZZERESP_h
#define __BUZZERESP_h

#include "Arduino.h"
#include "BuzzerESPNote.h"

class BuzzerESP {
    private:    
        int _pinBuzzer;
        int _channel;
        int _pause;
        
    public:
        BuzzerESP(int pinBuzzer, int channel = 0);
        void begin(int pause);
        void end(int pause);
        void sound(int note, int duration);
        void distortion(int noteFrom, int noteTo);
};

#endif
