/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 31/05/20222
  Ultima Alteração: 31/05/20222
  Versão: 0.1.0
*/
#ifndef __BUZZERESP_h
#define __BUZZERESP_h

#include "Arduino.h"

#define BUZZERESP_VERSION "0.1.1 update date 05/31/2022"
// <<<<<<<<<<<<<<< Classe BuzzerESP >>>>>>>>>>>>>>
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
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Constructor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Creates the object to be used as a buzzer and assigns the pin and channel to be used.
- pinBuzzer: Pin Buzzer;
- channel: optional ledcAttachPin channel;
*/
BuzzerESP::BuzzerESP(int pinBuzzer, int channel) {
    _pinBuzzer  = pinBuzzer;
    _channel    = channel;
    _pause      = 0;

    ledcAttachPin(_pinBuzzer, _channel);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<< Begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Sets the rest before the note.
- pause: Value in percentage;
*/
void BuzzerESP::begin(int pause) {
    _pause = pause;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<< End >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Hold the last note and end the melody.
-pause: Time in milliseconds;
*/
void BuzzerESP::end(int pause) {
    delay(pause);
    ledcWriteTone(_channel, 0);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<< Sound >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Play the musical note with the set tempo.
-note: Musical note;
-duration: Music note duration time in milliseconds; */
void BuzzerESP::sound(int note, int duration) {
    ledcWriteTone(_channel, note);
    delay(duration);
    delay(((duration * _pause) / 100));
}

// <<<<<<<<<<<<<<<<<<<<<<<<<< distortion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* It creates a distortion effect on the Buzzer */
void BuzzerESP::distortion(int noteFrom, int noteTo) {
    int nCycles = abs(noteFrom - noteTo);

    if (noteFrom > noteTo)
        for (int i = 0; i < nCycles; i++)
            sound(noteFrom - i, 10000 / nCycles);
    else
        for (int i = 0; i < nCycles; i++)
            sound(noteFrom + i, 10000 / nCycles);
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Notas >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define NOTE_C0  16
#define NOTE_CS0  17
#define NOTE_D0  18
#define NOTE_DS0  19
#define NOTE_E0  21
#define NOTE_F0  22
#define NOTE_FS0  23
#define NOTE_G0  25
#define NOTE_GS0  26
#define NOTE_A0  28
#define NOTE_AS0  29
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_E8 5274
#define NOTE_F8 5588
#define NOTE_FS8 5920
#define NOTE_G8 6272
#define NOTE_GS8 6645
#define NOTE_A8 7040
#define NOTE_AS8 7459
#define NOTE_B8 7902
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#endif
