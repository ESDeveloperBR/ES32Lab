/**
 * @file Potentiometer-TimeLedBlink.ino
 * @brief This example demonstrates how to alternately blink the LEDs on the ES32Lab board 
 * (Green, Yellow, Red, and Blue) with adjustable activation speed using potentiometers.
 * | Este exemplo demonstra como piscar alternadamente os LEDs na placa ES32Lab 
 * (Verde, Amarelo, Vermelho e Azul) com ajuste de velocidade de ativação usando potenciômetros.
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * @attention The GPIOs used for the LEDs and potentiometers are labeled directly on the ES32Lab board. 
 * Refer to the board for correct connections. For more details, watch the video tutorial at: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=250s
 * | Atenção: Os GPIOs utilizados para os LEDs e potenciômetros estão anotados diretamente na placa ES32Lab. 
 * Consulte a placa para conexões corretas. Para mais detalhes, assista ao tutorial em vídeo em: 
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
  Serial.begin(115200); // Initializes serial communication | Inicializa a comunicação serial
  pinMode(P_LED_GREEN , OUTPUT);  // Sets the green LED pin as output | Define o pino do LED verde como saída
  pinMode(P_LED_YELLOW, OUTPUT);  // Sets the yellow LED pin as output | Define o pino do LED amarelo como saída
  pinMode(P_LED_RED   , OUTPUT);  // Sets the red LED pin as output | Define o pino do LED vermelho como saída
  pinMode(P_LED_BLUE  , OUTPUT);  // Sets the blue LED pin as output | Define o pino do LED azul como saída

  pinMode(P_POT1, INPUT); // Sets the first potentiometer pin as input | Define o pino do primeiro potenciômetro como entrada
  pinMode(P_POT2, INPUT); // Sets the second potentiometer pin as input | Define o pino do segundo potenciômetro como entrada
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  int onTimer;  // Reads the value from the first potentiometer and maps it to a timer value | Lê o valor do primeiro potenciômetro e mapeia para um valor de temporizador
  onTimer = map(analogRead(P_POT1), 0, 4095, 1, 1000);  // Maps the potentiometer value to a range of 1 to 1000 milliseconds

  int offTimer; // Reads the value from the second potentiometer and maps it to a timer value | Lê o valor do segundo potenciômetro e mapeia para um valor de temporizador
  offTimer = map(analogRead(P_POT2), 0, 4095, 1, 1000); // Maps the potentiometer value to a range of 1 to 1000 milliseconds

  Serial.print("onTime: ");
  Serial.print(onTimer);  // Prints the onTimer value to the serial monitor | Imprime o valor de onTimer no monitor serial
  Serial.print(" offTimer:");
  Serial.println(offTimer); // Prints the offTimer value to the serial monitor | Imprime o valor de offTimer no monitor serial

  digitalWrite(P_LED_GREEN, HIGH);  // Turns on the green LED | Liga o LED verde
  delay(onTimer); // Waits for the onTimer duration | Aguarda a duração de onTimer
  digitalWrite(P_LED_YELLOW, HIGH); // Turns on the yellow LED | Liga o LED amarelo
  delay(onTimer); // Waits for the onTimer duration | Aguarda a duração de onTimer
  digitalWrite(P_LED_RED, HIGH);  // Turns on the red LED | Liga o LED vermelho
  delay(onTimer); // Waits for the onTimer duration | Aguarda a duração de onTimer
  digitalWrite(P_LED_BLUE, HIGH); // Turns on the blue LED | Liga o LED azul
  delay(onTimer); // Waits for the onTimer duration | Aguarda a duração de onTimer

  digitalWrite(P_LED_GREEN, LOW); // Turns off the green LED | Desliga o LED verde
  delay(offTimer);  // Waits for the offTimer duration | Aguarda a duração de offTimer
  digitalWrite(P_LED_YELLOW, LOW);  // Turns off the yellow LED | Desliga o LED amarelo
  delay(offTimer);  // Waits for the offTimer duration | Aguarda a duração de offTimer
  digitalWrite(P_LED_RED, LOW); // Turns off the red LED | Desliga o LED vermelho
  delay(offTimer);  // Waits for the offTimer duration | Aguarda a duração de offTimer
  digitalWrite(P_LED_BLUE, LOW);  // Turns off the blue LED | Desliga o LED azul
  delay(offTimer);  // Waits for the offTimer duration | Aguarda a duração de offTimer
}