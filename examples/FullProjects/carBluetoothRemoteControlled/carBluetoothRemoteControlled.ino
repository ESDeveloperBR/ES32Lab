/**
 * @file carBluetoothRemoteControlled.ino
 * @brief This is an example of using ES32Lab to create a Bluetooth-controlled car using a smartphone. In this project, 
 * all motor control commands and accessory functions such as horn and lights are not manually implemented in the program 
 * source code. It is recommended to use the 'Bluetooth RC Car' app as a remote control for this project. The app can be 
 * downloaded from the following link: https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * It is important to note that the ES32Lab programming library has a predefined method that replaces this example code 
 * with just a few lines of programming, resulting in a simpler and more concise code. You can find an example of this 
 * code in the file 'carBluetoothRemoteControlled_simplified.ino'.
  * | Este é um exemplo de utilização da ES32Lab para criar um carro controlado por Bluetooth utilizando um smartphone. 
 * Neste projeto, todos os comandos de controle dos motores e acessórios, como buzina e luzes, não são implementados 
 * manualmente no código-fonte do programa. Recomenda-se o uso do aplicativo 'Bluetooth RC Car' como controle remoto 
 * para esse projeto. O aplicativo pode ser baixado no seguinte link: https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * É importante ressaltar que a biblioteca de programação da ES32Lab possui um método pré-definido que substitui esse
 * código de exemplo por apenas algumas linhas de programação, resultando em um código mais simples e conciso. Você 
 * pode encontrar um exemplo desse código no arquivo ‘carBluetoothRemoteControlled_simplified.ino’.
 * @warning Make sure you have the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) and its dependency TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) installed.
 * | Certifique-se de ter a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) e sua dependência TFT_eSPI_ES32Lab (https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) instaladas.
 */

#include <Arduino.h>
#include <ES32Lab.h>
#include <BluetoothSerial.h>
  
#define SPEED_DELAY 40  // Value in percentage over the nominal motor speed. It generates a delay for one of the motors to smoothly turn during movement. | Valor percentual sobre a velocidade nominal do motor. Tem como finalidade gerar um atraso de um dos motores para curva em movimento suave.
#define FORWARD 'F'     // Move forward. | Movimento para frente.
#define BACK 'B'        // Move backward. | Movimento para trás.
#define LEFT 'L'        // Move to the left. | Movimento para a esquerda.
#define RIGHT 'R'       // Move to the right. | Movimento para a direita.
#define STOP 'S'        // Stop the motors. | Parar os motores.
#define FORWARD_LEFT 'G'    // Move forward and to the left. | Movimento para frente e esquerda.
#define FORWARD_RIGHT 'I'   // Move forward and to the right. | Movimento para frente e direita.
#define BACK_LEFT 'H'   // Move backward and to the left. | Movimento para trás e esquerda.
#define BACK_RIGHT 'J'  // Move backward and to the right. | Movimento para trás e direita.
#define FRONT_LIGHTS_ON 'W'  // Turn on the front lights. | Ligar a luz dianteira.
#define FRONT_LIGHTS_OFF 'w' // Turn off the front lights. | Desligar a luz dianteira.
#define BACK_LIGHTS_ON 'U'   // Turn on the back lights. | Ligar a luz traseira.
#define BACK_LIGHTS_OFF 'u'  // Turn off the back lights. | Desligar a luz traseira.
#define HORN_ON 'V'     // Turn on the horn. | Ligar a buzina.
#define HORN_OFF 'v'    // Turn off the horn. | Desligar a buzina.
#define EXTRA_ON 'X'    // Activate extra command. | Ligar comando extra.
#define EXTRA_OFF 'x'   // Deactivate extra command. | Desligar comando extra.

#define PIN_FRONT_LIGHTS EX0  // Pin from the I2C GPIO expander for the front light circuit. | Pino da expansão de GPIOs i2C com o circuito de luz dianteira.
#define PIN_BACK_LIGHTS  EX1  // Pin from the I2C GPIO expander for the back light circuit. | Pino da expansão de GPIOs i2C com o circuito de luz traseira.

