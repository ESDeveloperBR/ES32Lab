#ifndef ES_VL53L0X_H
#define ES_VL53L0X_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @brief Current version of the ES_VL53L0X class. | Versão atual da classe ES_VL53L0X.
 */
#define ES_VL53L0X_VERSION "0.2.0 update 06/22/2026"  // mm/dd/yyyy

/**
 * @brief Default 7-bit I2C address used by the VL53L0X after power-up. | Endereço I2C padrão de 7 bits usado pelo VL53L0X após energizar.
 */
#define ES_VL53L0X_DEFAULT_ADDRESS 0x29

/**
 * @brief Invalid distance value returned when the sensor is not initialized or times out. | Valor de distância inválida retornado quando o sensor não está inicializado ou ocorre timeout.
 */
#define ES_VL53L0X_INVALID_DISTANCE 65535

/**
 * @brief ES32Lab driver for the ST VL53L0X time-of-flight distance sensor.
 * |
 * Driver ES32Lab para o sensor de distância time-of-flight ST VL53L0X.
 *
 * This class performs the I2C communication and basic sensor configuration
 * directly, without exposing external sensor-driver classes to the user.
 * The public reading method returns distance in millimeters and applies the
 * configured offset when one is set.
 * |
 * Esta classe executa diretamente a comunicação I2C e a configuração básica
 * do sensor, sem expor classes externas de driver ao usuário. O método público
 * de leitura retorna a distância em milímetros e aplica o offset configurado,
 * quando definido.
 */
class ES_VL53L0X {
  private:
    struct SequenceStepEnables {
      boolean tcc;
      boolean dss;
      boolean msrc;
      boolean preRange;
      boolean finalRange;
    };

    struct SequenceStepTimeouts {
      uint16_t preRangeVcselPeriodPclks;
      uint16_t finalRangeVcselPeriodPclks;

      uint16_t msrcDssTccMclks;
      uint32_t msrcDssTccUs;

      uint16_t preRangeMclks;
      uint32_t preRangeUs;

      uint16_t finalRangeMclks;
      uint32_t finalRangeUs;
    };

    TwoWire *_bus;                      // I2C bus used by the sensor. | Barramento I2C utilizado pelo sensor.
    uint8_t _address;                   // Current/final 7-bit I2C address. | Endereço I2C atual/final de 7 bits.
    uint8_t _lastStatus = 0;            // Last I2C write status. | Último status de escrita I2C.
    uint8_t _stopVariable = 0;          // Internal value used by the single-shot sequence. | Valor interno usado pela sequência de leitura única.
    uint16_t _timeout = 0;              // Read timeout in milliseconds. | Timeout de leitura em milissegundos.
    uint16_t _distanceOffset = 0;       // Distance correction offset in mm. | Offset de correção da distância em mm.
    uint16_t _lastDistance = ES_VL53L0X_INVALID_DISTANCE; // Last corrected distance in mm. | Última distância corrigida em mm.
    uint32_t _measurementTimingBudgetUs = 0; // Current measurement timing budget. | Tempo de medição atual.
    boolean _isInitialized = false;     // Indicates if begin() succeeded. | Indica se begin() foi executado com sucesso.
    boolean _didTimeout = false;        // Indicates if a timeout occurred. | Indica se ocorreu timeout.

    uint16_t _applyDistanceOffset(uint16_t distanceMm);

    boolean _initializeSensor(boolean io2v8);
    boolean _getSpadInfo(uint8_t *count, boolean *typeIsAperture);
    boolean _performSingleRefCalibration(uint8_t vhvInitByte);
    void _loadTuningSettings();

    uint16_t _readRawSingle();
    uint16_t _readRawResult();

    boolean _setMeasurementTimingBudget(uint32_t budgetUs);
    uint32_t _getMeasurementTimingBudget();
    void _getSequenceStepEnables(SequenceStepEnables *enables);
    void _getSequenceStepTimeouts(const SequenceStepEnables *enables, SequenceStepTimeouts *timeouts);
    uint8_t _readVcselPeriodPclks(boolean finalRange);

    boolean _writeReg(uint8_t reg, uint8_t value);
    boolean _writeReg16(uint8_t reg, uint16_t value);
    boolean _writeMulti(uint8_t reg, const uint8_t *src, uint8_t count);
    uint8_t _readReg(uint8_t reg);
    uint16_t _readReg16(uint8_t reg);
    boolean _readMulti(uint8_t reg, uint8_t *dst, uint8_t count);

