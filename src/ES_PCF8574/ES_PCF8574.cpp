#include <Arduino.h>
#include "ES_PCF8574.h"
/**
 * Constructor of the ES_PCF8574 class.
 * @param address Address of the PCF8574 in the I2C communication.
 * Initializes an instance of the ES_PCF8574 class with the provided PCF8574 address.
 * --- (Português BR) ---
 * Construtor da classe ES_PCF8574
 * @param address Endereço do PCF8574 na comunicação I2C
 * Inicializa uma instância da classe ES_PCF8574 com o endereço do PCF8574 fornecido.
 */
ES_PCF8574::ES_PCF8574(uint8_t address) {
    _address = address;
    _value = 0;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Beguin >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Initializes the I2C communication and configures the PCF8574.
 * Returns true if the communication was successfully initiated, otherwise returns false.
 * --- (Português BR) ---
 * Inicializa a comunicação I2C e configura o PCF8574.
 * Retorna true se a comunicação foi iniciada com sucesso, caso contrário, retorna false.
 */
boolean ES_PCF8574::begin(){
    boolean _return = Wire.begin();
    if(_return){
        Wire.beginTransmission(_address);
        Wire.write(_value);
        Wire.endTransmission();
    }
    return _return;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< digitalWrite >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< digitalRead >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * Reads the logical signal present on a specific GPIO of PCF8574.
 * The read value is returned as an 8-bit integer (0 for LOW, 1 for HIGH).
 * | 
 * Realiza a leitura do sinal lógico presente em uma GPIO específica do PCF8574.
 * O valor lido é retornado como um inteiro de 8 bits (0 para LOW, 1 para HIGH).
 * 
 * @param pin Number of the GPIO to be read. | Número da GPIO que será lida.
 */
uint8_t ES_PCF8574::digitalRead(uint8_t pin) {
  Wire.requestFrom(_address, (uint8_t)1);
  uint8_t data = Wire.read();
  return (data >> pin) & 1;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< btHold >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * The 'true' condition is returned while the expansion GPIO is being used as a button input and remains pressed, meaning it stays at a logical high level.
 * |
 * A condição 'true' é retornada enquanto a GPIO da expansão estiver sendo utilizada como entrada de botão e permanecer pressionada, ou seja, mantendo-se em nível lógico alto.
 * 
 * @param pin Number of the GPIO to be read. | Número da GPIO que será lida.
*/
boolean ES_PCF8574::btHold(uint8_t pin){
  if( digitalRead(pin) ) { 
    return true;
  }
  return false;
}

// <<<<<<<<<<<<<<<<<<<<<< btPress >>>>>>>>>>>>>>>>>>>
/**
 * The 'true' condition is returned at the exact moment when the expansion GPIO is used as a button input and there is a transition from a low to high logical level, that is, when the button is pressed.
 * |
 * A condição 'true' é retornada no exato momento em que a GPIO da expansão é utilizada como entrada de botão e ocorre a transição do nível lógico de baixo para alto, ou seja, quando o botão é pressionado.
 * @param pin Number of the GPIO to be read. | Número da GPIO que será lida.
*/
boolean ES_PCF8574::btPress(uint8_t pin){
  if( !btHold(pin) & !_btPress[pin] ) { 
    _btPress[pin] = true;
  } else if( btHold(pin) & _btPress[pin] ) {
    _btPress[pin] = false;
    return true;
  }
  return false;
}

// <<<<<<<<<<<<<<<<< btRelease >>>>>>>>>>>>>>>>>>>>>>>>
/**
 * The 'true' condition is returned at the exact moment when the expansion GPIO is used as a button input and there is a transition from a high to low logical level, that is, when the button is release.
 * |
 * A condição 'true' é retornada no exato momento em que a GPIO da expansão é utilizada como entrada de botão e ocorre a transição do nível lógico de alto para baixo, ou seja, quando o botão é solto.
 * @param pin Number of the GPIO to be read. | Número da GPIO que será lida.
*/
boolean ES_PCF8574::btRelease(uint8_t pin){
  if( !btHold(pin) & !_btRelease[pin] ) {
    _btRelease[pin] = true;
    return true;
  } else if(btHold(pin) & _btRelease[pin] ){
    _btRelease[pin] = false;
  }
  return false;
}