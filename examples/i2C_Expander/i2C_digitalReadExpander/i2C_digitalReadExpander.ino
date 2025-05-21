/**
 * @brief Example: Reading a digital input with the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Leitura de entrada digital com o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to read the state of a digital input (such as a button or sensor) connected to a GPIO pin of the PCF8574 I2C expander using the ES32Lab library.
 * The code instantiates the ES_PCF8574 object with the I2C address 0x20 and initializes the expander. In the main loop, it reads the state of the EX0 pin (GPIO 0 of the expander) using the digitalRead() method.
 * The result is printed to the serial monitor: if the pin receives a HIGH logic level, the value '1' will be displayed; if it receives a LOW logic level, the value '0' will be displayed.
 * This allows you to monitor the status of buttons, switches, or other digital sensors connected to the expander, expanding the number of inputs available to your project via I2C.
 * If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como ler o estado de uma entrada digital (como um botão ou sensor) conectada a um pino GPIO do expansor I2C PCF8574 utilizando a biblioteca ES32Lab.
 * O código instancia o objeto ES_PCF8574 com o endereço I2C 0x20 e inicializa o expansor. No loop principal, lê o estado do pino EX0 (GPIO 0 do expansor) usando o método digitalRead().
 * O resultado é impresso no monitor serial: se o pino receber nível lógico alto (HIGH), será exibido o valor '1'; se receber nível lógico baixo (LOW), será exibido o valor '0'.
 * Isso permite monitorar o status de botões, chaves ou outros sensores digitais conectados ao expansor, ampliando a quantidade de entradas disponíveis para seu projeto via I2C.
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
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab
ES_PCF8574 expander(0x20);  // Instantiates the 'expander' object with the default address `0x20`. | Instancia o objeto 'expander' com o endereço padrão `0x20`.

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