BluetoothSerial SerialBT;   // Instantiate a BluetoothSerial object. | Instanciar um objeto BluetoothSerial.
ES_PCF8574 expander(0x38);  // Instantiate an object to manage the expander. | Instanciar um objeto para gerenciar o expansor.
ES_Buzzer buzzer(P_BUZZER); // Instantiate an object for controlling the buzzer. | Instanciar um objeto para controle do "buzzer".

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
void setup() {
  Serial.begin(115200);       // Initialize the serial terminal. | Inicializa o terminal serial.
  SerialBT.begin("ES32Lab");  // Initialize Bluetooth with the name "ES32Lab" to be discoverable by other devices. | Inicializa o bluetooth com o nome "ES32Lab" para ser encontrado por outros dispositivos.

  expander.motorBegin(1, EX4, EX5); // Initialize motor 1, using GPIOs 'EX4' and 'EX5' of the expander. | Inicializar o motor 1, utilizando as GPIOs 'EX4' e 'EX5' do expansor.
  expander.motorBegin(2, EX6, EX7); // Initialize motor 2, using GPIOs 'EX6' and 'EX7' of the expander. | Inicializar o motor 2, utilizando as GPIOs 'EX6' e 'EX7' do expansor.
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
void loop() {
  static int speed = 20; // Initial speed of the motors. | Velocidade inicial dos motores.

  static char btRead; // Variable to receive commands coming from Bluetooth. | Variável que irá receber os comandos que virão do bluetooth.

  if (SerialBT.available()) { // Check if there is information coming from Bluetooth. | Verifica se existem informações vindas do Bluetooth.
    btRead = SerialBT.read(); // Read a character coming from Bluetooth and save it to the variable 'btRead'. | Faz a leitura de um caractere vindo do Bluetooth e salva na variável 'btRead'.
    Serial.write(btRead);     // Print the 'btRead' variable to the Serial terminal. | Imprime a variável 'btRead' no terminal Serial.

    switch (btRead) {
      case FORWARD: // Moves all motors forward. | Aciona todos os motores para frente.
        expander.motorRotationA(1, speed);
        expander.motorRotationA(2, speed);
      break;

      case BACK:  // Moves all motors backward. | Aciona todos os motores para trás.
        expander.motorRotationB(1, speed);
        expander.motorRotationB(2, speed);
      break;

      case LEFT:  // Turns left. | Vira para a esquerda.
        expander.motorRotationB(1, speed);
        expander.motorRotationA(2, speed);   
      break;

      case RIGHT: // Turns right. | Vira para a direita.
        expander.motorRotationA(1, speed);
        expander.motorRotationB(2, speed);
      break;

      case FORWARD_LEFT: // Moves forward while slightly turning left, according to the percentage value adjusted in 'SPEED_DELAY'. | Vai para frente virando levemente para a esquerda, conforme o valor em percentual ajustado em 'SPEED_DELAY'.
        expander.motorRotationA(1, speed * (SPEED_DELAY / 100.0));  // Delays the motor according to the percentage value set in 'SPEED_DELAY'. | Atrasa o motor conforme o valor percentual estabelecido em 'SPEED_DELAY'.
        expander.motorRotationA(2, speed);
      break;

      case FORWARD_RIGHT: // Moves forward while slightly turning right, according to the percentage value adjusted in 'SPEED_DELAY'. | Vai para frente virando levemente para a direita, conforme o valor em percentual ajustado em 'SPEED_DELAY'.
        expander.motorRotationA(1, speed);
        expander.motorRotationA(2, speed * (SPEED_DELAY / 100.0));  // Delays the motor according to the percentage value set in 'SPEED_DELAY'. | Atrasa o motor conforme o valor percentual estabelecido em 'SPEED_DELAY'.
      break;

      case BACK_LEFT: //  Moves backward while slightly turning left, according to the percentage value adjusted in 'SPEED_DELAY'. | Vai para trás virando levemente para a esquerda, conforme o valor em percentual ajustado em 'SPEED_DELAY'.
        expander.motorRotationB(1, speed * (SPEED_DELAY / 100.0));  // Delays the motor according to the percentage value set in 'SPEED_DELAY'. | Atrasa o motor conforme o valor percentual estabelecido em 'SPEED_DELAY'.
        expander.motorRotationB(2, speed);
      break;

      case BACK_RIGHT: // Moves backward while slightly turning right, according to the percentage value adjusted in 'SPEED_DELAY'. | Vai para trás virando levemente para a direita, conforme o valor em percentual ajustado em 'SPEED_DELAY'.
        expander.motorRotationB(1, speed);
        expander.motorRotationB(2, speed * (SPEED_DELAY / 100.0));  // Delays the motor according to the percentage value set in 'SPEED_DELAY'. | Atrasa o motor conforme o valor percentual estabelecido em 'SPEED_DELAY'.
      break;

      case FRONT_LIGHTS_ON: // Turns on the front lights. | Liga a luz dianteira.
        expander.digitalWrite(PIN_FRONT_LIGHTS, HIGH);
      break;

      case FRONT_LIGHTS_OFF: // Turns off the front lights. | Apaga a luz dianteira.
        expander.digitalWrite(PIN_FRONT_LIGHTS, LOW);
      break;

      case BACK_LIGHTS_ON: // Turns on the back lights. | Liga a luz traseira.
        expander.digitalWrite(PIN_BACK_LIGHTS, HIGH);
      break;

      case BACK_LIGHTS_OFF: // Turns off the back lights. | Apaga a luz traseira.
        expander.digitalWrite(PIN_BACK_LIGHTS, LOW);
      break;

      case HORN_ON:   // Activates the horn. | Aciona a buzina.
        buzzer.sound(NOTE_C4, 500);
        buzzer.end(0);
      break;

      case HORN_OFF:  // Deactivates the horn. But in this case, the horn will sound again. | Desliga a buzina. Mas nesse caso a buzina tocará novamente.
        buzzer.sound(NOTE_C4, 500);
        buzzer.end(0);      
      break;

      case EXTRA_ON:  // Activates the hazard lights. | Aciona o pisca alerta.
        expander.pwmWrite(PIN_FRONT_LIGHTS, 50, 1);  // Activates PWM pulse on pin 'PIN_FRONT_LIGHTS' with 50% duty at 1 Hz frequency. | Aciona o pulso PWM ao pino 'PIN_FRONT_LIGHTS' com o Duty em 50% a 1 Hz de frequência.
        expander.pwmWrite(PIN_BACK_LIGHTS, 50, 1);   // Activates PWM pulse on pin 'PIN_BACK_LIGHTS' with 50% duty at 1 Hz frequency. | Aciona o pulso PWM ao pino 'PIN_BACK_LIGHTS' com o Duty em 50% a 1 Hz de frequência.
      break;

      case EXTRA_OFF: // Deactivates the hazard lights. | Desliga o pisca alerta.
        expander.pwmWrite(PIN_FRONT_LIGHTS, 50, 0);  // Deactivates the PWM pulse on pin 'PIN_FRONT_LIGHTS'. | Desativa o pulso PWM do pino 'PIN_FRONT_LIGHTS'.
        expander.pwmWrite(PIN_BACK_LIGHTS, 50, 0);   // Deactivates the PWM pulse on pin 'PIN_BACK_LIGHTS'. | Desativa o pulso PWM do pino 'PIN_BACK_LIGHTS'.
      break;

      case STOP:  // Para os motores.
        expander.motorStop(1);  // Stops motor 1. | Para o motor 1.
        expander.motorStop(2);  // Stops motor 2. | Para o motor 2.
      break;

      case '0' ... '9': // Adjusts the speed of the motors. | Ajuste da velocidade nos motores.
        speed = btRead - '0';   // Converts a CHAR value to INTEGER. | Conversão de um valor CHAR para INTEGER.
        speed = speed * 10;     // Converts an integer value to the percentage of motor power. | Converte um valor inteiro para o percentual da potência dos motores.
      break;
    }
  }
}
