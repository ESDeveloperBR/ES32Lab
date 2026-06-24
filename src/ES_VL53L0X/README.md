| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_VL53L0X

A classe `ES_VL53L0X` é um componente da biblioteca ES32Lab desenvolvido para simplificar o uso do sensor de distância VL53L0X em projetos com ESP32 e com a PCB ES32Lab. O VL53L0X é um sensor de distância do tipo *time-of-flight* (ToF), capaz de medir distância em milímetros usando emissão e recepção de luz infravermelha.

Dentro da ES32Lab, esta classe foi criada para oferecer uma interface direta, didática e padronizada para inicializar o sensor, realizar leituras de distância, aplicar correção de offset, configurar timeout de leitura e ajustar o tempo interno usado em cada medição. Dessa forma, o usuário pode utilizar o sensor com poucos comandos, sem precisar lidar diretamente com registradores internos, sequências de calibração ou detalhes de comunicação I2C.

A `ES_VL53L0X` pertence oficialmente à biblioteca ES32Lab e pode ser utilizada diretamente através do arquivo principal da biblioteca:

```cpp
#include <ES32Lab.h>
```

Após incluir `ES32Lab.h`, a classe `ES_VL53L0X` já estará disponível para uso no sketch.

### **Principais Recursos**
- **Leitura de Distância em Milímetros**: método `read()` retorna a distância já corrigida pelo offset configurado.
- **Comunicação I2C Integrada**: a classe inicializa e utiliza o barramento I2C automaticamente no uso padrão da ES32Lab.
- **Endereço I2C Configurável**: permite utilizar o endereço padrão `0x29` ou alterar o endereço final do sensor durante a inicialização.
- **Calibração de Offset**: permite compensar a distância inicial indicada pelo sensor, principalmente quando ele está montado em suportes, carcaças ou habitáculos.
- **Timeout de Leitura**: evita que o programa fique aguardando indefinidamente caso o sensor não responda corretamente.
- **Ajuste do Tempo de Medição**: método `setMeasurementTimingBudget()` permite equilibrar velocidade de leitura e estabilidade.
- **Integração com o Padrão ES32Lab**: utiliza nomenclatura, estilo e organização compatíveis com as demais classes da biblioteca.

---

## Índice

