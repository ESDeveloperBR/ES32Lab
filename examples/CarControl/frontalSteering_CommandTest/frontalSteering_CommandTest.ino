/**
 * @brief This example aims to demonstrate and test all steering commands in a vehicle with "FRONTAL" steering
 * mechanics using the "ES_CarControl" class.
 * | Este exemplo visa demonstrar e testar todos os comandos de direção em um veículo que apresenta uma mecânica de 
 * direção do tipo "FRONTAL", utilizando a classe "ES_CarControl". 
 * @warning For more information on the documentation of the 'ES_CarControl' class contained in the ES32Lab library, please refer to the link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 * | Para mais informações sobre a documentação da classe ‘ES_CarControl’ contida na biblioteca ES32Lab, acesse o link (https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarControl#readme).
 */

#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido.
ES_Buzzer buzzer(P_BUZZER); // Instantiates the 'buzzer' object and its respective GPIO to be used. | Instancia o objeto 'buzzer' e sua respectiva GPIO a ser utilizada.
ES_CarControl car(&expander, &buzzer);  // Instantiate the 'car' object derived from the 'ES_CarControl' class. | Instancia o objeto 'car' derivado da classe 'ES_CarControl'.
// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
  // The object "car," derived from the class "ES_CarControl," will be initialized, specifying the type of vehicle steering. For this project, the "FRONTAL" steering type will be used.
  // |
  // O objeto "car", derivado da classe "ES_CarControl", será inicializado, informando o tipo de direção do veículo. Para este projeto, será utilizada a direção "FRONTAL".
  car.begin(FRONTAL);
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