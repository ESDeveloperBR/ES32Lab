/*
  (Português)
  Exemplo de Utilização do Método release() da Classe AnalogKeyboard

  Objetivo:
  Este exemplo demonstra como utilizar o método release() da classe AnalogKeyboard para verificar se as teclas do teclado
  analógico da ES32Lab foram soltas. O método release() verifica se uma tecla foi solta e imprime uma mensagem correspondente
  no terminal serial.

  Aplicação:
  - O método release() é útil para detectar o momento em que uma tecla é solta.
  - O exemplo monitora cinco teclas: cima, direita, baixo, esquerda e centro.
  - Quando uma tecla é solta, uma mensagem é enviada ao terminal serial.

  Passos:
  1. Conecte o teclado analógico ao pino especificado na criação do objeto AnalogKeyboard.
     - A GPIO padrão do ESP32 conectada na ES32Lab para o teclado analógico é `P_KEY` (ou GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Carregue o código no ESP32 e abra o terminal serial na velocidade de 115200 bps.
  3. Solte qualquer tecla para ver a mensagem correspondente no terminal serial.

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
  Example of Using the release() Method of the AnalogKeyboard Class

  Objective:
  This example demonstrates how to use the release() method of the AnalogKeyboard class to check if the keys of the ES32Lab
  analog keyboard have been released. The release() method checks if a key has been released and prints a corresponding message
  to the serial terminal.

  Application:
  - The release() method is useful for detecting the moment a key is released.
  - The example monitors five keys: up, right, down, left, and center.
  - When a key is released, a message is sent to the serial terminal.

  Steps:
  1. Connect the analog keyboard to the pin specified in the creation of the AnalogKeyboard object.
     - The default GPIO of the ESP32 connected to the ES32Lab for the analog keyboard is `P_KEY` (or GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Load the code onto the ESP32 and open the serial terminal at a speed of 115200 bps.
  3. Release any key to see the corresponding message on the serial terminal.

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
  // ----------- Release key -----------
  if(keyboard.release(KEY_CENTER)) { // Verifica se a tecla "Centro" foi solta | Checks if the "Center" key was released
    Serial.println("Key Center - RELEASE");
  }
  if(keyboard.release(KEY_UP)) { // Verifica se a tecla "Cima" foi solta | Checks if the "Up" key was released
    Serial.println("Key UP - RELEASE");
  }
  if(keyboard.release(KEY_RIGHT)) { // Verifica se a tecla "Direita" foi solta | Checks if the "Right" key was released
    Serial.println("Key Right - RELEASE");
  }
  if(keyboard.release(KEY_DOWN)) { // Verifica se a tecla "Baixo" foi solta | Checks if the "Down" key was released
    Serial.println("Key Down - RELEASE");
  }
  if(keyboard.release(KEY_LEFT)) { // Verifica se a tecla "Esquerda" foi solta | Checks if the "Left" key was released
    Serial.println("Key Left - RELEASE");
  }
}
