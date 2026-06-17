#ifndef ES_CAR_LINE_FOLLOWER_H
#define ES_CAR_LINE_FOLLOWER_H

#include <Arduino.h>
#include "ES_CarControl/ES_CarControl.h"
#include "ES_PCF8574/ES_PCF8574.h"
#include "ES_TimeInterval/ES_TimeInterval.h"

#define ES_CAR_LINE_FOLLOWER_VERSION "0.3.0 update 06/16/2026"  // mm/dd/yyyy

class ES_CarLineFollower {
  private:
    ES_CarControl* _car;       // Pointer to the car control object. | Ponteiro para o objeto de controle do carro.
    ES_PCF8574* _expander;     // Pointer to the PCF8574 I2C expander object. | Ponteiro para o objeto expansor I2C PCF8574.

    boolean _lineFollowerEnabled = false;     // Enables or disables automatic line following. | Habilita ou desabilita o seguidor de linha automatico.
    boolean _lineFollowerWasEnabled = false;  // Indicates the first update cycle after enabling. | Indica o primeiro ciclo de update depois da ativacao.

    uint8_t _leftPin = 0;   // PCF8574 pin connected to the left line sensor. | Pino do PCF8574 conectado ao sensor esquerdo de linha.
    uint8_t _rightPin = 0;  // PCF8574 pin connected to the right line sensor. | Pino do PCF8574 conectado ao sensor direito de linha.

    uint8_t _highSpeed = 20;  // Forward speed used after the robot is stable on the line. | Velocidade para frente usada depois que o robo estabiliza na linha.
    uint8_t _lowSpeed = 10;   // Forward speed used immediately after a correction. | Velocidade para frente usada imediatamente apos uma correcao.

    uint16_t _lowSpeedDuration = 2500;  // Time before returning from low speed to high speed. | Tempo antes de voltar da velocidade baixa para a velocidade alta.
    uint16_t _noLineDuration = 5000;    // Maximum time without sensor contact before stopping. | Tempo maximo sem contato dos sensores com a linha antes de parar.

    uint8_t _leftSpeed = 70;   // Turning speed used when the left sensor detects the line. | Velocidade de giro usada quando o sensor esquerdo detecta a linha.
    uint8_t _rightSpeed = 70;  // Turning speed used when the right sensor detects the line. | Velocidade de giro usada quando o sensor direito detecta a linha.

    ES_TimeInterval _lowSpeedInterval;  // Timer used to return to high speed after corrections. | Temporizador usado para retornar a velocidade alta apos correcoes.
    ES_TimeInterval _noLineInterval;    // Timer used to stop the robot when no line is detected. | Temporizador usado para parar o robo quando nenhuma linha e detectada.

    uint8_t _limitSpeed(uint8_t speed);  // Limits speed values to the 0-100 range. | Limita valores de velocidade para a faixa de 0 a 100.
    void _resetIntervals();              // Resets the internal timing intervals. | Reinicia os temporizadores internos.

  public:
    /**
     * @brief Constructor of the class | Construtor da classe
     * @param car Reference to the ES_CarControl object used to move the robot. | Referencia para o objeto ES_CarControl usado para mover o robo.
     * @param expander Reference to the ES_PCF8574 object used to read the line sensors. | Referencia para o objeto ES_PCF8574 usado para ler os sensores de linha.
     */
    ES_CarLineFollower(ES_CarControl &car, ES_PCF8574 &expander);

    /**
     * @brief Initializes the line follower with sensor pins and behavior parameters.
     * | Inicializa o seguidor de linha com os pinos dos sensores e parametros de comportamento.
     * @param leftPin PCF8574 pin connected to the left sensor. | Pino do PCF8574 conectado ao sensor esquerdo.
     * @param rightPin PCF8574 pin connected to the right sensor. | Pino do PCF8574 conectado ao sensor direito.
     * @param highSpeed Forward speed used when the robot is stable. | Velocidade para frente usada quando o robo esta estabilizado.
     * @param lowSpeed Forward speed used after leaving a correction. | Velocidade para frente usada apos sair de uma correcao.
     * @param lowSpeedDuration Time in milliseconds before returning to high speed. | Tempo em milissegundos antes de retornar para a velocidade alta.
     * @param noLineDuration Maximum time in milliseconds without line contact before stopping. | Tempo maximo em milissegundos sem contato com a linha antes de parar.
     * @param turnSpeed Turning speed applied to both left and right corrections. | Velocidade de giro aplicada as correcoes esquerda e direita.
     * @return true after storing the configuration. | true apos armazenar a configuracao.
     */
    boolean begin(uint8_t leftPin, uint8_t rightPin, uint8_t highSpeed = 20, uint8_t lowSpeed = 10,
                  uint16_t lowSpeedDuration = 2500, uint16_t noLineDuration = 5000, uint8_t turnSpeed = 70);

