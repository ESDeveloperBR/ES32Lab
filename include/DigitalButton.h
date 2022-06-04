/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 12/12/2018
*/
#ifndef DigitalButton_H
#define DigitalButton_H

#include <Arduino.h>

#define DIGITALBUTTON_VERSION "0.2.4 update 06/03/2022"  // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class DigitalButton{
  private:
    int     _pin;             // Pino a ser utilizado pelo botão ou sensor
    boolean _btPress = false; // Botão pressionado inicia com "false"
    
  public:
    // <<<<<<<<<<<<<<<< Inicializa o pino do botão >>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Initialize button pin.
    - pin: Address of the GPIO that is connected to the button or sensor
    */
    void setPino(int pin){
      _pin = pin;
      pinMode(_pin, INPUT_PULLUP);
    }

    // <<<<<<< Retorna "true" enquanto o botão estiver pressionado >>>>>>>>>>>>>>>>
    /* Returns "true" while the button is hold.
    */
    boolean hold(){
      if( !digitalRead(_pin) ) { 
        return true;
      }
      return false;
    }

    // <<<<<<<<<<<<<<<<<<<<<< Retorna "true" quando o botão for pressionado >>>>>>>>>>>>>>>>>>>
    /* Returns "true" when the button is pressed.
    */
    boolean press(){
      if( !digitalRead(_pin) & !_btPress ) { 
        _btPress = true;
        return true;
      } else if( digitalRead(_pin) & _btPress ) {
        _btPress = false;
      }
      return false;
    }

    // <<<<<<< Retorna "true" quando o botão for solto >>>>>>>>>>>>
    /* Returns "true" when the button is released.
    */
    boolean release(){
      if( !digitalRead(_pin) & !_btPress ) {
        _btPress = true;
      } else if(digitalRead(_pin) & _btPress ){
        _btPress = false;
        return true;
      }
      return false;
    }
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
#endif