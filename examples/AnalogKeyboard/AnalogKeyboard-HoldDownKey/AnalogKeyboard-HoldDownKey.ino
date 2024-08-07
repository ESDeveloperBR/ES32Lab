/*
  (Português)
  Exemplo de Utilização do Método hold() da Classe AnalogKeyboard

  Objetivo:
  Este exemplo demonstra como utilizar o método hold() da classe AnalogKeyboard para verificar se as teclas do teclado analógico
  da ES32Lab estão sendo mantidas pressionadas. O método hold() verifica continuamente se uma tecla específica está sendo pressionada
  e imprime uma mensagem no terminal serial correspondente a cada tecla.

  Aplicação:
  - O método hold() é útil para detectar a manutenção de uma tecla pressionada durante um período de tempo.
  - O exemplo monitora cinco teclas: cima, direita, baixo, esquerda e centro.
  - Quando uma tecla é mantida pressionada, uma mensagem é enviada ao terminal serial.

  Passos:
  1. Conecte o teclado analógico ao pino especificado na criação do objeto AnalogKeyboard.
     - A GPIO padrão do ESP32 conectada na ES32Lab para o teclado analógico é `P_KEY` (ou GPIO 33).
     - YouTube (https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s)
  2. Carregue o código no ESP32 e abra o terminal serial na velocidade de 115200 bps.
  3. Pressione e mantenha pressionada qualquer tecla para ver a mensagem correspondente no terminal serial.

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
  Example of Using the hold() Method from the AnalogKeyboard Class

  Objective:
  This example demonstrates how to use the hold() method from the AnalogKeyboard class to check if the keys of the ES32Lab analog keyboard
  are being held down. The hold() method continuously checks if a specific key is being pressed and prints a message to the serial terminal
  corresponding to each key.

  Application:
  - The hold() method is useful for detecting if a key is being held down over a period of time.
  - The example monitors five keys: up, right, down, left, and center.
  - When a key is held down, a message is sent to the serial terminal.

  Steps:
  1. Connect the analog keyboard to the specified pin when creating the AnalogKeyboard object.
     - The default ESP32 GPIO connected to the ES32Lab analog keyboard is `P_KEY` (or GPIO 33).
     - YouTube (https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s)
  2. Upload the code to the ESP32 and open the serial terminal at 115200 bps.
  3. Press and hold any key to see the corresponding message on the serial terminal.

  Note:
  It is important to ensure that the display library (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) is installed,
  as it is essential for the proper functioning of the ES32Lab LIB.

  Author: ES Developer
  GitHub: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Creation Date: 08/07/2024
*/
#include <Arduino.h>
#include <ES32Lab.h>

AnalogKeyboard keyboard(P_KEY); // Criação do objeto AnalogKeyboard conectado ao pino especificado | Creation of the AnalogKeyboard object connected to the specified pin

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial | Initializes serial communication
}

void loop() {
  if(keyboard.hold(KEY_CENTER)) { // Verifica se a tecla "Centro" está sendo pressionada | Checks if the "Center" key is being held
    Serial.println("Key Center - HOLD");
  }
  if(keyboard.hold(KEY_UP)) { // Verifica se a tecla "Cima" está sendo pressionada | Checks if the "Up" key is being held
    Serial.println("Key UP - HOLD");
  }
  if(keyboard.hold(KEY_RIGHT)) { // Verifica se a tecla "Direita" está sendo pressionada | Checks if the "Right" key is being held
    Serial.println("Key RIGHT - HOLD");
  }
  if(keyboard.hold(KEY_DOWN)) { // Verifica se a tecla "Baixo" está sendo pressionada | Checks if the "Down" key is being held
    Serial.println("Key Down - HOLD");
  }
  if(keyboard.hold(KEY_LEFT)) { // Verifica se a tecla "Esquerda" está sendo pressionada | Checks if the "Left" key is being held
    Serial.println("Key Left - HOLD");
  }
}
