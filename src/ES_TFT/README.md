| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |

---

# Documentação da Classe ES_TFT

A classe `ES_TFT` é um componente da biblioteca ES32Lab desenvolvido para facilitar o uso do display TFT da placa ES32Lab. Ela funciona como uma camada de conveniência sobre a biblioteca [`TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab), que é uma versão derivada da biblioteca original [`Bodmer/TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI), com ajustes de configuração para o hardware da ES32Lab.

Com a `ES_TFT`, o usuário pode imprimir textos, desenhar elementos gráficos, renderizar imagens JPEG armazenadas em sistemas de arquivos, exibir frames capturados pela classe [`ES_Camera`](../ES_Camera/README.md) e carregar fontes salvas em arquivos. A classe foi pensada para simplificar tarefas comuns no display sem impedir o acesso aos recursos avançados herdados da `TFT_eSPI_ES32Lab`.

A configuração de hardware do display já vem preparada na biblioteca [`TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab), evitando que o usuário precise configurar manualmente as GPIOs do display para a placa ES32Lab.

### **Principais Recursos**
- **Compatibilidade com TFT_eSPI_ES32Lab**: a classe herda da base gráfica fornecida pela biblioteca `TFT_eSPI_ES32Lab`, permitindo usar os métodos tradicionais de desenho e controle do display.
- **Configuração Pronta para ES32Lab**: a biblioteca `TFT_eSPI_ES32Lab` já traz os ajustes de GPIO e display necessários para a placa ES32Lab.
- **Atalhos para Texto**: métodos para desenhar texto centralizado ou alinhado à direita na largura total da tela.
- **Renderização de JPEG**: exibe imagens JPEG a partir de `SD`, `SPIFFS` ou `LittleFS`, usando a classe [`ES_File`](../ES_File/README.md) e a biblioteca `JPEGDecoder`.
- **Ajuste Automático de Imagem**: pode reduzir imagens grandes para caberem na área disponível do display.
- **Integração com Câmera**: renderiza frames capturados pela classe [`ES_Camera`](../ES_Camera/README.md).
- **Navegação entre Imagens**: renderiza o primeiro, último, próximo ou anterior arquivo JPEG de um diretório.
- **Carregamento de Fontes**: permite carregar fontes `.vlw` armazenadas em sistema de arquivos.

> **Atenção sobre desempenho:**  
> O redimensionamento automático de imagens JPEG exige processamento adicional no ESP32. Quando `fitToScreen` está ativo e a imagem original é maior que a área disponível, a renderização pode ficar mais lenta e a qualidade visual pode ser reduzida. Para melhor desempenho e melhor nitidez, prefira usar imagens previamente redimensionadas para a resolução do display.

---

## Índice

1. [Dependência Obrigatória](#dependência-obrigatória)
2. [Classes e Bibliotecas Utilizadas](#classes-e-bibliotecas-utilizadas)
3. [Configuração do Display](#configuração-do-display)
4. [Construtor](#construtor)
5. [Inicialização no setup()](#inicialização-no-setup)
6. [Métodos Herdados da TFT_eSPI_ES32Lab](#métodos-herdados-da-tft_espi_es32lab)
    - [Convenções básicas](#convenções-básicas)
    - [Inicialização e configuração](#inicialização-e-configuração)
    - [Dimensões, origem e área útil](#dimensões-origem-e-área-útil)
    - [Controle de tela e texto](#controle-de-tela-e-texto)
    - [Desenho de textos](#desenho-de-textos)
    - [Alinhamento, medidas e padding de texto](#alinhamento-medidas-e-padding-de-texto)
    - [Primitivas gráficas](#primitivas-gráficas)
    - [Gradientes e gráficos suavizados](#gradientes-e-gráficos-suavizados)
    - [Viewport](#viewport)
    - [Imagens e buffers](#imagens-e-buffers)
    - [Leitura de pixels e cópia de áreas](#leitura-de-pixels-e-cópia-de-áreas)
    - [Conversão e mistura de cores](#conversão-e-mistura-de-cores)
    - [Fontes suaves](#fontes-suaves)
    - [Sprites](#sprites)
    - [Transações, DMA e métodos avançados](#transações-dma-e-métodos-avançados)
    - [Diagnóstico e atributos](#diagnóstico-e-atributos)
7. [Métodos de Texto](#métodos-de-texto)
    - [`drawCentreScreenString()`](#drawcentrescreenstring)
    - [`drawRightScreenString()`](#drawrightscreenstring)
8. [Renderização de JPEG](#renderização-de-jpeg)
    - [`renderJPEG()`](#renderjpeg)
    - [`renderJpegBuffer()`](#renderjpegbuffer)
9. [Renderização de Frame da Câmera](#renderização-de-frame-da-câmera)
    - [`renderCameraFrame()`](#rendercameraframe)
10. [Navegação entre Arquivos JPEG](#navegação-entre-arquivos-jpeg)
    - [`renderFirstFileJPEG()`](#renderfirstfilejpeg)
    - [`renderLastFileJPEG()`](#renderlastfilejpeg)
    - [`renderNextFileJPEG()`](#rendernextfilejpeg)
    - [`renderPreviousFileJPEG()`](#renderpreviousfilejpeg)
11. [Carregamento de Fontes](#carregamento-de-fontes)
    - [`loadFontFile()`](#loadfontfile)
12. [Versão da Classe](#versão-da-classe)
13. [Recomendações de Desempenho](#recomendações-de-desempenho)
14. [Exemplo Completo: Texto no Display](#exemplo-completo-texto-no-display)
15. [Exemplo Completo: Renderizar JPEG do Cartão SD](#exemplo-completo-renderizar-jpeg-do-cartão-sd)
16. [Exemplo Completo: Visualizador de Fotos com Teclado](#exemplo-completo-visualizador-de-fotos-com-teclado)
17. [Exemplo Completo: Frame da Câmera no Display](#exemplo-completo-frame-da-câmera-no-display)
18. [Exemplos Oficiais](#exemplos-oficiais)

---

## Dependência Obrigatória

A classe `ES_TFT` depende obrigatoriamente da biblioteca [`ESDeveloperBR/TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab).

