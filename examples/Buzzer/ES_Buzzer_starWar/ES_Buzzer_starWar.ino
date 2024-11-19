/**
 * @file ES_Buzzer_starWars.ino
 * @brief This example plays the Star Wars theme using the ES_Buzzer class on the ES32Lab board.
 * | Este exemplo reproduz o tema de Star Wars usando a classe ES_Buzzer na placa ES32Lab.
 * @warning Ensure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) está instalada.
 */

#include <Arduino.h>
#include <ES32Lab.h>

// Instância da classe ES_Buzzer utilizando o pino P_BUZZER.
// | Instance of the ES_Buzzer class using the P_BUZZER pin.
ES_Buzzer buzzer(P_BUZZER);

void setup() {
  buzzer.begin(); // Inicializa o buzzer. | Initializes the buzzer.
}

void loop() {
  // Star Wars Theme - Parte 1
  buzzer.sound(NOTE_AS4, 150);  // Play NOTE_AS4 for 150ms. | Reproduz NOTE_AS4 por 150ms.
  buzzer.sound(NOTE_AS4, 150);
  buzzer.sound(NOTE_AS4, 150);
  buzzer.sound(NOTE_F5, 600);  // Play NOTE_F5 for 600ms. | Reproduz NOTE_F5 por 600ms.
  buzzer.sound(NOTE_C6, 600);  // Play NOTE_C6 for 600ms. | Reproduz NOTE_C6 por 600ms.
  buzzer.sound(NOTE_AS5, 150);
  buzzer.sound(NOTE_A5, 150);
  buzzer.sound(NOTE_G5, 150);
  buzzer.sound(NOTE_F6, 600);
  buzzer.sound(NOTE_C6, 300);  // Pause for 300ms | Pausa por 300ms.
  buzzer.sound(NOTE_AS5, 150);
  buzzer.sound(NOTE_A5, 150);
  buzzer.sound(NOTE_G5, 150);
  buzzer.sound(NOTE_F6, 600);
  buzzer.sound(NOTE_C6, 300);

  // Star Wars Theme - Parte 2
  buzzer.sound(NOTE_AS5, 150);
  buzzer.sound(NOTE_A5, 150);
  buzzer.sound(NOTE_AS5, 150);
  buzzer.sound(NOTE_G5, 600);
  buzzer.sound(NOTE_C5, 150);
  buzzer.sound(NOTE_C5, 150);
  buzzer.sound(NOTE_C5, 150);
  buzzer.sound(NOTE_F5, 600);
  buzzer.sound(NOTE_C6, 600);
  buzzer.sound(NOTE_AS5, 150);
  buzzer.sound(NOTE_A5, 150);
  buzzer.sound(NOTE_G5, 150);
  buzzer.sound(NOTE_F6, 600);
  buzzer.sound(NOTE_C6, 300);

  // Pausa antes de reiniciar a melodia
  buzzer.end(1500); // Pause for 1.5 seconds before repeating. | Pausa de 1.5 segundos antes de repetir.
}
