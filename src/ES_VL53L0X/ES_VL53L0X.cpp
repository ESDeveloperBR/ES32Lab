#include "ES_VL53L0X.h" 

namespace {
  const uint8_t SYSRANGE_START = 0x00;
  const uint8_t SYSTEM_SEQUENCE_CONFIG = 0x01;
  const uint8_t SYSTEM_INTERRUPT_CONFIG_GPIO = 0x0A;
  const uint8_t SYSTEM_INTERRUPT_CLEAR = 0x0B;
  const uint8_t RESULT_INTERRUPT_STATUS = 0x13;
  const uint8_t RESULT_RANGE_STATUS = 0x14;
  const uint8_t I2C_SLAVE_DEVICE_ADDRESS = 0x8A;
  const uint8_t MSRC_CONFIG_CONTROL = 0x60;
  const uint8_t MSRC_CONFIG_TIMEOUT_MACROP = 0x46;
  const uint8_t PRE_RANGE_CONFIG_VCSEL_PERIOD = 0x50;
  const uint8_t PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI = 0x51;
  const uint8_t FINAL_RANGE_CONFIG_VCSEL_PERIOD = 0x70;
  const uint8_t FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI = 0x71;
  const uint8_t GLOBAL_CONFIG_SPAD_ENABLES_REF_0 = 0xB0;
  const uint8_t GLOBAL_CONFIG_REF_EN_START_SELECT = 0xB6;
  const uint8_t DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD = 0x4E;
  const uint8_t DYNAMIC_SPAD_REF_EN_START_OFFSET = 0x4F;
  const uint8_t GPIO_HV_MUX_ACTIVE_HIGH = 0x84;
  const uint8_t VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV = 0x89;
  const uint8_t IDENTIFICATION_MODEL_ID = 0xC0;

  const uint8_t SEQUENCE_STEP_TCC = 0x10;
  const uint8_t SEQUENCE_STEP_DSS = 0x08;
  const uint8_t SEQUENCE_STEP_MSRC = 0x04;
  const uint8_t SEQUENCE_STEP_PRE_RANGE = 0x40;
  const uint8_t SEQUENCE_STEP_FINAL_RANGE = 0x80;

  const uint32_t START_OVERHEAD_US = 1320;
  const uint32_t END_OVERHEAD_US = 960;
  const uint32_t MSRC_OVERHEAD_US = 660;
  const uint32_t TCC_OVERHEAD_US = 590;
  const uint32_t DSS_OVERHEAD_US = 690;
  const uint32_t PRE_RANGE_OVERHEAD_US = 660;
  const uint32_t FINAL_RANGE_OVERHEAD_US = 550;
  const uint32_t MIN_TIMING_BUDGET_US = 20000;
}

// <<< Constructor of the class | Construtor da classe >>>
ES_VL53L0X::ES_VL53L0X(uint8_t address, TwoWire &bus) {
  _address = address;
  _bus = &bus;
}

// <<< Initializes the sensor | Inicializa o sensor >>>
boolean ES_VL53L0X::begin(boolean io2v8) {
  if (_bus == nullptr) {
    _isInitialized = false;
    return false;
  }

  _bus->begin();
  _didTimeout = false;
  _lastDistance = ES_VL53L0X_INVALID_DISTANCE;

  uint8_t finalAddress = _address;
  _address = ES_VL53L0X_DEFAULT_ADDRESS;
  _isInitialized = false;

  if (!isConnected()) {
    _address = finalAddress;
    return false;
  }

  if (_readReg(IDENTIFICATION_MODEL_ID) != 0xEE) {
    _address = finalAddress;
    return false;
  }

  if (!_initializeSensor(io2v8)) {
    _address = finalAddress;
    return false;
  }

  _isInitialized = true;

  if (finalAddress != ES_VL53L0X_DEFAULT_ADDRESS) {
    if (!setAddress(finalAddress)) {
      _isInitialized = false;
      return false;
    }
  }

  _address = finalAddress;
  return true;
}

// <<< Initializes the sensor with a final address | Inicializa o sensor com endereço final >>>
boolean ES_VL53L0X::begin(uint8_t address, boolean io2v8) {
  if (address > 0x7F) {
    return false;
  }

  _address = address;
  return begin(io2v8);
}

// <<< Initializes the sensor with a custom bus | Inicializa o sensor com barramento personalizado >>>
boolean ES_VL53L0X::begin(TwoWire &bus, uint8_t address, boolean io2v8) {
  setBus(bus);
  return begin(address, io2v8);
}

