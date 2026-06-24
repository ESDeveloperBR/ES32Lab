/**
 * @brief Didactic example using ES_VL53L0X with setMeasurementTimingBudget().
 * | Exemplo didático usando ES_VL53L0X com setMeasurementTimingBudget().
 *
 * This program shows how to configure the measurement timing budget of the
 * VL53L0X distance sensor through the ES_VL53L0X class.
 *
 * The timing budget is the approximate time reserved internally by the sensor
 * for each distance measurement. Smaller values make readings faster, but can
 * reduce stability and repeatability. Larger values make readings slower, but
 * can improve stability, especially when the target is darker, farther away,
 * angled, or less reflective.
 *
 * In this example, the budget is configured to 200000 us, which means about
 * 200 ms per measurement. The loop also uses a delay of 100 ms only to keep the
 * Serial Monitor easy to read. In practice, the sensor reading itself already
 * takes time according to the configured budget.
 *
 * The example also applies setDistanceOffset(50), because many VL53L0X modules
 * can report a small initial distance even when an object is very close to the
 * sensor. This value should be calibrated for each physical sensor when needed.
 *
 * | Este programa mostra como configurar o tempo de medição do sensor de
 * distância VL53L0X através da classe ES_VL53L0X.
 *
 * O timing budget é o tempo aproximado reservado internamente pelo sensor para
 * cada medição de distância. Valores menores tornam as leituras mais rápidas,
 * mas podem reduzir a estabilidade e a repetibilidade. Valores maiores tornam
 * as leituras mais lentas, mas podem melhorar a estabilidade, principalmente
 * quando o alvo é mais escuro, está mais distante, inclinado ou reflete pouca
 * luz.
 *
 * Neste exemplo, o tempo de medição é configurado para 200000 us, ou seja,
 * cerca de 200 ms por medição. O loop também usa um delay de 100 ms apenas para
 * deixar o Monitor Serial fácil de acompanhar. Na prática, a própria leitura do
 * sensor já leva tempo conforme o budget configurado.
 *
 * O exemplo também aplica setDistanceOffset(50), porque muitos módulos VL53L0X
 * podem indicar uma pequena distância inicial mesmo quando um objeto está muito
 * próximo ao sensor. Esse valor deve ser calibrado para cada sensor físico
 * quando necessário.
 */

#include <Arduino.h> // Provides the Arduino base functions. | Fornece as funções base do Arduino.
#include <ES32Lab.h> // Loads the ES32Lab library and the ES_VL53L0X class. | Carrega a biblioteca ES32Lab e a classe ES_VL53L0X.

ES_VL53L0X distance; // Creates the VL53L0X distance sensor object. | Cria o objeto do sensor de distância VL53L0X.

void setup() { // Runs once when the ESP32 starts. | Executa uma vez quando o ESP32 inicia.
    Serial.begin(115200); // Starts the Serial Monitor at 115200 bps. | Inicia o Monitor Serial em 115200 bps.

    delay(500); // Waits for the Serial Monitor and sensor power-up. | Aguarda o Monitor Serial e a energização do sensor.

    Serial.println(); // Prints a blank line to separate the startup messages. | Imprime uma linha em branco para separar as mensagens de inicialização.
    Serial.println("Teste ES_VL53L0X com timing budget."); // Identifies this example on the Serial Monitor. | Identifica este exemplo no Monitor Serial.

    distance.setTimeout(500); // Defines how long read() may wait before timeout. | Define quanto tempo read() pode esperar antes de timeout.
    distance.setDistanceOffset(50); // Applies the initial distance correction. | Aplica a correção inicial de distância.

    if (!distance.begin()) { // Tries to initialize the sensor at the default I2C address 0x29. | Tenta inicializar o sensor no endereço I2C padrão 0x29.
        Serial.println("Sensor VL53L0X nao encontrado."); // Reports that the sensor did not answer. | Informa que o sensor não respondeu.

        while (true) { // Keeps the program stopped because the sensor is required. | Mantém o programa parado porque o sensor é necessário.
            delay(100); // Avoids a tight infinite loop. | Evita um loop infinito sem pausa.
        } // Ends the infinite stop loop. | Finaliza o loop infinito de parada.
    } // Ends the initialization failure check. | Finaliza a verificação de falha na inicialização.

    if (!distance.setMeasurementTimingBudget(200000)) { // Try to apply the selected measurement time in microseconds. | Tenta aplicar o tempo de medição escolhido em microssegundos.
        Serial.println("Timing budget invalido."); // Reports that the configured value was rejected. | Informa que o valor configurado foi recusado.

        while (true) { // Keeps the program stopped because the configuration failed. | Mantém o programa parado porque a configuração falhou.
            delay(100); // Avoids a tight infinite loop. | Evita um loop infinito sem pausa.
        } // Ends the infinite stop loop. | Finaliza o loop infinito de parada.
    } // Ends the timing budget configuration check. | Finaliza a verificação da configuração do timing budget.

    Serial.print("Sensor iniciado no endereco I2C 0x"); // Prints the I2C address label. | Imprime o rótulo do endereço I2C.
    Serial.println(distance.getAddress(), HEX); // Prints the current sensor I2C address. | Imprime o endereço I2C atual do sensor.

    Serial.print("Offset aplicado: "); // Prints the offset label. | Imprime o rótulo do offset.
    Serial.print(distance.getDistanceOffset()); // Prints the configured distance offset. | Imprime o offset de distância configurado.
    Serial.println(" mm"); // Prints the offset unit. | Imprime a unidade do offset.

    Serial.print("Timing budget aplicado: "); // Prints the timing budget label. | Imprime o rótulo do timing budget.
    Serial.print(distance.getMeasurementTimingBudget()); // Prints the real timing budget stored by the sensor configuration. | Imprime o timing budget real armazenado pela configuração do sensor.
    Serial.println(" us"); // Prints the timing budget unit. | Imprime a unidade do timing budget.
} // Ends setup(). | Finaliza setup().

void loop() { // Runs repeatedly after setup(). | Executa repetidamente depois de setup().
    uint16_t mm = distance.read(); // Reads one corrected distance measurement in millimeters. | Lê uma medição corrigida de distância em milímetros.

    if (distance.timeoutOccurred()) { // Checks if the last read exceeded the configured timeout. | Verifica se a última leitura ultrapassou o timeout configurado.
        Serial.println("TIMEOUT"); // Reports a timeout on the Serial Monitor. | Informa timeout no Monitor Serial.
    } else { // Runs when the reading finished without timeout. | Executa quando a leitura termina sem timeout.
        Serial.print("Distancia: "); // Prints the distance label. | Imprime o rótulo da distância.
        Serial.print(mm); // Prints the measured distance value. | Imprime o valor de distância medido.
        Serial.println(" mm"); // Prints the distance unit. | Imprime a unidade da distância.
    } // Ends the timeout check. | Finaliza a verificação de timeout.

    delay(100); // Adds a short pause to keep the Serial Monitor readable. | Adiciona uma pequena pausa para manter o Monitor Serial legível.
} // Ends loop(). | Finaliza loop().
