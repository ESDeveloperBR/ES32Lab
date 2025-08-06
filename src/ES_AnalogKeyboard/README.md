| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----

# Documentação da Classe ES_AnalogKeyboard

A classe `ES_AnalogKeyboard` é um componente prático e versátil da biblioteca ES32Lab, projetada para simplificar a leitura e o gerenciamento de teclados analógicos de 5 teclas (com suporte a múltiplas combinações) utilizando microcontroladores ESP32. Ela abstrai toda a lógica de detecção, tratamento de ruído e estado das teclas, tornando o uso prático, confiável e eficiente para aplicações como interfaces de usuário, robótica, automação e projetos educacionais.

Principais recursos:
- **Leitura precisa de teclas analógicas**: Detecta pressionamento, manutenção e liberação de teclas.
- **Suporte a combinações de teclas**: Permite identificar múltiplas teclas pressionadas simultaneamente.
- **Calibração facilitada**: Método de depuração para identificar valores analógicos reais.
- **Configuração simples**: Parâmetros padrão para uso imediato.
- **Interface intuitiva**: Métodos claros para iniciantes e flexibilidade para desenvolvedores experientes.

---

## Índice

1. [Construtor](#construtor)
2. [Exemplos de Instanciação](#exemplos-de-instanciação)
3. [Métodos da Classe](#Métodos-da-Classe)
   - [press(key)](#boolean-pressuint16_t-key)
   - [hold(key)](#boolean-holduint16_t-key)
   - [release(key)](#boolean-releaseuint16_t-key)
   - [debugRead()](#void-debugread)
4. [Teclas Pré-Definidas](#Teclas-Pré-Definidas)
   - [Teclas Individuais](#teclas-individuais)
   - [Combinações de Teclas](#Combinações-de-Teclas)
5. [Exemplo Prático](#Exemplo-Prático)
6. [Dicas e Observações](#Dicas-e-Observações)

---

## Construtor

O construtor da classe `ES_AnalogKeyboard` inicializa o objeto responsável pela leitura do teclado analógico. Ele já possui valores padrão que atendem à maioria das aplicações, tornando a utilização simples e rápida.

```cpp
ES_AnalogKeyboard(uint8_t pinKeyboard = P_KEYBOARD, uint8_t readingAccuracy = 20);
```

### Parâmetros
- **`pinKeyboard`** *(padrão: P_KEYBOARD)*: Pino (GPIO) analógico do ESP32 ao qual o teclado está conectado. Por padrão, `P_KEYBOARD` é definido como **33**, ou seja, o teclado normalmente é ligado à GPIO 33 do ESP32. Use o valor padrão para placas ES32Lab ou defina o pino conforme sua montagem.
- **`readingAccuracy`** *(padrão: 20)*: Percentual de tolerância para variações na leitura analógica (em %). O valor padrão (20%) é recomendado para a maioria dos casos, pois oferece boa estabilidade e confiabilidade. Ajuste este valor se houver ruído, variações inesperadas ou se desejar maior precisão na detecção das teclas.

---

## Exemplos de Instanciação
- Instanciação mais comum (usando todos os parâmetros padrão):
  ```cpp
  ES_AnalogKeyboard keyboard;
  ```
- Instanciando com pino específico:
  ```cpp
  ES_AnalogKeyboard keyboard(32); // Usa GPIO 32
  ```
- Instanciando com ajuste de precisão:
  ```cpp
  ES_AnalogKeyboard keyboard(P_KEYBOARD, 15); // Maior precisão na leitura
  ```

> **Dica:** Na maioria dos projetos, basta instanciar o objeto sem parâmetros, aproveitando os valores padrão. Só altere os parâmetros se houver necessidade específica de hardware ou ajuste fino na leitura.

---

## Métodos da Classe

### `boolean press(uint16_t key)`
Retorna `true` apenas no instante em que a tecla é pressionada (transição de não pressionada para pressionada). Útil para detectar eventos de clique.
- **Parâmetro:** `key` — valor analógico da tecla (use as constantes pré-definidas).
- **Uso típico:**
  ```cpp
  if (keyboard.press(KEY_UP)) {
    // Executa ação ao pressionar "Cima"
  }
  ```

### `boolean hold(uint16_t key)`
Retorna `true` enquanto a tecla está sendo pressionada (mantida). Útil para ações contínuas enquanto o botão está pressionado.
- **Parâmetro:** `key` — valor analógico da tecla.

### `boolean release(uint16_t key)`
Retorna `true` apenas no instante em que a tecla é solta (transição de pressionada para não pressionada). Útil para detectar eventos de soltura.
- **Parâmetro:** `key` — valor analógico da tecla.

### `void debugRead()`
Realiza múltiplas leituras do pino analógico, calcula estatísticas (mínimo, máximo, média) e imprime no terminal serial. Ideal para calibrar e identificar os valores analógicos reais das teclas no seu hardware.

---

## Teclas Pré-Definidas

A classe oferece constantes para facilitar o uso das teclas e suas combinações. Utilize sempre as constantes para garantir compatibilidade e legibilidade.

### Teclas Individuais
- **Centro:** `KEY_CENTER`
- **Cima:** `KEY_UP`
- **Direita:** `KEY_RIGHT`
- **Baixo:** `KEY_DOWN`
- **Esquerda:** `KEY_LEFT`

### Combinações de Teclas
Permite detectar múltiplas teclas pressionadas simultaneamente, ampliando as possibilidades de interação:
- **Cima + Direita:** `KEY_UP_RIGHT`
- **Cima + Baixo:** `KEY_UP_DOWN`
- **Cima + Esquerda:** `KEY_UP_LEFT`
- **Baixo + Direita:** `KEY_DOWN_RIGHT`
- **Baixo + Esquerda:** `KEY_DOWN_LEFT`
- **Esquerda + Direita:** `KEY_LEFT_RIGHT`
- **Cima + Baixo + Direita:** `KEY_UP_DOWN_RIGHT`
- **Cima + Baixo + Esquerda:** `KEY_UP_DOWN_LEFT`
- **Cima + Direita + Esquerda:** `KEY_UP_RIGHT_LEFT`
- **Baixo + Direita + Esquerda:** `KEY_DOWN_RIGHT_LEFT`
- **Cima + Baixo + Direita + Esquerda:** `KEY_UP_DOWN_RIGHT_LEFT`

---

## Exemplo Prático

O exemplo abaixo mostra como detectar eventos de pressionar, segurar e soltar para as teclas "Cima" e "Baixo". Mensagens são enviadas ao terminal serial conforme o estado das teclas.

```cpp
#include <ES32Lab.h>

// Instancia o teclado analógico no pino definido
ES_AnalogKeyboard keyboard;

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
}

void loop() {
  // Tecla "Cima"
  if (keyboard.press(KEY_UP)) {
    Serial.println("Cima Pressionada | Up Pressed");
  }
  if (keyboard.hold(KEY_UP)) {
    Serial.println("Cima Segurada | Up Held");
  }
  if (keyboard.release(KEY_UP)) {
    Serial.println("Cima Solta | Up Released");
  }

  // Tecla "Baixo"
  if (keyboard.press(KEY_DOWN)) {
    Serial.println("Baixo Pressionada | Down Pressed");
  }
  if (keyboard.hold(KEY_DOWN)) {
    Serial.println("Baixo Segurada | Down Held");
  }
  if (keyboard.release(KEY_DOWN)) {
    Serial.println("Baixo Solta | Down Released");
  }

  delay(100); // Evita leituras excessivas
}
```

---

## Dicas e Observações

- Sempre utilize as constantes pré-definidas para garantir precisão e compatibilidade.
- Caso as combinações de teclas apresentem inconsistências, utilize o método `debugRead()` para calibrar os valores analógicos conforme seu hardware.
- O uso dos parâmetros padrão é suficiente para a maioria dos projetos. Ajuste apenas se necessário.
- O método `debugRead()` é fundamental para identificar ruídos ou desvios nas leituras e ajustar a tolerância (`readingAccuracy`).

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |