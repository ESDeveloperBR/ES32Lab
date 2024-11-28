#include "ES_CarControl.h"

/**
 * Initializes the car control system with an optional PCF8574 I2C expander. The buzzer is disabled by default.
 * | Inicializa o sistema de controle do carro com um expansor I2C PCF8574 opcional. O buzzer está desativado por padrão.
 * @param pcf8574 A pointer to an `ES_PCF8574` object for I2C GPIO expansion. Pass `nullptr` if not used. | Um ponteiro para um objeto `ES_PCF8574` para expansão de GPIO via I2C. Passe `nullptr` se não for usado.
 */
ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574) {
    _buzzer = nullptr;
    _pcf8574 = pcf8574;
}

/**
 * Initializes the car control system with optional PCF8574 I2C expander and Buzzer components.
 * | Inicializa o sistema de controle do carro com componentes opcionais de expansor I2C PCF8574 e Buzzer.
 * @param pcf8574 A pointer to an `ES_PCF8574` object for I2C GPIO expansion. Pass `nullptr` if not used. | Um ponteiro para um objeto `ES_PCF8574` para expansão de GPIO via I2C. Passe `nullptr` se não for usado.
 * @param buzzer A pointer to an `ES_Buzzer` object for sound output. Pass `nullptr` if not used. | Um ponteiro para um objeto `ES_Buzzer` para saída de som. Passe `nullptr` se não for usado.
 */
ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer) {
    _buzzer = buzzer;
    _pcf8574 = pcf8574;
}

/**
 * Initializes the car control system with specified configurations for motors, lights, commands, and speed settings.
 * | Inicializa o sistema de controle do carro com configurações especificadas para motores, luzes, comandos e ajustes de velocidade.
 * 
 * This method sets up the driving mode, pin configurations, and command mappings. It also initializes optional components like the buzzer and I2C expander if provided.
 * | Este método configura o modo de direção, pinos e mapeamento de comandos. Também inicializa componentes opcionais como o buzzer e o expansor I2C, se fornecidos.
 * 
 * @param drivingMode Driving mode (e.g., 0 for differential, 1 for frontal). | Modo de direção (ex.: 0 para diferencial, 1 para dianteiro).
 * @param motor1Pin1 GPIO for motor 1, pin 1. | GPIO para o motor 1, pino 1.
 * @param motor1Pin2 GPIO for motor 1, pin 2. | GPIO para o motor 1, pino 2.
 * @param motor2Pin1 GPIO for motor 2, pin 1. | GPIO para o motor 2, pino 1.
 * @param motor2Pin2 GPIO for motor 2, pin 2. | GPIO para o motor 2, pino 2.
 * @param frontLightsPin GPIO for front lights. | GPIO para luzes dianteiras.
 * @param backLightsPin GPIO for back lights. | GPIO para luzes traseiras.
 * @param stop Command for stopping the vehicle. | Comando para parar o veículo.
 * @param forward Command for forward movement. | Comando para movimento para frente.
 * @param back Command for backward movement. | Comando para movimento para trás.
 * @param left Command for left movement. | Comando para movimento à esquerda.
 * @param right Command for right movement. | Comando para movimento à direita.
 * @param forwardLeft Command for forward-left movement. | Comando para movimento para frente e à esquerda.
 * @param forwardRight Command for forward-right movement. | Comando para movimento para frente e à direita.
 * @param backLeft Command for backward-left movement. | Comando para movimento para trás e à esquerda.
 * @param backRight Command for backward-right movement. | Comando para movimento para trás e à direita.
 * @param frontLightsOn Command to turn on the front lights. | Comando para ligar as luzes dianteiras.
 * @param frontLightsOff Command to turn off the front lights. | Comando para desligar as luzes dianteiras.
 * @param backLightsOn Command to turn on the back lights. | Comando para ligar as luzes traseiras.
 * @param backLightsOff Command to turn off the back lights. | Comando para desligar as luzes traseiras.
 * @param hornOn Command to activate the horn. | Comando para ativar a buzina.
 * @param hornOff Command to deactivate the horn. | Comando para desativar a buzina.
 * @param extraOn Command to activate an extra feature. | Comando para ativar uma funcionalidade extra.
 * @param extraOff Command to deactivate an extra feature. | Comando para desativar uma funcionalidade extra.
 * @param speedDelay Delay for smoother speed transitions. | Atraso para transições de velocidade mais suaves.
 * @param speed0 Command for speed level 0. | Comando para velocidade nível 0.
 * @param speed1 Command for speed level 1. | Comando para velocidade nível 1.
 * @param speed2 Command for speed level 2. | Comando para velocidade nível 2.
 * @param speed3 Command for speed level 3. | Comando para velocidade nível 3.
 * @param speed4 Command for speed level 4. | Comando para velocidade nível 4.
 * @param speed5 Command for speed level 5. | Comando para velocidade nível 5.
 * @param speed6 Command for speed level 6. | Comando para velocidade nível 6.
 * @param speed7 Command for speed level 7. | Comando para velocidade nível 7.
 * @param speed8 Command for speed level 8. | Comando para velocidade nível 8.
 * @param speed9 Command for speed level 9. | Comando para velocidade nível 9.
 * @param speed10 Command for speed level 10. | Comando para velocidade nível 10.
 * @return `true` if initialization is successful, `false` if there is an error (e.g., motor initialization failure). | `true` se a inicialização for bem-sucedida, `false` se houver um erro (ex.: falha na inicialização dos motores).
 */
