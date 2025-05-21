/**
 * @brief Example: Setting and reading PWM frequency for motor control using the I2C GPIO expander (PCF8574) and ES32Lab
 * | Exemplo: Ajuste e leitura da frequência PWM para controle de motor utilizando o expansor de GPIO I2C (PCF8574) e ES32Lab
 *
 * This example demonstrates how to configure and read the PWM frequency used for controlling a DC motor via an H-bridge connected to GPIO pins of the PCF8574 I2C expander with the ES32Lab library.
 * The code shows how to initialize the motor control by specifying which GPIOs of the expander are connected to the H-bridge inputs. The setMotorFrequency() method is used to set the PWM frequency for motor 1, and getMotorFrequency() retrieves the configured frequency, which is then printed to the serial monitor. The motor is then activated in direction A at 20% of the maximum speed.
 * Adjusting the PWM frequency is important for optimizing motor performance, reducing noise, and adapting the control to different types of motors or application requirements. This feature provides greater flexibility and precision in motor control projects.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como configurar e ler a frequência PWM utilizada para controlar um motor DC via ponte H conectada aos pinos GPIO do expansor I2C PCF8574 com a biblioteca ES32Lab.
 * O código mostra como inicializar o controle do motor, especificando quais GPIOs do expansor estão conectadas às entradas da ponte H. O método setMotorFrequency() é utilizado para definir a frequência PWM do motor 1, e getMotorFrequency() recupera a frequência configurada, que é impressa no monitor serial. Em seguida, o motor é ativado no sentido A a 20% da velocidade máxima.
 * O ajuste da frequência PWM é importante para otimizar o desempenho do motor, reduzir ruídos e adaptar o controle a diferentes tipos de motores ou requisitos de aplicação. Esse recurso proporciona maior flexibilidade e precisão em projetos de controle de motores.
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