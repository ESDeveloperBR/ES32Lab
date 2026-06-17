#include "ES_CarControl.h"

// <<< Constructor using a PCF8574 pointer | Construtor usando ponteiro para PCF8574 >>>
ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574) {
    _buzzer = nullptr;
    _pcf8574 = pcf8574;
}

// <<< Constructor using a PCF8574 reference | Construtor usando referência para PCF8574 >>>
ES_CarControl::ES_CarControl(ES_PCF8574 &pcf8574) {
    _buzzer = nullptr;
    _pcf8574 = &pcf8574;
}

// <<< Constructor using PCF8574 and buzzer pointers | Construtor usando ponteiros para PCF8574 e buzina >>>
ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer) {
    _buzzer = buzzer;
    _pcf8574 = pcf8574;
}

// <<< Constructor using PCF8574 and buzzer references | Construtor usando referências para PCF8574 e buzina >>>
ES_CarControl::ES_CarControl(ES_PCF8574 &pcf8574, ES_Buzzer &buzzer) {
    _buzzer = &buzzer;
    _pcf8574 = &pcf8574;
}

// <<< Get class version | Obtém a versão da classe >>>
const char* ES_CarControl::getVersion() {
    return ES_CAR_CONTROL_VERSION;
}

// <<< Initialize car control configuration | Inicializa a configuração de controle do carro >>>
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





// <<< Process a command character | Processa um caractere de comando >>>
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


// <<< Read and process a serial command | Lê e processa um comando serial >>>
void ES_CarControl::controlCommand(Stream& serial) {
    if (serial.available()) {
        controlCommand(serial.read());
    }
}

// <<< Set current speed | Ajusta a velocidade atual >>>
void ES_CarControl::setSpeed(uint8_t value) {
    _currentSpeed = value;
}

// <<< Get current speed | Obtém a velocidade atual >>>
uint8_t ES_CarControl::getSpeed() {
    return _currentSpeed;
}

// <<< Set smooth-turn speed percentage | Ajusta o percentual de velocidade para curvas suaves >>>
void ES_CarControl::setSpeedDelay(uint8_t value) {
    _speedDelay = value;
}

// <<< Get smooth-turn speed percentage | Obtém o percentual de velocidade para curvas suaves >>>
uint8_t ES_CarControl::getSpeedDelay() {
    return _speedDelay;
}

// <<< Stop both motors | Para os dois motores >>>
void ES_CarControl::stop() {
    if (_pcf8574) {
        _pcf8574->motorStop(0);
        _pcf8574->motorStop(1);
    }
}

// <<< Move forward using current speed | Move para frente usando a velocidade atual >>>
void ES_CarControl::forward() {
    forward(_currentSpeed);
}

// <<< Move forward using specified speed | Move para frente usando a velocidade especificada >>>
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

// <<< Move backward using current speed | Move para trás usando a velocidade atual >>>
void ES_CarControl::backward() {
    backward(_currentSpeed);
}

// <<< Move backward using specified speed | Move para trás usando a velocidade especificada >>>
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

// <<< Turn left using current speed | Vira à esquerda usando a velocidade atual >>>
void ES_CarControl::left() {
    left(_currentSpeed);
}

// <<< Turn left using specified speed | Vira à esquerda usando a velocidade especificada >>>
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

// <<< Turn right using current speed | Vira à direita usando a velocidade atual >>>
void ES_CarControl::right() {
    right(_currentSpeed);
}

// <<< Turn right using specified speed | Vira à direita usando a velocidade especificada >>>
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

// <<< Move forward while turning left | Move para frente virando à esquerda >>>
void ES_CarControl::forwardLeft() {
    forwardLeft(_currentSpeed);
}

// <<< Move forward-left using specified speed | Move para frente e à esquerda usando a velocidade especificada >>>
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

// <<< Move forward while turning right | Move para frente virando à direita >>>
void ES_CarControl::forwardRight() {
    forwardRight(_currentSpeed);
}

// <<< Move forward-right using specified speed | Move para frente e à direita usando a velocidade especificada >>>
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

// <<< Move backward while turning left | Move para trás virando à esquerda >>>
void ES_CarControl::backLeft() {
    backLeft(_currentSpeed);
}

// <<< Move backward-left using specified speed | Move para trás e à esquerda usando a velocidade especificada >>>
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

