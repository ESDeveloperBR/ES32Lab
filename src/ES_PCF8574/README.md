| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
-----

# Documentação da Classe ES_PCF8574

A classe `ES_PCF8574` foi desenvolvida especificamente para o controle do expansor de portas I2C PCF8574 em projetos com ESP32, integrados à ES32Lab. Essa classe permite uma interação direta e eficiente com as GPIOs do expansor, utilizando métodos dedicados para operações digitais e avançadas.

Entre suas funcionalidades, a `ES_PCF8574` oferece:
- **Leitura e Escrita Digital**: Métodos otimizados para configurar e ler o estado lógico das GPIOs do PCF8574, possibilitando controle direto sobre dispositivos conectados à expansão.
- **Leitura de Botões**: Recursos dedicados para a detecção de ações em botões, como a manutenção do pressionamento, a detecção do instante de pressão e a liberação, facilitando a integração de botões com diferentes comportamentos de leitura.
- **Simulação de PWM**: Implementa um simulador de PWM que permite controlar a intensidade de sinais nas GPIOs da expansão, com uma frequência máxima de 200 Hz, ideal para controlar LEDs e outros dispositivos que requerem ajustes de intensidade.
- **Controle de Motores com Ponte H**: Capacidades de controle de motores DC através da associação de GPIOs do PCF8574 a uma ponte H, incluindo métodos para ajustar a direção e a velocidade, além de possibilitar a inversão de comandos para adequação da fiação.

Com essas funcionalidades, a classe `ES_PCF8574` torna-se uma solução completa e prática para gerenciar múltiplos dispositivos e componentes, ampliando a flexibilidade e o potencial de projetos desenvolvidos com a ES32Lab.

---

## Construtor

### `ES_PCF8574(uint8_t address)`

O construtor `ES_PCF8574` inicializa uma instância da classe para o controle do expansor PCF8574 através do protocolo I2C. Esse endereço é essencial para garantir que a comunicação com o dispositivo seja direcionada ao módulo correto no barramento I2C, especialmente em setups que envolvem múltiplos dispositivos I2C.

- **Parâmetro**:
  - `address`: Define o endereço do PCF8574 no barramento I2C, possibilitando a identificação única do expansor durante a comunicação e evitando conflitos com outros dispositivos conectados.

---

## Configuração no `setup()`

Os métodos descritos nesta seção são utilizados na função `setup()` para a configuração inicial do expansor PCF8574, integrado à ES32Lab. O método principal é o `begin()`, que deve ser sempre chamado para iniciar a comunicação I2C com o expansor. Métodos adicionais, como `pwmBegin()` e `motorBegin()`, são opcionais e devem ser utilizados apenas quando for necessário habilitar funcionalidades extras, como o simulador de PWM ou o controle de motores.

### begin()

O método `begin` é o principal para configurar o expansor. Ele inicializa a comunicação I2C, permitindo operações básicas de leitura e escrita nas GPIOs do PCF8574. Além disso, oferece a opção de ativar o simulador PWM, permitindo que as GPIOs do expansor gerem sinais PWM com frequência e duty cycle configuráveis (até 200 Hz). 

Caso não seja necessário utilizar o simulador PWM ou outras funções extras, basta chamar `begin()` sem parâmetros. Para ativar o simulador PWM, utilize `begin(true)`.

#### Sintaxe:
`boolean begin(boolean pwmSimulation)`

#### Parâmetro:
  - `pwmSimulation`: Define se o simulador PWM será ativado. Utilize `true` para ativar o PWM ou `false` (ou omita o parâmetro) para operar apenas com leitura e escrita digitais.

#### Retorno:
  - Retorna `true` se a comunicação com o expansor foi inicializada com sucesso e o PWM ativado, se solicitado. Retorna `false` caso ocorra algum erro na inicialização.

#### Exemplo de uso:

**`expander.begin();`**

Inicializa a comunicação I2C com o PCF8574 integrado à ES32Lab sem ativar o simulador PWM. Essa configuração é suficiente para operações básicas de leitura e escrita digitais.

**`expander.begin(true);`**

Inicia a comunicação I2C com o PCF8574 e ativa o simulador PWM, permitindo o controle PWM com frequência máxima de 200 Hz.