Essa biblioteca é uma versão derivada da biblioteca original [`Bodmer/TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI), porém já preparada para o hardware da placa ES32Lab. O objetivo dessa adaptação é evitar que o usuário precise configurar manualmente as GPIOs, o driver e os parâmetros básicos do display TFT usado na ES32Lab.

### Formas de instalação

- **Arduino IDE**: instale a biblioteca `TFT_eSPI_ES32Lab` pelo Gerenciador de Bibliotecas da Arduino IDE.
- **Instalação manual**: baixe ou clone a biblioteca pelo repositório [`ESDeveloperBR/TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab) e instale na pasta de bibliotecas do Arduino ou no ambiente PlatformIO.

> **Importante:**  
> Para projetos com a placa ES32Lab, use a biblioteca `TFT_eSPI_ES32Lab`. A biblioteca original `Bodmer/TFT_eSPI` é a base do projeto, mas não deve substituir a versão ajustada para a ES32Lab neste contexto. Usar a biblioteca errada pode causar conflito de configuração ou funcionamento incorreto dos pinos do display.

---

## Classes e Bibliotecas Utilizadas

A `ES_TFT` trabalha em conjunto com outras classes e bibliotecas:

- [`TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab): biblioteca obrigatória usada pela classe `ES_TFT`. Ela fornece a base gráfica compatível com a placa ES32Lab.
- [`Bodmer/TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI): biblioteca original da qual a `TFT_eSPI_ES32Lab` foi derivada.
- [`ES_File`](../ES_File/README.md): usada para abrir, localizar e navegar entre arquivos JPEG nos sistemas de arquivos.
- [`ES_Camera`](../ES_Camera/README.md): usada nos métodos que exibem frames capturados pela câmera.
- `JPEGDecoder`: biblioteca usada internamente para decodificar imagens JPEG por blocos.

Como `ES_TFT` herda da classe gráfica fornecida pela `TFT_eSPI_ES32Lab`, os métodos públicos da base gráfica continuam disponíveis, como `begin()`, `setRotation()`, `fillScreen()`, `setCursor()`, `print()`, `println()`, `drawString()`, `drawLine()`, `drawRect()`, `pushImage()` e outros.

---

## Configuração do Display

