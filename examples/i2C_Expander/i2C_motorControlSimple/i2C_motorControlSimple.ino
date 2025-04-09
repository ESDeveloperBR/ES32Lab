/**
 * @file i2C_motorControlSimple.ino
 * @brief This example demonstrates how to use the ES32Lab I2C PCF8574 expander to control a motor 
 * through an H-bridge circuit. The motor is gradually accelerated until it reaches 100% speed. 
 * When the speed reaches 100%, the 'speed' variable is reset to 0, and the cycle starts again.
 * | Este exemplo demonstra como usar o expansor I2C PCF8574 da ES32Lab para controlar um motor através 
 * de um circuito H-bridge. O motor é gradualmente acelerado até atingir 100% de velocidade. Quando a 
 * velocidade atinge 100%, a variável 'speed' é redefinida para 0, e o ciclo recomeça.
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
 * @note To correctly configure the jumpers for the H-bridge connection, watch the video tutorial at: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * | Nota: Para configurar corretamente os jumpers para a conexão da ponte-H, assista ao tutorial em vídeo em: 
 * https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 * @see ES_PCF8574 documentation: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
 * | Documentação da classe ES_PCF8574: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_PCF8574#readme
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
