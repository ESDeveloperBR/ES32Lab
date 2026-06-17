| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_CarLineFollower

A classe `ES_CarLineFollower` é um componente da biblioteca ES32Lab desenvolvido para simplificar a criação de robôs seguidores de linha usando a PCB ES32Lab, um veículo controlado pela classe [`ES_CarControl`](../ES_CarControl/README.md) e sensores digitais conectados ao expansor I2C [`ES_PCF8574`](../ES_PCF8574/README.md).

Ela foi criada para encapsular a lógica básica de seguimento de linha em uma classe própria, mantendo a responsabilidade de movimento dentro da `ES_CarControl` e a leitura dos sensores dentro da `ES_PCF8574`. Essa separação facilita a manutenção, melhora a organização didática do projeto e permite que o algoritmo de seguimento de linha evolua sem alterar diretamente a classe principal de controle do veículo.

A `ES_CarLineFollower` utiliza dois sensores digitais: um sensor esquerdo e um sensor direito. Quando um dos sensores encontra a linha preta, a classe executa uma correção para o lado oposto. Quando os dois sensores detectam a linha ao mesmo tempo, o robô interpreta essa condição como fim de percurso e para automaticamente.

Internamente, a classe utiliza [`ES_TimeInterval`](../ES_TimeInterval/README.md) para controlar tempos de recuperação de velocidade e parada por ausência de linha, evitando o uso de `delay()` dentro do algoritmo principal.

### **Principais Recursos**
- **Seguimento de Linha com Dois Sensores**: leitura de sensor esquerdo e direito conectados ao `ES_PCF8574`.
- **Integração com ES_CarControl**: todos os movimentos são executados pela classe `ES_CarControl`.
- **Correção Automática de Trajetória**: quando um sensor detecta a linha, o robô executa uma correção para retornar ao centro.
- **Controle de Velocidade Alta e Baixa**: após uma correção, o robô pode andar mais devagar por um tempo antes de voltar à velocidade normal.
- **Parada no Final do Percurso**: quando os dois sensores detectam a linha preta ao mesmo tempo, o seguidor é desabilitado e o carro para.
- **Parada por Ausência de Linha**: se nenhum evento de linha for detectado por tempo configurável, o robô para por segurança.
- **Métodos de Configuração**: ajuste de velocidades, tempos e estado de ativação em tempo de execução.

---

## Índice