bool ES_CarControl::begin(uint8_t drivingMode, uint8_t motor1Pin1, uint8_t motor1Pin2, uint8_t motor2Pin1, uint8_t motor2Pin2, 
                          uint8_t frontLightsPin, uint8_t backLightsPin, uint8_t stop, uint8_t forward, uint8_t back, 
                          uint8_t left, uint8_t right, uint8_t forwardLeft, uint8_t forwardRight, uint8_t backLeft, 
                          uint8_t backRight, uint8_t frontLightsOn, uint8_t frontLightsOff, uint8_t backLightsOn, 
                          uint8_t backLightsOff, uint8_t hornOn, uint8_t hornOff, uint8_t extraOn, uint8_t extraOff, 
                          uint8_t speedDelay, uint8_t speed0, uint8_t speed1, uint8_t speed2, uint8_t speed3, 
                          uint8_t speed4, uint8_t speed5, uint8_t speed6, uint8_t speed7, uint8_t speed8, 
                          uint8_t speed9, uint8_t speed10) {

    _drivingMode = drivingMode;
    _motor1Pin1 = motor1Pin1;
    _motor1Pin2 = motor1Pin2;
    _motor2Pin1 = motor2Pin1;
    _motor2Pin2 = motor2Pin2;
    _frontLightsPin = frontLightsPin;
    _backLightsPin = backLightsPin;

    _stop = stop;
    _forward = forward;
    _back = back;
    _left = left;
    _right = right;
    _forwardLeft = forwardLeft;
    _forwardRight = forwardRight;
    _backLeft = backLeft;
    _backRight = backRight;
    _frontLightsOn = frontLightsOn;
    _frontLightsOff = frontLightsOff;
    _backLightsOn = backLightsOn;
    _backLightsOff = backLightsOff;
    _hornOn = hornOn;
    _hornOff = hornOff;
    _extraOn = extraOn;
    _extraOff = extraOff;
    _speedDelay = speedDelay;

    _speed0 = speed0;
    _speed1 = speed1;
    _speed2 = speed2;
    _speed3 = speed3;
    _speed4 = speed4;
    _speed5 = speed5;
    _speed6 = speed6;
    _speed7 = speed7;
    _speed8 = speed8;
    _speed9 = speed9;
    _speed10 = speed10;

    if (_buzzer != nullptr) {
        _buzzer->begin();
    } else {
        Serial.println("Buzzer disable.");
    }

    if (_pcf8574 != nullptr) {
        bool motor1Init = _pcf8574->motorBegin(0, _motor1Pin1, _motor1Pin2);
        bool motor2Init = _pcf8574->motorBegin(1, _motor2Pin1, _motor2Pin2);

        if (!motor1Init || !motor2Init) {
            Serial.println("Error initializing motors.");
            return false;
        }

    } else {
        Serial.println("Expansor I2C disable.");
    }

    return true;
}





