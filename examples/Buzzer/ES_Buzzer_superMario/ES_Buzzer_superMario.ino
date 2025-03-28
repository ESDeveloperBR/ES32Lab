/**
* @file ES_Buzzer_superMario.ino
* @brief This example plays the soundtrack of the classic Nintendo game Super Mario World on the ESP32Lab buzzer.
* | Este exemplo reproduz a trilha sonora do clássico jogo da Nintendo, Super Mario World, no buzzer do ESP32Lab.
* @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
* | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
* @attention Ensure that the buzzer of the ES32Lab is activated via the green jumper "BUZZER/P25". 
* | Atenção: Lembre-se de ativar o buzzer da ES32Lab através do jumper verde "BUZZER/P25".
* @see Official board: https://www.esdeveloper.com.br
* | Placa oficial disponível em: https://www.esdeveloper.com.br
* @see ES_Buzzer documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
* | Documentação da classe ES_Buzzer: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
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
  buzzer.sound(NOTE_E7, 136);  // Play the note E7 for 136 milliseconds. | Reproduz a nota E7 por 136 milissegundos.
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);        // Pause for 136 milliseconds (silent). | Pausa por 136 milissegundos (silêncio).
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_C7, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_G7, 136);
  buzzer.sound(0, 408);        // Pause for 408 milliseconds (silent). | Pausa por 408 milissegundos (silêncio).
  buzzer.sound(NOTE_G6, 136);
  buzzer.sound(0, 408);
  buzzer.sound(NOTE_C7, 136);
  buzzer.sound(0, 272);
  buzzer.sound(NOTE_G6, 136);
  buzzer.sound(0, 272);
  buzzer.sound(NOTE_E6, 136);
  buzzer.sound(0, 272);
  buzzer.sound(NOTE_A6, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_B6, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_AS6, 136);
  buzzer.sound(NOTE_A6, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_G6, 170);   // Play the note G6 for 170 milliseconds. | Reproduz a nota G6 por 170 milissegundos.
  buzzer.sound(NOTE_E7, 170);   // Play the note E7 for 170 milliseconds. | Reproduz a nota E7 por 170 milissegundos.
  buzzer.sound(NOTE_G7, 170);   // Play the note G7 for 170 milliseconds. | Reproduz a nota G7 por 170 milissegundos.
  buzzer.sound(NOTE_A7, 136);   // Play the note A7 for 136 milliseconds. | Reproduz a nota A7 por 136 milissegundos.
  buzzer.sound(0, 136);         // Pause for 136 milliseconds (silent). | Pausa por 136 milissegundos (silêncio).
  buzzer.sound(NOTE_F7, 136);
  buzzer.sound(NOTE_G7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_C7, 136);
  buzzer.sound(NOTE_D7, 136);
  buzzer.sound(NOTE_B6, 136);

  buzzer.end(5000);  // Wait for 5 seconds before repeating the melody. | Espera por 5 segundos antes de repetir a melodia.
}
