#include "ES_CarControl.h"

ES_CarControl::ES_CarControl() {
  _buzzer = NULL;
  _pcf8574 = NULL;
}

ES_CarControl::ES_CarControl(ES_Buzzer* buzzer) {
  _buzzer = buzzer;
  _pcf8574 = NULL;
}

ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574) {
  _buzzer = NULL;
  _pcf8574 = pcf8574;
}

ES_CarControl::ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer) {
  _buzzer = buzzer;
  _pcf8574 = pcf8574;
}

/**
 * 
 * O método begin tem como objetivo iniciar, de forma fácil e objetiva, um mecanismo de controle de motores usando duas pontes H para a locomoção de um veículo. É extremamente importante a escolha do parâmetro drivingMode, que indicará qual tipo de direção será utilizado pelo veículo. Caso nenhuma opção seja indicada, será utilizada como padrão a opção 0: Direção Diferencial. Esse tipo de direção segue o mesmo princípio de locomoção de um trator de esteira, onde cada esteira é acionada por um motor separado, permitindo que elas girem em velocidades diferentes. Para mudar de direção, o trator ajusta a velocidade de rotação de uma esteira em relação à outra. Por exemplo, se o trator deseja girar para a esquerda, ele reduz a velocidade da esteira direita ou aumenta a velocidade da esteira esquerda, criando uma diferença de rotação que faz o trator virar para a esquerda.
 * @param drivingMode Escolha do tipo de direção, entre ela estão: 0: Direção Diferencial; 1: Direção Dianteira
 * @param speedDelay Valor em percentual sobre velocidade nominal do motor. Tem como finalidade gerar um atrazo de um dos motores para curva em movimento cuave.
*/
void ES_CarControl::begin(uint8_t drivingMode, uint8_t motor1Pin1, uint8_t motor1Pin2, uint8_t motor2Pin1, uint8_t motor2Pin2, uint8_t frontLightsPin, uint8_t backLightsPin, uint8_t stop, uint8_t forward, uint8_t back, uint8_t left, uint8_t right, uint8_t forwardLeft, uint8_t forwardRight, uint8_t backLeft, uint8_t backRight, uint8_t frontLightsOn, uint8_t frontLightsOff, uint8_t backLightsOn, uint8_t backLightsOff, uint8_t hornOn, uint8_t hornOff, uint8_t extraOn, uint8_t extraOff, uint8_t speedDelay ) {
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

  if(_buzzer != NULL){  // Verifica se o objeto da classe 'ES_Buzzer' foi repassado para o objeto instanciado da classe 'ES_CarControl'.
    _buzzer->begin();
  }else{
    Serial.println("Buzzer disable.");
  }

  if(_pcf8574 != NULL){ // Verifica se o objeto da classe 'ES_PCF8574' foi repassado para o objeto instanciado da classe 'ES_CarControl'.
    _pcf8574->motorBegin(0, _motor1Pin1, _motor1Pin2);
    _pcf8574->motorBegin(1, _motor2Pin1, _motor2Pin2);
  }else{
    Serial.println("Expansor i2C disable.");
    delay(3000);
  }
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
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    _pcf8574->motorStop(0);
    _pcf8574->motorStop(1);
  }else if(_drivingMode == 1){  
    // --- Direção dianteira ---
    _pcf8574->motorStop(0);
    _pcf8574->motorStop(1);
  }
}

void ES_CarControl::forward() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    _pcf8574->motorRotationA(0, _speed);
    _pcf8574->motorRotationA(1, _speed);
  }else if(_drivingMode == 1){
    // --- Direção dianteira ---
    _pcf8574->motorRotationA(0, _speed);
    _pcf8574->motorStop(1);
  }
}

void ES_CarControl::backward() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    _pcf8574->motorRotationB(0, _speed);
    _pcf8574->motorRotationB(1, _speed);
  }else if(_drivingMode == 1){
    // --- Direção dianteira ---
    _pcf8574->motorRotationB(0, _speed);
    _pcf8574->motorStop(1);
  }
}

void ES_CarControl::left() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationB(1, _speed);
    }else{
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationA(1, _speed);
    }
  }else if(_drivingMode == 1){
    // --- Direção dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(1, _speed);
    }else{
      _pcf8574->motorRotationA(1, _speed);
    }
    _pcf8574->motorStop(0);
  }
}

void ES_CarControl::right() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationA(1, _speed);
    }else{
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationB(1, _speed);
    }
  }else if(_drivingMode == 1){
    // --- Direção dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(1, _speed);
    }else{
      _pcf8574->motorRotationB(1, _speed);
    }
    _pcf8574->motorStop(0);
  }
}

