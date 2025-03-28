/**
* @file ES_Buzzer_PinkPanther.ino
* @brief This example plays the theme of the Pink Panther on the ESP32Lab buzzer.
* | Este exemplo reproduz o tema da Pantera Cor-de-Rosa no buzzer da ES32Lab.
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
 
ES_Buzzer buzzer(P_BUZZER); // Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin. | Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'.
 
// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  buzzer.begin(); // Initialize the buzzer instance. | Inicializa a instância do buzzer.
}
 
// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  // Play the Pink Panther melody on the buzzer. | Reproduz a melodia da Pantera Cor-de-Rosa no buzzer.
 
  buzzer.sound(0, 480); // Pause for 480ms. | Pausa por 480ms.
  buzzer.sound(0, 240); // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_DS4, 240); // Play note DS4 for 240ms. | Toca a nota DS4 por 240ms.
  buzzer.sound(NOTE_E4, 480);  // Play note E4 for 480ms. | Toca a nota E4 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_FS4, 240); // Play note FS4 for 240ms. | Toca a nota FS4 por 240ms.
  buzzer.sound(NOTE_G4, 480);  // Play note G4 for 480ms. | Toca a nota G4 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_DS4, 240); // Play note DS4 for 240ms. | Toca a nota DS4 por 240ms.
   
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(NOTE_FS4, 240); // Play note FS4 for 240ms. | Toca a nota FS4 por 240ms.
  buzzer.sound(NOTE_G4, 240);  // Play note G4 for 240ms. | Toca a nota G4 por 240ms.
  buzzer.sound(NOTE_C5, 240);  // Play note C5 for 240ms. | Toca a nota C5 por 240ms.
  buzzer.sound(NOTE_B4, 240);  // Play note B4 for 240ms. | Toca a nota B4 por 240ms.
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(NOTE_G4, 240);  // Play note G4 for 240ms. | Toca a nota G4 por 240ms.
  buzzer.sound(NOTE_B4, 240);  // Play note B4 for 240ms. | Toca a nota B4 por 240ms.
  buzzer.sound(NOTE_AS4, 480); // Play note AS4 for 480ms. | Toca a nota AS4 por 480ms.
  buzzer.sound(NOTE_A4, 160);  // Play note A4 for 160ms. | Toca a nota A4 por 160ms.
   
  buzzer.sound(NOTE_G4, 160);  // Play note G4 for 160ms. | Toca a nota G4 por 160ms.
  buzzer.sound(NOTE_E4, 160);  // Play note E4 for 160ms. | Toca a nota E4 por 160ms.
  buzzer.sound(NOTE_D4, 160);  // Play note D4 for 160ms. | Toca a nota D4 por 160ms.
  buzzer.sound(NOTE_E4, 480);  // Play note E4 for 480ms. | Toca a nota E4 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_DS4, 240); // Play note DS4 for 240ms. | Toca a nota DS4 por 240ms.
  buzzer.sound(NOTE_E4, 480);  // Play note E4 for 480ms. | Toca a nota E4 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_FS4, 240); // Play note FS4 for 240ms. | Toca a nota FS4 por 240ms.
  buzzer.sound(NOTE_G4, 480);  // Play note G4 for 480ms. | Toca a nota G4 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_DS4, 240); // Play note DS4 for 240ms. | Toca a nota DS4 por 240ms.
   
  buzzer.sound(NOTE_E4, 240);  // Play note E4 for 240ms. | Toca a nota E4 por 240ms.
  buzzer.sound(NOTE_FS4, 240); // Play note FS4 for 240ms. | Toca a nota FS4 por 240ms.
  buzzer.sound(NOTE_G4, 240);  // Play note G4 for 240ms. | Toca a nota G4 por 240ms.
  buzzer.sound(NOTE_C5, 240);  // Play note C5 for 240ms. | Toca a nota C5 por 240ms.
  buzzer.sound(NOTE_B4, 240);  // Play note B4 for 240ms. | Toca a nota B4 por 240ms.
  buzzer.sound(NOTE_E5, 480);  // Play note E5 for 480ms. | Toca a nota E5 por 480ms.
  buzzer.sound(NOTE_DS5, 960); // Play note DS5 for 960ms. | Toca a nota DS5 por 960ms.
  buzzer.sound(NOTE_D5, 480);  // Play note D5 for 480ms. | Toca a nota D5 por 480ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(0, 240);        // Pause for 240ms. | Pausa por 240ms.
  buzzer.sound(NOTE_DS4, 240); // Play note DS4 for 240ms. | Toca a nota DS4 por 240ms.
   
  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}
 