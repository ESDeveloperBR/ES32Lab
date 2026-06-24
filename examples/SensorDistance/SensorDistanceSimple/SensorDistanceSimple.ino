/**
 * @brief Simple test example for the ES_VL53L0X distance sensor.
 * | Exemplo simples de teste para o sensor de distância ES_VL53L0X.
 *
 * This sketch initializes the I2C bus, starts the VL53L0X sensor and prints
 * the measured distance in millimeters on the Serial Monitor.
 *
 * | Este sketch inicializa o barramento I2C, inicia o sensor VL53L0X e imprime
 * a distância medida em milímetros no Monitor Serial.
 */
 
#include <Arduino.h>
#include <ES32Lab.h>

ES_VL53L0X distance; // Distance sensor object. | Objeto do sensor de distância.

void setup() {
    Serial.begin(115200); // Starts serial communication. | Inicia a comunicação serial.

    distance.setTimeout(500);       // Sets read timeout. | Define o timeout de leitura.
    distance.setDistanceOffset(50); // Initial distance calibration. | Calibração da distância inicial.

    if (!distance.begin()) {
        Serial.println("Sensor VL53L0X nao encontrado.");

        while (true) {
            delay(100);
        }
    }

    Serial.println("Sensor VL53L0X iniciado.");
}

void loop() {
    uint16_t mm = distance.read();

    if (distance.timeoutOccurred()) {
        Serial.println("TIMEOUT");
    } else {
        Serial.print(mm);
        Serial.println(" mmX");
    }

    delay(100);
}