/**
 * Processes a single-character command and executes the corresponding action, such as movement, light control, or speed adjustment. This method interprets a command and maps it to predefined actions, such as starting/stopping motors, turning lights on/off, activating the horn, or adjusting speed levels.
 * | Processa um comando de caractere único e executa a ação correspondente, como movimento, controle de luzes ou ajuste de velocidade. Este método interpreta um comando e o mapeia para ações predefinidas, como ligar/desligar motores, ligar/desligar luzes, ativar a buzina ou ajustar os níveis de velocidade.
 * @param command A single character representing the desired action. | Um caractere único representando a ação desejada.
 */
void ES_CarControl::controlCommand(char command) {
    if (command == _stop) stop();
    else if (command == _forward) forward();
    else if (command == _forwardLeft) forwardLeft();
    else if (command == _forwardRight) forwardRight();

    else if (command == _back) backward();
    else if (command == _backLeft) backLeft();
    else if (command == _backRight) backRight();

    else if (command == _left) left();
    else if (command == _right) right();

    else if (command == _frontLightsOn) frontLights(true);
    else if (command == _frontLightsOff) frontLights(false);
    else if (command == _backLightsOn) backLights(true);
    else if (command == _backLightsOff) backLights(false);
    else if (command == _hornOn) horn(true);
    else if (command == _hornOff) horn(false);
    else if (command == _extraOn) extra(true);
    else if (command == _extraOff) extra(false);

    else if (command == _speed0) _currentSpeed = 0;
    else if (command == _speed1) _currentSpeed = 10;
    else if (command == _speed2) _currentSpeed = 20;
    else if (command == _speed3) _currentSpeed = 30;
    else if (command == _speed4) _currentSpeed = 40;
    else if (command == _speed5) _currentSpeed = 50;
    else if (command == _speed6) _currentSpeed = 60;
    else if (command == _speed7) _currentSpeed = 70;
    else if (command == _speed8) _currentSpeed = 80;
    else if (command == _speed9) _currentSpeed = 90;
    else if (command == _speed10) _currentSpeed = 100;
    else stop();
}


/**
 * Reads a command from a serial stream and executes the corresponding action. This method is ideal for use with Bluetooth modules, allowing direct interaction with a Bluetooth object passed as a parameter.
 * | Lê um comando de um fluxo serial e executa a ação correspondente. Este método é ideal para uso com módulos Bluetooth, permitindo interação direta com um objeto Bluetooth passado como parâmetro.
 * @param serial A reference to a serial stream (e.g., `Serial`, `Serial1`, `Serial2`) from which commands will be read. | Uma referência para um fluxo serial (ex.: `Serial`, `Serial1`, `Serial2`) de onde os comandos serão lidos.
 */
void ES_CarControl::controlCommand(Stream& serial) {
    if (serial.available()) {
        controlCommand(serial.read());
    }
}

/**
 * Sets the current speed of the vehicle for future movement commands. This value determines how fast the motors will operate.
 * | Define a velocidade atual do veículo para futuros comandos de movimento. Este valor determina a rapidez com que os motores irão operar.
 * @param value The speed value to set, typically ranging from 0 to 100. | O valor da velocidade a ser definido, geralmente variando de 0 a 100.
 */
void ES_CarControl::setSpeed(uint8_t value) {
    _currentSpeed = value;
}

