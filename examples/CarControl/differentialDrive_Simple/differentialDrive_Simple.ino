/**
 * @file differentialDrive_Simple.ino
 * @brief This example aims to provide an easy and straightforward mechanism for motor control using two H-bridges for the locomotion 
 * of a vehicle through the differential drive method. This method follows the same principle of locomotion as a tank, where each track is driven by a separate motor,
 * allowing them to rotate at different speeds. To change direction, the tank adjusts the rotation speed of one track relative to the other. For example, if 
 * the tank wants to turn left, it reduces the speed of the right track or increases the speed of the left track, creating a rotational difference that makes the tank turn left.
 * | Esse exemplo tem como objetivo utilizar, de forma fácil e objetiva, um mecanismo de controle de motores usando duas pontes H para a locomoção
 * de um veículo através do método diferencial. Esse método segue o mesmo princípio de locomoção de um trator de esteira,
 * onde cada esteira é acionada por um motor separado, permitindo que elas girem em velocidades diferentes. Para mudar de direção, o trator ajusta a velocidade de
 * rotação de uma esteira em relação à outra. Por exemplo, se o trator deseja girar para a esquerda, ele reduz a velocidade da esteira direita ou aumenta a
 * velocidade da esteira esquerda, criando uma diferença de rotação que faz o trator virar para a esquerda.
 * @warning For more information on the documentation of the 'ES_CarControl' class contained in the ES32Lab library, please refer to the link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 * | Para mais informações sobre a documentação da classe ‘ES_CarControl’ contida na biblioteca ES32Lab, acesse o link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido.
ES_Buzzer buzzer(P_BUZZER); // Instantiates the 'buzzer' object and its respective GPIO to be used. | Instancia o objeto 'buzzer' e sua respectiva GPIO a ser utilizada.
ES_CarControl car;  // Instantiate the 'car' object derived from the 'ES_CarControl' class. | Instancia o objeto 'car' derivado da classe 'ES_CarControl'.

// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
  
  // To use the differentialDriveBegin method, which is responsible for managing differential drive in a simple and straightforward way, following the methodology 
  // used in tanks, it is necessary to fill in some configuration parameters when using this class in ES32Lab. These parameters are shown below:
  // - car.differentialDriveBegin(&expander); // In this case, the 'car' object is initialized using the 'differentialDriveBegin' method, and the object responsible for motor control through the i2C expander of ES32Lab is passed as a parameter.
  // |
  // Para utilizar o método differentialDriveBegin, responsável por gerenciar o tracionamento diferencial de forma simples e objetiva, seguindo a metodologia 
  // utilizada em tratores de esteira, é necessário preencher alguns parâmetros de configuração ao utilizar essa classe na ES32Lab. Esses parâmetros são demonstrados na sequência:
  //  - car.differentialDriveBegin(&expander); // Nesse caso, o objeto 'car' é inicializado utilizando o método 'differentialDriveBegin', e é passado como parâmetro o objeto responsável pelo controle dos motores através do expansor i2C da ES32Lab.
  
  car.differentialDriveBegin(&expander, &buzzer); // In addition to motor control, the 'buzzer' object is also passed as a parameter, enabling the simulation of a horn sound through the ES32Lab buzzer. | Dessa forma, além do controle dos motores, também é passado como parâmetro o objeto buzzer, possibilitando a simulação de um som de buzina através do buzzer da ES32Lab.
  car.setSpeed(20); // Ajusta a velocidade de rotação dos motores em uma escala que pode variar entre 0 a 100% | Adjusts the motor rotation speed on a scale that can vary between 0 to 100%
}

// <<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  car.horn(); // Activates the horn. | Aciona a buzina.
  delay(3000);

  car.forward();  // Move the vehicle forward. | Move o veículo para frente.
  delay(3000);

  car.backward(); // Move the vehicle backward. | Move o veículo para trás.
  delay(3000);

  car.left(); // Turn the vehicle to the left. | Vira o veículo para a esquerda.
  delay(3000);

  car.right(); // Turn the vehicle to the right. | Vira o veículo para a direita.
  delay(3000);

  car.forwardLeft(); // Move the vehicle diagonally forward left. | Move o veículo diagonalmente para frente e para a esquerda.
  delay(3000);

  car.forwardRight(); // Move the vehicle diagonally forward right. | Move o veículo diagonalmente para frente e para a direita.
  delay(3000);

  car.backLeft(); // Move the vehicle diagonally backward left. | Move o veículo diagonalmente para trás e para a esquerda.
  delay(3000);

  car.backRight(); // Move the vehicle diagonally backward right. | Move o veículo diagonalmente para trás e para a direita.
  delay(3000);

  car.stop(); // Stop the vehicle. | Para o veículo.
  delay(3000);

  car.frontLights(true); // Turn on the front lights. | Acende as luzes dianteiras.
  delay(3000);

  car.backLights(true); // Turn on the back lights. | Acende as luzes traseiras.
  delay(3000);

  car.frontLights(false); // Turn off the front lights. | Apaga as luzes dianteiras. 
  delay(3000);

  car.backLights(false); // Turn off the back lights. | Apaga as luzes traseiras.
  delay(3000);

  car.extra(true); // Activate the extra feature. | Ativa o recurso extra.
  delay(3000);

  car.extra(false); // Deactivate the extra feature. | Desativa o recurso extra.
  delay(3000);
}
