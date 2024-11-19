| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_Buzzer

A classe `ES_Buzzer` é um componente essencial da biblioteca ES32Lab, projetada para proporcionar controle intuitivo e eficiente de circuitos de buzzer utilizando a tecnologia PWM (Modulação por Largura de Pulso) integrada ao ESP32. Essa classe possibilita a reprodução de melodias, tons únicos e efeitos sonoros personalizados, sendo uma ferramenta ideal para projetos que exigem feedback auditivo, como alarmes, sistemas de notificação sonora, e aplicações interativas.

Por meio de métodos dedicados, a classe oferece alto grau de precisão no ajuste de tom, duração e efeitos sonoros. A possibilidade de manipular a velocidade da reprodução de melodias e aplicar efeitos de distorção expande ainda mais as capacidades criativas e funcionais dos projetos. Além disso, a classe é otimizada para facilitar o desenvolvimento, permitindo que mesmo usuários iniciantes integrem sons ao seu sistema sem complexidade.

Seja para criar efeitos sonoros dinâmicos ou reproduzir melodias detalhadas, a ES_Buzzer torna o controle de áudio no ESP32 uma tarefa acessível e altamente configurável. A classe está alinhada ao compromisso da ES32Lab de fornecer ferramentas modernas e simplificadas para prototipagem e desenvolvimento com ESP32.

---

## Construtor

### `ES_Buzzer(int8_t pinBuzzer)`

O construtor `ES_Buzzer` é utilizado para inicializar uma nova instância da classe, configurando o pino PWM responsável por controlar o circuito do buzzer. Ele é essencial para estabelecer a conexão entre o buzzer e a placa ESP32, garantindo que o hardware esteja corretamente configurado para reprodução sonora.

Na ES32Lab, existe uma constante pré-definida chamada **`P_BUZZER`**, que mapeia o pino correto do buzzer integrado ao hardware da placa. Essa constante elimina a necessidade de memorizar os pinos GPIO utilizados e simplifica a configuração, tornando o código mais legível e menos suscetível a erros.

#### Parâmetro
- **`pinBuzzer`**: Define o pino GPIO do ESP32 que será utilizado para controlar o circuito do buzzer. Para projetos com a ES32Lab, recomenda-se o uso da constante **`P_BUZZER`**.

**Atenção:** Para que o buzzer funcione corretamente, é necessário verificar se o jumper está conectando o circuito do buzzer à GPIO correspondente da ES32Lab.  

