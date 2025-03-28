/**
* @file ES_Buzzer_hinoNacionalBrasileiro.ino
* @brief This example plays the Brazilian National Anthem on the ESP32Lab buzzer.
* | Este exemplo reproduz o Hino Nacional Brasileiro no buzzer da ES32Lab.
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
  // Play the Brazilian National Anthem melody. | Reproduz a melodia do Hino Nacional Brasileiro.
 
  buzzer.sound(NOTE_C4, 487);   // Play note C4 for 487ms. | Toca a nota C4 por 487ms.
  buzzer.sound(NOTE_F4, 325);   // Play note F4 for 325ms. | Toca a nota F4 por 325ms.
  buzzer.sound(NOTE_E4, 122);   // Play note E4 for 122ms. | Toca a nota E4 por 122ms.
  buzzer.sound(NOTE_F4, 325);   // Play note F4 for 325ms. | Toca a nota F4 por 325ms.
  buzzer.sound(NOTE_G4, 122);   // Play note G4 for 122ms. | Toca a nota G4 por 122ms.
  buzzer.sound(NOTE_A4, 325);   // Play note A4 for 325ms. | Toca a nota A4 por 325ms.
  buzzer.sound(NOTE_G4, 122);   // Play note G4 for 122ms. | Toca a nota G4 por 122ms.
  buzzer.sound(NOTE_A4, 325);   // Play note A4 for 325ms. | Toca a nota A4 por 325ms.
  buzzer.sound(NOTE_AS4, 122);  // Play note AS4 for 122ms. | Toca a nota AS4 por 122ms.
  buzzer.sound(NOTE_B4, 325);   // Play note B4 for 325ms. | Toca a nota B4 por 325ms.
  buzzer.sound(NOTE_C5, 975);   // Play note C5 for 975ms. | Toca a nota C5 por 975ms.

  buzzer.sound(NOTE_F4, 487);   // Play note F4 for 487ms. | Toca a nota F4 por 487ms.
  buzzer.sound(NOTE_C4, 325);   // Play note C4 for 325ms. | Toca a nota C4 por 325ms.
  buzzer.sound(NOTE_F4, 122);   // Play note F4 for 122ms. | Toca a nota F4 por 122ms.
  buzzer.sound(NOTE_E4, 325);   // Play note E4 for 325ms. | Toca a nota E4 por 325ms.
  buzzer.sound(NOTE_G4, 325);   // Play note G4 for 325ms. | Toca a nota G4 por 325ms.
  buzzer.sound(NOTE_F4, 325);   // Play note F4 for 325ms. | Toca a nota F4 por 325ms.
  buzzer.sound(NOTE_A4, 325);   // Play note A4 for 325ms. | Toca a nota A4 por 325ms.
  buzzer.sound(NOTE_G4, 325);   // Play note G4 for 325ms. | Toca a nota G4 por 325ms.
  buzzer.sound(NOTE_AS4, 325);  // Play note AS4 for 325ms. | Toca a nota AS4 por 325ms.
  buzzer.sound(NOTE_A4, 122);   // Play note A4 for 122ms. | Toca a nota A4 por 122ms.
  buzzer.sound(NOTE_FS4, 325);  // Play note FS4 for 325ms. | Toca a nota FS4 por 325ms.

  buzzer.sound(NOTE_G4, 487);   // Play note G4 for 487ms. | Toca a nota G4 por 487ms.
  buzzer.sound(0, 650);         // Pause for 650ms. | Pausa por 650ms.
  buzzer.sound(NOTE_C4, 325);   // Play note C4 for 325ms. | Toca a nota C4 por 325ms.
  buzzer.sound(NOTE_G4, 325);   // Play note G4 for 325ms. | Toca a nota G4 por 325ms.
  buzzer.sound(NOTE_FS4, 122);  // Play note FS4 for 122ms. | Toca a nota FS4 por 122ms.
  buzzer.sound(NOTE_G4, 325);   // Play note G4 for 325ms. | Toca a nota G4 por 325ms.
  buzzer.sound(NOTE_A4, 325);   // Play note A4 for 325ms. | Toca a nota A4 por 325ms.
  buzzer.sound(NOTE_AS4, 325);  // Play note AS4 for 325ms. | Toca a nota AS4 por 325ms.

  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}