1. [Funcionamento Geral do VL53L0X](#funcionamento-geral-do-vl53l0x)
2. [Ligação Elétrica](#ligação-elétrica)
3. [Endereço I2C](#endereço-i2c)
4. [Calibração da Distância Inicial](#calibração-da-distância-inicial)
5. [Timing Budget](#timing-budget)
6. [Constantes da Classe](#constantes-da-classe)
    - [`ES_VL53L0X_VERSION`](#es_vl53l0x_version)
    - [`ES_VL53L0X_DEFAULT_ADDRESS`](#es_vl53l0x_default_address)
    - [`ES_VL53L0X_INVALID_DISTANCE`](#es_vl53l0x_invalid_distance)
7. [Construtor](#construtor)
8. [Inicialização do Sensor](#inicialização-do-sensor)
    - [`begin(boolean io2v8 = true)`](#beginboolean-io2v8--true)
    - [`begin(uint8_t address, boolean io2v8 = true)`](#beginuint8_t-address-boolean-io2v8--true)
    - [`begin(TwoWire &bus, uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, boolean io2v8 = true)`](#begintwowire-bus-uint8_t-address--es_vl53l0x_default_address-boolean-io2v8--true)
9. [Estado e Comunicação I2C](#estado-e-comunicação-i2c)
    - [`isInitialized()`](#isinitialized)
    - [`isConnected()`](#isconnected)
    - [`setBus(TwoWire &bus)`](#setbustwowire-bus)
    - [`getBus()`](#getbus)
    - [`setAddress(uint8_t address)`](#setaddressuint8_t-address)
    - [`getAddress()`](#getaddress)
    - [`lastStatus()`](#laststatus)
10. [Timeout de Leitura](#timeout-de-leitura)
    - [`setTimeout(uint16_t timeoutMs)`](#settimeoutuint16_t-timeoutms)
    - [`getTimeout()`](#gettimeout)
    - [`timeoutOccurred()`](#timeoutoccurred)
11. [Leitura de Distância](#leitura-de-distância)
    - [`read()`](#read)
    - [`lastDistance()`](#lastdistance)
12. [Offset de Distância](#offset-de-distância)
    - [`setDistanceOffset(uint16_t offsetMm)`](#setdistanceoffsetuint16_t-offsetmm)
    - [`getDistanceOffset()`](#getdistanceoffset)
13. [Tempo de Medição](#tempo-de-medição)
    - [`setMeasurementTimingBudget(uint32_t budgetUs)`](#setmeasurementtimingbudgetuint32_t-budgetus)
    - [`getMeasurementTimingBudget()`](#getmeasurementtimingbudget)
14. [Atributos Internos Relevantes](#atributos-internos-relevantes)
15. [Exemplo Completo: Leitura Simples de Distância](#exemplo-completo-leitura-simples-de-distância)
16. [Exemplo Completo: Ajuste do Timing Budget](#exemplo-completo-ajuste-do-timing-budget)
17. [Exemplo de Uso com Endereço I2C Personalizado](#exemplo-de-uso-com-endereço-i2c-personalizado)
18. [Recomendações de Uso](#recomendações-de-uso)
19. [Exemplos Oficiais](#exemplos-oficiais)

---

## Funcionamento Geral do VL53L0X

O VL53L0X mede distância usando a técnica *time-of-flight*. Em vez de estimar distância apenas pela intensidade da luz refletida, o sensor emite pulsos de luz infravermelha e analisa o tempo de retorno dessa luz após refletir no objeto à frente.

Na prática, isso permite obter uma leitura direta em milímetros. A classe `ES_VL53L0X` encapsula toda a sequência básica necessária para preparar o sensor, fazer a calibração inicial interna, configurar os registradores essenciais e solicitar uma medição única sempre que o método `read()` é chamado.

O método de leitura pública da classe é propositalmente simples:

```cpp
uint16_t mm = distance.read();
```

Esse valor já considera o offset configurado por `setDistanceOffset()`. Portanto, se o sensor retornar internamente `54 mm` quando um objeto está encostado na referência física do projeto, e o offset estiver configurado como `50 mm`, a leitura entregue ao usuário será aproximadamente `4 mm`.

---

## Ligação Elétrica

No uso comum com a ES32Lab, o VL53L0X deve ser ligado ao barramento I2C da placa.

### Ligações principais:

| Pino do módulo VL53L0X | Ligação na ES32Lab / ESP32 |
| :------: | ------ |
| `VCC` | Alimentação compatível com o módulo utilizado |
| `GND` | GND |
| `SCL` | Pino SCL do barramento I2C. Na ES32Lab, normalmente `P22` |
| `SDA` | Pino SDA do barramento I2C. Na ES32Lab, normalmente `P21` |
| `XSHUT` | Opcional para uso com um único sensor |
| `GPIO1` | Não utilizado pela implementação atual da `ES_VL53L0X` |

No ecossistema da ES32Lab, o padrão de sinais lógicos é `3V3`. Para a maioria dos módulos VL53L0X comerciais usados com ESP32, a chamada padrão `begin()` já é a escolha recomendada.

No uso padrão, a classe chama `Wire.begin()` internamente durante `begin()`. Por isso, nos exemplos oficiais da ES32Lab para esta classe, o usuário não precisa inicializar manualmente o barramento I2C antes de chamar `distance.begin()`.

> **Atenção:**  
> Verifique o módulo físico utilizado. Alguns módulos VL53L0X possuem regulador e adaptação de nível lógico na própria placa do sensor. Outros podem expor sinais mais próximos do circuito integrado original. Em projetos com ES32Lab, use sempre ligações compatíveis com lógica de `3V3`.

### Sobre o pino `XSHUT`

O pino `XSHUT` permite desligar e religar logicamente o sensor. Para uso com apenas um VL53L0X, normalmente ele pode ficar sem controle direto pelo software, dependendo do módulo.

Esse pino passa a ser importante em aplicações com múltiplos sensores iguais no mesmo barramento I2C, porque todos os VL53L0X iniciam com o mesmo endereço padrão `0x29`. Para mudar o endereço de vários sensores individualmente, é necessário manter apenas um sensor ativo por vez durante a inicialização. Esse controle pode ser feito por GPIOs do ESP32, por um expansor como o `ES_PCF8574` ou por outro circuito dedicado.

### Sobre o pino `GPIO1`

O pino `GPIO1` do VL53L0X pode ser usado pelo sensor para sinalização de interrupção em aplicações mais avançadas. A implementação atual da classe `ES_VL53L0X` trabalha com leitura bloqueante via I2C usando `read()`, portanto esse pino não é necessário para os exemplos básicos e não é usado pela API pública atual.

---

## Endereço I2C

O endereço I2C padrão do VL53L0X após energizar é:

```cpp
0x29
```

Esse valor está disponível na constante:

```cpp
ES_VL53L0X_DEFAULT_ADDRESS
```

Para um único sensor no barramento I2C, normalmente não é necessário alterar esse endereço. Basta criar o objeto e chamar `begin()`:

```cpp
ES_VL53L0X distance;

void setup() {
    distance.begin();
}
```

Também é possível informar um endereço final diferente. Nesse caso, a classe inicializa o sensor no endereço padrão `0x29` e depois altera o endereço para o valor solicitado:

```cpp
ES_VL53L0X distance;

void setup() {
    distance.begin(0x30);
}
```

> **Importante:**  
> Apenas alterar o endereço por software não resolve sozinho o uso de múltiplos VL53L0X no mesmo barramento quando todos estão ligados ao mesmo tempo desde o início. Como todos iniciam em `0x29`, é necessário isolar os sensores durante a inicialização, normalmente usando `XSHUT`.

---

## Calibração da Distância Inicial

Uma característica importante do VL53L0X é que a leitura inicial pode variar conforme o sensor físico, o módulo utilizado, a posição de montagem, a existência de carcaça, a espessura de uma tampa, o alinhamento do sensor e a distância entre a janela óptica e o ponto mecânico considerado como referência.

Por isso, a classe `ES_VL53L0X` possui o método:

```cpp
distance.setDistanceOffset(50);
```

Esse método define um valor fixo, em milímetros, que será subtraído de todas as leituras retornadas por `read()`.

Para um sensor fora de qualquer carcaça, habitáculo ou suporte que afaste o módulo do ponto de referência, o valor recomendado como ponto de partida na ES32Lab é:

```cpp
distance.setDistanceOffset(50);
```

Esse valor representa uma calibração inicial prática para muitos módulos VL53L0X. Entretanto, ele não deve ser tratado como uma verdade absoluta para todos os sensores e montagens.

### Como ajustar o offset

1. Posicione um objeto na referência física que você deseja considerar como distância zero.
2. Faça leituras com o sensor sem aplicar offset, ou comece com um valor aproximado.
3. Observe a distância indicada.
4. Configure `setDistanceOffset()` com o valor necessário para que a leitura corrigida fique próxima do comportamento esperado.

Exemplo:

```cpp
distance.setDistanceOffset(50);
```

Se a distância medida internamente for menor ou igual ao offset configurado, a classe retorna `0`. Isso evita que uma subtração gere valores negativos, já que o retorno do método `read()` é do tipo `uint16_t`.

> **Nota:**  
> O offset é uma configuração feita em RAM. Ele deve ser configurado novamente no `setup()` sempre que o ESP32 reiniciar. A classe não grava esse valor em memória permanente.

---

## Timing Budget

O *measurement timing budget* é o tempo aproximado, em microssegundos, reservado pelo VL53L0X para realizar cada medição. Esse tempo influencia diretamente o equilíbrio entre velocidade de leitura e estabilidade.

Valores menores tornam as leituras mais rápidas, mas podem gerar mais variação entre medições consecutivas. Valores maiores tornam as leituras mais lentas, porém podem melhorar a estabilidade, principalmente em condições mais difíceis, como:

- alvo mais escuro;
- objeto mais distante;
- superfície inclinada;
- pouca reflexão;
- ambiente com interferências;
- necessidade de leituras mais repetíveis.

A classe permite configurar esse tempo com:

```cpp
distance.setMeasurementTimingBudget(200000);
```

O valor é informado em microssegundos. Portanto:

```cpp
200000 us = 200 ms
```

O valor mínimo aceito internamente pela classe é `20000 us`. Valores menores são recusados e o método retorna `false`.

> **Importante:**  
> `setMeasurementTimingBudget()` deve ser chamado depois de `begin()`, pois o sensor precisa estar inicializado antes de receber essa configuração.

---

## Constantes da Classe

### `ES_VL53L0X_VERSION`

Indica a versão atual da classe `ES_VL53L0X` dentro da biblioteca ES32Lab.

#### Sintaxe:
```cpp
ES_VL53L0X_VERSION
```

#### Exemplo de Uso:
```cpp
Serial.println(ES_VL53L0X_VERSION);
```

---

### `ES_VL53L0X_DEFAULT_ADDRESS`

Define o endereço I2C padrão de 7 bits usado pelo VL53L0X após energizar.

#### Valor:
```cpp
0x29
```

#### Exemplo de Uso:
```cpp
ES_VL53L0X distance(ES_VL53L0X_DEFAULT_ADDRESS);
```

---

### `ES_VL53L0X_INVALID_DISTANCE`

Define o valor retornado quando uma leitura não é válida, quando o sensor não foi inicializado ou quando ocorre timeout durante a leitura.

#### Valor:
```cpp
65535
```

#### Exemplo de Uso:
```cpp
uint16_t mm = distance.read();

if (mm == ES_VL53L0X_INVALID_DISTANCE) {
    Serial.println("Leitura invalida.");
}
```

---

## Construtor

### `ES_VL53L0X(uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, TwoWire &bus = Wire)`

Cria um objeto da classe `ES_VL53L0X` e armazena as configurações desejadas de endereço I2C e barramento.

O construtor não acessa o sensor e não faz comunicação I2C. A comunicação real começa somente quando um dos métodos `begin()` é chamado.

#### Sintaxe:
```cpp
ES_VL53L0X distance;
ES_VL53L0X distance(0x29);
ES_VL53L0X distance(0x30, Wire);
```

#### Parâmetros:
- **`address`**: endereço I2C final desejado para o sensor. O valor padrão é `ES_VL53L0X_DEFAULT_ADDRESS`, equivalente a `0x29`.
- **`bus`**: barramento I2C usado para comunicação. O padrão é `Wire`.

#### Exemplo de Uso:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_VL53L0X distance;

void setup() {
    Serial.begin(115200);
    distance.begin();
}

void loop() {
    Serial.println(distance.read());
    delay(100);
}
```

---

## Inicialização do Sensor

O sensor deve ser inicializado no `setup()` antes de qualquer leitura. A inicialização configura a comunicação I2C, verifica se há um VL53L0X respondendo no endereço esperado, valida o identificador interno do sensor, carrega configurações essenciais e executa calibrações internas necessárias para leitura.

### `begin(boolean io2v8 = true)`

Inicializa o sensor usando o barramento e o endereço armazenados no objeto.

Essa é a forma recomendada para a maioria dos projetos com apenas um sensor VL53L0X na ES32Lab.

#### Sintaxe:
```cpp
boolean begin(boolean io2v8 = true);
```

#### Parâmetro:
- **`io2v8`**: quando `true`, configura o modo interno de I/O do sensor através do ajuste relacionado ao registrador `VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV`. Em termos práticos, esse ajuste prepara os pinos I2C do VL53L0X para o modo usado pelos módulos comuns conectados a microcontroladores como o ESP32. No ecossistema ES32Lab, onde os sinais lógicos são `3V3`, o valor padrão `true` deve ser mantido na maioria dos casos.

#### Retorno:
- **`true`**: se o sensor foi encontrado, identificado e inicializado corretamente.
- **`false`**: se o sensor não respondeu, se o identificador interno não corresponde ao VL53L0X ou se a sequência de inicialização falhou.

#### Exemplo de Uso:
```cpp
if (!distance.begin()) {
    Serial.println("Sensor VL53L0X nao encontrado.");
    while (true) {
        delay(100);
    }
}
```

> **Dica:**  
> Para o uso normal com ES32Lab, chame apenas `distance.begin()`. Não é necessário informar `io2v8`, pois o valor padrão já atende ao cenário comum.

---

### `begin(uint8_t address, boolean io2v8 = true)`

Inicializa o sensor e define um endereço I2C final diferente do padrão.

Durante a inicialização, o VL53L0X é encontrado primeiro no endereço padrão `0x29`. Depois, se a inicialização for bem-sucedida, a classe altera o endereço para o valor informado.

#### Sintaxe:
```cpp
boolean begin(uint8_t address, boolean io2v8 = true);
```

#### Parâmetros:
- **`address`**: endereço I2C final de 7 bits. Deve estar no intervalo válido de endereços I2C.
- **`io2v8`**: mantém o mesmo comportamento descrito em `begin(boolean io2v8 = true)`.

#### Retorno:
- **`true`**: se o sensor foi inicializado e o endereço final foi aplicado.
- **`false`**: se o endereço for inválido ou se a inicialização falhar.

#### Exemplo de Uso:
```cpp
if (!distance.begin(0x30)) {
    Serial.println("Falha ao inicializar o VL53L0X no endereco 0x30.");
    while (true) {
        delay(100);
    }
}
```

> **Atenção:**  
> Essa alteração de endereço não é permanente no sensor. Ao reiniciar ou desenergizar o módulo, o VL53L0X volta ao endereço padrão `0x29`.

---

### `begin(TwoWire &bus, uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, boolean io2v8 = true)`

Seleciona um barramento I2C, inicializa o sensor e armazena o endereço final desejado.

Essa forma é útil quando o projeto utiliza um objeto `TwoWire` específico ou quando o código precisa deixar explícito qual barramento será usado.

#### Sintaxe:
```cpp
boolean begin(TwoWire &bus, uint8_t address = ES_VL53L0X_DEFAULT_ADDRESS, boolean io2v8 = true);
```

#### Parâmetros:
- **`bus`**: referência para o barramento I2C, como `Wire`.
- **`address`**: endereço I2C final desejado. O padrão é `ES_VL53L0X_DEFAULT_ADDRESS`.
- **`io2v8`**: configuração avançada do modo de I/O do sensor. No uso comum com ES32Lab, mantenha o valor padrão.

#### Retorno:
- **`true`**: se o sensor foi inicializado corretamente.
- **`false`**: se a inicialização falhar.

#### Exemplo de Uso:
```cpp
if (!distance.begin(Wire, 0x29)) {
    Serial.println("Falha ao inicializar o sensor.");
    while (true) {
        delay(100);
    }
}
```

> **Nota:**  
> A classe recebe o barramento por referência. Portanto, o usuário escreve `distance.begin(Wire, 0x29)` e não precisa usar `&Wire`.

---

## Estado e Comunicação I2C

### `isInitialized()`

Retorna se o sensor foi inicializado com sucesso pela última chamada de `begin()`.

Esse método é útil quando o programa precisa tomar decisões em tempo de execução com base no estado da classe.

#### Sintaxe:
```cpp
boolean isInitialized();
```

#### Retorno:
- **`true`**: se o objeto está inicializado e pronto para leitura.
- **`false`**: se `begin()` ainda não foi chamado ou se a inicialização falhou.

#### Exemplo de Uso:
```cpp
if (distance.isInitialized()) {
    Serial.println("Sensor pronto.");
}
```

---

### `isConnected()`

Verifica se há algum dispositivo I2C respondendo no endereço atualmente armazenado pela classe.

Esse método faz uma verificação simples de comunicação I2C. Ele não substitui `begin()`, pois não configura nem calibra o sensor. Ele apenas indica se existe resposta no endereço atual.

#### Sintaxe:
```cpp
boolean isConnected();
```

#### Retorno:
- **`true`**: se um dispositivo respondeu no endereço atual.
- **`false`**: se não houve resposta.

#### Exemplo de Uso:
```cpp
if (distance.isConnected()) {
    Serial.println("Dispositivo I2C encontrado.");
} else {
    Serial.println("Nenhum dispositivo respondeu.");
}
```

---

### `setBus(TwoWire &bus)`

Define qual barramento I2C será usado pelo objeto.

Na maior parte dos projetos com ES32Lab, não é necessário chamar esse método diretamente, pois o construtor e o `begin()` já usam `Wire` por padrão. Ele existe para cenários onde o projeto precisa trocar ou deixar explícito o barramento usado.

#### Sintaxe:
```cpp
void setBus(TwoWire &bus);
```

#### Parâmetro:
- **`bus`**: objeto `TwoWire` usado para comunicação I2C.

#### Exemplo de Uso:
```cpp
distance.setBus(Wire);
```

---

### `getBus()`

Retorna um ponteiro para o barramento I2C atualmente associado ao objeto.

Esse método é destinado a usos mais avançados, diagnósticos ou integrações específicas. Para leitura básica de distância, ele normalmente não é necessário.

#### Sintaxe:
```cpp
TwoWire *getBus();
```

#### Retorno:
- Ponteiro para o barramento `TwoWire` usado pela classe.

#### Exemplo de Uso:
```cpp
TwoWire *bus = distance.getBus();
```

---

### `setAddress(uint8_t address)`

Define o endereço I2C armazenado pela classe.

Se o sensor já estiver inicializado, o método também envia o novo endereço para o VL53L0X. Se o sensor ainda não estiver inicializado, o método apenas armazena o endereço desejado para uso posterior.

#### Sintaxe:
```cpp
boolean setAddress(uint8_t address);
```

#### Parâmetro:
- **`address`**: novo endereço I2C de 7 bits.

#### Retorno:
- **`true`**: se o endereço foi aceito.
- **`false`**: se o endereço for inválido ou se a escrita no sensor falhar.

#### Exemplo de Uso:
```cpp
if (distance.setAddress(0x30)) {
    Serial.println("Endereco alterado para 0x30.");
}
```

> **Nota:**  
> Para a maioria dos projetos, prefira informar o endereço diretamente no `begin(0x30)`, pois isso deixa a sequência de inicialização mais clara.

---

### `getAddress()`

Retorna o endereço I2C atualmente armazenado pela classe.

#### Sintaxe:
```cpp
uint8_t getAddress();
```

#### Retorno:
- Endereço I2C atual de 7 bits.

#### Exemplo de Uso:
```cpp
Serial.print("Endereco atual: 0x");
Serial.println(distance.getAddress(), HEX);
```

---

### `lastStatus()`

Retorna o status da última transmissão I2C de escrita realizada pela classe.

Esse método é útil para diagnóstico quando o sensor não responde ou quando há suspeita de problema de ligação, endereço incorreto, mau contato, barramento travado ou alimentação inadequada.

#### Sintaxe:
```cpp
uint8_t lastStatus();
```

#### Retorno:
- Valor retornado internamente por `Wire.endTransmission()`.
- Normalmente, `0` indica sucesso.
- Valores diferentes de `0` indicam algum tipo de falha de comunicação I2C.

#### Exemplo de Uso:
```cpp
Serial.print("Ultimo status I2C: ");
Serial.println(distance.lastStatus());
```

---

## Timeout de Leitura

### `setTimeout(uint16_t timeoutMs)`

Define o tempo máximo, em milissegundos, que a classe pode aguardar durante operações bloqueantes de leitura e inicialização.

Esse método é importante para evitar que o programa fique preso caso o sensor pare de responder, seja desconectado ou apresente falha de comunicação.

#### Sintaxe:
```cpp
void setTimeout(uint16_t timeoutMs);
```

#### Parâmetro:
- **`timeoutMs`**: tempo máximo em milissegundos.

#### Exemplo de Uso:
```cpp
distance.setTimeout(500);
```

> **Atenção:**  
> Usar `0` desativa o timeout. Isso pode ser útil em testes específicos, mas não é recomendado em aplicações finais, pois o programa pode ficar aguardando indefinidamente caso o sensor não responda.

---

### `getTimeout()`

Retorna o timeout atualmente configurado.

#### Sintaxe:
```cpp
uint16_t getTimeout();
```

#### Retorno:
- Timeout em milissegundos.

#### Exemplo de Uso:
```cpp
Serial.println(distance.getTimeout());
```

---

### `timeoutOccurred()`

Indica se ocorreu timeout desde a última chamada desse método.

Quando `timeoutOccurred()` é chamado, a flag interna de timeout é limpa. Isso significa que uma segunda chamada consecutiva retornará `false`, a menos que um novo timeout tenha ocorrido.

#### Sintaxe:
```cpp
boolean timeoutOccurred();
```

#### Retorno:
- **`true`**: se ocorreu timeout.
- **`false`**: se não ocorreu timeout desde a última verificação.

#### Exemplo de Uso:
```cpp
uint16_t mm = distance.read();

if (distance.timeoutOccurred()) {
    Serial.println("TIMEOUT");
} else {
    Serial.println(mm);
}
```

---

## Leitura de Distância

### `read()`

Realiza uma leitura única de distância e retorna o valor em milímetros.

Esse é o principal método de uso da classe. Ele solicita uma medição ao VL53L0X, aguarda o resultado, lê o valor bruto, aplica o offset configurado por `setDistanceOffset()` e armazena o resultado em `lastDistance()`.

#### Sintaxe:
```cpp
uint16_t read();
```

#### Retorno:
- Distância corrigida em milímetros.
- `ES_VL53L0X_INVALID_DISTANCE` (`65535`) se o sensor não estiver inicializado ou se a leitura falhar por timeout.

#### Exemplo de Uso:
```cpp
uint16_t mm = distance.read();

if (distance.timeoutOccurred()) {
    Serial.println("TIMEOUT");
} else {
    Serial.print(mm);
    Serial.println(" mm");
}
```

> **Importante:**  
> A leitura retornada por `read()` já considera o offset configurado. Se você chamou `distance.setDistanceOffset(50)`, o valor retornado já será a distância corrigida.

---

### `lastDistance()`

Retorna a última distância corrigida armazenada pela classe.

Esse método não solicita uma nova leitura ao sensor. Ele apenas retorna o último valor obtido por `read()`.

#### Sintaxe:
```cpp
uint16_t lastDistance();
```

#### Retorno:
- Última distância corrigida em milímetros.
- `ES_VL53L0X_INVALID_DISTANCE` se ainda não houve leitura válida ou se a última leitura foi inválida.

#### Exemplo de Uso:
```cpp
distance.read();

Serial.print("Ultima distancia: ");
Serial.println(distance.lastDistance());
```

---

## Offset de Distância

### `setDistanceOffset(uint16_t offsetMm)`

Define o valor fixo, em milímetros, que será subtraído de todas as leituras retornadas por `read()`.

Esse método é essencial para ajustar a distância inicial do sensor de acordo com a montagem física. Um sensor instalado atrás de uma frente acrílica, dentro de uma carcaça, recuado em um suporte ou posicionado em um habitáculo pode apresentar uma diferença significativa entre a leitura óptica e a referência mecânica real do projeto.

#### Sintaxe:
```cpp
void setDistanceOffset(uint16_t offsetMm);
```

#### Parâmetro:
- **`offsetMm`**: offset em milímetros.

#### Exemplo de Uso:
```cpp
distance.setDistanceOffset(50);
```

#### Comportamento:
- Se a leitura bruta for maior que o offset, o retorno será `leitura - offset`.
- Se a leitura bruta for menor ou igual ao offset, o retorno será `0`.
- Se a leitura for inválida, o retorno continuará sendo `ES_VL53L0X_INVALID_DISTANCE`.

#### Exemplo Prático:
```cpp
distance.setDistanceOffset(50);

uint16_t mm = distance.read();

Serial.print("Distancia corrigida: ");
Serial.print(mm);
Serial.println(" mm");
```

> **Recomendação ES32Lab:**  
> Para um sensor fora de qualquer carcaça ou habitáculo, use `setDistanceOffset(50)` como valor inicial de calibração. Ajuste esse valor conforme a montagem real do seu projeto.

---

### `getDistanceOffset()`

Retorna o offset de distância atualmente configurado.

#### Sintaxe:
```cpp
uint16_t getDistanceOffset();
```

#### Retorno:
- Offset atual em milímetros.

#### Exemplo de Uso:
```cpp
Serial.print("Offset atual: ");
Serial.print(distance.getDistanceOffset());
Serial.println(" mm");
```

---

## Tempo de Medição

### `setMeasurementTimingBudget(uint32_t budgetUs)`

Define o tempo aproximado, em microssegundos, reservado pelo sensor para cada medição.

Esse método permite ajustar o comportamento do VL53L0X conforme a necessidade do projeto. Leituras mais rápidas podem ser úteis em robôs móveis e aplicações com resposta rápida. Leituras mais lentas podem ser preferíveis quando a prioridade é estabilidade, repetibilidade ou leitura de alvos mais difíceis.

#### Sintaxe:
```cpp
boolean setMeasurementTimingBudget(uint32_t budgetUs);
```

#### Parâmetro:
- **`budgetUs`**: tempo de medição em microssegundos.

#### Retorno:
- **`true`**: se o valor foi aceito e aplicado.
- **`false`**: se o sensor não estiver inicializado ou se o valor for inválido.

#### Exemplo de Uso:
```cpp
if (!distance.setMeasurementTimingBudget(200000)) {
    Serial.println("Timing budget invalido.");
}
```

#### Valores de Referência:

| Valor | Comportamento esperado |
| :------: | ------ |
| `20000 us` | Valor mínimo aceito pela classe. Leitura mais rápida, menor estabilidade. |
| `50000 us` | Ponto intermediário para aplicações gerais. |
| `100000 us` | Leitura mais estável, porém mais lenta. |
| `200000 us` | Leitura ainda mais estável, indicada para testes e alvos mais difíceis. |

> **Importante:**  
> Esse método deve ser chamado depois de `begin()`. Se for chamado antes da inicialização do sensor, retornará `false`.

---

### `getMeasurementTimingBudget()`

Retorna o timing budget atual configurado no sensor.

#### Sintaxe:
```cpp
uint32_t getMeasurementTimingBudget();
```

#### Retorno:
- Tempo de medição em microssegundos.
- `0` se o sensor não estiver inicializado.

#### Exemplo de Uso:
```cpp
Serial.print("Timing budget atual: ");
Serial.print(distance.getMeasurementTimingBudget());
Serial.println(" us");
```

---

## Atributos Internos Relevantes

Os atributos internos da classe são privados e não devem ser acessados diretamente pelo usuário. Eles existem para manter o estado da comunicação e das leituras de forma organizada dentro do padrão da biblioteca ES32Lab.

### Estado mantido internamente:

- **Barramento I2C**: ponteiro para o objeto `TwoWire` usado pela classe.
- **Endereço I2C atual**: endereço final usado para comunicação com o sensor.
- **Status I2C**: último status retornado por uma transmissão I2C.
- **Timeout configurado**: tempo máximo permitido para operações bloqueantes.
- **Offset de distância**: valor subtraído das leituras retornadas por `read()`.
- **Última distância**: último valor corrigido armazenado pela classe.
- **Timing budget**: tempo de medição atualmente configurado.
- **Estado de inicialização**: indica se `begin()` foi executado com sucesso.
- **Flag de timeout**: indica se ocorreu timeout desde a última consulta com `timeoutOccurred()`.

Esses atributos são acessados de forma controlada pelos métodos públicos, como `getAddress()`, `lastStatus()`, `getTimeout()`, `getDistanceOffset()`, `lastDistance()` e `isInitialized()`.

---

## Exemplo Completo: Leitura Simples de Distância

Este exemplo inicializa o sensor VL53L0X, aplica um offset inicial de `50 mm` e imprime a distância corrigida no Monitor Serial.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_VL53L0X distance; // Objeto do sensor de distância.

void setup() {
    Serial.begin(115200);

    distance.setTimeout(500);       // Define timeout de leitura.
    distance.setDistanceOffset(50); // Calibração inicial recomendada para muitos sensores.

    if (!distance.begin()) {
        Serial.println("Sensor VL53L0X nao encontrado.");

        while (true) {
            delay(100);
        }
    }

    Serial.println("Sensor VL53L0X iniciado.");
}

void loop() {
    uint16_t mm = distance.read();

    if (distance.timeoutOccurred()) {
        Serial.println("TIMEOUT");
    } else {
        Serial.print(mm);
        Serial.println(" mm");
    }

    delay(100);
}
```

### Funcionamento:

1. Cria o objeto `ES_VL53L0X`.
2. Configura o timeout para `500 ms`.
3. Aplica offset inicial de `50 mm`.
4. Inicializa o sensor com `begin()`.
5. Lê a distância continuamente com `read()`.
6. Verifica se ocorreu timeout com `timeoutOccurred()`.
7. Imprime a distância corrigida no Monitor Serial.

---

## Exemplo Completo: Ajuste do Timing Budget

Este exemplo mostra como configurar o tempo de medição do VL53L0X usando `setMeasurementTimingBudget()`. O valor `200000` representa aproximadamente `200 ms` por medição.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_VL53L0X distance;

void setup() {
    Serial.begin(115200);

    delay(500);

    Serial.println();
    Serial.println("Teste ES_VL53L0X com timing budget.");

    distance.setTimeout(500);
    distance.setDistanceOffset(50);

    if (!distance.begin()) {
        Serial.println("Sensor VL53L0X nao encontrado.");

        while (true) {
            delay(100);
        }
    }

    if (!distance.setMeasurementTimingBudget(200000)) {
        Serial.println("Timing budget invalido.");

        while (true) {
            delay(100);
        }
    }

    Serial.print("Sensor iniciado no endereco I2C 0x");
    Serial.println(distance.getAddress(), HEX);

    Serial.print("Offset aplicado: ");
    Serial.print(distance.getDistanceOffset());
    Serial.println(" mm");

    Serial.print("Timing budget aplicado: ");
    Serial.print(distance.getMeasurementTimingBudget());
    Serial.println(" us");
}

void loop() {
    uint16_t mm = distance.read();

    if (distance.timeoutOccurred()) {
        Serial.println("TIMEOUT");
    } else {
        Serial.print("Distancia: ");
        Serial.print(mm);
        Serial.println(" mm");
    }

    delay(100);
}
```

### Funcionamento:

1. Inicializa o sensor.
2. Aplica offset de `50 mm`.
3. Configura o timing budget para `200000 us`.
4. Mostra no Monitor Serial o endereço I2C, o offset e o timing budget aplicado.
5. Realiza leituras contínuas com maior tempo de medição.

> **Dica de ajuste:**  
> Se o projeto precisa de resposta mais rápida, teste valores menores, como `50000`. Se precisa de leitura mais estável, teste valores maiores, como `100000` ou `200000`.

---

## Exemplo de Uso com Endereço I2C Personalizado

Este exemplo mostra como inicializar o sensor e alterar o endereço final para `0x30`.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_VL53L0X distance;

void setup() {
    Serial.begin(115200);

    distance.setTimeout(500);
    distance.setDistanceOffset(50);

    if (!distance.begin(0x30)) {
        Serial.println("Falha ao inicializar o VL53L0X.");

        while (true) {
            delay(100);
        }
    }

    Serial.print("Endereco final: 0x");
    Serial.println(distance.getAddress(), HEX);
}

void loop() {
    Serial.println(distance.read());
    delay(100);
}
```

> **Atenção:**  
> Para múltiplos sensores VL53L0X no mesmo barramento, é necessário controlar o `XSHUT` de cada sensor durante a inicialização. Caso todos estejam ligados ao mesmo tempo, todos responderão inicialmente no endereço `0x29`.

---

## Recomendações de Uso

- Use `#include <ES32Lab.h>` para carregar a classe no padrão oficial da biblioteca ES32Lab.
- Para a maioria dos projetos, crie o objeto com `ES_VL53L0X distance;`.
- Configure `setTimeout(500)` antes de iniciar leituras em aplicações didáticas e testes iniciais.
- Configure `setDistanceOffset(50)` como ponto de partida para sensores fora de carcaça ou habitáculo.
- Ajuste o offset conforme a montagem física real do sensor.
- Chame `begin()` no `setup()` e verifique o retorno antes de usar `read()`.
- Use `timeoutOccurred()` logo após `read()` para identificar falhas de leitura.
- Use `setMeasurementTimingBudget()` apenas depois de `begin()`.
- Para leituras mais rápidas, reduza o timing budget com cuidado.
- Para leituras mais estáveis, aumente o timing budget.
- Para múltiplos sensores iguais, planeje o controle individual do pino `XSHUT`.

---

## Exemplos Oficiais

A biblioteca ES32Lab possui exemplos práticos para uso da classe `ES_VL53L0X` com leitura simples de distância e ajuste do tempo de medição.

- [Exemplo SensorDistance](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/SensorDistance)
- [Exemplo SensorDistanceTimingBudget](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/SensorDistanceTimingBudget)

Esses exemplos servem como ponto de partida para testar o sensor, calibrar o offset inicial, avaliar estabilidade de leitura e integrar o VL53L0X com outros recursos da biblioteca ES32Lab.

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
