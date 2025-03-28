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
 * @param channel The PWM channel to be used. If no channel is specified, the default channel will be 7. | O canal PWM a ser utilizado. Se não for especificado qual o canal, o canal padrão será o 7.
 */
void ES_Buzzer::begin(int8_t channel) {
    _channel = channel;
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 1000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num = _pinBuzzer,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = static_cast<ledc_channel_t>(_channel),
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

// <<<<<<<<<< sound >>>>>>>>>>
/**
 * Plays a musical note with a specified duration. 
 * | Reproduz uma nota musical com uma duração especificada.
 * @param note The musical note to be played. | A nota musical a ser reproduzida.
 * @param duration The duration in milliseconds of the chosen musical note. | A duração em milissegundos da nota musical escolhida.
 */
void ES_Buzzer::sound(int note, int duration) {
    if (note <= 0) {
        delay(duration * (100.0 / _speed)); // Pausa sem som
        return;
    }

    int adjustedFreq = note * (_pitch / 100.0);
    adjustedFreq = constrain(adjustedFreq, 4, 3910);   // Contrains the frequency to a valid range. | Limita a frequência a uma faixa válida.

    ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, static_cast<uint32_t>(adjustedFreq));
    ledc_set_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(_channel), map(_duty, 0, 100, 0, 255));
    ledc_update_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(_channel));
    delayMicroseconds((duration * (100.0 / _speed)) * 1000);
    ledc_stop(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(_channel), 0);
}

// <<<<<<<<<< end >>>>>>>>>>
/**
 * Ends the melody and pauses execution for a specified time in milliseconds. 
 * | Finaliza a melodia e pausa a execução por um determinado tempo em milissegundos.
 * @param pause The time in milliseconds to pause execution. The default value is 0. | O tempo em milissegundos para pausar a execução. O valor padrão é 0.
 */
void ES_Buzzer::end(int16_t pause) {
    ledc_stop(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(_channel), 0);
    delay(pause);
}

// <<<<<<<<<< setVolume >>>>>>>>>>
/**
 * Sets the output volume of the buzzer by adjusting the PWM duty cycle.
 * | Define o volume de saída do buzzer ajustando o duty cycle do PWM.
 * @param percentage Volume percentage from 0 to 100. | Percentual de volume de 0 a 100.
 */
void ES_Buzzer::setVolume(int percentage) {
    _duty = constrain(percentage, 0, 100);
}

// <<<<<<<<<< getVolume >>>>>>>>>>
/**
 * Returns the current volume percentage based on PWM duty cycle.
 * | Retorna o volume atual em percentual baseado no duty cycle do PWM.
 * @return Volume percentual de 0 a 100. | Percentual do volume de 0 a 100.
 */
int ES_Buzzer::getVolume() {
    return _duty;
}

// <<<<<<<<<< setSpeed >>>>>>>>>>
/**
 * Sets the playback speed percentage for note execution.
 * | Define a velocidade de reprodução em percentual para a execução das notas (100 = velocidade original).
 * @param percentage The playback speed percentage. | O percentual de velocidade a ser aplicado na duração das notas.
 */
void ES_Buzzer::setSpeed(int percentage) {
    _speed = constrain(percentage, 1, 255);
}

// <<<<<<<<<< getSpeed >>>>>>>>>>
/**
 * Gets the current playback speed percentage.
 * | Retorna o valor atual da velocidade de reprodução em percentual.
 * @return The current speed percentage. | O valor percentual atual da velocidade de reprodução.
 */
int ES_Buzzer::getSpeed(){
    return _speed;
}

// <<<<<<<<<< setPitch >>>>>>>>>>
/**
 * Sets the pitch adjustment percentage (100 = normal pitch).
 * | Define o fator percentual de ajuste de pitch (100 = tom original).
 * @param percentage The pitch percentage. | O percentual do pitch a ser aplicado nas notas.
 */
//void ES_Buzzer::setPitch(float percentage) {
void ES_Buzzer::setPitch(int percentage) {
    _pitch = constrain(percentage, 1, 255);
    //Serial.printf("Pitch: %d\n", _pitch);
}

// <<<<<<<<<< getPitch >>>>>>>>>>
/**
 * Gets the current pitch adjustment percentage.
 * | Retorna o valor atual do ajuste de pitch em percentual.
 * @return The current pitch percentage. | O valor percentual atual do pitch.
 */
//float ES_Buzzer::getPitch() {
int ES_Buzzer::getPitch() {
    return _pitch;
}

// <<<<<<<<<< setPitchAndSpeed >>>>>>>>>>
/**
 * Adjusts pitch and synchronously updates playback speed to reflect realistic tonal behavior.
 * | Ajusta o tom e sincroniza automaticamente a velocidade de reprodução para refletir um comportamento musical realista.
 * @param percentage The adjustment percentage (100 = original). | O percentual de ajuste (100 = original).
 */
void ES_Buzzer::setPitchAndSpeed(int percentage) {
    setPitch(percentage);
    setSpeed(percentage);
}