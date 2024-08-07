/*
  (Português)
  Exemplo de Utilização do Método press() da Classe AnalogKeyboard

  Objetivo:
  Este exemplo demonstra como utilizar o método press() da classe AnalogKeyboard para verificar se as teclas do teclado
  analógico da ES32Lab foram pressionadas. O método press() verifica se uma tecla foi pressionada e imprime uma mensagem
  correspondente no terminal serial.

  Aplicação:
  - O método press() é útil para detectar o momento em que uma tecla é pressionada.
  - O exemplo monitora cinco teclas: cima, direita, baixo, esquerda e centro.
  - Quando uma tecla é pressionada, uma mensagem é enviada ao terminal serial.

  Passos:
  1. Conecte o teclado analógico ao pino especificado na criação do objeto AnalogKeyboard.
     - A GPIO padrão do ESP32 conectada na ES32Lab para o teclado analógico é `P_KEY` (ou GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Carregue o código no ESP32 e abra o terminal serial na velocidade de 115200 bps.
  3. Pressione qualquer tecla para ver a mensagem correspondente no terminal serial.

  Nota:
  É importante garantir que a biblioteca do display (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) esteja instalada,
  pois ela é fundamental para o funcionamento da LIB ES32Lab.

  Autor: ES Developer
  GitHub: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Criação: 08/07/2024
*/

/*
  (English)
  Example of Using the press() Method of the AnalogKeyboard Class

  Objective:
  This example demonstrates how to use the press() method of the AnalogKeyboard class to check if the keys of the ES32Lab
  analog keyboard have been pressed. The press() method checks if a key has been pressed and prints a corresponding message
  to the serial terminal.

  Application:
  - The press() method is useful for detecting the moment a key is pressed.
  - The example monitors five keys: up, right, down, left, and center.
  - When a key is pressed, a message is sent to the serial terminal.

  Steps:
  1. Connect the analog keyboard to the pin specified in the creation of the AnalogKeyboard object.
     - The default GPIO of the ESP32 connected to the ES32Lab for the analog keyboard is `P_KEY` (or GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Load the code onto the ESP32 and open the serial terminal at a speed of 115200 bps.
  3. Press any key to see the corresponding message on the serial terminal.

  Note:
  It is important to ensure that the display library (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) is installed,
  as it is essential for the proper functioning of the ES32Lab LIB.

  Author: ES Developer
  GitHub: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Created: 08/07/2024
*/

#include <Arduino.h>
#include <ES32Lab.h>

AnalogKeyboard keyboard(P_KEY); // Criação do objeto AnalogKeyboard conectado ao pino especificado | Creation of the AnalogKeyboard object connected to the specified pin

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial | Initializes serial communication
}

void loop() {
  // ----------- Press key -----------
  if(keyboard.press(KEY_CENTER)) { // Verifica se a tecla "Centro" foi pressionada | Checks if the "Center" key was pressed
    Serial.println("Key Center - PRESS");
  }
  if(keyboard.press(KEY_UP)) { // Verifica se a tecla "Cima" foi pressionada | Checks if the "Up" key was pressed
    Serial.println("Key UP - PRESS");
  }
  if(keyboard.press(KEY_RIGHT)) { // Verifica se a tecla "Direita" foi pressionada | Checks if the "Right" key was pressed
    Serial.println("Key Right - PRESS");
  }
  if(keyboard.press(KEY_DOWN)) { // Verifica se a tecla "Baixo" foi pressionada | Checks if the "Down" key was pressed
    Serial.println("Key Down - PRESS");
  }
  if(keyboard.press(KEY_LEFT)) { // Verifica se a tecla "Esquerda" foi pressionada | Checks if the "Left" key was pressed
    Serial.println("Key Left - PRESS");
  }
}
