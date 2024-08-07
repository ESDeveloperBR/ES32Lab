/*
  Autor..: ES Developer
  GitHub.: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Criação: 05/31/2022       (mm/dd/yyyy)
*/
#include "AnalogKeyboardb.h"

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< _getIndex >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Mapeia os valores analógicos para índices no array | Maps analog values to indices in the array
uint8_t AnalogKeyboard::_getIndex(uint16_t address) {
    switch (address) {
        case KEY_CENTER: return 0;
        case KEY_UP: return 1;
        case KEY_RIGHT: return 2;
        case KEY_DOWN: return 3;
        case KEY_LEFT: return 4;
        case KEY_UP_RIGHT: return 5;
        case KEY_UP_DOWN: return 6;
        case KEY_UP_LEFT: return 7;
        case KEY_DOWN_RIGHT: return 8;
        case KEY_DOWN_LEFT: return 9;
        case KEY_LEFT_RIGHT: return 10;
        case KEY_UP_DOWN_RIGHT: return 11;
        case KEY_UP_DOWN_LEFT: return 12;
        case KEY_UP_RIGHT_LEFT: return 13;
        case KEY_DOWN_RIGHT_LEFT: return 14;
        case KEY_UP_DOWN_RIGHT_LEFT: return 15;
        default: return 0xFF; // Retorna um valor inválido se o endereço não for encontrado | Returns an invalid value if the address is not found
    }
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Constructor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
AnalogKeyboard::AnalogKeyboard(uint8_t pinKeyboard, uint8_t readingAccuracy) {
    _pinKeyboard = pinKeyboard;
    _readingAccuracy = readingAccuracy;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Hold >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * @brief Verifica se a tecla está sendo pressionada. | Checks if the key is being pressed.
 * 
 * @param key Valor analógico da tecla. | Analog value of the key.
 * @return `true` se a tecla está sendo pressionada ou `false` se a tecla não está sendo pressionada.
 * @return | `true` if the key is being pressed or `false` if the key is not being pressed.
 */
boolean AnalogKeyboard::hold(uint16_t key) {
    uint16_t readValue = analogRead(_pinKeyboard);
    uint16_t toleranceValue = key * (float(_readingAccuracy) / 100);

    if (((key - toleranceValue) <= readValue) && (readValue <= (key + toleranceValue))) {
        return true;
    }
    return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Press >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * @brief Verifica se a tecla foi pressionada. | Checks if the key was pressed.
 * 
 * @param key Valor analógico da tecla. | Analog value of the key.
 * @return `true` se a tecla foi pressionada ou `false` se a tecla não foi pressionada.
 * @return | `true` if the key was pressed or `false` if the key was not pressed.
 */
boolean AnalogKeyboard::press(uint16_t key) {
    uint8_t index = _getIndex(key);
    if (index == 0xFF) return false; // Verifica se o endereço é válido

    if (!hold(key) && !_keyPress[index]) {
        _keyPress[index] = true;
    } else if (hold(key) && _keyPress[index]) {
        _keyPress[index] = false;
        return true;
    }
    return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Release >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * @brief Verifica se a tecla foi solta. | Checks if the key was released.
 * 
 * @param key Valor analógico da tecla. | Analog value of the key.
 * @return `true` se a tecla foi solta ou `false` se a tecla não foi solta.
 * @return | `true` if the key was released or `false` if the key was not released.
 */
boolean AnalogKeyboard::release(uint16_t key) {
    uint8_t index = _getIndex(key);
    if (index == 0xFF) return false; // Verifica se o endereço é válido

    if (!hold(key) && !_keyRelease[index]) {
        _keyRelease[index] = true;
        return true;
    } else if (hold(key) && _keyRelease[index]) {
        _keyRelease[index] = false;
    }
    return false;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Debug Read >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * @brief Método para depuração que lê e imprime o valor atual da leitura analógica. | Debug method that reads and prints the current analog read value.
 */
void AnalogKeyboard::debugRead() {
    const int numSamples = 200; // Número de amostras para calcular as estatísticas
    uint16_t readings[numSamples];
    uint16_t minValue = 65535; // Valor máximo possível para uint16_t
    uint16_t maxValue = 0;
    uint32_t sumValues = 0;

    // Coleta de amostras
    for (int i = 0; i < numSamples; i++) {
        readings[i] = analogRead(_pinKeyboard);
        delay(10); // Pequeno atraso entre as leituras
    }

    // Calcula o menor, maior e soma dos valores
    for (int i = 0; i < numSamples; i++) {
        uint16_t readValue = readings[i];
        if (readValue < minValue) minValue = readValue;
        if (readValue > maxValue) maxValue = readValue;
        sumValues += readValue;
    }

    // Calcula a média
    float averageValue = sumValues / float(numSamples);

    // Imprime valores
    Serial.print("Min: ");
    Serial.print(minValue);
    Serial.print(", Max: ");
    Serial.print(maxValue);
    Serial.print(", Media: ");
    Serial.println(averageValue, 0);
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>