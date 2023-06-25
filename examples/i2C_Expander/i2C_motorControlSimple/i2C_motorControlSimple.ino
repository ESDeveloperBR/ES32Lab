/**
 * @file i2C_motorControlSimple.ino
 * @author ES Developer
 * @brief  This code uses the PCF8574 I2C expander to control a motor through an H-bridge circuit on the ES32Lab. 
 * The purpose of this example program is to demonstrate in a didactic way how to use the motor control class from the ES32Lab library through the I2C expander. 
 * In this example, the motor is gradually accelerated until it reaches 100% speed. When the speed reaches 100%, the 'speed' variable is set to 0 and the cycle starts again.
 * | 
 * Este código utiliza o expansor I2C PCF8574 para controlar um motor através de um circuito H-bridge no ES32Lab. 
 * O objetivo deste programa de exemplo é demonstrar de forma didática como utilizar a classe de controle de motor da biblioteca ES32Lab por meio do expansor I2C. 
 * Neste exemplo, o motor é gradualmente acelerado até atingir 100% de velocidade. Quando a velocidade atinge 100%, a variável 'speed' é definida como 0 e o ciclo recomeça.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | 
 * Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca utilizada para facilitar o uso da placa ES32Lab

ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido

int speed = 0; // Initializes the variable responsible for motor speed control | Inicializa a variável responsável pelo controle de velocidade do motor

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  expander.motorBegin(1, EX4, EX5); // Initializes the H-bridge control for motor 1, using GPIO 4 and 5 of the PCF8574 expander from ES32Lab | Inicializa o controle da ponte H para o motor 1, utilizando as GPIO 4 e 5 do expansor PCF8574 da ES32Lab
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  expander.motorRotationA(1, speed);  // Activates rotation in direction A for motor 1, at the speed established by the 'speed' variable, representing the percentage value of the motor's maximum speed | Ativa a rotação no sentido A para o motor 1, na velocidade estabelecida pela variável 'speed', que representa o valor percentual da velocidade máxima do motor

  if (speed > 100){ // If the speed exceeds 100%, set it to zero | Se a velocidade ultrapassar 100%, defina-a como zero
    speed = 0;  // Set the motor speed to zero percent | Atribui o valor de zero porcento à velocidade do motor
  }else{
    speed = speed + 5;  // Increase the motor speed by 5% | Aumenta a velocidade do motor em 5%
  }
  
  delay(2000);  // Pause the LOOP for 2 seconds to demonstrate the motor speed | Pausa o LOOP por 2 segundos para demonstrar a velocidade do motor
}
