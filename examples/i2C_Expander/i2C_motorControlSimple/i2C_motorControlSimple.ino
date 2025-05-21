/**
 * @brief Example: Simple motor speed control using the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Controle simples de velocidade de motor utilizando o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to perform a simple speed control of a DC motor using an H-bridge connected to GPIO pins of the PCF8574 I2C expander with the ES32Lab library.
 * The code shows how to initialize the motor control by specifying which GPIOs of the expander are connected to the H-bridge inputs. In the main loop, the motor is activated in direction A, and its speed is gradually increased from 0% to 100% in steps of 5%, with a 2-second pause at each step. When the speed exceeds 100%, it resets to 0% and the cycle repeats.
 * This approach allows you to expand the number of motors controlled by your project using only two wires (SDA and SCL), freeing up microcontroller pins and enabling remote or distributed motor control. The example is ideal for understanding the basics of speed control and how to use the ES32Lab library to interface with I2C expanders for motor applications.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como realizar um controle simples de velocidade de um motor DC utilizando uma ponte H conectada aos pinos GPIO do expansor I2C PCF8574 com a biblioteca ES32Lab.
 * O código mostra como inicializar o controle do motor, especificando quais GPIOs do expansor estão conectadas às entradas da ponte H. No loop principal, o motor é ativado no sentido A e sua velocidade é aumentada gradualmente de 0% a 100% em passos de 5%, com uma pausa de 2 segundos em cada etapa. Quando a velocidade ultrapassa 100%, ela retorna para 0% e o ciclo se repete.
 * Essa abordagem permite expandir a quantidade de motores controlados no seu projeto utilizando apenas dois fios (SDA e SCL), liberando pinos do microcontrolador e possibilitando controle remoto ou distribuído dos motores. O exemplo é ideal para compreender os conceitos básicos de controle de velocidade e como utilizar a biblioteca ES32Lab para interfacear com expansores I2C em aplicações de motores.
 * O expansor deve ser configurado com o endereço I2C correto. Caso você não saiba o endereço I2C do seu dispositivo, utilize o exemplo de scanner I2C disponível em:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
 * | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
 *
 * @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca utilizada para facilitar o uso da placa ES32Lab

ES_PCF8574 expander(0x20);  // Instantiates the 'expander' object with the default address `0x20`. | Instancia o objeto 'expander' com o endereço padrão `0x20`.

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
