/**
 * @file ledBlinkGreen.ino
 * @brief This example demonstrates how to blink the green LED on the ES32Lab board repeatedly. 
 * The green LED is connected to GPIO17, labeled directly on the ES32Lab board.
 * | Este exemplo demonstra como piscar o LED verde na placa ES32Lab repetidamente. 
 * O LED verde está conectado ao GPIO17, identificado diretamente na placa ES32Lab.
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * @attention The GPIOs used for the LEDs are labeled directly on the ES32Lab board. 
 * For more details, watch the video tutorial at: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=250s
 * | Atenção: Os GPIOs utilizados para os LEDs estão anotados diretamente na placa ES32Lab. 
 * Para mais detalhes, assista ao tutorial em vídeo em: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=250s
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES32Lab documentation: https://github.com/ESDeveloperBR/ES32Lab#readme
 * | Documentação da ES32Lab: https://github.com/ESDeveloperBR/ES32Lab#readme
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab

// <<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  pinMode(P_LED_GREEN , OUTPUT);  // Sets the green LED pin as output | Define o pino do LED verde como saída
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);  // Turns on the green LED | Liga o LED verde
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos

  digitalWrite(P_LED_GREEN, LOW); // Turns off the green LED | Desliga o LED verde
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
}