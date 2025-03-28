/**
* @file ES_Buzzer_jingleBells.ino
* @brief This example plays the Jingle Bells theme using the ES_Buzzer class on the ES32Lab board.
* | Este exemplo reproduz o tema de Jingle Bells usando a classe ES_Buzzer na placa ES32Lab.
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
  buzzer.setSpeed(50); // Set the speed of the song to 50%. | Define a velocidade da música para 50%.
}
 
void loop() {
  buzzer.sound(NOTE_G3, 166); // Play NOTE_G3 for 166ms. | Reproduz NOTE_G3 por 166ms.
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_G3, 666); // Play NOTE_G3 for 666ms. | Reproduz NOTE_G3 por 666ms.
    
  buzzer.sound(NOTE_G3, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_A4, 666);
    
  buzzer.sound(NOTE_A4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_G4, 250); // Play NOTE_G4 for 250ms. | Reproduz NOTE_G4 por 250ms.
  buzzer.sound(NOTE_G4, 250);
    
  buzzer.sound(NOTE_A5, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_E4, 666);
    
  buzzer.sound(NOTE_G3, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_G3, 666);
    
  buzzer.sound(NOTE_G3, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_A4, 666);
    
  buzzer.sound(NOTE_A4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_G4, 250);
  buzzer.sound(NOTE_G4, 84); // Play NOTE_G4 for 84ms. | Reproduz NOTE_G4 por 84ms.
   
  buzzer.sound(NOTE_A5, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 666);
    
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 250); // Play NOTE_E4 for 250ms. | Reproduz NOTE_E4 por 250ms.
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 250);
    
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_E4, 666);
    
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 84); // Play NOTE_E4 for 84ms. | Reproduz NOTE_E4 por 84ms.
  buzzer.sound(NOTE_E4, 84);
    
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_D4, 250);
  buzzer.sound(NOTE_G4, 250);
    
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 250);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 250);
    
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_C4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_E4, 666);
    
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 166);
  buzzer.sound(NOTE_E4, 84);
  buzzer.sound(NOTE_E4, 84);
    
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_G4, 166);
  buzzer.sound(NOTE_F4, 166);
  buzzer.sound(NOTE_D4, 166);
  buzzer.sound(NOTE_C4, 666);
    
  buzzer.end(5000); // Pause for 5s before repeating. | Pausa de 5s antes de repetir.
}
 