/**
 * @file ES_Buzzer_startWarImperialMarch.ino
 * @brief This example plays the Imperial March theme using the ES_Buzzer class on the ES32Lab board.
 * | Este exemplo reproduz o tema da Marcha Imperial usando a classe ES_Buzzer na placa ES32Lab.
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
  // Imperial March Theme - Part 1
  buzzer.sound(NOTE_A3, 365);  // Play NOTE_A3 for 365ms. | Reproduz NOTE_A3 por 365ms.
  buzzer.sound(NOTE_A3, 365);
  buzzer.sound(NOTE_A3, 365);
  buzzer.sound(NOTE_F3, 275);  // Play NOTE_F3 for 275ms. | Reproduz NOTE_F3 por 275ms.
  buzzer.sound(NOTE_C4, 91);   // Play NOTE_C4 for 91ms. | Reproduz NOTE_C4 por 91ms.

  buzzer.sound(NOTE_A3, 365);
  buzzer.sound(NOTE_F3, 275);
  buzzer.sound(NOTE_C4, 91);
  buzzer.sound(NOTE_A3, 730);  // Play NOTE_A3 for 730ms. | Reproduz NOTE_A3 por 730ms.

  // Imperial March Theme - Part 2
  buzzer.sound(NOTE_E4, 365);  // Play NOTE_E4 for 365ms. | Reproduz NOTE_E4 por 365ms.
  buzzer.sound(NOTE_E4, 365);
  buzzer.sound(NOTE_E4, 365);
  buzzer.sound(NOTE_F4, 275);  // Play NOTE_F4 for 275ms. | Reproduz NOTE_F4 por 275ms.
  buzzer.sound(NOTE_C4, 91);

  buzzer.sound(NOTE_GS3, 365); // Play NOTE_GS3 for 365ms. | Reproduz NOTE_GS3 por 365ms.
  buzzer.sound(NOTE_F3, 275);
  buzzer.sound(NOTE_C4, 91);
  buzzer.sound(NOTE_A3, 730);  // Play NOTE_A3 for 730ms. | Reproduz NOTE_A3 por 730ms.

  // Imperial March Theme - Part 3
  buzzer.sound(NOTE_A4, 365);  // Play NOTE_A4 for 365ms. | Reproduz NOTE_A4 por 365ms.
  buzzer.sound(NOTE_A3, 275);
  buzzer.sound(NOTE_A3, 91);
  buzzer.sound(NOTE_A4, 365);
  buzzer.sound(NOTE_GS4, 275); // Play NOTE_GS4 for 275ms. | Reproduz NOTE_GS4 por 275ms.
  buzzer.sound(NOTE_G4, 91);

  buzzer.sound(NOTE_FS4, 91);  // Play NOTE_FS4 for 91ms. | Reproduz NOTE_FS4 por 91ms.
  buzzer.sound(NOTE_E4, 91);
  buzzer.sound(NOTE_F4, 182);  // Play NOTE_F4 for 182ms. | Reproduz NOTE_F4 por 182ms.
  buzzer.sound(0, 182);        // Pause for 182ms (silence). | Pausa por 182ms (silêncio).
  buzzer.sound(NOTE_AS3, 182); // Play NOTE_AS3 for 182ms. | Reproduz NOTE_AS3 por 182ms.
  buzzer.sound(NOTE_DS4, 365); // Play NOTE_DS4 for 365ms. | Reproduz NOTE_DS4 por 365ms.
  buzzer.sound(NOTE_D4, 275);  // Play NOTE_D4 for 275ms. | Reproduz NOTE_D4 por 275ms.
  buzzer.sound(NOTE_CS4, 91);

  buzzer.sound(NOTE_C4, 91);   // Play NOTE_C4 for 91ms. | Reproduz NOTE_C4 por 91ms.
  buzzer.sound(NOTE_B3, 91);
  buzzer.sound(NOTE_C4, 182);  // Play NOTE_C4 for 182ms. | Reproduz NOTE_C4 por 182ms.
  buzzer.sound(0, 182);        // Pause for 182ms (silence). | Pausa por 182ms (silêncio).
  buzzer.sound(NOTE_F3, 182);
  buzzer.sound(NOTE_GS3, 365); // Play NOTE_GS3 for 365ms. | Reproduz NOTE_GS3 por 365ms.
  buzzer.sound(NOTE_F3, 275);
  buzzer.sound(NOTE_A3, 91);

  // Imperial March Theme - Part 4
  buzzer.sound(NOTE_C4, 365);  // Play NOTE_C4 for 365ms. | Reproduz NOTE_C4 por 365ms.
  buzzer.sound(NOTE_A3, 275);
  buzzer.sound(NOTE_C4, 91);
  buzzer.sound(NOTE_E4, 730);  // Play NOTE_E4 for 730ms. | Reproduz NOTE_E4 por 730ms.

  buzzer.sound(NOTE_A4, 365);  // Play NOTE_A4 for 365ms. | Reproduz NOTE_A4 por 365ms.
  buzzer.sound(NOTE_A3, 275);
  buzzer.sound(NOTE_A3, 91);
  buzzer.sound(NOTE_A4, 365);
  buzzer.sound(NOTE_GS4, 275);
  buzzer.sound(NOTE_G4, 91);

  buzzer.sound(NOTE_FS4, 91);  // Play NOTE_FS4 for 91ms. | Reproduz NOTE_FS4 por 91ms.
  buzzer.sound(NOTE_E4, 91);
  buzzer.sound(NOTE_F4, 182);
  buzzer.sound(0, 182);
  buzzer.sound(NOTE_AS3, 182);
  buzzer.sound(NOTE_DS4, 365);
  buzzer.sound(NOTE_D4, 275);
  buzzer.sound(NOTE_CS4, 91);

  buzzer.sound(NOTE_C4, 91);   // Play NOTE_C4 for 91ms. | Reproduz NOTE_C4 por 91ms.
  buzzer.sound(NOTE_B3, 91);
  buzzer.sound(NOTE_C4, 182);  // Play NOTE_C4 for 182ms. | Reproduz NOTE_C4 por 182ms.
  buzzer.sound(0, 182);        // Pause for 182ms (silence). | Pausa por 182ms (silêncio).
  buzzer.sound(NOTE_F3, 182);
  buzzer.sound(NOTE_GS3, 365);
  buzzer.sound(NOTE_F3, 275);
  buzzer.sound(NOTE_C4, 91);

  buzzer.sound(NOTE_A3, 365);  // Play NOTE_A3 for 365ms. | Reproduz NOTE_A3 por 365ms.
  buzzer.sound(NOTE_F3, 275);
  buzzer.sound(NOTE_C4, 91);
  buzzer.sound(NOTE_A3, 730);  // Play NOTE_A3 for 730ms. | Reproduz NOTE_A3 por 730ms.

  // Pause before repeating
  buzzer.end(5000); // Pause for 5 seconds before repeating. | Pausa de 5 segundos antes de repetir.
}