void ES_CarControl::forwardLeft() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationA(0, _speed * (_speedDelay / 100.0));
      _pcf8574->motorRotationA(1, _speed);
    }
  }else if(_drivingMode == 1){
    // --- Direção Dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }
  }
}

void ES_CarControl::forwardRight() {
  if(_drivingMode == 0 ){     
    // --- Direção diferencial ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(0, _speed * (_speedDelay / 100.0));
      _pcf8574->motorRotationA(1, _speed);
    }else{
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }
  }else if(_drivingMode == 1){
    // --- Direção Dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationA(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }
  }
}

void ES_CarControl::backLeft() {
  if(_drivingMode == 0 ){
    // --- Direção diferencial ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationB(0, _speed * (_speedDelay / 100.0));
      _pcf8574->motorRotationB(1, _speed);
    }
  }else if(_drivingMode == 1){
    // --- Direção dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }    
  }
}

void ES_CarControl::backRight() {
  if(_drivingMode == 0 ){     // <-- Direção diferencial
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(0, _speed * (_speedDelay / 100.0));
      _pcf8574->motorRotationB(1, _speed);
    }else{
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }
  }else if(_drivingMode == 1){  // <-- Direção dianteira
    // --- Direção Dianteira ---
    if(_pcf8574->invertMotorStatus(1)){ // Se o motor estiver com a rotação espelhada, faça:
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationA(1, _speed * (_speedDelay / 100.0));
    }else{
      _pcf8574->motorRotationB(0, _speed);
      _pcf8574->motorRotationB(1, _speed * (_speedDelay / 100.0));
    }
  }
}

void ES_CarControl::frontLights(boolean status) {
  _pcf8574->digitalWrite(_frontLightsPin, status);
}

void ES_CarControl::backLights(boolean status) {
  _pcf8574->digitalWrite(_backLightsPin, status);
}

void ES_CarControl::horn() {
  if(_buzzer != NULL){
    _buzzer->sound(NOTE_C4, 500);
    _buzzer->end(0);
  }
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
    if(invertTractionStatus()){  // Se o tracionamento estiver invertido
      backward();
    }else{
      forward();
    }
  }else if(command == _back){ // Aciona todos os motores para TRÁS.
    if(invertTractionStatus()){  // Se o tracionamento estiver invertido
      forward();
    }else{
      backward();
    }    
  }else if(command == _left){ // Vira para a ESQUERDA.
    if(invertDirectionStatus()){  // Se a direção estiver invertida
      right();
    }else{
      left();
    }
  }else if(command == _right){  // Vira para a DIREITA.
    if(invertDirectionStatus()){  // Se a direção estiver invertida
      left();
    }else{
      right();
    }
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

/**
 * Inverts the direction of the 'motorRotationA' and 'motorRotationB' methods. Ideal for when the motor wires are not connected in the order in which the program was written.
 * |
 * Inverte a direção dos métodos 'motorRotationA' e 'motorRotationB'. Ideal para quando os fios do motor não foram ligados na ordem na qual o programa foi escrito.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
void ES_CarControl::invertMotorCommands(uint8_t motorID){
  _pcf8574->invertMotorCommands(motorID);
}

/**
 * Returns a boolean value indicating whether the motor has been configured to invert its rotation commands.
 * | 
 * Retorna um valor booleano indicando se o motor foi configurado para inverter seus comandos de rotação.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
boolean ES_CarControl::invertMotorStatus(uint8_t motorID){
  return _pcf8574->invertMotorStatus(motorID);
}

/**
 * Inverte o controle de direção do veiculo, logo ao executar o comando de virar para a esquerda o mesmo virará para a direita.
*/
void ES_CarControl::invertDirection(){
  _invertDirection = !_invertDirection;
}

/**
 * Retorna o status de inverção da direção, se estiver invertido retorna 'true', caso contrario retorna 'false'.
*/
boolean ES_CarControl::invertDirectionStatus(){
  return _invertDirection;
}

/**
 * Inverte o controle de tracionamento do veiculo, logo ao executar o comando de tracionar para frente o mesmo ira para trás. 
*/
void ES_CarControl::invertTraction(){
  _invertTraction = !_invertTraction;
}

/**
 * Retorna o status de inverção da tação, se estiver invertido retorna 'true', caso contrario retorna 'false'.
*/
boolean ES_CarControl::invertTractionStatus(){
  return _invertTraction;
}