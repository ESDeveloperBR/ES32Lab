| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_CarControl

A classe `ES_CarControl` é um componente da biblioteca ES32Lab desenvolvido para simplificar o controle de veículos robóticos com a PCB ES32Lab, motores DC, ponte H, expansor de GPIO `ES_PCF8574` e, opcionalmente, buzzer.

Ela concentra em uma única interface os comandos de movimento do carro, controle de velocidade, comandos por caractere, controle de luzes, buzina, saída extra, callbacks personalizados e inversão lógica dos motores. A classe foi pensada para projetos didáticos, robôs móveis, carros controlados por Bluetooth, veículos seguidores de linha com a classe [`ES_CarLineFollower`](../ES_CarLineFollower/README.md) e protótipos que precisam de uma camada simples entre o código da aplicação e o hardware de tração.

A `ES_CarControl` trabalha principalmente em conjunto com a classe `ES_PCF8574`, responsável pelo acionamento dos pinos conectados à ponte H. Quando um objeto `ES_Buzzer` também é fornecido, a classe passa a controlar a buzina usando a infraestrutura de áudio da biblioteca ES32Lab.

### **Principais Recursos**
- **Controle de Movimentos**: comandos para parar, avançar, retroceder, virar e executar movimentos combinados.
- **Modos de Direção**: suporte a veículos com direção diferencial (`DIFFERENTIAL`) e direção frontal (`FRONTAL`).
- **Controle de Velocidade**: ajuste da velocidade atual e do percentual usado em curvas suaves.
- **Comandos por Caractere**: interpretação de comandos simples, útil para Bluetooth, Serial, controles remotos e aplicativos móveis.
- **Luzes, Buzina e Saída Extra**: métodos dedicados para controlar recursos auxiliares do veículo.
- **Callbacks Personalizados**: possibilidade de substituir o comportamento padrão dos movimentos e periféricos.
- **Inversão de Motores**: correção lógica do sentido dos motores sem alterar a ligação física dos fios.

---

## Índice

