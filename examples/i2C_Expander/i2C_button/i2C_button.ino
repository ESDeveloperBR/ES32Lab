/**
 * @file i2C_button.ino
 * @author ES Developer
 * @brief This code utilizes the ES32Lab I2C PCF8574 expander to connect buttons to its GPIOs and read the button states, such as pressed, holding, and released.
 * | Este código utiliza o expansor I2C PCF8574 da ES32Lab para conectar botões às suas GPIOs e ler os estados do botão, como pressionado, segurando e solto.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed. 
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

int GPIO_EX = EX4;

void setup() {
  Serial.begin(115200);
  expander.begin(); // Initializes the i2C PCF8574 expander | Inicializa o expansor i2C PCF8574
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