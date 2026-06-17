| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_TimeInterval

A classe `ES_TimeInterval` é um componente da biblioteca ES32Lab desenvolvido para simplificar o controle de tempo em projetos Arduino e ESP32 sem bloquear a execução do programa principal.

Ela encapsula o uso das funções nativas `millis()` e `micros()`, permitindo criar rotinas periódicas, temporizadores simples e medições de tempo sem utilizar `delay()`. Isso é especialmente útil em projetos que precisam executar várias tarefas ao mesmo tempo, como leitura de sensores, atualização de display, controle de motores, comunicação Serial, Bluetooth, Wi-Fi ou lógica de robôs móveis.

A `ES_TimeInterval` trabalha com valores do tipo `unsigned long`, seguindo o mesmo tipo utilizado pelas funções `millis()` e `micros()` do Arduino. Dessa forma, a classe fica alinhada ao comportamento nativo da plataforma e mantém comparações de tempo seguras mesmo quando o contador interno do microcontrolador reinicia após o estouro natural.

### **Principais Recursos**
- **Controle sem delay()**: permite executar ações periódicas sem parar o `loop()` principal.
- **Intervalos em Milissegundos**: uso de `intervalMillis()` para tarefas comuns de temporização.
- **Intervalos em Microssegundos**: uso de `intervalMicros()` para medições ou rotinas que exigem maior precisão.
- **Cronômetro Simples**: métodos para iniciar e medir tempo decorrido em milissegundos ou microssegundos.
- **Integração com Outras Classes**: pode ser usada para atualizar displays, controlar sensores, temporizar movimentos e organizar rotinas não bloqueantes.
- **Compatível com o Padrão Arduino**: utiliza `unsigned long`, mesmo tipo retornado por `millis()` e `micros()`.

---

## Índice