// <<< Move backward while turning right | Move para trás virando à direita >>>
void ES_CarControl::backRight() {
    backRight(_currentSpeed);
}

// <<< Move backward-right using specified speed | Move para trás e à direita usando a velocidade especificada >>>
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


// <<< Control horn state | Controla o estado da buzina >>>
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

// <<< Control front lights | Controla as luzes dianteiras >>>
void ES_CarControl::frontLights(boolean status) {
    if (_customFrontLightsFunction) {
        _customFrontLightsFunction(status);
    } else if (_pcf8574) {
        _pcf8574->digitalWrite(_frontLightsPin, status);
    }
}

// <<< Control back lights | Controla as luzes traseiras >>>
void ES_CarControl::backLights(boolean status) {
    if (_customBackLightsFunction) {
        _customBackLightsFunction(status);
    } else if (_pcf8574) {
        _pcf8574->digitalWrite(_backLightsPin, status);
    }
}

// <<< Control extra output | Controla a saída extra >>>
void ES_CarControl::extra(boolean status) {
    if (_customExtraFunction) {
        _customExtraFunction(status);
    } else if (_pcf8574) {
        _pcf8574->pwmWrite(_frontLightsPin, 50, status);
        _pcf8574->pwmWrite(_backLightsPin, 50, status);
    }
}

// <<< Set custom horn callback | Define callback personalizado para a buzina >>>
void ES_CarControl::setHornFunction(void (*callback)(bool)) {
  _customHornFunction = callback;
}

// <<< Set custom front lights callback | Define callback personalizado para as luzes dianteiras >>>
void ES_CarControl::setFrontLightsFunction(void (*callback)(bool)) {
  _customFrontLightsFunction = callback;
}

// <<< Set custom back lights callback | Define callback personalizado para as luzes traseiras >>>
void ES_CarControl::setBackLightsFunction(void (*callback)(bool)) {
  _customBackLightsFunction = callback;
}

// <<< Set custom extra callback | Define callback personalizado para a saída extra >>>
void ES_CarControl::setExtraFunction(void (*callback)(bool)) {
  _customExtraFunction = callback;
}

// <<< Set custom forward movement callback | Define callback personalizado para o movimento para frente >>>
void ES_CarControl::setForwardFunction(void (*callback)(uint8_t)) {
    _customForwardFunction = callback;
}

// <<< Set custom forward-left movement callback | Define callback personalizado para o movimento para frente e à esquerda >>>
void ES_CarControl::setForwardLeftFunction(void (*callback)(uint8_t)) {
    _customForwardLeftFunction = callback;
}

// <<< Set custom forward-right movement callback | Define callback personalizado para o movimento para frente e à direita >>>
void ES_CarControl::setForwardRightFunction(void (*callback)(uint8_t)) {
    _customForwardRightFunction = callback;
}

// <<< Set custom backward movement callback | Define callback personalizado para o movimento para trás >>>
void ES_CarControl::setBackwardFunction(void (*callback)(uint8_t)) {
    _customBackwardFunction = callback;
}

// <<< Set custom left turn callback | Define callback personalizado para virar à esquerda >>>
void ES_CarControl::setLeftFunction(void (*callback)(uint8_t)) {
    _customLeftFunction = callback;
}

// <<< Set custom right turn callback | Define callback personalizado para virar à direita >>>
void ES_CarControl::setRightFunction(void (*callback)(uint8_t)) {
    _customRightFunction = callback;
}

// <<< Set custom backward-left movement callback | Define callback personalizado para o movimento para trás e à esquerda >>>
void ES_CarControl::setBackLeftFunction(void (*callback)(uint8_t)) {
    _customBackLeftFunction = callback;
}

// <<< Set custom backward-right movement callback | Define callback personalizado para o movimento para trás e à direita >>>
void ES_CarControl::setBackRightFunction(void (*callback)(uint8_t)) {
    _customBackRightFunction = callback;
}

// <<< Invert selected motor commands | Inverte os comandos do motor selecionado >>>
void ES_CarControl::invertMotorCommands(uint8_t motorID) {
    if (_pcf8574) _pcf8574->invertMotorCommands(motorID);
}

// <<< Get selected motor inversion status | Obtém o estado de inversão do motor selecionado >>>
boolean ES_CarControl::invertMotorStatus(uint8_t motorID) {
    return _pcf8574 ? _pcf8574->invertMotorStatus(motorID) : false;
}
