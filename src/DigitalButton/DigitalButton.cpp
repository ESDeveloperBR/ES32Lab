#include "DigitalButton.h"

// <<<<<<<<<<<<<<<<<<< Construtor >>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Creates the object to be used as a digital button and assigns the GPIO to be used.
 * - pin: GPIO of the button. | GPIO do botão.
 * - pullUp: Enables pull-up resistor. Defaults to false. | Ativa o resistor pull-up. O padrão é false.
 */
DigitalButton::DigitalButton(int pin, boolean pullUp) {
    _pin = pin;            // Assign the GPIO pin. | Atribui o pino GPIO.
    _pullUp = pullUp;      // Assign pull-up configuration. | Atribui a configuração de pull-up.
}

// <<<<<<<<<<<<<<<<<<< Métodos de Inicialização >>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Checks if the pin is valid. GPIOs 34-39 are restricted. 
 * | 
 * Verifica se o pino é válido. GPIOs 34-39 são restritos.
 */
boolean DigitalButton::_isPinValid() {
    if (_pin >= 34 && _pin <= 39) { 
        return false; // Invalid pins. | Pinos inválidos.
    }
    return true;
}

/**
 * Initializes the button with the given pin and configuration.
 * - pin: GPIO of the button. | GPIO do botão.
 * - pullUp: Enables pull-up resistor. Defaults to false. | Ativa o resistor pull-up. O padrão é false.
 * Returns true if the pin is successfully configured. | Retorna true se o pino for configurado com sucesso.
 */
boolean DigitalButton::begin(int pin, boolean pullUp) {
    _pin = pin;            // Assign the pin. | Atribui o pino.
    _pullUp = pullUp;      // Set the pull-up configuration. | Define a configuração do pull-up.

    if (!_isPinValid()) { 
        return false; // Invalid pin. | Pino inválido.
    }

    pinMode(_pin, pullUp ? INPUT_PULLUP : INPUT); // Configures the pin. | Configura o pino.
    return true;
}

/**
 * Initializes the button with the stored pin and configuration.
 * | 
 * Inicializa o botão com o pino e configuração armazenados.
 */
boolean DigitalButton::begin() {
    return begin(_pin, _pullUp); // Calls the parameterized begin method. | Chama o método begin parametrizado.
}

/**
 * Sets the pin for the button and initializes it.
 * - pin: GPIO of the button. | GPIO do botão.
 * - pullUp: Enables pull-up resistor. Defaults to false. | Ativa o resistor pull-up. O padrão é false.
 */
boolean DigitalButton::setPino(int pin, boolean pullUp) {
    return begin(pin, pullUp); // Reuses begin logic. | Reutiliza a lógica do begin.
}

// <<<<<<<<<<<<<<<<<< Métodos de Estado >>>>>>>>>>>>>>>>>>>>>
/**
 * Returns "true" while the button is held.
 * | 
 * Retorna "true" enquanto o botão estiver pressionado.
 */
boolean DigitalButton::hold() {
    if (_pin < 0) return false; // Ensure pin is configured. | Garante que o pino esteja configurado.
    return !digitalRead(_pin); // Read pin state. | Lê o estado do pino.
}

/**
 * Returns "true" when the button is pressed.
 * | 
 * Retorna "true" quando o botão for pressionado.
 */
boolean DigitalButton::press() {
    if (hold() && !_btPress) { 
        _btPress = true; // Button pressed. | Botão pressionado.
        return true;
    }
    if (!hold()) _btPress = false; // Reset state. | Reseta o estado.
    return false;
}

/**
 * Returns "true" when the button is released.
 * | 
 * Retorna "true" quando o botão for solto.
 */
boolean DigitalButton::release() {
    if (!hold() && !_btRelease) { 
        _btRelease = true; // Button released. | Botão solto.
        return true;
    }
    if (hold()) _btRelease = false; // Reset state. | Reseta o estado.
    return false;
}
