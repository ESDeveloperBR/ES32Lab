/**
 * @file i2C_scanDevices.ino
 * @brief This code demonstrates how to use the `scanI2C()` method of the ES32Lab library to scan and display all I2C device addresses connected to the bus.
 * | Este código demonstra como usar o método `scanI2C()` da biblioteca ES32Lab para escanear e exibir todos os endereços de dispositivos I2C conectados ao barramento.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab

ES_PCF8574 expander;  // The I2C address is not mandatory for the scanI2C() method when instantiating the object | O endereço I2C não é obrigatório para o método scanI2C() no momento de instanciar o objeto

void setup() {
  Serial.begin(115200);  // Initializes serial communication | Inicializa a comunicação serial
  expander.begin();      // Initializes the PCF8574 expander | Inicializa o expansor PCF8574

  // Scan for I2C devices and print the results | Escaneia dispositivos I2C e imprime os resultados
  String i2cDevices = expander.scanI2C();
  if (i2cDevices != "") {
    Serial.println("Dispositivos I2C encontrados:");  // Displays a list of found devices | Exibe uma lista de dispositivos encontrados
    Serial.println(i2cDevices);
  } else {
    Serial.println("Nenhum dispositivo I2C encontrado.");  // Displays a message if no devices are found | Exibe uma mensagem se nenhum dispositivo for encontrado
  }
}

void loop() {
  // No operations in the loop for this example | Sem operações no loop para este exemplo
}
