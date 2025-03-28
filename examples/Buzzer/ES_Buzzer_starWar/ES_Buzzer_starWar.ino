/**
* @file ES_Buzzer_starWars.ino
* @brief This example plays the Star Wars theme using the ES_Buzzer class on the ES32Lab board.
* | Este exemplo reproduz o tema de Star Wars usando a classe ES_Buzzer na placa ES32Lab.
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

// Instância da classe ES_Buzzer utilizando o pino P_BUZZER.
// | Instance of the ES_Buzzer class using the P_BUZZER pin.
ES_Buzzer buzzer(P_BUZZER);

void setup() {
  buzzer.begin(); // Inicializa o buzzer. | Initializes the buzzer.
}

void loop() {
  // Star Wars Theme - Parte 1
  buzzer.sound(NOTE_AS4, 218);  // Play NOTE_AS4 for 218ms. | Reproduz NOTE_AS4 por 218ms.
  buzzer.sound(NOTE_AS4, 218);
  buzzer.sound(NOTE_AS4, 218);
  buzzer.sound(NOTE_F5, 870);
  buzzer.sound(NOTE_C6, 870);
  buzzer.sound(NOTE_AS5, 218);
  buzzer.sound(NOTE_A5, 218);
  buzzer.sound(NOTE_G5, 218);
  buzzer.sound(NOTE_F6, 870);
  buzzer.sound(NOTE_C6, 435);
  buzzer.sound(NOTE_AS5, 218);
  buzzer.sound(NOTE_A5, 218);
  buzzer.sound(NOTE_G5, 218);
  buzzer.sound(NOTE_F6, 870);
  buzzer.sound(NOTE_C6, 435);

  // Star Wars Theme - Parte 2
  buzzer.sound(NOTE_AS5, 218);
  buzzer.sound(NOTE_A5, 218);
  buzzer.sound(NOTE_AS5, 218);
  buzzer.sound(NOTE_G5, 870);
  buzzer.sound(NOTE_C5, 218);
  buzzer.sound(NOTE_C5, 218);
  buzzer.sound(NOTE_C5, 218);
  buzzer.sound(NOTE_F5, 870);
  buzzer.sound(NOTE_C6, 870);
  buzzer.sound(NOTE_AS5, 218);
  buzzer.sound(NOTE_A5, 218);
  buzzer.sound(NOTE_G5, 218);
  buzzer.sound(NOTE_F6, 870);
  buzzer.sound(NOTE_C6, 435);

  // Pausa antes de reiniciar a melodia
  buzzer.end(1500); // Pause for 1.5 seconds before repeating. | Pausa de 1.5 segundos antes de repetir.
}
