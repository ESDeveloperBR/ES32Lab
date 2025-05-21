/**
 * @brief Example: Simulating PWM on I2C GPIO expander (PCF8574) outputs with ES32Lab
 * | Exemplo: Simulação de PWM nas saídas do expansor de GPIO I2C (PCF8574) com a ES32Lab
 *
 * This example demonstrates how to generate PWM (Pulse Width Modulation) signals on the output pins of the PCF8574 I2C expander using the ES32Lab library.
 * The code shows how to enable the PWM simulator for the expander using the pwmBegin() method (or alternatively begin(true)), and how to configure PWM on specific pins with the pwmWrite() method.
 * In this example, pin EX0 is set to output a PWM signal with a 50% duty cycle at 2 Hz, and pin EX1 is set to output a PWM signal with a 50% duty cycle at 4 Hz. This allows you to control devices such as LEDs, buzzers, or other actuators that benefit from PWM, even though the PCF8574 does not natively support hardware PWM.
 * The PWM simulation is managed by the ES32Lab library, making it possible to expand the number of PWM outputs in your project using only two wires (SDA and SCL), freeing up microcontroller pins and enabling distributed or remote control.
 * The expander must be configured with the correct I2C address. If you do not know the I2C address of your device, use the I2C scanner example available at:
 * https://github.com/ESDeveloperBR/ES32Lab/blob/main/examples/i2C_Expander/i2C_scanI2C/i2C_scanI2C.ino
 *
 * | Este exemplo demonstra como gerar sinais PWM (Pulse Width Modulation) nas saídas do expansor I2C PCF8574 utilizando a biblioteca ES32Lab.
 * O código mostra como habilitar o simulador de PWM do expansor usando o método pwmBegin() (ou alternativamente begin(true)), e como configurar o PWM em pinos específicos com o método pwmWrite().
 * Neste exemplo, o pino EX0 é configurado para gerar um sinal PWM com ciclo de trabalho de 50% e frequência de 2 Hz, e o pino EX1 para gerar um sinal PWM com ciclo de trabalho de 50% e frequência de 4 Hz. Isso permite controlar dispositivos como LEDs, buzzers ou outros atuadores que se beneficiam de PWM, mesmo que o PCF8574 não suporte PWM por hardware.
 * A simulação de PWM é gerenciada pela biblioteca ES32Lab, tornando possível expandir a quantidade de saídas PWM do seu projeto utilizando apenas dois fios (SDA e SCL), liberando pinos do microcontrolador e permitindo controle distribuído ou remoto.
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
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x20);  // Instantiates the 'expander' object with the default address `0x20`. | Instancia o objeto 'expander' com o endereço padrão `0x20`.

// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);

  expander.pwmBegin();  // Starts the I2C expander by enabling the PWM simulator. An alternative to enable the PWM simulator of the I2C expander is to use the command 'begin(true)'. | Inicia o expansor I2C ativando o simulador PWM. Uma alternativa para ativar o simulador PWM do expansor I2C é utilizando o comando 'begin(true)'.
  expander.pwmWrite(EX0, 50, 2);  // Enables the PWM simulator on pin EX0 with a duty cycle of 50% and a frequency of 2 hertz. | Ativa o simulador PWM no pino EX0, com um ciclo de trabalho de 50% e frequência de 2 hertz.
  expander.pwmWrite(EX1, 50, 4);  // Enables the PWM simulator on pin EX1 with a duty cycle of 50% and a frequency of 4 hertz. | Ativa o simulador PWM no pino EX1, com um ciclo de trabalho de 50% e frequência de 4 hertz.
}

// <<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>
void loop() {

}