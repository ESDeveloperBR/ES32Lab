#ifndef ES_CARCONTROL_H
#define ES_CARCONTROL_H

#include <Arduino.h>
#include "ES_PCF8574/ES_PCF8574.h"
#include "ES_Buzzer/ES_Buzzer.h"

#define ES_CAR_CONTROL_VERSION "0.4.4 update 06/16/2026" // mm/dd/yyyy

#define DIFFERENTIAL 0 // Differential steering mode | Modo de direção diferencial
#define FRONTAL 1      // Front steering mode | Modo de direção dianteira

class ES_CarControl {
  private:
    ES_PCF8574* _pcf8574;
    ES_Buzzer*  _buzzer;

    uint8_t _drivingMode;
    uint8_t _currentSpeed = 20;
    uint8_t _speedDelay;
    uint8_t _motor1Pin1;
    uint8_t _motor1Pin2;
    uint8_t _motor2Pin1;
    uint8_t _motor2Pin2;
    uint8_t _frontLightsPin;
    uint8_t _backLightsPin;

    uint8_t _stop;
    uint8_t _forward;
    uint8_t _back;
    uint8_t _left;
    uint8_t _right;
    uint8_t _forwardLeft;
    uint8_t _forwardRight;
    uint8_t _backLeft;
    uint8_t _backRight;
    uint8_t _frontLightsOn;
    uint8_t _frontLightsOff;
    uint8_t _backLightsOn;
    uint8_t _backLightsOff;
    uint8_t _hornOn;
    uint8_t _hornOff;
    uint8_t _extraOn;
    uint8_t _extraOff;

    uint8_t _speed0, _speed1, _speed2, _speed3, _speed4, _speed5, _speed6, _speed7, _speed8, _speed9, _speed10;

    // boolean _invertDirection = false;
    // boolean _invertTraction  = false;

    // External function pointers | Ponteiros para funções externas
    void (*_customHornFunction)(bool) = nullptr;
    void (*_customFrontLightsFunction)(bool) = nullptr;
    void (*_customBackLightsFunction)(bool) = nullptr;
    void (*_customExtraFunction)(bool) = nullptr;

    // Movement function pointers | Ponteiros para funções associadas aos movimentos
    void (*_customForwardFunction)(uint8_t) = nullptr;
    void (*_customBackwardFunction)(uint8_t) = nullptr;
    void (*_customLeftFunction)(uint8_t) = nullptr;
    void (*_customRightFunction)(uint8_t) = nullptr;
    void (*_customForwardLeftFunction)(uint8_t) = nullptr;
    void (*_customForwardRightFunction)(uint8_t) = nullptr;
    void (*_customBackLeftFunction)(uint8_t) = nullptr;
    void (*_customBackRightFunction)(uint8_t) = nullptr;

  public:
    /**
     * @brief Constructor using a PCF8574 pointer. The buzzer remains disabled. (This version is obsolete and will be discontinued).
     * | Construtor usando um ponteiro para PCF8574. A buzina permanece desabilitada. (Esse versão é obsoleta e será descontinuada).
     * @param pcf8574 Pointer to an `ES_PCF8574` object used to control the motors and digital outputs. Use `nullptr` when no expander is used.
     * | Ponteiro para um objeto `ES_PCF8574` usado para controlar os motores e saídas digitais. Use `nullptr` quando nenhum expansor for utilizado.
     */
    ES_CarControl(ES_PCF8574* pcf8574);

