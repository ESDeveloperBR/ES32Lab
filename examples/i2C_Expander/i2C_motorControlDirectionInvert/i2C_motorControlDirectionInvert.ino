/**
 * @brief Example: Motor direction inversion using the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Inversão de sentido do motor utilizando o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to invert the rotation direction of a DC motor controlled by an H-bridge connected to GPIO pins of the PCF8574 I2C expander using the ES32Lab library.
 * The code shows how to initialize the motor control by specifying which GPIOs of the expander are connected to the H-bridge inputs. In the main loop, the motor is first rotated in direction A at 50% speed for 2 seconds. Then, the invertMotorCommands() method is called, which inverts the logic of the motorRotationA() and motorRotationB() methods, effectively swapping the rotation directions for subsequent commands.
 * This feature is especially useful when the motor wires are not connected in the expected order, allowing you to correct the rotation direction via software without rewiring the hardware.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como inverter o sentido de rotação de um motor DC controlado por uma ponte H conectada aos pinos GPIO do expansor I2C PCF8574 utilizando a biblioteca ES32Lab.
 * O código mostra como inicializar o controle do motor, especificando quais GPIOs do expansor estão conectadas às entradas da ponte H. No loop principal, o motor gira inicialmente no sentido A a 50% da velocidade por 2 segundos. Em seguida, o método invertMotorCommands() é chamado, invertendo a lógica dos métodos motorRotationA() e motorRotationB(), trocando efetivamente os sentidos de rotação para os próximos comandos.
 * Esse recurso é especialmente útil quando os fios do motor não foram conectados na ordem esperada, permitindo corrigir o sentido de rotação via software, sem necessidade de alterar a fiação.
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
  expander.invertMotorCommands(1);  // Inverts the direction of the 'motorRotationA' and 'motorRotationB' methods. Ideal for when the motor wires are not connected in the order in which the program was written. | Inverte a direção dos métodos 'motorRotationA' e 'motorRotationB'. Ideal para quando os fios do motor não foram ligados na ordem na qual o programa foi escrito.
}