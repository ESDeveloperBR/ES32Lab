/**
 * @brief Example: Using a button with the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Utilizando um botão com o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to use a button connected to a GPIO of the PCF8574 I2C expander with the ES32Lab library.
 * It shows how to detect when the button is pressed, held, or released using the methods btPress(), btHold(), and btRelease().
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como utilizar um botão conectado a uma GPIO do expansor I2C PCF8574 com a biblioteca ES32Lab.
 * Mostra como detectar quando o botão é pressionado, mantido pressionado ou solto utilizando os métodos btPress(), btHold() e btRelease().
 * O expansor deve ser configurado com o endereço I2C correto. Caso você não saiba o endereço I2C do seu dispositivo, utilize o exemplo de scanner I2C disponível em:
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
  Serial.begin(115200);
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
  Serial.println(expander.scanI2C());  // Scan the I2C bus for connected devices and print the results to the Serial Monitor. | Faz a varredura do barramento I2C em busca de dispositivos conectados e imprime os resultados no Serial Monitor.
}

void loop() {
  // ---- Button 0 ----
  if(expander.btPress(EX0)){  // When the button connected to the expansion GPIO is pressed, execute: | Quando o botão conectado à GPIO de expansão for pressionado, execute:
    Serial.println("EN: Button 0 Press");  // Display on the serial monitor. | Exibe no monitor serial.
    Serial.println("PT: Botão 0 Pressionado");  // Display on the serial monitor. | Exibe no monitor serial.
  }

  if(expander.btHold(EX0)){  // When the button connected to the expansion GPIO is pressed, execute: | Quando o botão conectado à GPIO de expansão estiver pressionado, execute:
    Serial.println("EN: Button 0 Hold");  // Display on the serial monitor. | Exibe no monitor serial.
    Serial.println("PT: Botão 0 Mantido");  // Display on the serial monitor. | Exibe no monitor serial.
    delay(500);  // Wait for 500 milliseconds. | Aguarda 500 milissegundos.
  }

  if(expander.btRelease(EX0)){  // When the button connected to the expansion GPIO is released, execute: | Quando o botão conectado à GPIO de expansão for solto, execute:
    Serial.println("EN: Button 0 released");  // Display on the serial monitor. | Exibe no monitor serial.
    Serial.println("PT: Botão 0 Solto");  // Display on the serial monitor. | Exibe no monitor serial.
  }
  
}