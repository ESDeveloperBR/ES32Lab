/**
 * @file i2C_pwm.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to simulate PWM pulses. 
 * The white LED blinks twice per second intermittently, while the orange LED blinks four times per second.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para simular pulsos PWM. O LED 
 * branco pisca duas vezes por segundo de forma intermitente, enquanto o LED laranja pisca quatro vezes 
 * por segundo.
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
 * @note To activate the white and orange LEDs, ensure the jumpers are correctly configured. 
 * Watch the video tutorial at: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * | Nota: Para ativar os LEDs branco e laranja, certifique-se de que os jumpers estão configurados 
 * corretamente. Assista ao tutorial em vídeo em: https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES_PCF8574 documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação da classe ES_PCF8574: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
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