**[Clique aqui para assistir a um vídeo explicativo sobre como configurar o jumper do buzzer na ES32Lab](https://www.youtube.com/watch?v=xpoNbSA8pPM&t=383s).**  

Este vídeo demonstra como identificar e ajustar os jumpers necessários para garantir que o buzzer esteja operando corretamente na ES32Lab.

### Exemplo de Uso

#### `ES_Buzzer buzzer(P_BUZZER);`

---

## Configuração no `setup()`

O método `begin` é fundamental para inicializar a instância da classe `ES_Buzzer` e configurar o canal PWM que será usado pelo buzzer. Essa configuração deve ser realizada dentro da função `setup()` para garantir que o hardware esteja pronto para reproduzir sons durante a execução do programa.

O método permite especificar qual canal PWM será utilizado. Por padrão, o canal **15** é atribuído, tornando sua configuração mais simples e direta para a maioria dos casos.

### begin()

Inicializa o buzzer, atribuindo o canal PWM e preparando-o para reprodução sonora.

#### Sintaxe:
`void begin(int8_t channel = 15)`

#### Parâmetro:
- **`channel`**: Define o canal PWM que será utilizado pelo buzzer. O valor padrão é **15**, e ele deve ser mantido em situações normais.


### Exemplo de Uso

No uso padrão, a configuração do buzzer no método `setup()` é simples e direta:

#### `buzzer.begin();`


Em casos específicos e pontuais, o canal PWM pode ser alterado para atender a requisitos particulares do projeto. Por exemplo:

#### `buzzer.begin(10); // Configura o buzzer no canal PWM 10`

**Nota:** Alterar o canal PWM só deve ser feito quando necessário e com cuidado, garantindo que o canal escolhido esteja disponível e não seja compartilhado com outros dispositivos no sistema.

---

## Métodos da Classe

A classe `ES_Buzzer` oferece uma série de métodos que facilitam o controle do buzzer, permitindo desde a reprodução de notas musicais até a criação de efeitos sonoros personalizados. Esses métodos são projetados para serem intuitivos, proporcionando flexibilidade tanto para projetos simples quanto para aplicações mais complexas. 

Abaixo estão descritos os métodos disponíveis, com suas respectivas funcionalidades e exemplos práticos de uso.


### sound()

O método `sound()` é utilizado para reproduzir uma nota musical específica por uma duração definida, ideal para criar melodias ou efeitos sonoros simples e diretos.

#### Sintaxe:
`void sound(int note, int duration)`

#### Parâmetros:
- **`note`**: Frequência da nota musical em Hertz (Hz). 
  - Para facilitar a criação de músicas, as frequências das notas musicais já estão pré-definidas em constantes, como `NOTE_A4` para a nota Lá na oitava 4. Isso garante maior precisão e assertividade ao gerar músicas.
- **`duration`**: Duração da nota em milissegundos.

#### Exemplo:
Reproduz a nota **A4** por **500ms**.

`buzzer.sound(NOTE_A4, 500);`

**Ressalva:** Sempre utilize as constantes pré-definidas das notas musicais, como `NOTE_C4`, `NOTE_E4` ou `NOTE_G4`, para obter resultados mais precisos e consistentes. Estas constantes já estão otimizadas para representar as frequências reais das notas musicais.


### end()

O método `end()` é utilizado para finalizar a melodia e opcionalmente pausar a execução por um intervalo de tempo especificado. Ele é útil para criar intervalos entre melodias ou notas consecutivas, permitindo maior controle na sequência sonora.

#### Sintaxe:
`void end(int16_t pause = 0)`

#### Parâmetro:
- **`pause`** (opcional): Define o tempo, em milissegundos, para pausar a execução após o encerramento da melodia. O valor padrão é **0**, o que significa que não haverá pausa.

#### Exemplo:
Para finalizar a melodia instantaneamente:  
`buzzer.end(); // Finaliza a melodia sem pausa adicional`

Para criar uma pausa de 500ms antes de iniciar uma nova melodia:  
`buzzer.end(500); // Pausa a execução por 500ms`


### pitch()

O método `pitch()` ajusta a velocidade de reprodução da melodia, permitindo alterações dinâmicas na duração relativa das notas. Esse ajuste é realizado em relação à velocidade padrão (100%), sendo possível acelerar ou desacelerar a execução conforme necessário.

#### Sintaxe:
`void pitch(float percentage)`

#### Parâmetro:
- **`percentage`**: Valor percentual que define a velocidade relativa da melodia:
  - Valores **acima de 100%** tornam a melodia mais rápida. Por exemplo, `120` aumenta a velocidade em 20%.
  - Valores **abaixo de 100%** tornam a melodia mais lenta. Por exemplo, `80` reduz a velocidade em 20%.
  - O valor padrão de velocidade é **100%**, indicando a execução normal da melodia.

#### Exemplo:
Aumentar a velocidade da melodia em 20%:
`buzzer.pitch(120);`


### distortion()

O método `distortion()` é utilizado para criar um efeito de distorção sonora entre duas notas musicais. Ele gera uma sequência de tons, variando gradualmente entre as frequências das notas inicial (`noteFrom`) e final (`noteTo`). Esse efeito é ideal para simular transições sonoras ou criar variações dinâmicas em melodias.

#### Sintaxe:
`void distortion(int noteFrom, int noteTo)`

#### Parâmetros:
- **`noteFrom`**: Nota inicial da distorção, representada pela frequência em Hertz. 
- **`noteTo`**: Nota final da distorção, também representada pela frequência em Hertz.

#### Exemplo:
Criar uma distorção do C4 ao C5:
`buzzer.distortion(NOTE_C4, NOTE_C5);`

#### Observação:
A direção da distorção é definida pela ordem dos parâmetros:
- Se `noteFrom` for maior que `noteTo`, a distorção será descendente (do agudo para o grave).
- Se `noteFrom` for menor que `noteTo`, a distorção será ascendente (do grave para o agudo).

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
}

void loop() {
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);      
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 240);     
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 240);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_E6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_AS6, 80);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G6, 100);
  buzzer.sound(NOTE_E7, 100);
  buzzer.sound(NOTE_G7, 100);
  buzzer.sound(NOTE_A7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_F7, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_D7, 80);
  buzzer.sound(NOTE_B6, 80);

  buzzer.end(5000);
}
```

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