### pwmBegin()

O método `pwmBegin` é um atalho para inicializar o expansor com o simulador PWM ativado. Ele é equivalente a chamar o método `begin(true)` diretamente. Este método deve ser utilizado quando o projeto exige apenas a ativação do PWM, sem outras operações de configuração.

#### Sintaxe:
`boolean pwmBegin()`

#### Retorno:
  - Retorna `true` se a comunicação com o expansor e o simulador PWM foram inicializados com sucesso, ou `false` se houver falha.

#### Exemplo de uso:

**`expander.pwmBegin();`**

Inicializa o expansor PCF8574 com o simulador PWM ativo, permitindo o uso das GPIOs para geração de sinais PWM, com uma frequência máxima de 200 Hz.

### motorBegin()

O método `motorBegin` é utilizado na configuração inicial do controle de motores DC por meio de uma ponte H conectada às GPIOs do expansor. Ele associa duas GPIOs específicas ao controle de um motor, permitindo o uso dos métodos de rotação e parada do motor.

Assim como o método `begin()`, `motorBegin()` deve ser configurado no `setup()`, antes de qualquer comando de rotação. Este método deve ser chamado para cada motor que será controlado pelo expansor.

#### Sintaxe:
`boolean motorBegin(uint8_t motorID, uint8_t controlPin1, uint8_t controlPin2)`

#### Parâmetros:
  - `motorID`: Identificação do motor para controle. É usado nos métodos subsequentes de controle de rotação.
  - `controlPin1`: GPIO do expansor usada como o primeiro pino de controle da ponte H (EX0 a EX7).
  - `controlPin2`: GPIO do expansor usada como o segundo pino de controle da ponte H (EX0 a EX7).

#### Retorno:
  - Retorna `true` se o motor foi configurado corretamente.

#### Exemplo de uso:

**`expander.motorBegin(1, EX4, EX5);`**

Configura o motor 1, associando as GPIOs EX4 e EX5 do expansor PCF8574 para o controle por meio de uma ponte H.

---

### Resumo para Configuração no `setup()`

1. Sempre utilize **`expander.begin();`** no `setup()` para inicializar a comunicação I2C.
2. Caso precise de funcionalidades adicionais, como PWM ou controle de motores:
   - Use **`expander.begin(true);`** ou **`expander.pwmBegin();`** para ativar o simulador PWM.
   - Use **`expander.motorBegin(motorID, controlPin1, controlPin2);`** para configurar motores.
3. Certifique-se de que todas as configurações sejam realizadas no `setup()` antes de utilizar os métodos correspondentes no `loop()`.

Com essas configurações, o expansor PCF8574 estará pronto para operar de forma eficiente, com suporte completo às funcionalidades extras oferecidas pela ES32Lab.

**Atenção:** Se for utilizar a ponte H da ES32Lab, certifique-se de que os jumpers estão conectando as GPIOs do expansor ao circuito da ponte H.

[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)

---

## Scanner I2C

### scanI2C()

O método `scanI2C` realiza uma varredura completa no barramento I2C, detectando todos os dispositivos conectados e retornando seus endereços. Essa funcionalidade é particularmente útil para verificar a conectividade e assegurar que os dispositivos estejam corretamente endereçados e ativos no barramento.

#### Sintaxe:
`String scanI2C()`

#### Retorno:
- Uma `String` contendo os endereços I2C detectados, formatados em hexadecimal e separados por vírgulas (ex.: "0x20, 0x21, 0x22"). Caso nenhum dispositivo seja encontrado, o método retorna uma `String` vazia (`""`).

Este método permite uma verificação rápida e eficiente do estado do barramento I2C, facilitando a depuração de conexões e a identificação de dispositivos. Em caso de erro desconhecido, uma mensagem correspondente é incluída na `String` de retorno.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander;  // O endereço I2C não é obrigatório para o método scanI2C() no momento de instanciar o objeto

void setup() {
  Serial.begin(115200);
  expander.begin();

  String i2cDevices = expander.scanI2C();
  if (i2cDevices != "") {
    Serial.println("Dispositivos I2C encontrados:");
    Serial.println(i2cDevices);
  } else {
    Serial.println("Nenhum dispositivo I2C encontrado.");
  }
}