A configuração física do display é fornecida pela biblioteca [`TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab). No contexto interno dessa biblioteca, o arquivo [`User_Setup.h`](./User_Setup.h) define:

- driver do display;
- pinos SPI;
- pino de controle DC;
- pino CS;
- pino de reset;
- frequência SPI;
- fontes carregadas na compilação;
- suporte a fontes suaves com `SMOOTH_FONT`.

Na configuração atual da ES32Lab, o arquivo define o driver `ST7735_DRIVER` e os pinos usados pela placa. Essa classe foi pensada especificamente para uso com a placa ES32Lab e seu display TFT.

> **Nota:**  
> Alterações em `User_Setup.h` afetam diretamente a comunicação com o display. Para a placa ES32Lab, recomenda-se manter a configuração oficial da biblioteca `TFT_eSPI_ES32Lab`.

---

## Construtor

### `ES_TFT()`

Cria uma instância da classe `ES_TFT`.

#### Sintaxe:
```cpp
ES_TFT display;
```

#### Exemplo:
```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TFT display;
```

---

## Inicialização no `setup()`

A inicialização do display é feita com o método `begin()`, herdado da base gráfica fornecida pela `TFT_eSPI_ES32Lab`. Normalmente, também é configurada a rotação da tela com `setRotation()`.

#### Exemplo:
```cpp
void setup() {
    display.begin();
    display.setRotation(3);
    display.fillScreen(TFT_BLACK);
}
```

> **Importante:**  
> `begin()`, `setRotation()`, `fillScreen()` e a maioria dos métodos gráficos são herdados da `TFT_eSPI_ES32Lab`. A classe `ES_TFT` adiciona métodos de conveniência sobre essa base.

---

## Métodos Herdados da TFT_eSPI_ES32Lab

Como `ES_TFT` herda da base gráfica da `TFT_eSPI_ES32Lab`, os métodos tradicionais de controle do display continuam disponíveis diretamente no objeto `ES_TFT`.

Na prática, isso significa que o mesmo objeto usado para os métodos próprios da `ES_TFT` também pode chamar os métodos herdados da biblioteca gráfica:

```cpp
ES_TFT display;

display.begin();                    // Método herdado da TFT_eSPI_ES32Lab.
display.fillScreen(TFT_BLACK);      // Método herdado da TFT_eSPI_ES32Lab.
display.drawCentreScreenString("ES32Lab", 20); // Método próprio da ES_TFT.
```

Esta seção não substitui a documentação completa da biblioteca [`TFT_eSPI_ES32Lab`](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab), mas apresenta os métodos mais importantes para uso didático com a ES32Lab.

### Convenções básicas

- **Coordenadas**: a origem padrão é o canto superior esquerdo da tela. O eixo `x` cresce para a direita e o eixo `y` cresce para baixo.
- **Largura e altura**: em métodos como `fillRect(x, y, w, h, color)`, `w` representa largura e `h` representa altura.
- **Cores**: as cores normalmente usam o formato RGB565 de 16 bits. A biblioteca já fornece constantes como `TFT_BLACK`, `TFT_WHITE`, `TFT_RED`, `TFT_GREEN`, `TFT_BLUE`, `TFT_YELLOW`, `TFT_CYAN` e `TFT_MAGENTA`.
- **Rotação**: `setRotation()` altera a orientação da tela e também muda os valores retornados por `width()` e `height()`.
- **Texto**: métodos como `print()` e `println()` usam a posição definida por `setCursor()`. Métodos como `drawString()` recebem a posição diretamente.

### Inicialização e configuração

Esses métodos preparam o display e ajustam propriedades gerais de funcionamento.

```cpp
display.begin();
display.init();
display.setRotation(3);
display.getRotation();
display.invertDisplay(false);
```

| Método | Uso principal |
| :------ | :------ |
| `begin()` | Inicializa o display. É o método mais comum no `setup()`. |
| `init()` | Equivalente a `begin()`. Mantido pela biblioteca base por compatibilidade. |
| `setRotation(r)` | Define a rotação da tela. Normalmente usa valores de `0` a `3`. |
| `getRotation()` | Retorna a rotação atual. |
| `invertDisplay(status)` | Inverte ou restaura as cores exibidas no display. |

#### Exemplo:
```cpp
void setup() {
    display.begin();
    display.setRotation(3);
    display.invertDisplay(false);
    display.fillScreen(TFT_BLACK);
}
```

### Dimensões, origem e área útil

Esses métodos ajudam a consultar o tamanho atual da tela e a alterar a origem das coordenadas.

```cpp
int16_t largura = display.width();
int16_t altura  = display.height();

display.setOrigin(10, 10);
int32_t origemX = display.getOriginX();
int32_t origemY = display.getOriginY();
```

| Método | Uso principal |
| :------ | :------ |
| `width()` | Retorna a largura atual da tela, considerando a rotação. |
| `height()` | Retorna a altura atual da tela, considerando a rotação. |
| `setOrigin(x, y)` | Altera a origem das coordenadas. |
| `getOriginX()` | Retorna a origem atual no eixo `x`. |
| `getOriginY()` | Retorna a origem atual no eixo `y`. |

> **Nota:**  
> `setRotation()`, `setViewport()` e `resetViewport()` podem redefinir a origem para o canto superior esquerdo. Em exemplos didáticos, normalmente é mais simples manter a origem padrão.

### Controle de tela e texto

Esses métodos são usados para limpar a tela, posicionar texto e escrever usando a interface padrão `Print` do Arduino.

```cpp
display.fillScreen(TFT_BLACK);
display.setCursor(0, 0);
display.setTextColor(TFT_WHITE);
display.setTextSize(2);
display.setTextFont(2);
display.print("Texto");
display.println("Linha");
```

| Método | Uso principal |
| :------ | :------ |
| `fillScreen(color)` | Preenche toda a tela com uma cor. |
| `setCursor(x, y)` | Define a posição usada por `print()` e `println()`. |
| `getCursorX()` | Retorna a posição atual do cursor no eixo `x`. |
| `getCursorY()` | Retorna a posição atual do cursor no eixo `y`. |
| `setTextColor(color)` | Define a cor do texto sem preencher o fundo. |
| `setTextColor(fg, bg)` | Define cor do texto e cor de fundo. |
| `setTextSize(size)` | Define o multiplicador de tamanho da fonte. |
| `setTextFont(font)` | Seleciona uma fonte numérica da biblioteca. |
| `setTextWrap(wrapX, wrapY)` | Ativa ou desativa a quebra automática de texto. |
| `print()` | Escreve texto, números ou variáveis na posição do cursor. |
| `println()` | Igual a `print()`, mas avança para a próxima linha. |

#### Exemplo:
```cpp
display.fillScreen(TFT_BLACK);
display.setCursor(5, 10);
display.setTextColor(TFT_WHITE, TFT_BLACK);
display.setTextSize(1);
display.println("Sistema iniciado");
display.print("Versao: ");
display.println(ES_TFT_VERSION);
```

### Desenho de textos

Esses métodos desenham textos em posições específicas e retornam a largura renderizada em pixels.

```cpp
display.drawString("Texto", 10, 20);
display.drawCentreString("Centro", 80, 40, 2);
display.drawRightString("Direita", 160, 60, 2);
display.drawNumber(123, 10, 80);
display.drawFloat(3.14, 2, 10, 100);
```

| Método | Uso principal |
| :------ | :------ |
| `drawString(texto, x, y)` | Desenha uma string usando a fonte atual. |
| `drawString(texto, x, y, font)` | Desenha uma string usando uma fonte específica. |
| `drawNumber(numero, x, y)` | Desenha um número inteiro. |
| `drawNumber(numero, x, y, font)` | Desenha um número inteiro com fonte específica. |
| `drawFloat(valor, casas, x, y)` | Desenha número decimal com quantidade definida de casas decimais. |
| `drawFloat(valor, casas, x, y, font)` | Desenha número decimal com fonte específica. |
| `drawCentreString(texto, x, y, font)` | Desenha texto centralizado em relação ao ponto `x`. |
| `drawRightString(texto, x, y, font)` | Desenha texto alinhado à direita em relação ao ponto `x`. |

> **Recomendação:**  
> Para novos projetos, prefira `setTextDatum()` com `drawString()` quando precisar de alinhamento mais controlado. Os métodos próprios da `ES_TFT`, como `drawCentreScreenString()` e `drawRightScreenString()`, continuam úteis quando o objetivo é alinhar o texto em relação à tela inteira.

### Alinhamento, medidas e padding de texto

Esses métodos ajudam a posicionar textos com precisão e a atualizar valores sem deixar resíduos na tela.

```cpp
display.setTextDatum(MC_DATUM);
display.setTextPadding(80);
display.drawString("OK", display.width() / 2, display.height() / 2, 2);

int16_t larguraTexto = display.textWidth("OK", 2);
int16_t alturaFonte  = display.fontHeight(2);
```

| Método | Uso principal |
| :------ | :------ |
| `setTextDatum(datum)` | Define o ponto de referência usado por `drawString()`, `drawNumber()` e `drawFloat()`. |
| `getTextDatum()` | Retorna o datum atual. |
| `setTextPadding(width)` | Define uma área de limpeza horizontal para sobrescrever textos antigos. |
| `getTextPadding()` | Retorna o padding atual. |
| `textWidth(texto)` | Retorna a largura do texto com a fonte atual. |
| `textWidth(texto, font)` | Retorna a largura do texto com uma fonte específica. |
| `fontHeight()` | Retorna a altura da fonte atual. |
| `fontHeight(font)` | Retorna a altura de uma fonte específica. |

#### Datums mais comuns:
| Constante | Referência |
| :------ | :------ |
| `TL_DATUM` | Topo à esquerda. |
| `TC_DATUM` | Topo centralizado. |
| `TR_DATUM` | Topo à direita. |
| `ML_DATUM` ou `CL_DATUM` | Meio à esquerda. |
| `MC_DATUM` ou `CC_DATUM` | Centro exato. |
| `MR_DATUM` ou `CR_DATUM` | Meio à direita. |
| `BL_DATUM` | Base à esquerda. |
| `BC_DATUM` | Base centralizada. |
| `BR_DATUM` | Base à direita. |

#### Exemplo:
```cpp
display.fillScreen(TFT_BLACK);
display.setTextColor(TFT_WHITE, TFT_BLACK);
display.setTextDatum(MC_DATUM);
display.drawString("CENTRO", display.width() / 2, display.height() / 2, 2);
```

### Primitivas gráficas

Esses métodos desenham formas geométricas simples diretamente no display.

```cpp
display.drawPixel(10, 10, TFT_WHITE);
display.drawLine(0, 0, 100, 50, TFT_GREEN);
display.drawFastHLine(0, 20, 100, TFT_BLUE);
display.drawFastVLine(20, 0, 80, TFT_BLUE);
display.drawRect(10, 10, 60, 40, TFT_YELLOW);
display.fillRect(10, 60, 60, 30, TFT_RED);
display.drawRoundRect(5, 5, 80, 50, 6, TFT_CYAN);
display.fillRoundRect(5, 60, 80, 40, 6, TFT_CYAN);
display.drawCircle(80, 60, 20, TFT_WHITE);
display.fillCircle(120, 60, 20, TFT_MAGENTA);
display.drawTriangle(20, 100, 60, 100, 40, 70, TFT_ORANGE);
display.fillTriangle(90, 100, 130, 100, 110, 70, TFT_ORANGE);
```

| Método | Uso principal |
| :------ | :------ |
| `drawPixel(x, y, color)` | Desenha um único pixel. |
| `drawLine(x1, y1, x2, y2, color)` | Desenha uma linha entre dois pontos. |
| `drawFastHLine(x, y, w, color)` | Desenha uma linha horizontal. |
| `drawFastVLine(x, y, h, color)` | Desenha uma linha vertical. |
| `drawRect(x, y, w, h, color)` | Desenha o contorno de um retângulo. |
| `fillRect(x, y, w, h, color)` | Desenha um retângulo preenchido. |
| `drawRoundRect(x, y, w, h, radius, color)` | Desenha retângulo com cantos arredondados. |
| `fillRoundRect(x, y, w, h, radius, color)` | Desenha retângulo arredondado preenchido. |
| `drawCircle(x, y, r, color)` | Desenha o contorno de um círculo. |
| `fillCircle(x, y, r, color)` | Desenha um círculo preenchido. |
| `drawEllipse(x, y, rx, ry, color)` | Desenha o contorno de uma elipse. |
| `fillEllipse(x, y, rx, ry, color)` | Desenha uma elipse preenchida. |
| `drawTriangle(x1, y1, x2, y2, x3, y3, color)` | Desenha o contorno de um triângulo. |
| `fillTriangle(x1, y1, x2, y2, x3, y3, color)` | Desenha um triângulo preenchido. |

### Gradientes e gráficos suavizados

A biblioteca base também oferece alguns métodos para gradientes e formas com antialiasing. Eles podem deixar a interface mais bonita, mas exigem mais processamento que as primitivas simples.

```cpp
display.fillRectVGradient(0, 0, display.width(), display.height(), TFT_BLUE, TFT_BLACK);
display.fillRectHGradient(0, 0, display.width(), 30, TFT_RED, TFT_YELLOW);

display.drawSmoothArc(80, 64, 50, 40, 30, 300, TFT_GREEN, TFT_BLACK, true);
display.fillSmoothCircle(80, 64, 20, TFT_CYAN, TFT_BLACK);
display.drawWideLine(10, 110, 150, 110, 6, TFT_WHITE, TFT_BLACK);
```

| Método | Uso principal |
| :------ | :------ |
| `fillRectVGradient(x, y, w, h, color1, color2)` | Preenche retângulo com gradiente vertical. |
| `fillRectHGradient(x, y, w, h, color1, color2)` | Preenche retângulo com gradiente horizontal. |
| `drawPixel(x, y, color, alpha, bg)` | Desenha pixel com transparência simulada por mistura de cores. |
| `drawSmoothArc(x, y, r, ir, start, end, fg, bg, roundEnds)` | Desenha arco suavizado. |
| `drawArc(x, y, r, ir, start, end, fg, bg, smoothArc)` | Desenha arco comum ou suavizado. |
| `drawSmoothCircle(x, y, r, fg, bg)` | Desenha círculo suavizado. |
| `fillSmoothCircle(x, y, r, color, bg)` | Desenha círculo preenchido suavizado. |
| `drawSmoothRoundRect(x, y, r, ir, w, h, fg, bg)` | Desenha retângulo arredondado suavizado. |
| `fillSmoothRoundRect(x, y, w, h, radius, color, bg)` | Desenha retângulo arredondado preenchido e suavizado. |
| `drawWideLine(ax, ay, bx, by, width, fg, bg)` | Desenha linha larga suavizada. |
| `drawWedgeLine(ax, ay, bx, by, aw, bw, fg, bg)` | Desenha linha suavizada com larguras diferentes nas extremidades. |

### Viewport

Viewport limita a região onde os desenhos aparecem. É útil quando uma interface possui áreas fixas, como barra superior, área de conteúdo e rodapé.

```cpp
display.setViewport(0, 20, display.width(), display.height() - 20);
display.fillScreen(TFT_BLACK);      // Preenche apenas a viewport.
display.drawString("Area util", 5, 5);
display.frameViewport(TFT_YELLOW, 1);
display.resetViewport();
```

| Método | Uso principal |
| :------ | :------ |
| `setViewport(x, y, w, h, vpDatum)` | Define uma área de desenho limitada. |
| `checkViewport(x, y, w, h)` | Verifica se uma área cruza a viewport atual. |
| `getViewportX()` | Retorna o `x` da viewport. |
| `getViewportY()` | Retorna o `y` da viewport. |
| `getViewportWidth()` | Retorna a largura da viewport. |
| `getViewportHeight()` | Retorna a altura da viewport. |
| `getViewportDatum()` | Informa se as coordenadas usam a viewport como referência. |
| `frameViewport(color, w)` | Desenha uma borda ao redor da viewport. |
| `resetViewport()` | Remove a viewport e volta a usar a tela inteira. |
| `clipAddrWindow()` | Ajusta uma área para caber dentro da viewport. |
| `clipWindow()` | Ajusta coordenadas finais para caber dentro da viewport. |

> **Atenção:**  
> Enquanto uma viewport estiver ativa, métodos como `fillScreen()` e desenhos comuns podem afetar apenas a região limitada. Use `resetViewport()` quando quiser voltar a desenhar na tela inteira.

### Imagens e buffers

Esses métodos enviam blocos de pixels ou imagens RGB565 diretamente para o display. Eles são úteis para ícones, sprites, imagens convertidas para arrays C/C++ e buffers gerados em tempo de execução.

```cpp
display.setSwapBytes(true);
display.getSwapBytes();
display.pushImage(0, 0, largura, altura, bufferRGB565);
```

| Método | Uso principal |
| :------ | :------ |
| `setSwapBytes(status)` | Inverte a ordem dos bytes ao enviar imagens RGB565. |
| `getSwapBytes()` | Retorna se a troca de bytes está ativa. |
| `pushImage(x, y, w, h, data)` | Renderiza uma imagem RGB565 armazenada em RAM ou FLASH. |
| `pushImage(x, y, w, h, data, transparent)` | Renderiza imagem ignorando uma cor transparente. |
| `pushMaskedImage(x, y, w, h, img, mask)` | Renderiza imagem usando máscara de 1 bit. |
| `pushPixels(data, len)` | Envia uma sequência de pixels para uma janela já configurada. |
| `setAddrWindow(x, y, w, h)` | Define uma janela para envio sequencial de pixels. |
| `pushBlock(color, len)` | Escreve vários pixels da mesma cor na janela atual. |
| `drawBitmap(x, y, bitmap, w, h, fg)` | Desenha bitmap monocromático com cor de frente. |
| `drawBitmap(x, y, bitmap, w, h, fg, bg)` | Desenha bitmap monocromático com cor de frente e fundo. |
| `drawXBitmap(x, y, bitmap, w, h, fg)` | Desenha bitmap no formato XBM. |
| `setBitmapColor(fg, bg)` | Define cores padrão para bitmaps de 1 bit por pixel. |

#### Exemplo com array RGB565:
```cpp
const uint16_t icone[] PROGMEM = {
    TFT_RED, TFT_GREEN,
    TFT_BLUE, TFT_WHITE
};

display.setSwapBytes(false);
display.pushImage(20, 20, 2, 2, icone);
```

#### Exemplo com envio manual de pixels:
```cpp
display.setAddrWindow(0, 0, 10, 10);
display.pushBlock(TFT_RED, 100);
```

### Leitura de pixels e cópia de áreas

Esses métodos leem pixels do display ou copiam blocos de uma área para outra.

```cpp
uint16_t cor = display.readPixel(10, 10);

uint16_t bloco[20 * 20];
display.readRect(0, 0, 20, 20, bloco);
display.pushRect(40, 40, 20, 20, bloco);
```

| Método | Uso principal |
| :------ | :------ |
| `readPixel(x, y)` | Lê a cor RGB565 de um pixel. |
| `readRect(x, y, w, h, data)` | Lê uma área para um buffer RGB565. |
| `pushRect(x, y, w, h, data)` | Escreve no display um bloco RGB565 lido anteriormente. |
| `readRectRGB(x, y, w, h, data)` | Lê uma área em formato RGB888, usando 3 bytes por pixel. |

> **Observação:**  
> A leitura do display costuma ser mais lenta que a escrita e depende da configuração de hardware. Use esses métodos apenas quando realmente precisar recuperar pixels da tela.

### Conversão e mistura de cores

Esses métodos ajudam a converter cores e criar efeitos simples de mistura.

```cpp
uint16_t vermelho = display.color565(255, 0, 0);
uint16_t azul     = display.color565(0, 0, 255);
uint16_t meioTom  = display.alphaBlend(128, vermelho, azul);

display.fillScreen(meioTom);
```

| Método | Uso principal |
| :------ | :------ |
| `color565(r, g, b)` | Converte RGB888 para RGB565. |
| `color8to16(color332)` | Converte cor RGB332 para RGB565. |
| `color16to8(color565)` | Converte RGB565 para RGB332. |
| `color16to24(color565)` | Converte RGB565 para RGB888 empacotado em 24 bits. |
| `color24to16(color888)` | Converte RGB888 empacotado em 24 bits para RGB565. |
| `alphaBlend(alpha, fg, bg)` | Mistura duas cores RGB565. |
| `alphaBlend24(alpha, fg, bg)` | Mistura duas cores RGB888 empacotadas em 24 bits. |

### Fontes suaves

Fontes suaves são fontes com antialiasing carregadas de arquivo `.vlw` ou de array em FLASH. Na classe `ES_TFT`, o método próprio `loadFontFile()` simplifica o carregamento a partir de `SD`, `SPIFFS` ou `LittleFS`, mas os métodos herdados também ficam disponíveis.

```cpp
display.loadFont("MinhaFonte");
display.unloadFont();
```

| Método | Uso principal |
| :------ | :------ |
| `loadFont(nome)` | Carrega uma fonte suave pelo nome. |
| `loadFont(nome, fs)` | Carrega uma fonte suave a partir de um sistema de arquivos, quando suportado. |
| `loadFont(array)` | Carrega uma fonte suave armazenada em array. |
| `unloadFont()` | Libera a fonte suave carregada. |
| `showFont(delayMs)` | Exibe os caracteres da fonte carregada, útil para teste visual. |

> **Observação:**  
> O uso de fontes suaves depende de `SMOOTH_FONT` estar habilitado na configuração da biblioteca.

### Sprites

`TFT_eSprite` é uma classe auxiliar da `TFT_eSPI_ES32Lab`. Ela cria uma área de desenho em memória RAM. Você desenha primeiro no sprite e depois envia o resultado para o display. Isso é útil para reduzir flicker em interfaces que atualizam pequenos elementos.

```cpp
TFT_eSprite sprite(&display);

sprite.createSprite(80, 30);
sprite.fillSprite(TFT_BLACK);
sprite.setTextColor(TFT_WHITE, TFT_BLACK);
sprite.drawString("Temp: 25C", 5, 8, 2);
sprite.pushSprite(20, 40);
sprite.deleteSprite();
```

| Método | Uso principal |
| :------ | :------ |
| `createSprite(w, h)` | Cria o buffer em RAM. |
| `deleteSprite()` | Libera a memória usada pelo sprite. |
| `fillSprite(color)` | Preenche o sprite com uma cor. |
| `pushSprite(x, y)` | Envia o sprite para o display. |
| `pushSprite(x, y, transparent)` | Envia o sprite ignorando uma cor transparente. |
| `setColorDepth(bpp)` | Define profundidade de cor do sprite: 1, 4, 8 ou 16 bits. |
| `getColorDepth()` | Retorna a profundidade de cor atual. |
| `created()` | Informa se o sprite foi criado. |

> **Atenção sobre memória:**  
> Sprites usam RAM. Um sprite RGB565 de 100 x 50 pixels usa aproximadamente 10 KB. Em interfaces simples, prefira sprites pequenos e libere com `deleteSprite()` quando não forem mais necessários.

### Transações, DMA e métodos avançados

Esses métodos existem na biblioteca base para casos avançados de desempenho e escrita direta no barramento. Em uso didático, normalmente não são necessários.

```cpp
display.startWrite();
display.setAddrWindow(0, 0, 20, 20);
display.pushBlock(TFT_GREEN, 400);
display.endWrite();
```

| Método | Uso principal |
| :------ | :------ |
| `startWrite()` | Inicia uma transação de escrita no display. |
| `endWrite()` | Finaliza uma transação de escrita. |
| `initDMA()` | Inicializa DMA quando suportado. |
| `deInitDMA()` | Desativa DMA. |
| `pushImageDMA(x, y, w, h, data)` | Envia imagem usando DMA quando suportado. |
| `pushPixelsDMA(data, len)` | Envia pixels usando DMA. |
| `dmaBusy()` | Informa se há transferência DMA em andamento. |
| `dmaWait()` | Aguarda o fim da transferência DMA. |

> **Recomendação:**  
> Use DMA apenas quando houver necessidade real de desempenho e depois de validar o comportamento com a placa usada. Para a maioria dos exemplos da ES32Lab, os métodos comuns de desenho são mais simples e suficientes.

### Diagnóstico e atributos

Esses métodos ajudam a verificar a configuração ativa da biblioteca e alterar alguns comportamentos internos.

```cpp
setup_t info;
display.getSetup(info);

Serial.println(info.version);
Serial.println(info.tft_width);
Serial.println(info.tft_height);

display.setAttribute(UTF8_SWITCH, true);
uint8_t utf8Ativo = display.getAttribute(UTF8_SWITCH);
```

| Método | Uso principal |
| :------ | :------ |
| `getSetup(info)` | Preenche uma estrutura `setup_t` com dados da configuração compilada. |
| `verifySetupID(id)` | Verifica se o ID de configuração corresponde ao esperado. |
| `setAttribute(id, value)` | Ajusta atributos internos, como UTF-8 e CP437. |
| `getAttribute(id)` | Lê o valor de um atributo interno. |
| `fontsLoaded()` | Retorna um mapa de bits indicando fontes carregadas na compilação. |

---

## Métodos de Texto

### `drawCentreScreenString()`

Desenha uma string centralizada horizontalmente na tela. O método calcula automaticamente o centro com base na largura atual do display.

#### Sintaxe:
```cpp
int16_t drawCentreScreenString(const char *string, int32_t y, uint8_t font = 1);
int16_t drawCentreScreenString(const String& string, int32_t y, uint8_t font = 1);
```

#### Parâmetros:
- **`string`**: texto a ser desenhado.
- **`y`**: posição vertical do texto.
- **`font`**: fonte utilizada pela base gráfica da `TFT_eSPI_ES32Lab`.

#### Retorno:
- Largura do texto desenhado, conforme retorno da base gráfica da `TFT_eSPI_ES32Lab`.

#### Exemplo:
```cpp
display.drawCentreScreenString("ES32Lab", 20, 2);
display.drawCentreScreenString("Display TFT", 45);
```

---

### `drawRightScreenString()`

Desenha uma string alinhada à direita da tela.

#### Sintaxe:
```cpp
int16_t drawRightScreenString(const char *string, int32_t y, uint8_t font = 1);
int16_t drawRightScreenString(const String& string, int32_t y, uint8_t font = 1);
```

#### Parâmetros:
- **`string`**: texto a ser desenhado.
- **`y`**: posição vertical do texto.
- **`font`**: fonte utilizada pela base gráfica da `TFT_eSPI_ES32Lab`.

#### Retorno:
- Largura do texto desenhado, conforme retorno da base gráfica da `TFT_eSPI_ES32Lab`.

#### Exemplo:
```cpp
display.drawRightScreenString("OK", 10);
display.drawRightScreenString("100%", 30, 2);
```

---

## Renderização de JPEG

A `ES_TFT` pode renderizar imagens JPEG armazenadas em um sistema de arquivos, como `SD`, `SPIFFS` ou `LittleFS`. A abertura do arquivo é feita com apoio da classe [`ES_File`](../ES_File/README.md), e a decodificação é feita pela biblioteca `JPEGDecoder`.

### `renderJPEG()`

Renderiza uma imagem JPEG a partir do sistema de arquivos informado.

#### Sintaxe:
```cpp
bool renderJPEG(fs::FS& fs, const String& fileName, int xpos = 0, int ypos = 0, bool fitToScreen = true);
```

#### Parâmetros:
- **`fs`**: sistema de arquivos onde a imagem está armazenada. Exemplos: `SD`, `SPIFFS` ou `LittleFS`.
- **`fileName`**: nome ou caminho do arquivo JPEG.
- **`xpos`**: posição horizontal inicial da imagem.
- **`ypos`**: posição vertical inicial da imagem.
- **`fitToScreen`**: quando `true`, reduz automaticamente imagens maiores que a área disponível do display. O valor padrão é `true`.

#### Retorno:
- **`true`**: se a imagem foi aberta, decodificada e renderizada.
- **`false`**: se o arquivo não existir, não puder ser aberto ou não puder ser decodificado.

#### Funcionamento:
- Se o nome informado não possuir extensão `.jpg` ou `.jpeg`, a classe tenta acrescentar `.jpg`.
- Extensões `.jpg`, `.JPG`, `.jpeg` e `.JPEG` são aceitas.
- Se `fitToScreen` for `true` e a imagem for maior que a área disponível, a classe reduz a imagem mantendo a proporção.
- Se a imagem já couber na área disponível, o método usa o render original, sem redimensionamento.
- Se `fitToScreen` for `false`, a imagem é renderizada no tamanho original.

> **Atenção:**  
> O redimensionamento automático é útil para compatibilidade, mas exige mais processamento. Para melhor desempenho, prefira salvar imagens já no tamanho do display ou em tamanho próximo.

#### Exemplo de Uso 1: Renderização com ajuste automático
```cpp
display.renderJPEG(SD, "/foto.jpg");
```

#### Exemplo de Uso 2: Renderização sem ajuste automático
```cpp
display.renderJPEG(SD, "/foto.jpg", 0, 0, false);
```

#### Exemplo de Uso 3: Renderização em posição personalizada
```cpp
display.renderJPEG(SD, "/imagens/logo", 10, 20);
```

---

### `renderJpegBuffer()`

Renderiza uma imagem JPEG armazenada em um buffer de memória RAM.

#### Sintaxe:
```cpp
bool renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos = 0, int ypos = 0);
```

#### Parâmetros:
- **`jpegBuf`**: ponteiro para o buffer JPEG.
- **`jpegLen`**: tamanho do buffer JPEG em bytes.
- **`xpos`**: posição horizontal inicial.
- **`ypos`**: posição vertical inicial.

#### Retorno:
- **`true`**: se o buffer foi decodificado e renderizado.
- **`false`**: caso contrário.

#### Nota:
Este método não aplica redimensionamento automático. Ele é usado principalmente para dados já carregados em memória, como frames JPEG capturados pela câmera.

---

## Renderização de Frame da Câmera

### `renderCameraFrame()`

Captura um frame da câmera e renderiza diretamente no display.

#### Sintaxe:
```cpp
bool renderCameraFrame(ES_Camera& camera, int xpos = 0, int ypos = 0);
```

#### Parâmetros:
- **`camera`**: objeto [`ES_Camera`](../ES_Camera/README.md) já inicializado.
- **`xpos`**: posição horizontal inicial.
- **`ypos`**: posição vertical inicial.

#### Retorno:
- **`true`**: se o frame foi capturado e renderizado.
- **`false`**: se a captura falhar ou se o formato do frame não for suportado.

#### Funcionamento:
- Se o frame estiver em `PIXFORMAT_JPEG`, o método usa `renderJpegBuffer()`.
- Se o frame estiver em `PIXFORMAT_RGB565`, o método envia os pixels diretamente ao display com `pushImage()`.

> **Dica de desempenho:**  
> Para exibição contínua no display, use resoluções compatíveis com o tamanho do TFT. Frames muito grandes aumentam o tempo de renderização e o consumo de memória.

---

## Navegação entre Arquivos JPEG

Os métodos de navegação usam a classe [`ES_File`](../ES_File/README.md) para localizar arquivos em um diretório e renderizar apenas arquivos reconhecidos como JPEG.

### `renderFirstFileJPEG()`

Renderiza o primeiro arquivo JPEG encontrado em um diretório.

#### Sintaxe:
```cpp
bool renderFirstFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0, bool fitToScreen = true);
```

#### Parâmetros:
- **`fs`**: sistema de arquivos.
- **`directory`**: diretório onde os arquivos serão procurados.
- **`xpos`**: posição horizontal inicial.
- **`ypos`**: posição vertical inicial.
- **`fitToScreen`**: ativa ou desativa o ajuste automático de tamanho.

#### Retorno:
- **`true`**: se encontrou e renderizou um JPEG.
- **`false`**: se não encontrou imagem válida.

---

### `renderLastFileJPEG()`

Renderiza o último arquivo JPEG encontrado em um diretório.

#### Sintaxe:
```cpp
bool renderLastFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0, bool fitToScreen = true);
```

#### Exemplo:
```cpp
display.renderLastFileJPEG(SD, "/fotos");
```

---

### `renderNextFileJPEG()`

Renderiza o próximo arquivo JPEG com base no arquivo atual ou no caminho informado.

#### Sintaxe:
```cpp
bool renderNextFileJPEG(fs::FS& fs, const String& path = "", int xpos = 0, int ypos = 0, bool fitToScreen = true);
```

#### Exemplo:
```cpp
display.renderNextFileJPEG(SD);
```

---

### `renderPreviousFileJPEG()`

Renderiza o arquivo JPEG anterior com base no arquivo atual ou no caminho informado.

#### Sintaxe:
```cpp
bool renderPreviousFileJPEG(fs::FS& fs, const String& path = "", int xpos = 0, int ypos = 0, bool fitToScreen = true);
```

#### Exemplo:
```cpp
display.renderPreviousFileJPEG(SD);
```

> **Nota sobre navegação:**  
> Arquivos que não possuem extensão JPEG são ignorados. Se não houver nenhum arquivo `.jpg` ou `.jpeg` disponível no diretório, os métodos retornam `false`.

---

## Carregamento de Fontes

### `loadFontFile()`

Carrega uma fonte armazenada em sistema de arquivos para uso com os métodos de texto da base gráfica da `TFT_eSPI_ES32Lab`.

#### Sintaxe:
```cpp
void loadFontFile(fs::FS& fs, const String& fontName);
```

#### Parâmetros:
- **`fs`**: sistema de arquivos onde a fonte está armazenada.
- **`fontName`**: nome do arquivo de fonte. A extensão `.vlw` pode ser informada ou omitida.

#### Exemplo:
```cpp
display.loadFontFile(SD, "/fontes/minhaFonte.vlw");
display.drawString("Texto com fonte carregada", 10, 30);
display.unloadFont();
```

> **Nota:**  
> O suporte a fontes suaves depende de `SMOOTH_FONT` estar habilitado no arquivo `User_Setup.h`.

---

## Versão da Classe

A versão atual da classe é disponibilizada pela macro:

```cpp
ES_TFT_VERSION
```

#### Exemplo:
```cpp
Serial.println(ES_TFT_VERSION);
display.println(ES_TFT_VERSION);
```

---

## Recomendações de Desempenho

A renderização de imagens em um ESP32 possui limitações naturais de memória e processamento. Para obter melhor resultado:

- Use imagens já redimensionadas para a resolução do display sempre que possível.
- Prefira JPEGs com resolução igual ou próxima à resolução física da tela.
- Evite imagens muito grandes quando a intenção for apenas exibir no TFT.
- Use `fitToScreen = true` como recurso de conveniência, não como fluxo principal de alta performance.
- Use `fitToScreen = false` quando tiver certeza de que a imagem já está no tamanho correto.
- Em visualizadores de fotos, prepare as imagens previamente no computador antes de gravá-las no cartão SD.
- Para exibição contínua de câmera, configure a [`ES_Camera`](../ES_Camera/README.md) com resolução compatível com o display.

### Sobre qualidade visual

O redimensionamento automático implementado pela classe prioriza baixo uso de RAM e simplicidade. Por isso, a imagem reduzida pode apresentar perda de nitidez quando comparada a uma imagem redimensionada previamente em um computador.

## Exemplo Completo: Texto no Display

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TFT display;

void setup() {
    display.begin();
    display.setRotation(3);
    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE);

    display.drawCentreScreenString("ES32Lab", 20, 2);
    display.drawCentreScreenString("Display TFT", 45);
    display.drawRightScreenString(ES_TFT_VERSION, 100);
}

void loop() {

}
```

