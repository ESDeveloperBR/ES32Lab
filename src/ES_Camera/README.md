| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |


---


# Documentação da Classe ES_Camera

A classe `ES_Camera` é um componente avançado e versátil da biblioteca ES32Lab, projetada para simplificar o controle e a configuração de câmeras compatíveis com o ESP32. Ela oferece uma interface poderosa e intuitiva para capturar imagens, ajustar configurações do sensor e realizar streaming de vídeo em tempo real, tornando-a ideal para uma ampla gama de aplicações.

Com suporte a funcionalidades como ajuste de brilho, contraste, saturação, controle de exposição, efeitos especiais e muito mais, a `ES_Camera` é uma ferramenta indispensável para projetos que exigem captura de imagens ou vídeos. Exemplos incluem sistemas de vigilância, robótica, IoT, aplicações interativas e protótipos avançados.

Além disso, a classe permite salvar imagens capturadas em sistemas de arquivos como SPIFFS ou SD, bem como configurar endpoints HTTP para streaming de vídeo. A `ES_Camera` é otimizada para oferecer alto desempenho e flexibilidade, alinhada ao compromisso da ES32Lab de fornecer ferramentas modernas, acessíveis e eficientes para desenvolvimento com ESP32.

### **Principais Recursos**
- **Streaming de Vídeo em Tempo Real**: Configure endpoints HTTP para transmitir vídeo diretamente do ESP32.
- **Ajustes Avançados do Sensor**: Controle brilho, contraste, saturação, exposição, efeitos especiais e muito mais.
- **Captura e Salvamento de Imagens**: Salve imagens em formatos JPEG diretamente em sistemas de arquivos como SPIFFS ou SD.
- **Flexibilidade e Desempenho**: Suporte a diferentes tamanhos de quadro, formatos de pixel e configurações de qualidade JPEG.
- **Fácil Integração**: Interface intuitiva para iniciantes e recursos avançados para desenvolvedores experientes.


---


## Índice