void loop() {
}
```

---

## Métodos para Controle das GPIOs

Esses métodos permitem o controle direto das GPIOs do expansor PCF8574, integrado à ES32Lab, possibilitando operações básicas de leitura e escrita em cada pino disponível. Com essas funções, é possível configurar o estado lógico de cada GPIO e monitorar entradas digitais conectadas ao expansor.

### digitalWrite()

O método `digitalWrite` configura uma GPIO específica do PCF8574, parte integrante da ES32Lab, para um valor lógico determinado, permitindo o controle de dispositivos conectados à expansão, como LEDs e relés. Com ele, é possível ativar ou desativar componentes de maneira precisa e simplificada, simulando o comportamento das funções nativas `digitalWrite` do ESP32.

#### Sintax:
`digitalWrite(uint8_t pin, boolean value)`

#### Parâmetros:
  - `pin`: Número da GPIO no expansor PCF8574 que será configurada (EX0 a EX7), permitindo o acesso direto a cada pino.
  - `value`: Valor lógico a ser atribuído à GPIO (use `true` para HIGH e `false` para LOW), definindo o estado de ativação do pino.

Esse método fornece um meio essencial de controlar dispositivos conectados ao PCF8574 da ES32Lab, ideal para projetos que requerem controle de saída em uma interface I2C expandida.

#### Exemplo de Uso: digitalWrite()

Este exemplo demonstra como utilizar o método `digitalWrite()` para controlar o estado lógico de uma GPIO no expansor PCF8574. No caso, o LED conectado à GPIO EX0 na ES32Lab pisca intermitentemente, alternando entre os estados HIGH e LOW com um intervalo de 1 segundo.

- Quando a GPIO EX0 é configurada como `HIGH`, o LED é aceso.
- Quando a GPIO EX0 é configurada como `LOW`, o LED é apagado.
- Este exemplo é ideal para demonstrar o controle básico de dispositivos conectados às GPIOs do expansor.

**Atenção:** Se for utilizar os LEDs integrados da ES32Lab, certifique-se de que os jumpers estão conectando as GPIOs do expansor ao circuito dos LEDs. 

[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x38);  // Instancia o objeto 'expander' com o endereço fornecido do PCF8574

void setup() {
  expander.begin();  // Inicializa o expansor I2C PCF8574
}

void loop() {
  expander.digitalWrite(EX0, HIGH);  // Define a GPIO EX0 como HIGH (acende o LED)
  delay(1000);  // Aguarda 1 segundo
  
  expander.digitalWrite(EX0, LOW);  // Define a GPIO EX0 como LOW (apaga o LED)
  delay(1000);  // Aguarda 1 segundo
}
```

### digitalRead()

O método `digitalRead` lê o estado lógico atual de uma GPIO específica do PCF8574, integrado à ES32Lab, permitindo verificar se o pino está em estado HIGH ou LOW. Ele é útil para monitorar entradas digitais, como sensores ou botões, conectados à expansão I2C.

#### Sintaxe:
`boolean digitalRead(uint8_t pin)`

#### Parâmetros:
  - `pin`: Número da GPIO no expansor PCF8574 a ser lida (EX0 a EX7), identificando o pino que será monitorado.

#### Retorno:
  - Um valor lógico da GPIO, retornando `0` para LOW e `1` para HIGH.

Ao possibilitar a leitura do estado lógico de cada GPIO, o método `digitalRead` facilita o monitoramento em tempo real de sensores e dispositivos digitais conectados ao PCF8574 da ES32Lab, ampliando a capacidade do ESP32 de reagir a entradas externas por meio da interface I2C.

#### Exemplo de Uso: digitalRead()

Este exemplo demonstra como utilizar o método `digitalRead()` para realizar uma leitura digital em uma GPIO do expansor PCF8574. No caso, a GPIO EX0 do expansor é monitorada, e o valor lógico lido (HIGH ou LOW) é exibido no monitor serial.

- Se a GPIO EX0 receber um sinal lógico HIGH, será exibido o número `1` no terminal serial.
- Se a GPIO EX0 estiver em estado LOW, será exibido o número `0`.

