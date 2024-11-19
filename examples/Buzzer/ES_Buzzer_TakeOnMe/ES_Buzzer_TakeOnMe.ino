/**
 * @file ES_Buzzer_TakeOnMe.ino
 * @brief This example plays the theme of "Take On Me" by A-ha on the ESP32Lab buzzer.
 * | Este exemplo reproduz o tema de "Take On Me" da banda A-ha no buzzer da ES32Lab.
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
  // Play "Take On Me" melody on the buzzer. | Reproduz a melodia de "Take On Me" no buzzer.

  buzzer.sound(NOTE_FS5, 107); // Play note FS5 for 107ms. | Toca a nota FS5 por 107ms.
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_D5, 107); // Play note D5 for 107ms. | Toca a nota D5 por 107ms.
  buzzer.sound(NOTE_B4, 107); // Play note B4 for 107ms. | Toca a nota B4 por 107ms.
  buzzer.sound(0, 107);       // Pause for 107ms. | Pausa por 107ms.
  buzzer.sound(NOTE_B4, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107); // Play note E5 for 107ms. | Toca a nota E5 por 107ms.
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107);

  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_GS5, 107); // Play note GS5 for 107ms. | Toca a nota GS5 por 107ms.
  buzzer.sound(NOTE_GS5, 107);
  buzzer.sound(NOTE_A5, 107);  // Play note A5 for 107ms. | Toca a nota A5 por 107ms.
  buzzer.sound(NOTE_B5, 107);  // Play note B5 for 107ms. | Toca a nota B5 por 107ms.
  buzzer.sound(NOTE_A5, 107);  // Play note A5 for 107ms. | Toca a nota A5 por 107ms.
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_E5, 107);

  buzzer.sound(0, 107);
  buzzer.sound(NOTE_D5, 107);  // Play note D5 for 107ms. | Toca a nota D5 por 107ms.
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107); // Play note FS5 for 107ms. | Toca a nota FS5 por 107ms.
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_FS5, 107);

  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_D5, 107);
  buzzer.sound(NOTE_B4, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_B4, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107);

  buzzer.sound(0, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_GS5, 107);
  buzzer.sound(NOTE_GS5, 107);
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_B5, 107);
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_A5, 107);
  buzzer.sound(NOTE_E5, 107);

  buzzer.sound(0, 107);
  buzzer.sound(NOTE_D5, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(0, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_E5, 107);
  buzzer.sound(NOTE_FS5, 107);
  buzzer.sound(NOTE_E5, 107);

  buzzer.end(5000); // Wait 3.3 seconds before repeating the melody. | Espera 3.3 segundos antes de repetir a melodia.
}