/**
 * Retrieves the current speed setting of the vehicle.
 * | Retorna a configuração atual de velocidade do veículo.
 * @return The current speed value, typically ranging from 0 to 100. | O valor atual da velocidade, geralmente variando de 0 a 100.
 */
uint8_t ES_CarControl::getSpeed() {
    return _currentSpeed;
}

/**
 * Sets the delay factor for the speed of the motors responsible for steering, enabling smoother maneuvers while the vehicle is in motion.
 * | Define o fator de atraso para velocidades dos motores responsáveis pela direção do carro, tornando uma direção mais suave enquanto o veículo estiver em movimento.
 * @param value The delay value to set, typically used to adjust steering smoothness. | O valor do atraso a ser definido, geralmente usado para ajustar a suavidade da direção.
 */
void ES_CarControl::setSpeedDelay(uint8_t value) {
    _speedDelay = value;
}

/**
 * Retrieves the delay factor used for the speed of the motors responsible for steering, enabling smoother maneuvers while the vehicle is in motion.
 * | Retorna o fator de atraso usado para as velocidades dos motores responsáveis pela direção, permitindo manobras mais suaves enquanto o veículo estiver em movimento.
 * @return The current delay value for steering adjustments. | O valor atual do atraso para ajustes de direção.
 */
uint8_t ES_CarControl::getSpeedDelay() {
    return _speedDelay;
}

/**
 * Stops both motors of the car, bringing the vehicle to a halt. This method sends stop commands to the motors through the connected I2C expander (PCF8574), if available.
 * | Para ambos os motores do carro, interrompendo o movimento do veículo. Este método envia comandos de parada para os motores através do expansor I2C conectado (PCF8574), se disponível.
 */
void ES_CarControl::stop() {
    if (_pcf8574) {
        _pcf8574->motorStop(0);
        _pcf8574->motorStop(1);
    }
}

/**
 * Moves the vehicle forward using the current speed setting. This method uses the overloaded `forward(uint8_t speed)` function.
 * | Move o veículo para frente usando a configuração de velocidade atual.
 */
void ES_CarControl::forward() {
    forward(_currentSpeed);
}

/**
 * Moves the vehicle forward at a specified speed. If a custom forward function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para frente em uma velocidade especificada. Se uma função personalizada de avanço for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves forward, typically ranging from 0 to 100. | A velocidade com que o veículo avança, geralmente variando de 0 a 100.
 */
void ES_CarControl::forward(uint8_t speed) {
    _currentSpeed = speed;
    if (_customForwardFunction) {
        _customForwardFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorRotationA(1, _currentSpeed);
        }else if(_drivingMode == 1){
            // --- Direção dianteira ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorStop(1);
        }
    }
}

/**
 * Moves the vehicle backward using the current speed setting. This method uses the overloaded `backward(uint8_t speed)` function.
 * | Move o veículo para trás usando a configuração de velocidade atual.
 */
void ES_CarControl::backward() {
    backward(_currentSpeed);
}

/**
 * Moves the vehicle backward at a specified speed. If a custom backward function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para trás em uma velocidade especificada. Se uma função personalizada de retrocesso for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves backward, typically ranging from 0 to 100. | A velocidade com que o veículo retrocede, geralmente variando de 0 a 100.
 */
void ES_CarControl::backward(uint8_t speed) {
    _currentSpeed = speed;
    if (_customBackwardFunction) {
        _customBackwardFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorRotationB(1, _currentSpeed);
        }else if(_drivingMode == 1){
            // --- Direção dianteira ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorStop(1);
        }
    }
}

/**
 * Turns the vehicle to the left using the current speed setting.
 * | Vira o veículo para a esquerda usando a configuração de velocidade atual.
 */
void ES_CarControl::left() {
    left(_currentSpeed);
}

/**
 * Turns the vehicle to the left at a specified speed. If a custom left function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Vira o veículo para a esquerda em uma velocidade especificada. Se uma função personalizada de virar à esquerda for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle turns left, typically ranging from 0 to 100. | A velocidade com que o veículo vira para a esquerda, geralmente variando de 0 a 100.
 */
