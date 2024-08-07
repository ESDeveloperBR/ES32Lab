/*
  (Português)
  Exemplo de Utilização do Método debugRead() da Classe AnalogKeyboard

  Objetivo:
  Este exemplo demonstra como utilizar o método debugRead() da classe AnalogKeyboard para obter leituras precisas dos valores analógicos
  correspondentes às teclas do teclado analógico da ES32Lab. O método debugRead() coleta múltiplas amostras dos valores analógicos,
  calcula os valores mínimos, máximos e a média, e imprime esses valores no terminal serial. Essa informação é útil para calibrar
  e ajustar a precisão da leitura das teclas.

  Aplicação:
  - O método debugRead() deve ser usado para depuração e calibração do teclado analógico.
  - Segure pressionada a tecla a ser analisada e aguarde a resposta de pelo menos 3 resultados antes de soltar a tecla.
  - Os resultados ajudarão a determinar os valores analógicos precisos das teclas, permitindo ajustes finos na configuração do teclado.

  Passos:
  1. Conecte o teclado analógico ao pino especificado na criação do objeto AnalogKeyboard.
     - A GPIO padrão do ESP32 conectada na ES32Lab para o teclado analógico é `P_KEY` (ou GPIO 33).
     - YouTube (https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s)
  2. Carregue o código no ESP32 e abra o terminal serial na velocidade de 115200 bps.
  3. Siga as instruções no terminal serial para segurar e soltar as teclas.

  Nota:
  É importante garantir que a biblioteca do display (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) esteja instalada,
  pois ela é fundamental para o funcionamento da LIB ES32Lab.

  Autor: ES Developer
  GitHub: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Criação: 08/07/2024   (mm/dd/yyyy)
*/

/*
  (English)
  Example of Using the debugRead() Method from the AnalogKeyboard Class

  Objective:
  This example demonstrates how to use the debugRead() method from the AnalogKeyboard class to obtain precise readings of the analog values
  corresponding to the keys of the ES32Lab analog keyboard. The debugRead() method collects multiple samples of the analog values,
  calculates the minimum, maximum, and average values, and prints these values to the serial terminal. This information is useful for calibrating
  and adjusting the accuracy of key readings.

  Application:
  - The debugRead() method should be used for debugging and calibrating the analog keyboard.
  - Hold down the key to be analyzed and wait for at least 3 results before releasing the key.
  - The results will help determine the precise analog values of the keys, allowing for fine adjustments in the keyboard configuration.

  Steps:
  1. Connect the analog keyboard to the specified pin when creating the AnalogKeyboard object.
     - The default ESP32 GPIO connected to the ES32Lab analog keyboard is `P_KEY` (or GPIO 33).
     - YouTube (https://www.youtube.com/watch?v=xpoNbSA8pPM&t=324s)
  2. Upload the code to the ESP32 and open the serial terminal at 115200 bps.
  3. Follow the instructions on the serial terminal to hold and release the keys.

  Note:
  It is important to ensure that the display library (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) is installed,
  as it is essential for the proper functioning of the ES32Lab LIB.

  Author: ES Developer
  GitHub: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Creation Date: 08/07/2024 (mm/dd/yyyy)
*/

#include <Arduino.h>
#include <ES32Lab.h>

AnalogKeyboard keyboard(P_KEY);

void setup() {
  Serial.begin(115200);
  Serial.println("(BR): Segure pressionada a tecla a ser analisada e aguarde a resposta de pelo menos 3 resultados antes de soltá-la.");
  Serial.println("(EN): Hold down the key to be analyzed and wait for at least 3 results before releasing it.");
  delay(3000);
}

void loop() {
    keyboard.debugRead();
    delay(1000);    // Pausa de 1 segundo antes de começar a nova leitura. | Pause of 1 second before starting a new reading.
}
