/**
 * @file ES_Buzzer_DJPitchSimulation.ino
 * @brief Simulates DJ pitch control, where both pitch and speed are dynamically adjusted, mimicking a vinyl record's rotation changes.
 * | Simula o controle de pitch de DJs, onde tanto o pitch quanto a velocidade são ajustados dinamicamente, imitando as mudanças de rotação de um disco de vinil.
 * 
 * This example demonstrates the use of the `setPitchAndSpeed()` method from the ES_Buzzer class to create a realistic DJ-like pitch and speed effect.
 * Two onboard potentiometers are used to control the sound volume and simulate the pitch-speed relationship in real time.
 * | Este exemplo demonstra o uso do método `setPitchAndSpeed()` da classe ES_Buzzer para criar um efeito realista de pitch e velocidade semelhante ao de DJs.
 * Dois potenciômetros integrados são usados para controlar o volume do som e simular a relação entre pitch e velocidade em tempo real.
 * 
 * A small melody is included for testing purposes only.
 * | Uma pequena melodia é incluída apenas para fins de teste.
 *
 * @warning Make sure the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * 
 * @attention Ensure that the buzzer of the ES32Lab is activated via the green jumper "BUZZER/P25" and the potentiometers are activated via the blue jumpers. If this is not done, the buzzer and potentiometer controls will not function.
 * | Atenção: Lembre-se de ativar o buzzer da ES32Lab através do jumper verde "BUZZER/P25" e os potenciômetros através dos Jumpers Azuis. Caso isso não esteja feito, o buzzer e os controles pelos potenciômetros não funcionarão.
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 *
 * @see ES_Buzzer documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
 * | Documentação da classe ES_Buzzer: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme
*/

#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER); // Create an instance of the 'ES_Buzzer' class using the 'P_BUZZER' pin. | Cria uma instância da classe 'ES_Buzzer' utilizando o pino 'P_BUZZER'.

int pot1 = 0;  // Create a variable to store the potentiometer value. | Cria uma variável para armazenar o valor do potenciômetro.
int pot2 = 0;  // Create a variable to store the potentiometer value. | Cria uma variável para armazenar o valor do potenciômetro.

// <<<<<<<<<< setup >>>>>>>>>>
void setup() {
  Serial.begin(115200); // Initialize the Serial Monitor. | Inicializa o Monitor Serial.
  buzzer.begin();       // Initialize the buzzer instance. | Inicializa a instância do buzzer.

  pinMode(P_POT1, INPUT); // Set the 'P_POT1' pin as input. | Define o pino 'P_POT1' como entrada.
  pinMode(P_POT2, INPUT); // Set the 'P_POT2' pin as input. | Define o pino 'P_POT2' como entrada.
}

// <<<<<<<<<< loop >>>>>>>>>>
void loop() {
  pot1 = map(analogRead(P_POT1), 0, 4095, 0, 100);  // Read the potentiometer value and map it to a range from 0 to 100. | Lê o valor do potenciômetro e mapeia para uma faixa de 0 a 100.
  pot2 = map(analogRead(P_POT2), 0, 4095, 0, 200);  // Read the potentiometer value and map it to a range from 0 to 200. | Lê o valor do potenciômetro e mapeia para uma faixa de 0 a 200.

  Serial.printf("Pot1: %d\n", pot1); // Print the 'pot1' variable to the Serial Monitor. | Imprime a variável 'pot1' no Monitor Serial.
  Serial.printf("Pot2: %d\n", pot2); // Print the 'pot2' variable to the Serial Monitor. | Imprime a variável 'pot2' no Monitor Serial.

  buzzer.setVolume(pot1);        // Set the volume to the 'pot1' variable. | Define o volume pela a variável 'pot1'.
  Serial.print("Volume GET: ");  // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.
  Serial.println(buzzer.getVolume()); // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.

  buzzer.setPitchAndSpeed(pot2);// Set the pitch and speed equivalently by the 'pot2' variable. | Define o pitch e a velocidade de forma equivalente pela variável 'pot2'.
  Serial.print("Pitch GET: ");  // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.
  Serial.println(buzzer.getPitch());  // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.
  Serial.print("Speed GET: ");  // Print the current speed to the Serial Monitor. | Imprime a velocidade atual no Monitor Serial.
  Serial.println(buzzer.getSpeed());  // Print the current speed to the Serial Monitor. | Imprime a velocidade atual no Monitor Serial.

  Serial.println("--------------------"); // Print a separator to the Serial Monitor. | Imprime um separador no Monitor Serial.

  // Play "Nintendo game Super Mario World" melody on the buzzer. | Reproduz a melodia do "jogo da Nintendo Super Mario World" no buzzer.
  buzzer.sound(NOTE_E7, 136);  // Play the note E7 for 136 milliseconds. | Reproduz a nota E7 por 136 milissegundos.
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);        // Pause for 136 milliseconds (silent). | Pausa por 136 milissegundos (silêncio).
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_C7, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_G7, 136);
  buzzer.sound(0, 408);        // Pause for 408 milliseconds (silent). | Pausa por 408 milissegundos (silêncio).
  buzzer.sound(NOTE_G6, 136);

  buzzer.end(500);  // Pause for 500ms before repeating. | Pausa por 500ms antes de repetir.
}