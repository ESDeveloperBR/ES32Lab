/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 12/12/2018
  Ultima Alteração: 31/05/20222
  Versão: 0.2.0
*/

#ifndef DigitalButton_H
#define DigitalButton_H

#include <Arduino.h>

// <<<<<<<<<<<<<<< Classe Botão Externo >>>>>>>>>>>>>>
class DigitalButton{
  private:
    int     _pino;                  // Pino responsavel em habilitar ou não o drive do motor
    boolean _btPress = false; // Botão pressionado inicia com false
    
  public:
    // <<<<<<<< Método >>>>>>
    void setPino(int pino); // Configura qual o pino de leitura
    boolean hold();      // Retorna true interuptamente ao seguar o botão
    boolean press();   // Retorna true ao pressionar
    boolean release();       // Retorna true ao soltar
};
// <<<<<<<<< Configura qual pino será o botão >>>>>>>>>>
void DigitalButton::setPino(int pino){
  _pino = pino;
  pinMode(_pino, INPUT_PULLUP);
}
// <<<<<<< Retorna true interuptamente ao seguar o botão >>>>>>>>>>>>>>>>
boolean DigitalButton::hold(){
  if( !digitalRead(_pino) ) { 
    return true;
  }
  return false;
}
boolean DigitalButton::press(){
  if( !digitalRead(_pino) & !_btPress ) { 
    _btPress = true;
    return true;
  } else if( digitalRead(_pino) & _btPress ) {
    _btPress = false;
  }
  return false;
}
// <<<<<<< Retorna true ao soltar >>>>>>>>>>>>
boolean DigitalButton::release(){
  if( !digitalRead(_pino) & !_btPress ) {
    _btPress = true;
  } else if(digitalRead(_pino) & _btPress ){
    _btPress = false;
    return true;
  }
  return false;
 }

#endif