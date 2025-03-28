| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_Buzzer

A classe `ES_Buzzer` é um componente essencial da biblioteca ES32Lab, projetada para proporcionar controle intuitivo e eficiente de circuitos de buzzer utilizando a tecnologia PWM (Modulação por Largura de Pulso) integrada ao ESP32. Essa classe possibilita a reprodução de melodias, tons únicos e efeitos sonoros personalizados, sendo uma ferramenta ideal para projetos que exigem feedback auditivo, como alarmes, sistemas de notificação sonora, e aplicações interativas.

Por meio de métodos dedicados, a classe oferece alto grau de precisão no ajuste de tom, duração e efeitos sonoros. A possibilidade de manipular a velocidade da reprodução de melodias e aplicar efeitos de distorção expande ainda mais as capacidades criativas e funcionais dos projetos. Além disso, a classe é otimizada para facilitar o desenvolvimento, permitindo que mesmo usuários iniciantes integrem sons ao seu sistema sem complexidade.

Seja para criar efeitos sonoros dinâmicos ou reproduzir melodias detalhadas, a ES_Buzzer torna o controle de áudio no ESP32 uma tarefa acessível e altamente configurável. A classe está alinhada ao compromisso da ES32Lab de fornecer ferramentas modernas e simplificadas para prototipagem e desenvolvimento com ESP32.

---


## Índice

