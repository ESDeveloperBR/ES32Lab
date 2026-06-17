/**
 * @brief Simple example using ES_DigitalButton with the ESP32 BOOT button.
 * | Exemplo simples usando ES_DigitalButton com o botão BOOT do ESP32.
 *
 * The ESP32 BOOT button is usually connected to GPIO 0 and is active in LOW.
 * Therefore, the second parameter is false.
 *
 * | O botão BOOT do ESP32 normalmente está conectado à GPIO 0 e é ativo em LOW.
 * Por isso, o segundo parâmetro é false.
 */

#include <Arduino.h>
#include <ES32Lab.h>

ES_DigitalButton button; // Digital button object. | Objeto do botão digital.

void setup() {
    Serial.begin(115200); // Starts serial communication. | Inicia a comunicação serial.
    button.begin(0, false); // GPIO 0, active LOW. | GPIO 0, ativo em LOW.
}

void loop() {
    if (button.press()) {
        Serial.println("Button pressed. | Botao pressionado.");
    }

    if (button.hold()) {
        Serial.println("Button held. | Botao segurado.");
    }

    if (button.release()) {
        Serial.println("Button released. | Botao solto.");
    }

    delay(100); // Reduces repeated hold messages. | Reduz mensagens repetidas do estado segurado.
}
