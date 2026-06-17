| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_DigitalButton

A classe `ES_DigitalButton` é um componente da biblioteca ES32Lab desenvolvido para simplificar a leitura de botões digitais, chaves fim de curso, sensores de presença, sensores magnéticos, sensores ópticos e qualquer outro dispositivo que entregue um sinal digital simples em uma GPIO nativa do ESP32.

Ela permite identificar três estados fundamentais de uma entrada digital:

- **press()**: detecta o momento em que a entrada é acionada.
- **hold()**: detecta enquanto a entrada permanece acionada.
- **release()**: detecta o momento em que a entrada é solta.

A classe foi pensada para ser simples e didática. Por isso, o construtor não recebe parâmetros. A configuração do pino e da lógica de acionamento é feita no método `begin()`, normalmente dentro do `setup()`, deixando claro em que momento o hardware é inicializado.

### **Principais Recursos**
- **Construtor Simples**: o objeto é criado sem configurar GPIOs diretamente.
- **Configuração no begin()**: o pino e a lógica ativa são definidos no `setup()`.
- **Lógica Ativa Configurável**: suporte a entradas ativas em `HIGH` ou em `LOW`.
- **Configuração Automática de Pull-up/Pull-down**: a classe tenta aplicar `INPUT_PULLDOWN` para entradas ativas em `HIGH` e `INPUT_PULLUP` para entradas ativas em `LOW`.
- **Eventos de Botão**: métodos separados para detectar acionamento, estado mantido e liberação.
- **Uso com Botões e Sensores**: a classe não se limita a botões físicos; qualquer sinal digital pode ser tratado como entrada binária.

---

## Índice

