| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----


# Classe AnalogKeyboard
A classe `AnalogKeyboard` é responsável pelo funcionamento do teclado analógico de 5 teclas da placa ES32Lab. Sua estrutura é constituída da seguinte forma:


## Construtor
```cpp
AnalogKeyboard(uint8_t pinKeyboard, uint8_t readingAccuracy = 20);
```

Durante a criação de um objeto derivado da classe `AnalogKeyboard`, é possível passar alguns valores de ajuste, como:
- `pinKeyboard`: Pino (GPIO) ao qual será conectado o teclado analógico da placa ES32Lab ao ESP32. Exemplo: AnalogKeyboard keyboard(P_KEY);
- `readingAccuracy`: Ajuste de tolerância de erros na leitura analógica do teclado (em %). O valor padrão é o ideal para um bom funcionamento e, no geral, não é necessário mudá-lo;

### Exemplo
```cpp
AnalogKeyboard keyboard(P_KEY, 15); // Aumentando a precisão da leitura
```



## Métodos
- **boolean press(uint16_t key):** Retorna `true` se a tecla foi pressionada ou `false` se a tecla não foi pressionada. O valor analógico da tecla deverá ser repassado pelo parâmetro `key`;

- **boolean release(uint16_t key):** Retorna `true` se a tecla foi solta ou `false` se a tecla não foi solta. O valor analógico da tecla deverá ser repassado pelo parâmetro `key`;

- **boolean hold(uint16_t key):** Retorna `true` se a tecla está sendo pressionada ou `false` se a tecla não está sendo pressionada. O valor analógico da tecla deverá ser repassado pelo parâmetro `key`;

- **void debugRead():** Método para depuração que lê e imprime o valor atual da leitura analógica.




## Teclas Pré-Definidas da AnalogKeyboard
A classe `AnalogKeyboard` possui várias teclas pré-definidas que podem ser utilizadas para facilitar a interação com o teclado analógico da placa ES32Lab. Estas definições são representadas por constantes que mapeiam as teclas individuais e suas combinações. Abaixo estão as teclas pré-definidas:

### Teclas Individuais
Estas são as teclas básicas que podem ser usadas individualmente:

- **Centro:** Representado pela constante `KEY_CENTER`.
- **Cima:** Representado pela constante `KEY_UP`.
- **Direita:** Representado pela constante `KEY_RIGHT`.
- **Baixo:** Representado pela constante `KEY_DOWN`.
- **Esquerda:** Representado pela constante `KEY_LEFT`.






### Combinações de Teclas
Além das teclas individuais, a `classe AnalogKeyboard` permite a utilização de combinações de teclas. Essas combinações são úteis para implementar funcionalidades mais complexas que requerem múltiplas entradas simultâneas.

- **Cima + Direita:** Representado pela constante `KEY_UP_RIGHT`.
- **Cima + Baixo:** Representado pela constante `KEY_UP_DOWN`.
- **Cima + Esquerda:** Representado pela constante `KEY_UP_LEFT`.
- **Baixo + Direita:** Representado pela constante `KEY_DOWN_RIGHT`.
- **Baixo + Esquerda:** Representado pela constante `KEY_DOWN_LEFT`.
- **Esquerda + Direita:** Representado pela constante `KEY_LEFT_RIGHT`.
- **Cima + Baixo + Direita:** Representado pela constante `KEY_UP_DOWN_RIGHT`.
- **Cima + Baixo + Esquerda:** Representado pela constante `KEY_UP_DOWN_LEFT`.
- **Cima + Direita + Esquerda:** Representado pela constante `KEY_UP_RIGHT_LEFT`.
- **Baixo + Direita + Esquerda:** Representado pela constante `KEY_DOWN_RIGHT_LEFT`.
- **Cima + Baixo + Direita + Esquerda:** Representado pela constante `KEY_UP_DOWN_RIGHT_LEFT`.

**Atenção:** A combinação de teclas do teclado analógico da ES32Lab depende da calibração correta do leitor analógico do seu ESP32 para garantir leituras precisas. Se as combinações de teclas não atenderem às suas expectativas e apresentarem erros ou inconsistências, recomendamos o uso do método `void debugRead()`. Com os resultados obtidos através desse método, podemos obter uma leitura mais precisa dos valores analógicos do seu ESP32, permitindo uma configuração personalizada entre o seu ESP32 e o teclado da ES32Lab. Na seção de exemplos, incluímos um código-fonte que exemplifica a utilização do método `void debugRead()`.




## Exemplo prático:
Nesse exemplo, toda vez que for pressionada uma tecla, será enviada uma mensagem para o terminal serial informando qual tecla foi pressionada.

```cpp
#include <ES32Lab.h>

// Criação do objeto AnalogKeyboard, conectando ao pino específico
AnalogKeyboard keyboard(P_KEY);

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
}

void loop() {
  // Verificação do botão "Cima" (Up)
  if (keyboard.press(KEY_UP)) {
    Serial.println("Cima Pressionada | Up Pressed");
  }
  if (keyboard.hold(KEY_UP)) {
    Serial.println("Cima Segurada | Up Held");
  }
  if (keyboard.release(KEY_UP)) {
    Serial.println("Cima Solta | Up Released");
  }

  // Verificação do botão "Baixo" (Down)
  if (keyboard.press(KEY_DOWN)) {
    Serial.println("Baixo Pressionada | Down Pressed");
  }
  if (keyboard.hold(KEY_DOWN)) {
    Serial.println("Baixo Segurada | Down Held");
  }
  if (keyboard.release(KEY_DOWN)) {
    Serial.println("Baixo Solta | Down Released");
  }

  delay(100); // Atraso para evitar leituras excessivas
}

```



| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----