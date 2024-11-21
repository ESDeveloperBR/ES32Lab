#ifndef DIGITALBUTTON_H
#define DIGITALBUTTON_H

#include <Arduino.h>

#define DIGITALBUTTON_VERSION "0.3.0 update 11/20/2024" // [mm/dd/yyyy]

// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
/**
 * Class DigitalButton
 * Provides functionality to handle digital button states (press, hold, release).
 * | 
 * Classe DigitalButton
 * Fornece funcionalidade para gerenciar estados de botões digitais (pressionar, segurar, soltar).
 */
class DigitalButton {
  private:
    int     _pin;             // Pin used for the button or sensor. | Pino usado pelo botão ou sensor.
    boolean _pullUp;          // Defines if pull-up is enabled. | Define se o pull-up está ativado.
    boolean _btPress = false; // Button pressed starts as "false". | Botão pressionado inicia como "false".
    boolean _btRelease = true;// Button released starts as "true". | Botão solto inicia como "true".

    boolean _isPinValid();     // Checks if the pin is valid for usage. | Verifica se o pino é válido para uso.

  public:
    DigitalButton(int pin = -1, boolean pullUp = false); // Constructor | Construtor
    boolean begin(int pin, boolean pullUp = false);      // Initializes the button. | Inicializa o botão.
    boolean begin();                                     // Initializes with the current pin. | Inicializa com o pino atual.
    boolean setPino(int pin, boolean pullUp = false);    // Sets the pin for the button. | Define o pino para o botão.

    boolean hold();   // Returns "true" while the button is held. | Retorna "true" enquanto o botão é segurado.
    boolean press();  // Returns "true" when the button is pressed. | Retorna "true" quando o botão é pressionado.
    boolean release();// Returns "true" when the button is released. | Retorna "true" quando o botão é solto.
};

#endif