1. [Construtor](#construtor)
2. [Configuração no `setup()`](#configuração-no-setup)
3. [Métodos da Classe](#métodos-da-classe)
   - [`sound()`](#sound)
   - [`end()`](#end)
   - [`setVolume()`](#setvolume)
   - [`getVolume()`](#getvolume)
   - [`setSpeed()`](#setspeed)
   - [`getSpeed()`](#getspeed)
   - [`setPitch()`](#setpitch)
   - [`getPitch()`](#getpitch)
   - [`setPitchAndSpeed()`](#setpitchandspeed)
4. [Exemplo: Reproduzindo a Trilha Sonora de Super Mario World](#exemplo-reproduzindo-a-trilha-sonora-de-super-mario-world)

---


## Construtor

### `ES_Buzzer(int8_t pinBuzzer)`

O construtor `ES_Buzzer` é utilizado para inicializar uma nova instância da classe, configurando o pino PWM responsável por controlar o circuito do buzzer. Ele é essencial para estabelecer a conexão entre o buzzer e a placa ESP32, garantindo que o hardware esteja corretamente configurado para reprodução sonora.

Na ES32Lab, existe uma constante pré-definida chamada **`P_BUZZER`**, que mapeia o pino correto do buzzer integrado ao hardware da placa. Essa constante, cujo valor é **GPIO25**, elimina a necessidade de memorizar os pinos GPIO utilizados e simplifica a configuração, tornando o código mais legível e menos suscetível a erros.

#### Parâmetro
- **`pinBuzzer`**: Define o pino GPIO do ESP32 que será utilizado para controlar o circuito do buzzer. Para projetos com a ES32Lab, recomenda-se o uso da constante **`P_BUZZER`**.

### `ES_Buzzer()`

Além da forma tradicional de inicializar o construtor com o pino GPIO do buzzer, a classe `ES_Buzzer` também oferece a possibilidade de criar uma instância sem passar nenhum parâmetro. Nesse caso, o pino padrão utilizado será o **GPIO25**, que corresponde ao pino do buzzer integrado na ES32Lab.

Essa abordagem é útil para simplificar ainda mais o código, especialmente em projetos que utilizam a configuração padrão da ES32Lab, onde o pino do buzzer já está pré-definido.

**Atenção:** Para que o buzzer funcione corretamente, é necessário verificar se o jumper está conectando o circuito do buzzer à GPIO correspondente da ES32Lab.

**[Clique aqui para assistir a um vídeo explicativo sobre como configurar o jumper do buzzer na ES32Lab](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s).**  

Este vídeo demonstra como identificar e ajustar os jumpers necessários para garantir que o buzzer esteja operando corretamente na ES32Lab.

### Exemplos de Uso

1. Inicializando o buzzer com o pino especificado:
  ```cpp
  ES_Buzzer buzzer(P_BUZZER);
  ```

2. Inicializando o buzzer sem especificar o pino (utilizando o padrão GPIO25):
  ```cpp
  ES_Buzzer buzzer;
  ```

---
## Configuração no `setup()`

O método `begin()` é essencial para inicializar a instância da classe `ES_Buzzer` e configurar o canal PWM que será utilizado pelo buzzer. Essa configuração deve ocorrer dentro da função `setup()` para garantir que o hardware esteja preparado para reproduzir sons ao longo do programa.

O canal padrão utilizado é o **canal 7**, que corresponde ao último canal disponível do ESP32 para PWM, reduzindo as chances de conflito com outras aplicações.

### begin()

Inicializa o buzzer, atribuindo o canal PWM e preparando-o para reprodução sonora.

#### Sintaxe:
```cpp
void begin(int8_t channel = 7)
```

#### Parâmetro:
- channel: Define o canal PWM que será utilizado pelo buzzer. O valor padrão é 7, e ele deve ser mantido em situações normais.

### Exemplo de Uso
Configuração padrão recomendada no `setup()`:
```cpp
buzzer.begin();
```

Em casos pontuais, é possível alterar o canal PWM, se necessário:
```cpp
buzzer.begin(6); // Configura o buzzer no canal PWM 6
```
**Nota:** Alterar o canal só deve ser feito quando realmente necessário, sempre garantindo que o canal escolhido esteja disponível e não seja utilizado por outro periférico.

---

## Métodos da Classe

A classe `ES_Buzzer` oferece uma série de métodos que facilitam o controle do buzzer, permitindo desde a reprodução de notas musicais até a criação de efeitos sonoros personalizados. Esses métodos são projetados para serem intuitivos, proporcionando flexibilidade tanto para projetos simples quanto para aplicações mais complexas. 

Abaixo estão descritos os métodos disponíveis, com suas respectivas funcionalidades e exemplos práticos de uso.

### sound()

O método `sound()` é utilizado para reproduzir uma nota musical específica por uma duração definida, ideal para criar melodias ou efeitos sonoros simples e diretos.

#### Sintaxe:
```cpp
void sound(int note, int duration);
```

#### Parâmetros:
- **`note`**: Frequência da nota musical em Hertz (Hz). 
  - Para facilitar a criação de músicas, as frequências das notas musicais já estão pré-definidas em constantes, como `NOTE_A4` para a nota Lá na oitava 4. Isso garante maior precisão e assertividade ao gerar músicas.
- **`duration`**: Duração da nota em milissegundos.

#### Exemplo:
Reproduz a nota **A4** por **500ms**.

```cpp
buzzer.sound(NOTE_A4, 500);
```

**Ressalva:** Sempre utilize as constantes pré-definidas das notas musicais, como `NOTE_C4`, `NOTE_E4` ou `NOTE_G4`, para obter resultados mais precisos e consistentes. Estas constantes já estão otimizadas para representar as frequências reais das notas musicais.


### end()

O método `end()` é utilizado para finalizar a melodia e, opcionalmente, pausar a execução por um intervalo de tempo especificado. Ele é útil para criar intervalos entre melodias ou notas consecutivas, permitindo maior controle na sequência sonora.

#### Sintaxe:
```cpp
void end(int16_t pause = 0);
```

#### Parâmetro:
- **`pause`** (opcional): Define o tempo, em milissegundos, para pausar a execução após o encerramento da melodia. O valor padrão é **0**, o que significa que não haverá pausa.

#### Exemplo de Uso

Finalizar a melodia sem pausa adicional:
```cpp
buzzer.end();
```

Finalizar a melodia e criar uma pausa de 500ms antes de iniciar uma nova:
```cpp
buzzer.end(500);
```

**Nota:** Este método é ideal para controlar o fluxo de execução entre diferentes melodias ou efeitos sonoros, garantindo uma transição suave entre eles.


### setVolume()
O método `setVolume()` ajusta o volume do som reproduzido pelo buzzer, controlando a intensidade do sinal PWM enviado ao circuito. Ele é útil para criar efeitos sonoros com diferentes níveis de volume, permitindo maior personalização na reprodução de sons. O valor padrão do volume é de **50%**, sendo possível ajustá-lo para mais ou para menos conforme a necessidade, garantindo flexibilidade para atender a diferentes requisitos de áudio nos projetos.

#### Sintaxe:
```cpp
void setVolume(int percentage);
```

#### Parâmetro:
- **`percentage`**: Percentual de volume desejado. O valor deve estar entre **0** (mudo) e **100** (volume máximo). Valores fora desse intervalo serão automaticamente ajustados para os limites permitidos.

#### Exemplo de Uso

Definir o volume para 50%:
```cpp
buzzer.setVolume(50);
```

Definir o volume para o máximo:
```cpp
buzzer.setVolume(100);
```

**Nota:** O ajuste de volume é realizado por meio da modulação do ciclo de trabalho do PWM, o que pode influenciar a percepção sonora dependendo do tipo de buzzer utilizado.


### getVolume()

O método `getVolume()` retorna o volume atual do buzzer em formato percentual, com base no ciclo de trabalho (duty cycle) do PWM. Ele é útil para verificar o nível de volume configurado no momento, permitindo ajustes dinâmicos ou monitoramento do estado do buzzer.

#### Sintaxe:
```cpp
int getVolume();
```

#### Retorno:
- **`int`**: O volume atual em percentual, variando de **0** (mudo) a **100** (volume máximo).

#### Exemplo de Uso

Obter o volume atual e exibi-lo no monitor serial:
```cpp
Serial.print("Volume atual: ");
Serial.println(buzzer.getVolume());
```

**Nota:** O valor retornado representa diretamente o ciclo de trabalho (duty cycle) configurado no PWM. A percepção do volume pode variar dependendo das características do buzzer utilizado.


### setSpeed()

Define a velocidade de execução das notas em formato percentual, permitindo acelerar ou desacelerar a reprodução da melodia. Essa função afeta diretamente o tempo de duração de cada nota musical, sem alterar sua frequência (tom).

#### Sintaxe:
```cpp
void setSpeed(int percentage);
```

#### Parâmetro:
- **`percentage`**: Percentual da velocidade de execução. O valor **100** representa a velocidade normal. Valores acima de 100 tornam a música mais rápida, enquanto valores abaixo de 100 tornam mais lenta. O valor é automaticamente limitado entre **1** e **255**.

### Exemplo de Uso

Aumentar a velocidade da melodia em 50%:
```cpp
buzzer.setSpeed(150);
```

Reduzir a velocidade da melodia para metade:
```cpp
buzzer.setSpeed(50);
```


### getSpeed()

O método `getSpeed()` retorna a velocidade atual de reprodução das notas, definida anteriormente com o método `setSpeed()`. Esse valor é utilizado para calcular o tempo de duração de cada nota musical executada, permitindo ajustes dinâmicos na velocidade de reprodução.

#### Sintaxe:
```cpp
int getSpeed();
```

#### Retorno:
- **`int`**: O valor percentual atual da velocidade de reprodução. O valor padrão é **100**, indicando velocidade normal.

#### Exemplo de Uso

Obter a velocidade atual e exibi-la no monitor serial:
```cpp
Serial.print("Velocidade atual: ");
Serial.println(buzzer.getSpeed());
```

**Nota:** Valores acima de 100 indicam uma reprodução mais rápida, enquanto valores abaixo de 100 tornam a reprodução mais lenta.


### setPitch()

O método `setPitch()` define o ajuste de pitch (tom) da música em formato percentual, alterando apenas a frequência das notas musicais, sem afetar a velocidade (duração) de reprodução.

#### Sintaxe:
```cpp
void setPitch(int percentage);
```

#### Parâmetro:
- **`percentage`**: Percentual de ajuste de tom. O valor padrão é **100** (pitch original). Valores abaixo de 100 tornam o som mais grave, e valores acima de 100 tornam o som mais agudo. O valor é automaticamente limitado entre **50** e **200** para manter a estabilidade do PWM.

#### Exemplo de Uso

Aumentar o pitch (tom) em 20%:
```cpp
buzzer.setPitch(120);
```

Reduzir o pitch (tom) em 30%:
```cpp
buzzer.setPitch(70);
```

**Nota:** Alterar o pitch pode ser útil para criar variações sonoras ou efeitos personalizados em melodias.


### getPitch()

O método `getPitch()` retorna o valor atual do ajuste de pitch (tom) em formato percentual. Esse valor é definido previamente com o método `setPitch()` e influencia a frequência das notas reproduzidas, tornando-as mais agudas ou graves.

#### Sintaxe:
```cpp
int getPitch();
```

#### Retorno:
- **`int`**: O valor percentual atual do pitch. O valor padrão é **100**, indicando que as frequências das notas estão em seu tom original.

#### Exemplo de Uso

Obter o pitch atual e exibi-lo no monitor serial:
```cpp
Serial.print("Pitch atual: ");
Serial.println(buzzer.getPitch());
```

**Nota:** Valores acima de 100 tornam o som mais agudo, enquanto valores abaixo de 100 tornam o som mais grave. Esse ajuste é útil para criar variações sonoras ou efeitos personalizados em melodias.


### setPitchAndSpeed()

O método `setPitchAndSpeed()` ajusta simultaneamente o pitch (tom) e a velocidade de reprodução das notas em formato percentual. Essa funcionalidade é útil para criar efeitos sonoros dinâmicos, permitindo que o tom e a velocidade sejam alterados de forma sincronizada.

#### Sintaxe:
```cpp
void setPitchAndSpeed(int percentage);
```

#### Parâmetro:
- **`percentage`**: Percentual aplicado tanto ao pitch quanto à velocidade. O valor padrão é **100**, indicando pitch e velocidade originais. Valores acima de 100 aumentam o tom e aceleram a reprodução, enquanto valores abaixo de 100 tornam o tom mais grave e a reprodução mais lenta.

#### Exemplo de Uso

Aumentar o pitch e a velocidade em 20%:
```cpp
buzzer.setPitchAndSpeed(120);
```

Reduzir o pitch e a velocidade em 30%:
```cpp
buzzer.setPitchAndSpeed(70);
```

**Nota:** Este método é ideal para criar efeitos sonoros sincronizados, onde o tom e a velocidade precisam ser ajustados proporcionalmente.

---
## Exemplo: Reproduzindo a Trilha Sonora de Super Mario World

Este exemplo utiliza a classe `ES_Buzzer` para reproduzir a trilha sonora do clássico jogo **Super Mario World** no buzzer da ES32Lab. Ele demonstra como utilizar o método `sound` para reproduzir notas musicais e criar uma sequência melódica.

Para mais exemplos de utilização da classe `ES_Buzzer`, acesse o link:  
**(https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/Buzzer)**

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_Buzzer buzzer(P_BUZZER);

void setup() {
  buzzer.begin();
  buzzer.setVolume(50);
}

void loop() {
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_C7, 136);
  buzzer.sound(NOTE_E7, 136);
  buzzer.sound(0, 136);
  buzzer.sound(NOTE_G7, 136);
  buzzer.sound(0, 408);
  buzzer.sound(NOTE_G6, 136);

  buzzer.end(5000);
}
```

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
