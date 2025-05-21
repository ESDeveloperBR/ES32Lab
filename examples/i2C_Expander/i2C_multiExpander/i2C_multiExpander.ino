
/**
 * @brief Example: Using multiple I2C GPIO expanders (PCF8574) with ES32Lab
 * | Exemplo: Utilizando múltiplos expansores de GPIO I2C (PCF8574) com a ES32Lab
 *
 * This example demonstrates how to control several I2C GPIO expanders (PCF8574) simultaneously using the ES32Lab library.
 * Each expander must have a unique I2C address on the bus. The code shows how to instantiate and operate two expanders independently, turning all their pins ON and OFF in sequence.
 * You can connect and control multiple I2C expanders at the same time, as long as each one has a different address.
 * If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * 
 * | Este exemplo demonstra como controlar vários expansores de GPIO I2C (PCF8574) simultaneamente utilizando a biblioteca ES32Lab.
 * Cada expansor deve possuir um endereço I2C único no barramento. O código mostra como instanciar e operar dois expansores de forma independente, ligando e desligando todos os seus pinos em sequência.
 * É possível conectar e controlar diversos expansores I2C ao mesmo tempo, desde que cada um possua um endereço diferente.
 * Caso você não saiba o endereço I2C do seu dispositivo, utilize o exemplo de scanner I2C disponível em:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
 *
 * @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_File/README.md
 * | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_File/README.md
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library ES32Lab | Biblioteca ES32Lab

ES_PCF8574 expander0(0x20); // PCF8574 I2C address for the first expander | Endereço I2C do primeiro expansor
ES_PCF8574 expander1(0x27); // PCF8574 I2C address for the second expander | Endereço I2C do segundo expansor

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate | Inicializa a comunicação serial a 115200 bps
  expander0.begin();    // Initialize the first PCF8574 expander | Inicializa o primeiro expansor PCF8574
  expander1.begin();    // Initialize the second PCF8574 expander | Inicializa o segundo expansor PCF8574

  Serial.println("EN: Example of use with several I2C expanders");
  Serial.println("PT: Exemplo de uso com vários expansores I2C");
}

void loop() {

  Serial.println("EN: Using the FIRST i2C PCF8574 expander");   // Displays the message on the serial monitor | Exibe a mensagem no monitor serial
  Serial.println("PT: Usando o PRIMEIRO expansor i2C PCF8574"); // Displays the message on the serial monitor | Exibe a mensagem no monitor serial
  expander0.digitalWrite(EX0, HIGH); // Set pin 0 of the first expander to HIGH | Define o pino 0 do primeiro expansor como HIGH
  expander0.digitalWrite(EX1, HIGH); // Set pin 1 of the first expander to HIGH | Define o pino 1 do primeiro expansor como HIGH
  expander0.digitalWrite(EX2, HIGH); // Set pin 2 of the first expander to HIGH | Define o pino 2 do primeiro expansor como HIGH
  expander0.digitalWrite(EX3, HIGH); // Set pin 3 of the first expander to HIGH | Define o pino 3 do primeiro expansor como HIGH
  expander0.digitalWrite(EX4, HIGH); // Set pin 4 of the first expander to HIGH | Define o pino 4 do primeiro expansor como HIGH
  expander0.digitalWrite(EX5, HIGH); // Set pin 5 of the first expander to HIGH | Define o pino 5 do primeiro expansor como HIGH
  expander0.digitalWrite(EX6, HIGH); // Set pin 6 of the first expander to HIGH | Define o pino 6 do primeiro expansor como HIGH
  expander0.digitalWrite(EX7, HIGH); // Set pin 7 of the first expander to HIGH | Define o pino 7 do primeiro expansor como HIGH
  delay(1000); // Wait for 1 second | Aguarda 1 segundo
  expander0.digitalWrite(EX0, LOW); // Set pin 0 of the first expander to LOW | Define o pino 0 do primeiro expansor como LOW
  expander0.digitalWrite(EX1, LOW); // Set pin 1 of the first expander to LOW | Define o pino 1 do primeiro expansor como LOW
  expander0.digitalWrite(EX2, LOW); // Set pin 2 of the first expander to LOW | Define o pino 2 do primeiro expansor como LOW
  expander0.digitalWrite(EX3, LOW); // Set pin 3 of the first expander to LOW | Define o pino 3 do primeiro expansor como LOW
  expander0.digitalWrite(EX4, LOW); // Set pin 4 of the first expander to LOW | Define o pino 4 do primeiro expansor como LOW
  expander0.digitalWrite(EX5, LOW); // Set pin 5 of the first expander to LOW | Define o pino 5 do primeiro expansor como LOW
  expander0.digitalWrite(EX6, LOW); // Set pin 6 of the first expander to LOW | Define o pino 6 do primeiro expansor como LOW
  expander0.digitalWrite(EX7, LOW); // Set pin 7 of the first expander to LOW | Define o pino 7 do primeiro expansor como LOW
  delay(1000); // Wait for 1 second | Aguarda 1 segundo

  Serial.println("EN: Using the SECOND i2C PCF8574 expander");  // Displays the message on the serial monitor | Exibe a mensagem no monitor serial
  Serial.println("PT: Usando o SEGUNDO expansor i2C PCF8574");  // Displays the message on the serial monitor | Exibe a mensagem no monitor serial
  expander1.digitalWrite(EX0, HIGH); // Set pin 0 of the first expander to HIGH | Define o pino 0 do primeiro expansor como HIGH
  expander1.digitalWrite(EX1, HIGH); // Set pin 1 of the first expander to HIGH | Define o pino 1 do primeiro expansor como HIGH
  expander1.digitalWrite(EX2, HIGH); // Set pin 2 of the first expander to HIGH | Define o pino 2 do primeiro expansor como HIGH
  expander1.digitalWrite(EX3, HIGH); // Set pin 3 of the first expander to HIGH | Define o pino 3 do primeiro expansor como HIGH
  expander1.digitalWrite(EX4, HIGH); // Set pin 4 of the first expander to HIGH | Define o pino 4 do primeiro expansor como HIGH
  expander1.digitalWrite(EX5, HIGH); // Set pin 5 of the first expander to HIGH | Define o pino 5 do primeiro expansor como HIGH
  expander1.digitalWrite(EX6, HIGH); // Set pin 6 of the first expander to HIGH | Define o pino 6 do primeiro expansor como HIGH
  expander1.digitalWrite(EX7, HIGH); // Set pin 7 of the first expander to HIGH | Define o pino 7 do primeiro expansor como HIGH
  delay(1000); // Wait for 1 second | Aguarda 1 segundo
  expander1.digitalWrite(EX0, LOW); // Set pin 0 of the first expander to LOW | Define o pino 0 do primeiro expansor como LOW
  expander1.digitalWrite(EX1, LOW); // Set pin 1 of the first expander to LOW | Define o pino 1 do primeiro expansor como LOW
  expander1.digitalWrite(EX2, LOW); // Set pin 2 of the first expander to LOW | Define o pino 2 do primeiro expansor como LOW
  expander1.digitalWrite(EX3, LOW); // Set pin 3 of the first expander to LOW | Define o pino 3 do primeiro expansor como LOW
  expander1.digitalWrite(EX4, LOW); // Set pin 4 of the first expander to LOW | Define o pino 4 do primeiro expansor como LOW
  expander1.digitalWrite(EX5, LOW); // Set pin 5 of the first expander to LOW | Define o pino 5 do primeiro expansor como LOW
  expander1.digitalWrite(EX6, LOW); // Set pin 6 of the first expander to LOW | Define o pino 6 do primeiro expansor como LOW
  expander1.digitalWrite(EX7, LOW); // Set pin 7 of the first expander to LOW | Define o pino 7 do primeiro expansor como LOW
  delay(1000); // Wait for 1 second | Aguarda 1 segundo
}