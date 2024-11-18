#include <Arduino.h>
#include "ES_PCF8574.h"
/**
 * Constructor of the ES_PCF8574 class.
 * |
 * Construtor da classe ES_PCF8574
 * @param address The address of the PCF8574 in the I2C communication protocol. Initializes an instance of the ES_PCF8574 class with the provided PCF8574 address. | Endereço do PCF8574 no protocolo de comunicação I2C. Inicializa uma instância da classe ES_PCF8574 com o endereço do PCF8574 fornecido.
 */
ES_PCF8574::ES_PCF8574(uint8_t address) {
  _address = address;
  _value = 0;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< scanI2CDevices >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Scans and returns all I2C device addresses connected to the I2C bus.
 * |
 * Varre e retorna todos os endereços de dispositivos I2C conectados ao barramento I2C.
 * @return A String containing all detected I2C addresses in hexadecimal format. If no devices are found, returns an empty String (""). | Uma String contendo todos os endereços I2C detectados em formato hexadecimal. Se nenhum dispositivo for encontrado, retorna uma String vazia ("").
 */
String ES_PCF8574::scanI2C() {
  if (!_isI2CInitialized) {  // Checa se I2C já foi inicializado
    _isI2CInitialized = Wire.begin();
  }
  
  byte error, address;
  int nDevices = 0;
  String result = "";

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      if(result!="") result += ", ";
      result += "0x";
      if (address < 16) result += "0";  // Adds leading zero for addresses below 0x10
      result += String(address, HEX);
      nDevices++;
    } else if (error == 4) {
      result += "Unknown error at address 0x";
      if (address < 16) result += "0";
      result += String(address, HEX) + "\n";
    }
  }
  if (nDevices == 0) {
    result = "";
  }
  return result;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< begin | início >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Initializes the I2C communication and configures the PCF8574. Returns true if the communication was successfully initialized, otherwise returns false.
 * | 
 * Inicializa a comunicação I2C e configura o PCF8574. Retorna true se a comunicação foi iniciada com sucesso, caso contrário, retorna false.
 * @param pwmSimulation When true, activates the PWM simulator through the I2C expander. | Quando o valor for verdadeiro, ativa o simulador PWM através do expansor i2C.