// <<< Returns initialization status | Retorna status de inicialização >>>
boolean ES_VL53L0X::isInitialized() {
  return _isInitialized;
}

// <<< Checks I2C connection | Verifica conexão I2C >>>
boolean ES_VL53L0X::isConnected() {
  if (_bus == nullptr) {
    return false;
  }

  _bus->beginTransmission(_address);
  _lastStatus = _bus->endTransmission();
  return _lastStatus == 0;
}

// <<< Defines the I2C bus | Define o barramento I2C >>>
void ES_VL53L0X::setBus(TwoWire &bus) {
  _bus = &bus;
}

// <<< Returns the I2C bus | Retorna o barramento I2C >>>
TwoWire *ES_VL53L0X::getBus() {
  return _bus;
}

// <<< Changes the I2C address | Altera o endereço I2C >>>
boolean ES_VL53L0X::setAddress(uint8_t address) {
  if (address > 0x7F) {
    return false;
  }

  if (_isInitialized && !_writeReg(I2C_SLAVE_DEVICE_ADDRESS, address & 0x7F)) {
    return false;
  }

  _address = address;
  return true;
}

// <<< Returns the I2C address | Retorna o endereço I2C >>>
uint8_t ES_VL53L0X::getAddress() {
  return _address;
}

// <<< Sets read timeout | Define timeout de leitura >>>
void ES_VL53L0X::setTimeout(uint16_t timeoutMs) {
  _timeout = timeoutMs;
}

// <<< Returns read timeout | Retorna timeout de leitura >>>
uint16_t ES_VL53L0X::getTimeout() {
  return _timeout;
}

// <<< Checks timeout flag | Verifica flag de timeout >>>
boolean ES_VL53L0X::timeoutOccurred() {
  boolean tmp = _didTimeout;
  _didTimeout = false;
  return tmp;
}

// <<< Returns last I2C write status | Retorna último status de escrita I2C >>>
uint8_t ES_VL53L0X::lastStatus() {
  return _lastStatus;
}

// <<< Reads distance | Lê distância >>>
uint16_t ES_VL53L0X::read() {
  if (!_isInitialized) {
    _lastDistance = ES_VL53L0X_INVALID_DISTANCE;
    return _lastDistance;
  }

  _lastDistance = _applyDistanceOffset(_readRawSingle());
  return _lastDistance;
}

// <<< Returns last distance | Retorna última distância >>>
uint16_t ES_VL53L0X::lastDistance() {
  return _lastDistance;
}

// <<< Sets distance offset | Define offset de distância >>>
void ES_VL53L0X::setDistanceOffset(uint16_t offsetMm) {
  _distanceOffset = offsetMm;
}

// <<< Returns distance offset | Retorna offset de distância >>>
uint16_t ES_VL53L0X::getDistanceOffset() {
  return _distanceOffset;
}

// <<< Sets measurement timing budget | Define tempo de medição >>>
boolean ES_VL53L0X::setMeasurementTimingBudget(uint32_t budgetUs) {
  if (!_isInitialized) {
    return false;
  }

  return _setMeasurementTimingBudget(budgetUs);
}

// <<< Returns measurement timing budget | Retorna tempo de medição >>>
uint32_t ES_VL53L0X::getMeasurementTimingBudget() {
  if (!_isInitialized) {
    return 0;
  }

  return _getMeasurementTimingBudget();
}

// ----------------------------------------------------------------------------------------------
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PRIVATE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ----------------------------------------------------------------------------------------------

uint16_t ES_VL53L0X::_applyDistanceOffset(uint16_t distanceMm) {
  if (distanceMm == ES_VL53L0X_INVALID_DISTANCE) {
    return ES_VL53L0X_INVALID_DISTANCE;
  }

  if (distanceMm <= _distanceOffset) {
    return 0;
  }

  return distanceMm - _distanceOffset;
}

