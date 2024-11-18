#ifndef ES_PCF8574_H
#define ES_PCF8574_H

#include <Arduino.h>
#include <Wire.h>
#include "TimeInterval/TimeInterval.h"

#define ES_PCF8574_VERSION "0.7.2 update 11/18/2024"  // mm/dd/yyyy

#define ES_PCF8574_TASK_PWM_SIM_STACK_DEPTH 1200  // Sets the amount of memory available for local variables and function calls within the PWM simulator. | Define a quantidade de memória disponível para as variáveis locais e chamadas de função dentro do simulador PWM.
#define ES_PCF8574_TASK_PWM_SIM_PRIORITY 2         // Represents the task priority. Higher values indicate higher priority. | Representa a prioridade da tarefa. Valores maiores indicam maior prioridade.
#define ES_PCF8574_TASK_PWM_SIM_CORE_ID 0          // Specifies the processor core where the PWM simulator will run. | Especifica o núcleo do processador onde o simulador PWM será executado.

#define EX0 0
#define EX1 1
#define EX2 2
#define EX3 3
#define EX4 4
#define EX5 5
#define EX6 6
#define EX7 7

class ES_PCF8574 {

  private:
    uint8_t _address;
    uint8_t _value;
    boolean _btPress[8] = {false, false, false, false, false, false, false, false}; // Button pressed starts with "false"
    boolean _btRelease[8] = {true, true, true, true, true, true, true, true}; // The button is released "True"  
    boolean _pwmSimulation(uint8_t pin); // Gera o siclo do pulso PWM.
    boolean _pwmSimulationStatus; // Indica se o simulador de PWM está ativo.

    float   _pwmDutyCycle[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // Matriz onde cada endereço representa uma GPIO da expansão i2C, onde será armazenado o comprimento do Duty Cycle.
    float   _pwmFrequency[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // Matriz onde cada endereço representa uma GPIO da expansão i2C, onde será armazenado a frequência PWM independente de cada GPIO.
    TimeInterval _pwmDutyTime[8]; // Matriz do tipo 'TimeInterval' responsável com controlar o tempo de ciclo de cada GPIO a ser utilizada para gerar pulso PWM.

    uint8_t _motorFrequency[4] = {20, 20, 20, 20};
    uint8_t _motorPin1[4];
    uint8_t _motorPin2[4];
    bool    _invertMotorCommands[4];

    bool  _isI2CInitialized = false;

  public:
    ES_PCF8574(uint8_t address=0x00);

    String scanI2C();
    boolean begin(boolean pwmSimulation = false);
    void digitalWrite(uint8_t pin, boolean value);
    boolean digitalRead(uint8_t pin);

    boolean btHold(uint8_t pin,    boolean activateHigh = true);
    boolean btPress(uint8_t pin,   boolean activateHigh = true);
    boolean btRelease(uint8_t pin, boolean activateHigh = true);

    boolean pwmBegin();
    void pwmWrite(uint8_t pin, uint8_t dutyCycle = 50, uint8_t frequency = 1);

    boolean motorBegin(uint8_t motorID, uint8_t controlPin1, uint8_t controlPin2);
    void motorRotationA(uint8_t motorID, uint8_t speed);
    void motorRotationB(uint8_t motorID, uint8_t speed);
    void motorStop(uint8_t motorID);

    void invertMotorCommands(uint8_t motorID);
    boolean invertMotorStatus(uint8_t motorID);
    
    uint8_t getMotorFrequency(uint8_t motorID);
    void setMotorFrequency(uint8_t motorID, uint8_t frequency);

};

#endif