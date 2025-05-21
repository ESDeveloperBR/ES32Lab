/**
 * @brief Example: Dual motor control using the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Controle de dois motores utilizando o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to control two independent DC motors using H-bridges connected to GPIO pins of the PCF8574 I2C expander with the ES32Lab library.
 * The code shows how to initialize the control of each motor by specifying which GPIOs of the expander are connected to the H-bridge inputs for each motor. In the setup, motor 1 is configured to use GPIOs EX4 and EX5, and motor 2 uses GPIOs EX6 and EX7. The example then activates rotation in direction A for motor 1 at 10% speed and rotation in direction B for motor 2 at 40% speed.
 * This approach allows you to expand the number of motors controlled by your project using only two wires (SDA and SCL), freeing up microcontroller pins and enabling remote or distributed motor control. You can easily adapt the code to control more motors or change the speed and direction as needed.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como controlar dois motores DC de forma independente utilizando pontes H conectadas aos pinos GPIO do expansor I2C PCF8574 com a biblioteca ES32Lab.
 * O código mostra como inicializar o controle de cada motor, especificando quais GPIOs do expansor estão conectadas às entradas da ponte H de cada motor. No setup, o motor 1 é configurado para usar as GPIOs EX4 e EX5, e o motor 2 utiliza as GPIOs EX6 e EX7. O exemplo então ativa a rotação no sentido A para o motor 1 a 10% da velocidade e a rotação no sentido B para o motor 2 a 40% da velocidade máxima.
 * Essa abordagem permite expandir a quantidade de motores controlados no seu projeto utilizando apenas dois fios (SDA e SCL), liberando pinos do microcontrolador e possibilitando controle remoto ou distribuído dos motores. Você pode facilmente adaptar o código para controlar mais motores ou alterar a velocidade e o sentido conforme necessário.
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
  expander.motorBegin(2, EX6, EX7); // Initializes the H-bridge control for motor 1, using GPIO 6 and 7 of the PCF8574 expander from ES32Lab | Inicializa o controle da ponte H para o motor 1, utilizando as GPIO 6 e 7 do expansor PCF8574 da ES32Lab


  expander.motorRotationA(1, 10);   // Activates rotation in direction A for motor 1, at a speed of 10% of maximum speed | Ativa a rotação no sentido A para o motor 1, na velocidade estabelecida em 10% da velocidade máxima
  expander.motorRotationB(2, 40);   // Activates rotation in direction B for motor 2, at a speed of 40% of maximum speed | Ativa a rotação no sentido B para o motor 2, na velocidade estabelecida em 40% da velocidade máxima
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {

}