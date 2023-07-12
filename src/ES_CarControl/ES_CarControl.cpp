#include "ES_CarControl.h"

ES_CarControl::ES_CarControl() {
  _buzzer = NULL;
  _pcf8574 = NULL;
}

ES_CarControl::ES_CarControl(ES_Buzzer* buzzer) {
  _buzzer = buzzer;
  _pcf8574 = NULL;
}


/**
 * 
 * O método differentialDriveBegin tem como objetivo iniciar, de forma fácil e objetiva, um mecanismo de controle de motores usando duas pontes H para a locomoção de um veículo através do método diferencial. Esse método segue o mesmo princípio de locomoção de um trator de esteira, onde cada esteira é acionada por um motor separado, permitindo que elas girem em velocidades diferentes. Para mudar de direção, o trator ajusta a velocidade de rotação de uma esteira em relação à outra. Por exemplo, se o trator deseja girar para a esquerda, ele reduz a velocidade da esteira direita ou aumenta a velocidade da esteira esquerda, criando uma diferença de rotação que faz o trator virar para a esquerda.
 * @param speedDelay Valor em percentual sobre velocidade nominal do motor. Tem como finalidade gerar um atrazo de um dos motores para curva em movimento cuave.
*/
void ES_CarControl::differentialDriveBegin(ES_PCF8574* pcf8574, ES_Buzzer* buzzer, uint8_t motor1Pin1, uint8_t motor1Pin2, uint8_t motor2Pin1, uint8_t motor2Pin2, uint8_t frontLightsPin, uint8_t backLightsPin, uint8_t stop, uint8_t forward, uint8_t back, uint8_t left, uint8_t right, uint8_t forwardLeft, uint8_t forwardRight, uint8_t backLeft, uint8_t backRight, uint8_t frontLightsOn, uint8_t frontLightsOff, uint8_t backLightsOn, uint8_t backLightsOff, uint8_t hornOn, uint8_t hornOff, uint8_t extraOn, uint8_t extraOff, uint8_t speedDelay ) {
  _buzzer = buzzer;
  _buzzer->begin();

  differentialDriveBegin(pcf8574, motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, frontLightsPin, backLightsPin, stop, forward, back, left, right, forwardLeft, forwardRight, backLeft, backRight, frontLightsOn, frontLightsOff, backLightsOn, backLightsOff, hornOn, hornOff,  extraOn, extraOff, speedDelay );

}

void ES_CarControl::differentialDriveBegin(ES_PCF8574* pcf8574, uint8_t motor1Pin1, uint8_t motor1Pin2, uint8_t motor2Pin1, uint8_t motor2Pin2, uint8_t frontLightsPin, uint8_t backLightsPin, uint8_t stop, uint8_t forward, uint8_t back, uint8_t left, uint8_t right, uint8_t forwardLeft, uint8_t forwardRight, uint8_t backLeft, uint8_t backRight, uint8_t frontLightsOn, uint8_t frontLightsOff, uint8_t backLightsOn, uint8_t backLightsOff, uint8_t hornOn, uint8_t hornOff, uint8_t extraOn, uint8_t extraOff, uint8_t speedDelay ) {
  _pcf8574 = pcf8574;
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

  _buzzer->begin();

  _pcf8574->motorBegin(0, _motor1Pin1, _motor1Pin2);
  _pcf8574->motorBegin(1, _motor2Pin1, _motor2Pin2);
  
}

void ES_CarControl::setSpeed(uint8_t value) {
  _speed = value;
}

uint8_t ES_CarControl::getSpeed() {
  return _speed;
}

void ES_CarControl::setSpeedDelay(uint8_t value) {
  _speedDelay = value;
}

uint8_t ES_CarControl::getSpeedDelay() {
  return _speedDelay;
}

void ES_CarControl::stop() {
  _pcf8574->motorStop(0);
  _pcf8574->motorStop(1);
}

