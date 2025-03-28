/**
 * @file ES_Buzzer_controlPitchSpeed.ino
 * @brief Demonstrates how to dynamically control the buzzer pitch and the melody playback speed using the potentiometers of the ES32Lab.
 * | Demonstra como controlar dinamicamente o pitch e a velocidade de reprodução da melodia utilizando os potenciômetros da ES32Lab.
 * 
 * This example showcases the usage of `setPitch()` and `setSpeed()` methods from the ES_Buzzer class.
 * Two onboard potentiometers are used to adjust the sound pitch and playback speed in real time.
 * | Este exemplo demonstra a utilização dos métodos `setPitch()` e `setSpeed()` da classe ES_Buzzer.
 * Os dois potenciômetros integrados da ES32Lab são usados para ajustar o pitch e a velocidade de reprodução da melodia em tempo real.
 * 
 * A small melody is used for testing purposes only.
 * | Uma pequena melodia é usada apenas para fins de teste.
 * 
 * @attention Ensure that the buzzer of the ES32Lab is activated via the green jumper "BUZZER/P25" and the potentiometers are activated via the blue jumpers. If this is not done, the buzzer and potentiometer controls will not function.
 * | Atenção: Lembre-se de ativar o buzzer da ES32Lab através do jumper verde "BUZZER/P25" e os potenciômetros através dos Jumpers Azuis. Caso isso não esteja feito, o buzzer e os controles pelos potenciômetros não funcionarão.
 *
 * @warning Make sure the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
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
   buzzer.setVolume(50); // Set the volume to the 'volume' variable. | Define o volume para a variável 'volume'.
  
   pinMode(P_POT1, INPUT); // Set the 'P_POT1' pin as input. | Define o pino 'P_POT1' como entrada.
   pinMode(P_POT2, INPUT); // Set the 'P_POT2' pin as input. | Define o pino 'P_POT2' como entrada.
 }
   
 // <<<<<<<<<< loop >>>>>>>>>>
 void loop() {
   pot1 = map(analogRead(P_POT1), 0, 4095, 0, 200);  // Read the potentiometer value and map it to a range from 0 to 200. | Lê o valor do potenciômetro e mapeia para uma faixa de 0 a 200.
   pot2 = map(analogRead(P_POT2), 0, 4095, 0, 200);  // Read the potentiometer value and map it to a range from 0 to 200. | Lê o valor do potenciômetro e mapeia para uma faixa de 0 a 200.
  
   Serial.printf("Pot1: %d\n", pot1); // Print the 'pot1' variable to the Serial Monitor. | Imprime a variável 'pot1' no Monitor Serial.
   Serial.printf("Pot2: %d\n", pot2); // Print the 'pot2' variable to the Serial Monitor. | Imprime a variável 'pot2' no Monitor Serial. 
     
   buzzer.setPitch(pot1);       // Adjust the pitch dynamically based on the value of 'pot1'. | Ajusta o pitch dinamicamente com base no valor de 'pot1'.
   Serial.print("Pitch GET: "); // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.
   Serial.println(buzzer.getPitch()); // Print the current pitch to the Serial Monitor. | Imprime o pitch atual no Monitor Serial.
    
   buzzer.setSpeed(pot2);        // Adjust the speed dynamically based on the value of 'pot2'. | Ajusta a velocidade dinamicamente com base no valor de 'pot2'.
   Serial.print("Speed GET: ");  // Print the current speed to the Serial Monitor. | Imprime a velocidade atual no Monitor Serial.
   Serial.println(buzzer.getSpeed()); // Print the current speed to the Serial Monitor. | Imprime a velocidade atual no Monitor Serial.
  
   Serial.println("--------------------"); // Print a separator to the Serial Monitor. | Imprime um separador no Monitor Serial.
  
   // Play "Take On Me" melody on the buzzer. | Reproduz a melodia de "Take On Me" no buzzer.
   buzzer.sound(NOTE_FS5, 214); // Play note FS5 for 214ms. | Toca a nota FS5 por 214ms.
   buzzer.sound(NOTE_FS5, 214);
   buzzer.sound(NOTE_D5, 214); // Play note D5 for 214ms. | Toca a nota D5 por 214ms.
   buzzer.sound(NOTE_B4, 214); // Play note B4 for 214ms. | Toca a nota B4 por 214ms.
   buzzer.sound(0, 214);       // Pause for 214ms. | Pausa por 214ms.
   buzzer.sound(NOTE_B4, 214);
   buzzer.sound(0, 214);
   buzzer.sound(NOTE_E5, 214); // Play note E5 for 214ms. | Toca a nota E5 por 214ms.
   buzzer.sound(0, 214);
   buzzer.sound(NOTE_E5, 214);
  
   buzzer.end(500);  // Pause for 500ms before repeating. | Pausa por 500ms antes de repetir.
 }