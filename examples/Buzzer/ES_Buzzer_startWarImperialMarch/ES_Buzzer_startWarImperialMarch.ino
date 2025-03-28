/**
* @file ES_Buzzer_startWarImperialMarch.ino
* @brief This example plays the Imperial March theme using the ES_Buzzer class on the ES32Lab board.
* | Este exemplo reproduz o tema da Marcha Imperial usando a classe ES_Buzzer na placa ES32Lab.
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
  // Imperial March Theme - Part 1
  buzzer.sound(NOTE_A3, 511);  // Play NOTE_A3 for 511ms. | Reproduz NOTE_A3 por 511ms.
  buzzer.sound(NOTE_A3, 511);
  buzzer.sound(NOTE_A3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_C4, 127);
 
  buzzer.sound(NOTE_A3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_A3, 1022);

  // Imperial March Theme - Part 2
  buzzer.sound(NOTE_E4, 511);
  buzzer.sound(NOTE_E4, 511);
  buzzer.sound(NOTE_E4, 511);
  buzzer.sound(NOTE_F4, 385);
  buzzer.sound(NOTE_C4, 127);

  buzzer.sound(NOTE_GS3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_A3, 1022);

  // Imperial March Theme - Part 3
  buzzer.sound(NOTE_A4, 511);
  buzzer.sound(NOTE_A3, 385);
  buzzer.sound(NOTE_A3, 127);
  buzzer.sound(NOTE_A4, 511);
  buzzer.sound(NOTE_GS4, 385);
  buzzer.sound(NOTE_G4, 127);

  buzzer.sound(NOTE_FS4, 127);
  buzzer.sound(NOTE_E4, 127);
  buzzer.sound(NOTE_F4, 255);
  buzzer.sound(0, 255);       
  buzzer.sound(NOTE_AS3, 255);
  buzzer.sound(NOTE_DS4, 511);
  buzzer.sound(NOTE_D4, 385);
  buzzer.sound(NOTE_CS4, 127);

  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_B3, 127);
  buzzer.sound(NOTE_C4, 255);
  buzzer.sound(0, 255);
  buzzer.sound(NOTE_F3, 255);
  buzzer.sound(NOTE_GS3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_A3, 127);

  // Imperial March Theme - Part 4
  buzzer.sound(NOTE_C4, 511);
  buzzer.sound(NOTE_A3, 385);
  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_E4, 1022);

  buzzer.sound(NOTE_A4, 511);
  buzzer.sound(NOTE_A3, 385);
  buzzer.sound(NOTE_A3, 127);
  buzzer.sound(NOTE_A4, 511);
  buzzer.sound(NOTE_GS4, 385);
  buzzer.sound(NOTE_G4, 127);

  buzzer.sound(NOTE_FS4, 127);
  buzzer.sound(NOTE_E4, 127);
  buzzer.sound(NOTE_F4, 255);
  buzzer.sound(0, 255);
  buzzer.sound(NOTE_AS3, 255);
  buzzer.sound(NOTE_DS4, 511);
  buzzer.sound(NOTE_D4, 385);
  buzzer.sound(NOTE_CS4, 127);

  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_B3, 127);
  buzzer.sound(NOTE_C4, 255);
  buzzer.sound(0, 255);
  buzzer.sound(NOTE_F3, 255);
  buzzer.sound(NOTE_GS3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_C4, 127);

  buzzer.sound(NOTE_A3, 511);
  buzzer.sound(NOTE_F3, 385);
  buzzer.sound(NOTE_C4, 127);
  buzzer.sound(NOTE_A3, 1022);

  // Pause before repeating
  buzzer.end(5000); // Pause for 5 seconds before repeating. | Pausa de 5 segundos antes de repetir.
}
