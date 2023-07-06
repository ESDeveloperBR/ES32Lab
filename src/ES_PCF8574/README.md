| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----

# Documentação da Classe ES_PCF8574

A classe `ES_PCF8574` é usada para controlar a comunicação com o expansor de porta PCF8574 no ESP32. Ela fornece métodos para interagir com as GPIOs do PCF8574 e também inclui um simulador PWM.

## Construtor

### `ES_PCF8574(uint8_t address)`

Inicializa uma instância da classe `ES_PCF8574` com o endereço fornecido do PCF8574.

- Parâmetros:
  - `address`: Endereço do PCF8574 no protocolo de comunicação I2C.

## Configuração

### `boolean begin(boolean pwmSimulation)`

Inicializa a comunicação I2C e configura o PCF8574.

- Parâmetros:
  - `pwmSimulation`: Quando verdadeiro, ativa o simulador PWM através do expansor I2C.

- Retorno:
  - `true` se a comunicação for inicializada com sucesso, caso contrário, `false`.

## Métodos GPIO

### `void digitalWrite(uint8_t pin, boolean value)`

Define o valor lógico (HIGH ou LOW) para uma GPIO específica do PCF8574.

- Parâmetros:
  - `pin`: Número da GPIO a ser alterada.
  - `value`: Valor lógico a ser atribuído à GPIO (true para HIGH, false para LOW).

### `uint8_t digitalRead(uint8_t pin)`

Lê o valor lógico presente em uma GPIO específica do PCF8574.

- Parâmetros:
  - `pin`: Número da GPIO a ser lida.

- Retorno:
  - O valor lido como um inteiro de 8 bits (0 para LOW, 1 para HIGH).

### `boolean btHold(uint8_t pin)`

Retorna `true` enquanto a GPIO estiver sendo utilizada como entrada de botão e permanecer pressionada (nível lógico alto).

- Parâmetros:
  - `pin`: Número da GPIO a ser lida.

- Retorno:
  - `true` se o botão estiver sendo pressionado, caso contrário, `false`.

### `boolean btPress(uint8_t pin)`

Retorna `true` no momento exato em que a GPIO é utilizada como entrada de botão e ocorre a transição do nível lógico de baixo para alto (quando o botão é pressionado).

- Parâmetros:
  - `pin`: Número da GPIO a ser lida.

- Retorno:
  - `true` no momento em que o botão é pressionado, caso contrário, `false`.

### `boolean btRelease(uint8_t pin)`

Retorna `true` no momento exato em que a GPIO é utilizada como entrada de botão e ocorre a transição do nível lógico de alto para baixo (quando o botão é solto).

- Parâmetros:
  - `pin`: Número da GPIO a ser lida.

- Retorno:
  - `true` no momento em que o botão é solto, caso contrário, `false`.

## Simulador PWM

### `boolean pwmBegin()`

Inicializa o expansor I2C com o simulador PWM ativado.

- Retorno:
  - `true` se a comunicação for inicializada com sucesso,caso contrário, `false`.

### `void pwmWrite(uint8_t pin, uint8_t dutyCycle)`

Atribui valores como frequência e ciclo de trabalho à GPIO simulada para o sinal PWM.

- Parâmetros:
  - `pin`: Número da GPIO a ser configurada para o sinal PWM.
  - `dutyCycle`: Ciclo de trabalho do sinal PWM, especificado como um valor percentual.

## Exemplo de Uso

Aqui está um exemplo de uso básico da classe `ES_PCF8574`:

```cpp
#include <Wire.h>
#include "ES_PCF8574.h"

ES_PCF8574 pcf8574(0x38); // Criar uma instância com o endereço do PCF8574

void setup() {
  Wire.begin();
  pcf8574.begin(true); // Inicializar a comunicação e ativar o simulador PWM
}

void loop() {
  // Definir o valor lógico HIGH na GPIO 0
  pcf8574.digitalWrite(EX0, HIGH);

  // Ler o valor lógico da GPIO 1
  uint8_t value = pcf8574.digitalRead(EX1);

  // Verificar se o botão na GPIO 2 está sendo pressionado
  if (pcf8574.btPress(EX2)) {
    // Realizar alguma ação quando o botão é pressionado
  }

  // Atribuir um ciclo de trabalho de 50% na GPIO 3 para o sinal PWM com a frequência de 2 hertz.
  pcf8574.pwmWrite(EX3, 50, 2);
}
```

-----
| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |