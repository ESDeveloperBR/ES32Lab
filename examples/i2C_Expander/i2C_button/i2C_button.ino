 /**
 * @file i2C_button.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to connect buttons to its GPIOs and read their states, such as pressed, holding, and released.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para conectar botões às suas GPIOs e ler seus estados, como pressionado, segurando e solto.
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * @attention If the I2C address is incorrect, the program will not work. Use the command `expander.scanI2C()` to find the correct address. For more details, refer to the example available at: 
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * | Atenção: Se o endereço I2C estiver incorreto, o programa não funcionará. Use o comando `expander.scanI2C()` para encontrar o endereço correto. Para mais detalhes, consulte o exemplo disponível 
 * em: https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES_PCF8574 documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação da classe ES_PCF8574: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
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
    Serial.println("Button 0 Press");  // Display on the serial monitor. | Exibe no monitor serial.
  }

  if(expander.btHold(EX0)){  // When the button connected to the expansion GPIO is pressed, execute: | Quando o botão conectado à GPIO de expansão estiver pressionado, execute:
    Serial.println("Button 0 Hold");  // Display on the serial monitor. | Exibe no monitor serial.
    delay(500);  // Wait for 500 milliseconds. | Aguarda 500 milissegundos.
  }

  if(expander.btRelease(EX0)){  // When the button connected to the expansion GPIO is released, execute: | Quando o botão conectado à GPIO de expansão for solto, execute:
    Serial.println("Button 0 released");  // Display on the serial monitor. | Exibe no monitor serial.
  }
  
}