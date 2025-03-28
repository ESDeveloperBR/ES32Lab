/**
* @file ES_Buzzer_gameOfThrones.ino
* @brief This example plays the Game of Thrones theme using the ES_Buzzer class on the ES32Lab board.
* | Este exemplo reproduz o tema de Game of Thrones usando a classe ES_Buzzer na placa ES32Lab.
* @warning Ensure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) installed.
* | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) está instalada.
* @attention Ensure that the buzzer of the ES32Lab is activated via the green jumper "BUZZER/P25". 
* | Atenção: Lembre-se de ativar o buzzer da ES32Lab através do jumper verde "BUZZER/P25".
* @see Official board: https://www.esdeveloper.com.br
* | Placa oficial disponível em: https://www.esdeveloper.com.br
* @see ES_Buzzer documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
* | Documentação da classe ES_Buzzer: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
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
    buzzer.sound(NOTE_G4, 240); // Play NOTE_G4 for 240ms. | Reproduz NOTE_G4 por 240ms.
    buzzer.sound(NOTE_C4, 240);
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_G4, 240);
    buzzer.sound(NOTE_C4, 240);
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_G4, 240);
    buzzer.sound(NOTE_C4, 240);
    buzzer.sound(NOTE_E4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_G4, 240);
    buzzer.sound(NOTE_C4, 240);
    buzzer.sound(NOTE_E4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_G4, 960);
    buzzer.sound(NOTE_C4, 960);

    // Game of Thrones Theme - Part 2
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_G4, 720);
    buzzer.sound(NOTE_C4, 720);
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_F4, 120);
    buzzer.sound(NOTE_D4, 2880);
    buzzer.sound(NOTE_F4, 960);
    buzzer.sound(NOTE_AS3, 960);
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_D4, 120);
    buzzer.sound(NOTE_F4, 720);
    buzzer.sound(NOTE_AS3, 960);
    buzzer.sound(NOTE_DS4, 120);
    buzzer.sound(NOTE_D4, 120);
    buzzer.sound(NOTE_C4, 2880);

    // Game of Thrones Theme - Final Part
    buzzer.sound(NOTE_C5, 1440);
    buzzer.sound(NOTE_AS4, 1440);
    buzzer.sound(NOTE_C4, 1440);
    buzzer.sound(NOTE_G4, 1440);
    buzzer.sound(NOTE_DS4, 1440);
    buzzer.sound(NOTE_G4, 960);
    buzzer.sound(NOTE_C5, 480);
    buzzer.sound(NOTE_G4, 480);
    buzzer.sound(NOTE_GS4, 240);
    buzzer.sound(NOTE_AS4, 240);
    buzzer.sound(NOTE_C5, 480);
    buzzer.sound(NOTE_G4, 480);
    buzzer.sound(NOTE_GS4, 240);
    buzzer.sound(NOTE_AS4, 240);
 
    buzzer.end(1500); // Pause for 1.5 seconds before repeating. | Pausa de 1.5 segundos antes de repetir.
}