**Atenção:** Certifique-se de que o dispositivo conectado à GPIO EX0 esteja devidamente configurado e que a tensão lógica utilizada seja compatível (3.3V ou 5V). Para conexões feitas através dos circuitos da ES32Lab, consulte os jumpers de configuração.

[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x38);  // Instancia o objeto 'expander' com o endereço fornecido do PCF8574

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial
  expander.begin();      // Inicializa o expansor I2C PCF8574
}

void loop() {
  boolean readExpander;               // Variável para armazenar o valor lido da GPIO do expansor
  readExpander = expander.digitalRead(EX0);  // Lê o estado lógico da GPIO EX0
  Serial.println(readExpander);      // Exibe o valor lido no terminal serial
  delay(1000);                       // Aguarda 1 segundo
}
```

---

## Controle de Botões

A classe `ES_PCF8574`, integrada à ES32Lab, oferece métodos dedicados para monitorar GPIOs configuradas como botões. Com esses métodos, é possível detectar ações de pressão, manutenção e liberação de um botão, tornando o controle de dispositivos interativos mais preciso e responsivo. Cada método permite configurar o nível lógico que representa o estado de pressionado ou solto, oferecendo flexibilidade para diferentes tipos de hardware.

### btHold()

O método `btHold` verifica se um botão conectado a uma GPIO do expansor está pressionado, retornando `true` enquanto o botão permanece pressionado, de acordo com o nível lógico configurado. Ele é útil para monitorar ações de longa duração, como pressionamentos constantes ou contínuos.

#### Sintaxe:
`boolean btHold(uint8_t pin, boolean activateHigh)`

#### Parâmetros:
  - `pin`: Número da GPIO usada como entrada de botão no expansor PCF8574 (EX0 a EX7).
  - `activateHigh`: Define o nível lógico que representa o botão pressionado (`true` para HIGH, `false` para LOW).

#### Retorno:
  - Retorna `true` enquanto o botão estiver sendo pressionado, e `false` caso contrário.

#### Exemplo de uso:

**`expander.btHold(EX2, true);`**

Verifica se o botão conectado à GPIO EX2 está pressionado, considerando o nível HIGH como pressionado.

### btPress()

O método `btPress` detecta o momento exato em que ocorre a transição do estado lógico de baixo para alto (ou vice-versa, conforme configurado por `activateHigh`) na GPIO, indicando que o botão foi pressionado. Este método é ideal para detectar o primeiro instante do pressionamento do botão, ativando ações com base nesse evento.

#### Sintaxe:
`boolean btPress(uint8_t pin, boolean activateHigh)`

#### Parâmetros:
  - `pin`: Número da GPIO usada como entrada de botão no expansor PCF8574 (EX0 a EX7).
  - `activateHigh`: Define a transição lógica para detecção do botão pressionado (`true` para transição de LOW para HIGH, `false` para transição de HIGH para LOW).

#### Retorno:
  - Retorna `true` no instante em que o botão é pressionado, e `false` caso contrário.

#### Exemplo de uso:

**`expander.btPress(EX3, true);`**

Detecta o momento exato em que o botão conectado à GPIO EX3 é pressionado, considerando a transição de LOW para HIGH.

### btRelease()

O método `btRelease` identifica o momento exato em que o botão conectado à GPIO do expansor é liberado, ou seja, quando ocorre a transição do estado lógico de alto para baixo (ou vice-versa, conforme configurado por `activateHigh`). Esse método é útil para ações que devem ser executadas no instante da liberação do botão.

#### Sintaxe:
`boolean btRelease(uint8_t pin, boolean activateHigh)`

#### Parâmetros:
  - `pin`: Número da GPIO usada como entrada de botão no expansor PCF8574 (EX0 a EX7).
  - `activateHigh`: Define a transição lógica para detecção do botão liberado (`true` para transição de HIGH para LOW, `false` para transição de LOW para HIGH).

#### Retorno:
  - Retorna `true` no instante em que o botão é liberado, e `false` caso contrário.

#### Exemplo de uso:

**`expander.btRelease(EX4, true);`**

Detecta o momento exato em que o botão conectado à GPIO EX4 é liberado, considerando a transição de HIGH para LOW.

### Exemplo de Uso: Controle de Botões no expansor i2C

Este exemplo demonstra como utilizar os métodos `btPress()`, `btHold()`, e `btRelease()` para monitorar o estado de um botão conectado à GPIO EX0 do expansor PCF8574 na ES32Lab. Esses métodos permitem detectar os seguintes estados do botão:

- **btPress()**: Detecta o momento exato em que o botão é pressionado.
- **btHold()**: Detecta quando o botão está sendo mantido pressionado.
- **btRelease()**: Detecta o momento exato em que o botão é solto.

**Descrição do funcionamento:**
- Com as configurações deste exemplo, o botão é identificado como pressionado através de um pulso lógico alto (HIGH) na GPIO do expansor.
- Caso não tenha um botão físico conectado, você pode simular a interação utilizando um fio jumper. Conecte uma extremidade do jumper à GPIO EX0 do expansor e a outra a uma fonte de tensão de 3.3V. Ao tocar e remover o fio do terminal de 3.3V, o sistema irá detectar as ações de pressão, manutenção e liberação.

Este exemplo é ideal para entender o comportamento do controle de botões e permite simulação básica mesmo sem o hardware completo.

**Atenção:** Certifique-se de que o jumper ou botão esteja conectado corretamente à GPIO do expansor e, para conexões feitas através dos circuitos da ES32Lab, consulte os jumpers de configuração.

[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_PCF8574 expander(0x38);  // Instancia o objeto 'expander' com o endereço fornecido do PCF8574

void setup() {
  Serial.begin(115200);
  expander.begin();  // Inicializa o expansor I2C PCF8574
}

void loop() {
  if (expander.btPress(EX0)) {  // Detecta quando o botão conectado à GPIO EX0 é pressionado
    Serial.println("Button 0 Press");
  }

  if (expander.btHold(EX0)) {  // Detecta quando o botão conectado à GPIO EX0 está sendo mantido pressionado
    Serial.println("Button 0 Hold");
    delay(500);  // Aguarda 500 milissegundos antes de repetir a mensagem
  }

  if (expander.btRelease(EX0)) {  // Detecta quando o botão conectado à GPIO EX0 é solto
    Serial.println("Button 0 Released");
  }
}

```

