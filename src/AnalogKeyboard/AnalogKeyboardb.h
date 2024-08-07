/*
  Autor..: ES Developer
  GitHub.: https://github.com/ESDeveloperBR/ES32Lab
  YouTube: https://www.youtube.com/@ESDeveloperBR
  Criação: 05/31/2022       (mm/dd/yyyy)
*/

#ifndef _ANALOGKEYBOARD_h
#define _ANALOGKEYBOARD_h

#include <Arduino.h>

#define ANALOGKEYBOARD_VERSION "0.4.2 date 08/07/2024" // (mm/dd/yyyy)

// Definindo as teclas individuais | Defining individual keys
#define KEY_CENTER 0     // Centro | Center
#define KEY_UP 769       // Cima | Up
#define KEY_RIGHT 1585   // Direita | Right
#define KEY_DOWN 2400    // Baixo | Down
#define KEY_LEFT 3323    // Esquerda | Left

// Definindo as combinações de teclas | Defining key combinations
#define KEY_UP_RIGHT 561                // Cima + Direita | Up + Right
#define KEY_UP_DOWN 659                 // Cima + Baixo | Up + Down
#define KEY_UP_LEFT 727                 // Cima + Esquerda | Up + Left
#define KEY_DOWN_RIGHT 1218             // Baixo + Direita | Down + Right
#define KEY_DOWN_LEFT 2097              // Baixo + Esquerda | Down + Left
#define KEY_LEFT_RIGHT 1432             // Esquerda + Direita | Left + Right
#define KEY_UP_DOWN_RIGHT 492           // Cima + Baixo + Direita | Up + Down + Right
#define KEY_UP_DOWN_LEFT 628            // Cima + Baixo + Esquerda | Up + Down + Left
#define KEY_UP_RIGHT_LEFT 537           // Cima + Direita + Esquerda | Up + Right + Left
#define KEY_DOWN_RIGHT_LEFT 1126        // Baixo + Direita + Esquerda | Down + Right + Left
#define KEY_UP_DOWN_RIGHT_LEFT 470      // Cima + Baixo + Direita + Esquerda | Up + Down + Right + Left

/**
 * @brief Classe AnalogKeyboard para ler e gerenciar um teclado analógico. | AnalogKeyboard class to read and manage an analog keyboard.
 * 
 * @param pinKeyboard Pino de leitura analógica do teclado. | Analog read pin of the keyboard.
 * @param readingAccuracy Precisão de leitura dos valores analógicos (em %). | Reading accuracy of analog values (in %).
 *
 */
class AnalogKeyboard {
    private:    
        uint8_t  _pinKeyboard;    // Pino de leitura do teclado | Keyboard read pin
        boolean  _keyPress[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}; // Verifica se a tecla foi pressionada | Checks if the key is pressed
        boolean  _keyRelease[16] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};  // Verifica se a tecla foi solta | Checks if the key is released
        uint8_t  _readingAccuracy;  // Precisão de leitura dos valores analógicos | Reading accuracy of analog values
        uint8_t  _getIndex(uint16_t address); // Retorna o endereço do Array correspodente a determinada tecla. | Returns the array index corresponding to a specific key.
    
    public:
        AnalogKeyboard(uint8_t pinKeyboard, uint8_t readingAccuracy = 20);
        boolean hold(uint16_t key);
        boolean press(uint16_t key);
        boolean release(uint16_t key);
        void debugRead();
};

#endif