1. [Construtor](#construtor)
2. [Configuração no setup()](#configuração-no-setup)
3. [Configuração de Brilho](#configuração-de-brilho)
    - [`setBrightness(int8_t level)`](#setbrightnessint8_t-level)
    - [`getBrightness()`](#getbrightness)
4. [Configuração de Contraste](#configuração-de-contraste)
    - [`setContrast(int8_t level)`](#setcontrastint8_t-level)
    - [`getContrast()`](#getcontrast)
5. [Configuração de Saturação](#configuração-de-saturação)
    - [`setSaturation(int8_t level)`](#setsaturationint8_t-level)
    - [`getSaturation()`](#getsaturation)
6. [Balanço de Branco](#balanço-de-branco)
    - [`setWhiteBalance(bool enable)`](#setwhitebalancebool-enable)
    - [`getWhiteBalance()`](#getwhitebalance)
    - [`setWhiteBalanceGain(bool enable)`](#setwhitebalancegainbool-enable)
    - [`getWhiteBalanceGain()`](#getwhitebalancegain)
7. [Controle de Exposição](#controle-de-exposição)
    - [`setExposure(bool enable)`](#setexposurebool-enable)
    - [`getExposure()`](#getexposure)
    - [`setExposureAdvanced(bool enable)`](#setexposureadvancedbool-enable)
    - [`getExposureAdvanced()`](#getexposureadvanced)
    - [`setExposureLevel(int8_t level)`](#setexposurelevelint8_t-level)
    - [`getExposureLevel()`](#getexposurelevel)
    - [`setExposureValue(uint16_t value)`](#setexposurevalueuint16_t-value)
    - [`getExposureValue()`](#getexposurevalue)
    - [`setExposureGain(uint8_t gain)`](#setexposuregainuint8_t-gain)
    - [`getExposureGain()`](#getexposuregain)
8. [Efeitos Especiais](#efeitos-especiais)
    - [`setSpecialEffect(uint8_t effect)`](#setspecialeffectuint8_t-effect)
    - [`getSpecialEffect()`](#getspecialeffect)
9. [Correção de Lente e Cor](#correção-de-lente-e-cor)
    - [`setLensCorrection(bool enable)`](#setlenscorrectionbool-enable)
    - [`getLensCorrection()`](#getlenscorrection)
    - [`setColorCorrection(bool enable)`](#setcolorcorrectionbool-enable)
    - [`getColorCorrection()`](#getcolorcorrection)
10. [Correção de Cor RAW](#correção-de-cor-raw)
    - [`setRawColorCorrection(bool enable)`](#setrawcolorcorrectionbool-enable)
    - [`getRawColorCorrection()`](#getrawcolorcorrection)
11. [Nitidez](#nitidez)
    - [`setSharpness(int8_t level)`](#setsharpnessint8_t-level)
    - [`getSharpness()`](#getsharpness)
12. [Espelhamento](#espelhamento)
    - [`setHorizontalMirror(bool enable)`](#sethorizontalmirrorbool-enable)
    - [`getHorizontalMirror()`](#gethorizontalmirror)
    - [`setVerticalMirror(bool enable)`](#setverticalmirrorbool-enable)
    - [`getVerticalMirror()`](#getverticalmirror)
13. [Barra de Cores](#barra-de-cores)
    - [`setColorBar(bool enable)`](#setcolorbarbool-enable)
    - [`getColorBar()`](#getcolorbar)
14. [Tamanho do Quadro](#tamanho-do-quadro)
    - [`setFrameSize(framesize_t frameSize)`](#setframesizeframesize_t-framesize)
    - [`getFrameSize()`](#getframesize)
    - [`getFrameWidth()`](#getframewidth)
    - [`getFrameHeight()`](#getframeheight)    
15. [Configuração de Compressão JPEG](#configuração-de-compressão-jpeg)
    - [`setJpegCompression(int8_t jpegQuality)`](#setjpegcompressionint8_t-jpegquality)
    - [`getJpegCompression()`](#getjpegcompression)
16. [Captura de Frame no Formato Nativo](#captura-de-frame-no-formato-nativo)
    - [`getFrameBuffer(uint8_t** buf, size_t* bufLen)`](#getframebufferuint8_t-buf-size_t-buflen)
17. [Captura de Frame no Formato JPEG](#captura-de-frame-no-formato-jpeg)
    - [`getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen, framesize_t frameSize, int8_t jpegQuality)`](#getframejpegbufferuint8_t-jpegbuf-size_t-jpegbuflen-framesize_t-framesize-int8_t-jpegquality)
18. [Salvamento de Frame no Formato JPEG](#salvamento-de-frame-no-formato-jpeg)
    - [`saveFrameToJpegFile(fs::FS &fs, const char* filePath, framesize_t frameSize, int8_t jpegQuality)`](#saveframetojpegfilefsfs-const-char-filepath-framesize_t-framesize-int8_t-jpegquality)
19. [Métodos de Streaming](#métodos-de-streaming)
    - [`handleStreamRequest(httpd_req_t *req)`](#handlestreamrequesthttpd_req_t-req)
    - [`createStreamEndpoint(const char* streamUri)`](#createstreamendpointconst-char-streamuri)
    - [`getStreamUri()`](#getstreamuri)
20. [Exemplo: Configuração de Streaming de Vídeo](#exemplo-configuração-de-streaming-de-vídeo)
21. [Exemplos Oficiais](#exemplos-oficiais)


---


## Construtor

### `ES_Camera()`

O construtor `ES_Camera` é utilizado para inicializar uma nova instância da classe, configurando os pinos e parâmetros padrão necessários para o funcionamento da câmera. Ele é essencial para estabelecer a conexão entre o ESP32 e o módulo de câmera, garantindo que o hardware da ES32Lab esteja corretamente configurado.


---


## Configuração no `setup()`

O método `begin()` é essencial para inicializar a câmera com os parâmetros desejados. Ele deve ser chamado dentro da função `setup()` para garantir que a câmera esteja pronta para capturar imagens ou realizar streaming. A configuração correta dos parâmetros é fundamental para otimizar o desempenho e evitar problemas como reinicializações inesperadas do ESP32.

### `begin()`

Inicializa a câmera com os parâmetros especificados, permitindo configurar aspectos como tamanho do quadro, qualidade JPEG, formato de pixel, modo de captura, localização do buffer de quadros, número de buffers e frequência do sinal XCLK. Esses parâmetros são cruciais para ajustar o desempenho, a qualidade da imagem e a compatibilidade com os requisitos do projeto.

#### Sintaxe:
```cpp
bool begin(framesize_t frameSize, uint8_t jpegQuality, framesize_t maxFrameSize, pixformat_t pixelFormat, camera_grab_mode_t grabMode, camera_fb_location_t fbLocation, int fbCount, int xclkFreqHz);
```

#### Parâmetros:
- **`frameSize`**: Define o tamanho do quadro capturado pela câmera. Este parâmetro determina a resolução da imagem ou vídeo. Os valores disponíveis são:
  - `FRAMESIZE_96X96`: 96x96 pixels.
  - `FRAMESIZE_QQVGA`: 160x120 pixels.
  - `FRAMESIZE_HQVGA`: 240x176 pixels.
  - `FRAMESIZE_240X240`: 240x240 pixels.
  - `FRAMESIZE_QVGA`: 320x240 pixels.
  - `FRAMESIZE_CIF`: 400x296 pixels.
  - `FRAMESIZE_HVGA`: 480x320 pixels.
  - `FRAMESIZE_VGA`: 640x480 pixels.
  - `FRAMESIZE_SVGA`: 800x600 pixels.
  - `FRAMESIZE_XGA`: 1024x768 pixels.
  - `FRAMESIZE_HD`: 1280x720 pixels.
  - `FRAMESIZE_P_HD`: 720x1280 pixels.
  - `FRAMESIZE_SXGA`: 1280x1024 pixels.
  - `FRAMESIZE_UXGA`: 1600x1200 pixels.
  - `FRAMESIZE_FHD`: 1920x1080 pixels.
  - `FRAMESIZE_P_3MP`: 864x1536 pixels.
  - `FRAMESIZE_QXGA`: 2048x1536 pixels.
  - `FRAMESIZE_WQXGA`: 2560x1600 pixels.
  - `FRAMESIZE_QSXGA`: 2560x2048 pixels.

  **Dica de otimização:** Escolha a menor resolução que atenda às necessidades do seu projeto para economizar memória e melhorar o desempenho.

- **`jpegQuality`**: Define a qualidade da compressão JPEG. Os valores variam de 0 a 63:
  - **0-10**: Alta qualidade (maior tamanho de arquivo).
  - **11-20**: Qualidade média.
  - **21-63**: Baixa qualidade (menor tamanho de arquivo).
  
  **Dica de otimização:** Para streaming em tempo real, considere usar uma qualidade média para equilibrar desempenho e qualidade visual.

- **`maxFrameSize`**: Estabelece a resolução máxima que a câmera pode usar. Este parâmetro é importante para reservar a quantidade de memória necessária para ajustes de resolução em tempo de execução.
  - **Nota:** Se a aplicação não exigir altas resoluções ou se o ESP32 estiver reiniciando devido a instabilidades, ajuste este parâmetro para um valor menor, como `FRAMESIZE_QVGA` ou `FRAMESIZE_VGA`.

- **`pixelFormat`**: Define o formato de pixel da imagem capturada. Escolher o formato correto é importante, pois há um equilíbrio entre o uso de memória e a qualidade da imagem. Formatos como `PIXFORMAT_JPEG` economizam memória e são ideais para armazenamento e streaming, enquanto formatos como `PIXFORMAT_RGB565` ou `PIXFORMAT_GRAYSCALE` oferecem maior qualidade para processamento de imagem. Os valores suportados incluem:
  - `PIXFORMAT_JPEG` **(Default)**: Formato JPEG (ideal para streaming e armazenamento).
  - `PIXFORMAT_RGB565`: Formato RGB565 (ideal para processamento de imagem).
  - `PIXFORMAT_YUV422`: Formato YUV422.
  - `PIXFORMAT_GRAYSCALE`: Formato em escala de cinza.
  - `PIXFORMAT_RGB888`: Formato RGB888.
  - `PIXFORMAT_RAW`: Formato RAW.
  - `PIXFORMAT_RGB444`: Formato RGB444.
  - `PIXFORMAT_RGB555`: Formato RGB555.
  
  **Dica de otimização:** Use `PIXFORMAT_JPEG` para economizar memória ao capturar imagens.  
  **Nota:** Este formato não é adequado para processamento de imagem em tempo real devido à sobrecarga de compressão.

- **`grabMode`**: Especifica o modo de captura de quadros:
  - `CAMERA_GRAB_WHEN_EMPTY` **(Default)**: Aguarda até que o buffer esteja vazio antes de capturar um novo quadro, garantindo que nenhum quadro seja descartado, sendo mais adequado para aplicações que priorizam a integridade dos dados capturados, como análise de imagem ou fotografia.
  - `CAMERA_GRAB_LATEST`: Captura o quadro mais recente disponível no buffer, ideal para aplicações que exigem alta taxa de quadros, como streaming de vídeo em tempo real, mas pode resultar em perda de quadros se o processamento for mais lento que a captura.

- **`fbLocation`**: Define onde o buffer de quadros será armazenado:
  - `CAMERA_FB_IN_DRAM` **(Default)**: Usa a DRAM para armazenar os quadros (recomendado para resoluções baixas).  
    **Exemplo:** Adequado para capturas de baixa resolução, como `FRAMESIZE_QVGA`, em dispositivos com memória limitada.
  - `CAMERA_FB_IN_PSRAM`: Usa a PSRAM para armazenar os quadros (recomendado para resoluções altas).  
    **Exemplo:** Ideal para streaming de vídeo em alta resolução, como `FRAMESIZE_HD` ou superior, onde o uso de memória é maior.
  

- **`fbCount`** **(Default = 1)**: Número de buffers de quadros a serem usados. Um valor maior pode melhorar o desempenho em aplicações de streaming, especialmente em cenários com alta taxa de quadros ou onde o processamento de cada quadro é demorado, pois permite que a câmera continue capturando enquanto os quadros anteriores são processados. No entanto, isso consome mais memória, o que pode ser uma limitação em dispositivos com recursos restritos. Para aplicações como streaming de vídeo em tempo real, recomenda-se usar pelo menos 2 buffers, enquanto para capturas de imagem estática, 1 buffer pode ser suficiente.

- **`xclkFreqHz`** **(Default = 20000000)**: Frequência do sinal XCLK em Hz. Valores comuns são 10 MHz, 20 MHz ou 40 MHz. Frequências mais altas podem melhorar a taxa de quadros, mas aumentam o consumo de energia e podem gerar mais calor, o que pode ser crítico em dispositivos alimentados por bateria. Por outro lado, frequências mais baixas reduzem o consumo de energia e a geração de calor, mas podem limitar a taxa de quadros, tornando-as mais adequadas para aplicações que priorizam eficiência energética.

#### Retorno:
- **`true`**: Se a câmera foi inicializada com sucesso.
- **`false`**: Caso contrário. Possíveis razões incluem:
  - Memória insuficiente para alocar buffers de quadros.
  - Frequência XCLK incompatível com o módulo da câmera.
  - Falha na comunicação com o sensor da câmera.
  - Configuração incorreta dos pinos da câmera, esse é o menos provável caso esteja utilizado uma ES32Lab e sua LIB de programação.

### Exemplo de Uso 1
Todos os parâmetros utilizados neste exemplo usarão seus valores padrão predefinidos
```cpp
if (!camera.begin()) {
    Serial.println("Falha ao inicializar a câmera!");
    while (true);
}
Serial.println("Câmera inicializada com sucesso!");
```

### Exemplo de Uso 2
Os parâmetros podem ser preenchidos parcialmente, desde que sejam preenchidos da esquerda para a direita, ou seja, os parâmetros mais à direita, se não preenchidos, receberão o valor padrão pré-definido.
```cpp
if (!camera.begin(FRAMESIZE_QVGA, 12)) {
    Serial.println("Falha ao inicializar a câmera!");
    while (true);
}
Serial.println("Câmera inicializada com sucesso!");
```

### Exemplo de Uso 3
Preenchimento manual de todos os parâmetros: todos os valores devem ser explicitamente fornecidos, seguindo a ordem definida na assinatura do método.
```cpp
if (!camera.begin(FRAMESIZE_QVGA, 12, FRAMESIZE_VGA, PIXFORMAT_JPEG, CAMERA_GRAB_LATEST, CAMERA_FB_IN_PSRAM, 2, 20000000)) {
    Serial.println("Falha ao inicializar a câmera!");
    while (true);
}
Serial.println("Câmera inicializada com sucesso!");
```


---


## Métodos da Classe

A classe `ES_Camera` oferece uma ampla gama de métodos para configurar e controlar o sensor da câmera, permitindo ajustes precisos para atender às necessidades específicas de cada aplicação. Abaixo estão descritos os métodos disponíveis, organizados por categoria, com detalhes sobre sua utilização.

### Configuração de Brilho
A configuração de brilho permite ajustar a luminosidade das imagens capturadas pela câmera, garantindo que elas sejam adequadas às condições de iluminação do ambiente. Este recurso é especialmente útil para evitar imagens muito escuras ou superexpostas, proporcionando maior qualidade visual. A classe `ES_Camera` oferece métodos para ajustar e monitorar o nível de brilho, permitindo flexibilidade para atender às necessidades específicas de cada aplicação.

#### `setBrightness(int8_t level)`
Ajusta o nível de brilho do sensor da câmera. Este método permite configurar o brilho da imagem capturada, sendo útil para adaptar a câmera a diferentes condições de iluminação.

- **Parâmetro**:
  - `level`: O nível de brilho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **-2** (brilho mínimo) a **2** (brilho máximo), onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o ajuste foi realizado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ajuste o brilho para evitar imagens muito escuras ou superexpostas, especialmente em ambientes com iluminação variável.


#### `getBrightness()`
Obtém o nível de brilho atual configurado no sensor da câmera. Este método é útil para verificar o valor atual antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o nível de brilho atual, variando de **-2** a **2**.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**: Use este método para monitorar o estado do brilho e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Configuração de Contraste
A configuração de contraste permite ajustar a diferença entre as áreas claras e escuras das imagens capturadas pela câmera, garantindo maior definição e qualidade visual. Este recurso é especialmente útil para aplicações que exigem imagens com maior clareza e detalhamento, como análise de imagem, fotografia ou streaming de vídeo. A classe `ES_Camera` oferece métodos para ajustar e monitorar o nível de contraste, proporcionando flexibilidade para atender a diferentes condições de iluminação e preferências visuais.

#### `setContrast(int8_t level)`
Ajusta o nível de contraste do sensor da câmera. Este método permite configurar o contraste da imagem capturada, sendo útil para melhorar a qualidade visual em diferentes condições de iluminação ou para atender a requisitos específicos de processamento de imagem.

- **Parâmetro**:
  - `level`: O nível de contraste a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **-2** (contraste mínimo) a **2** (contraste máximo), onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o ajuste foi realizado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**: Ajuste o contraste para evitar imagens muito lavadas (baixo contraste) ou com áreas excessivamente escuras e claras (alto contraste). Isso é especialmente importante em aplicações que envolvem análise de imagem.


#### `getContrast()`
Obtém o nível de contraste atual configurado no sensor da câmera. Este método é útil para verificar o valor atual antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o nível de contraste atual, variando de **-2** a **2**.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**: Use este método para monitorar o estado do contraste e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Configuração de Saturação
A configuração de saturação permite ajustar a intensidade das cores capturadas pela câmera, garantindo que as imagens sejam vibrantes ou neutras, dependendo das necessidades do projeto. Este recurso é especialmente útil para aplicações que exigem controle preciso da aparência visual, como fotografia, streaming de vídeo ou análise de imagem. A classe `ES_Camera` oferece métodos para ajustar e monitorar o nível de saturação, proporcionando flexibilidade para atender a diferentes condições de iluminação e preferências estéticas.

#### `setSaturation(int8_t level)`
Ajusta o nível de saturação do sensor da câmera. Este método permite configurar a intensidade das cores na imagem capturada, sendo útil para ajustar a aparência visual de acordo com as necessidades do projeto.

- **Parâmetro**:
  - `level`: O nível de saturação a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **-2** (saturação mínima) a **2** (saturação máxima), onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o ajuste foi realizado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Use níveis mais baixos de saturação para aplicações que exigem imagens neutras ou em tons de cinza.
  - Níveis mais altos podem ser úteis para destacar cores em ambientes com iluminação fraca ou para aplicações visuais mais vibrantes.


#### `getSaturation()`
Obtém o nível de saturação atual configurado no sensor da câmera. Este método é útil para verificar o valor atual antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o nível de saturação atual, variando de **-2** a **2**.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado da saturação e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Balanço de Branco
O balanço de branco é uma funcionalidade essencial para ajustar a tonalidade das cores capturadas pela câmera, garantindo que elas sejam representadas de forma precisa e natural, independentemente das condições de iluminação. Com o balanço de branco, é possível compensar diferentes tipos de luz, como luz natural, fluorescente ou incandescente, evitando que as imagens fiquem com tons indesejados, como azulados ou amarelados. A classe `ES_Camera` oferece métodos para ativar ou desativar o balanço de branco automático, ajustar o ganho do balanço de branco e monitorar o status dessas configurações, proporcionando flexibilidade para atender às necessidades específicas de cada aplicação.

#### `setWhiteBalance(bool enable)`
Ativa ou desativa o balanço de branco automático. Este método ajusta automaticamente a tonalidade das cores capturadas pela câmera para compensar diferentes condições de iluminação, como luz natural, fluorescente ou incandescente.

- **Parâmetro**:
  - `enable`: Define se o balanço de branco automático será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o balanço de branco foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o balanço de branco automático para aplicações em ambientes com iluminação variável.
  - Desative-o em cenários onde a iluminação é constante e você deseja manter um controle manual das cores.


#### `getWhiteBalance()`
Obtém o status atual do balanço de branco automático. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o balanço de branco automático estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado do balanço de branco antes de realizar ajustes adicionais.


#### `setWhiteBalanceGain(bool enable)`
Ativa ou desativa o ganho do balanço de branco. Este recurso ajusta automaticamente a intensidade do ganho aplicado ao balanço de branco, melhorando a precisão das cores em condições de iluminação desafiadoras.

- **Parâmetro**:
  - `enable`: Define se o ganho do balanço de branco será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o ganho do balanço de branco foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o ganho do balanço de branco para melhorar a precisão das cores em ambientes com iluminação mista ou de baixa qualidade.
  - Desative-o para economizar recursos de processamento em aplicações que não exigem alta fidelidade de cores.


#### `getWhiteBalanceGain()`
Obtém o status atual do ganho do balanço de branco. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o ganho do balanço de branco estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para confirmar o estado do ganho do balanço de branco antes de realizar ajustes adicionais.


---


### Controle de Exposição
O controle de exposição permite ajustar automaticamente ou manualmente a quantidade de luz capturada pelo sensor da câmera, garantindo imagens equilibradas em diferentes condições de iluminação. Com ele, é possível evitar fotos muito escuras ou superexpostas, adaptando a câmera a ambientes internos, externos ou com iluminação variável. A classe `ES_Camera` oferece métodos para ativar ou desativar o controle automático, ajustar níveis de exposição e configurar parâmetros avançados, como ganho e tempo de exposição, proporcionando flexibilidade para atender às necessidades específicas de cada aplicação.

#### `setExposure(bool enable)`
Ativa ou desativa o controle automático de exposição. Este método ajusta automaticamente a exposição da câmera para compensar diferentes condições de iluminação, garantindo que as imagens capturadas não fiquem muito escuras ou superexpostas.

- **Parâmetro**:
  - `enable`: Define se o controle automático de exposição será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o controle de exposição foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o controle automático de exposição para aplicações em ambientes com iluminação variável.
  - Desative-o em cenários onde a iluminação é constante e você deseja manter um controle manual da exposição.

- **Nota**:
  - Este método é útil para capturar imagens em condições de iluminação desafiadoras, como ambientes externos ou com luzes intermitentes.


#### `getExposure()`
Obtém o status atual do controle automático de exposição. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o controle automático de exposição estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado do controle de exposição antes de realizar ajustes adicionais.

#### `setExposureAdvanced(bool enable)`
Ativa ou desativa o controle avançado de exposição. Este método permite um ajuste mais refinado da exposição, ideal para cenários onde o controle automático padrão não é suficiente para atender às necessidades específicas de iluminação.

- **Parâmetro**:
  - `enable`: Define se o controle avançado de exposição será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o controle avançado de exposição foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o controle avançado de exposição para capturar imagens em ambientes com iluminação complexa ou de baixa qualidade.
  - Desative-o para economizar recursos de processamento em aplicações que não exigem ajustes avançados.


#### `getExposureAdvanced()`
Obtém o status atual do controle avançado de exposição. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o controle avançado de exposição estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado do controle avançado de exposição antes de realizar ajustes adicionais.


#### `setExposureLevel(int8_t level)`
Ajusta o nível de controle de exposição. Este método permite configurar manualmente o nível de exposição, oferecendo maior controle sobre a quantidade de luz capturada pela câmera.

- **Parâmetro**:
  - `level`: O nível de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **-2** (exposição mínima) a **2** (exposição máxima), onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o nível de exposição foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ajuste o nível de exposição para evitar imagens muito escuras ou superexpostas, especialmente em ambientes com iluminação variável.

#### `getExposureLevel()`
Obtém o nível de controle de exposição atual. Este método é útil para verificar o valor configurado antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o nível de exposição atual, variando de **-2** a **2**.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado do nível de exposição e garantir que os ajustes realizados estejam de acordo com as expectativas.

#### `setExposureValue(uint16_t value)`
Ajusta o valor de controle de exposição. Este método permite configurar manualmente o tempo de exposição da câmera, ajustando a quantidade de luz capturada pelo sensor.

- **Parâmetro**:
  - `value`: O valor de controle de exposição a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **0** a **1000**, onde **300** é o padrão.

- **Retorno**:
  - Retorna `true` se o valor de controle de exposição foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.

- **Dica de otimização**:
  - Use valores mais baixos para reduzir a exposição em ambientes muito iluminados.
  - Use valores mais altos para aumentar a exposição em condições de pouca luz.


#### `getExposureValue()`
Obtém o valor de controle de exposição atual. Este método é útil para verificar o valor configurado antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o valor de controle de exposição atual.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado do controle de exposição e garantir que os ajustes realizados estejam de acordo com as expectativas.


#### `setExposureGain(uint8_t gain)`
Ajusta o ganho relacionado à exposição. Este método controla a amplificação do sinal do sensor, permitindo melhorar a captura de imagens em condições de baixa luz.

- **Parâmetro**:
  - `gain`: O valor de ganho a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **0** a **30**, onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o ganho foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.

- **Dica de otimização**:
  - Use valores mais baixos para reduzir o ruído em ambientes bem iluminados.
  - Use valores mais altos para melhorar a visibilidade em condições de pouca luz.


#### `getExposureGain()`
Obtém o ganho relacionado à exposição atual. Este método é útil para verificar o valor configurado antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o ganho atual.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado do ganho de exposição e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Efeitos Especiais
A configuração de efeitos especiais permite aplicar filtros visuais diretamente no sensor da câmera, alterando a aparência das imagens capturadas sem a necessidade de processamento adicional no software. Esses efeitos podem ser usados para criar imagens estilizadas, destacar características específicas ou atender a requisitos visuais de diferentes aplicações. A classe `ES_Camera` oferece métodos para ajustar e monitorar os efeitos especiais, proporcionando flexibilidade e criatividade para projetos que envolvem captura de imagens ou vídeos.


#### `setSpecialEffect(uint8_t effect)`
Ajusta o efeito especial do sensor da câmera. Este método permite aplicar filtros visuais diretamente no hardware do sensor, alterando a aparência das imagens capturadas.

- **Parâmetro**:
  - `effect`: O efeito especial a ser ajustado. Os valores aceitos são:
    - **0**: Nenhum efeito (padrão).
    - **1**: Negativo.
    - **2**: Preto e branco.
    - **3**: Tons de azul.
    - **4**: Tons de vermelho.
    - **5**: Tons de verde.
    - **6**: Sépia.

- **Retorno**:
  - Retorna `true` se o efeito especial foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Use efeitos especiais para criar imagens estilizadas diretamente no sensor, reduzindo a necessidade de processamento adicional no software.


#### `getSpecialEffect()`
Obtém o efeito especial atual configurado no sensor da câmera. Este método é útil para verificar qual filtro está ativo antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o efeito especial atual, conforme a tabela de valores do método `setSpecialEffect`.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado do efeito especial e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Correção de Lente e Cor
A funcionalidade de correção de lente e cor permite ajustar automaticamente distorções geométricas e desvios de tonalidade nas imagens capturadas pela câmera. A correção de lente elimina distorções causadas pela curvatura da lente, garantindo imagens mais proporcionais e precisas, enquanto a correção de cor ajusta as tonalidades para maior fidelidade e precisão. Essas funcionalidades são especialmente úteis em aplicações que exigem alta qualidade de imagem, como visão computacional, análise de imagem e fotografia. A classe `ES_Camera` oferece métodos para ativar, desativar e monitorar essas correções, proporcionando flexibilidade para atender às necessidades específicas de cada projeto.


#### `setLensCorrection(bool enable)`
Ativa ou desativa a correção de lente. Este método ajusta automaticamente as distorções geométricas causadas pela lente da câmera, garantindo que as imagens capturadas sejam mais precisas e proporcionais.

- **Parâmetro**:
  - `enable`: Define se a correção de lente será ativada (`true`) ou desativada (`false`).

- **Retorno**:
  - Retorna `true` se a correção de lente foi ajustada com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative a correção de lente para aplicações que exigem alta precisão geométrica, como visão computacional ou análise de imagem.
  - Desative-a em cenários onde a distorção da lente não afeta o desempenho ou quando o processamento precisa ser otimizado.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.


#### `getLensCorrection()`
Obtém o status atual da correção de lente. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se a correção de lente estiver ativada.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado da correção de lente antes de realizar ajustes adicionais.


#### `setColorCorrection(bool enable)`
Ativa ou desativa a correção de cor. Este método ajusta automaticamente as cores capturadas pela câmera para garantir maior precisão e fidelidade, corrigindo possíveis desvios de tonalidade.

- **Parâmetro**:
  - `enable`: Define se a correção de cor será ativada (`true`) ou desativada (`false`).

- **Retorno**:
  - Retorna `true` se a correção de cor foi ajustada com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative a correção de cor para aplicações que exigem alta precisão de cores, como fotografia ou análise de imagem.
  - Desative-a em cenários onde a fidelidade de cor não é crítica para economizar recursos de processamento.


#### `getColorCorrection()`
Obtém o status atual da correção de cor. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se a correção de cor estiver ativada.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado da correção de cor antes de realizar ajustes adicionais.


### Correção de Cor RAW

#### `setRawColorCorrection(bool enable)`
Ativa ou desativa a correção de cor RAW. Este método ajusta as cores diretamente no formato RAW, permitindo maior controle sobre a tonalidade e a qualidade da imagem capturada.

- **Parâmetro**:
  - `enable`: Define se a correção de cor RAW será ativada (`true`) ou desativada (`false`).

- **Retorno**:
  - Retorna `true` se a correção de cor RAW foi ajustada com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative a correção de cor RAW para aplicações que exigem processamento avançado de imagem ou alta fidelidade de cores.
  - Desative-a em cenários onde o processamento de cor RAW não é necessário para economizar recursos.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.


#### `getRawColorCorrection()`
Obtém o status atual da correção de cor RAW. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se a correção de cor RAW estiver ativada.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado da correção de cor RAW antes de realizar ajustes adicionais.


---


### Nitidez
A configuração de nitidez permite ajustar o nível de clareza e definição das imagens capturadas pela câmera. Este recurso é especialmente útil para destacar detalhes em ambientes bem iluminados ou reduzir ruídos em condições de baixa luz. A classe `ES_Camera` oferece métodos para ajustar e monitorar o nível de nitidez, proporcionando flexibilidade para atender às necessidades específicas de cada aplicação, como fotografia, análise de imagem ou streaming de vídeo.

#### `setSharpness(int8_t level)`
Ajusta o nível de nitidez do sensor da câmera. Este método permite controlar a clareza e os detalhes das imagens capturadas, ajustando a intensidade do processamento de nitidez aplicado pelo sensor.

- **Parâmetro**:
  - `level`: O nível de nitidez a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de **-2** (nitidez mínima) a **2** (nitidez máxima), onde **0** é o padrão.

- **Retorno**:
  - Retorna `true` se o nível de nitidez foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Use níveis mais baixos para reduzir ruídos em imagens capturadas em ambientes com pouca luz.
  - Use níveis mais altos para destacar detalhes em imagens capturadas em ambientes bem iluminados.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.

#### `getSharpness()`
Obtém o nível de nitidez atual configurado no sensor da câmera. Este método é útil para verificar o valor atual antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando o nível de nitidez atual, variando de **-2** a **2**.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado da nitidez e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Espelhamento
A funcionalidade de espelhamento permite inverter as imagens capturadas pela câmera, tanto horizontalmente quanto verticalmente. Este recurso é útil para aplicações que exigem ajustes na orientação da imagem, como sistemas de visão traseira, interfaces de usuário específicas ou cenários onde o alinhamento padrão da câmera não atende aos requisitos do projeto. A classe `ES_Camera` oferece métodos para ativar, desativar e monitorar o status do espelhamento horizontal e vertical, proporcionando flexibilidade para atender às necessidades específicas de cada aplicação.


#### `setHorizontalMirror(bool enable)`
Ativa ou desativa o espelhamento horizontal do sensor da câmera. Este recurso inverte horizontalmente a imagem capturada, criando um efeito de espelho.

- **Parâmetro**:
  - `enable`: Define se o espelhamento horizontal será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o espelhamento horizontal foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o espelhamento horizontal para aplicações que exigem imagens invertidas, como sistemas de visão traseira ou interfaces de usuário específicas.
  - Desative-o para capturar imagens no formato padrão.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.

#### `getHorizontalMirror()`
Obtém o status atual do espelhamento horizontal do sensor da câmera. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o espelhamento horizontal estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado do espelhamento horizontal antes de realizar ajustes adicionais.


#### `setVerticalMirror(bool enable)`
Ativa ou desativa o espelhamento vertical do sensor da câmera. Este recurso inverte verticalmente a imagem capturada, criando um efeito de rotação vertical.

- **Parâmetro**:
  - `enable`: Define se o espelhamento vertical será ativado (`true`) ou desativado (`false`).

- **Retorno**:
  - Retorna `true` se o espelhamento vertical foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative o espelhamento vertical para aplicações que exigem imagens invertidas, como sistemas de visão reversa ou interfaces específicas.
  - Desative-o para capturar imagens no formato padrão.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.


#### `getVerticalMirror()`
Obtém o status atual do espelhamento vertical do sensor da câmera. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se o espelhamento vertical estiver ativado.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado do espelhamento vertical antes de realizar ajustes adicionais.


---


### Barra de Cores
A funcionalidade de barra de cores permite exibir uma sequência padrão de cores na saída da câmera, sendo especialmente útil para testes, calibração e verificação da integridade do sensor. Este recurso é amplamente utilizado em aplicações de diagnóstico e desenvolvimento, garantindo que o sensor esteja funcionando corretamente antes de capturar imagens ou vídeos reais. A classe `ES_Camera` oferece métodos para ativar, desativar e monitorar o status da barra de cores, proporcionando uma ferramenta prática para validação de hardware.

#### `setColorBar(bool enable)`
Ativa ou desativa a barra de cores no sensor da câmera. Este recurso exibe uma barra de cores padrão na saída da câmera, útil para testes e calibração.

- **Parâmetro**:
  - `enable`: Define se a barra de cores será ativada (`true`) ou desativada (`false`).

- **Retorno**:
  - Retorna `true` se a barra de cores foi ajustada com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Ative a barra de cores para verificar a integridade do sensor e realizar testes de calibração.
  - Desative-a para capturar imagens normais.

- **Nota**:
  - Nem todos os sensores suportam este recurso. Verifique a compatibilidade antes de utilizá-lo.


#### `getColorBar()`
Obtém o status atual da barra de cores no sensor da câmera. Este método é útil para verificar se o recurso está ativado ou desativado.

- **Retorno**:
  - Retorna `true` se a barra de cores estiver ativada.
  - Retorna `false` caso contrário.

- **Nota**:
  - Use este método para monitorar o estado da barra de cores antes de realizar ajustes adicionais.


---


### Tamanho do Quadro
A configuração do tamanho do quadro permite ajustar a resolução das imagens capturadas pela câmera, adaptando-as às necessidades específicas do projeto. Este recurso é essencial para equilibrar qualidade de imagem, desempenho e uso de memória. A classe `ES_Camera` oferece métodos para definir e monitorar o tamanho do quadro, proporcionando flexibilidade para aplicações que variam de streaming de vídeo em alta resolução a capturas de imagens em baixa resolução para economizar recursos.

Com suporte a uma ampla gama de resoluções, como `FRAMESIZE_QVGA` (320x240 pixels) e `FRAMESIZE_HD` (1280x720 pixels), a configuração do tamanho do quadro é ideal para atender a diferentes requisitos de qualidade e desempenho.

- **Dica de otimização**:
  - Escolha o menor tamanho de quadro que atenda às necessidades do projeto para economizar memória e melhorar o desempenho.
  - Certifique-se de que o tamanho do quadro não exceda o valor máximo configurado no parâmetro `maxFrameSize`.


#### `setFrameSize(framesize_t frameSize)`
Ajusta o tamanho do quadro capturado pelo sensor da câmera. Este método permite configurar a resolução da imagem, adaptando-a às necessidades do projeto.

- **Parâmetro**:
  - `frameSize`: O tamanho do quadro a ser ajustado. Exemplos de valores:
    - `FRAMESIZE_96X96`: 96x96 pixels.
    - `FRAMESIZE_QQVGA`: 160x120 pixels.
    - `FRAMESIZE_HQVGA`: 240x176 pixels.
    - `FRAMESIZE_240X240`: 240x240 pixels.
    - `FRAMESIZE_QVGA`: 320x240 pixels.
    - `FRAMESIZE_CIF`: 400x296 pixels.
    - `FRAMESIZE_HVGA`: 480x320 pixels.
    - `FRAMESIZE_VGA`: 640x480 pixels.
    - `FRAMESIZE_SVGA`: 800x600 pixels.
    - `FRAMESIZE_XGA`: 1024x768 pixels.
    - `FRAMESIZE_HD`: 1280x720 pixels.
    - `FRAMESIZE_P_HD`: 720x1280 pixels.
    - `FRAMESIZE_SXGA`: 1280x1024 pixels.
    - `FRAMESIZE_UXGA`: 1600x1200 pixels.
    - `FRAMESIZE_FHD`: 1920x1080 pixels.
    - `FRAMESIZE_P_3MP`: 864x1536 pixels.
    - `FRAMESIZE_QXGA`: 2048x1536 pixels.
    - `FRAMESIZE_WQXGA`: 2560x1600 pixels.
    - `FRAMESIZE_QSXGA`: 2560x2048 pixels.

- **Retorno**:
  - Retorna `true` se o tamanho do quadro foi ajustado com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Escolha o menor tamanho de quadro que atenda às necessidades do projeto para economizar memória e melhorar o desempenho.
  - Certifique-se de que o tamanho do quadro não exceda o valor máximo configurado no parâmetro `maxFrameSize`.

- **Nota**:
  - Caso o valor fornecido seja inválido ou exceda o limite máximo, o método ajustará automaticamente para o menor ou maior valor permitido.


#### `getFrameSize()`
Obtém o tamanho do quadro atual configurado no sensor da câmera. Este método é útil para verificar a resolução antes de realizar novos ajustes.

- **Retorno**:
  - Retorna o tamanho do quadro atual como um valor do tipo `framesize_t`.
  - Retorna `FRAMESIZE_INVALID` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado do tamanho do quadro e garantir que os ajustes realizados estejam de acordo com as expectativas.


#### `getFrameWidth()`
Obtém a largura (em pixels) do quadro atual configurado na câmera. Este método é útil para saber a resolução horizontal da imagem capturada, especialmente ao trabalhar com diferentes tamanhos de quadro.

- **Retorno**:
  - Retorna um valor inteiro representando a largura do quadro atual em pixels.
  - Retorna `0` caso ocorra algum erro ou se o tamanho do quadro não for reconhecido.

- **Nota**:
  - Use este método para ajustar operações de processamento de imagem, exibição em display ou salvamento de arquivos, garantindo que a largura utilizada corresponde à configuração atual da câmera.


#### `getFrameHeight()`
Obtém a altura (em pixels) do quadro atual configurado na câmera. Este método é útil para saber a resolução vertical da imagem capturada, especialmente ao trabalhar com diferentes tamanhos de quadro.

- **Retorno**:
  - Retorna um valor inteiro representando a altura do quadro atual em pixels.
  - Retorna `0` caso ocorra algum erro ou se o tamanho do quadro não for reconhecido.

- **Nota**:
  - Use este método para ajustar operações de processamento de imagem, exibição em display ou salvamento de arquivos, garantindo que a altura utilizada corresponde à configuração atual da câmera.


---


### Configuração de Compressão JPEG

A configuração de compressão JPEG permite ajustar o nível de compressão das imagens capturadas pela câmera, equilibrando qualidade visual e tamanho do arquivo. Este recurso é essencial para aplicações que exigem armazenamento eficiente, transmissão em tempo real ou alta qualidade de imagem. A classe `ES_Camera` oferece métodos para definir e monitorar a qualidade de compressão JPEG, proporcionando flexibilidade para atender às necessidades específicas de cada projeto.


#### `setJpegCompression(int8_t jpegQuality)`
Ajusta a qualidade de compressão JPEG do sensor da câmera. Este método permite configurar o nível de compressão das imagens capturadas, equilibrando qualidade visual e tamanho do arquivo.

- **Parâmetro**:
  - `jpegQuality`: O nível de qualidade de compressão JPEG a ser ajustado. Geralmente, a escala aceita valores inteiros que variam de:
    - **0-10**: Alta qualidade (maior tamanho de arquivo).
    - **11-20**: Qualidade média.
    - **21-63**: Baixa qualidade (menor tamanho de arquivo).

- **Retorno**:
  - Retorna `true` se a qualidade de compressão JPEG foi ajustada com sucesso.
  - Retorna `false` caso contrário.

- **Dica de otimização**:
  - Use valores mais baixos para reduzir o tamanho do arquivo em aplicações que exigem armazenamento eficiente ou transmissão em tempo real.
  - Use valores mais altos para capturar imagens com maior qualidade visual em aplicações que priorizam detalhes.

- **Nota**:
  - Nem todos os sensores suportam a configuração de compressão JPEG. Verifique a compatibilidade antes de utilizá-lo.


#### `getJpegCompression()`
Obtém a qualidade de compressão JPEG atual configurada no sensor da câmera. Este método é útil para verificar o valor antes de realizar novos ajustes.

- **Retorno**:
  - Retorna um valor inteiro representando a qualidade de compressão JPEG atual.
  - Retorna `0` caso ocorra algum erro ao acessar o sensor.

- **Nota**:
  - Use este método para monitorar o estado da compressão JPEG e garantir que os ajustes realizados estejam de acordo com as expectativas.


---


### Captura de Frame no Formato Nativo

Este método captura um frame no formato nativo configurado na câmera (por exemplo, RGB565, GRAYSCALE ou JPEG) e armazena os dados em um buffer fornecido pelo usuário. Ele é útil para aplicações que precisam processar, exibir ou manipular imagens diretamente no formato original capturado pelo sensor, sem conversão para JPEG.

#### `getFrameBuffer(uint8_t** buf, size_t* bufLen)`
Captura um frame no formato nativo atual da câmera, armazenando os dados em um buffer fornecido pelo usuário. Este método é ideal para aplicações que exigem acesso rápido ao frame para exibição em displays TFT, processamento de imagem ou integração com outros periféricos.

- **Parâmetros**:
  - `buf`: Ponteiro para o buffer onde os dados do frame capturado serão armazenados.
  - `bufLen`: Ponteiro para a variável onde o tamanho dos dados do frame será armazenado.

- **Retorno**:
  - Retorna `true` se o frame foi capturado com sucesso.
  - Retorna `false` caso contrário.

- **Funcionamento**:
  - O método captura o frame diretamente no formato configurado em `begin()` (ex: RGB565, GRAYSCALE ou JPEG).
  - Não realiza conversão de formato, garantindo máxima performance e menor uso de memória.
  - O buffer retornado deve ser utilizado imediatamente, pois pertence ao driver da câmera e será liberado após o uso.

- **Dica de otimização**:
  - Utilize este método para exibir imagens em displays TFT, onde o formato RGB565 é o mais eficiente.
  - Para salvar ou transmitir imagens em JPEG, utilize o método `getFrameJpegBuffer()`.

- **Nota**:
  - O conteúdo e o tamanho do buffer dependem do formato configurado na inicialização da câmera.
  - Não é necessário liberar o buffer manualmente, pois ele é gerenciado pelo driver da câmera.
  - Caso precise de JPEG, utilize o método `getFrameJpegBuffer()`.

> **Atenção:**  
> Se você precisa de imagens em JPEG para armazenamento ou transmissão, prefira inicializar a câmera diretamente em `PIXFORMAT_JPEG` usando o método `begin()`, ou utilize o método `getFrameJpegBuffer()` para realizar a conversão (sujeito à disponibilidade de memória RAM).

#### Exemplo de Uso: Captura de Frame no Formato Nativo
```cpp
uint8_t* buf = nullptr;
size_t bufLen = 0;

if (camera.getFrameBuffer(&buf, &bufLen)) {
    // Processa ou exibe o buffer capturado (ex: display TFT)
    Serial.printf("Frame capturado com sucesso! Tamanho: %zu bytesXn", bufLen);
    // Não é necessário liberar o buffer manualmente
} else {
    Serial.println("Falha ao capturar o frame.");
}
```

---


### Captura de Frame no Formato JPEG
Este método captura um frame no formato JPEG e armazena os dados em um buffer fornecido pelo usuário. Ele é útil para aplicações que precisam processar, salvar ou exibir imagens capturadas pela câmera.

#### `getFrameJpegBuffer(uint8_t** jpegBuf, size_t* jpegBufLen, framesize_t frameSize, int8_t jpegQuality)`
Captura um frame no formato JPEG com o tamanho de quadro e a qualidade de compressão especificados, armazenando os dados em um buffer fornecido pelo usuário. Este método é ideal para aplicações que exigem controle detalhado sobre a resolução e a qualidade da imagem capturada, como streaming de vídeo, análise de imagem ou armazenamento local.

- **Parâmetros**:
  - `jpegBuf`: Ponteiro para o buffer onde os dados JPEG capturados serão armazenados.
  - `jpegBufLen`: Ponteiro para a variável onde o tamanho dos dados JPEG será armazenado.
  - `frameSize`: O tamanho do quadro a ser ajustado. Exemplos:
    - `FRAMESIZE_QVGA`: 320x240 pixels.
    - `FRAMESIZE_VGA`: 640x480 pixels.
    - `FRAMESIZE_HD`: 1280x720 pixels.
  - `jpegQuality`: A qualidade de compressão JPEG a ser ajustada. Escala:
    - **0-10**: Alta qualidade (maior tamanho de arquivo).
    - **11-20**: Qualidade média.
    - **21-63**: Baixa qualidade (menor tamanho de arquivo).

- **Retorno**:
  - Retorna `true` se o frame foi capturado com sucesso.
  - Retorna `false` caso contrário.

- **Funcionamento**:
  - O método ajusta o tamanho do quadro e a qualidade JPEG antes de capturar o frame.
  - Caso o frame não esteja no formato JPEG, ele será convertido usando o método `frame2jpg`.

- **Dica de otimização**:
  - Certifique-se de liberar a memória alocada para o buffer após o uso para evitar vazamentos de memória.
  - Use resoluções menores e compressão mais alta para economizar memória e largura de banda em aplicações de streaming.

- **Nota**:
  - Caso o ajuste do tamanho do quadro ou da qualidade JPEG falhe, o método retorna `false` e registra um erro no log.

> **Atenção:**  
> A conversão de frames de outros formatos (como RGB565) para JPEG pode falhar por falta de memória RAM no ESP32.  
> Para evitar esse problema, **inicialize a câmera diretamente em [PIXFORMAT_JPEG](http://_vscodecontentref_/2)** usando o método [begin()](http://_vscodecontentref_/3), por exemplo:
> ```cpp
> camera.begin(FRAMESIZE_QVGA, 12, FRAMESIZE_VGA, PIXFORMAT_JPEG);
> ```
> Isso garante que os frames já serão capturados em JPEG, economizando memória e evitando falhas na conversão ou no salvamento de imagens.

#### Exemplo de Uso 1: Captura de Frame com Configuração Padrão
```cpp
uint8_t* jpegBuf = nullptr;
size_t jpegBufLen = 0;

if (camera.getFrameJpegBuffer(&jpegBuf, &jpegBufLen)) {
    // Processa o buffer JPEG capturado
    Serial.printf("Frame capturado com sucesso! Tamanho: %zu bytes\n", jpegBufLen);
    free(jpegBuf); // Libera o buffer após o uso
} else {
    Serial.println("Falha ao capturar o frame.");
}
```


#### Exemplo de Uso 2: Captura de Frame com Configuração Personalizada
```cpp
uint8_t* jpegBuf = nullptr;
size_t jpegBufLen = 0;

if (camera.getFrameJpegBuffer(&jpegBuf, &jpegBufLen, FRAMESIZE_VGA, 10)) {
    // Processa o buffer JPEG capturado
    Serial.printf("Frame capturado com sucesso! Tamanho: %zu bytes\n", jpegBufLen);
    free(jpegBuf); // Libera o buffer após o uso
} else {
    Serial.println("Falha ao capturar o frame.");
}
```

### Salvamento de Frame no Formato JPEG

#### `saveFrameToJpegFile(fs::FS &fs, const char* filePath, framesize_t frameSize, int8_t jpegQuality)`
Este método captura um frame no formato JPEG com o tamanho de quadro e a qualidade de compressão especificados e salva diretamente em um arquivo no sistema de arquivos fornecido. Ele é ideal para aplicações que precisam armazenar imagens capturadas para análise posterior, arquivamento ou compartilhamento.

- **Parâmetros**:
  - `fs`: Referência ao sistema de arquivos onde o arquivo será salvo (por exemplo, SPIFFS ou SD).
  - `filePath`: Caminho completo do arquivo onde o frame será salvo.
  - `frameSize`: O tamanho do quadro a ser capturado. Exemplos:
    - `FRAMESIZE_QVGA`: 320x240 pixels.
    - `FRAMESIZE_VGA`: 640x480 pixels.
    - `FRAMESIZE_HD`: 1280x720 pixels.
  - `jpegQuality`: A qualidade de compressão JPEG a ser ajustada. Escala:
    - **0-10**: Alta qualidade (maior tamanho de arquivo).
    - **11-20**: Qualidade média.
    - **21-63**: Baixa qualidade (menor tamanho de arquivo).

- **Retorno**:
  - Retorna `true` se o frame foi capturado e salvo com sucesso.
  - Retorna `false` caso contrário.

- **Funcionamento**:
  - O método ajusta o tamanho do quadro e a qualidade JPEG antes de capturar o frame.
  - Após a captura, os dados JPEG são gravados no arquivo especificado no sistema de arquivos.
  - O tamanho do quadro e a qualidade JPEG originais são restaurados após a operação.

- **Dica de otimização**:
  - Certifique-se de que o sistema de arquivos tenha espaço suficiente antes de salvar o arquivo.
  - Use nomes de arquivos únicos para evitar sobrescritas acidentais.
  - Para economizar espaço, use resoluções menores e compressão mais alta, dependendo das necessidades do projeto.

- **Nota**:
  - Caso o ajuste do tamanho do quadro ou da qualidade JPEG falhe, o método retorna `false` e registra um erro no log.
  - Este método é útil para capturas pontuais. Para capturas contínuas, combine este método com bibliotecas de rede para enviar os arquivos para um servidor ou nuvem.

> **Atenção:**  
> A conversão de frames de outros formatos (como RGB565) para JPEG pode falhar por falta de memória RAM no ESP32.  
> Para evitar esse problema, **inicialize a câmera diretamente em [PIXFORMAT_JPEG](http://_vscodecontentref_/2)** usando o método [begin()](http://_vscodecontentref_/3), por exemplo:
> ```cpp
> camera.begin(FRAMESIZE_QVGA, 12, FRAMESIZE_VGA, PIXFORMAT_JPEG);
> ```
> Isso garante que os frames já serão capturados em JPEG, economizando memória e evitando falhas na conversão ou no salvamento de imagens.

---


#### Exemplo de Uso 1: Salvamento com Configuração Padrão
Este exemplo demonstra como capturar um frame no formato JPEG utilizando a configuração padrão da câmera e salvá-lo no sistema de arquivos SPIFFS. A configuração padrão inclui o tamanho de quadro e a qualidade JPEG predefinidos pela biblioteca. Este método é ideal para aplicações simples que não exigem ajustes personalizados.

- **Funcionamento**:
  - Inicializa o sistema de arquivos SPIFFS.
  - Configura a câmera utilizando os parâmetros padrão.
  - Captura um frame e salva no arquivo especificado (`/captura.jpg`).
  - Exibe mensagens no console indicando o sucesso ou falha da operação.

```cpp
#include <ES32Lab.h>

ES_Camera camera;

void setup() {
    SPIFFS.begin();
    camera.begin();

    if (camera.saveFrameToJpegFile(SPIFFS, "/captura.jpg")) {
        Serial.println("Frame salvo com sucesso em /captura.jpg");
    } else {
        Serial.println("Falha ao salvar o frame.");
    }
}
void loop(){

}
```

#### Exemplo de Uso 2: Salvamento com Configuração Personalizada
Este exemplo demonstra como capturar um frame no formato JPEG utilizando configurações personalizadas de tamanho de quadro e qualidade de compressão, e salvá-lo no sistema de arquivos SD. Este método é ideal para aplicações que exigem maior controle sobre a resolução e a qualidade da imagem capturada.

- **Funcionamento**:
  - Inicializa o sistema de arquivos SD.
  - Configura a câmera utilizando parâmetros personalizados, como tamanho de quadro (`FRAMESIZE_VGA`) e qualidade JPEG (`10`).
  - Captura um frame e salva no arquivo especificado (`/captura_custom.jpg`).
  - Exibe mensagens no console indicando o sucesso ou falha da operação.

```cpp
#include <ES32Lab.h>

ES_Camera camera;

void setup() {
    SD.begin();
    camera.begin();

    if (camera.saveFrameToJpegFile(SD, "/captura_custom.jpg", FRAMESIZE_VGA, 10)) {
        Serial.println("Frame salvo com sucesso em /captura_custom.jpg");
    } else {
        Serial.println("Falha ao salvar o frame.");
    }
}
void loop(){
    
}
```


---


### Métodos de Streaming
Os métodos de streaming permitem configurar e gerenciar a transmissão de vídeo em tempo real da câmera conectada ao ESP32. Com esses métodos, é possível criar endpoints HTTP para que clientes acessem o stream de vídeo diretamente, utilizando navegadores ou outras ferramentas compatíveis. Eles são ideais para aplicações como vigilância, monitoramento remoto, robótica e IoT.

#### `handleStreamRequest(httpd_req_t *req)`
Este método manipula solicitações de streaming HTTP, permitindo que a câmera envie frames JPEG contínuos para o cliente em um formato de streaming. Ele é ideal para aplicações que exigem transmissão de vídeo em tempo real, como vigilância ou monitoramento remoto.

- **Parâmetros**:
  - `req`: Ponteiro para a solicitação HTTP recebida.

- **Retorno**:
  - Retorna `ESP_OK` se a solicitação foi manipulada com sucesso.
  - Retorna um código de erro caso contrário.

- **Funcionamento**:
  1. Define o cabeçalho HTTP para indicar que a resposta será um stream multipart (`multipart/x-mixed-replace`).
  2. Captura frames JPEG da câmera usando o método `getFrameJpegBuffer`.
  3. Envia cada frame como parte do stream, incluindo os cabeçalhos necessários para o cliente interpretar os dados como imagens JPEG.
  4. Pausa o streaming se `pauseStream` estiver ativado, aguardando antes de continuar.

- **Dica de otimização**:
  - Certifique-se de que a largura de banda da rede seja suficiente para suportar o streaming em tempo real.
  - Use resoluções menores e compressão mais alta para reduzir o tamanho dos frames e melhorar o desempenho em redes lentas.

- **Nota**:
  - Caso a captura de frames falhe, o método interrompe o streaming e retorna um erro.
  - Este método é projetado para ser usado em conjunto com um servidor HTTP, como o ESP-IDF HTTP Server.

> **Atenção:**  
> A conversão de frames de outros formatos (como RGB565) para JPEG pode falhar por falta de memória RAM no ESP32.  
> Para evitar esse problema, **inicialize a câmera diretamente em [PIXFORMAT_JPEG](http://_vscodecontentref_/2)** usando o método [begin()](http://_vscodecontentref_/3), por exemplo:
> ```cpp
> camera.begin(FRAMESIZE_QVGA, 12, FRAMESIZE_VGA, PIXFORMAT_JPEG);
> ```
> Isso garante que os frames já serão capturados em JPEG, economizando memória e evitando falhas na conversão ou no salvamento de imagens.


#### Exemplo de Uso
```cpp
// Estrutura httpd_uri_t para configurar o endpoint de streaming
httpd_uri_t streamEndpoint = {
    .uri = "/stream", // URI do endpoint de streaming
    .method = HTTP_GET, // Método HTTP permitido (GET)
    .handler = [](httpd_req_t *req) -> esp_err_t { // Função de manipulação da solicitação
        ES_Camera* camera = (ES_Camera*)req->user_ctx; // Obtém o contexto do usuário (instância da câmera)
        return camera->handleStreamRequest(req); // Chama o método para manipular a solicitação de streaming
    },
    .user_ctx = this, // Contexto do usuário (instância da câmera)
    .is_websocket = false, // Indica que não é um WebSocket
    .handle_ws_control_frames = false, // Não manipula quadros de controle WebSocket
    .supported_subprotocol = NULL // Sem subprotocolos suportados
};
```


#### `createStreamEndpoint(const char* streamUri)`
Este método cria um endpoint HTTP para streaming de vídeo da câmera. Ele configura a estrutura necessária para que o servidor HTTP manipule solicitações de streaming, permitindo que frames JPEG sejam enviados continuamente para o cliente.

- **Parâmetros**:
  - `streamUri`: O URI do endpoint de streaming. Este será o caminho acessado pelo cliente para visualizar o stream (por exemplo, `"/stream"`).

- **Retorno**:
  - Retorna uma estrutura `httpd_uri_t` configurada para o endpoint de streaming.

- **Funcionamento**:
  1. Armazena o URI fornecido no atributo interno `_streamUri`.
  2. Configura a estrutura `httpd_uri_t` com os seguintes parâmetros:
     - `uri`: Define o URI do endpoint.
     - `method`: Define o método HTTP permitido (neste caso, `HTTP_GET`).
     - `handler`: Define a função de manipulação da solicitação, que chama o método `handleStreamRequest` para processar o streaming.
     - `user_ctx`: Define o contexto do usuário, que é a instância da classe `ES_Camera`.
     - `is_websocket`: Define que o endpoint não é um WebSocket.
     - `handle_ws_control_frames`: Define que quadros de controle WebSocket não serão manipulados.
     - `supported_subprotocol`: Define que nenhum subprotocolo é suportado.

- **Dica de uso**:
  - Após criar o endpoint com este método, registre-o no servidor HTTP para ativar o streaming.
  - Certifique-se de que o servidor HTTP esteja configurado corretamente para lidar com endpoints.


#### `getStreamUri()`
Este método retorna o URI configurado para o endpoint de streaming da câmera. Ele é útil para recuperar o caminho que os clientes devem acessar para visualizar o stream de vídeo.

- **Retorno**:
  - Retorna uma string (`const char*`) contendo o URI do stream configurado.
  - Caso o URI não tenha sido configurado, retorna `NULL`.

- **Funcionamento**:
  - O método simplesmente retorna o valor armazenado na variável interna `_streamUri`, que é configurada durante a criação do endpoint de streaming com o método `createStreamEndpoint`.

- **Dica de uso**:
  - Use este método para exibir ou registrar o URI do stream no console serial ou em logs, facilitando o acesso ao stream pelos clientes.


---

### Exemplo: Configuração de Streaming de Vídeo
Este exemplo demonstra como configurar um servidor HTTP para streaming de vídeo em tempo real utilizando a biblioteca `ES32Lab` e uma câmera conectada ao ESP32. O código inicializa a câmera, conecta o ESP32 a uma rede Wi-Fi e configura um endpoint HTTP para transmitir frames JPEG contínuos.

- **Funcionamento**:
  1. **Conexão Wi-Fi**: O ESP32 se conecta à rede Wi-Fi utilizando as credenciais fornecidas (`ssid` e `password`).
  2. **Inicialização da Câmera**: A câmera é configurada com resolução `QQVGA` e qualidade JPEG de `12`.
  3. **Configuração do Servidor HTTP**: Um servidor HTTP é iniciado na porta `80`, e um endpoint de streaming é registrado no caminho `/stream`.
  4. **Streaming de Vídeo**: O servidor transmite frames JPEG contínuos para qualquer cliente que acessar o endpoint `/stream`.
  5. **URL do Stream**: A URL para acessar o stream é exibida no console serial.

```cpp
#include <Arduino.h>    
#include <WiFi.h>       // Wi-Fi library | Biblioteca Wi-Fi
#include <ES32Lab.h>    // Library ES32Lab | Biblioteca ES32Lab

//--- Wi-Fi Configuration | Configuração do Wi-Fi ---//
const char* ssid = "YOUR_SSID";         // Replace with your Wi-Fi network name. | Substitua pelo nome da sua rede Wi-Fi.
const char* password = "YOUR_PASSWORD"; // Replace with your Wi-Fi password. | Substitua pela senha da sua rede Wi-Fi.

ES_Camera camera;   // Camera object | Objeto da câmera

httpd_handle_t stream_httpd = NULL; // HTTP server handle for streaming | Manipulador do servidor HTTP para streaming

void setup() {
    Serial.begin(115200);   // Initialize serial communication at 115200 baud rate | Inicializa a comunicação serial a 115200 bps
    Serial.println();
    Serial.println("Initializing...");

    //--- Wi-Fi Connection | Conexão Wi-Fi ---//
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.print("Connected to WiFi: ");
    Serial.println(ssid);

    //--- Camera Initialization | Inicialização da câmera ---
    if (!camera.begin(FRAMESIZE_QQVGA, 12)) {   // Initialize the camera with QQVGA resolution and JPEG quality of 12 | Inicializa a câmera com resolução QQVGA e qualidade JPEG de 12
        Serial.println("Camera initialization failed!");
        while (true);
    }
    Serial.println("Camera initialized successfully!");

    // --- Set web server for streaming | Configura o servidor web para streaming ---
    httpd_config_t config = HTTPD_DEFAULT_CONFIG(); // Default HTTP server configuration | Configuração padrão do servidor HTTP
    config.server_port = 80;    // Set the server port to 80 | Define a porta do servidor como 80

    //--- Start the HTTP server | Inicia o servidor HTTP ---
    if (httpd_start(&stream_httpd, &config) == ESP_OK) {
        httpd_uri_t stream_uri = camera.createStreamEndpoint("/stream");    // Create the stream endpoint | Cria o endpoint de stream
        httpd_register_uri_handler(stream_httpd, &stream_uri);  // Register the stream URI handler | Registra o manipulador do URI de stream
    }

    //--- Print the stream URL | Imprime a URL do stream ---
    Serial.print("Camera Stream URL: http://");
    Serial.print(WiFi.localIP());
    Serial.println(camera.getStreamUri());
}

void loop() {

}

```

---

## Exemplos Oficiais

A biblioteca ES32Lab oferece exemplos práticos e completos para facilitar o uso da classe `ES_Camera` em diferentes cenários, como captura de imagens, salvamento em arquivos e streaming de vídeo via HTTP.  
Você pode acessar os exemplos oficiais diretamente no repositório do projeto:

- [Exemplos Oficiais da Classe ES_Camera](https://github.com/ESDeveloperBR/ES32Lab/tree/main/examples/Camera/Camera-StreamHTTP)

Esses exemplos demonstram as melhores práticas de inicialização, configuração, captura, salvamento e streaming com a `ES_Camera`, servindo como referência para o desenvolvimento dos seus próprios projetos.

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |