/**
 * @file ES_Buzzer_HappyBirthday.ino
 * @brief This example plays "Happy Birthday" on the ESP32Lab buzzer, 80% faster.
 * | Este exemplo reproduz "Parabéns pra Você" no buzzer da ES32Lab, 80% mais rápido.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER); // Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin. | Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'.

// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  buzzer.begin(); // Initialize the buzzer instance. | Inicializa a instância do buzzer.
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  // Play "Happy Birthday" melody 80% faster. | Reproduz a melodia de "Parabéns pra Você" 80% mais rápido.

  buzzer.sound(NOTE_C4, 139);  // Play note C4 for 139ms. | Toca a nota C4 por 139ms.
  buzzer.sound(NOTE_C4, 69);   // Play note C4 for 69ms. | Toca a nota C4 por 69ms.
  buzzer.sound(NOTE_D4, 208);  // Play note D4 for 208ms. | Toca a nota D4 por 208ms.
  buzzer.sound(NOTE_C4, 208);  // Play note C4 for 208ms. | Toca a nota C4 por 208ms.
  buzzer.sound(NOTE_F4, 208);  // Play note F4 for 208ms. | Toca a nota F4 por 208ms.
  buzzer.sound(NOTE_E4, 417);  // Play note E4 for 417ms. | Toca a nota E4 por 417ms.

  buzzer.sound(NOTE_C4, 139);  // Play note C4 for 139ms. | Toca a nota C4 por 139ms.
  buzzer.sound(NOTE_C4, 69);   // Play note C4 for 69ms. | Toca a nota C4 por 69ms.
  buzzer.sound(NOTE_D4, 208);  // Play note D4 for 208ms. | Toca a nota D4 por 208ms.
  buzzer.sound(NOTE_C4, 208);  // Play note C4 for 208ms. | Toca a nota C4 por 208ms.
  buzzer.sound(NOTE_G4, 208);  // Play note G4 for 208ms. | Toca a nota G4 por 208ms.
  buzzer.sound(NOTE_F4, 417);  // Play note F4 for 417ms. | Toca a nota F4 por 417ms.

  buzzer.sound(NOTE_C4, 139);  // Play note C4 for 139ms. | Toca a nota C4 por 139ms.
  buzzer.sound(NOTE_C5, 208);  // Play note C5 for 208ms. | Toca a nota C5 por 208ms.
  buzzer.sound(NOTE_A4, 208);  // Play note A4 for 208ms. | Toca a nota A4 por 208ms.
  buzzer.sound(NOTE_F4, 208);  // Play note F4 for 208ms. | Toca a nota F4 por 208ms.
  buzzer.sound(NOTE_E4, 208);  // Play note E4 for 208ms. | Toca a nota E4 por 208ms.
  buzzer.sound(NOTE_D4, 417);  // Play note D4 for 417ms. | Toca a nota D4 por 417ms.

  buzzer.sound(NOTE_AS4, 139); // Play note AS4 for 139ms. | Toca a nota AS4 por 139ms.
  buzzer.sound(NOTE_AS4, 69);  // Play note AS4 for 69ms. | Toca a nota AS4 por 69ms.
  buzzer.sound(NOTE_A4, 208);  // Play note A4 for 208ms. | Toca a nota A4 por 208ms.
  buzzer.sound(NOTE_F4, 208);  // Play note F4 for 208ms. | Toca a nota F4 por 208ms.
  buzzer.sound(NOTE_G4, 208);  // Play note G4 for 208ms. | Toca a nota G4 por 208ms.
  buzzer.sound(NOTE_F4, 417);  // Play note F4 for 417ms. | Toca a nota F4 por 417ms.

  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}
