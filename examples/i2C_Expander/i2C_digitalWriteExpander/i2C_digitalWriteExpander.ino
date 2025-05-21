/**
 * @brief Example: Writing to a digital output with the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Escrita em saída digital com o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to control a digital output (such as an LED or relay) connected to a GPIO pin of the PCF8574 I2C expander using the ES32Lab library.
 * The code instantiates the ES_PCF8574 object with the I2C address 0x20 and initializes the expander. In the main loop, it alternately sets the EX0 pin (GPIO 0 of the expander) to HIGH and LOW using the digitalWrite() method, turning the connected device on and off every second.
 * This allows you to expand the number of digital outputs available in your project via I2C, making it possible to control LEDs, relays, or other actuators with just two wires (SDA and SCL).
 * If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como controlar uma saída digital (como um LED ou relé) conectada a um pino GPIO do expansor I2C PCF8574 utilizando a biblioteca ES32Lab.
 * O código instancia o objeto ES_PCF8574 com o endereço I2C 0x20 e inicializa o expansor. No loop principal, alterna o estado do pino EX0 (GPIO 0 do expansor) entre HIGH e LOW usando o método digitalWrite(), ligando e desligando o dispositivo conectado a cada segundo.
 * Isso permite expandir a quantidade de saídas digitais disponíveis no seu projeto via I2C, possibilitando o controle de LEDs, relés ou outros atuadores utilizando apenas dois fios (SDA e SCL).
 * Caso você não saiba o endereço I2C do seu dispositivo, utilize o exemplo de scanner I2C disponível em:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
 *
 * @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x20);  // Instantiates the 'expander' object with the default address `0x20`. | Instancia o objeto 'expander' com o endereço padrão `0x20`.

void setup() {
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
}

void loop() {
  expander.digitalWrite(EX0, HIGH); // Sets pin 0 of the expander to HIGH (turns on the LED) | Define o pino 0 do expansor como HIGH (acende o LED)
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
  
  expander.digitalWrite(EX0, LOW);  // Sets pin 0 of the expander to LOW (turns off the LED) | Define o pino 0 do expansor como LOW (apaga o LED)
  delay(1000); // Waits for 1 second | Aguarda 1 segundo
}
