/**
 * @file i2C_digitalReadExpander.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to read a digital input on GPIO 0 (EX0) of the expander. The voltage to be used as a logic high level can be 3.3V or 5V.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para fazer uma leitura digital na GPIO 0 (EX0) da expansão. A tensão a ser utilizada como nível lógico alto pode ser de 3.3V ou 5V.
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