boolean ES_VL53L0X::_initializeSensor(boolean io2v8) {
  if (io2v8) {
    _writeReg(VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV, _readReg(VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV) | 0x01);
  }

  _writeReg(0x88, 0x00);
  _writeReg(0x80, 0x01);
  _writeReg(0xFF, 0x01);
  _writeReg(0x00, 0x00);
  _stopVariable = _readReg(0x91);
  _writeReg(0x00, 0x01);
  _writeReg(0xFF, 0x00);
  _writeReg(0x80, 0x00);

  _writeReg(MSRC_CONFIG_CONTROL, _readReg(MSRC_CONFIG_CONTROL) | 0x12);

  _writeReg16(0x44, 0x0020); // Signal rate limit of 0.25 MCPS. | Limite de sinal de 0,25 MCPS.
  _writeReg(SYSTEM_SEQUENCE_CONFIG, 0xFF);

  uint8_t spadCount = 0;
  boolean spadTypeIsAperture = false;
  if (!_getSpadInfo(&spadCount, &spadTypeIsAperture)) {
    return false;
  }

  uint8_t refSpadMap[6];
  if (!_readMulti(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, refSpadMap, 6)) {
    return false;
  }

  _writeReg(0xFF, 0x01);
  _writeReg(DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
  _writeReg(DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
  _writeReg(0xFF, 0x00);
  _writeReg(GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);

  uint8_t firstSpadToEnable = spadTypeIsAperture ? 12 : 0;
  uint8_t spadsEnabled = 0;

  for (uint8_t i = 0; i < 48; i++) {
    if (i < firstSpadToEnable || spadsEnabled == spadCount) {
      refSpadMap[i / 8] &= ~(1 << (i % 8));
    } else if (refSpadMap[i / 8] & (1 << (i % 8))) {
      spadsEnabled++;
    }
  }

  if (!_writeMulti(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, refSpadMap, 6)) {
    return false;
  }

  _loadTuningSettings();

  _writeReg(SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
  _writeReg(GPIO_HV_MUX_ACTIVE_HIGH, _readReg(GPIO_HV_MUX_ACTIVE_HIGH) & ~0x10);
  _writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);

  _measurementTimingBudgetUs = _getMeasurementTimingBudget();

  _writeReg(SYSTEM_SEQUENCE_CONFIG, 0xE8);
  if (!_setMeasurementTimingBudget(_measurementTimingBudgetUs)) {
    return false;
  }

  _writeReg(SYSTEM_SEQUENCE_CONFIG, 0x01);
  if (!_performSingleRefCalibration(0x40)) {
    return false;
  }

  _writeReg(SYSTEM_SEQUENCE_CONFIG, 0x02);
  if (!_performSingleRefCalibration(0x00)) {
    return false;
  }

  _writeReg(SYSTEM_SEQUENCE_CONFIG, 0xE8);
  return !_didTimeout;
}

boolean ES_VL53L0X::_getSpadInfo(uint8_t *count, boolean *typeIsAperture) {
  _writeReg(0x80, 0x01);
  _writeReg(0xFF, 0x01);
  _writeReg(0x00, 0x00);
  _writeReg(0xFF, 0x06);
  _writeReg(0x83, _readReg(0x83) | 0x04);
  _writeReg(0xFF, 0x07);
  _writeReg(0x81, 0x01);
  _writeReg(0x80, 0x01);
  _writeReg(0x94, 0x6B);
  _writeReg(0x83, 0x00);

  uint32_t startMs = millis();
  while (_readReg(0x83) == 0x00) {
    if (_timeoutExpired(startMs)) {
      return false;
    }
  }

  _writeReg(0x83, 0x01);
  uint8_t tmp = _readReg(0x92);

  *count = tmp & 0x7F;
  *typeIsAperture = (tmp >> 7) & 0x01;

  _writeReg(0x81, 0x00);
  _writeReg(0xFF, 0x06);
  _writeReg(0x83, _readReg(0x83) & ~0x04);
  _writeReg(0xFF, 0x01);
  _writeReg(0x00, 0x01);
  _writeReg(0xFF, 0x00);
  _writeReg(0x80, 0x00);

  return true;
}

boolean ES_VL53L0X::_performSingleRefCalibration(uint8_t vhvInitByte) {
  _writeReg(SYSRANGE_START, 0x01 | vhvInitByte);

  uint32_t startMs = millis();
  while ((_readReg(RESULT_INTERRUPT_STATUS) & 0x07) == 0) {
    if (_timeoutExpired(startMs)) {
      return false;
    }
  }

  _writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
  _writeReg(SYSRANGE_START, 0x00);
  return true;
}

void ES_VL53L0X::_loadTuningSettings() {
  _writeReg(0xFF, 0x01);
  _writeReg(0x00, 0x00);
  _writeReg(0xFF, 0x00);
  _writeReg(0x09, 0x00);
  _writeReg(0x10, 0x00);
  _writeReg(0x11, 0x00);
  _writeReg(0x24, 0x01);
  _writeReg(0x25, 0xFF);
  _writeReg(0x75, 0x00);
  _writeReg(0xFF, 0x01);
  _writeReg(0x4E, 0x2C);
  _writeReg(0x48, 0x00);
  _writeReg(0x30, 0x20);
  _writeReg(0xFF, 0x00);
  _writeReg(0x30, 0x09);
  _writeReg(0x54, 0x00);
  _writeReg(0x31, 0x04);
  _writeReg(0x32, 0x03);
  _writeReg(0x40, 0x83);
  _writeReg(0x46, 0x25);
  _writeReg(0x60, 0x00);
  _writeReg(0x27, 0x00);
  _writeReg(0x50, 0x06);
  _writeReg(0x51, 0x00);
  _writeReg(0x52, 0x96);
  _writeReg(0x56, 0x08);
  _writeReg(0x57, 0x30);
  _writeReg(0x61, 0x00);
  _writeReg(0x62, 0x00);
  _writeReg(0x64, 0x00);
  _writeReg(0x65, 0x00);
  _writeReg(0x66, 0xA0);
  _writeReg(0xFF, 0x01);
  _writeReg(0x22, 0x32);
  _writeReg(0x47, 0x14);
  _writeReg(0x49, 0xFF);
  _writeReg(0x4A, 0x00);
  _writeReg(0xFF, 0x00);
  _writeReg(0x7A, 0x0A);
  _writeReg(0x7B, 0x00);
  _writeReg(0x78, 0x21);
  _writeReg(0xFF, 0x01);
  _writeReg(0x23, 0x34);
  _writeReg(0x42, 0x00);
  _writeReg(0x44, 0xFF);
  _writeReg(0x45, 0x26);
  _writeReg(0x46, 0x05);
  _writeReg(0x40, 0x40);
  _writeReg(0x0E, 0x06);
  _writeReg(0x20, 0x1A);
  _writeReg(0x43, 0x40);
  _writeReg(0xFF, 0x00);
  _writeReg(0x34, 0x03);
  _writeReg(0x35, 0x44);
  _writeReg(0xFF, 0x01);
  _writeReg(0x31, 0x04);
  _writeReg(0x4B, 0x09);
  _writeReg(0x4C, 0x05);
  _writeReg(0x4D, 0x04);
  _writeReg(0xFF, 0x00);
  _writeReg(0x44, 0x00);
  _writeReg(0x45, 0x20);
  _writeReg(0x47, 0x08);
  _writeReg(0x48, 0x28);
  _writeReg(0x67, 0x00);
  _writeReg(0x70, 0x04);
  _writeReg(0x71, 0x01);
  _writeReg(0x72, 0xFE);
  _writeReg(0x76, 0x00);
  _writeReg(0x77, 0x00);
  _writeReg(0xFF, 0x01);
  _writeReg(0x0D, 0x01);
  _writeReg(0xFF, 0x00);
  _writeReg(0x80, 0x01);
  _writeReg(0x01, 0xF8);
  _writeReg(0xFF, 0x01);
  _writeReg(0x8E, 0x01);
  _writeReg(0x00, 0x01);
  _writeReg(0xFF, 0x00);
  _writeReg(0x80, 0x00);
}

uint16_t ES_VL53L0X::_readRawSingle() {
  _writeReg(0x80, 0x01);
  _writeReg(0xFF, 0x01);
  _writeReg(0x00, 0x00);
  _writeReg(0x91, _stopVariable);
  _writeReg(0x00, 0x01);
  _writeReg(0xFF, 0x00);
  _writeReg(0x80, 0x00);

  _writeReg(SYSRANGE_START, 0x01);

  uint32_t startMs = millis();
  while (_readReg(SYSRANGE_START) & 0x01) {
    if (_timeoutExpired(startMs)) {
      return ES_VL53L0X_INVALID_DISTANCE;
    }
  }

  return _readRawResult();
}

uint16_t ES_VL53L0X::_readRawResult() {
  uint32_t startMs = millis();
  while ((_readReg(RESULT_INTERRUPT_STATUS) & 0x07) == 0) {
    if (_timeoutExpired(startMs)) {
      return ES_VL53L0X_INVALID_DISTANCE;
    }
  }

  uint16_t range = _readReg16(RESULT_RANGE_STATUS + 10);
  _writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);

  return range;
}

boolean ES_VL53L0X::_setMeasurementTimingBudget(uint32_t budgetUs) {
  if (budgetUs < MIN_TIMING_BUDGET_US) {
    return false;
  }

  SequenceStepEnables enables;
  SequenceStepTimeouts timeouts;

  uint32_t usedBudgetUs = START_OVERHEAD_US + END_OVERHEAD_US;

  _getSequenceStepEnables(&enables);
  _getSequenceStepTimeouts(&enables, &timeouts);

  if (enables.tcc) {
    usedBudgetUs += timeouts.msrcDssTccUs + TCC_OVERHEAD_US;
  }

  if (enables.dss) {
    usedBudgetUs += 2 * (timeouts.msrcDssTccUs + DSS_OVERHEAD_US);
  } else if (enables.msrc) {
    usedBudgetUs += timeouts.msrcDssTccUs + MSRC_OVERHEAD_US;
  }

  if (enables.preRange) {
    usedBudgetUs += timeouts.preRangeUs + PRE_RANGE_OVERHEAD_US;
  }

  if (enables.finalRange) {
    usedBudgetUs += FINAL_RANGE_OVERHEAD_US;

    if (usedBudgetUs > budgetUs) {
      return false;
    }

    uint32_t finalRangeTimeoutUs = budgetUs - usedBudgetUs;
    uint32_t finalRangeTimeoutMclks = _timeoutMicrosecondsToMclks(finalRangeTimeoutUs, timeouts.finalRangeVcselPeriodPclks);

    if (enables.preRange) {
      finalRangeTimeoutMclks += timeouts.preRangeMclks;
    }

    _writeReg16(FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, _encodeTimeout(finalRangeTimeoutMclks));
    _measurementTimingBudgetUs = budgetUs;
  }

  return true;
}

uint32_t ES_VL53L0X::_getMeasurementTimingBudget() {
  SequenceStepEnables enables;
  SequenceStepTimeouts timeouts;

  uint32_t budgetUs = START_OVERHEAD_US + END_OVERHEAD_US;

  _getSequenceStepEnables(&enables);
  _getSequenceStepTimeouts(&enables, &timeouts);

  if (enables.tcc) {
    budgetUs += timeouts.msrcDssTccUs + TCC_OVERHEAD_US;
  }

  if (enables.dss) {
    budgetUs += 2 * (timeouts.msrcDssTccUs + DSS_OVERHEAD_US);
  } else if (enables.msrc) {
    budgetUs += timeouts.msrcDssTccUs + MSRC_OVERHEAD_US;
  }

  if (enables.preRange) {
    budgetUs += timeouts.preRangeUs + PRE_RANGE_OVERHEAD_US;
  }

  if (enables.finalRange) {
    budgetUs += timeouts.finalRangeUs + FINAL_RANGE_OVERHEAD_US;
  }

  _measurementTimingBudgetUs = budgetUs;
  return budgetUs;
}

void ES_VL53L0X::_getSequenceStepEnables(SequenceStepEnables *enables) {
  uint8_t sequenceConfig = _readReg(SYSTEM_SEQUENCE_CONFIG);

  enables->tcc = (sequenceConfig & SEQUENCE_STEP_TCC) != 0;
  enables->dss = (sequenceConfig & SEQUENCE_STEP_DSS) != 0;
  enables->msrc = (sequenceConfig & SEQUENCE_STEP_MSRC) != 0;
  enables->preRange = (sequenceConfig & SEQUENCE_STEP_PRE_RANGE) != 0;
  enables->finalRange = (sequenceConfig & SEQUENCE_STEP_FINAL_RANGE) != 0;
}

void ES_VL53L0X::_getSequenceStepTimeouts(const SequenceStepEnables *enables, SequenceStepTimeouts *timeouts) {
  timeouts->preRangeVcselPeriodPclks = _readVcselPeriodPclks(false);
  timeouts->msrcDssTccMclks = _readReg(MSRC_CONFIG_TIMEOUT_MACROP) + 1;
  timeouts->msrcDssTccUs = _timeoutMclksToMicroseconds(timeouts->msrcDssTccMclks, timeouts->preRangeVcselPeriodPclks);

  timeouts->preRangeMclks = _decodeTimeout(_readReg16(PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI));
  timeouts->preRangeUs = _timeoutMclksToMicroseconds(timeouts->preRangeMclks, timeouts->preRangeVcselPeriodPclks);

  timeouts->finalRangeVcselPeriodPclks = _readVcselPeriodPclks(true);
  timeouts->finalRangeMclks = _decodeTimeout(_readReg16(FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI));

  if (enables->preRange) {
    timeouts->finalRangeMclks -= timeouts->preRangeMclks;
  }

  timeouts->finalRangeUs = _timeoutMclksToMicroseconds(timeouts->finalRangeMclks, timeouts->finalRangeVcselPeriodPclks);
}

uint8_t ES_VL53L0X::_readVcselPeriodPclks(boolean finalRange) {
  return _decodeVcselPeriod(_readReg(finalRange ? FINAL_RANGE_CONFIG_VCSEL_PERIOD : PRE_RANGE_CONFIG_VCSEL_PERIOD));
}

boolean ES_VL53L0X::_writeReg(uint8_t reg, uint8_t value) {
  _bus->beginTransmission(_address);
  _bus->write(reg);
  _bus->write(value);
  _lastStatus = _bus->endTransmission();
  return _lastStatus == 0;
}

boolean ES_VL53L0X::_writeReg16(uint8_t reg, uint16_t value) {
  _bus->beginTransmission(_address);
  _bus->write(reg);
  _bus->write((value >> 8) & 0xFF);
  _bus->write(value & 0xFF);
  _lastStatus = _bus->endTransmission();
  return _lastStatus == 0;
}

boolean ES_VL53L0X::_writeMulti(uint8_t reg, const uint8_t *src, uint8_t count) {
  _bus->beginTransmission(_address);
  _bus->write(reg);

  for (uint8_t i = 0; i < count; i++) {
    _bus->write(src[i]);
  }

  _lastStatus = _bus->endTransmission();
  return _lastStatus == 0;
}

uint8_t ES_VL53L0X::_readReg(uint8_t reg) {
  uint8_t value = 0;
  _readMulti(reg, &value, 1);
  return value;
}

uint16_t ES_VL53L0X::_readReg16(uint8_t reg) {
  uint8_t data[2] = {0, 0};
  _readMulti(reg, data, 2);
  return ((uint16_t)data[0] << 8) | data[1];
}

boolean ES_VL53L0X::_readMulti(uint8_t reg, uint8_t *dst, uint8_t count) {
  _bus->beginTransmission(_address);
  _bus->write(reg);
  _lastStatus = _bus->endTransmission(false);

  if (_lastStatus != 0) {
    return false;
  }

  uint8_t received = _bus->requestFrom(_address, count);

  if (received != count) {
    _didTimeout = true;
    while (_bus->available()) {
      _bus->read();
    }
    return false;
  }

  for (uint8_t i = 0; i < count; i++) {
    dst[i] = _bus->read();
  }

  return true;
}

boolean ES_VL53L0X::_timeoutExpired(uint32_t startMs) {
  if (_timeout == 0) {
    return false;
  }

  if ((uint32_t)(millis() - startMs) > _timeout) {
    _didTimeout = true;
    return true;
  }

  return false;
}

uint16_t ES_VL53L0X::_decodeTimeout(uint16_t regVal) {
  return ((regVal & 0x00FF) << ((regVal & 0xFF00) >> 8)) + 1;
}

uint16_t ES_VL53L0X::_encodeTimeout(uint32_t timeoutMclks) {
  uint32_t lsByte = 0;
  uint16_t msByte = 0;

  if (timeoutMclks > 0) {
    lsByte = timeoutMclks - 1;

    while ((lsByte & 0xFFFFFF00) > 0) {
      lsByte >>= 1;
      msByte++;
    }

    return (msByte << 8) | (lsByte & 0xFF);
  }

  return 0;
}

uint32_t ES_VL53L0X::_timeoutMclksToMicroseconds(uint16_t timeoutMclks, uint8_t vcselPeriodPclks) {
  uint32_t macroPeriodNs = _calcMacroPeriod(vcselPeriodPclks);
  return ((uint32_t)timeoutMclks * macroPeriodNs + 500) / 1000;
}

uint32_t ES_VL53L0X::_timeoutMicrosecondsToMclks(uint32_t timeoutUs, uint8_t vcselPeriodPclks) {
  uint32_t macroPeriodNs = _calcMacroPeriod(vcselPeriodPclks);
  return ((timeoutUs * 1000) + (macroPeriodNs / 2)) / macroPeriodNs;
}

uint32_t ES_VL53L0X::_calcMacroPeriod(uint8_t vcselPeriodPclks) {
  return (((uint32_t)2304 * vcselPeriodPclks * 1655) + 500) / 1000;
}

uint8_t ES_VL53L0X::_decodeVcselPeriod(uint8_t regVal) {
  return (regVal + 1) << 1;
}
