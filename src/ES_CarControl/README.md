| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_CarControl

A classe `ES_CarControl` fornece uma interface para controle de veículos RC utilizando o ESP32. Com suporte para modos de direção diferenciados, controle de motores, luzes e buzina, é ideal para projetos de automação com controle remoto.

---

## Construtores

### `ES_CarControl(ES_PCF8574* pcf8574)`

Cria uma instância da classe `ES_CarControl` com suporte opcional para expansão de GPIOs via PCF8574.

- **Parâmetro**:
    - `pcf8574`: Ponteiro para um objeto da classe `ES_PCF8574`. Use `nullptr` se a expansão I2C não for necessária.

---

### `ES_CarControl(ES_PCF8574* pcf8574, ES_Buzzer* buzzer)`

Cria uma instância da classe `ES_CarControl` com suporte para expansão de GPIOs via PCF8574 e controle de som via Buzzer.

- **Parâmetros**:
    - `pcf8574`: Ponteiro para um objeto da classe `ES_PCF8574`. Use `nullptr` se a expansão I2C não for necessária.
    - `buzzer`: Ponteiro para um objeto da classe `ES_Buzzer`. Use `nullptr` se o controle de som não for necessário.

---

## Configuração no `setup()`

Os métodos descritos nesta seção são utilizados na função `setup()` para a configuração inicial do sistema.

### begin()

O método `begin` é o principal para configurar os pinos, comandos e outros parâmetros necessários para controlar o veículo.

#### Sintaxe:
`boolean begin(uint8_t drivingMode, uint8_t motor1Pin1, uint8_t motor1Pin2, ...)`

#### Parâmetros:
  - `drivingMode`: Define o modo de direção (0 para diferencial, 1 para frontal).
  - `motor1Pin1`, `motor1Pin2`, `motor2Pin1`, `motor2Pin2`: Pinos GPIO para controle dos motores.
  - `frontLightsPin`, `backLightsPin`: Pinos GPIO para controle das luzes.
  - Demais parâmetros: Configurações adicionais para comandos de movimento, luzes e buzina.

#### Retorno:
  - Retorna `true` se a inicialização for bem-sucedida.
  - Retorna `false` se houver falha (ex.: problemas ao inicializar os motores).

#### Exemplo de uso:
---
`carControl.begin(0, 4, 5, 6, 7, 0, 1, 'S', 'F', 'B', 'L', 'R', 'G', 'I', 'H', 'J', 'W', 'w', 'U', 'u', 'V', 'v', 'X', 'x', 40, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'q');`
---

---

## Métodos para Controle de Movimentos

### stop()

#### Sintaxe:
`void stop()`

Para todos os motores.

#### Exemplo de Uso:
---
`carControl.stop();`
---

---

### forward(uint8_t speed)

#### Sintaxe:
`void forward(uint8_t speed)`

Move o veículo para frente em uma velocidade especificada.

#### Parâmetros:
  - `speed`: Velocidade do movimento (0 a 100).

#### Exemplo de Uso:
---
`carControl.forward(50);`
---

---

### backward(uint8_t speed)

#### Sintaxe:
`void backward(uint8_t speed)`

Move o veículo para trás em uma velocidade especificada.

#### Parâmetros:
  - `speed`: Velocidade do movimento (0 a 100).

#### Exemplo de Uso:
---
`carControl.backward(40);`
---

---

### Métodos Avançados de Movimento

#### forwardLeft(uint8_t speed)

Move o veículo para frente e à esquerda.

#### forwardRight(uint8_t speed)

Move o veículo para frente e à direita.

#### backLeft(uint8_t speed)

Move o veículo para trás e à esquerda.

#### backRight(uint8_t speed)

Move o veículo para trás e à direita.

---

## Controle de Luzes e Buzina

### frontLights(boolean status)

#### Sintaxe:
`void frontLights(boolean status)`

Liga ou desliga as luzes dianteiras.

#### Parâmetros:
  - `status`: `true` para ligar, `false` para desligar.

#### Exemplo de Uso:
---
`carControl.frontLights(true);`
---

---

### horn(boolean status)

#### Sintaxe:
`void horn(boolean status)`

Ativa ou desativa a buzina.

#### Parâmetros:
  - `status`: `true` para ligar, `false` para desligar.

#### Exemplo de Uso:
---
`carControl.horn(true);`
---

---

## Funções Customizadas

Permite definir funções customizadas para movimentos e controle de luzes e buzina.

### setForwardFunction(void (*callback)(uint8_t))

Define uma função customizada para o movimento para frente.

#### Sintaxe:
`void setForwardFunction(void (*callback)(uint8_t speed))`

#### Parâmetros:
  - `callback`: Ponteiro para uma função que recebe a velocidade como parâmetro.

#### Exemplo de Uso:
---
`carControl.setForwardFunction([](uint8_t speed) { Serial.print("Moving forward at speed: "); Serial.println(speed); });`
---

---

## Inversão de Motores

### invertMotorCommands(uint8_t motorID)

#### Sintaxe:
`void invertMotorCommands(uint8_t motorID)`

Inverte os comandos de direção de um motor.

#### Parâmetros:
  - `motorID`: ID do motor a ser invertido (0 ou 1).

#### Exemplo de Uso:
---
`carControl.invertMotorCommands(0);`
---

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---
