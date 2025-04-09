/**
 * @file i2C_motorControlDirectionStop.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to control a motor 
 * through an H-bridge circuit. The motor rotates in one direction for a specific period, then stops 
 * for another specific period before starting to rotate again. This cycle repeats indefinitely.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para controlar um motor através 
 * de um circuito H-bridge. O motor gira em uma direção por um período específico, depois para por outro 
 * período específico antes de começar a girar novamente. Esse ciclo se repete indefinidamente.
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) are installed.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência 
 * TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) estejam instaladas.
 * @attention If the I2C address is incorrect, the program will not work. Use the command 
 * `expander.scanI2C()` to find the correct address. For more details, refer to the example available at: 
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * | Atenção: Se o endereço I2C estiver incorreto, o programa não funcionará. Use o comando 
 * `expander.scanI2C()` para encontrar o endereço correto. Para mais detalhes, consulte o exemplo disponível 
 * em: https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 * @note To correctly configure the jumpers for the H-bridge connection, watch the video tutorial at: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * | Nota: Para configurar corretamente os jumpers para a conexão da ponte-H, assista ao tutorial em vídeo em: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES_PCF8574 documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação da classe ES_PCF8574: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca utilizada para facilitar o uso da placa ES32Lab

ES_PCF8574 expander(0x20);  // Instantiates the 'expander' object with the default address `0x20`. | Instancia o objeto 'expander' com o endereço padrão `0x20`.

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  expander.motorBegin(1, EX4, EX5); // Initializes the H-bridge control for motor 1, using GPIO 4 and 5 of the PCF8574 expander from ES32Lab | Inicializa o controle da ponte H para o motor 1, utilizando as GPIO 4 e 5 do expansor PCF8574 da ES32Lab
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  expander.motorRotationA(1, 50);  // Activates rotation in direction A for motor 1, at a speed of 50% of maximum speed | Ativa a rotação no sentido A para o motor 1, na velocidade estabelecida em 50% da velocidade máxima
  delay(2000);  // Pauses the loop for 2 seconds | Pausa o LOOP por 2 segundos

  expander.motorStop(1);  // Give a stop command to the motor. | Dá um comando de parada no motor.
  delay(2000);  // Pauses the loop for 2 seconds | Pausa o LOOP por 2 segundos
}