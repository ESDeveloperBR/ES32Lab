/**
 * @brief 
 * In this practical example, we utilize the "ES_CarControl" class to create a concise and effective programming code for controlling a "FRONTAL" steering vehicle.
 * This way, the vehicle adjusts the front wheel direction as needed. This steering method is identical to what's used in typical street vehicles.
 * For controlling the motors, we'll employ the ES32Lab's H-bridge, along with Bluetooth communication between the smartphone and ES32Lab.
 * The recommended app for this experiment is the "Bluetooth RC Controller."
 * https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
 * | Neste exemplo prático, utilizamos a classe "ES_CarControl" para criar um código de programação conciso e eficaz destinado ao controle de um veículo de direção “FRONTAL”.
 * Dessa forma, o veículo ajusta a direção das rodas dianteiras de acordo com o deslocamento necessário. Esse método de direção é idêntico ao utilizado em veículos comuns de rua.
 * Para o controle dos motores, empregaremos a ponte H da ES32Lab, juntamente com a comunicação Bluetooth entre o smartphone e a ES32Lab.
 * O aplicativo recomendado para esse experimento é o "Bluetooth RC Controller".
 * https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller
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
  SerialBT.begin("ES32Lab_Car");  // Initialize Bluetooth with the name "ES32Lab_Car" so that it can be discovered by other devices. | Inicializa o Bluetooth com o nome "ES32Lab_Car" para que possa ser encontrado por outros dispositivos.
  
  // The object "car," derived from the class "ES_CarControl," will be initialized, specifying the type of vehicle steering. For this project, the "FRONTAL" steering type will be used.
  // |
  // O objeto "car", derivado da classe "ES_CarControl", será inicializado, informando o tipo de direção do veículo. Para este projeto, será utilizada a direção "FRONTAL".
  car.begin(FRONTAL);

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
  // The 'controlCommand' method aims to simplify motor activation through predefined commands. For more information on how to use this method, please refer to the complete documentation available at the following link: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme
  // | O método 'controlCommand' tem como objetivo simplificar o acionamento de motores através de comandos pré-definidos. Para obter mais informações sobre o uso desse método, consulte a documentação completa disponível no seguinte link: https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme
  car.controlCommand(SerialBT);
}