/**
 * @file ES_Buzzer_pitch.ino
 * @brief In this example, we play a portion of the soundtrack from the classic Nintendo game, Super 
 * Mario World, on the ESP32Lab buzzer. With each iteration of the main loop, a new value is added to
 * the melody's pitch.
 * | Neste exemplo, reproduzimos parte da trilha sonora do clássico jogo da Nintendo, Super 
 * Mario World, no buzzer do ESP32Lab. A cada ciclo do LOOP principal, é incrementado um novo valor 
 * ao pitch da melodia.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER);   // Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'. | Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin.
int percentagePitch = 25;
// <<<<<<<<<< setup >>>>>>>>>>
void setup(){
  buzzer.begin(); // Initialize the settings of the 'buzzer' instance. | Inicializa as configurações da instância 'buzzer'.
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  buzzer.pitch(percentagePitch); // Adjusts the playback speed of the generated melody, where values below 100% make the melody slower and values above 100% make it faster. | Ajusta a velocidade de reprodução da melodia gerada, onde valores abaixo de 100% tornam a melodia mais lenta e valores acima de 100% a tornam mais rápida.

  buzzer.sound(NOTE_E7, 80);  // Play the note E7 for 80 milliseconds. | Reproduz a nota E7 por 80 milissegundos.
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);        // Pause for 80 milliseconds (silent). | Pausa por 80 milissegundos (silêncio).
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 240);       // Pause for 240 milliseconds (silent). | Pausa por 240 milissegundos (silêncio).
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 240);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_E6, 80);
  buzzer.sound(0, 160);

  buzzer.end(1000);  // Wait for 5 seconds before repeating the melody. | Espera por 5 segundos antes de repetir a melodia.
  percentagePitch = percentagePitch + 25; // Increase the percentage value of the pitch speed to notice the difference in the melody's pitch adjustment more prominently. | Aumente o valor percentual da velocidade de pitch para notar a diferença no ajuste do pitch da melodia de forma mais evidente.

}