---

## Exemplo Completo: Renderizar JPEG do Cartão SD

Este exemplo renderiza uma imagem armazenada no cartão SD. A imagem será ajustada automaticamente caso seja maior que a tela.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TFT display;

void setup() {
    display.begin();
    display.setRotation(3);
    display.fillScreen(TFT_BLACK);

    if (!display.renderJPEG(SD, "/foto.jpg")) {
        display.setTextColor(TFT_RED);
        display.drawCentreScreenString("Falha ao abrir JPEG", 50);
    }
}

void loop() {

}
```

### Renderização sem redimensionamento

```cpp
display.renderJPEG(SD, "/foto.jpg", 0, 0, false);
```

---

## Exemplo Completo: Visualizador de Fotos com Teclado

Este exemplo usa o teclado analógico da ES32Lab para navegar entre imagens JPEG no cartão SD.

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_TFT display;
ES_AnalogKeyboard keyboard(P_KEYBOARD);

void setup() {
    display.begin();
    display.setRotation(3);
    display.fillScreen(TFT_BLACK);

    display.renderFirstFileJPEG(SD, "/");
}

void loop() {
    if (keyboard.press(KEY_LEFT)) {
        display.renderPreviousFileJPEG(SD);
    }

    if (keyboard.press(KEY_RIGHT)) {
        display.renderNextFileJPEG(SD);
    }
}
```

