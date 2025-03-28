/**
* @file ES_Buzzer_HappyBirthday.ino
* @brief This example plays "Happy Birthday" on the ESP32Lab buzzer.
* | Este exemplo reproduz "Parabéns pra Você" no buzzer da ES32Lab.
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
  // Play "Happy Birthday" melody. | Reproduz a melodia de "Parabéns pra Você".
  
  buzzer.sound(NOTE_C4, 278);  // Play note C4 for 278ms. | Toca a nota C4 por 278ms.
  buzzer.sound(NOTE_C4, 138);  // Play note C4 for 138ms. | Toca a nota C4 por 138ms.
  buzzer.sound(NOTE_D4, 416);  // Play note D4 for 416ms. | Toca a nota D4 por 416ms.
  buzzer.sound(NOTE_C4, 416);  // Play note C4 for 416ms. | Toca a nota C4 por 416ms.
  buzzer.sound(NOTE_F4, 416);  // Play note F4 for 416ms. | Toca a nota F4 por 416ms.
  buzzer.sound(NOTE_E4, 834);  // Play note E4 for 834ms. | Toca a nota E4 por 834ms.
  
  buzzer.sound(NOTE_C4, 278);  // Play note C4 for 278ms. | Toca a nota C4 por 278ms.
  buzzer.sound(NOTE_C4, 138);  // Play note C4 for 138ms. | Toca a nota C4 por 138ms.
  buzzer.sound(NOTE_D4, 416);  // Play note D4 for 416ms. | Toca a nota D4 por 416ms.
  buzzer.sound(NOTE_C4, 416);  // Play note C4 for 416ms. | Toca a nota C4 por 416ms.
  buzzer.sound(NOTE_G4, 416);  // Play note G4 for 416ms. | Toca a nota G4 por 416ms.
  buzzer.sound(NOTE_F4, 834);  // Play note F4 for 834ms. | Toca a nota F4 por 834ms.
  
  buzzer.sound(NOTE_C4, 278);  // Play note C4 for 278ms. | Toca a nota C4 por 278ms.
  buzzer.sound(NOTE_C5, 416);  // Play note C5 for 416ms. | Toca a nota C5 por 416ms.
  buzzer.sound(NOTE_A4, 416);  // Play note A4 for 416ms. | Toca a nota A4 por 416ms.
  buzzer.sound(NOTE_F4, 416);  // Play note F4 for 416ms. | Toca a nota F4 por 416ms.
  buzzer.sound(NOTE_E4, 416);  // Play note E4 for 416ms. | Toca a nota E4 por 416ms.
  buzzer.sound(NOTE_D4, 834);  // Play note D4 for 834ms. | Toca a nota D4 por 834ms.
  
  buzzer.sound(NOTE_AS4, 278); // Play note AS4 for 278ms. | Toca a nota AS4 por 278ms.
  buzzer.sound(NOTE_AS4, 138); // Play note AS4 for 138ms. | Toca a nota AS4 por 138ms.
  buzzer.sound(NOTE_A4, 416);  // Play note A4 for 416ms. | Toca a nota A4 por 416ms.
  buzzer.sound(NOTE_F4, 416);  // Play note F4 for 416ms. | Toca a nota F4 por 416ms.
  buzzer.sound(NOTE_G4, 416);  // Play note G4 for 416ms. | Toca a nota G4 por 416ms.
  buzzer.sound(NOTE_F4, 834);  // Play note F4 for 834ms. | Toca a nota F4 por 834ms.
    
  buzzer.end(5000); // Wait 5 seconds before repeating the melody. | Espera 5 segundos antes de repetir a melodia.
}  