1. [Classes Utilizadas](#classes-utilizadas)
2. [Ligação e Leitura dos Sensores](#ligação-e-leitura-dos-sensores)
3. [Conceito de Funcionamento](#conceito-de-funcionamento)
4. [Construtor](#construtor)
5. [Configuração no setup()](#configuração-no-setup)
6. [Atualização no loop()](#atualização-no-loop)
7. [Controle de Ativação](#controle-de-ativação)
    - [`enable()`](#enable)
    - [`disable()`](#disable)
    - [`setEnabled(boolean status)`](#setenabledboolean-status)
    - [`isEnabled()`](#isenabled)
8. [Parâmetros de Velocidade](#parâmetros-de-velocidade)
    - [`setHighSpeed(uint8_t speed)`](#sethighspeeduint8_t-speed)
    - [`getHighSpeed()`](#gethighspeed)
    - [`setLowSpeed(uint8_t speed)`](#setlowspeeduint8_t-speed)
    - [`getLowSpeed()`](#getlowspeed)
    - [`setLeftSpeed(uint8_t speed)`](#setleftspeeduint8_t-speed)
    - [`getLeftSpeed()`](#getleftspeed)
    - [`setRightSpeed(uint8_t speed)`](#setrightspeeduint8_t-speed)
    - [`getRightSpeed()`](#getrightspeed)
    - [`setTurnSpeed(uint8_t speed)`](#setturnspeeduint8_t-speed)
9. [Parâmetros de Tempo](#parâmetros-de-tempo)
    - [`setLowSpeedDuration(uint16_t duration)`](#setlowspeeddurationuint16_t-duration)
    - [`getLowSpeedDuration()`](#getlowspeedduration)
    - [`setNoLineDuration(uint16_t duration)`](#setnolinedurationuint16_t-duration)
    - [`getNoLineDuration()`](#getnolineduration)
10. [Versão da Classe](#versão-da-classe)
11. [Ajuste Fino do Robô](#ajuste-fino-do-robô)
12. [Exemplo Completo: Seguidor de Linha Simples](#exemplo-completo-seguidor-de-linha-simples)
13. [Exemplo Completo: Ativar e Desativar pela Serial](#exemplo-completo-ativar-e-desativar-pela-serial)
14. [Exemplos Oficiais](#exemplos-oficiais)

---

## Classes Utilizadas

A `ES_CarLineFollower` não controla diretamente pinos de motor nem faz leitura elétrica isolada dos sensores. Ela coordena objetos já existentes da biblioteca ES32Lab:

- [`ES_CarControl`](../ES_CarControl/README.md): executa os movimentos do carro, como `forward()`, `left()`, `right()` e `stop()`.
- [`ES_PCF8574`](../ES_PCF8574/README.md): lê os sensores digitais conectados ao expansor I2C.
- [`ES_TimeInterval`](../ES_TimeInterval/README.md): controla os intervalos internos usados para recuperação de velocidade e parada por ausência de linha.

Essa arquitetura permite que a lógica do seguidor de linha fique separada da lógica de controle de motor e da lógica de leitura dos sensores.

---

## Ligação e Leitura dos Sensores

A implementação atual considera dois sensores digitais conectados ao expansor I2C `ES_PCF8574`:

- **Sensor esquerdo**: informado no parâmetro `leftPin` do método `begin()`.
- **Sensor direito**: informado no parâmetro `rightPin` do método `begin()`.

Durante a execução, a classe lê os sensores usando os métodos `btHold(pin, true)` e `btRelease(pin, true)` da [`ES_PCF8574`](../ES_PCF8574/README.md). O segundo parâmetro configurado como `true` indica leitura considerando comportamento com pull-up.

Em termos práticos, o algoritmo espera que a detecção da linha preta possa ser interpretada como um estado de acionamento do sensor. Se o seu módulo de sensor trabalhar com lógica invertida em relação ao esperado, revise a ligação elétrica, o tipo de saída do módulo ou a configuração de hardware antes de ajustar os parâmetros de velocidade.

### Marcação de fim de percurso

Para indicar o fim do percurso, use uma faixa preta transversal larga o suficiente para que os dois sensores detectem a linha ao mesmo tempo. Quando isso ocorre, a classe chama `disable()` e o carro para por meio da [`ES_CarControl`](../ES_CarControl/README.md).

---

## Conceito de Funcionamento

O algoritmo atual foi pensado para um robô didático com dois sensores digitais posicionados próximos à linha:

- **Sensor esquerdo detecta a linha**: o robô corrige para a direita usando `car.right(leftSpeed)`.
- **Sensor direito detecta a linha**: o robô corrige para a esquerda usando `car.left(rightSpeed)`.
- **Sensor esquerdo ou direito libera a linha**: o robô volta a andar para frente em velocidade baixa usando `car.forward(lowSpeed)`.
- **Após o tempo de baixa velocidade**: o robô retorna para a velocidade alta usando `car.forward(highSpeed)`.
- **Os dois sensores detectam a linha ao mesmo tempo**: o robô interpreta como fim do percurso, desabilita o seguidor e para.
- **Nenhum evento de linha ocorre por muito tempo**: o robô para por segurança.

> **Atenção:**  
> A detecção de fim de percurso usa a condição em que os dois sensores encontram a linha preta ao mesmo tempo. Se o circuito possuir cruzamentos, bifurcações ou marcações largas, essa condição também pode ser interpretada como parada.

> **Nota sobre ausência de linha:**  
> Com apenas dois sensores digitais laterais, o robô não consegue distinguir perfeitamente uma linha bem centralizada entre os sensores de uma situação em que a linha desapareceu. Por isso, o parâmetro `noLineDuration` deve ser ajustado com cuidado. Valores muito baixos podem parar o robô durante trechos retos longos; valores maiores tornam a parada por perda de linha mais tolerante.

---

## Construtor

### `ES_CarLineFollower(ES_CarControl &car, ES_PCF8574 &expander)`

Cria uma instância da classe `ES_CarLineFollower` usando um objeto [`ES_CarControl`](../ES_CarControl/README.md) e um objeto [`ES_PCF8574`](../ES_PCF8574/README.md) já existentes.

#### Sintaxe:
```cpp
ES_CarLineFollower lineFollower(car, expander);
```

#### Parâmetros:
- **`car`**: referência para um objeto `ES_CarControl`, usado para executar os movimentos do robô.
- **`expander`**: referência para um objeto `ES_PCF8574`, usado para ler os sensores de linha.

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_CarControl car(expander);
ES_CarLineFollower lineFollower(car, expander);
```

---

## Configuração no `setup()`

O método `begin()` configura os pinos dos sensores e os principais parâmetros de comportamento do seguidor de linha. Ele deve ser chamado depois da criação dos objetos e, preferencialmente, após a inicialização do `ES_PCF8574` e da `ES_CarControl`.

### `begin()`

Inicializa o seguidor de linha com os sensores e parâmetros de movimento.

#### Sintaxe:
```cpp
boolean begin(
    uint8_t leftPin,
    uint8_t rightPin,
    uint8_t highSpeed = 20,
    uint8_t lowSpeed = 10,
    uint16_t lowSpeedDuration = 2500,
    uint16_t noLineDuration = 5000,
    uint8_t turnSpeed = 70
);
```

#### Parâmetros:
- **`leftPin`**: pino do `ES_PCF8574` conectado ao sensor esquerdo.
- **`rightPin`**: pino do `ES_PCF8574` conectado ao sensor direito.
- **`highSpeed`**: velocidade para frente usada quando o robô está estabilizado.
- **`lowSpeed`**: velocidade para frente usada logo após uma correção.
- **`lowSpeedDuration`**: tempo, em milissegundos, que o robô permanece em velocidade baixa antes de retornar à velocidade alta.
- **`noLineDuration`**: tempo máximo, em milissegundos, sem evento de linha antes de parar.
- **`turnSpeed`**: velocidade de correção aplicada igualmente para esquerda e direita.

#### Retorno:
- **`true`**: após armazenar a configuração.

#### Exemplo de Uso 1: Configuração com Valores Padrão
```cpp
void setup() {
    Serial.begin(115200);
    expander.begin();
    car.begin(DIFFERENTIAL);

    lineFollower.begin(EX3, EX2);
}
```

#### Exemplo de Uso 2: Configuração Personalizada
```cpp
void setup() {
    Serial.begin(115200);
    expander.begin();
    car.begin(DIFFERENTIAL);

    lineFollower.begin(
        EX3,  // Sensor esquerdo
        EX2,  // Sensor direito
        20,   // Velocidade alta
        10,   // Velocidade baixa
        2500, // Tempo em baixa velocidade
        5000, // Tempo máximo sem encontrar linha
        70    // Velocidade de correção
    );
}
```

---

## Atualização no `loop()`

### `update()`

O método `update()` deve ser chamado continuamente dentro do `loop()`. Ele lê os sensores, aplica correções, controla os temporizadores internos e decide quando o robô deve continuar, corrigir ou parar.

#### Sintaxe:
```cpp
void update();
```

#### Exemplo de Uso:
```cpp
void loop() {
    lineFollower.update();
}
```

> **Importante:**  
> O método `update()` não utiliza `delay()`. Para que o comportamento seja responsivo, evite inserir atrasos longos no `loop()` principal.

---

## Controle de Ativação

O seguidor de linha pode ser habilitado ou desabilitado em tempo de execução. Quando desabilitado, o método `update()` não aplica correções.

### `enable()`

Habilita o seguidor de linha, reinicia os temporizadores internos e inicia o movimento para frente na velocidade alta.

#### Sintaxe:
```cpp
void enable();
```

#### Exemplo de Uso:
```cpp
lineFollower.enable();
```

---

### `disable()`

Desabilita o seguidor de linha e para o robô usando `car.stop()`.

#### Sintaxe:
```cpp
void disable();
```

#### Exemplo de Uso:
```cpp
lineFollower.disable();
```

---

### `setEnabled(boolean status)`

Define o estado de ativação do seguidor de linha. Internamente, chama `enable()` quando `status` é `true` e `disable()` quando `status` é `false`.

#### Sintaxe:
```cpp
void setEnabled(boolean status);
```

#### Parâmetro:
- **`status`**: `true` para habilitar, `false` para desabilitar.

#### Exemplo de Uso:
```cpp
lineFollower.setEnabled(true);
lineFollower.setEnabled(false);
```

---

### `isEnabled()`

Retorna se o seguidor de linha está habilitado.

#### Sintaxe:
```cpp
boolean isEnabled();
```

#### Retorno:
- **`true`**: se o seguidor estiver habilitado.
- **`false`**: se o seguidor estiver desabilitado.

#### Exemplo de Uso:
```cpp
if (lineFollower.isEnabled()) {
    Serial.println("Seguidor de linha ativo.");
}
```

---

## Parâmetros de Velocidade

As velocidades são valores percentuais normalmente configurados entre `0` e `100`. Valores acima de `100` são limitados internamente para `100`.

### `setHighSpeed(uint8_t speed)`

Define a velocidade para frente usada quando o robô está estabilizado.

#### Sintaxe:
```cpp
void setHighSpeed(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade alta, normalmente entre `0` e `100`.

#### Exemplo de Uso:
```cpp
lineFollower.setHighSpeed(25);
```

---

### `getHighSpeed()`

Retorna a velocidade alta atual.

#### Sintaxe:
```cpp
uint8_t getHighSpeed();
```

#### Retorno:
- Velocidade alta atual.

---

### `setLowSpeed(uint8_t speed)`

Define a velocidade para frente usada logo após uma correção.

#### Sintaxe:
```cpp
void setLowSpeed(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade baixa, normalmente entre `0` e `100`.

#### Exemplo de Uso:
```cpp
lineFollower.setLowSpeed(10);
```

---

### `getLowSpeed()`

Retorna a velocidade baixa atual.

#### Sintaxe:
```cpp
uint8_t getLowSpeed();
```

#### Retorno:
- Velocidade baixa atual.

---

### `setLeftSpeed(uint8_t speed)`

Define a velocidade usada na correção acionada pelo sensor esquerdo.

#### Sintaxe:
```cpp
void setLeftSpeed(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade de correção do sensor esquerdo, normalmente entre `0` e `100`.

#### Exemplo de Uso:
```cpp
lineFollower.setLeftSpeed(65);
```

---

### `getLeftSpeed()`

Retorna a velocidade atual de correção do sensor esquerdo.

#### Sintaxe:
```cpp
uint8_t getLeftSpeed();
```

#### Retorno:
- Velocidade de correção do sensor esquerdo.

---

### `setRightSpeed(uint8_t speed)`

Define a velocidade usada na correção acionada pelo sensor direito.

#### Sintaxe:
```cpp
void setRightSpeed(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade de correção do sensor direito, normalmente entre `0` e `100`.

#### Exemplo de Uso:
```cpp
lineFollower.setRightSpeed(70);
```

---

### `getRightSpeed()`

Retorna a velocidade atual de correção do sensor direito.

#### Sintaxe:
```cpp
uint8_t getRightSpeed();
```

#### Retorno:
- Velocidade de correção do sensor direito.

---

### `setTurnSpeed(uint8_t speed)`

Define a mesma velocidade de correção para esquerda e direita. É útil quando o robô não precisa compensar diferenças mecânicas entre os motores.

#### Sintaxe:
```cpp
void setTurnSpeed(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade aplicada às duas correções.

#### Exemplo de Uso:
```cpp
lineFollower.setTurnSpeed(70);
```

---

## Parâmetros de Tempo

Os parâmetros de tempo controlam a recuperação de velocidade e a parada por ausência de linha. Eles são configurados em milissegundos.

### `setLowSpeedDuration(uint16_t duration)`

Define por quanto tempo o robô permanece em velocidade baixa após uma correção.

#### Sintaxe:
```cpp
void setLowSpeedDuration(uint16_t duration);
```

#### Parâmetro:
- **`duration`**: tempo em milissegundos.

#### Exemplo de Uso:
```cpp
lineFollower.setLowSpeedDuration(2500);
```

---

### `getLowSpeedDuration()`

Retorna o tempo configurado para recuperação da velocidade alta.

#### Sintaxe:
```cpp
uint16_t getLowSpeedDuration();
```

#### Retorno:
- Tempo atual em milissegundos.

---

### `setNoLineDuration(uint16_t duration)`

Define o tempo máximo sem evento de linha antes de parar o robô.

#### Sintaxe:
```cpp
void setNoLineDuration(uint16_t duration);
```

#### Parâmetro:
- **`duration`**: tempo em milissegundos.

#### Exemplo de Uso:
```cpp
lineFollower.setNoLineDuration(8000);
```

> **Dica de ajuste:**  
> Aumente esse valor se o robô estiver parando em trechos retos longos. Reduza esse valor se o robô continuar andando por muito tempo depois de sair do percurso.

---

### `getNoLineDuration()`

Retorna o tempo máximo configurado para ausência de linha.

#### Sintaxe:
```cpp
uint16_t getNoLineDuration();
```

#### Retorno:
- Tempo atual em milissegundos.

---

## Versão da Classe

### `getVersion()`

Retorna a versão atual da classe `ES_CarLineFollower`.

#### Sintaxe:
```cpp
const char* getVersion();
```

#### Retorno:
- String constante com a versão da classe.

#### Exemplo de Uso:
```cpp
Serial.println(lineFollower.getVersion());
```

---

## Ajuste Fino do Robô

O comportamento do robô depende de fatores mecânicos e elétricos: posição dos sensores, largura da fita, velocidade dos motores, aderência das rodas, distância entre eixos, iluminação ambiente e tempo de resposta dos sensores.

### Recomendações iniciais:
- Comece com velocidades baixas, como `highSpeed = 20` e `lowSpeed = 10`.
- Use `turnSpeed` maior que a velocidade de avanço, como `60` ou `70`, para correções firmes.
- Se o robô oscilar muito, reduza `turnSpeed` ou aumente levemente `lowSpeedDuration`.
- Se o robô perder curvas, reduza `highSpeed` ou aumente `turnSpeed`.
- Se o robô parar em linha reta, aumente `noLineDuration`.
- Se um lado corrige melhor que o outro, use `setLeftSpeed()` e `setRightSpeed()` separadamente.

### Valores sugeridos para teste inicial:
```cpp
lineFollower.begin(EX3, EX2, 20, 10, 2500, 5000, 70);
```

### Ajuste separado por lado:
```cpp
lineFollower.setLeftSpeed(65);
lineFollower.setRightSpeed(75);
```

---

## Exemplo Completo: Seguidor de Linha Simples

Este exemplo inicializa o expansor I2C, configura o carro em modo diferencial e habilita o seguidor de linha automaticamente no `setup()`.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_CarControl car(expander);
ES_CarLineFollower lineFollower(car, expander);

void setup() {
    Serial.begin(115200);
    expander.begin();

    if (!car.begin(DIFFERENTIAL)) {
        Serial.println("Falha ao inicializar o carro.");
        while (true);
    }

    car.invertMotorCommands(0); // Use apenas se o sentido de um motor estiver invertido.

    lineFollower.begin(
        EX3,  // Sensor esquerdo
        EX2,  // Sensor direito
        20,   // Velocidade alta
        10,   // Velocidade baixa
        2500, // Tempo antes de retornar para velocidade alta
        5000, // Tempo máximo sem detectar evento de linha
        70    // Velocidade de correção
    );

    lineFollower.enable();
}

void loop() {
    lineFollower.update();
}
```

---

## Exemplo Completo: Ativar e Desativar pela Serial

Este exemplo permite iniciar e parar o seguidor de linha usando comandos enviados pelo Monitor Serial.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_CarControl car(expander);
ES_CarLineFollower lineFollower(car, expander);

void setup() {
    Serial.begin(115200);
    expander.begin();
    car.begin(DIFFERENTIAL);

    lineFollower.begin(EX3, EX2, 20, 10, 2500, 5000, 70);

    Serial.println("Envie 'r' para iniciar ou 's' para parar o seguidor de linha.");
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read();

        if (command == 'r') {
            lineFollower.enable();
            Serial.println("Seguidor de linha iniciado.");
        } else if (command == 's') {
            lineFollower.disable();
            Serial.println("Seguidor de linha parado.");
        }
    }

    lineFollower.update();
}
```

---

## Exemplos Oficiais

A biblioteca ES32Lab terá exemplos práticos para uso da classe `ES_CarLineFollower` em robôs seguidores de linha com sensores digitais conectados ao expansor I2C.

- [Exemplos Oficiais da Classe ES_CarLineFollower](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/CarLineFollower)

Esses exemplos servirão como ponto de partida para testes de sensores, ajuste de velocidade, calibração de curvas, parada no final do percurso e integração com outras classes da biblioteca ES32Lab.

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
