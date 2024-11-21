/**
 * @file DigitalButton.ino
 * @brief This example demonstrates the use of the DigitalButton class to monitor the three states
 * of a button connected to GPIO 0 on the ESP32: pressed, held, and released.
 * | Este exemplo demonstra o uso da classe DigitalButton para monitorar os três estados
 * de um botão conectado à GPIO 0 no ESP32: pressionado, segurando e solto.
 * @note The GPIO 0 is used as an example and has a special function for bootloader mode on ESP32 boards.
 * Use it with caution in production environments.
 * | A GPIO 0 é usada como exemplo e possui uma função especial para o modo bootloader nas placas ESP32.
 * Use-a com cautela em ambientes de produção.
 * @warning Ensure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) está instalada.
 */

#include <Arduino.h>
#include <ES32Lab.h>

// Creates the object for the button on GPIO 0. | Cria o objeto para o botão na GPIO 0.
DigitalButton button(0, true);

void setup() {
  Serial.begin(115200); // Initializes serial communication. | Inicializa a comunicação serial.
  button.begin();       // Initializes button monitoring. | Inicializa o monitoramento do botão.
}

void loop() {
  // Checks if the button was pressed. | Verifica se o botão foi pressionado.
  if (button.press()) {
    Serial.println("Button was pressed!"); // Message when the button is pressed. | Mensagem quando o botão é pressionado.
  }

  // Checks if the button is being held. | Verifica se o botão está sendo segurado.
  if (button.hold()) {
    Serial.println("Button is being held!"); // Message while the button is held. | Mensagem enquanto o botão está sendo segurado.
  }

  // Checks if the button was released. | Verifica se o botão foi solto.
  if (button.release()) {
    Serial.println("Button was released!"); // Message when the button is released. | Mensagem quando o botão é solto.
  }

  delay(100); // Prevents excessive readings. | Evita leituras excessivas.
}