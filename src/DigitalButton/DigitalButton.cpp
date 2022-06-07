#include "DigitalButton.h"

// <<<<<<<<<<<<<<<<<<< Construtor >>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
Creates the object to be used as a digital button and assigns the GPIO to be used.
- pin: GPIO of the button;
--- (Português BR) ---
Cria o objeto a ser usado como botão digital e atribui a GPIO a ser utilizada.
- pin: GPIO do botão;
*/
DigitalButton::DigitalButton(int pin){
  _pin = pin;
}

// <<<<<<<<<<<<<<<< Begin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
Begin the instantiated button.
--- (Português BR) ---
Inicializar o botão instanciado.
*/
void DigitalButton::begin(){
  begin(_pin);
}

/*
Begin the instantiated button.
- pin: Address of the GPIO that is connected to the button or sensor.
--- (Português BR) ---
Inicializar o botão instanciado.
- pin: Endereço da GPIO que está conectado ao botão ou sensor.
*/
void DigitalButton::begin(int pin){
  _pin = pin;
  if(_pin >= 0){
    pinMode(_pin, INPUT_PULLUP);
  }
}

// <<<<<<<<<<<<<<<< Inicializa o pino do botão >>>>>>>>>>>>>>>>>>>>>>>>>>
/*
Initialize button pin.
- pin: Address of the GPIO that is connected to the button or sensor.
--- (Português BR) ---
Inicializa o pino do botão.
- pin: Endereço da GPIO que está conectado ao botão ou sensor.
*/
void DigitalButton::setPino(int pin){
  begin(pin);
}

// <<<<<<< Retorna "true" enquanto o botão estiver pressionado >>>>>>>>>>>>>>>>
/*
Returns "true" while the button is hold.
--- (Português BR) ---
Retorna "true" enquanto o botão estiver pressionado.
*/
boolean DigitalButton::hold(){
  if( !digitalRead(_pin) ) { 
    return true;
  }
  return false;
}

// <<<<<<<<<<<<<<<<<<<<<< Retorna "true" quando o botão for pressionado >>>>>>>>>>>>>>>>>>>
/*
Returns "true" when the button is pressed.
--- (Português BR) ---
Retorna "true" se o botão for pressionado.
*/
boolean DigitalButton::press(){
  if( !hold() & !_btPress ) { 
    _btPress = true;
  } else if( hold() & _btPress ) {
    _btPress = false;
    return true;
  }
  return false;
}

// <<<<<<< Retorna "true" quando o botão for solto >>>>>>>>>>>>
/*
Returns "true" when the button is released.
--- (Português BR) ---
Retorna "true" quando o botão for solto.
*/
boolean DigitalButton::release(){
  if( !hold() & !_btRelease ) {
    _btRelease = true;
    return true;
  } else if(hold() & _btRelease ){
    _btRelease = false;
  }
  return false;
}
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
