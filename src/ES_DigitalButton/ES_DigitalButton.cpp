#include "ES_DigitalButton.h"

// <<< Constructor of the class | Construtor da classe >>>
ES_DigitalButton::ES_DigitalButton() {
}


// <<< Checks if the configured GPIO is valid | Verifica se a GPIO configurada é válida >>>
boolean ES_DigitalButton::_isPinValid() {
    return (_pin >= 0);
}


// <<< Initializes the digital input | Inicializa a entrada digital >>>
boolean ES_DigitalButton::begin(int pin, boolean activeHigh) {
    _pin = pin;                    // Set the GPIO pin | Define o pino GPIO
    _activeHigh = activeHigh;      // Set the active logic | Define a lógica ativa

    if (!_isPinValid()) {
        return false;              // Invalid pin | Pino inválido
    }

    /*
     * Active HIGH inputs should rest in LOW, so the class tries to enable INPUT_PULLDOWN.
     * Active LOW inputs should rest in HIGH, so the class tries to enable INPUT_PULLUP.
     *
     * | Entradas ativas em HIGH devem repousar em LOW, por isso a classe tenta usar INPUT_PULLDOWN.
     * Entradas ativas em LOW devem repousar em HIGH, por isso a classe tenta usar INPUT_PULLUP.
     */
    pinMode(_pin, _activeHigh ? INPUT_PULLDOWN : INPUT_PULLUP);

    _btPress = false;              // Reset press state | Reinicia o estado de acionamento
    _btRelease = true;             // Reset release state | Reinicia o estado de liberação

    return true;
}


// <<< Initializes using the stored configuration | Inicializa usando a configuração armazenada >>>
boolean ES_DigitalButton::begin() {
    return begin(_pin, _activeHigh);
}


// <<< Sets the GPIO pin and initializes the input | Define o pino GPIO e inicializa a entrada >>>
boolean ES_DigitalButton::setPin(int pin, boolean activeHigh) {
    return begin(pin, activeHigh);
}


// <<< Legacy alias for setPin() | Alias legado para setPin() >>>
boolean ES_DigitalButton::setPino(int pin, boolean activeHigh) {
    return setPin(pin, activeHigh);
}


// <<< Checks if the input is active | Verifica se a entrada está ativa >>>
boolean ES_DigitalButton::hold() {
    if (!_isPinValid()) {
        return false;
    }

    boolean pinState = digitalRead(_pin);       // Read current GPIO state | Lê o estado atual da GPIO
    return _activeHigh ? pinState : !pinState;  // Apply active logic | Aplica a lógica ativa
}


// <<< Detects when the input becomes active | Detecta quando a entrada é acionada >>>
boolean ES_DigitalButton::press() {
    if (hold() && !_btPress) {
        _btPress = true;           // Store pressed state | Armazena o estado pressionado
        return true;
    }

    if (!hold()) {
        _btPress = false;          // Release allows a new press event | A liberação permite um novo evento de press()
    }

    return false;
}


// <<< Detects when the input is released | Detecta quando a entrada é solta >>>
boolean ES_DigitalButton::release() {
    if (!hold() && !_btRelease) {
        _btRelease = true;         // Store released state | Armazena o estado solto
        return true;
    }

    if (hold()) {
        _btRelease = false;        // Press allows a new release event | O acionamento permite um novo evento de release()
    }

    return false;
}
