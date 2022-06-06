#include "BuzzerESP.h"

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