----

## Simulação de PWM

A classe `ES_PCF8574`, integrada à ES32Lab, oferece uma funcionalidade de simulação de PWM para as GPIOs do expansor PCF8574. Essa simulação permite o controle de intensidade de dispositivos como LEDs e pequenos motores, com um sinal de saída ajustável em frequência e duty cycle. A frequência máxima suportada pelo simulador PWM é de **200 Hz**, devido às limitações de comunicação no barramento I2C.

Para utilizar o método de simulação de PWM, é necessário que o simulador esteja ativo. Isso pode ser feito inicializando o expansor com `begin(true)` ou `pwmBegin()`. Uma vez ativado, o simulador PWM permite o ajuste de intensidade ou velocidade em dispositivos conectados às GPIOs.

### pwmWrite()

O método `pwmWrite` configura uma GPIO do expansor PCF8574 para gerar um sinal PWM simulado, com duty cycle e frequência especificados. Isso possibilita um controle preciso sobre a intensidade ou a velocidade de dispositivos conectados, proporcionando uma forma prática de simular PWM mesmo em um expansor I2C que não é projetado para operações de alta velocidade.

#### Sintaxe:
`void pwmWrite(uint8_t pin, uint8_t dutyCycle, uint8_t frequency)`

#### Parâmetros:
  - `pin`: Número da GPIO a ser configurada para o PWM (EX0 a EX7), definindo o pino de saída do sinal.
  - `dutyCycle`: Ciclo de trabalho do sinal PWM, ajustável entre 0% e 100%, onde 0% significa desativado e 100% significa intensidade máxima.
  - `frequency`: Frequência do sinal PWM, configurável entre 0 Hz e 200 Hz, sendo o limite máximo imposto pelo expansor para garantir a estabilidade do sinal.

Esse método torna possível controlar a intensidade de componentes analógicos, simulando um sinal PWM de baixa frequência diretamente nas GPIOs da expansão da ES32Lab.

