/**
 * @file i2C_motorControlSetFrequency.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to control a motor 
 * through an H-bridge circuit. The program adjusts the PWM pulse frequency for the motor according 
 * to the designer's preferences and displays the new value in hertz on the serial monitor.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para controlar um motor através 
 * de um circuito H-bridge. O programa ajusta a frequência do pulso PWM do motor de acordo com as 
 * preferências do projetista e exibe o novo valor em hertz no monitor serial.
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
  Serial.begin(115200); // Initializes serial communication with a data transmission rate of 115200 bits per second. | Inicializa a comunicação serial com uma taxa de transmissão de dados de 115200 bits por segundo. 

  expander.motorBegin(1, EX4, EX5); // Initializes the H-bridge control for motor 1, using GPIO 4 and 5 of the PCF8574 expander from ES32Lab | Inicializa o controle da ponte H para o motor 1, utilizando as GPIO 4 e 5 do expansor PCF8574 da ES32Lab

  expander.setMotorFrequency(1, 50);  // Sets motor 1 to operate with a PWM pulse of 50Hz. | Ajusta o motor 1 para operar com um pulso PWM de 50Hz.

  int frequency = expander.getMotorFrequency(1);  // Returns the value of the frequency in hertz associated with motor 1. | Retorna o valor da frequência em hertz associada ao motor 1.
  Serial.print("Frequency: ");
  Serial.println(frequency);

  expander.motorRotationA(1, 20);   // Activates rotation in direction A for motor 1, at a speed of 20% of maximum speed | Ativa a rotação no sentido A para o motor 1, na velocidade estabelecida em 20% da velocidade máxima
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {

}