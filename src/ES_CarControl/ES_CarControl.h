#ifndef ES_CARCONTROL_H
#define ES_CARCONTROL_H

#include <Arduino.h>
#include "ES_PCF8574/ES_PCF8574.h"
#include "ES_Buzzer/ES_Buzzer.h"

#define ES_CAR_CONTROL_VERSION "0.4.2 update 11/22/2024" // mm/dd/yyyy

#define DIFFERENTIAL 0 // Modo de direção diferencial
#define FRONTAL 1      // Modo de direção dianteira

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

    //boolean _invertDirection = false;
    //boolean _invertTraction  = false;

    // Ponteiros para funções externas
    void (*_customHornFunction)(bool) = nullptr;
    void (*_customFrontLightsFunction)(bool) = nullptr;
    void (*_customBackLightsFunction)(bool) = nullptr;
    void (*_customExtraFunction)(bool) = nullptr;

    // Ponteiros para funções associadas aos movimentos
    void (*_customForwardFunction)(uint8_t) = nullptr;
    void (*_customBackwardFunction)(uint8_t) = nullptr;
    void (*_customLeftFunction)(uint8_t) = nullptr;
    void (*_customRightFunction)(uint8_t) = nullptr;
    void (*_customForwardLeftFunction)(uint8_t) = nullptr;
    void (*_customForwardRightFunction)(uint8_t) = nullptr;
    void (*_customBackLeftFunction)(uint8_t) = nullptr;
    void (*_customBackRightFunction)(uint8_t) = nullptr;

  public:
    // Construtores
    ES_CarControl(ES_PCF8574* pcf8574);
    ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer);

    // Inicialização
    boolean begin(uint8_t drivingMode = 0, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, 
               uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', 
               uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', 
               uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', 
               uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', 
               uint8_t speedDelay = 40, uint8_t speed0 = '0', uint8_t speed1 = '1', uint8_t speed2 = '2', uint8_t speed3 = '3', uint8_t speed4 = '4',
               uint8_t speed5 = '5', uint8_t speed6 = '6', uint8_t speed7 = '7', uint8_t speed8 = '8', uint8_t speed9 = '9', uint8_t speed10 = 'q'          
               );

    // Controle de comandos
    void controlCommand(char command);
    void controlCommand(Stream& serial);

    // Ajustes de velocidade
    void setSpeed(uint8_t value);
    uint8_t getSpeed();
    void setSpeedDelay(uint8_t value);
    uint8_t getSpeedDelay();

    // Movimentos básicos
    void stop();
    void forward();
    void forward(uint8_t speed);
    void backward();
    void backward(uint8_t speed);
    void left();
    void left(uint8_t speed);
    void right();
    void right(uint8_t speed);

    // Movimentos avançados
    void forwardLeft();
    void forwardLeft(uint8_t speed);
    void forwardRight();
    void forwardRight(uint8_t speed);
    void backLeft();
    void backLeft(uint8_t speed);
    void backRight();
    void backRight(uint8_t speed);

    // Controle de luzes e buzina
    void frontLights(boolean status);
    void backLights(boolean status);
    void horn(boolean status);
    void extra(boolean status);

    // Funções externas
    void setHornFunction(void (*callback)(bool));
    void setFrontLightsFunction(void (*callback)(bool));
    void setBackLightsFunction(void (*callback)(bool));
    void setExtraFunction(void (*callback)(bool));

    // Funções externas associadas aos movimentos
    void setForwardFunction(void (*callback)(uint8_t));
    void setBackwardFunction(void (*callback)(uint8_t));
    void setLeftFunction(void (*callback)(uint8_t));
    void setRightFunction(void (*callback)(uint8_t));
    void setForwardLeftFunction(void (*callback)(uint8_t));
    void setForwardRightFunction(void (*callback)(uint8_t));
    void setBackLeftFunction(void (*callback)(uint8_t));
    void setBackRightFunction(void (*callback)(uint8_t));

    // Inversão de controle
    void invertMotorCommands(uint8_t motorID);
    boolean invertMotorStatus(uint8_t motorID);
    //void invertDirection();
    //boolean invertDirectionStatus();
    //void invertTraction();
    //boolean invertTractionStatus();
};

#endif