#### Exemplo de uso:

**`expander.pwmWrite(EX5, 50, 100);`**

Configura a GPIO EX5 do expansor PCF8574 para emitir um sinal PWM simulado com duty cycle de 50% e frequência de 100 Hz. Esse ajuste resulta em uma saída com metade da intensidade máxima, ideal para controle de brilho de LEDs ou ajuste de velocidade em pequenos motores.

### Exemplo de Código - PWM com Expansor I2C

Este exemplo demonstra como ativar o simulador de pulso PWM no expansor I2C da ES32Lab, controlando a frequência de pisca de dois LEDs integrados. No código, o LED branco da ES32Lab pisca duas vezes por segundo, enquanto o LED laranja pisca quatro vezes por segundo, ambos de forma intermitente com um duty cycle de 50%.

**Importante:** Para que os LEDs branco e laranja da ES32Lab funcionem com o código proposto, é necessário garantir que o jumper branco de cada um desses LEDs esteja devidamente conectado. 

[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)
 

```cpp
#include <Arduino.h>
#include <ES32Lab.h>  // Library used to facilitate the use of the ES32Lab board | LIB utilizada para facilitar a utilização da placa ES32Lab
ES_PCF8574 expander(0x38);  // Instantiates the 'expander' object with the given address | Instancia o objeto 'expander' com o endereço fornecido.

void setup() {
  Serial.begin(115200);

  expander.pwmBegin();  // Starts the I2C expander by enabling the PWM simulator. An alternative to enable the PWM simulator of the I2C expander is to use the command 'begin(true)'. | Inicia o expansor I2C ativando o simulador PWM. Uma alternativa para ativar o simulador PWM do expansor I2C é utilizando o comando 'begin(true)'.
  expander.pwmWrite(EX0, 50, 2);  // Enables the PWM simulator on pin EX0 with a duty cycle of 50% and a frequency of 2 hertz. | Ativa o simulador PWM no pino EX0, com um ciclo de trabalho de 50% e frequência de 2 hertz.
  expander.pwmWrite(EX1, 50, 4);  // Enables the PWM simulator on pin EX1 with a duty cycle of 50% and a frequency of 4 hertz. | Ativa o simulador PWM no pino EX1, com um ciclo de trabalho de 50% e frequência de 4 hertz.
}

void loop() {

}
```

---

## Controle de Motores

A classe `ES_PCF8574`, integrada à ES32Lab, facilita o controle de motores DC por meio de uma ponte H associada às GPIOs do expansor. Para utilizar os métodos de controle de motores, é necessário configurar os parâmetros com o método `motorBegin()` no `setup()`. Esse processo inicializa as GPIOs do expansor para funcionar como pinos de controle para o motor especificado.

### motorBegin()

O método `motorBegin` associa duas GPIOs do PCF8574 a uma ponte H, preparando-as para o controle de um motor DC. Esse método deve ser chamado uma vez na função `setup()` para cada motor a ser controlado.

#### Sintaxe:
`boolean motorBegin(uint8_t motorID, uint8_t controlPin1, uint8_t controlPin2)`

#### Parâmetros:
  - `motorID`: Identificação do motor para controle. Esse valor é usado nos métodos de rotação e parada.
  - `controlPin1`: Pino de controle 1 do motor (EX0 a EX7), conectando a um dos terminais da ponte H.
  - `controlPin2`: Pino de controle 2 do motor (EX0 a EX7), conectando ao segundo terminal da ponte H.

#### Retorno:
  - Retorna `true` se o motor for inicializado corretamente.

#### Exemplo de uso:

**`expander.motorBegin(1, EX4, EX5);`**

Inicializa o controle do motor 1, associando as GPIOs EX4 e EX5 do expansor PCF8574 para operação com uma ponte H.

### motorRotationA()

O método `motorRotationA` ativa a rotação do motor em uma direção específica (sentido A) com a velocidade indicada. 

#### Sintaxe:
`void motorRotationA(uint8_t motorID, uint8_t speed)`

#### Parâmetros:
  - `motorID`: Identificação do motor para controle.
  - `speed`: Velocidade do motor, variando entre 0% e 100%.

