/**
 * @file ES_Buzzer_jingleBells.ino
 * @brief This example plays the Jingle Bells theme using the ES_Buzzer class on the ES32Lab board.
 * | Este exemplo reproduz o tema de Jingle Bells usando a classe ES_Buzzer na placa ES32Lab.
 * @warning Ensure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) está instalada.
 */

#include <Arduino.h>
#include <ES32Lab.h>

// Instance of the ES_Buzzer class using the P_BUZZER pin. | Instância da classe ES_Buzzer utilizando o pino P_BUZZER.
ES_Buzzer buzzer(P_BUZZER);

void setup() {
  buzzer.begin(); // Initializes the buzzer. | Inicializa o buzzer.
}

void loop() {
  buzzer.sound(NOTE_G3, 83);  // Play NOTE_G3 for 83ms. | Reproduz NOTE_G3 por 83ms.
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_G3, 333);  // Play NOTE_G3 for 333ms. | Reproduz NOTE_G3 por 333ms.

  buzzer.sound(NOTE_G3, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_A4, 333);

  buzzer.sound(NOTE_A4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_G4, 125);  // Play NOTE_G4 for 125ms. | Reproduz NOTE_G4 por 125ms.
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_A5, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_E4, 333);

  buzzer.sound(NOTE_G3, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_G3, 333);

  buzzer.sound(NOTE_G3, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_A4, 333);

  buzzer.sound(NOTE_A4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_G4, 125);
  buzzer.sound(NOTE_G4, 42);  // Play NOTE_G4 for 42ms. | Reproduz NOTE_G4 por 42ms.

  buzzer.sound(NOTE_A5, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 333);

  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 125);  // Play NOTE_E4 for 125ms. | Reproduz NOTE_E4 por 125ms.
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 125);

  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_E4, 333);

  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 42);  // Play NOTE_E4 for 42ms. | Reproduz NOTE_E4 por 42ms.
  buzzer.sound(NOTE_E4, 42);

  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_D4, 125);
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 125);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 125);

  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_C4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_E4, 333);

  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 83);
  buzzer.sound(NOTE_E4, 42);
  buzzer.sound(NOTE_E4, 42);

  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_G4, 83);
  buzzer.sound(NOTE_F4, 83);
  buzzer.sound(NOTE_D4, 83);
  buzzer.sound(NOTE_C4, 333);

  buzzer.end(5000); // Pause for 5s before repeating. | Pausa de 5s antes de repetir.
}
