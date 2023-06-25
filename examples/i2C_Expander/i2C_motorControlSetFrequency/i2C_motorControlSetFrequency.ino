/**
 * @file i2C_motorControlSetFrequency.ino
 * @brief This code uses the I2C PCF8574 expander to control a motor through an H-bridge circuit on the ES32Lab.
 * The purpose of this example program is to demonstrate, in a didactic way, how to use the motor control class from the ES32Lab library via the I2C expander.
 * In this example, the working frequency of the PWM pulse for the motor will be adjusted according to the designer's preferences, and the new value in hertz will be displayed on the serial monitor.
 * Attention: Do not use an external power source with the H-bridge, as it can overload the USB port of your computer.
 * |
 * Este código utiliza o expansor I2C PCF8574 para controlar um motor através de um circuito H-bridge no ES32Lab.
 * O objetivo deste programa de exemplo é demonstrar de forma didática como utilizar a classe de controle de motor da biblioteca ES32Lab por meio do expansor I2C.
 * Neste exemplo, a frequência de trabalho do pulso PWM do motor será alterada de acordo com as preferências do projetista, e o novo valor em hertz será exibido no monitor serial.
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
  Serial.begin(115200); // Initializes serial communication with a data transmission rate of 115200 bits per second. | Inicializa a comunicação serial com uma taxa de transmissão de dados de 115200 bits por segundo. 

  expander.motorBegin(1, EX4, EX5); // Initializes the H-bridge control for motor 1, using GPIO 4 and 5 of the PCF8574 expander from ES32Lab | Inicializa o controle da ponte H para o motor 1, utilizando as GPIO 4 e 5 do expansor PCF8574 da ES32Lab

  expander.motorSetFrequency(1, 50);  // Sets motor 1 to operate with a PWM pulse of 50Hz. | Ajusta o motor 1 para operar com um pulso PWM de 50Hz.

  int frequency = expander.motorGetFrequency(1);  // Returns the value of the frequency in hertz associated with motor 1. | Retorna o valor da frequência em hertz associada ao motor 1.
  Serial.print("Frequency: ");
  Serial.println(frequency);

  expander.motorRotationA(1, 20);   // Activates rotation in direction A for motor 1, at a speed of 20% of maximum speed | Ativa a rotação no sentido A para o motor 1, na velocidade estabelecida em 20% da velocidade máxima
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {

}