---

## Exemplo Completo: Frame da Câmera no Display

```cpp
#include <Arduino.h>
#include <ES32Lab.h>

ES_Camera camera;
ES_TFT display;

void setup() {
    display.begin();
    display.setRotation(3);
    display.fillScreen(TFT_BLACK);

    if (!camera.begin()) {
        display.fillScreen(TFT_RED);
        display.println("Camera failed!");
        while (true);
    }
}

void loop() {
    display.renderCameraFrame(camera);
}
```

---

## Exemplos Oficiais

A biblioteca ES32Lab possui exemplos práticos para uso da classe `ES_TFT` em textos, desenhos, imagens JPEG, fontes e integração com câmera.

- [Biblioteca TFT_eSPI_ES32Lab](https://github.com/ESDeveloperBR/TFT_eSPI_ES32Lab)
- [Exemplos Oficiais da Classe ES_TFT](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/Display-TFT)
- [Exemplo de Câmera com Display TFT](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/Camera/Camera-DisplayTFT)
- [Exemplo de Foto Salva no SD e Exibida no TFT](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/Camera/Camera-SaveFrameToSD)

Esses exemplos servem como ponto de partida para interfaces visuais, visualizadores de fotos, testes gráficos, carregamento de fontes e projetos com câmera.

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |
