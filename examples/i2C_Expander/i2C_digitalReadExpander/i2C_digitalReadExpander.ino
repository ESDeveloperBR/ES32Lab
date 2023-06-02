/**
 * @file i2C_digitalReadExpander.ino
 * @brief This code uses the i2C PCF8574 expander on the ES32Lab board to read a digital input on GPIO 0. The voltage to be used as logic high level can be 3.3V or 5V.
 * | Este código utiliza o expansor i2C PCF8574 da placa ES32Lab para fazer uma leitura digital na GPIO 0. A tensão a ser utilizada como sinal lógico alto pode ser de 3.3V ou 5V.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) installed and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) instalada e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab
ES_PCF8574 expander(0x38); // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  Serial.begin(115200); // Initializes the serial communication | Inicializa a comunicação serial
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  boolean readExpander; // Variable to store the GPIO read value from the expander | Variável para armazenar o valor lido da GPIO do expansor
  readExpander = expander.digitalRead(EX0); // Reads the GPIO 0 of the ES32Lab expander | Lê a GPIO 0 do expansor ES32Lab
  Serial.println(readExpander); // If the GPIO EX0 of the expander receives a logic high signal, the number 1 will be displayed on the serial terminal | Se a GPIO EX0 do expansor receber um sinal lógico alto, o número 1 será exibido no terminal serial
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
}