    boolean _timeoutExpired(uint32_t startMs);

    static uint16_t _decodeTimeout(uint16_t regVal);
    static uint16_t _encodeTimeout(uint32_t timeoutMclks);
    static uint32_t _timeoutMclksToMicroseconds(uint16_t timeoutMclks, uint8_t vcselPeriodPclks);
    static uint32_t _timeoutMicrosecondsToMclks(uint32_t timeoutUs, uint8_t vcselPeriodPclks);
    static uint32_t _calcMacroPeriod(uint8_t vcselPeriodPclks);
    static uint8_t _decodeVcselPeriod(uint8_t regVal);

  public:
    /**
     * @brief Creates an ES_VL53L0X object and stores the desired I2C settings.
     * |
     * Cria um objeto ES_VL53L0X e armazena as configurações I2C desejadas.
     * @param address Final 7-bit I2C address used by the sensor. Defaults to 0x29. | Endereço I2C final de 7 bits usado pelo sensor. O padrão é 0x29.
     * @param bus I2C bus used for communication. Defaults to Wire. | Barramento I2C usado para comunicação. O padrão é Wire.
     * @note The constructor does not access the I2C bus. Communication starts only in begin(). | O construtor não acessa o barramento I2C. A comunicação começa apenas no begin().
     */
    ES_VL53L0X(uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, TwoWire &bus = Wire);

    /**
     * @brief Initializes the sensor with the stored bus and address settings.
     * |
     * Inicializa o sensor com as configurações de barramento e endereço armazenadas.
     * @param io2v8 When true, configures the sensor for 2.8 V I/O mode. | Quando verdadeiro, configura o sensor para modo de I/O em 2,8 V.
     * @return true if the VL53L0X was detected and initialized, false otherwise. | true se o VL53L0X foi detectado e inicializado, false caso contrário.
     */
    boolean begin(boolean io2v8 = true);

    /**
     * @brief Initializes the sensor and changes it to the specified final I2C address.
     * |
     * Inicializa o sensor e altera para o endereço I2C final especificado.
     * @param address Final 7-bit I2C address. | Endereço I2C final de 7 bits.
     * @param io2v8 When true, configures the sensor for 2.8 V I/O mode. | Quando verdadeiro, configura o sensor para modo de I/O em 2,8 V.
     * @return true if the sensor was initialized and the address is valid, false otherwise. | true se o sensor foi inicializado e o endereço é válido, false caso contrário.
     */
    boolean begin(uint8_t address, boolean io2v8 = true);

    /**
     * @brief Selects an I2C bus, initializes the sensor and stores its final address.
     * |
     * Seleciona um barramento I2C, inicializa o sensor e armazena seu endereço final.
     * @param bus TwoWire bus used by the sensor. | Barramento TwoWire usado pelo sensor.
     * @param address Final 7-bit I2C address. | Endereço I2C final de 7 bits.
     * @param io2v8 When true, configures the sensor for 2.8 V I/O mode. | Quando verdadeiro, configura o sensor para modo de I/O em 2,8 V.
     * @return true if the sensor was initialized, false otherwise. | true se o sensor foi inicializado, false caso contrário.
     */
    boolean begin(TwoWire &bus, uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, boolean io2v8 = true);

    /**
     * @brief Returns whether the last begin() call initialized the sensor successfully.
     * |
     * Retorna se a última chamada de begin() inicializou o sensor com sucesso.
     * @return true if the object is initialized, false otherwise. | true se o objeto está inicializado, false caso contrário.
     */
    boolean isInitialized();

    /**
     * @brief Checks if an I2C device acknowledges at the stored address.
     * |
     * Verifica se algum dispositivo I2C responde no endereço armazenado.
     * @return true if the current address responds on the I2C bus, false otherwise. | true se o endereço atual responde no barramento I2C, false caso contrário.
     */
    boolean isConnected();

    /**
     * @brief Defines the I2C bus used by the sensor.
     * |
     * Define o barramento I2C utilizado pelo sensor.
     * @param bus TwoWire object, such as Wire or Wire1. | Objeto TwoWire, como Wire ou Wire1.
     */
    void setBus(TwoWire &bus);

