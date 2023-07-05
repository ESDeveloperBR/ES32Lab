/**
 * @file i2C_pwm.ino
 * @author ES Developer
 * @brief This example code demonstrates how to activate the PWM pulse simulator on the ES32Lab's I2C expander. In this case, the white LED on the ES32Lab
 * blinks twice per second intermittently, while the orange LED on the ES32Lab blinks four times per second intermittently.
 * | Esse código exemplo mostra como ativar o simulador de pulso PWM no expansor I2C da ES32Lab. Nesse caso, o LED branco da ES32Lab pisca duas vezes 
 * por segundo de forma intermitente, enquanto o LED laranja da ES32Lab pisca quatro vezes por segundo de forma intermitente.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed. 
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido.

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