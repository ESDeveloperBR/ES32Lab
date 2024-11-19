/**
 * @file ES_Buzzer_gameOfThrones.ino
 * @brief This example plays the Game of Thrones theme using the ES_Buzzer class on the ES32Lab board.
 * | Este exemplo reproduz o tema de Game of Thrones usando a classe ES_Buzzer na placa ES32Lab.
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
  // Game of Thrones Theme - Part 1
  buzzer.sound(NOTE_G4, 120);  // Play NOTE_G4 for 120ms. | Reproduz NOTE_G4 por 120ms.
  buzzer.sound(NOTE_C4, 120);
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_G4, 120);
  buzzer.sound(NOTE_C4, 120);
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_G4, 120);
  buzzer.sound(NOTE_C4, 120);
  buzzer.sound(NOTE_E4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_G4, 120);
  buzzer.sound(NOTE_C4, 120);
  buzzer.sound(NOTE_E4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_G4, 480);  // Play NOTE_G4 for 480ms. | Reproduz NOTE_G4 por 480ms.
  buzzer.sound(NOTE_C4, 480);

  // Game of Thrones Theme - Part 2
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_G4, 360);
  buzzer.sound(NOTE_C4, 360);
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_F4, 60);
  buzzer.sound(NOTE_D4, 1440); // Play NOTE_D4 for 1440ms. | Reproduz NOTE_D4 por 1440ms.
  buzzer.sound(NOTE_F4, 480);
  buzzer.sound(NOTE_AS3, 480);
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_D4, 60);
  buzzer.sound(NOTE_F4, 360);
  buzzer.sound(NOTE_AS3, 480);
  buzzer.sound(NOTE_DS4, 60);
  buzzer.sound(NOTE_D4, 60);
  buzzer.sound(NOTE_C4, 1440); // Play NOTE_C4 for 1440ms. | Reproduz NOTE_C4 por 1440ms.

  // Game of Thrones Theme - Final Part
  buzzer.sound(NOTE_C5, 720);  // Play NOTE_C5 for 720ms. | Reproduz NOTE_C5 por 720ms.
  buzzer.sound(NOTE_AS4, 720);
  buzzer.sound(NOTE_C4, 720);
  buzzer.sound(NOTE_G4, 720);
  buzzer.sound(NOTE_DS4, 720);
  buzzer.sound(NOTE_G4, 480);
  buzzer.sound(NOTE_C5, 240);
  buzzer.sound(NOTE_G4, 240);
  buzzer.sound(NOTE_GS4, 120);
  buzzer.sound(NOTE_AS4, 120);
  buzzer.sound(NOTE_C5, 240);
  buzzer.sound(NOTE_G4, 240);
  buzzer.sound(NOTE_GS4, 120);
  buzzer.sound(NOTE_AS4, 120);

  buzzer.end(1500); // Pause for 1.5 seconds before repeating. | Pausa de 1.5 segundos antes de repetir.
}