#### Exemplo de uso:

**`expander.motorRotationA(1, 8);`**

Ativa o motor 1 no sentido A a uma velocidade de 8% da máxima.

### motorRotationB()

O método `motorRotationB` ativa a rotação do motor no sentido oposto (sentido B) com a velocidade indicada.

#### Sintaxe:
`void motorRotationB(uint8_t motorID, uint8_t speed)`

#### Parâmetros:
  - `motorID`: Identificação do motor para controle.
  - `speed`: Velocidade do motor, variando entre 0% e 100%.

#### Exemplo de uso:

**`expander.motorRotationB(1, 50);`**

Ativa o motor 1 no sentido B a uma velocidade de 50% da máxima.

### motorStop()

O método `motorStop` para o motor indicado, desativando os sinais de controle nas GPIOs associadas.

#### Sintaxe:
`void motorStop(uint8_t motorID)`

#### Parâmetro:
  - `motorID`: Identificação do motor para controle.

#### Exemplo de uso:

**`expander.motorStop(1);`**

Para o motor 1.

### invertMotorCommands()

O método `invertMotorCommands` inverte a direção dos comandos de rotação para o motor especificado, ajustando o sentido de rotação sem alterar a fiação.

#### Sintaxe:
`void invertMotorCommands(uint8_t motorID)`

#### Parâmetro:
  - `motorID`: Identificação do motor para controle.

#### Exemplo de uso:

**`expander.invertMotorCommands(1);`**

Inverte os comandos de rotação do motor 1.

### invertMotorStatus()

O método `invertMotorStatus` verifica se os comandos de rotação do motor foram invertidos.

#### Sintaxe:
`boolean invertMotorStatus(uint8_t motorID)`

#### Parâmetro:
  - `motorID`: Identificação do motor para controle.

#### Retorno:
  - Retorna `true` se os comandos foram invertidos, `false` caso contrário.

#### Exemplo de uso:

**`expander.invertMotorStatus(1);`**

Retorna `true` se os comandos do motor 1 foram invertidos.

### getMotorFrequency()

O método `getMotorFrequency` obtém a frequência de operação associada ao motor.

#### Sintaxe:
`uint8_t getMotorFrequency(uint8_t motorID)`

#### Parâmetro:
  - `motorID`: Identificação do motor para controle.

#### Retorno:
  - Frequência atual do motor em hertz.

#### Exemplo de uso:

**`expander.getMotorFrequency(1);`**

Obtém a frequência configurada para o motor 1.

### setMotorFrequency()

O método `setMotorFrequency` define uma nova frequência de operação para o motor especificado.

#### Sintaxe:
`void setMotorFrequency(uint8_t motorID, uint8_t frequency)`

#### Parâmetros:
  - `motorID`: Identificação do motor para controle.
  - `frequency`: Frequência desejada para o motor, em hertz.

#### Exemplo de uso:

**`expander.setMotorFrequency(1, 50);`**

Define a frequência de operação do motor 1 para 50 Hz.

### Exemplo Completo de Controle de Motor
Este exemplo demonstra como configurar e controlar um motor com a ES32Lab usando o expansor I2C PCF8574. O motor gira em um sentido por um período de tempo e depois inverte a direção, repetindo o ciclo.
[Clique aqui para ser direcionado para um vídeo explicando como identificar os jumpers de conexão aos circuitos i2C](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s)


```cpp
#include <Arduino.h>
#include <ES32Lab.h>  // Biblioteca para facilitar o uso da ES32Lab

ES_PCF8574 expander(0x38);  // Instancia o objeto 'expander' com o endereço fornecido

void setup() {
  expander.motorBegin(1, EX4, EX5); // Configura o motor 1 com controle nas GPIOs EX4 e EX5 do expansor PCF8574
}

void loop() {
  expander.motorRotationA(1, 8);  // Roda o motor 1 no sentido A a 8% da velocidade máxima
  delay(8000);                    // Pausa o loop por 8 segundos

  expander.motorRotationB(1, 50); // Roda o motor 1 no sentido B a 50% da velocidade máxima
  delay(2000);                    // Pausa o loop por 2 segundos
}
```

---
