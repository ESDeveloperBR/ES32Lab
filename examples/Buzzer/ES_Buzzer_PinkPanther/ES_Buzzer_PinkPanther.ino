/**
 * @file ES_Buzzer_PinkPanther.ino
 * @brief This example plays the theme of the Pink Panther on the ESP32Lab buzzer.
 * | Este exemplo reproduz o tema da Pantera Cor-de-Rosa no buzzer da ES32Lab.
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
  // Play the Pink Panther melody on the buzzer. | Reproduz a melodia da Pantera Cor-de-Rosa no buzzer.

  buzzer.sound(0, 240); // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(0, 120); // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_DS4, 120); // Play note DS4 for 120ms. | Toca a nota DS4 por 120ms.
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_FS4, 120); // Play note FS4 for 120ms. | Toca a nota FS4 por 120ms.
  buzzer.sound(NOTE_G4, 240);  // Play note G4 for 240ms. | Toca a nota G4 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_DS4, 120); // Play note DS4 for 120ms. | Toca a nota DS4 por 120ms.

  buzzer.sound(NOTE_E4, 120);  // Play note E4 for 120ms. | Toca a nota E4 por 120ms.
  buzzer.sound(NOTE_FS4, 120); // Play note FS4 for 120ms. | Toca a nota FS4 por 120ms.
  buzzer.sound(NOTE_G4, 120);  // Play note G4 for 120ms. | Toca a nota G4 por 120ms.
  buzzer.sound(NOTE_C5, 120);  // Play note C5 for 120ms. | Toca a nota C5 por 120ms.
  buzzer.sound(NOTE_B4, 120);  // Play note B4 for 120ms. | Toca a nota B4 por 120ms.
  buzzer.sound(NOTE_E4, 120);  // Play note E4 for 120ms. | Toca a nota E4 por 120ms.
  buzzer.sound(NOTE_G4, 120);  // Play note G4 for 120ms. | Toca a nota G4 por 120ms.
  buzzer.sound(NOTE_B4, 120);  // Play note B4 for 120ms. | Toca a nota B4 por 120ms.
  buzzer.sound(NOTE_AS4, 240); // Play note AS4 for 240ms. | Toca a nota AS4 por 240ms.
  buzzer.sound(NOTE_A4, 80);   // Play note A4 for 80ms. | Toca a nota A4 por 80ms.

  buzzer.sound(NOTE_G4, 80);   // Play note G4 for 80ms. | Toca a nota G4 por 80ms.
  buzzer.sound(NOTE_E4, 80);   // Play note E4 for 80ms. | Toca a nota E4 por 80ms.
  buzzer.sound(NOTE_D4, 80);   // Play note D4 for 80ms. | Toca a nota D4 por 80ms.
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_DS4, 120); // Play note DS4 for 120ms. | Toca a nota DS4 por 120ms.
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_FS4, 120); // Play note FS4 for 120ms. | Toca a nota FS4 por 120ms.
  buzzer.sound(NOTE_G4, 240);  // Play note G4 for 240ms. | Toca a nota G4 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_DS4, 120); // Play note DS4 for 120ms. | Toca a nota DS4 por 120ms.

  buzzer.sound(NOTE_E4, 120);  // Play note E4 for 120ms. | Toca a nota E4 por 120ms.
  buzzer.sound(NOTE_FS4, 120); // Play note FS4 for 120ms. | Toca a nota FS4 por 120ms.
  buzzer.sound(NOTE_G4, 120);  // Play note G4 for 120ms. | Toca a nota G4 por 120ms.
  buzzer.sound(NOTE_C5, 120);  // Play note C5 for 120ms. | Toca a nota C5 por 120ms.
  buzzer.sound(NOTE_B4, 120);  // Play note B4 for 120ms. | Toca a nota B4 por 120ms.
  buzzer.sound(NOTE_E5, 240);  // Play note E5 for 240ms. | Toca a nota E5 por 240ms.
  buzzer.sound(NOTE_DS5, 480); // Play note DS5 for 480ms. | Toca a nota DS5 por 480ms.
  buzzer.sound(NOTE_D5, 240);  // Play note D5 for 240ms. | Toca a nota D5 por 240ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(0, 120);        // Pause for 120ms. | Pausa por 120ms.
  buzzer.sound(NOTE_DS4, 120); // Play note DS4 for 120ms. | Toca a nota DS4 por 120ms.

  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}