*/
boolean ES_PCF8574::begin(boolean pwmSimulation){
  _isI2CInitialized = Wire.begin();
  if(_isI2CInitialized){
    Wire.beginTransmission(_address);
    Wire.write(_value);
    _isI2CInitialized = !Wire.endTransmission();

    // ---- Starts the LOOP that generates the simulated PWM pulse | Inicia o LOOP que gera o pulso PWM simulado ----
    if (!_pwmSimulationStatus && pwmSimulation) {  // Controls the activation of the PWM simulator by creating a task with a LOOP execution. | Controla a ativação do simulador PWM criando uma tarefa com um LOOP de execução.
      _pwmSimulationStatus = pwmSimulation; // Changes the status of the flag that indicates whether the PWM simulator is active. | Altera o status da flag que indica se o simulador PWM está ativo.

      xTaskCreatePinnedToCore([](void* parameter){
        ES_PCF8574* instance = static_cast<ES_PCF8574*>(parameter); // Get the instance of the ES_PCF8574 class from the parameter. | Obtém a instância da classe ES_PCF8574 a partir do parâmetro.
        boolean enablePWM = false;

        while (true) {
          for(uint_fast8_t i = 0; i < 8; i++){
            if(enablePWM){
              instance->_pwmSimulation(i);
            }else{
              enablePWM = instance->_pwmSimulation(i);
            }
          }

          if(enablePWM){  // This flag controls the execution of the PWM simulator LOOP. If no PWM pulse is being generated, a pause is executed in the 'loopPWMSimulation' to reduce processor usage. | Essa flag controla a execução do LOOP do simulador PWM. Se nenhum pulso PWM estiver sendo gerado, é executada uma pausa no 'loopPWMSimulation' para reduzir o uso do processador.
            enablePWM = false;
          }else{
            vTaskDelay(pdMS_TO_TICKS(100)); // Adds a small delay to the LOOP to reduce unnecessary processor usage. | Adiciona um pequeno atraso no LOOP para reduzir o uso desnecessário do processador.
          }

        }
      }, "loopPWMSimulation", ES_PCF8574_TASK_PWM_SIM_STACK_DEPTH, this, ES_PCF8574_TASK_PWM_SIM_PRIORITY, NULL, ES_PCF8574_TASK_PWM_SIM_CORE_ID); // Creates the LOOP responsible for running the PWM simulator. | Cria o LOOP responsável por executar o simulador PWM.
    }
  }
  return _isI2CInitialized;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< digitalWrite >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Sets the logical value HIGH or LOW for a specific GPIO of PCF8574. | Define o valor lógico HIGH ou LOW para uma GPIO específica do PCF8574.
 * @param pin Number of the GPIO to be changed. | Número da GPIO que será alterada.
 * @param value Logical value to be assigned to the GPIO (true for HIGH, false for LOW). | Valor lógico a ser atribuído à GPIO (true para HIGH, false para LOW).
 */
void ES_PCF8574::digitalWrite(uint8_t pin, boolean value) {
  if (value) {
    _value |= (1 << pin);
  } else {
    _value &= ~(1 << pin);
  }

  Wire.beginTransmission(_address);
  Wire.write(_value);
  Wire.endTransmission();
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< digitalRead >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Reads the logical signal present on a specific GPIO of PCF8574.
 * The read value is returned as an 8-bit integer (0 for LOW, 1 for HIGH).
 * | 
 * Realiza a leitura do sinal lógico presente em uma GPIO específica do PCF8574.
 * O valor lido é retornado como um inteiro de 8 bits (0 para LOW, 1 para HIGH).
 * 
 * @param pin Number of the GPIO to be read. | Número da GPIO que será lida.
 */
boolean ES_PCF8574::digitalRead(uint8_t pin) {
  Wire.requestFrom(_address, (uint8_t)1);
  uint8_t data = Wire.read();
  return (data >> pin) & 1;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< btHold >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Checks if the specified GPIO on the I2C expansion PCF8574 is being used as a button input and is currently held down.
 * Returns 'true' while the button remains pressed, maintaining a logical high or low level based on configuration.
 * | 
 * Verifica se a GPIO especificada na expansão I2C PCF8574 está sendo utilizada como entrada de botão e está pressionada.
 * Retorna 'true' enquanto o botão permanecer pressionado, mantendo um nível lógico alto ou baixo conforme configurado.
 * @param pin Number of the GPIO on the PCF8574 expansion to be read. | Número da GPIO na expansão PCF8574 que será lida.
 * @param activateHigh Configures whether the logical high level (true) or logical low level (false) indicates the button press. | Configura se o nível lógico alto (true) ou baixo (false) indica a pressão do botão.
 * @return 'true' if the button is being held down at the specified logical level, otherwise 'false'. | 'true' se o botão estiver sendo pressionado no nível lógico especificado, caso contrário, 'false'.
 */
boolean ES_PCF8574::btHold(uint8_t pin, boolean activateHigh){
  digitalWrite(pin, !activateHigh);
  if(activateHigh){
    if( digitalRead(pin) ) { 
      return true;
    }
  }else{
    if(!digitalRead(pin) ) { 
      return true;
    }
  }
  return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< btPress >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * The 'true' condition is returned at the exact moment when the expansion GPIO on the I2C PCF8574 is used as a button input, and a transition occurs from a low to high logical level, that is, when the button is pressed.
 * | 
 * A condição 'true' é retornada no exato momento em que a GPIO da expansão I2C PCF8574 é utilizada como entrada de botão e ocorre a transição do nível lógico de baixo para alto, ou seja, quando o botão é pressionado.
 * @param pin Number of the GPIO on the PCF8574 expansion to be read. | Número da GPIO na expansão PCF8574 que será lida.
 * @param activateHigh Configures whether the transition to a logical high level (true) or a logical low level (false) indicates the button press. | Configura se a transição para o nível lógico alto (true) ou baixo (false) indica a pressão do botão.
 * @return 'true' if the button is pressed at the specified logical transition, otherwise 'false'. | 'true' se o botão for pressionado na transição lógica especificada, caso contrário, 'false'.
 */
boolean ES_PCF8574::btPress(uint8_t pin, boolean activateHigh){
  if( !btHold(pin, activateHigh) && !_btPress[pin] ) { 
    _btPress[pin] = true;
  } else if( btHold(pin, activateHigh) && _btPress[pin] ) {
    _btPress[pin] = false;
    return true;
  }
  return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< btRelease >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * The 'true' condition is returned at the exact moment when the expansion GPIO on the I2C PCF8574 is used as a button input, and a transition occurs from a high to low logical level, that is, when the button is released.
 * | 
 * A condição 'true' é retornada no exato momento em que a GPIO da expansão I2C PCF8574 é utilizada como entrada de botão e ocorre a transição do nível lógico de alto para baixo, ou seja, quando o botão é solto.
 * @param pin Number of the GPIO on the PCF8574 expansion to be read. | Número da GPIO na expansão PCF8574 que será lida.
 * @param activateHigh Configures whether the transition to a logical low level (true) or a logical high level (false) indicates the button release. | Configura se a transição para o nível lógico baixo (true) ou alto (false) indica a liberação do botão.
 * @return 'true' if the button is released at the specified logical transition, otherwise 'false'. | 'true' se o botão for solto na transição lógica especificada, caso contrário, 'false'.
 */
boolean ES_PCF8574::btRelease(uint8_t pin, boolean activateHigh){
  if( !btHold(pin, activateHigh) && !_btRelease[pin] ) {
    _btRelease[pin] = true;
    return true;
  } else if(btHold(pin, activateHigh) && _btRelease[pin] ){
    _btRelease[pin] = false;
  }
  return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< pwmBegin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Initializes the I2C expander with the PWM simulator enabled.
 * |
 * Inicializa o expansor I2C com o simulador PWM ativado.
*/
boolean ES_PCF8574::pwmBegin(){
  return begin(true);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< pwmWrite >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Assigns values such as frequency and duty cycle to the simulated GPIO for the PWM signal. Attention: the maximum frequency cannot exceed 200 Hz.
 * | 
 * Atribui valores como frequência e ciclo de trabalho à GPIO simulada para o sinal PWM. Atenção: a frequência máxima não pode exceder 200 Hz.
 * @param pin Number of the GPIO to be used. | Número da GPIO a ser utilizada.
 * @param dutyCycle Duty cycle value as a percentage of the PWM signal. Acceptable values range from 0% to 100%. | Informação do tamanho do ciclo de trabalho em porcentagem do sinal PWM. Os valores aceitáveis estão entre 0% e 100%.
 * @param frequency PWM signal frequency. The maximum value cannot exceed 100%. | Frequência do sinal PWM. O valor máximo não pode exceder 100%.
*/
void ES_PCF8574::pwmWrite(uint8_t pin, uint8_t dutyCycle, uint8_t frequency){
  _pwmDutyCycle[pin] = (dutyCycle > 100) ? 100 : dutyCycle;
  _pwmFrequency[pin] = (frequency > 200) ? 200 : frequency;

  if(!_pwmFrequency[pin]){  // If the frequency assigned to the GPIO is equal to 0, disable the PWM pulse. | Se a frequência atribuída à GPIO for igual a 0, desativa o pulso PWM.
    digitalWrite(pin, LOW);
  }
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< motorBegin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * This method is responsible for associating two GPIOs of the I2C expander with an H-bridge for motor control.
 * | 
 * Este método é responsável por associar duas GPIOs da expansão i2C à ponte H para o controle de motores.
 * @param motorID Motor identification for control and association. | Identificação para o controle e associação do motor.
 * @param controlPin1 Control pin 1 of the I2C expander, responsible for motor acceleration and direction. | Pino de controle 1 da expansão i2C, responsável pela aceleração e direção do motor.
 * @param controlPin2 Control pin 2 of the I2C expander, responsible for motor acceleration and direction. | Pino de controle 2 da expansão i2C, responsável pela aceleração e direção do motor.
*/
boolean ES_PCF8574::motorBegin(uint8_t motorID, uint8_t controlPin1, uint8_t controlPin2){
  _motorPin1[motorID] = controlPin1;
  _motorPin2[motorID] = controlPin2;
  return begin(true);  // Initializes the I2C expander and activates the PWM simulator. | Inicializa o expanso i2C e ativa o simulador PWM.
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< motorStop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Stops the motor indicated by the 'motorID' parameter.
 * |
 * Interrompe o motor indicado pelo parâmetro 'motorID'.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
void ES_PCF8574::motorStop(uint8_t motorID){
  motorRotationA(motorID, 0); // Stops motor rotation A. | Interrompe a rotação A do motor.
  motorRotationB(motorID, 0); // Stops motor rotation B. | Interrompe a rotação B do motor.
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< motorRotationA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Activates the motor with the specified ID to rotate in the 'A' direction at a specific speed.
 * |
 * Aciona o motor com base na sua ID para girar na direção 'A', com uma velocidade específica.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
 * @param speed Speed at which the motor should rotate. This value should range from 0% to 100% of its maximum speed. | Velocidade na qual o motor deve girar. Esse valor deve variar entre 0% e 100% de sua velocidade máxima.
*/
void ES_PCF8574::motorRotationA(uint8_t motorID, uint8_t speed){
  speed = (speed > 100) ? 100 : speed;

  if(_invertMotorCommands[motorID]){
    pwmWrite(_motorPin1[motorID], speed, _motorFrequency[motorID]);
    pwmWrite(_motorPin2[motorID], 0, 0);
  }else{
    pwmWrite(_motorPin1[motorID], 0, 0);    
    pwmWrite(_motorPin2[motorID], speed, _motorFrequency[motorID]);
  }
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< motorRotationB >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Activates the motor with the specified ID to rotate in the 'B' direction at a specific speed.
 * |
 * Aciona o motor com base na sua ID para girar na direção 'B', com uma velocidade específica.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
 * @param speed Speed at which the motor should rotate. This value should range from 0% to 100% of its maximum speed. | Velocidade na qual o motor deve girar. Esse valor deve variar entre 0% e 100% de sua velocidade máxima.
*/
void ES_PCF8574::motorRotationB(uint8_t motorID, uint8_t speed){
  if(_invertMotorCommands[motorID]){
    pwmWrite(_motorPin1[motorID], 0, 0);
    pwmWrite(_motorPin2[motorID], speed, _motorFrequency[motorID]);
  }else{
    pwmWrite(_motorPin1[motorID], speed, _motorFrequency[motorID]);
    pwmWrite(_motorPin2[motorID], 0, 0);    
  }
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< invertMotorCommands >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Inverts the direction of the 'motorRotationA' and 'motorRotationB' methods. Ideal for when the motor wires are not connected in the order in which the program was written.
 * |
 * Inverte a direção dos métodos 'motorRotationA' e 'motorRotationB'. Ideal para quando os fios do motor não foram ligados na ordem na qual o programa foi escrito.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
void ES_PCF8574::invertMotorCommands(uint8_t motorID){
  _invertMotorCommands[motorID] = !_invertMotorCommands[motorID];
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< invertMotorStatus >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Returns a boolean value indicating whether the motor has been configured to invert its rotation commands.
 * | 
 * Retorna um valor booleano indicando se o motor foi configurado para inverter seus comandos de rotação.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
boolean ES_PCF8574::invertMotorStatus(uint8_t motorID){
  return _invertMotorCommands[motorID];  
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< getMotorFrequency >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Returns the frequency value in hertz associated with a specific motor.
 * |
 * Retorna o valor da frequência em hertz associado a um motor específico.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
*/
uint8_t ES_PCF8574::getMotorFrequency(uint8_t motorID){
  return _motorFrequency[motorID];
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setMotorFrequency >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Sends a new frequency value in hertz associated with a specific motor.
 * |
 * Envia um novo valor da frequência em hertz associado a um motor específico.
 * @param motorID Identification for motor control and association. | Identificação para o controle e associação do motor.
 * @param frequency Frequency in hertz associated with the motor. | Frequência em hertz associado ao motor.
*/
void ES_PCF8574::setMotorFrequency(uint8_t motorID, uint8_t frequency){
  _motorFrequency[motorID] = frequency;
}
// ----------------------------------------------------------------------------------------------
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PRIVATE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ----------------------------------------------------------------------------------------------
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< _pwmSimulation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Manages a simulated PWM pulse on the I2C expander. ATTENTION: The I2C expander does not generate high-frequency PWM.
 * |
 * Gerencia um pulso PWM simulado no expansor i2C. ATENÇÃO: O expansor i2C não gera PWM de alta frequencia.
 * @param pin Number of the GPIO to be used. | Número da GPIO a ser utilizada.
*/
boolean ES_PCF8574::_pwmSimulation(uint8_t pin){
  bool pinStatus = (_value >> pin) & 1;

  if( (_pwmFrequency[pin]) && (_pwmDutyCycle[pin])){  // If the frequency and duty cycle are different from zero, do: | Se a frequência e o duty clycle for diferente de zero, faça:

    float period = 1000.0f / _pwmFrequency[pin];  // Calculates the period in milliseconds of a complete cycle. | Calcula o período em milissegundos de um ciclo completo.

    if(pinStatus){
      period = period * ( _pwmDutyCycle[pin] / 100);
    }else{
      period = period - (period * (_pwmDutyCycle[pin] / 100));
    }

    if(_pwmDutyTime[pin].intervalMillis(period)){
      if(pinStatus){
        digitalWrite(pin, LOW);  // Sets the expander pin to LOW. | Define o pino do expansor como LOW.
      }else{
        digitalWrite(pin, HIGH);  // Sets the expander pin to HIGH | Define o pino do expansor como HIGH.
      }

    }
    return true;
  }else{
    return false;
  }
}