/**
 * @file ES_DigitalButton.h
 * @brief Digital button and binary sensor helper for native GPIO pins.
 * | Classe auxiliar para botões digitais e sensores binários em GPIOs nativas.
 *
 * This class simplifies the detection of three common digital input states:
 * press, hold and release.
 *
 * | Esta classe simplifica a detecção de três estados comuns de uma entrada digital:
 * pressionado, segurado e solto.
 */
#ifndef ES_DIGITALBUTTON_H
#define ES_DIGITALBUTTON_H

#include <Arduino.h>

#define ES_DIGITALBUTTON_VERSION "0.5.1 update 06/17/2026" // [mm/dd/yyyy]

/**
 * @class ES_DigitalButton
 * @brief Handles digital buttons and binary sensors connected to native GPIO pins.
 * | Gerencia botões digitais e sensores binários conectados às GPIOs nativas.
 *
 * The GPIO pin and active logic are configured in the begin() method. This keeps the
 * constructor simple and makes hardware setup explicit inside setup().
 *
 * | O pino GPIO e a lógica ativa são configurados no método begin(). Isso mantém o
 * construtor simples e deixa a configuração de hardware explícita dentro do setup().
 *
 * The activeHigh parameter defines the active logic of the button or sensor:
 * - activeHigh = true: the input is active when digitalRead() returns HIGH.
 * - activeHigh = false: the input is active when digitalRead() returns LOW.
 *
 * | O parâmetro activeHigh define a lógica ativa do botão ou sensor:
 * - activeHigh = true: a entrada está ativa quando digitalRead() retorna HIGH.
 * - activeHigh = false: a entrada está ativa quando digitalRead() retorna LOW.
 *
 * @note When activeHigh is true, the class tries to configure the pin as INPUT_PULLDOWN.
 * When activeHigh is false, the class tries to configure the pin as INPUT_PULLUP.
 * Some ESP32 GPIOs may not support internal pull-up or pull-down resistors. In these
 * cases, use an external resistor in the circuit.
 *
 * | Quando activeHigh é true, a classe tenta configurar o pino como INPUT_PULLDOWN.
 * Quando activeHigh é false, a classe tenta configurar o pino como INPUT_PULLUP.
 * Algumas GPIOs do ESP32 podem não suportar resistores internos de pull-up ou pull-down.
 * Nesses casos, utilize um resistor externo no circuito.
 *
 * @warning This class does not implement debounce filtering. If the physical button
 * presents bouncing, apply hardware debounce or handle it in the application logic.
 *
 * | Esta classe não implementa filtro de debounce. Se o botão físico apresentar ruído
 * mecânico, aplique debounce por hardware ou trate isso na lógica da aplicação.
 */
class ES_DigitalButton {
  private:
    int     _pin = -1;              // Pin used for the button or sensor. | Pino usado pelo botão ou sensor.
    boolean _activeHigh = true;     // Active logic of the input. | Lógica ativa da entrada.
    boolean _btPress = false;       // Internal state used by press(). | Estado interno usado por press().
    boolean _btRelease = true;      // Internal state used by release(). | Estado interno usado por release().

    /**
     * @brief Checks if the configured GPIO number is valid.
     * | Verifica se o número da GPIO configurada é válido.
     *
     * @return true if the pin number is valid, false otherwise.
     * | Verdadeiro se o número do pino é válido, falso caso contrário.
     */
    boolean _isPinValid();

  public:
    /**
     * @brief Constructor of the class.
     * | Construtor da classe.
     *
     * The constructor does not configure any GPIO. Use begin() to define the pin and
     * the active logic of the button or sensor.
     *
     * | O construtor não configura nenhuma GPIO. Use begin() para definir o pino e
     * a lógica ativa do botão ou sensor.
     */
    ES_DigitalButton();

    /**
     * @brief Initializes the digital button or binary sensor.
     * | Inicializa o botão digital ou sensor binário.
     *
     * @param pin GPIO pin connected to the button or sensor.
     * | Pino GPIO conectado ao botão ou sensor.
     * @param activeHigh Defines the active logic. Use true for active HIGH and false for active LOW.
     * | Define a lógica ativa. Use true para ativo em HIGH e false para ativo em LOW.
     * @return true if the pin was accepted and configured, false otherwise.
     * | Verdadeiro se o pino foi aceito e configurado, falso caso contrário.
     *
     * @note activeHigh defaults to true, so a simple begin(pin) call assumes an active HIGH input.
     * | activeHigh tem true como padrão, então uma chamada simples begin(pin) considera entrada ativa em HIGH.
     */
    boolean begin(int pin, boolean activeHigh = true);

    /**
     * @brief Initializes the button using the currently stored configuration.
     * | Inicializa o botão usando a configuração armazenada atualmente.
     *
     * @return true if the stored pin was accepted and configured, false otherwise.
     * | Verdadeiro se o pino armazenado foi aceito e configurado, falso caso contrário.
     */
    boolean begin();

    /**
     * @brief Sets the GPIO pin and active logic, then initializes the input.
     * | Define o pino GPIO e a lógica ativa, depois inicializa a entrada.
     *
     * @param pin GPIO pin connected to the button or sensor.
     * | Pino GPIO conectado ao botão ou sensor.
     * @param activeHigh Defines the active logic. Use true for active HIGH and false for active LOW.
     * | Define a lógica ativa. Use true para ativo em HIGH e false para ativo em LOW.
     * @return true if the pin was accepted and configured, false otherwise.
     * | Verdadeiro se o pino foi aceito e configurado, falso caso contrário.
     */
    boolean setPin(int pin, boolean activeHigh = true);

    /**
     * @brief Legacy alias for setPin().
     * | Alias legado para setPin().
     *
     * @param pin GPIO pin connected to the button or sensor.
     * | Pino GPIO conectado ao botão ou sensor.
     * @param activeHigh Defines the active logic. Use true for active HIGH and false for active LOW.
     * | Define a lógica ativa. Use true para ativo em HIGH e false para ativo em LOW.
     * @return true if the pin was accepted and configured, false otherwise.
     * | Verdadeiro se o pino foi aceito e configurado, falso caso contrário.
     *
     * @note Prefer setPin() in new projects.
     * | Prefira setPin() em novos projetos.
     */
    boolean setPino(int pin, boolean activeHigh = true);

    /**
     * @brief Checks if the input is currently active.
     * | Verifica se a entrada está ativa no momento.
     *
     * @return true while the button or sensor is active, false otherwise.
     * | Verdadeiro enquanto o botão ou sensor está ativo, falso caso contrário.
     */
    boolean hold();

    /**
     * @brief Detects the moment when the input becomes active.
     * | Detecta o momento em que a entrada é acionada.
     *
     * @return true only once when the input changes from inactive to active.
     * | Verdadeiro apenas uma vez quando a entrada muda de inativa para ativa.
     */
    boolean press();

    /**
     * @brief Detects the moment when the input is released.
     * | Detecta o momento em que a entrada é solta.
     *
     * @return true only once when the input changes from active to inactive.
     * | Verdadeiro apenas uma vez quando a entrada muda de ativa para inativa.
     */
    boolean release();
};

#endif