1. [Conceito de Funcionamento](#conceito-de-funcionamento)
2. [Lógica Ativa: activeHigh](#lógica-ativa-activehigh)
3. [Pull-up, Pull-down e Limitações das GPIOs](#pull-up-pull-down-e-limitações-das-gpios)
4. [Construtor](#construtor)
5. [Configuração no setup()](#configuração-no-setup)
    - [`begin(int pin, boolean activeHigh)`](#beginint-pin-boolean-activehigh)
    - [`begin()`](#begin)
6. [Alteração de Pino em Tempo de Execução](#alteração-de-pino-em-tempo-de-execução)
    - [`setPin(int pin, boolean activeHigh)`](#setpinint-pin-boolean-activehigh)
    - [`setPino(int pin, boolean activeHigh)`](#setpinoint-pin-boolean-activehigh)
7. [Leitura dos Estados](#leitura-dos-estados)
    - [`press()`](#press)
    - [`hold()`](#hold)
    - [`release()`](#release)
8. [Debounce](#debounce)
9. [Versão da Classe](#versão-da-classe)
10. [Exemplo Completo: Botão BOOT na GPIO 0](#exemplo-completo-botão-boot-na-gpio-0)
11. [Exemplo Completo: Sensor Ativo em HIGH](#exemplo-completo-sensor-ativo-em-high)
12. [Exemplos Oficiais](#exemplos-oficiais)

---

## Conceito de Funcionamento

Uma entrada digital pode estar em dois estados elétricos: `HIGH` ou `LOW`. Porém, nem todo botão ou sensor usa o mesmo estado para indicar acionamento.

Exemplos comuns:

- Um botão ligado ao GND com resistor de pull-up fica em `HIGH` quando solto e vai para `LOW` quando pressionado.
- Um sensor digital com saída ativa em `HIGH` fica em `LOW` quando inativo e vai para `HIGH` quando detecta algo.

A `ES_DigitalButton` separa esse conceito usando o parâmetro `activeHigh`. Assim, o usuário informa qual estado elétrico deve ser interpretado como entrada ativa, e a classe passa a tratar `press()`, `hold()` e `release()` com base nessa lógica.

---

## Lógica Ativa: activeHigh

O parâmetro `activeHigh` define se a entrada será considerada ativa em `HIGH` ou em `LOW`.

| Valor | Interpretação | Configuração tentada pela classe | Uso comum |
| :---: | --- | --- | --- |
| `true` | Ativo em `HIGH` | `INPUT_PULLDOWN` | sensores digitais ativos em HIGH, botões ligados ao VCC |
| `false` | Ativo em `LOW` | `INPUT_PULLUP` | botão BOOT/GPIO 0, botões ligados ao GND |

Por padrão, `activeHigh` é `true`:

```cpp
button.begin(25);       // GPIO 25, ativo em HIGH
button.begin(25, true); // equivalente à linha acima
```

Para entradas ativas em `LOW`, informe `false`:

```cpp
button.begin(0, false); // GPIO 0, ativo em LOW
```

Esse formato evita que o usuário precise decidir diretamente entre `INPUT`, `INPUT_PULLUP` e `INPUT_PULLDOWN` na maioria dos casos didáticos.

---

## Pull-up, Pull-down e Limitações das GPIOs

Quando uma entrada digital não está conectada claramente a `HIGH` ou `LOW`, ela pode ficar flutuando. Isso gera leituras instáveis, alternando entre `HIGH` e `LOW` sem que o botão ou sensor tenha mudado de estado.

Para evitar isso, normalmente usamos:

- **Pull-up**: mantém a entrada em `HIGH` quando ela está em repouso.
- **Pull-down**: mantém a entrada em `LOW` quando ela está em repouso.

A `ES_DigitalButton` tenta configurar automaticamente o resistor interno mais coerente com a lógica ativa:

```cpp
activeHigh = true  -> pinMode(pin, INPUT_PULLDOWN)
activeHigh = false -> pinMode(pin, INPUT_PULLUP)
```

### Limitação importante do ESP32

Nem todas as GPIOs do ESP32 possuem os mesmos recursos internos. Em especial:

- **GPIOs 34 a 39**: em muitos ESP32, são apenas entrada e não possuem pull-up/pull-down interno disponível.
- **GPIOs 6 a 11**: normalmente são usadas pela memória flash do módulo e devem ser evitadas em projetos comuns.
- **GPIO 0**: possui função especial de bootloader; é útil para testes com o botão BOOT, mas deve ser usada com cuidado em projetos finais.

Se a GPIO escolhida não suportar `INPUT_PULLUP` ou `INPUT_PULLDOWN`, a classe ainda pode configurar o pino como entrada, mas o resistor interno esperado pode não existir. Nesse caso, o circuito precisa ter um resistor físico externo de pull-up ou pull-down para garantir uma leitura estável.

> **Resumo prático:**  
> A classe não bloqueia GPIOs apenas por elas não possuírem pull-up/pull-down interno. Ela permite o uso, mas cabe ao projetista garantir que o circuito externo deixe o sinal em um estado definido.

---

## Construtor

### `ES_DigitalButton()`

Cria uma instância da classe `ES_DigitalButton`.

O construtor não configura pino, lógica ativa nem modo de entrada. Essa configuração deve ser feita posteriormente com o método `begin()`.

#### Sintaxe:
```cpp
ES_DigitalButton button;
```

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_DigitalButton button;
```

---

## Configuração no `setup()`

O método `begin()` deve ser chamado dentro do `setup()` para definir a GPIO usada e a lógica de acionamento da entrada.

### `begin(int pin, boolean activeHigh)`

Inicializa o botão ou sensor digital com o pino e a lógica ativa informados.

#### Sintaxe:
```cpp
boolean begin(int pin, boolean activeHigh = true);
```

#### Parâmetros:
- **`pin`**: GPIO conectada ao botão ou sensor.
- **`activeHigh`**: define a lógica ativa da entrada.
  - `true`: entrada ativa em `HIGH`.
  - `false`: entrada ativa em `LOW`.

#### Retorno:
- **`true`**: se o pino foi aceito e configurado.
- **`false`**: se o pino informado for inválido.

#### Exemplo de Uso 1: Entrada Ativa em HIGH
```cpp
void setup() {
    Serial.begin(115200);
    button.begin(25); // GPIO 25, ativo em HIGH
}
```

#### Exemplo de Uso 2: Entrada Ativa em LOW
```cpp
void setup() {
    Serial.begin(115200);
    button.begin(0, false); // GPIO 0, ativo em LOW
}
```

---

### `begin()`

Inicializa o botão usando a configuração atualmente armazenada no objeto.

#### Sintaxe:
```cpp
boolean begin();
```

#### Retorno:
- **`true`**: se o pino armazenado foi aceito e configurado.
- **`false`**: se ainda não houver pino válido configurado.

Como o construtor atual não recebe parâmetros, a forma mais comum de uso é chamar `begin(pin, activeHigh)` diretamente. O `begin()` sem parâmetros é útil em situações em que o pino já tenha sido configurado anteriormente por `setPin()`.

---

## Alteração de Pino em Tempo de Execução

### `setPin(int pin, boolean activeHigh)`

Define uma nova GPIO e uma nova lógica ativa, reinicializando a entrada digital.

#### Sintaxe:
```cpp
boolean setPin(int pin, boolean activeHigh = true);
```

#### Parâmetros:
- **`pin`**: nova GPIO conectada ao botão ou sensor.
- **`activeHigh`**: define se a entrada será ativa em `HIGH` ou em `LOW`.

#### Retorno:
- **`true`**: se o pino foi aceito e configurado.
- **`false`**: se o pino informado for inválido.

#### Exemplo:
```cpp
button.setPin(26);        // GPIO 26, ativo em HIGH
button.setPin(0, false);  // GPIO 0, ativo em LOW
```

---

### `setPino(int pin, boolean activeHigh)`

Alias legado para `setPin()`.

#### Sintaxe:
```cpp
boolean setPino(int pin, boolean activeHigh = true);
```

#### Observação:
Para novos projetos, prefira `setPin()`. O método `setPino()` permanece disponível por compatibilidade com códigos antigos.

---

## Leitura dos Estados

A `ES_DigitalButton` oferece três métodos principais para leitura da entrada digital.

---

### `press()`

Detecta o momento em que a entrada muda de inativa para ativa.

Esse método retorna `true` apenas uma vez no instante do acionamento. Se o botão continuar pressionado, chamadas seguintes retornarão `false` até que ele seja solto e pressionado novamente.

#### Sintaxe:
```cpp
boolean press();
```

#### Exemplo:
```cpp
if (button.press()) {
    Serial.println("Botao pressionado.");
}
```

---

### `hold()`

Verifica se a entrada está ativa no momento.

Esse método retorna `true` durante todo o tempo em que o botão ou sensor permanecer acionado.

#### Sintaxe:
```cpp
boolean hold();
```

#### Exemplo:
```cpp
if (button.hold()) {
    Serial.println("Botao segurado.");
}
```

---

### `release()`

Detecta o momento em que a entrada muda de ativa para inativa.

Esse método retorna `true` apenas uma vez no instante da liberação.

#### Sintaxe:
```cpp
boolean release();
```

#### Exemplo:
```cpp
if (button.release()) {
    Serial.println("Botao solto.");
}
```

---

## Debounce

A classe `ES_DigitalButton` não implementa debounce interno.

Botões mecânicos podem gerar pequenos ruídos elétricos durante o pressionamento ou liberação. Isso pode causar múltiplos eventos de `press()` ou `release()` em alguns circuitos.

Para aplicações didáticas simples, normalmente isso não impede o uso. Para projetos finais, considere:

- usar debounce por hardware;
- usar um pequeno capacitor no circuito do botão;
- tratar debounce na lógica da aplicação;
- evitar executar ações críticas diretamente sem validação adicional.

---

## Versão da Classe

A versão da classe é definida pela macro:

```cpp
ES_DIGITALBUTTON_VERSION
```

Exemplo:

```cpp
Serial.println(ES_DIGITALBUTTON_VERSION);
```

---

## Exemplo Completo: Botão BOOT na GPIO 0

Este exemplo usa o botão BOOT comum em placas ESP32. Normalmente esse botão está conectado à GPIO 0 e é ativo em `LOW`, por isso usamos `activeHigh = false`.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_DigitalButton button;

void setup() {
    Serial.begin(115200);
    button.begin(0, false); // GPIO 0, ativo em LOW
}

void loop() {
    if (button.press()) {
        Serial.println("Button pressed. | Botao pressionado.");
    }

    if (button.hold()) {
        Serial.println("Button held. | Botao segurado.");
    }

    if (button.release()) {
        Serial.println("Button released. | Botao solto.");
    }

    delay(100);
}
```

> **Atenção:**  
> A GPIO 0 participa do processo de boot do ESP32. Ela é útil para testes didáticos com o botão BOOT, mas deve ser usada com cuidado em projetos definitivos.

---

## Exemplo Completo: Sensor Ativo em HIGH

Este exemplo mostra um sensor digital conectado à GPIO 25 e ativo em `HIGH`. Como `activeHigh = true` é o padrão, não é necessário informar o segundo parâmetro.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_DigitalButton sensor;

void setup() {
    Serial.begin(115200);
    sensor.begin(25); // GPIO 25, ativo em HIGH
}

void loop() {
    if (sensor.press()) {
        Serial.println("Sensor ativado.");
    }

    if (sensor.release()) {
        Serial.println("Sensor desativado.");
    }
}
```

---

## Exemplos Oficiais

O exemplo oficial da classe `ES_DigitalButton` está disponível na pasta:

```text
examples/DigitalButton/
```

Quando publicado no repositório, ele poderá ser acessado em:

[`examples/DigitalButton`](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/DigitalButton)

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
