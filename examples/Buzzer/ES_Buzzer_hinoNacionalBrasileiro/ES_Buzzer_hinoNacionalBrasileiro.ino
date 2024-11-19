/**
 * @file ES_Buzzer_hinoNacionalBrasileiro.ino
 * @brief This example plays the Brazilian National Anthem on the ESP32Lab buzzer.
 * | Este exemplo reproduz o Hino Nacional Brasileiro no buzzer da ES32Lab.
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
  // Play the Brazilian National Anthem melody. | Reproduz a melodia do Hino Nacional Brasileiro.

  buzzer.pitch(150);

  buzzer.sound(NOTE_C4, 375);  // Play note C4 for 375ms. | Toca a nota C4 por 375ms.
  buzzer.sound(NOTE_F4, 250);  // Play note F4 for 250ms. | Toca a nota F4 por 250ms.
  buzzer.sound(NOTE_E4, 94);   // Play note E4 for 94ms. | Toca a nota E4 por 94ms.
  buzzer.sound(NOTE_F4, 250);  // Play note F4 for 250ms. | Toca a nota F4 por 250ms.
  buzzer.sound(NOTE_G4, 94);   // Play note G4 for 94ms. | Toca a nota G4 por 94ms.
  buzzer.sound(NOTE_A4, 250);  // Play note A4 for 250ms. | Toca a nota A4 por 250ms.
  buzzer.sound(NOTE_G4, 94);   // Play note G4 for 94ms. | Toca a nota G4 por 94ms.
  buzzer.sound(NOTE_A4, 250);  // Play note A4 for 250ms. | Toca a nota A4 por 250ms.
  buzzer.sound(NOTE_AS4, 94);  // Play note AS4 for 94ms. | Toca a nota AS4 por 94ms.
  buzzer.sound(NOTE_B4, 250);  // Play note B4 for 250ms. | Toca a nota B4 por 250ms.
  buzzer.sound(NOTE_C5, 750);  // Play note C5 for 750ms. | Toca a nota C5 por 750ms.

  buzzer.sound(NOTE_F4, 375);  // Play note F4 for 375ms. | Toca a nota F4 por 375ms.
  buzzer.sound(NOTE_C4, 250);  // Play note C4 for 250ms. | Toca a nota C4 por 250ms.
  buzzer.sound(NOTE_F4, 94);   // Play note F4 for 94ms. | Toca a nota F4 por 94ms.
  buzzer.sound(NOTE_E4, 250);  // Play note E4 for 250ms. | Toca a nota E4 por 250ms.
  buzzer.sound(NOTE_G4, 250);  // Play note G4 for 250ms. | Toca a nota G4 por 250ms.
  buzzer.sound(NOTE_F4, 250);  // Play note F4 for 250ms. | Toca a nota F4 por 250ms.
  buzzer.sound(NOTE_A4, 250);  // Play note A4 for 250ms. | Toca a nota A4 por 250ms.
  buzzer.sound(NOTE_G4, 250);  // Play note G4 for 250ms. | Toca a nota G4 por 250ms.
  buzzer.sound(NOTE_AS4, 250); // Play note AS4 for 250ms. | Toca a nota AS4 por 250ms.
  buzzer.sound(NOTE_A4, 94);   // Play note A4 for 94ms. | Toca a nota A4 por 94ms.
  buzzer.sound(NOTE_FS4, 250); // Play note FS4 for 250ms. | Toca a nota FS4 por 250ms.

  buzzer.sound(NOTE_G4, 375);  // Play note G4 for 375ms. | Toca a nota G4 por 375ms.
  buzzer.sound(0, 500);        // Pause for 500ms. | Pausa por 500ms.
  buzzer.sound(NOTE_C4, 250);  // Play note C4 for 250ms. | Toca a nota C4 por 250ms.
  buzzer.sound(NOTE_G4, 250);  // Play note G4 for 250ms. | Toca a nota G4 por 250ms.
  buzzer.sound(NOTE_FS4, 94);  // Play note FS4 for 94ms. | Toca a nota FS4 por 94ms.
  buzzer.sound(NOTE_G4, 250);  // Play note G4 for 250ms. | Toca a nota G4 por 250ms.
  buzzer.sound(NOTE_A4, 250);  // Play note A4 for 250ms. | Toca a nota A4 por 250ms.
  buzzer.sound(NOTE_AS4, 250); // Play note AS4 for 250ms. | Toca a nota AS4 por 250ms.

  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}
