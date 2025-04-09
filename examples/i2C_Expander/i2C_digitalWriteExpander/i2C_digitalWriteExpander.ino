/**
 * @file i2C_digitalWriteExpander.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to control GPIO 0 (EX0) of the expansion and make an LED blink intermittently.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para controlar a GPIO 0 (EX0) da expansão e fazer um LED piscar intermitentemente.
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * @attention If the I2C address is incorrect, the program will not work. Use the command `expander.scanI2C()` to find the correct address. For more details, refer to the example available at: 
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * | Atenção: Se o endereço I2C estiver incorreto, o programa não funcionará. Use o comando `expander.scanI2C()` para encontrar o endereço correto. Para mais detalhes, consulte o exemplo disponível em:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES_PCF8574 documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação da classe ES_PCF8574: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
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
