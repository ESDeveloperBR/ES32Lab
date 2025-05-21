/**
 * @brief Example: Scanning and identifying I2C devices on the bus with ES32Lab
 * | Exemplo: Escaneando e identificando dispositivos I2C no barramento com a ES32Lab
 *
 * This example demonstrates how to scan and identify all I2C devices connected to the bus using the ES32Lab library.
 * The code instantiates an ES_PCF8574 object (the I2C address is not required for the scanI2C() method) and initializes the expander. In the setup, the scanI2C() method is called to search for all I2C devices present on the bus. The addresses of the found devices are printed to the serial monitor. If no devices are found, a message is displayed indicating that no I2C devices were detected.
 * This example is especially useful for discovering the I2C address of new modules, sensors, or expanders connected to your project, helping to avoid address conflicts and ensuring correct configuration in your code.
 * The scan can be performed with any I2C device connected to the bus, not just PCF8574 expanders. Make sure all devices are properly powered and connected to the SDA and SCL lines.
 *
 * | Este exemplo demonstra como escanear e identificar todos os dispositivos I2C conectados ao barramento utilizando a biblioteca ES32Lab.
 * O código instancia um objeto ES_PCF8574 (o endereço I2C não é necessário para o método scanI2C()) e inicializa o expansor. No setup, o método scanI2C() é chamado para buscar todos os dispositivos I2C presentes no barramento. Os endereços dos dispositivos encontrados são impressos no monitor serial. Se nenhum dispositivo for encontrado, uma mensagem é exibida indicando que nenhum dispositivo I2C foi detectado.
 * Este exemplo é especialmente útil para descobrir o endereço I2C de novos módulos, sensores ou expansores conectados ao seu projeto, ajudando a evitar conflitos de endereço e garantindo a configuração correta no seu código.
 * O escaneamento pode ser realizado com qualquer dispositivo I2C conectado ao barramento, não apenas expansores PCF8574. Certifique-se de que todos os dispositivos estejam devidamente alimentados e conectados às linhas SDA e SCL.
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
