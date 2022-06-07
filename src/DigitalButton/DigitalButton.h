/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 12/12/2018
*/
#ifndef DIGITALBUTTON_H
#define DIGITALBUTTON_H

#include <Arduino.h>

#define DIGITALBUTTON_VERSION "0.2.7 update 07/06/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
/*
  class DigitalButton
*/
class DigitalButton{
  private:
    int     _pin;             // Pino a ser utilizado pelo botão ou sensor
    boolean _btPress = false; // Botão pressionado inicia com "false"
    boolean _btRelease = true;// Botão está solto. "True"
    
  public:
    DigitalButton(int pin = -1);
    void begin(int pin);
    void begin();
    void setPino(int pin);
    boolean hold();
    boolean press();
    boolean release();
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
#endif