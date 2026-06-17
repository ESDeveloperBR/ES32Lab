/**
 * @brief Example: line follower robot with TFT display and analog keyboard.
 * | Exemplo: robô seguidor de linha com display TFT e teclado analógico.
 *
 * This example demonstrates how to use ES_CarLineFollower with visual status on the TFT display
 * and manual commands from the ES32Lab analog keyboard.
 *
 * Sensor connection used in this example:
 * - Left line sensor:  EX2
 * - Right line sensor: EX3
 *
 * Keyboard controls:
 * - KEY_DOWN:   enable automatic line following
 * - KEY_CENTER: disable automatic line following and stop the car
 * - KEY_UP:     disable automatic line following and move backward slowly
 * - KEY_LEFT:   disable automatic line following and make a short right correction
 * - KEY_RIGHT:  disable automatic line following and make a short left correction
 *
 * | Este exemplo demonstra como usar ES_CarLineFollower com exibição de status no display TFT
 * e comandos manuais pelo teclado analógico da ES32Lab.
 *
 * Ligação dos sensores usada neste exemplo:
 * - Sensor de linha esquerdo: EX2
 * - Sensor de linha direito:  EX3
 *
 * Controles pelo teclado:
 * - KEY_DOWN:   habilita o seguidor de linha automático
 * - KEY_CENTER: desabilita o seguidor de linha automático e para o carro
 * - KEY_UP:     desabilita o seguidor de linha automático e move lentamente para trás
 * - KEY_LEFT:   desabilita o seguidor de linha automático e faz uma curta correção para a direita
 * - KEY_RIGHT:  desabilita o seguidor de linha automático e faz uma curta correção para a esquerda
 *
 * @warning Keep lineFollower.update() running continuously in loop(). Avoid long delays while
 * the automatic line follower is enabled.
 * | Mantenha lineFollower.update() rodando continuamente no loop(). Evite delays longos enquanto
 * o seguidor de linha automático estiver habilitado.
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

#define EXAMPLE_VERSION "1.0.0"

ES_PCF8574 expander(0x20);                  // I2C expander object. | Objeto expansor I2C.
ES_CarControl car(expander);                // Car control object. | Objeto de controle do carro.
ES_CarLineFollower lineFollower(car, expander); // Line follower object. | Objeto seguidor de linha.
ES_TFT display;                             // TFT display object. | Objeto do display TFT.
ES_AnalogKeyboard keyboard;                 // Analog keyboard object. | Objeto do teclado analógico.
ES_TimeInterval displayUpdateInterval;      // Display update timer. | Temporizador de atualização do display.

// <<< Draw status on TFT display | Desenha o status no display TFT >>>
void drawStatus() {
    if (lineFollower.isEnabled()) {
        display.fillScreen(TFT_GREEN);
        display.setTextColor(TFT_BLACK);
        display.drawCentreScreenString("LINE FOLLOWER", 10);
        display.drawCentreScreenString("ON", 34, 4);
    } else {
        display.fillScreen(TFT_YELLOW);
        display.setTextColor(TFT_BLACK);
        display.drawCentreScreenString("LINE FOLLOWER", 10);
        display.drawCentreScreenString("OFF", 34, 4);
    }

    display.drawCentreScreenString("DOWN: START", 76);
    display.drawCentreScreenString("CENTER: STOP", 96);
    display.drawCentreScreenString(EXAMPLE_VERSION, 116);
}

// <<<<<<<<<<<<<<<<<< SETUP >>>>>>>>>>>>>>>>>>>>>>
void setup() {
    Serial.begin(115200); // Starts serial communication. | Inicia a comunicação serial.

    display.begin();               // Starts the TFT display. | Inicializa o display TFT.
    display.setRotation(3);        // Sets display rotation. | Define a rotação do display.
    display.fillScreen(TFT_BLACK); // Clears the screen. | Limpa a tela.

    expander.begin(); // Starts the PCF8574 expander. | Inicializa o expansor PCF8574.

    // Initializes the car using differential steering. | Inicializa o carro usando direção diferencial.
    if (!car.begin(DIFFERENTIAL)) {
        display.fillScreen(TFT_RED);
        display.setTextColor(TFT_WHITE);
        display.drawCentreScreenString("CAR INIT FAILED", 50);
        while (true);
    }

    car.setSpeed(20); // Sets a safe initial speed. | Define uma velocidade inicial segura.

    // Use this line only if one motor is physically rotating in the wrong direction.
    // | Use esta linha apenas se um motor estiver girando fisicamente no sentido errado.
    // car.invertMotorCommands(0);

    // Initializes the line follower:
    // left sensor, right sensor, high speed, low speed, low speed time, no-line time, turn speed.
    // | Inicializa o seguidor de linha:
    // sensor esquerdo, sensor direito, velocidade alta, velocidade baixa, tempo em baixa,
    // tempo sem linha e velocidade de correção.
    lineFollower.begin(EX2, EX3, 20, 10, 2500, 5000, 70);

    drawStatus();
}

// <<<<<<<<<<<<<<<<<<< LOOP >>>>>>>>>>>>>>>>>>>>>>>
void loop() {
    if (displayUpdateInterval.intervalMillis(500)) {
        drawStatus(); // Updates the display status. | Atualiza o status no display.
    }

    if (keyboard.press(KEY_DOWN)) {
        lineFollower.enable(); // Enables automatic line following. | Habilita o seguidor de linha automático.
        drawStatus();
    }

    if (keyboard.press(KEY_CENTER)) {
        lineFollower.disable(); // Disables automatic line following and stops the car. | Desabilita o seguidor de linha automático e para o carro.
        drawStatus();
    }

    if (keyboard.press(KEY_UP)) {
        lineFollower.disable(); // Manual movement must disable automatic mode. | Movimento manual deve desabilitar o modo automático.
        car.backward(10);
        drawStatus();
    }

    if (keyboard.press(KEY_LEFT)) {
        lineFollower.disable();
        car.right(20);
        delay(600);
        car.stop();
        drawStatus();
    }

    if (keyboard.press(KEY_RIGHT)) {
        lineFollower.disable();
        car.left(20);
        delay(600);
        car.stop();
        drawStatus();
    }

    lineFollower.update(); // Reads sensors and corrects the robot. | Lê os sensores e corrige o robô.
}
