/**
 * @brief Simple example: line follower robot using ES_CarLineFollower.
 * | Exemplo simples: robô seguidor de linha usando ES_CarLineFollower.
 *
 * This example demonstrates the minimum structure needed to use the ES_CarLineFollower class.
 * The robot uses two digital line sensors connected to the PCF8574 I2C expander and the
 * ES_CarControl class to move the vehicle.
 *
 * Default sensor connection used in this example:
 * - Left line sensor:  EX2
 * - Right line sensor: EX3
 *
 * The main command is:
 *     lineFollower.update();
 *
 * It must be called continuously inside loop(), without long delays, so the robot can read
 * the sensors and correct its direction quickly.
 *
 * | Este exemplo demonstra a estrutura mínima necessária para usar a classe ES_CarLineFollower.
 * O robô utiliza dois sensores digitais de linha conectados ao expansor I2C PCF8574 e a
 * classe ES_CarControl para movimentar o veículo.
 *
 * Ligação dos sensores usada neste exemplo:
 * - Sensor de linha esquerdo: EX2
 * - Sensor de linha direito:  EX3
 *
 * O comando principal é:
 *     lineFollower.update();
 *
 * Ele deve ser chamado continuamente dentro do loop(), sem delays longos, para que o robô
 * consiga ler os sensores e corrigir sua direção rapidamente.
 *
 * @warning Start testing with low speeds. Increase the values only after the robot follows
 * the line reliably.
 * | Comece os testes com velocidades baixas. Aumente os valores apenas depois que o robô
 * estiver seguindo a linha de forma confiável.
 *
 * @see ES_CarLineFollower documentation:
 * https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarLineFollower#readme
 * | Documentação da classe ES_CarLineFollower:
 * https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_CarLineFollower#readme
 *
 * @see Official board: https://www.esdeveloper.com.br
 * | Placa oficial disponível em: https://www.esdeveloper.com.br
 */

#include <Arduino.h>
#include <ES32Lab.h> // Library ES32Lab | Biblioteca ES32Lab

ES_PCF8574 expander(0x20);                  // I2C expander object. | Objeto expansor I2C.
ES_CarControl car(expander);                // Car control object. | Objeto de controle do carro.
ES_CarLineFollower lineFollower(car, expander); // Line follower object. | Objeto seguidor de linha.

// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
    Serial.begin(115200); // Starts serial communication. | Inicia a comunicação serial.

    expander.begin();     // Starts the PCF8574 expander. | Inicializa o expansor PCF8574.

    // Initializes the car using differential steering. | Inicializa o carro usando direção diferencial.
    if (!car.begin(DIFFERENTIAL)) {
        Serial.println("Car initialization failed! | Falha ao inicializar o carro!");
        while (true);
    }

    // Use this line only if one motor is physically rotating in the wrong direction.
    // | Use esta linha apenas se um motor estiver girando fisicamente no sentido errado.
    // car.invertMotorCommands(0);

    // Initializes the line follower:
    // left sensor, right sensor, high speed, low speed, low speed time, no-line time, turn speed.
    // | Inicializa o seguidor de linha:
    // sensor esquerdo, sensor direito, velocidade alta, velocidade baixa, tempo em baixa,
    // tempo sem linha e velocidade de correção.
    lineFollower.begin(EX2, EX3, 20, 10, 2500, 5000, 70);

    lineFollower.enable(); // Starts automatic line following. | Inicia o seguidor de linha automático.

    Serial.println("Line follower started. | Seguidor de linha iniciado.");
}

// <<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>
void loop() {
    lineFollower.update(); // Reads sensors and corrects the robot. | Lê os sensores e corrige o robô.
}
