/**
 * @file ES_Buzzer_distortionEffect.ino
 * @brief Demonstrates the use of the 'distortion' method of the ES_Buzzer class to create dynamic sound effects.
 * | Demonstra o uso do método 'distortion' da classe ES_Buzzer para criar efeitos sonoros dinâmicos.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER);   // Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'. | Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin.

// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  buzzer.begin(); // Initialize the settings of the 'buzzer' instance. | Inicializa as configurações da instância 'buzzer'.
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  // Distortion from low to high pitch | Distorção de grave para agudo
  buzzer.distortion(NOTE_C4, NOTE_C6); // Distortion effect rising from C4 to C6 | Efeito de distorção subindo do C4 ao C6
  buzzer.end(500); // 500ms pause before the next effect | Pausa de 500ms antes do próximo efeito

  // Distortion from high to low pitch | Distorção de agudo para grave
  buzzer.distortion(NOTE_C6, NOTE_C4); // Distortion effect descending from C6 to C4 | Efeito de distorção descendo do C6 ao C4
  buzzer.end(500); // 500ms pause before the next effect | Pausa de 500ms antes do próximo efeito
}