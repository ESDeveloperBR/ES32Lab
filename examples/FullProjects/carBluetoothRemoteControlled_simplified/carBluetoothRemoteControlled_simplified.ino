/**
 * @file carBluetoothRemoteControlled_simplified.ino
 * @brief This example aims to provide an easy and straightforward mechanism for motor control using two H-bridges for the locomotion 
 * of a vehicle through the differential drive method. This method follows the same principle of locomotion as a tank, where each track is driven by a separate motor,
 * allowing them to rotate at different speeds. To change direction, the tank adjusts the rotation speed of one track relative to the other. For example, if 
 * the tank wants to turn left, it reduces the speed of the right track or increases the speed of the left track, creating a rotational difference that makes the tank 
 * turn left. For motor control, Bluetooth communication will be used, and the suggested app for this experiment is "Bluetooth RC Controller." 
 * https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * | Esse exemplo tem como objetivo utilizar, de forma fácil e objetiva, um mecanismo de controle de motores usando duas pontes H para a locomoção
 * de um veículo através do método diferencial. Esse método segue o mesmo princípio de locomoção de um trator de esteira,
 * onde cada esteira é acionada por um motor separado, permitindo que elas girem em velocidades diferentes. Para mudar de direção, o trator ajusta a velocidade de
 * rotação de uma esteira em relação à outra. Por exemplo, se o trator deseja girar para a esquerda, ele reduz a velocidade da esteira direita ou aumenta a
 * velocidade da esteira esquerda, criando uma diferença de rotação que faz o trator virar para a esquerda. Para o controle dos motores, será utilizada a comunicação Bluetooth, 
 * e o aplicativo sugerido para esse experimento é o "Bluetooth RC Controller". https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * @warning For more information on the documentation of the 'ES_CarControl' class contained in the ES32Lab library, please refer to the link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 * | Para mais informações sobre a documentação da classe ‘ES_CarControl’ contida na biblioteca ES32Lab, acesse o link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 */
#include <Arduino.h>
#include <BluetoothSerial.h>  // Library for Bluetooth utilization. | Biblioteca para a utilização do Bluetooth.
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab

ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido.
ES_Buzzer buzzer(P_BUZZER); // Instantiates the 'buzzer' object and its respective GPIO to be used. | Instancia o objeto 'buzzer' e sua respectiva GPIO a ser utilizada.
ES_CarControl car(&expander, &buzzer);  // Instantiate the 'car' object derived from the 'ES_CarControl' class. | Instancia o objeto 'car' derivado da classe 'ES_CarControl'.

BluetoothSerial SerialBT; // Instantiate an object derived from the 'BluetoothSerial' class. | Instancia um objeto derivado da classe 'BluetoothSerial'.

// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
  Serial.begin(115200);

  SerialBT.begin("ES32Lab_Car");  // Initialize Bluetooth with the name "ES32Lab_Car" so that it can be discovered by other devices. | Inicializa o Bluetooth com o nome "ES32Lab_Car" para que possa ser encontrado por outros dispositivos.
  
  // To use the differentialDriveBegin method, which is responsible for managing differential drive in a simple and straightforward way, following the methodology used in tanks.
  // |
  // Para utilizar o método differentialDriveBegin, responsável por gerenciar o tracionamento diferencial de forma simples e objetiva, seguindo a metodologia utilizada em tratores de esteira.
  car.differentialDriveBegin();

  car.setSpeed(25);   // Sets an initial value for the vehicle. | Estabelece um valor inicial para o veículo.
  car.setSpeedDelay(20);  // Adjustment of the delay of the wheels on one side of the vehicle, allowing it to turn while moving forward or backward. | Ajuste do atrazo das rodas de um dos lados do veiculo, para que o mesmo faça curva enquanto se movimenta para frete ou para trás.

  // Inverts the direction of motor 1 commands. This command is useful when the motor wires are connected in reverse on the terminals of the H-bridge responsible
  // for its control. By using this command, the motor control logic is also inverted, ensuring correct execution of the control commands. This allows the motor 
  // to operate as expected, even with the inverted wire connection.
  // |
  // Inverte a direção dos comandos do motor 1. Esse comando é útil quando os fios do motor foram ligados invertidos nos bornes da ponte H responsável 
  // pelo seu controle. Ao utilizar esse comando, a lógica de controle do motor também é invertida, garantindo uma execução correta dos comandos de controle. Isso 
  // permite que o motor funcione de acordo com as expectativas, mesmo com a conexão invertida dos fios.

  // car.invertMotorCommands(1);
}

// <<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  car.controlCommand(SerialBT);
}