void ES_CarControl::forward() {
  _pcf8574->motorRotationA(0, _speed);
  _pcf8574->motorRotationA(1, _speed);
}

void ES_CarControl::backward() {
  _pcf8574->motorRotationB(0, _speed);
  _pcf8574->motorRotationB(1, _speed);
}

void ES_CarControl::left() {
  _pcf8574->motorRotationB(0, _speed);
  _pcf8574->motorRotationA(1, _speed);
}

void ES_CarControl::right() {
  _pcf8574->motorRotationA(0, _speed);
  _pcf8574->motorRotationB(1, _speed);
}

void ES_CarControl::forwardLeft() {
  _pcf8574->motorRotationA(0, _speed * (_speedDelay / 100.0));
  _pcf8574->motorRotationA(1, _speed);
}

void ES_CarControl::forwardRight() {
  _pcf8574->motorRotationA(0, _speed);
  _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
}

void ES_CarControl::backLeft() {
  _pcf8574->motorRotationB(0, _speed * (_speedDelay / 100.0));
  _pcf8574->motorRotationB(1, _speed);
}

void ES_CarControl::backRight() {
  _pcf8574->motorRotationB(0, _speed);
  _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
}

void ES_CarControl::frontLights(boolean status) {
  _pcf8574->digitalWrite(_frontLightsPin, status);
}

void ES_CarControl::backLights(boolean status) {
  _pcf8574->digitalWrite(_backLightsPin, status);
}

void ES_CarControl::horn() {
  _buzzer->sound(NOTE_C4, 500);
  _buzzer->end(0);
}

void ES_CarControl::extra(boolean status) {
  if(status){
    _pcf8574->pwmWrite(_frontLightsPin, 50, 1);  // Aciona o pulso PWM 
    _pcf8574->pwmWrite(_backLightsPin, 50, 1);
  }else{
    _pcf8574->pwmWrite(_frontLightsPin, 50, 0);  // Desativa o pulso PWM 
    _pcf8574->pwmWrite(_backLightsPin, 50, 0);
  }
}


void ES_CarControl::controlCommand(char command){
  if(command == _stop){
    stop();
  }else if(command == _forward){  // Aciona todos os motores para FRENTE.
    forward();
  }else if(command == _back){ // Aciona todos os motores para TRÁS.
    backward();
  }else if(command == _left){ // Vira para a ESQUERDA.
    left();
  }else if(command == _right){  // Vira para a DIREITA.
    right();
  }else if(command == _forwardLeft){  // Vai para FRETE virando levemente para a ESQUERDA.
    forwardLeft();
  }else if(command == _forwardRight){ // Vai para FRETE virando levemente para a DIREITA.
    forwardRight();
  }else if(command == _backLeft){   // Vai para TRÁS virando levemente para a ESQUERDA.
    backLeft();
  }else if(command == _backRight){  // Vai para TRÁS virando levemente para a DIREITA.
    backRight();
  }else if(command == _frontLightsOn){  // Liga a luz dianteira.
    frontLights(true);
  }else if(command == _frontLightsOff){ // Apaga a luz dianteira.
    frontLights(false);
  }else if(command == _backLightsOn){   // Liga a luz traseira.
    backLights(true);
  }else if(command == _backLightsOff){  // Apaga a luz traseira.
    backLights(false);
  }else if(command == _hornOn){   // Aciona a buzina.
    horn();
  }else if(command == _hornOff){  // Desativa a buzina.
    horn();
  }else if(command == _extraOn){  // Aciona o pisca alerta
    extra(true);
  }else if(command == _extraOff){ // Desliga o pisca alerta
    extra(false);
  }else if(command >= '0' && command <= '9'){
    _speed = command - '0';
    _speed = _speed * 10;
  }else{
    stop();
  }

}

void ES_CarControl::controlCommand(Stream& serial){
  if (serial.available()) { //  Verifica se existem informações
    controlCommand(serial.read());
  }
}