void ES_CarControl::left(uint8_t speed) {
    _currentSpeed = speed;
    if (_customLeftFunction) {
        _customLeftFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorRotationB(1, _currentSpeed);

        }else if(_drivingMode == 1){
            // --- Direção dianteira ---
            _pcf8574->motorRotationA(1, _currentSpeed);
            _pcf8574->motorStop(0);
        }
    }
}

/**
 * Turns the vehicle to the right using the current speed setting.
 * | Vira o veículo para a direita usando a configuração de velocidade atual.
 */
void ES_CarControl::right() {
    right(_currentSpeed);
}

/**
 * Turns the vehicle to the right at a specified speed. If a custom right function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Vira o veículo para a direita em uma velocidade especificada. Se uma função personalizada de virar à direita for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle turns right, typically ranging from 0 to 100. | A velocidade com que o veículo vira para a direita, geralmente variando de 0 a 100.
 */
void ES_CarControl::right(uint8_t speed) {
    _currentSpeed = speed;
    if (_customRightFunction) {
        _customRightFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorRotationA(1, _currentSpeed);

        }else if(_drivingMode == 1){
            // --- Direção dianteira ---
            _pcf8574->motorRotationB(1, _currentSpeed);
            _pcf8574->motorStop(0);
        }
    }
}

/**
 * Moves the vehicle forward and turns left using the current speed setting.
 * | Move o veículo para frente e vira à esquerda usando a configuração de velocidade atual.
 */
void ES_CarControl::forwardLeft() {
    forwardLeft(_currentSpeed);
}

/**
 * Moves the vehicle forward and turns left at a specified speed. If a custom forward-left function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para frente e vira à esquerda em uma velocidade especificada. Se uma função personalizada de avanço à esquerda for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves forward and turns left, typically ranging from 0 to 100. | A velocidade com que o veículo avança e vira à esquerda, geralmente variando de 0 a 100.
 */
void ES_CarControl::forwardLeft(uint8_t speed) {
    _currentSpeed = speed;
    if (_customForwardLeftFunction) {
        _customForwardLeftFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorRotationA(1, _currentSpeed * (_speedDelay / 100.0));
        }else if(_drivingMode == 1){
            // --- Direção Dianteira ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorRotationA(1, _currentSpeed * (_speedDelay / 100.0));
        }
    }
}

/**
 * Moves the vehicle forward and turns right using the current speed setting.
 * | Move o veículo para frente e vira à direita usando a configuração de velocidade atual.
 */
void ES_CarControl::forwardRight() {
    forwardRight(_currentSpeed);
}

/**
 * Moves the vehicle forward and turns right at a specified speed. If a custom forward-right function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para frente e vira à direita em uma velocidade especificada. Se uma função personalizada de avanço à direita for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves forward and turns right, typically ranging from 0 to 100. | A velocidade com que o veículo avança e vira à direita, geralmente variando de 0 a 100.
 */
void ES_CarControl::forwardRight(uint8_t speed) {
    _currentSpeed = speed;
    if (_customForwardRightFunction) {
        _customForwardRightFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationA(0, _currentSpeed * (_speedDelay / 100.0));
            _pcf8574->motorRotationA(1, _currentSpeed);
        }else if(_drivingMode == 1){
            // --- Direção Dianteira ---
            _pcf8574->motorRotationA(0, _currentSpeed);
            _pcf8574->motorRotationB(1, _currentSpeed * (_speedDelay / 100.0));
        }
    }
}

/**
 * Moves the vehicle backward and turns left using the current speed setting.
 * | Move o veículo para trás e vira à esquerda usando a configuração de velocidade atual.
 */
void ES_CarControl::backLeft() {
    backLeft(_currentSpeed);
}

