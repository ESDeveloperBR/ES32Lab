/**
 * @brief Example: Stopping a motor with direction control using the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Parada de motor com controle de sentido utilizando o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to control the rotation direction and stop a DC motor using an H-bridge connected to GPIO pins of the PCF8574 I2C expander with the ES32Lab library.
 * The code shows how to initialize the motor control by specifying which GPIOs of the expander are connected to the H-bridge inputs. In the main loop, the motor is rotated in direction A at 50% speed for 2 seconds, then the motorStop() method is called to stop the motor for another 2 seconds. This cycle repeats continuously.
 * This approach allows you to expand the number of motors controlled by your project using only two wires (SDA and SCL), freeing up microcontroller pins and enabling remote or distributed motor control. The ability to stop the motor via software is essential for applications that require precise control, such as robotics or automation systems.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como controlar o sentido de rotação e realizar a parada de um motor DC utilizando uma ponte H conectada aos pinos GPIO do expansor I2C PCF8574 com a biblioteca ES32Lab.
 * O código mostra como inicializar o controle do motor, especificando quais GPIOs do expansor estão conectadas às entradas da ponte H. No loop principal, o motor gira no sentido A a 50% da velocidade por 2 segundos e, em seguida, o método motorStop() é chamado para parar o motor por mais 2 segundos. Esse ciclo se repete continuamente.
 * Essa abordagem permite expandir a quantidade de motores controlados no seu projeto utilizando apenas dois fios (SDA e SCL), liberando pinos do microcontrolador e possibilitando controle remoto ou distribuído dos motores. A capacidade de parar o motor via software é essencial para aplicações que exigem controle preciso, como robótica ou sistemas de automação.
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