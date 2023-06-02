/**
 * @file i2C_digitalWriteExpander.ino
 * @author ES Developer
 * @brief This code uses the i2C PCF8574 expander to control the GPIO EX0 and make an LED blink intermittently on the ES32Lab board. 
 * | Este código utiliza o expansor i2C PCF8574 para controlar a GPIO EX0 e fazer um LED piscar intermitentemente na placa ES32Lab.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed. 
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

void setup() {
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
}

void loop() {
  expander.digitalWrite(EX0, HIGH); // Sets pin 0 of the expander to HIGH (turns on the LED) | Define o pino 0 do expansor como HIGH (acende o LED)
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
  
  expander.digitalWrite(EX0, LOW);  // Sets pin 0 of the expander to LOW (turns off the LED) | Define o pino 0 do expansor como LOW (apaga o LED)
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
}