/**
 * Moves the vehicle backward and turns left at a specified speed. If a custom back-left function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para trás e vira à esquerda em uma velocidade especificada. Se uma função personalizada de retrocesso à esquerda for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves backward and turns left, typically ranging from 0 to 100. | A velocidade com que o veículo retrocede e vira à esquerda, geralmente variando de 0 a 100.
 */
void ES_CarControl::backLeft(uint8_t speed) {
    _currentSpeed = speed;
    if (_customBackLeftFunction) {
        _customBackLeftFunction(_currentSpeed);
    } else if (_pcf8574) {
        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorRotationB(1, _currentSpeed * (_speedDelay / 100.0));

        }else if(_drivingMode == 1){
            // --- Direção Dianteira ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorRotationA(1, _currentSpeed * (_speedDelay / 100.0));
        }
    }
}

/**
 * Moves the vehicle backward and turns right using the current speed setting.
 * | Move o veículo para trás e vira à direita usando a configuração de velocidade atual.
 */
void ES_CarControl::backRight() {
    backRight(_currentSpeed);
}

/**
 * Moves the vehicle backward and turns right at a specified speed. If a custom back-right function is provided, it will be executed; otherwise, the motors are controlled via the PCF8574 expander.
 * | Move o veículo para trás e vira à direita em uma velocidade especificada. Se uma função personalizada de retrocesso à direita for fornecida, ela será executada; caso contrário, os motores são controlados pelo expansor PCF8574.
 * @param speed The speed at which the vehicle moves backward and turns right, typically ranging from 0 to 100. | A velocidade com que o veículo retrocede e vira à direita, geralmente variando de 0 a 100.
 */
void ES_CarControl::backRight(uint8_t speed) {
    _currentSpeed = speed;
    if (_customBackRightFunction) {
        _customBackRightFunction(_currentSpeed);
    } else if (_pcf8574) {

        if(_drivingMode == 0 ){
            // --- Direção diferencial ---
            _pcf8574->motorRotationB(0, _currentSpeed * (_speedDelay / 100.0));
            _pcf8574->motorRotationB(1, _currentSpeed);

        }else if(_drivingMode == 1){
            // --- Direção Dianteira ---
            _pcf8574->motorRotationB(0, _currentSpeed);
            _pcf8574->motorRotationB(1, _currentSpeed * (_speedDelay / 100.0));
        }
    }
}


/**
 * Controls the vehicle's horn status, either turning it on or off. If a custom horn function is provided, it will be executed; otherwise, the buzzer is used.
 * | Controla o estado da buzina do veículo, ligando-a ou desligando-a. Se uma função personalizada de buzina for fornecida, ela será executada; caso contrário, o buzzer é utilizado.
 * @param status A boolean value indicating whether to turn the horn on (`true`) or off (`false`). | Um valor booleano indicando se a buzina deve ser ligada (`true`) ou desligada (`false`).
 */
void ES_CarControl::horn(boolean status) {
    if (_customHornFunction) {
        _customHornFunction(status);
    } else if (_buzzer != nullptr) {
        if (status) {
            _buzzer->sound(NOTE_C4, 500);
        } else {
            _buzzer->end(0);
        }
    }
}

/**
 * Controls the front lights of the vehicle, either turning them on or off. If a custom front lights function is provided, it will be executed; otherwise, the PCF8574 expander is used.
 * | Controla as luzes dianteiras do veículo, ligando-as ou desligando-as. Se uma função personalizada para as luzes dianteiras for fornecida, ela será executada; caso contrário, o expansor PCF8574 é utilizado.
 * @param status A boolean value indicating whether to turn the front lights on (`true`) or off (`false`). | Um valor booleano indicando se as luzes dianteiras devem ser ligadas (`true`) ou desligadas (`false`).
 */
void ES_CarControl::frontLights(boolean status) {
    if (_customFrontLightsFunction) {
        _customFrontLightsFunction(status);
    } else if (_pcf8574) {
        _pcf8574->digitalWrite(_frontLightsPin, status);
    }
}