1. [Construtor](#construtor)
2. [Configuração no setup()](#configuração-no-setup)
3. [Modos de Direção](#modos-de-direção)
4. [Mapa de Comandos](#mapa-de-comandos)
5. [Controle por Comando](#controle-por-comando)
    - [`controlCommand(char command)`](#controlcommandchar-command)
    - [`controlCommand(Stream& serial)`](#controlcommandstream-serial)
6. [Controle de Velocidade](#controle-de-velocidade)
    - [`setSpeed(uint8_t value)`](#setspeeduint8_t-value)
    - [`getSpeed()`](#getspeed)
    - [`setSpeedDelay(uint8_t value)`](#setspeeddelayuint8_t-value)
    - [`getSpeedDelay()`](#getspeeddelay)
7. [Movimentos Básicos](#movimentos-básicos)
    - [`stop()`](#stop)
    - [`forward()` e `forward(uint8_t speed)`](#forward-e-forwarduint8_t-speed)
    - [`backward()` e `backward(uint8_t speed)`](#backward-e-backwarduint8_t-speed)
    - [`left()` e `left(uint8_t speed)`](#left-e-leftuint8_t-speed)
    - [`right()` e `right(uint8_t speed)`](#right-e-rightuint8_t-speed)
8. [Movimentos Combinados](#movimentos-combinados)
    - [`forwardLeft()` e `forwardLeft(uint8_t speed)`](#forwardleft-e-forwardleftuint8_t-speed)
    - [`forwardRight()` e `forwardRight(uint8_t speed)`](#forwardright-e-forwardrightuint8_t-speed)
    - [`backLeft()` e `backLeft(uint8_t speed)`](#backleft-e-backleftuint8_t-speed)
    - [`backRight()` e `backRight(uint8_t speed)`](#backright-e-backrightuint8_t-speed)
9. [Luzes, Buzina e Saída Extra](#luzes-buzina-e-saída-extra)
    - [`frontLights(boolean status)`](#frontlightsboolean-status)
    - [`backLights(boolean status)`](#backlightsboolean-status)
    - [`horn(boolean status)`](#hornboolean-status)
    - [`extra(boolean status)`](#extraboolean-status)
10. [Funções Personalizadas](#funções-personalizadas)
11. [Inversão de Motores](#inversão-de-motores)
    - [`invertMotorCommands(uint8_t motorID)`](#invertmotorcommandsuint8_t-motorid)
    - [`invertMotorStatus(uint8_t motorID)`](#invertmotorstatusuint8_t-motorid)
12. [Versão da Classe](#versão-da-classe)
13. [Exemplo Completo: Controle Diferencial por Comando Serial](#exemplo-completo-controle-diferencial-por-comando-serial)
14. [Exemplo Completo: Controle Manual no Código](#exemplo-completo-controle-manual-no-código)
15. [Exemplos Oficiais](#exemplos-oficiais)

---

## Construtor

### `ES_CarControl(ES_PCF8574 &expander)`

Cria uma instância da classe `ES_CarControl` usando um objeto `ES_PCF8574` já criado previamente. Essa é a forma recomendada quando o projeto utiliza apenas motores e saídas digitais controladas pelo expansor I2C.

#### Sintaxe:
```cpp
ES_CarControl car(expander);
```

#### Parâmetro:
- **`expander`**: referência para um objeto `ES_PCF8574`, responsável por controlar os pinos conectados aos motores e periféricos auxiliares.

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_CarControl car(expander);
```

---

### `ES_CarControl(ES_PCF8574 &expander, ES_Buzzer &buzzer)`

Cria uma instância da classe `ES_CarControl` usando um objeto `ES_PCF8574` e um objeto `ES_Buzzer`. Essa forma é recomendada quando o veículo também possui buzina controlada pela biblioteca ES32Lab.

#### Sintaxe:
```cpp
ES_CarControl car(expander, buzzer);
```

#### Parâmetros:
- **`expander`**: referência para um objeto `ES_PCF8574`, responsável pelo controle dos motores e saídas digitais.
- **`buzzer`**: referência para um objeto `ES_Buzzer`, responsável pelo controle sonoro da buzina.

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_Buzzer buzzer;
ES_CarControl car(expander, buzzer);
```

---

## Configuração no `setup()`

O método `begin()` deve ser chamado no `setup()` para configurar o modo de direção, os pinos dos motores, os pinos das luzes, o mapa de comandos e os níveis de velocidade. Sem essa etapa, a classe ainda possui o objeto criado, mas o hardware do veículo não estará preparado para receber comandos de movimento.

### `begin()`

Inicializa o controle do carro com os parâmetros informados. A chamada mais simples utiliza apenas o modo de direção, mantendo todos os demais valores padrão.

#### Sintaxe:
```cpp
boolean begin(
    uint8_t drivingMode = DIFFERENTIAL,
    uint8_t motor1Pin1 = 4,
    uint8_t motor1Pin2 = 5,
    uint8_t motor2Pin1 = 6,
    uint8_t motor2Pin2 = 7,
    uint8_t frontLightsPin = 0,
    uint8_t backLightsPin = 1,
    uint8_t stop = 'S',
    uint8_t forward = 'F',
    uint8_t back = 'B',
    uint8_t left = 'L',
    uint8_t right = 'R',
    uint8_t forwardLeft = 'G',
    uint8_t forwardRight = 'I',
    uint8_t backLeft = 'H',
    uint8_t backRight = 'J',
    uint8_t frontLightsOn = 'W',
    uint8_t frontLightsOff = 'w',
    uint8_t backLightsOn = 'U',
    uint8_t backLightsOff = 'u',
    uint8_t hornOn = 'V',
    uint8_t hornOff = 'v',
    uint8_t extraOn = 'X',
    uint8_t extraOff = 'x',
    uint8_t speedDelay = 40,
    uint8_t speed0 = '0',
    uint8_t speed1 = '1',
    uint8_t speed2 = '2',
    uint8_t speed3 = '3',
    uint8_t speed4 = '4',
    uint8_t speed5 = '5',
    uint8_t speed6 = '6',
    uint8_t speed7 = '7',
    uint8_t speed8 = '8',
    uint8_t speed9 = '9',
    uint8_t speed10 = 'q'
);
```

#### Parâmetros principais:
- **`drivingMode`**: define o tipo de direção do veículo. Use `DIFFERENTIAL` ou `FRONTAL`.
- **`motor1Pin1` e `motor1Pin2`**: pinos do expansor conectados à ponte H do motor 1.
- **`motor2Pin1` e `motor2Pin2`**: pinos do expansor conectados à ponte H do motor 2.
- **`frontLightsPin`**: pino usado para as luzes dianteiras.
- **`backLightsPin`**: pino usado para as luzes traseiras.
- **Comandos de movimento**: caracteres usados por `controlCommand()` para acionar o carro.
- **Comandos de velocidade**: caracteres usados por `controlCommand()` para alterar a velocidade atual.
- **`speedDelay`**: percentual aplicado ao motor mais lento nos movimentos combinados, como `forwardLeft()` e `forwardRight()`.

#### Retorno:
- **`true`**: se os motores foram inicializados corretamente.
- **`false`**: se houve falha na configuração dos motores.

#### Exemplo de Uso 1: Inicialização Padrão
```cpp
void setup() {
    Serial.begin(115200);
    expander.begin();

    if (!car.begin(DIFFERENTIAL)) {
        Serial.println("Falha ao inicializar o controle do carro.");
        while (true);
    }
}
```

#### Exemplo de Uso 2: Inicialização com Pinos Personalizados
```cpp
void setup() {
    Serial.begin(115200);
    expander.begin();

    car.begin(
        DIFFERENTIAL,
        EX4, EX5,   // Motor 1
        EX6, EX7,   // Motor 2
        EX0,        // Luz dianteira
        EX1         // Luz traseira
    );
}
```

---

## Modos de Direção

A classe `ES_CarControl` trabalha com dois modos de direção:

### `DIFFERENTIAL`

Modo indicado para veículos com dois motores independentes, um de cada lado do chassi. O carro vira alterando o sentido ou a velocidade relativa dos motores.

Esse modo é comum em:
- robôs seguidores de linha com a classe [`ES_CarLineFollower`](../ES_CarLineFollower/README.md);
- robôs móveis didáticos;
- chassis de duas rodas com roda boba;
- plataformas diferenciais simples.

### `FRONTAL`

Modo indicado para veículos em que um motor é usado para tração e outro motor atua como direção frontal. Nesse caso, os comandos de curva acionam o motor responsável pela direção.

Esse modo é comum em:
- carrinhos com direção mecânica dianteira;
- chassis adaptados de veículos RC;
- protótipos com motor de tração separado do motor de direção.

---

## Mapa de Comandos

O método `controlCommand()` interpreta caracteres individuais. Por padrão, a classe usa o seguinte mapa:

| Comando | Ação |
| :------: | ------ |
| `S` | Para o carro |
| `F` | Move para frente |
| `B` | Move para trás |
| `L` | Vira à esquerda |
| `R` | Vira à direita |
| `G` | Move para frente e à esquerda |
| `I` | Move para frente e à direita |
| `H` | Move para trás e à esquerda |
| `J` | Move para trás e à direita |
| `W` | Liga as luzes dianteiras |
| `w` | Desliga as luzes dianteiras |
| `U` | Liga as luzes traseiras |
| `u` | Desliga as luzes traseiras |
| `V` | Liga a buzina |
| `v` | Desliga a buzina |
| `X` | Ativa a saída extra |
| `x` | Desativa a saída extra |
| `0` | Ajusta velocidade para 0% |
| `1` | Ajusta velocidade para 10% |
| `2` | Ajusta velocidade para 20% |
| `3` | Ajusta velocidade para 30% |
| `4` | Ajusta velocidade para 40% |
| `5` | Ajusta velocidade para 50% |
| `6` | Ajusta velocidade para 60% |
| `7` | Ajusta velocidade para 70% |
| `8` | Ajusta velocidade para 80% |
| `9` | Ajusta velocidade para 90% |
| `q` | Ajusta velocidade para 100% |

> **Atenção:**  
> Qualquer caractere não reconhecido pelo mapa de comandos faz o carro parar. Esse comportamento é intencional e funciona como medida de segurança para evitar movimentos inesperados.

---

## Controle por Comando

Os métodos de controle por comando são úteis quando o carro recebe dados por Bluetooth, Serial, Wi-Fi, rádio ou qualquer outro meio que entregue caracteres individuais.

### `controlCommand(char command)`

Processa um único caractere e executa a ação correspondente no mapa de comandos.

#### Sintaxe:
```cpp
void controlCommand(char command);
```

#### Parâmetro:
- **`command`**: caractere que representa o comando a ser executado.

#### Exemplo de Uso:
```cpp
car.controlCommand('F'); // Move para frente
car.controlCommand('5'); // Ajusta velocidade para 50%
car.controlCommand('S'); // Para o carro
```

---

### `controlCommand(Stream& serial)`

Lê um caractere disponível em um fluxo serial e o envia para `controlCommand(char command)`.

#### Sintaxe:
```cpp
void controlCommand(Stream& serial);
```

#### Parâmetro:
- **`serial`**: referência para um objeto compatível com `Stream`, como `Serial`, `Serial1`, `Serial2` ou uma serial Bluetooth.

#### Exemplo de Uso:
```cpp
void loop() {
    car.controlCommand(Serial);
}
```

---

## Controle de Velocidade

A velocidade da classe é tratada como um valor percentual, normalmente entre `0` e `100`. Os métodos sem parâmetro de velocidade usam sempre a velocidade atual armazenada internamente.

### `setSpeed(uint8_t value)`

Ajusta a velocidade atual do carro.

#### Sintaxe:
```cpp
void setSpeed(uint8_t value);
```

#### Parâmetro:
- **`value`**: velocidade desejada, normalmente entre `0` e `100`.

#### Exemplo de Uso:
```cpp
car.setSpeed(30);
car.forward();
```

---

### `getSpeed()`

Retorna a velocidade atual configurada.

#### Sintaxe:
```cpp
uint8_t getSpeed();
```

#### Retorno:
- Valor atual de velocidade.

#### Exemplo de Uso:
```cpp
Serial.println(car.getSpeed());
```

---

### `setSpeedDelay(uint8_t value)`

Ajusta o percentual aplicado ao motor mais lento durante os movimentos combinados. Por exemplo, em uma curva suave, um motor pode girar com a velocidade principal e o outro com uma fração dessa velocidade.

#### Sintaxe:
```cpp
void setSpeedDelay(uint8_t value);
```

#### Parâmetro:
- **`value`**: percentual aplicado ao motor mais lento. O valor padrão é `40`.

#### Exemplo de Uso:
```cpp
car.setSpeed(50);
car.setSpeedDelay(30);
car.forwardLeft();
```

---

### `getSpeedDelay()`

Retorna o percentual usado para curvas suaves.

#### Sintaxe:
```cpp
uint8_t getSpeedDelay();
```

#### Retorno:
- Percentual atual usado nos movimentos combinados.

---

## Movimentos Básicos

Os movimentos básicos acionam o veículo diretamente. Cada movimento possui uma versão sem parâmetro, que usa a velocidade atual, e uma versão com parâmetro, que ajusta a velocidade antes de executar o movimento.

### `stop()`

Para os dois motores.

#### Sintaxe:
```cpp
void stop();
```

#### Exemplo de Uso:
```cpp
car.stop();
```

---

### `forward()` e `forward(uint8_t speed)`

Move o carro para frente.

#### Sintaxe:
```cpp
void forward();
void forward(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade desejada para o movimento.

#### Exemplo de Uso:
```cpp
car.forward();    // Usa a velocidade atual
car.forward(40);  // Move para frente a 40%
```

---

### `backward()` e `backward(uint8_t speed)`

Move o carro para trás.

#### Sintaxe:
```cpp
void backward();
void backward(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade desejada para o movimento.

#### Exemplo de Uso:
```cpp
car.backward();
car.backward(30);
```

---

### `left()` e `left(uint8_t speed)`

Vira o carro para a esquerda.

#### Sintaxe:
```cpp
void left();
void left(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade usada para a manobra.

#### Exemplo de Uso:
```cpp
car.left();
car.left(60);
```

---

### `right()` e `right(uint8_t speed)`

Vira o carro para a direita.

#### Sintaxe:
```cpp
void right();
void right(uint8_t speed);
```

#### Parâmetro:
- **`speed`**: velocidade usada para a manobra.

#### Exemplo de Uso:
```cpp
car.right();
car.right(60);
```

---

## Movimentos Combinados

Os movimentos combinados são úteis para curvas suaves. Eles movimentam o carro enquanto reduzem a velocidade de um dos motores com base no valor configurado por `setSpeedDelay()`.

### `forwardLeft()` e `forwardLeft(uint8_t speed)`

Move para frente virando à esquerda.

#### Sintaxe:
```cpp
void forwardLeft();
void forwardLeft(uint8_t speed);
```

#### Exemplo de Uso:
```cpp
car.forwardLeft();
car.forwardLeft(40);
```

---

### `forwardRight()` e `forwardRight(uint8_t speed)`

Move para frente virando à direita.

#### Sintaxe:
```cpp
void forwardRight();
void forwardRight(uint8_t speed);
```

#### Exemplo de Uso:
```cpp
car.forwardRight();
car.forwardRight(40);
```

---

### `backLeft()` e `backLeft(uint8_t speed)`

Move para trás virando à esquerda.

#### Sintaxe:
```cpp
void backLeft();
void backLeft(uint8_t speed);
```

#### Exemplo de Uso:
```cpp
car.backLeft();
car.backLeft(35);
```

---

### `backRight()` e `backRight(uint8_t speed)`

Move para trás virando à direita.

#### Sintaxe:
```cpp
void backRight();
void backRight(uint8_t speed);
```

#### Exemplo de Uso:
```cpp
car.backRight();
car.backRight(35);
```

---

## Luzes, Buzina e Saída Extra

Esses métodos controlam recursos auxiliares do veículo. Quando uma função personalizada é configurada por callback, ela substitui o comportamento padrão.

### `frontLights(boolean status)`

Liga ou desliga as luzes dianteiras.

#### Sintaxe:
```cpp
void frontLights(boolean status);
```

#### Parâmetro:
- **`status`**: `true` para ligar, `false` para desligar.

#### Exemplo de Uso:
```cpp
car.frontLights(true);
car.frontLights(false);
```

---

### `backLights(boolean status)`

Liga ou desliga as luzes traseiras.

#### Sintaxe:
```cpp
void backLights(boolean status);
```

#### Parâmetro:
- **`status`**: `true` para ligar, `false` para desligar.

#### Exemplo de Uso:
```cpp
car.backLights(true);
car.backLights(false);
```

---

### `horn(boolean status)`

Liga ou desliga a buzina.

#### Sintaxe:
```cpp
void horn(boolean status);
```

#### Parâmetro:
- **`status`**: `true` para ligar, `false` para desligar.

#### Exemplo de Uso:
```cpp
car.horn(true);
delay(300);
car.horn(false);
```

---

### `extra(boolean status)`

Ativa ou desativa uma saída extra. Para aplicações específicas, recomenda-se usar `setExtraFunction()` e definir exatamente qual ação deve ser executada.

#### Sintaxe:
```cpp
void extra(boolean status);
```

#### Parâmetro:
- **`status`**: `true` para ativar, `false` para desativar.

#### Exemplo de Uso:
```cpp
car.extra(true);
car.extra(false);
```

---

## Funções Personalizadas

A classe permite substituir o comportamento padrão de movimentos e periféricos por funções externas. Isso é útil quando o projeto utiliza outro driver de motor, outra topologia de hardware ou precisa executar lógica adicional junto com um comando.

### Métodos disponíveis:
```cpp
void setHornFunction(void (*callback)(bool));
void setFrontLightsFunction(void (*callback)(bool));
void setBackLightsFunction(void (*callback)(bool));
void setExtraFunction(void (*callback)(bool));

void setForwardFunction(void (*callback)(uint8_t));
void setBackwardFunction(void (*callback)(uint8_t));
void setLeftFunction(void (*callback)(uint8_t));
void setRightFunction(void (*callback)(uint8_t));
void setForwardLeftFunction(void (*callback)(uint8_t));
void setForwardRightFunction(void (*callback)(uint8_t));
void setBackLeftFunction(void (*callback)(uint8_t));
void setBackRightFunction(void (*callback)(uint8_t));
```

#### Exemplo de Uso:
```cpp
void customForward(uint8_t speed) {
    Serial.print("Movendo para frente com velocidade: ");
    Serial.println(speed);
}

void setup() {
    Serial.begin(115200);
    expander.begin();
    car.begin(DIFFERENTIAL);

    car.setForwardFunction(customForward);
}
```

> **Nota:**  
> Ao definir um callback para um movimento, o comportamento padrão daquele movimento deixa de ser executado. A função personalizada passa a ser responsável pela ação.

---

## Inversão de Motores

Em alguns projetos, os fios do motor ou da ponte H podem estar ligados em ordem invertida em relação ao sentido esperado pelo software. A inversão lógica permite corrigir esse comportamento sem alterar a ligação física.

### `invertMotorCommands(uint8_t motorID)`

Inverte os comandos do motor selecionado.

#### Sintaxe:
```cpp
void invertMotorCommands(uint8_t motorID);
```

#### Parâmetro:
- **`motorID`**: identificador do motor. Use `0` para o motor 1 e `1` para o motor 2.

#### Exemplo de Uso:
```cpp
car.invertMotorCommands(0);
```

---

### `invertMotorStatus(uint8_t motorID)`

Retorna se o motor selecionado está com os comandos invertidos.

#### Sintaxe:
```cpp
boolean invertMotorStatus(uint8_t motorID);
```

#### Parâmetro:
- **`motorID`**: identificador do motor. Use `0` para o motor 1 e `1` para o motor 2.

#### Retorno:
- **`true`**: se o motor estiver invertido.
- **`false`**: se o motor estiver no sentido padrão.

#### Exemplo de Uso:
```cpp
if (car.invertMotorStatus(0)) {
    Serial.println("Motor 1 invertido.");
}
```

---

## Versão da Classe

### `getVersion()`

Retorna a versão atual da classe `ES_CarControl`.

#### Sintaxe:
```cpp
const char* getVersion();
```

#### Retorno:
- String constante com a versão da classe.

#### Exemplo de Uso:
```cpp
Serial.println(car.getVersion());
```

---

## Exemplo Completo: Controle Diferencial por Comando Serial

Este exemplo cria um carro em modo diferencial, inicializa o expansor I2C e processa comandos enviados pela porta serial.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_Buzzer buzzer;
ES_CarControl car(expander, buzzer);

void setup() {
    Serial.begin(115200);
    expander.begin();

    if (!car.begin(DIFFERENTIAL)) {
        Serial.println("Falha ao inicializar o carro.");
        while (true);
    }

    car.setSpeed(40);
    Serial.println("Envie comandos pela Serial: F, B, L, R, S, 0-9 ou q.");
}

void loop() {
    car.controlCommand(Serial);
}
```

---

## Exemplo Completo: Controle Manual no Código

Este exemplo mostra o uso direto dos métodos de movimento, sem depender do mapa de comandos.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x20);
ES_CarControl car(expander);

void setup() {
    expander.begin();
    car.begin(DIFFERENTIAL);

    car.forward(30);
    delay(1000);

    car.forwardLeft(25);
    delay(700);

    car.right(40);
    delay(500);

    car.stop();
}

void loop() {

}
```

---

## Exemplos Oficiais

A biblioteca ES32Lab possui exemplos práticos para uso da classe `ES_CarControl` em veículos com direção diferencial, direção frontal e controle por comandos.

- [Exemplos Oficiais da Classe ES_CarControl](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/CarControl)

Esses exemplos servem como ponto de partida para projetos com controle por Bluetooth, testes de movimento, ajustes de direção e integração com outros recursos da biblioteca ES32Lab.

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
