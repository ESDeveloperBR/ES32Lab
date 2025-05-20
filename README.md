# Índice
* [Introdução](https://github.com/ESDeveloperBR/ES32Lab#introdu%C3%A7%C3%A3o)
  * [O que é o projeto ES32Lab?](https://github.com/ESDeveloperBR/ES32Lab#o-que-%C3%A9-o-projeto-es32lab)
  * [ESP32 sem protoboard!? Conheça cada detalhe do hardware da ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#esp32-sem-protoboard-conhe%C3%A7a-cada-detalhe-do-hardware-da-es32lab)
* [ES32Lab biblioteca](https://github.com/ESDeveloperBR/ES32Lab#es32lab-biblioteca)
	* [Endereço das GPIOs do ESP32 com conexões aos circuitos da ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#endere%C3%A7o-das-gpios-do-esp32-com-conex%C3%B5es-aos-circuitos-da-es32lab)
	* [Exemplo de utilização de GPIO](https://github.com/ESDeveloperBR/ES32Lab#exemplo-de-utiliza%C3%A7%C3%A3o-de-gpio)
	* [Conjunto de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab)


---
# Introdução
## O que é o projeto ES32Lab?
![](doc/imgs/ganheTempo.jpg)
[YouTube - Vídeo de introdução](https://www.youtube.com/watch?v=F3Kxc9TrW4A)

A ES32Lab é um conjunto de circuitos eletrônicos montados com o objetivo de facilitar a utilização e o estudo do microcontrolador ESP32 da ESPRESSIF. Ele é uma alternativa mais potente e contemporânea em relação ao consagrado Arduino, oferecendo maior capacidade de processamento e recursos avançados. Com a ES32Lab, é possível explorar de forma mais eficiente as funcionalidades do ESP32 e desenvolver projetos eletrônicos complexos com facilidade.

Aplicações e circuitos onboard da ES32Lab:
- Compatibilidade com as seguintes Shields de ESP32: DEVKit32S, DEVKit32C V4 e NodeMCU32;
- Fonte de alimentação de 5V e 3.3V para suprir diferentes necessidades;
Carregador 2S para baterias de íon-lítio, permitindo o uso de energia portátil;
- Ponte H para controle de dois motores DC, possibilitando a criação de projetos de robótica;
- Sensor de tensão DC para monitoramento de voltagem;
- Teclado com 5 teclas para interação com o sistema;
- 2 potenciômetros para ajuste de valores analógicos;
- 6 LEDs para indicadores visuais;
- Sensor de temperatura analógico para medição de temperatura ambiente;
- Sensor LDR para detecção de luz;
- Leitor de cartão micro SD para armazenamento externo;
- Conector preparado para câmera de vídeo OV2640, permitindo captura de imagens e vídeos;
- GPIOs do ESP32 organizadas em ordem crescente para facilitar a conexão de periféricos;
- Expansão de 8 GPIOs extras por i2C, aumentando o número de dispositivos conectados;
- Conexão ponta para RTC físico i2C, possibilitando o uso de um Real-Time Clock externo;
- Buzzer para emitir sons e alertas sonoros;
- Conector P2 para reprodução de áudio utilizando a porta DAC nativa do ESP32;
- Conector para expansões i2S, permitindo a conexão de dispositivos de áudio;
- Conector para os dois modelos mais comuns de display SPI TFT colorido, possibilitando a criação de interfaces gráficas;
- Tamanho compacto de 10x10cm, facilitando a integração em projetos;
- Pode ser acomodado dentro de uma caixa de passagem elétrica, garantindo praticidade na instalação.

Uma característica importante da ES32Lab é a sua capacidade de agilizar o desenvolvimento de projetos utilizando o microcontrolador ESP32 da ESPRESSIF. Com o conjunto de circuitos eletrônicos integrados, ela atende a uma ampla variedade de necessidades em projetos eletrônicos. Além disso, a ES32Lab possui um tamanho compacto que permite acomodá-la facilmente em uma caixa de passagem elétrica comum, adquirida em lojas de materiais de construção.

Essa característica traz benefícios significativos, pois dispensa a necessidade de cases especializados ou estruturas personalizadas para proteção e instalação da ES32Lab. Isso simplifica o processo de montagem e facilita a integração do dispositivo em diferentes ambientes e aplicações.

Dessa forma, a ES32Lab oferece uma solução prática e versátil para o desenvolvimento de projetos com o ESP32, permitindo que os usuários se concentrem na implementação e funcionalidade dos seus projetos, sem a preocupação adicional com a proteção física e instalação especializada do dispositivo.


## ESP32 sem protoboard!? Conheça cada detalhe do hardware da ES32Lab
![](doc/imgs/ESP32semProtoboard.jpg)
[YouTube - ESP32 sem protoboard!? Conheça cada detalhe do hardware da ES32Lab](https://www.youtube.com/watch?v=xpoNbSA8pPM)

Conheça cada detalhe de configuração do hardware da ES32Lab de forma simples e intuitiva. Crie projetos com ESP32 do zero em tempo recorde com essa poderosa ferramenta de desenvolvimento e prototipagem, assista o vídeo e veja com é simples ajustar o hardware da ES32Lab para atender seu projeto.

Tópicos importantes do vídeo explicativo no YouTube:
- [Compatível com diversas shields de ESP32;](https://youtu.be/xpoNbSA8pPM?t=40)
- [Alimentaçãode tensão da ES32Lab;](https://youtu.be/xpoNbSA8pPM?t=107)
- [Circuitos e conectores da ES32Lab;](https://youtu.be/xpoNbSA8pPM?t=182)
- [Parte inferior da ES32Lab;](https://youtu.be/xpoNbSA8pPM?t=234)
- [Legendas de fácil compreensão;](https://youtu.be/xpoNbSA8pPM?t=251)
- [Configuração e ajustes intuitivos;](https://youtu.be/xpoNbSA8pPM?t=292)
- [Tamanho compacto;](https://youtu.be/xpoNbSA8pPM?t=450)

---
# ES32Lab biblioteca

Para o correto funcionamento da biblioteca ES32Lab, é necessário fazer a instalação obrigatória da dependência [TFT_eSPI_ES32Lab](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab). Essa dependência é uma variação da biblioteca TFT_eSPI, desenvolvida por [Bobmer](https://github.com/Bodmer) e licenciada sob a licença MIT.

**IMPORTANTE:** Portanto, é essencial baixar e instalar a biblioteca TFT_eSPI_ES32Lab a fim de garantir o funcionamento adequado da biblioteca ES32Lab. Você pode encontrar o link para o download da biblioteca [TFT_eSPI_ES32Lab](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab). Certifique-se de seguir as instruções de instalação para integrar corretamente a biblioteca à sua plataforma de desenvolvimento.

## Endereço das GPIOs do ESP32 com conexões aos circuitos da ES32Lab

Para facilitar a programação da ES32Lab, foram criadas diversas constantes com os endereços de todas as GPIOs do ESP32 que estão conectadas aos diversos circuitos da ES32Lab. Isso dispensa a necessidade de que o programador precise memorizar as GPIOs que estão ligadas aos circuitos da ES32Lab. Abaixo estão algumas das constantes disponíveis:

- P_KEYBOARD = GPIO33
- P_LED_GREEN = GPIO17
- P_LED_YELLOW = GPIO16
- P_LED_RED = GPIO13
- P_LED_BLUE = GPIO12
- P_POT1 = GPIO36
- P_POT2 = GPIO39
- P_VOLTAGE_SENSOR = GPIO34
- P_BUZZER = GPIO25
- P_DAC1 = GPIO25  // Se a DAC for utilizada como áudio, será o canal L
- P_DAC2 = GPIO26  // Se a DAC for utilizada como áudio, será o canal R
- P_I2S_DOUT = GPIO25
- P_I2S_LRC = GPIO26
- P_I2S_BCLK = GPIO27
- P_SDA = GPIO21
- P_SCL = GPIO22
- P_TX0 = GPIO1
- P_RX0 = GPIO3
- P_TX2 = GPIO17
- P_RX2 = GPIO16
- P_MOSI = GPIO23
- P_MISO = GPIO19
- P_SCK = GPIO18
- P_SD_CS = GPIO5

## Exemplo de utilização de GPIO

Para exemplificar a utilização das constantes citadas acima, vamos criar um código que faz o LED verde da ES32Lab piscar de forma intermitente. O LED verde está conectado à GPIO17, que pode ser acionada utilizando a constante `P_LED_GREEN`.

```C++
#include <ES32Lab.h>
void setup() {
  pinMode(P_LED_GREEN , OUTPUT);
}
void loop() {
  digitalWrite(P_LED_GREEN, HIGH);
  delay(500);

  digitalWrite(P_LED_GREEN, LOW);
  delay(500);
}
```

Nesse exemplo, a GPIO utilizada para controlar o LED verde foi a 17, que pode ser substituída pela constante `P_LED_GREEN`. Isso evita que o programador precise memorizar todos os endereços GPIO utilizados pela ES32Lab.

Todas as constantes de endereços seguem a mesma linha de raciocínio em sua nomenclatura, tornando mais intuitiva sua utilização. No exemplo abaixo, explicarei o raciocínio utilizado para a criação de todas as constantes de GPIOs na ES32Lab.

**P_LED_GREEN:**
- **"P":** Pino;
- **"LED":** Circuito na ES32Lab;
- **"GREEN":** Cor do LED.

Seguindo essa linha de raciocínio, a constante de controle do LED vermelho será `P_LED_RED`, a do buzzer será `P_BUZZER`, potenciômetro 1 será `P_POT1` e assim por diante.




## Conjunto de classes contidas na LIB ES32Lab

A biblioteca da ES32Lab conta com diversas classes para programação orientada a objeto, que têm como objetivo facilitar a criação de programas em C++ para controle da placa de desenvolvimento e prototipagem ES32Lab. Abaixo estão as classes disponíveis:

- [AnalogKeyboard](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/AnalogKeyboard#readme)
  
- [DigitalButton](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/DigitalButton#readme)
  
- [ES_Buzzer](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Buzzer#readme)

- [ES_Camera](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_Camera)

- [ES_PCF8574](https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_PCF8574#readme)

- [ES_File](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_File#readme)


- [ES_TFT](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/ES_TFT#readme)


- [TimeInterval](https://github.com/ESDeveloperBR/ES32Lab/tree/main/src/TimeInterval#readme)

Essas classes podem ser utilizadas para facilitar o desenvolvimento de programas na ES32Lab, oferecendo recursos específicos e abstrações que simplificam o processo de criação de projetos. Cada classe possui sua própria documentação detalhada, que pode ser acessada através dos links fornecidos acima.

---