/**
 * Controls the back lights of the vehicle, either turning them on or off. If a custom back lights function is provided, it will be executed; otherwise, the PCF8574 expander is used.
 * | Controla as luzes traseiras do veículo, ligando-as ou desligando-as. Se uma função personalizada para as luzes traseiras for fornecida, ela será executada; caso contrário, o expansor PCF8574 é utilizado.
 * @param status A boolean value indicating whether to turn the back lights on (`true`) or off (`false`). | Um valor booleano indicando se as luzes traseiras devem ser ligadas (`true`) ou desligadas (`false`).
 */
void ES_CarControl::backLights(boolean status) {
    if (_customBackLightsFunction) {
        _customBackLightsFunction(status);
    } else if (_pcf8574) {
        _pcf8574->digitalWrite(_backLightsPin, status);
    }
}

/**
 * Controls an additional feature of the vehicle, either activating or deactivating it. If a custom extra function is provided, it will be executed; otherwise, the PCF8574 expander is used.
 * | Controla uma funcionalidade adicional do veículo, ativando-a ou desativando-a. Se uma função personalizada para essa funcionalidade extra for fornecida, ela será executada; caso contrário, o expansor PCF8574 é utilizado.
 * @param status A boolean value indicating whether to activate (`true`) or deactivate (`false`) the additional feature. | Um valor booleano indicando se a funcionalidade adicional deve ser ativada (`true`) ou desativada (`false`).
 */
void ES_CarControl::extra(boolean status) {
    if (_customExtraFunction) {
        _customExtraFunction(status);
    } else if (_pcf8574) {
        _pcf8574->pwmWrite(_frontLightsPin, 50, status);
        _pcf8574->pwmWrite(_backLightsPin, 50, status);
    }
}

/**
 * Sets a custom callback function to control the horn. The provided function will override the default horn behavior.
 * | Define uma função de callback personalizada para controlar a buzina. A função fornecida substituirá o comportamento padrão da buzina.
 * @param callback A pointer to a function that takes a boolean parameter (`true` to turn the horn on, `false` to turn it off). | Um ponteiro para uma função que recebe um parâmetro booleano (`true` para ligar a buzina, `false` para desligá-la).
 */
void ES_CarControl::setHornFunction(void (*callback)(bool)) {
  _customHornFunction = callback;
}

/**
 * Sets a custom callback function to control the front lights. The provided function will override the default front lights behavior.
 * | Define uma função de callback personalizada para controlar as luzes dianteiras. A função fornecida substituirá o comportamento padrão das luzes dianteiras.
 * @param callback A pointer to a function that takes a boolean parameter (`true` to turn the front lights on, `false` to turn them off). | Um ponteiro para uma função que recebe um parâmetro booleano (`true` para ligar as luzes dianteiras, `false` para desligá-las).
 */
void ES_CarControl::setFrontLightsFunction(void (*callback)(bool)) {
  _customFrontLightsFunction = callback;
}

/**
 * Sets a custom callback function to control the back lights. The provided function will override the default back lights behavior.
 * | Define uma função de callback personalizada para controlar as luzes traseiras. A função fornecida substituirá o comportamento padrão das luzes traseiras.
 * @param callback A pointer to a function that takes a boolean parameter (`true` to turn the back lights on, `false` to turn them off). | Um ponteiro para uma função que recebe um parâmetro booleano (`true` para ligar as luzes traseiras, `false` para desligá-las).
 */
void ES_CarControl::setBackLightsFunction(void (*callback)(bool)) {
  _customBackLightsFunction = callback;
}

/**
 * Sets a custom callback function to control an additional feature. The provided function will override the default behavior for this feature.
 * | Define uma função de callback personalizada para controlar uma funcionalidade adicional. A função fornecida substituirá o comportamento padrão dessa funcionalidade.
 * @param callback A pointer to a function that takes a boolean parameter (`true` to activate the feature, `false` to deactivate it). | Um ponteiro para uma função que recebe um parâmetro booleano (`true` para ativar a funcionalidade, `false` para desativá-la).
 */