    /**
     * @brief Constructor using PCF8574 and buzzer pointers. (This version is obsolete and will be discontinued).
     * | Construtor usando ponteiros para PCF8574 e buzina. (Esse versão é obsoleta e será descontinuada).
     * @param pcf8574 Pointer to an `ES_PCF8574` object used to control the motors and digital outputs. Use `nullptr` when no expander is used.
     * | Ponteiro para um objeto `ES_PCF8574` usado para controlar os motores e saídas digitais. Use `nullptr` quando nenhum expansor for utilizado.
     * @param buzzer Pointer to an `ES_Buzzer` object used for sound output. Use `nullptr` when no buzzer is used.
     * | Ponteiro para um objeto `ES_Buzzer` usado para saída sonora. Use `nullptr` quando nenhuma buzina for utilizada.
     */
    ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer);

    /**
     * @brief Constructor using a PCF8574 reference. The buzzer remains disabled.
     * | Construtor usando uma referência para PCF8574. A buzina permanece desabilitada.
     * @param pcf8574 Reference to an `ES_PCF8574` object used to control the motors and digital outputs.
     * | Referência para um objeto `ES_PCF8574` usado para controlar os motores e saídas digitais.
     */
    ES_CarControl(ES_PCF8574 &pcf8574);

    /**
     * @brief Constructor using PCF8574 and buzzer references.
     * | Construtor usando referências para PCF8574 e buzina.
     * @param pcf8574 Reference to an `ES_PCF8574` object used to control the motors and digital outputs.
     * | Referência para um objeto `ES_PCF8574` usado para controlar os motores e saídas digitais.
     * @param buzzer Reference to an `ES_Buzzer` object used for sound output.
     * | Referência para um objeto `ES_Buzzer` usado para saída sonora.
     */
    ES_CarControl(ES_PCF8574 &pcf8574, ES_Buzzer &buzzer);

    /**
     * @brief Initializes the car with motor pins, driving mode, command mapping, lights, buzzer and speed commands.
     * | Inicializa o carro com os pinos dos motores, modo de direção, mapeamento de comandos, luzes, buzina e comandos de velocidade.
     * @param drivingMode Driving mode. Use `DIFFERENTIAL` for differential steering or `FRONTAL` for front steering. | Modo de direção. Use `DIFFERENTIAL` para direção diferencial ou `FRONTAL` para direção dianteira.
     * @param motor1Pin1 First control pin of motor 1. | Primeiro pino de controle do motor 1.
     * @param motor1Pin2 Second control pin of motor 1. | Segundo pino de controle do motor 1.
     * @param motor2Pin1 First control pin of motor 2. | Primeiro pino de controle do motor 2.
     * @param motor2Pin2 Second control pin of motor 2. | Segundo pino de controle do motor 2.
     * @param frontLightsPin Output pin used for the front lights. | Pino de saída usado para as luzes dianteiras.
     * @param backLightsPin Output pin used for the back lights. | Pino de saída usado para as luzes traseiras.
     * @param stop Command character used to stop the car. | Caractere de comando usado para parar o carro.
     * @param forward Command character used to move forward. | Caractere de comando usado para mover para frente.
     * @param back Command character used to move backward. | Caractere de comando usado para mover para trás.
     * @param left Command character used to turn left. | Caractere de comando usado para virar à esquerda.
     * @param right Command character used to turn right. | Caractere de comando usado para virar à direita.
     * @param forwardLeft Command character used to move forward while turning left. | Caractere de comando usado para mover para frente virando à esquerda.
     * @param forwardRight Command character used to move forward while turning right. | Caractere de comando usado para mover para frente virando à direita.
     * @param backLeft Command character used to move backward while turning left. | Caractere de comando usado para mover para trás virando à esquerda.
     * @param backRight Command character used to move backward while turning right. | Caractere de comando usado para mover para trás virando à direita.
     * @param frontLightsOn Command character used to turn the front lights on. | Caractere de comando usado para ligar as luzes dianteiras.
     * @param frontLightsOff Command character used to turn the front lights off. | Caractere de comando usado para desligar as luzes dianteiras.
     * @param backLightsOn Command character used to turn the back lights on. | Caractere de comando usado para ligar as luzes traseiras.
     * @param backLightsOff Command character used to turn the back lights off. | Caractere de comando usado para desligar as luzes traseiras.
     * @param hornOn Command character used to turn the horn on. | Caractere de comando usado para ligar a buzina.
     * @param hornOff Command character used to turn the horn off. | Caractere de comando usado para desligar a buzina.
     * @param extraOn Command character used to enable the extra output. | Caractere de comando usado para ativar a saída extra.
     * @param extraOff Command character used to disable the extra output. | Caractere de comando usado para desativar a saída extra.
     * @param speedDelay Percentage applied to the slower motor during smooth turns. | Percentual aplicado ao motor mais lento durante curvas suaves.
     * @param speed0 Command character used to set speed to 0%. | Caractere de comando usado para ajustar a velocidade para 0%.
     * @param speed1 Command character used to set speed to 10%. | Caractere de comando usado para ajustar a velocidade para 10%.
     * @param speed2 Command character used to set speed to 20%. | Caractere de comando usado para ajustar a velocidade para 20%.
     * @param speed3 Command character used to set speed to 30%. | Caractere de comando usado para ajustar a velocidade para 30%.
     * @param speed4 Command character used to set speed to 40%. | Caractere de comando usado para ajustar a velocidade para 40%.
     * @param speed5 Command character used to set speed to 50%. | Caractere de comando usado para ajustar a velocidade para 50%.
     * @param speed6 Command character used to set speed to 60%. | Caractere de comando usado para ajustar a velocidade para 60%.
     * @param speed7 Command character used to set speed to 70%. | Caractere de comando usado para ajustar a velocidade para 70%.
     * @param speed8 Command character used to set speed to 80%. | Caractere de comando usado para ajustar a velocidade para 80%.
     * @param speed9 Command character used to set speed to 90%. | Caractere de comando usado para ajustar a velocidade para 90%.
     * @param speed10 Command character used to set speed to 100%. | Caractere de comando usado para ajustar a velocidade para 100%.
     * @return True if the motor setup was completed successfully, false otherwise. | Verdadeiro se a configuração dos motores foi concluída com sucesso, falso caso contrário.
     */
    boolean begin(uint8_t drivingMode = 0, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7,
               uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B',
               uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H',
               uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U',
               uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x',
               uint8_t speedDelay = 40, uint8_t speed0 = '0', uint8_t speed1 = '1', uint8_t speed2 = '2', uint8_t speed3 = '3', uint8_t speed4 = '4',
               uint8_t speed5 = '5', uint8_t speed6 = '6', uint8_t speed7 = '7', uint8_t speed8 = '8', uint8_t speed9 = '9', uint8_t speed10 = 'q'
               );

    /**
     * @brief Gets the current class version.
     * | Obtém a versão atual da classe.
     * @return Constant string with the class version. | String constante com a versão da classe.
     */
    const char* getVersion();

    /**
     * @brief Processes one command character and executes the mapped action.
     * | Processa um caractere de comando e executa a ação mapeada.
     * @param command Command character received from serial, Bluetooth or another controller. | Caractere de comando recebido pela serial, Bluetooth ou outro controlador.
     * @note Unknown commands intentionally stop the car for safety. | Comandos desconhecidos param o carro intencionalmente por segurança.
     */
    void controlCommand(char command);

    /**
     * @brief Reads one available character from a serial stream and processes it as a command.
     * | Lê um caractere disponível em um fluxo serial e o processa como comando.
     * @param serial Serial stream used as command source. Ex.: `Serial`, `Serial1`, `Serial2` or Bluetooth serial.
     * | Fluxo serial usado como origem dos comandos. Ex.: `Serial`, `Serial1`, `Serial2` ou serial Bluetooth.
     */
    void controlCommand(Stream& serial);

    /**
     * @brief Sets the current movement speed.
     * | Ajusta a velocidade atual de movimento.
     * @param value Speed value, typically from 0 to 100. | Valor de velocidade, geralmente de 0 a 100.
     */
    void setSpeed(uint8_t value);

    /**
     * @brief Gets the current movement speed.
     * | Obtém a velocidade atual de movimento.
     * @return Current speed value. | Valor atual de velocidade.
     */
    uint8_t getSpeed();

    /**
     * @brief Sets the smooth-turn speed percentage applied to the slower motor.
     * | Ajusta o percentual de velocidade aplicado ao motor mais lento em curvas suaves.
     * @param value Percentage used during smooth turns, typically from 0 to 100. | Percentual usado durante curvas suaves, geralmente de 0 a 100.
     */
    void setSpeedDelay(uint8_t value);

    /**
     * @brief Gets the smooth-turn speed percentage.
     * | Obtém o percentual de velocidade usado em curvas suaves.
     * @return Current smooth-turn percentage. | Percentual atual usado em curvas suaves.
     */
    uint8_t getSpeedDelay();

    /**
     * @brief Stops both motors.
     * | Para os dois motores.
     */
    void stop();

    /**
     * @brief Moves the car forward using the current speed.
     * | Move o carro para frente usando a velocidade atual.
     */
    void forward();

    /**
     * @brief Moves the car forward using the specified speed.
     * | Move o carro para frente usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void forward(uint8_t speed);

    /**
     * @brief Moves the car backward using the current speed.
     * | Move o carro para trás usando a velocidade atual.
     */
    void backward();

    /**
     * @brief Moves the car backward using the specified speed.
     * | Move o carro para trás usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void backward(uint8_t speed);

    /**
     * @brief Turns the car left using the current speed.
     * | Vira o carro para a esquerda usando a velocidade atual.
     */
    void left();

    /**
     * @brief Turns the car left using the specified speed.
     * | Vira o carro para a esquerda usando a velocidade especificada.
     * @param speed Turn speed, typically from 0 to 100. | Velocidade de giro, geralmente de 0 a 100.
     */
    void left(uint8_t speed);

    /**
     * @brief Turns the car right using the current speed.
     * | Vira o carro para a direita usando a velocidade atual.
     */
    void right();

    /**
     * @brief Turns the car right using the specified speed.
     * | Vira o carro para a direita usando a velocidade especificada.
     * @param speed Turn speed, typically from 0 to 100. | Velocidade de giro, geralmente de 0 a 100.
     */
    void right(uint8_t speed);

    /**
     * @brief Moves forward while turning left using the current speed.
     * | Move para frente virando à esquerda usando a velocidade atual.
     */
    void forwardLeft();

    /**
     * @brief Moves forward while turning left using the specified speed.
     * | Move para frente virando à esquerda usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void forwardLeft(uint8_t speed);

    /**
     * @brief Moves forward while turning right using the current speed.
     * | Move para frente virando à direita usando a velocidade atual.
     */
    void forwardRight();

    /**
     * @brief Moves forward while turning right using the specified speed.
     * | Move para frente virando à direita usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void forwardRight(uint8_t speed);

    /**
     * @brief Moves backward while turning left using the current speed.
     * | Move para trás virando à esquerda usando a velocidade atual.
     */
    void backLeft();

    /**
     * @brief Moves backward while turning left using the specified speed.
     * | Move para trás virando à esquerda usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void backLeft(uint8_t speed);

    /**
     * @brief Moves backward while turning right using the current speed.
     * | Move para trás virando à direita usando a velocidade atual.
     */
    void backRight();

    /**
     * @brief Moves backward while turning right using the specified speed.
     * | Move para trás virando à direita usando a velocidade especificada.
     * @param speed Movement speed, typically from 0 to 100. | Velocidade de movimento, geralmente de 0 a 100.
     */
    void backRight(uint8_t speed);

    /**
     * @brief Turns the front lights on or off.
     * | Liga ou desliga as luzes dianteiras.
     * @param status True to turn on, false to turn off. | Verdadeiro para ligar, falso para desligar.
     */
    void frontLights(boolean status);

    /**
     * @brief Turns the back lights on or off.
     * | Liga ou desliga as luzes traseiras.
     * @param status True to turn on, false to turn off. | Verdadeiro para ligar, falso para desligar.
     */
    void backLights(boolean status);

    /**
     * @brief Turns the horn on or off.
     * | Liga ou desliga a buzina.
     * @param status True to turn on, false to turn off. | Verdadeiro para ligar, falso para desligar.
     */
    void horn(boolean status);

    /**
     * @brief Enables or disables the extra output.
     * | Ativa ou desativa a saída extra.
     * @param status True to enable, false to disable. | Verdadeiro para ativar, falso para desativar.
     */
    void extra(boolean status);

    /**
     * @brief Defines a custom callback to control the horn.
     * | Define uma função de callback personalizada para controlar a buzina.
     * @param callback Function that receives true to turn on and false to turn off. | Função que recebe verdadeiro para ligar e falso para desligar.
     */
    void setHornFunction(void (*callback)(bool));

    /**
     * @brief Defines a custom callback to control the front lights.
     * | Define uma função de callback personalizada para controlar as luzes dianteiras.
     * @param callback Function that receives true to turn on and false to turn off. | Função que recebe verdadeiro para ligar e falso para desligar.
     */
    void setFrontLightsFunction(void (*callback)(bool));

    /**
     * @brief Defines a custom callback to control the back lights.
     * | Define uma função de callback personalizada para controlar as luzes traseiras.
     * @param callback Function that receives true to turn on and false to turn off. | Função que recebe verdadeiro para ligar e falso para desligar.
     */
    void setBackLightsFunction(void (*callback)(bool));

    /**
     * @brief Defines a custom callback to control the extra output.
     * | Define uma função de callback personalizada para controlar a saída extra.
     * @param callback Function that receives true to enable and false to disable. | Função que recebe verdadeiro para ativar e falso para desativar.
     */
    void setExtraFunction(void (*callback)(bool));

    /**
     * @brief Defines a custom callback for the forward movement.
     * | Define uma função de callback personalizada para o movimento para frente.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setForwardFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the backward movement.
     * | Define uma função de callback personalizada para o movimento para trás.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setBackwardFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the left turn.
     * | Define uma função de callback personalizada para virar à esquerda.
     * @param callback Function that receives the turn speed. | Função que recebe a velocidade de giro.
     */
    void setLeftFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the right turn.
     * | Define uma função de callback personalizada para virar à direita.
     * @param callback Function that receives the turn speed. | Função que recebe a velocidade de giro.
     */
    void setRightFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the forward-left movement.
     * | Define uma função de callback personalizada para o movimento para frente e à esquerda.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setForwardLeftFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the forward-right movement.
     * | Define uma função de callback personalizada para o movimento para frente e à direita.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setForwardRightFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the backward-left movement.
     * | Define uma função de callback personalizada para o movimento para trás e à esquerda.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setBackLeftFunction(void (*callback)(uint8_t));

    /**
     * @brief Defines a custom callback for the backward-right movement.
     * | Define uma função de callback personalizada para o movimento para trás e à direita.
     * @param callback Function that receives the movement speed. | Função que recebe a velocidade de movimento.
     */
    void setBackRightFunction(void (*callback)(uint8_t));

    /**
     * @brief Inverts the direction commands of the selected motor.
     * | Inverte os comandos de direção do motor selecionado.
     * @param motorID Motor identifier. Use 0 for motor 1 or 1 for motor 2. | Identificador do motor. Use 0 para o motor 1 ou 1 para o motor 2.
     */
    void invertMotorCommands(uint8_t motorID);

    /**
     * @brief Gets whether the selected motor has inverted commands.
     * | Obtém se o motor selecionado está com os comandos invertidos.
     * @param motorID Motor identifier. Use 0 for motor 1 or 1 for motor 2. | Identificador do motor. Use 0 para o motor 1 ou 1 para o motor 2.
     * @return True if the selected motor is inverted, false otherwise. | Verdadeiro se o motor selecionado estiver invertido, falso caso contrário.
     */
    boolean invertMotorStatus(uint8_t motorID);
    // void invertDirection();
    // boolean invertDirectionStatus();
    // void invertTraction();
    // boolean invertTractionStatus();
};

#endif
