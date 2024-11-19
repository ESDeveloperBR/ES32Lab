/**
 * @file ES_Buzzer_superMario.ino
 * @brief This example plays the soundtrack of the classic Nintendo game Super Mario World on the ESP32Lab buzzer.
 * | Este exemplo reproduz a trilha sonora do clássico jogo da Nintendo, Super Mario World, no buzzer do ESP32Lab.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER);   // Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'. | Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin.

// <<<<<<<<<< setup >>>>>>>>>>
void setup(){
  buzzer.begin(); // Initialize the settings of the 'buzzer' instance. | Inicializa as configurações da instância 'buzzer'.
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  buzzer.sound(NOTE_E7, 80);  // Play the note E7 for 80 milliseconds. | Reproduz a nota E7 por 80 milissegundos.
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);        // Pause for 80 milliseconds (silent). | Pausa por 80 milissegundos (silêncio).
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 240);       // Pause for 240 milliseconds (silent). | Pausa por 240 milissegundos (silêncio).
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 240);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_E6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_AS6, 80);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G6, 100);
  buzzer.sound(NOTE_E7, 100);
  buzzer.sound(NOTE_G7, 100);
  buzzer.sound(NOTE_A7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_F7, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_D7, 80);
  buzzer.sound(NOTE_B6, 80);

  buzzer.end(5000);  // Wait for 5 seconds before repeating the melody. | Espera por 5 segundos antes de repetir a melodia.
}
