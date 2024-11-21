| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----

# Classe DigitalButton

A classe **DigitalButton** foi projetada para facilitar o monitoramento de dispositivos binários, como botões, sensores de limite, chaves de fim de curso e outros sensores digitais simples. Com sua lógica robusta e flexível, ela permite detectar os estados "pressionado", "solto" e "segurando", além de oferecer suporte para resistores internos de **pull-up** ou **pull-down**.

## Por Que Usar a DigitalButton?

Essa classe não se limita ao uso com botões digitais, mas é uma solução ideal para qualquer dispositivo que forneça dois estados binários: ligado/desligado ou ativo/inativo. Seja um botão de pressão ou um sensor digital simples, como sensores magnéticos, sensores de proximidade ou de contato, a **DigitalButton** simplifica a implementação e o gerenciamento.

---

## Funcionalidades

- **Monitoramento de estados binários**: Detecta os estados "pressionado", "solto" e "segurando".
- **Suporte a pull-up e pull-down internos**: Configuração flexível para atender às características do sensor utilizado.
- **Compatibilidade ampla**: Aceita qualquer GPIO do ESP32, exceto GPIOs 34-39, que possuem restrições de hardware.
- **Validação de pinos**: Garante que apenas pinos válidos sejam configurados.

---

## Construtor

### `DigitalButton(int pin = -1, boolean pullUp = false)`
Cria uma instância da classe `DigitalButton` para gerenciar dispositivos binários, como botões ou sensores digitais. O construtor permite configurar diretamente a GPIO e a ativação do resistor interno pull-up no momento da criação do objeto, tornando a inicialização mais prática para muitos cenários.

- **Parâmetros**:
  - **`pin`**: GPIO conectado ao dispositivo binário. (Padrão: `-1`, sem pino configurado).
  - **`pullUp`**: Define se o resistor pull-up será ativado. (Padrão: `false`).

### Exemplos de Uso

1. **Inicialização sem especificar GPIO**  
   Neste caso, a GPIO será definida posteriormente no programa utilizando o método `begin` ou `setPino`:  
   `DigitalButton button; // Instância sem definir GPIO e pull-up.`

2. **Inicialização com GPIO e configuração padrão de pull-down**  
   O botão ou sensor será monitorado no **GPIO 0**, com resistor **pull-down** configurado (padrão):  
   `DigitalButton button(0); // Instância na GPIO 0 com pull-down.`

3. **Inicialização com GPIO e pull-up ativado**  
   Aqui a **GPIO 0** será configurado com resistor interno **pull-up**, ideal para botões conectados ao GND:  
   `DigitalButton digitalButton(0, true); // Instância na GPIO 0 com pull-up ativado.`

**Nota:** Caso a GPIO seja definido no construtor, o método `begin` ainda precisará ser chamado no `setup()` para inicializar o hardware.

---

## Configuração no `setup()`

O método `begin` é fundamental para inicializar a instância da classe `DigitalButton` e configurar a GPIO que será usado para monitorar o dispositivo binário. Essa configuração deve ser realizada dentro da função `setup()` para garantir que o hardware esteja pronto para operação durante a execução do programa.

A passagem de parâmetros ao método `begin` não é obrigatória. Quando nenhum parâmetro é especificado, o pino e o resistor pull-up ou pull-down definidos no construtor da classe serão utilizados. Isso proporciona flexibilidade tanto para inicializações rápidas quanto para configurações específicas.

### Considerações sobre a GPIO 0

Nos exemplos a seguir, utilizamos a **GPIO 0** como pino de entrada. A maioria dos ESP32 em shields tem um botão conectado à **GPIO 0** para colocá-lo em modo de programação (bootloader) ao ser mantido em LOW durante o reset. Esse botão pode ser reutilizado para testes simples com a classe `DigitalButton`. **No entanto, use a GPIO 0 com moderação em projetos definitivos**, devido à sua função especial no ESP32.

---

### begin()

Inicializa o dispositivo binário, atribuindo a GPIO e preparando-o para o monitoramento.

#### Sintaxe:
`boolean begin(int pin, boolean pullUp = false)`

