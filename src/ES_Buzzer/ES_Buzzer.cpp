#include "ES_Buzzer.h"

// <<<<<<<<<< ES_Buzzer Constructor >>>>>>>>>>
/**
 * Constructor of the ES_Buzzer class. 
 * | Construtor da classe ES_Buzzer.
 * @param pinBuzzer The pin on the controller that supports PWM to be used for the buzzer circuit. | O pino do controlador que suporta PWM a ser utilizado para o circuito do buzzer.
 */
ES_Buzzer::ES_Buzzer(int8_t pinBuzzer) {
    _pinBuzzer = pinBuzzer;
}

// <<<<<<<<<< begin >>>>>>>>>>
/**
 * Initializes the ES_Buzzer instance that will be responsible for sound reproduction. 
 * | Inicializa a instância do ES_Buzzer que será responsável pela reprodução de sons.
 * @param channel The PWM channel to be used. If no channel is specified, the default channel will be 15. | O canal PWM a ser utilizado. Se não for especificado qual o canal, o canal padrão será o 15.
 */
void ES_Buzzer::begin(int8_t channel) {
    _channel = channel;
    pinMode(_pinBuzzer, OUTPUT);

    ledcSetup(_channel, 1000, 8); // Configures the PWM channel, initial frequency, and resolution in bits. | Configura o canal PWM, a frequência inicial e a resolução em bits.
    ledcAttachPin(_pinBuzzer, _channel);
}

// <<<<<<<<<< pitch >>>>>>>>>>
/**
 * Adjusts the playback speed of the generated melody, where values below 100% make the melody slower and values above 100% make it faster. 
 * | Ajusta a velocidade de reprodução da melodia gerada, onde valores abaixo de 100% tornam a melodia mais lenta e valores acima de 100% a tornam mais rápida.
 * @param percentage The percentage value to adjust the melody speed. | O valor em porcentagem para ajustar a velocidade da melodia.
 */
void ES_Buzzer::pitch(int8_t percentage) {
    _pitchPause = percentage;
}

// <<<<<<<<<< end >>>>>>>>>>
/**
 * Ends the melody and holds the last musical note for a specified time in milliseconds. 
 * | Finaliza a melodia e segura a última nota musical por um determinado tempo em milissegundos.
 * @param pause The time in milliseconds to hold the last musical note. | O tempo em milissegundos para segurar a última nota musical.
 */
void ES_Buzzer::end(int16_t pause) {
    delay(pause);
    ledcWriteTone(_channel, 0);
}

// <<<<<<<<<< sound >>>>>>>>>>
/**
 * Plays a musical note with a specified duration. 
 * | Reproduz uma nota musical com uma duração especificada.
 * @param note The musical note to be played. | A nota musical a ser reproduzida.
 * @param duration The duration in milliseconds of the chosen musical note. | A duração em milissegundos da nota musical escolhida.
 */
void ES_Buzzer::sound(int note, int duration) {
    ledcWriteTone(_channel, note);
    delay(duration);
    delay(((duration * _pitchPause) / 100));
    ledcWriteTone(_channel, 0);
}

// <<<<<<<<<< distortion >>>>>>>>>>
/**
 * Distortion effect between two musical notes. 
 * | Efeito de distorção entre duas notas musicais.
 * @param noteFrom The starting musical note. | A nota musical inicial.
 * @param noteTo The ending musical note. | A nota musical final.
 */
void ES_Buzzer::distortion(int noteFrom, int noteTo) {
    int nCycles = abs(noteFrom - noteTo);

    if (noteFrom > noteTo) {
        for (int i = 0; i < nCycles; i++) {
            sound(noteFrom - i, 10000 / nCycles);
        }
    } else {
        for (int i = 0; i < nCycles; i++) {
            sound(noteFrom + i, 10000 / nCycles);
        }
    }
}
