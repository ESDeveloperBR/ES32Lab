| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----




### Classe AnalogKeyboard
A classe `AnalogKeyboard` é responsável pelo funcionamento do teclado analógico de 5 teclas da placa ES32Lab. Sua estrutura é constituída da seguinte forma:

#### Construtor
_AnalogKeyboard(uint8_t pinKeyboard, uint16_t addressKey0 = 0, uint16_t addressKey1 = 870, uint16_t addressKey2 = 1657, uint16_t addressKey3 = 2457, uint16_t addressKey4 = 3322, uint8_t readingAccuracy = 21 );_

Durante a criação de um objeto derivado da classe `AnalogKeyboard`, é possível passar alguns valores de ajuste, como:

* _**pinKeyboard:**_ Pino (GPIO) ao qual será conectado o teclado analógico da placa ES32Lab ao ESP32. Exemplo: _ AnalogKeyboard keyboard(P_KEYBOARD);_
* _**addressKey0:**_ Endereço analógico para a leitura da tecla “0” do teclado analógico da placa ES32Lab. O valor padrão é o ideal para um bom funcionamento;
* _**addressKey1:**_ Endereço analógico para a leitura da tecla “1” do teclado analógico da placa ES32Lab. O valor padrão é o ideal para um bom funcionamento;
* _**addressKey2:**_ Endereço analógico para a leitura da tecla “2” do teclado analógico da placa ES32Lab. O valor padrão é o ideal para um bom funcionamento;
* _**addressKey3:**_ Endereço analógico para a leitura da tecla “3” do teclado analógico da placa ES32Lab. O valor padrão é o ideal para um bom funcionamento;
* _**addressKey4:**_ Endereço analógico para a leitura da tecla “4” do teclado analógico da placa ES32Lab. O valor padrão é o ideal para um bom funcionamento;
* _**readingAccuracy:**_ Ajuste de tolerância de erros na leitura analógica do teclado. O valor padrão é o ideal para um bom funcionamento;

#### Métodos
* _**boolean press(uint8_t key) :**_ Retorna verdadeiro quando **a tecla for pressionada.** O número da tecla deverá ser repassado pelo parâmetro _key_;
* _**boolean release(uint8_t key) :**_ Retorna verdadeiro quando **a tecla for solta.** O número da tecla deverá ser repassado pelo parâmetro _key_;
* _**boolean hold(uint8_t key):**_ Retorna verdadeiro enquanto **a tecla estiver pressionada.** O número da tecla deverá ser repassado pelo parâmetro _key_;

#### Exemplo prático:
Nesse exemplo toda vez que for pressionado uma tecla, será enviado uma mensagem para o terminal serial informando qual tecla foi pressionada.
```C++
#include <ES32Lab.h>
AnalogKeyboard keyboard(P_KEYBOARD);
void setup() {
  Serial.begin(115200);
}
void loop() {
  if(keyboard.press(0)){
    Serial.println("Key 0 - PRESS");
  }
  if(keyboard.press(1)){
    Serial.println("Key 1 - PRESS");
  }
  if(keyboard.press(2)){
    Serial.println("Key 2 - PRESS");
  }
  if(keyboard.press(3)){
    Serial.println("Key 3 - PRESS");
  }
  if(keyboard.press(4)){
    Serial.println("Key 4 - PRESS");
  }
}
```






-----
| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |