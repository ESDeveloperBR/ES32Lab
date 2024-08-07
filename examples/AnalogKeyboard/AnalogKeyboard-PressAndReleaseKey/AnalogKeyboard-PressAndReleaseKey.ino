/*
  (Português)
  Exemplo de Utilização dos Métodos press(), release() e hold() da Classe AnalogKeyboard

  Objetivo:
  Este exemplo demonstra como utilizar os métodos press(), release() e hold() da classe AnalogKeyboard para verificar se as teclas do teclado
  analógico da ES32Lab foram pressionadas, soltas ou estão sendo mantidas pressionadas. O método press() verifica se uma tecla foi pressionada,
  enquanto o método release() verifica se uma tecla foi solta, e o método hold() verifica se uma tecla está sendo mantida pressionada.
  Mensagens correspondentes são impressas no terminal serial para cada tecla monitorada.

  Aplicação:
  - O método press() é útil para detectar o momento em que uma tecla é pressionada.
  - O método release() é útil para detectar o momento em que uma tecla é solta.
  - O método hold() é útil para detectar se uma tecla está sendo mantida pressionada.
  - O exemplo monitora cinco teclas: cima, direita, baixo, esquerda e centro.
  - Quando uma tecla é pressionada, solta ou mantida pressionada, uma mensagem é enviada ao terminal serial.

  Passos:
  1. Conecte o teclado analógico ao pino especificado na criação do objeto AnalogKeyboard.
     - A GPIO padrão do ESP32 conectada na ES32Lab para o teclado analógico é `P_KEY` (ou GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Carregue o código no ESP32 e abra o terminal serial na velocidade de 115200 bps.
  3. Pressione, solte ou mantenha pressionada qualquer tecla para ver a mensagem correspondente no terminal serial.

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
  Example of Using the press(), release(), and hold() Methods of the AnalogKeyboard Class

  Objective:
  This example demonstrates how to use the press(), release(), and hold() methods of the AnalogKeyboard class to check if the keys of the ES32Lab
  analog keyboard have been pressed, released, or are being held down. The press() method checks if a key has been pressed, the release() method
  checks if a key has been released, and the hold() method checks if a key is being held down. Corresponding messages are printed to the serial
  terminal for each monitored key.

  Application:
  - The press() method is useful for detecting the moment a key is pressed.
  - The release() method is useful for detecting the moment a key is released.
  - The hold() method is useful for detecting if a key is being held down.
  - The example monitors five keys: up, right, down, left, and center.
  - When a key is pressed, released, or held down, a message is sent to the serial terminal.

  Steps:
  1. Connect the analog keyboard to the pin specified in the creation of the AnalogKeyboard object.
     - The default GPIO of the ESP32 connected to the ES32Lab for the analog keyboard is `P_KEY` (or GPIO 33).
     - YouTube: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s
  2. Load the code onto the ESP32 and open the serial terminal at a speed of 115200 bps.
  3. Press, release, or hold any key to see the corresponding message on the serial terminal.

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

  // ----------- Hold key -----------
  if(keyboard.hold(KEY_CENTER)) { // Verifica se a tecla "Centro" está sendo mantida pressionada | Checks if the "Center" key is being held
    Serial.println("Key Center - HOLD");
  }
  if(keyboard.hold(KEY_UP)) { // Verifica se a tecla "Cima" está sendo mantida pressionada | Checks if the "Up" key is being held
    Serial.println("Key UP - HOLD");
  }
  if(keyboard.hold(KEY_RIGHT)) { // Verifica se a tecla "Direita" está sendo mantida pressionada | Checks if the "Right" key is being held
    Serial.println("Key Right - HOLD");
  }
  if(keyboard.hold(KEY_DOWN)) { // Verifica se a tecla "Baixo" está sendo mantida pressionada | Checks if the "Down" key is being held
    Serial.println("Key Down - HOLD");
  }
  if(keyboard.hold(KEY_LEFT)) { // Verifica se a tecla "Esquerda" está sendo mantida pressionada | Checks if the "Left" key is being held
    Serial.println("Key Left - HOLD");
  }

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

  delay(100); // Pequeno atraso para evitar leituras excessivas | Small delay to avoid excessive readings
}