    /**
     * @brief Returns the I2C bus currently assigned to the sensor.
     * |
     * Retorna o barramento I2C atualmente associado ao sensor.
     * @return Pointer to the TwoWire bus used by the class. | Ponteiro para o barramento TwoWire usado pela classe.
     */
    TwoWire *getBus();

    /**
     * @brief Changes the sensor I2C address when initialized, or stores it for the next begin().
     * |
     * Altera o endereço I2C do sensor quando inicializado, ou armazena para o próximo begin().
     * @param address New 7-bit I2C address. | Novo endereço I2C de 7 bits.
     * @return true if the address is valid, false otherwise. | true se o endereço é válido, false caso contrário.
     */
    boolean setAddress(uint8_t address);

    /**
     * @brief Returns the current/final I2C address stored by this object.
     * |
     * Retorna o endereço I2C atual/final armazenado por este objeto.
     * @return Current 7-bit I2C address. | Endereço I2C atual de 7 bits.
     */
    uint8_t getAddress();

    /**
     * @brief Sets the maximum waiting time for blocking read operations.
     * |
     * Define o tempo máximo de espera para operações de leitura bloqueantes.
     * @param timeoutMs Timeout in milliseconds. Use 0 to disable timeout. | Timeout em milissegundos. Use 0 para desativar o timeout.
     */
    void setTimeout(uint16_t timeoutMs);

    /**
     * @brief Returns the configured read timeout.
     * |
     * Retorna o timeout de leitura configurado.
     * @return Timeout in milliseconds. | Timeout em milissegundos.
     */
    uint16_t getTimeout();

    /**
     * @brief Indicates whether a timeout occurred since the previous call.
     * |
     * Indica se ocorreu timeout desde a chamada anterior.
     * @return true if a timeout occurred, false otherwise. | true se ocorreu timeout, false caso contrário.
     * @note The timeout flag is cleared after this method is called. | A flag de timeout é limpa depois que este método é chamado.
     */
    boolean timeoutOccurred();

    /**
     * @brief Returns the status of the last I2C write transmission.
     * |
     * Retorna o status da última transmissão I2C de escrita.
     * @return Value returned by Wire.endTransmission(). | Valor retornado por Wire.endTransmission().
     */
    uint8_t lastStatus();

    /**
     * @brief Reads one distance measurement in millimeters.
     * |
     * Realiza uma leitura de distância em milímetros.
     * @return Corrected distance in millimeters, or 65535 on invalid read/timeout. | Distância corrigida em milímetros, ou 65535 em leitura inválida/timeout.
     */
    uint16_t read();

    /**
     * @brief Returns the last corrected distance stored by the class.
     * |
     * Retorna a última distância corrigida armazenada pela classe.
     * @return Last corrected distance in millimeters. | Última distância corrigida em milímetros.
     */
    uint16_t lastDistance();

    /**
     * @brief Sets a fixed offset to subtract from every distance reading.
     * |
     * Define um offset fixo para subtrair de todas as leituras de distância.
     * @param offsetMm Offset in millimeters. | Offset em milímetros.
     * @note If the measured distance is less than or equal to the offset, the returned distance is 0. | Se a distância medida for menor ou igual ao offset, a distância retornada será 0.
     */
    void setDistanceOffset(uint16_t offsetMm);

    /**
     * @brief Returns the configured distance offset.
     * |
     * Retorna o offset de distância configurado.
     * @return Offset in millimeters. | Offset em milímetros.
     */
    uint16_t getDistanceOffset();

    /**
     * @brief Sets the measurement timing budget.
     * |
     * Define o tempo disponível para cada medição.
     * @param budgetUs Measurement timing budget in microseconds. | Tempo de medição em microssegundos.
     * @return true if the value was accepted, false otherwise. | true se o valor foi aceito, false caso contrário.
     * @note Larger budgets can improve stability/accuracy, but make readings slower. | Tempos maiores podem melhorar estabilidade/precisão, mas deixam as leituras mais lentas.
     */
    boolean setMeasurementTimingBudget(uint32_t budgetUs);

    /**
     * @brief Returns the current measurement timing budget.
     * |
     * Retorna o tempo de medição atual.
     * @return Timing budget in microseconds, or 0 if the sensor is not initialized. | Tempo de medição em microssegundos, ou 0 se o sensor não está inicializado.
     */
    uint32_t getMeasurementTimingBudget();
};

#endif 