#### Exemplos de Uso

1. Inicialização rápida, utilizando a **GPIO 0** definida no construtor:
```cpp
button.begin(); // Inicializa o monitoramento utilizando a configuração padrão.
```

2. Inicialização personalizada, especificando a GPIO e ativando o resistor **pull-up**:
```cpp 
button.begin(0, true); // Inicializa o monitoramento no GPIO 0 com pull-up ativado.
```
**Nota:** Ao utilizar a **GPIO 0**, certifique-se de que sua aplicação não entre em conflito com o modo de programação (bootloader). Use-a preferencialmente para testes ou projetos onde essa função especial seja considerada.

---

## Métodos da Classe

A classe `DigitalButton` possui métodos fáceis de usar para detectar os estados de dispositivos binários, como botões ou sensores digitais. Esses métodos permitem que você saiba quando o dispositivo está ativo, quando foi ativado ou desativado. Vamos entender como cada um funciona:

---

### press()

O método `press()` detecta o momento exato em que o dispositivo muda para o estado ativo. Ele informa quando algo foi "acionado", como um botão que acabou de ser pressionado.

#### Como funciona:
Se você quiser executar algo **apenas no momento em que o botão for pressionado**, use `press()`.

#### Exemplo:
```cpp
if(button.press()){
  Serial.println("Botão foi pressionado!");
}
```

---

### hold()

O método `hold()` verifica se o dispositivo está no estado ativo (por exemplo, um botão pressionado ou um sensor ativado). Ele retorna `true` enquanto o dispositivo estiver ativo.

#### Como funciona:
Imagine que você quer saber se alguém está segurando um botão. Enquanto o botão estiver pressionado, `hold()` retorna `true`.

#### Exemplo:
```cpp
if(button.hold()){ 
  Serial.println("Botão está sendo pressionado!");
}
```

---

### release()

O método `release()` detecta o momento exato em que o dispositivo muda para o estado inativo. Ele informa quando algo foi "solto", como um botão que deixa de ser pressionado.

#### Como funciona:
Se você quiser saber quando alguém tirou o dedo do botão, use `release()`.

#### Exemplo:
```cpp
if(button.release()){
  Serial.println("Botão foi solto!");
}
```

---

## Exemplo de Uso Prático

Este exemplo demonstra como utilizar a classe `DigitalButton` para monitorar os três estados de um botão digital conectado à **GPIO 0** de um ESP32: **pressionado**, **segurando** e **solto**. Quando o botão muda de estado, mensagens correspondentes são exibidas no monitor serial.

O botão é configurado com o resistor interno **pull-up**, tornando este exemplo ideal para botões que conectam a GPIO ao GND quando pressionados. Este código é didático e ajuda a entender como detectar e reagir aos diferentes estados de dispositivos binários.

**Nota:** A **GPIO 0** possui funções especiais em muitos ESP32 (modo bootloader), por isso deve ser usada com moderação. Este exemplo é adequado para aprendizado e testes simples.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

// Creates the object for the button on GPIO 0. | Cria o objeto para o botão na GPIO 0.
DigitalButton button(0, true);

void setup() {
  Serial.begin(115200); // Initializes serial communication. | Inicializa a comunicação serial.
  button.begin();       // Initializes button monitoring. | Inicializa o monitoramento do botão.
}

void loop() {
  // Checks if the button was pressed. | Verifica se o botão foi pressionado.
  if (button.press()) {
    Serial.println("Button - Press"); // Message when the button is pressed. | Mensagem quando o botão é pressionado.
  }

  // Checks if the button is being held. | Verifica se o botão está sendo segurado.
  if (button.hold()) {
    Serial.println("Button - Hold"); // Message while the button is held. | Mensagem enquanto o botão está sendo segurado.
  }

  // Checks if the button was released. | Verifica se o botão foi solto.
  if (button.release()) {
    Serial.println("Button - Release"); // Message when the button is released. | Mensagem quando o botão é solto.
  }

  delay(100); // Prevents excessive readings. | Evita leituras excessivas.
}

```
-----
| [Índece de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |