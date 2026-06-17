//#include <ES_CarLineFollower.h>
#include <ES_CarLineFollower/ES_CarLineFollower.h>

// <<< Constructor of the class | Construtor da classe >>>
ES_CarLineFollower::ES_CarLineFollower(ES_CarControl &car, ES_PCF8574 &expander) {
    _car = &car;
    _expander = &expander;
}

// <<< Initializes the line follower with the specified configuration parameters. | Inicializa o seguidor de linha com os parametros de configuracao especificados. >>>
boolean ES_CarLineFollower::begin(uint8_t leftPin, uint8_t rightPin, uint8_t highSpeed, uint8_t lowSpeed,
                                  uint16_t lowSpeedDuration, uint16_t noLineDuration, uint8_t turnSpeed) {
    _leftPin = leftPin;
    _rightPin = rightPin;

    setHighSpeed(highSpeed);
    setLowSpeed(lowSpeed);
    setLowSpeedDuration(lowSpeedDuration);
    setNoLineDuration(noLineDuration);
    setTurnSpeed(turnSpeed);

    disable();
    _resetIntervals();

    return true;
}

// <<< Updates sensor readings and applies movement corrections. | Atualiza as leituras dos sensores e aplica correcoes de movimento. >>>
void ES_CarLineFollower::update() {
    if (!_lineFollowerEnabled) {
        _lineFollowerWasEnabled = false;
        return;
    }

    if (!_lineFollowerWasEnabled) {
        _lineFollowerWasEnabled = true;
        _resetIntervals();
    }

    boolean leftHold = _expander->btHold(_leftPin, true);
    boolean rightHold = _expander->btHold(_rightPin, true);

    boolean leftRelease = _expander->btRelease(_leftPin, true);
    boolean rightRelease = _expander->btRelease(_rightPin, true);

    if (leftHold || rightHold || leftRelease || rightRelease) {
        _noLineInterval.resetMillis();
    }

    if (leftHold && rightHold) {
        disable();
        return;
    }

    if (leftHold) {
        _car->right(_leftSpeed);
        _lowSpeedInterval.resetMillis();
    }

    if (leftRelease) {
        _car->forward(_lowSpeed);
    }

    if (rightHold) {
        _car->left(_rightSpeed);
        _lowSpeedInterval.resetMillis();
    }

    if (rightRelease) {
        _car->forward(_lowSpeed);
    }

    if (_noLineInterval.intervalMillis(_noLineDuration)) {
        disable();
        return;
    }

    if (_lowSpeedInterval.intervalMillis(_lowSpeedDuration)) {
        _car->forward(_highSpeed);
    }
}

// <<< Enables automatic line following. | Habilita o seguidor de linha automatico. >>>
void ES_CarLineFollower::enable() {
    _lineFollowerEnabled = true;
    _lineFollowerWasEnabled = false;
    _resetIntervals();
    _car->forward(_highSpeed);
}

// <<< Disables automatic line following. | Desabilita o seguidor de linha automatico. >>>
void ES_CarLineFollower::disable() {
    _lineFollowerEnabled = false;
    _lineFollowerWasEnabled = false;
    _car->stop();
}

// <<< Sets the enabled status of the line follower. | Define o status de ativacao do seguidor de linha. >>>
void ES_CarLineFollower::setEnabled(boolean status) {
    if (status) {
        enable();
    } else {
        disable();
    }
}

// <<< Gets the enabled status of the line follower. | Obtem o status de ativacao do seguidor de linha. >>>
boolean ES_CarLineFollower::isEnabled() {
    return _lineFollowerEnabled;
}

// <<< Gets the class version string. | Obtem a string de versao da classe. >>>
const char* ES_CarLineFollower::getVersion() {
    return ES_CAR_LINE_FOLLOWER_VERSION;
}

// <<< Sets the forward speed used when the robot is stable. | Define a velocidade para frente usada quando o robo esta estabilizado. >>>
void ES_CarLineFollower::setHighSpeed(uint8_t speed) {
    _highSpeed = _limitSpeed(speed);
}

// <<< Gets the forward speed used when the robot is stable. | Obtem a velocidade para frente usada quando o robo esta estabilizado. >>>
uint8_t ES_CarLineFollower::getHighSpeed() {
    return _highSpeed;
}

// <<< Sets the forward speed used after a correction. | Define a velocidade para frente usada apos uma correcao. >>>
void ES_CarLineFollower::setLowSpeed(uint8_t speed) {
    _lowSpeed = _limitSpeed(speed);
}

// <<< Gets the forward speed used after a correction. | Obtem a velocidade para frente usada apos uma correcao. >>>
uint8_t ES_CarLineFollower::getLowSpeed() {
    return _lowSpeed;
}

// <<< Sets the time before returning to high speed after a correction. | Define o tempo antes de retornar para a velocidade alta apos uma correcao. >>>
void ES_CarLineFollower::setLowSpeedDuration(uint16_t duration) {
    _lowSpeedDuration = duration;
}

// <<< Gets the time before returning to high speed after a correction. | Obtem o tempo antes de retornar para a velocidade alta apos uma correcao. >>>
uint16_t ES_CarLineFollower::getLowSpeedDuration() {
    return _lowSpeedDuration;
}

// <<< Sets the maximum time without line contact before stopping. | Define o tempo maximo sem contato com a linha antes de parar. >>>
void ES_CarLineFollower::setNoLineDuration(uint16_t duration) {
    _noLineDuration = duration;
}

// <<< Gets the maximum time without line contact before stopping. | Obtem o tempo maximo sem contato com a linha antes de parar. >>>
uint16_t ES_CarLineFollower::getNoLineDuration() {
    return _noLineDuration;
}

// <<< Sets the turning speed for left sensor corrections. | Define a velocidade de giro para correcoes do sensor esquerdo. >>>
void ES_CarLineFollower::setLeftSpeed(uint8_t speed) {
    _leftSpeed = _limitSpeed(speed);
}

// <<< Gets the turning speed for left sensor corrections. | Obtem a velocidade de giro para correcoes do sensor esquerdo. >>>
uint8_t ES_CarLineFollower::getLeftSpeed() {
    return _leftSpeed;
}

// <<< Sets the turning speed for right sensor corrections. | Define a velocidade de giro para correcoes do sensor direito. >>>
void ES_CarLineFollower::setRightSpeed(uint8_t speed) {
    _rightSpeed = _limitSpeed(speed);
}

// <<< Gets the turning speed for right sensor corrections. | Obtem a velocidade de giro para correcoes do sensor direito. >>>
uint8_t ES_CarLineFollower::getRightSpeed() {
    return _rightSpeed;
}

// <<< Sets the same turning speed for both left and right corrections. | Define a mesma velocidade de giro para as correcoes esquerda e direita. >>>
void ES_CarLineFollower::setTurnSpeed(uint8_t speed) {
    speed = _limitSpeed(speed);
    _leftSpeed = speed;
    _rightSpeed = speed;
}

// <<< Limits speed values to the 0-100 range. | Limita valores de velocidade para a faixa de 0 a 100. >>>
uint8_t ES_CarLineFollower::_limitSpeed(uint8_t speed) {
    return speed > 100 ? 100 : speed;
}

// <<< Resets the internal timing intervals. | Reinicia os temporizadores internos. >>>
void ES_CarLineFollower::_resetIntervals() {
    _lowSpeedInterval.resetMillis();
    _noLineInterval.resetMillis();
}
