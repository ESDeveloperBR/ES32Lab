/**
 * @file ledBlink.ino
 * @brief This example demonstrates how to alternately blink the LEDs on the ES32Lab board. 
 * The LEDs used are: Green (GPIO17), Yellow (GPIO16), Red (GPIO13), and Blue (GPIO12).
 * | Este exemplo demonstra como piscar alternadamente os LEDs na placa ES32Lab. 
 * Os LEDs utilizados são: Verde (GPIO17), Amarelo (GPIO16), Vermelho (GPIO13) e Azul (GPIO12).
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
  pinMode(P_LED_YELLOW, OUTPUT);  // Sets the yellow LED pin as output | Define o pino do LED amarelo como saída
  pinMode(P_LED_RED   , OUTPUT);  // Sets the red LED pin as output | Define o pino do LED vermelho como saída
  pinMode(P_LED_BLUE  , OUTPUT);  // Sets the blue LED pin as output | Define o pino do LED azul como saída
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);  // Turns on the green LED | Liga o LED verde
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_YELLOW, HIGH); // Turns on the yellow LED | Liga o LED amarelo
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_RED, HIGH);  // Turns on the red LED | Liga o LED vermelho
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_BLUE, HIGH); // Turns on the blue LED | Liga o LED azul
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos

  digitalWrite(P_LED_GREEN, LOW); // Turns off the green LED | Desliga o LED verde
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_YELLOW, LOW); // Turns off the yellow LED | Desliga o LED amarelo
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_RED, LOW); // Turns off the red LED | Desliga o LED vermelho
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
  digitalWrite(P_LED_BLUE, LOW);  // Turns off the blue LED | Desliga o LED azul
  delay(500); // Waits for 500 milliseconds | Aguarda 500 milissegundos
}