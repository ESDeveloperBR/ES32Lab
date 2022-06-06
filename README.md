# ES32Lab biblioteca

Para o funcionamento da biblioteca ES32Lab é necessário atualmente a instalação obrigatória da dependência [TFT_eSPI_ES32Lab](https://github.com/ederjsantini/TFT_eSPI_ES32Lab), que é uma variação da biblioteca TFT_eSPI de licença MIT desenvolvida por [Bobmer]( https://github.com/Bodmer).

**ATENÇÃO!** Logo para o funcionamento da biblioteca ES32Lab, torna-se indispensável o download da biblioteca [TFT_eSPI_ES32Lab](https://github.com/ederjsantini/TFT_eSPI_ES32Lab).

## Endereço das GPIOs do ESP32 com conexões aos circuitos da ES32Lab

Para facilitar a programação da ES32Lab foram criadas diversas constantes com os endereços de todas as GPIOs do ESP32 que estão conectadas aos diversos circuitos da ES32Lab, dispensando assim que o programador precise memorizar as GPIOs que estão ligadas aos circuitos da ES32Lab, são elas:
- P_KEYBOARD = GPIO33
- P_LED_GREEN = GPIO17
- P_LED_YELLON= GPIO16
- P_LED_RED = GPIO13
- P_LED_BLUE = GPIO12
- P_POT1 = GPIO36
- P_POT2 = GPIO39
- P_VOLTAGE_SENSOR = GPIO34
- P_BUZZER = GPIO25
- P_DAC1 = GPIO25  // Se a DAC for utilizada como áudio, será o canal L
- P_DAC2 = GPIO26  // Se a DAC for utilizada como áudio, será o canal R
- P_I2S_DOUT = GPIO25
- P_I2S_LRC = GPIO26
- P_I2S_BCLK = GPIO27
- P_SDA = GPIO21
- P_SCL = GPIO22
- P_TX0 = GPIO1
- P_RX0 = GPIO3
- P_TX2 = GPIO17
- P_RX2 = GPIO16
- P_MOSI = GPIO23
- P_MISSO = GPIO19
- P_SCK = GPIO18
- P_SD_CS = GPIO5

Para exemplificar a utilização das constantes citadas acima, usarei como exemplo um código para piscar de forma intermitente o LED verde da ES32Lab.
```C++
#include <ES32Lab.h>
void setup() {
  pinMode(P_LED_GREEN , OUTPUT);
}
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);
  delay(500);

  digitalWrite(P_LED_GREEN, LOW);
  delay(500);
}
```
Nesse exemplo a GPIO utilizada para controlar o LED verde foi a 17 que pode ser substituída pela constante P_LED_GREEN, dispensando assim que o programador tenha que memorizar todos os endereços GPIOs utilizadas pela ES32Lab.
Todas as constantes de endereços seguem a mesma linha de raciocínio em sua nomenclatura, tonando assim mais intuitiva sua utilização. No exemplo abaixo explicarei o raciocíno a qual foi utilizado para a criação te dotas as constantes de GPIOs na ES32Lab.
P_LED_GREEN: 
* “P”: Pino;
* “LED”: Circuito na ES32Lab;
* “GREEN”: Cor do LED;

Se seguirmos essa linha de raciocínio, a constante de controle do LED vermelho será a P_LED_RED, a do buzzer será a P_BUZZER, potenciômetro 1 será P_POT1 e assim por diante.

## Conjunto de classes contidas na LIB ES32Lab
A biblioteca da ES32Lab conta com diversas classes para programação orientada a objeto, que tem como objetivo facilitar a criação de programas em C++ para controle da placa de desenvolvimento e prototipagem ES32Lab, são elas:
* AnalogKeyboard;
* BuzzerESP;
* DigitalButton;
* FileManager;
* TFT_Plus;
* TimeInterval;

### AnalogKeyboard
A classe _AnalogKeyboard_ é responsável pelo funcionamento do teclado analógico de 5 teclas da placa ES32Lab, sua estrutura é constituída da seguinte forma:
#### Construtor
_AnalogKeyboard(uint8_t pinKeyboard, uint16_t addressKey0 = 0, uint16_t addressKey1 = 870, uint16_t addressKey2 = 1657, uint16_t addressKey3 = 2457, uint16_t addressKey4 = 3322, uint8_t readingAccuracy = 20 );_

No momento da criação de um objeto derivado da classe _AnalogKeyboard_ pode-se passar alguns valores de ajustes, como:
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