void ES_CarControl::setExtraFunction(void (*callback)(bool)) {
  _customExtraFunction = callback;
}

/**
 * Sets a custom callback function to control the forward movement. The provided function will override the default forward movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para frente. A função fornecida substituirá o comportamento padrão do movimento para frente.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setForwardFunction(void (*callback)(uint8_t)) {
    _customForwardFunction = callback;
}

/**
 * Sets a custom callback function to control the forward-left movement. The provided function will override the default forward-left movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para frente e à esquerda. A função fornecida substituirá o comportamento padrão do movimento para frente e à esquerda.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setForwardLeftFunction(void (*callback)(uint8_t)) {
    _customForwardLeftFunction = callback;
}

/**
 * Sets a custom callback function to control the forward-right movement. The provided function will override the default forward-right movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para frente e à direita. A função fornecida substituirá o comportamento padrão do movimento para frente e à direita.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setForwardRightFunction(void (*callback)(uint8_t)) {
    _customForwardRightFunction = callback;
}

/**
 * Sets a custom callback function to control the backward movement. The provided function will override the default backward movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para trás. A função fornecida substituirá o comportamento padrão do movimento para trás.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setBackwardFunction(void (*callback)(uint8_t)) {
    _customBackwardFunction = callback;
}

/**
 * Sets a custom callback function to control the left movement. The provided function will override the default left movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento à esquerda. A função fornecida substituirá o comportamento padrão do movimento à esquerda.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setLeftFunction(void (*callback)(uint8_t)) {
    _customLeftFunction = callback;
}

/**
 * Sets a custom callback function to control the right movement. The provided function will override the default right movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento à direita. A função fornecida substituirá o comportamento padrão do movimento à direita.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setRightFunction(void (*callback)(uint8_t)) {
    _customRightFunction = callback;
}

/**
 * Sets a custom callback function to control the backward-left movement. The provided function will override the default backward-left movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para trás e à esquerda. A função fornecida substituirá o comportamento padrão do movimento para trás e à esquerda.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setBackLeftFunction(void (*callback)(uint8_t)) {
    _customBackLeftFunction = callback;
}

/**
 * Sets a custom callback function to control the backward-right movement. The provided function will override the default backward-right movement behavior.
 * | Define uma função de callback personalizada para controlar o movimento para trás e à direita. A função fornecida substituirá o comportamento padrão do movimento para trás e à direita.
 * @param callback A pointer to a function that takes a uint8_t parameter representing the speed (0 to 100). | Um ponteiro para uma função que recebe um parâmetro uint8_t representando a velocidade (0 a 100).
 */
void ES_CarControl::setBackRightFunction(void (*callback)(uint8_t)) {
    _customBackRightFunction = callback;
}

/**
 * Inverts the commands for the specified motor, reversing its direction.
 * | Inverte os comandos para o motor especificado, revertendo sua direção.
 * @param motorID The ID of the motor to invert (e.g., 0 for motor 1, 1 for motor 2). | O ID do motor a ser invertido (ex.: 0 para motor 1, 1 para motor 2).
 */
void ES_CarControl::invertMotorCommands(uint8_t motorID) {
    if (_pcf8574) _pcf8574->invertMotorCommands(motorID);
}

/**
 * Checks if the specified motor's commands are inverted.
 * | Verifica se os comandos do motor especificado estão invertidos.
 * @param motorID The ID of the motor to check (e.g., 0 for motor 1, 1 for motor 2). | O ID do motor a ser verificado (ex.: 0 para motor 1, 1 para motor 2).
 * @return `true` if the motor's commands are inverted, `false` otherwise. | `true` se os comandos do motor estiverem invertidos, `false` caso contrário.
 */
boolean ES_CarControl::invertMotorStatus(uint8_t motorID) {
    return _pcf8574 ? _pcf8574->invertMotorStatus(motorID) : false;
}
