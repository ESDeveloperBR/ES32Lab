/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 12/12/2018
  Ultima Alteração: 31/05/20222
  Versão: 0.2.1
*/

#ifndef DigitalButton_H
#define DigitalButton_H

#include <Arduino.h>

// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class DigitalButton{
  private:
    int     _pin;             // Pino a ser utilizado pelo botão ou sensor
    boolean _btPress = false; // Botão pressionado inicia com "false"
    
  public:
    // <<<<<<<< Método >>>>>>
    void setPino(int pino); // Inicializa o pino do botão
    boolean hold();         // Retorna "true" enquanto o botão estiver pressionado
    boolean press();        // Retorna "true" quando o botão for pressionado
    boolean release();      // Retorna "true" quando o botão for solto
};
// <<<<<<<<<<<<<<<< Inicializa o pino do botão >>>>>>>>>>>>>>>>>>>>>>>>>>
/* Initialize button pin.
- pin: Address of the GPIO that is connected to the button or sensor
*/
void DigitalButton::setPino(int pin){
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}
// <<<<<<< Retorna "true" enquanto o botão estiver pressionado >>>>>>>>>>>>>>>>
/* Returns "true" while the button is hold.
*/
boolean DigitalButton::hold(){
  if( !digitalRead(_pin) ) { 
    return true;
  }
  return false;
}
// <<<<<<<<<<<<<<<<<<<<<< Retorna "true" quando o botão for pressionado >>>>>>>>>>>>>>>>>>>
/* Returns "true" when the button is pressed.
*/
boolean DigitalButton::press(){
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
boolean DigitalButton::release(){
  if( !digitalRead(_pin) & !_btPress ) {
    _btPress = true;
  } else if(digitalRead(_pin) & _btPress ){
    _btPress = false;
    return true;
  }
  return false;
 }

#endif