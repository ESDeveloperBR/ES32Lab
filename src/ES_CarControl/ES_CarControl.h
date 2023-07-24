#ifndef ES_CARCONTROL_H
#define ES_CARCONTROL_H

#include <Arduino.h>
#include "ES_PCF8574/ES_PCF8574.h"
#include "ES_Buzzer/ES_Buzzer.h"

#define ES_CAR_CONTROL_VERSION "0.2.3 update 07/23/2023"  // mm/dd/yyyy

#define DIFFERENTIAL 0  // Modo de direção diferencial
#define FRONT 1         // Modo de direção dianteira

class ES_CarControl {
  private:
    ES_PCF8574* _pcf8574;
    ES_Buzzer*  _buzzer;

    uint8_t _drivingMode;
    uint8_t _speed = 20;
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

    boolean _invertDirection = false;
    boolean _invertTraction = false;

  public:
    ES_CarControl();
    ES_CarControl(ES_Buzzer* buzzer);
    ES_CarControl(ES_PCF8574* pcf8574);
    ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer);

/*
    void differentialDriveBegin(uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void differentialDriveBegin(ES_PCF8574* pcf8574, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void differentialDriveBegin(ES_PCF8574* pcf8574, ES_Buzzer* buzzer, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
*/
/*
    void frontSteeringDriveBegin(uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void frontSteeringDriveBegin(ES_PCF8574* pcf8574, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void frontSteeringDriveBegin(ES_PCF8574* pcf8574, ES_Buzzer* buzzer, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
*/

    void begin(uint8_t drivingMode = 0, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void begin(ES_PCF8574* pcf8574, uint8_t drivingMode = 0, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);
    void begin(ES_PCF8574* pcf8574, ES_Buzzer* buzzer, uint8_t drivingMode = 0, uint8_t motor1Pin1 = 4, uint8_t motor1Pin2 = 5, uint8_t motor2Pin1 = 6, uint8_t motor2Pin2 = 7, uint8_t frontLightsPin = 0, uint8_t backLightsPin = 1, uint8_t stop = 'S', uint8_t forward = 'F', uint8_t back = 'B', uint8_t left = 'L', uint8_t right = 'R', uint8_t forwardLeft = 'G', uint8_t forwardRight = 'I', uint8_t backLeft = 'H', uint8_t backRight = 'J', uint8_t frontLightsOn = 'W', uint8_t frontLightsOff = 'w', uint8_t backLightsOn = 'U', uint8_t backLightsOff = 'u', uint8_t hornOn = 'V', uint8_t hornOff = 'v', uint8_t extraOn = 'X', uint8_t extraOff = 'x', uint8_t speedDelay = 40);


    void controlCommand(char command);
    void controlCommand(Stream& serial);

    void setSpeed(uint8_t value);
    uint8_t getSpeed();
    void setSpeedDelay(uint8_t value);
    uint8_t getSpeedDelay();

    void stop();
    void forward();
    void backward();
    void left();
    void right();

    void forwardLeft();
    void forwardRight();
    void backLeft();
    void backRight();
    void frontLights(boolean status);
    void backLights(boolean status);
    void horn();
    void extra(boolean status);

    void invertMotorCommands(uint8_t motorID);
    boolean invertMotorStatus(uint8_t motorID);

    void invertDirection();
    boolean invertDirectionStatus();

    void invertTraction();
    boolean invertTractionStatus();
};

#endif