    /**
     * @brief Updates sensor readings and applies movement corrections. Call continuously in loop().
     * | Atualiza as leituras dos sensores e aplica correcoes de movimento. Chame continuamente no loop().
     */
    void update();

    /**
     * @brief Enables automatic line following and starts moving forward at high speed.
     * | Habilita o seguidor de linha automatico e inicia o movimento para frente na velocidade alta.
     */
    void enable();

    /**
     * @brief Disables automatic line following and stops the robot.
     * | Desabilita o seguidor de linha automatico e para o robo.
     */
    void disable();

    /**
     * @brief Sets the enabled status of the line follower.
     * | Define o status de ativacao do seguidor de linha.
     * @param status true to enable, false to disable. | true para habilitar, false para desabilitar.
     */
    void setEnabled(boolean status);

    /**
     * @brief Gets the enabled status of the line follower.
     * | Obtem o status de ativacao do seguidor de linha.
     * @return true if enabled, false otherwise. | true se estiver habilitado, false caso contrario.
     */
    boolean isEnabled();

    /**
     * @brief Gets the class version string.
     * | Obtem a string de versao da classe.
     * @return The ES_CarLineFollower version. | A versao da ES_CarLineFollower.
     */
    const char* getVersion();

    /**
     * @brief Sets the forward speed used when the robot is stable.
     * | Define a velocidade para frente usada quando o robo esta estabilizado.
     * @param speed Speed value from 0 to 100. | Valor de velocidade de 0 a 100.
     */
    void setHighSpeed(uint8_t speed);

    /**
     * @brief Gets the forward speed used when the robot is stable.
     * | Obtem a velocidade para frente usada quando o robo esta estabilizado.
     * @return Current high speed. | Velocidade alta atual.
     */
    uint8_t getHighSpeed();

    /**
     * @brief Sets the forward speed used after a correction.
     * | Define a velocidade para frente usada apos uma correcao.
     * @param speed Speed value from 0 to 100. | Valor de velocidade de 0 a 100.
     */
    void setLowSpeed(uint8_t speed);

    /**
     * @brief Gets the forward speed used after a correction.
     * | Obtem a velocidade para frente usada apos uma correcao.
     * @return Current low speed. | Velocidade baixa atual.
     */
    uint8_t getLowSpeed();

    /**
     * @brief Sets the time before returning to high speed after a correction.
     * | Define o tempo antes de retornar para a velocidade alta apos uma correcao.
     * @param duration Time in milliseconds. | Tempo em milissegundos.
     */
    void setLowSpeedDuration(uint16_t duration);

    /**
     * @brief Gets the time before returning to high speed after a correction.
     * | Obtem o tempo antes de retornar para a velocidade alta apos uma correcao.
     * @return Current duration in milliseconds. | Duracao atual em milissegundos.
     */
    uint16_t getLowSpeedDuration();

    /**
     * @brief Sets the maximum time without line contact before stopping.
     * | Define o tempo maximo sem contato com a linha antes de parar.
     * @param duration Time in milliseconds. | Tempo em milissegundos.
     * @note This is a heuristic because two side sensors cannot distinguish a centered line from a missing line.
     * | Esta e uma heuristica, pois dois sensores laterais nao distinguem linha centralizada de linha ausente.
     */
    void setNoLineDuration(uint16_t duration);

    /**
     * @brief Gets the maximum time without line contact before stopping.
     * | Obtem o tempo maximo sem contato com a linha antes de parar.
     * @return Current duration in milliseconds. | Duracao atual em milissegundos.
     */
    uint16_t getNoLineDuration();

    /**
     * @brief Sets the turning speed for left sensor corrections.
     * | Define a velocidade de giro para correcoes do sensor esquerdo.
     * @param speed Speed value from 0 to 100. | Valor de velocidade de 0 a 100.
     */
    void setLeftSpeed(uint8_t speed);

    /**
     * @brief Gets the turning speed for left sensor corrections.
     * | Obtem a velocidade de giro para correcoes do sensor esquerdo.
     * @return Current left correction speed. | Velocidade atual de correcao esquerda.
     */
    uint8_t getLeftSpeed();

    /**
     * @brief Sets the turning speed for right sensor corrections.
     * | Define a velocidade de giro para correcoes do sensor direito.
     * @param speed Speed value from 0 to 100. | Valor de velocidade de 0 a 100.
     */
    void setRightSpeed(uint8_t speed);

    /**
     * @brief Gets the turning speed for right sensor corrections.
     * | Obtem a velocidade de giro para correcoes do sensor direito.
     * @return Current right correction speed. | Velocidade atual de correcao direita.
     */
    uint8_t getRightSpeed();

    /**
     * @brief Sets the same turning speed for both left and right corrections.
     * | Define a mesma velocidade de giro para as correcoes esquerda e direita.
     * @param speed Speed value from 0 to 100. | Valor de velocidade de 0 a 100.
     */
    void setTurnSpeed(uint8_t speed);
};

#endif