1. [Conceito de Funcionamento](#conceito-de-funcionamento)
2. [Criação do Objeto](#criação-do-objeto)
3. [Intervalos em Milissegundos](#intervalos-em-milissegundos)
    - [`intervalMillis(unsigned long millisTime)`](#intervalmillisunsigned-long-millistime)
    - [`resetMillis()`](#resetmillis)
4. [Intervalos em Microssegundos](#intervalos-em-microssegundos)
    - [`intervalMicros(unsigned long microsTime)`](#intervalmicrosunsigned-long-microstime)
    - [`resetMicros()`](#resetmicros)
5. [Cronômetro em Milissegundos](#cronômetro-em-milissegundos)
    - [`stopwatchStartMillis()`](#stopwatchstartmillis)
    - [`stopwatchStopMillis()`](#stopwatchstopmillis)
6. [Cronômetro em Microssegundos](#cronômetro-em-microssegundos)
    - [`stopwatchStartMicros()`](#stopwatchstartmicros)
    - [`stopwatchStopMicros()`](#stopwatchstopmicros)
7. [Sobre unsigned long](#sobre-unsigned-long)
8. [Exemplo Completo: Piscar sem delay()](#exemplo-completo-piscar-sem-delay)
9. [Exemplo Completo: Atualização Periódica pela Serial](#exemplo-completo-atualização-periódica-pela-serial)
10. [Exemplo Completo: Medição com Cronômetro](#exemplo-completo-medição-com-cronômetro)
11. [Exemplos Oficiais](#exemplos-oficiais)

---

## Conceito de Funcionamento

Em muitos projetos Arduino, o comando `delay()` é usado para aguardar um tempo antes de executar a próxima ação. Apesar de simples, ele bloqueia o programa: enquanto o `delay()` está em execução, o microcontrolador não continua verificando botões, sensores, comunicação ou outras tarefas do `loop()`.

A classe `ES_TimeInterval` resolve esse problema usando uma abordagem não bloqueante. Em vez de parar o programa, ela verifica se o tempo desejado já passou. Quando o intervalo termina, o método retorna `true`; caso contrário, retorna `false` e o programa continua executando normalmente.

Exemplo conceitual:

```cpp
if (timer.intervalMillis(1000)) {
    // Este bloco executa a cada 1000 ms,
    // sem bloquear o restante do loop().
}
```

Essa técnica é recomendada para:

- atualizar informações no display em intervalos fixos;
- ler sensores periodicamente;
- controlar LEDs sem bloquear o programa;
- criar temporizadores de segurança;
- medir tempo de execução de trechos de código;
- organizar projetos com várias tarefas simultâneas.

---

## Criação do Objeto

Para usar a classe, crie um objeto global do tipo `ES_TimeInterval`.

#### Sintaxe:
```cpp
ES_TimeInterval timer;
```

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TimeInterval timer;
```

Não é necessário chamar método `begin()`. O objeto já armazena suas referências internas de tempo no momento da criação.

---

## Intervalos em Milissegundos

Intervalos em milissegundos são indicados para a maioria das tarefas comuns, como atualização de display, leitura de botões, leitura de sensores e execução de eventos periódicos.

### `intervalMillis(unsigned long millisTime)`

Verifica se o intervalo informado em milissegundos já passou. Quando o tempo é atingido, a referência interna é atualizada automaticamente e o método retorna `true`.

#### Sintaxe:
```cpp
boolean intervalMillis(unsigned long millisTime);
```

#### Parâmetro:
- **`millisTime`**: tempo do intervalo em milissegundos.

#### Retorno:
- **`true`**: se o intervalo terminou.
- **`false`**: se o intervalo ainda não terminou.

#### Exemplo de Uso:
```cpp
if (timer.intervalMillis(1000)) {
    Serial.println("Executa a cada 1 segundo.");
}
```

---

### `resetMillis()`

Reinicia a referência interna usada por `intervalMillis()`. Após chamar esse método, a contagem do intervalo em milissegundos começa novamente a partir do tempo atual.

#### Sintaxe:
```cpp
void resetMillis();
```

#### Exemplo de Uso:
```cpp
timer.resetMillis();
```

Esse método é útil quando uma condição externa deve reiniciar a contagem, como o pressionamento de um botão, uma nova leitura de sensor ou a mudança de estado de uma máquina de estados.

---

## Intervalos em Microssegundos

Intervalos em microssegundos são indicados para situações em que é necessário trabalhar com maior precisão do que milissegundos. Use esse recurso com cuidado, porque intervalos muito pequenos podem tornar o `loop()` mais sensível ao tempo de execução das demais tarefas.

### `intervalMicros(unsigned long microsTime)`

Verifica se o intervalo informado em microssegundos já passou. Quando o tempo é atingido, a referência interna é atualizada automaticamente e o método retorna `true`.

#### Sintaxe:
```cpp
boolean intervalMicros(unsigned long microsTime);
```

#### Parâmetro:
- **`microsTime`**: tempo do intervalo em microssegundos.

#### Retorno:
- **`true`**: se o intervalo terminou.
- **`false`**: se o intervalo ainda não terminou.

#### Exemplo de Uso:
```cpp
if (timer.intervalMicros(500)) {
    // Executa a cada 500 microssegundos.
}
```

---

### `resetMicros()`

Reinicia a referência interna usada por `intervalMicros()`. Após chamar esse método, a contagem do intervalo em microssegundos começa novamente a partir do tempo atual.

#### Sintaxe:
```cpp
void resetMicros();
```

#### Exemplo de Uso:
```cpp
timer.resetMicros();
```

---

## Cronômetro em Milissegundos

O cronômetro em milissegundos é útil para medir quanto tempo uma rotina levou para executar ou quanto tempo passou entre dois eventos.

### `stopwatchStartMillis()`

Inicia ou reinicia a referência do cronômetro em milissegundos.

#### Sintaxe:
```cpp
void stopwatchStartMillis();
```

#### Exemplo de Uso:
```cpp
timer.stopwatchStartMillis();
```

---

### `stopwatchStopMillis()`

Retorna o tempo decorrido, em milissegundos, desde a última chamada de `stopwatchStartMillis()`.

#### Sintaxe:
```cpp
unsigned long stopwatchStopMillis();
```

#### Retorno:
- **`unsigned long`**: tempo decorrido em milissegundos.

#### Exemplo de Uso:
```cpp
timer.stopwatchStartMillis();

// Código que será medido.

unsigned long elapsedTime = timer.stopwatchStopMillis();
Serial.println(elapsedTime);
```

---

## Cronômetro em Microssegundos

O cronômetro em microssegundos é indicado para medições mais curtas ou quando é necessário observar diferenças de tempo menores.

### `stopwatchStartMicros()`

Inicia ou reinicia a referência do cronômetro em microssegundos.

#### Sintaxe:
```cpp
void stopwatchStartMicros();
```

#### Exemplo de Uso:
```cpp
timer.stopwatchStartMicros();
```

---

### `stopwatchStopMicros()`

Retorna o tempo decorrido, em microssegundos, desde a última chamada de `stopwatchStartMicros()`.

#### Sintaxe:
```cpp
unsigned long stopwatchStopMicros();
```

#### Retorno:
- **`unsigned long`**: tempo decorrido em microssegundos.

#### Exemplo de Uso:
```cpp
timer.stopwatchStartMicros();

// Código que será medido.

unsigned long elapsedTime = timer.stopwatchStopMicros();
Serial.println(elapsedTime);
```

---

## Sobre unsigned long

As funções nativas `millis()` e `micros()` do Arduino retornam valores do tipo `unsigned long`. Por esse motivo, a `ES_TimeInterval` também utiliza `unsigned long` nos parâmetros e retornos ligados a tempo.

Esse tipo representa apenas números sem sinal, ou seja, não trabalha com valores negativos. Para controle de tempo, isso é adequado, pois uma contagem de tempo decorrido não deve ser negativa.

Outro ponto importante é o estouro natural do contador. Depois de certo período ligado, o valor retornado por `millis()` ou `micros()` volta para zero. A forma usada pela classe mantém a comparação segura:

```cpp
if ((millis() - startTime) >= intervalTime) {
    // O intervalo terminou.
}
```

Essa abordagem é o padrão recomendado em projetos Arduino para lidar com temporização sem `delay()`.

---

## Exemplo Completo: Piscar sem delay()

Este exemplo alterna o estado de um LED a cada 500 milissegundos sem bloquear o `loop()`.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TimeInterval ledTimer;

const uint8_t ledPin = 2;
boolean ledStatus = false;

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (ledTimer.intervalMillis(500)) {
        ledStatus = !ledStatus;
        digitalWrite(ledPin, ledStatus);
    }

    // Outras tarefas podem continuar sendo executadas aqui.
}
```

---

## Exemplo Completo: Atualização Periódica pela Serial

Este exemplo imprime uma mensagem a cada 2 segundos sem interromper o restante do programa.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TimeInterval serialTimer;

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (serialTimer.intervalMillis(2000)) {
        Serial.println("O loop principal continua rodando sem delay().");
    }

    // Leituras de sensores, botões ou comunicação podem ficar aqui.
}
```

---

## Exemplo Completo: Medição com Cronômetro

Este exemplo mede em microssegundos quanto tempo um bloco de comandos levou para executar.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TimeInterval stopwatch;

void setup() {
    Serial.begin(115200);
}

void loop() {
    stopwatch.stopwatchStartMicros();

    Serial.println("*************");
    Serial.println("Hello World");
    Serial.println("*************");

    unsigned long elapsedTime = stopwatch.stopwatchStopMicros();

    Serial.print("Tempo de execucao: ");
    Serial.print(elapsedTime);
    Serial.println(" microssegundos.");

    delay(5000);
}
```

> **Observação:**  
> Neste exemplo, o `delay(5000)` aparece apenas para facilitar a leitura da saída no Monitor Serial. Para rotinas principais não bloqueantes, prefira `intervalMillis()`.

---

## Exemplos Oficiais

Os exemplos oficiais da classe `ES_TimeInterval` podem ser disponibilizados na pasta de exemplos da biblioteca ES32Lab:

```text
examples/TimeInterval/
```

Quando publicados no repositório, eles poderão ser acessados em:

[`examples/TimeInterval`](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/TimeInterval)

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
