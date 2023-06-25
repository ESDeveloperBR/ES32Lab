/**
 * @file i2C_motorControlDirectionStop.ino
 * @brief This code uses the I2C PCF8574 expander to control a motor through an H-bridge circuit on the ES32Lab.
 * The purpose of this example program is to demonstrate, in a didactic way, how to use the motor control class from the ES32Lab library via the I2C expander.
 * In this example, the motor rotates in one direction for a certain period of time, then stops for another specific period of time before starting to rotate again. This cycle repeats indefinitely in a loop.
 * Attention: Do not use an external power source with the H-bridge, as it can overload the USB port of your computer.
 * |
 * Este código utiliza o expansor I2C PCF8574 para controlar um motor através de um circuito H-bridge no ES32Lab.
 * O objetivo deste programa de exemplo é demonstrar de forma didática como utilizar a classe de controle de motor da biblioteca ES32Lab por meio do expansor I2C.
 * Neste exemplo, o motor gira em uma direção por um período de tempo específico e, em seguida, para por outro período de tempo determinado antes de começar a girar novamente. Esse ciclo se repete indefinidamente em um loop.
 * Atenção: Não utilize a ponte H com uma fonte externa, isso pode sobrecarregar a porta USB do seu computador.
 *   
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed. | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 * |
 * Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas. | Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 */
#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca utilizada para facilitar o uso da placa ES32Lab

ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

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