| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |


---


# Documentação da Classe ES_File

A classe `ES_File` é um componente essencial da biblioteca ES32Lab, projetada para simplificar o gerenciamento de arquivos e diretórios em sistemas de arquivos suportados pelo ESP32, como SPIFFS, LittleFS e SD. Ela oferece uma interface poderosa e intuitiva para realizar operações como criação, leitura, escrita, exclusão, listagem e manipulação de arquivos e diretórios.

Com suporte a funcionalidades como verificação de existência de arquivos, obtenção de tamanho, navegação entre arquivos em diretórios e cópia de arquivos entre diferentes sistemas de arquivos, a `ES_File` é uma ferramenta indispensável para projetos que exigem armazenamento e manipulação de dados. Exemplos incluem sistemas de registro de dados, armazenamento de configurações, manipulação de logs e muito mais.

Além disso, a classe é otimizada para oferecer alto desempenho e flexibilidade, alinhada ao compromisso da ES32Lab de fornecer ferramentas modernas, acessíveis e eficientes para desenvolvimento com ESP32.

### **Principais Recursos**
- **Suporte a Múltiplos Sistemas de Arquivos**: Compatível com SPIFFS, LittleFS e SD.
- **Operações Básicas de Arquivos**: Criação, leitura, escrita, exclusão e verificação de existência.
- **Manipulação de Diretórios**: Criação, exclusão e listagem de arquivos e subdiretórios.
- **Navegação em Diretórios**: Obtenção do primeiro, último, próximo e anterior arquivo em um diretório.
- **Cópia de Arquivos e Diretórios**: Entre diferentes sistemas de arquivos.
- **Informações do Sistema de Arquivos**: Obtenção de espaço total, usado e disponível.


---


## Índice

1. [Construtor](#construtor)
2. [Configuração no `setup()`](#configuração-no-setup)
3. [Métodos da Classe](#métodos-da-classe)
   - [Inicialização do Sistema de Arquivos](#inicialização-do-sistema-de-arquivos)
   - [Operações Básicas de Arquivos](#operações-básicas-de-arquivos)
   - [Manipulação de Diretórios](#manipulação-de-diretórios)
   - [Navegação em Diretórios](#navegação-em-diretórios)
   - [Cópia de Arquivos e Diretórios](#cópia-de-arquivos-e-diretórios)
   - [Informações do Sistema de Arquivos](#informações-do-sistema-de-arquivos)
4. [Exemplo: Operações Básicas com Arquivos](#exemplo-operações-básicas-com-arquivos)


---


## Construtor

### `ES_File()`

O construtor `ES_File` é utilizado para inicializar uma nova instância da classe, configurando os parâmetros padrão necessários para o funcionamento da manipulação de arquivos e diretórios. Ele é essencial para estabelecer a conexão entre o ESP32 e o sistema de arquivos escolhido.

---


## Configuração no `setup()`

O método `begin()` é essencial para inicializar o sistema de arquivos com os parâmetros desejados. Ele deve ser chamado dentro da função `setup()` para garantir que o sistema de arquivos esteja pronto para realizar operações de leitura e escrita.

### `begin()`

Inicializa o sistema de arquivos especificado, permitindo configurar o tipo de sistema de arquivos a ser utilizado (SPIFFS, LittleFS ou SD).

#### Sintaxe:
```cpp
bool begin(fs::FS& fs);
```

#### Parâmetros:
- **`fs`**: Sistema de arquivos a ser inicializado. Pode ser `SPIFFS`, `LittleFS` ou `SD`.

#### Retorno:
- **`true`**: Se o sistema de arquivos foi inicializado com sucesso.
- **`false`**: Caso contrário.

#### Exemplo de Uso:
```cpp
ES_File fileManager;

void setup() {
    Serial.begin(115200);

    if (fileManager.begin(SPIFFS)) {
        Serial.println("Sistema de arquivos inicializado com sucesso!");
    } else {
        Serial.println("Falha ao inicializar o sistema de arquivos.");
    }
}
```

---


## Métodos da Classe

### Inicialização do Sistema de Arquivos

- **`bool begin(fs::FS& fs)`**  
  Inicializa o sistema de arquivos especificado.

---

### Operações Básicas de Arquivos

- **`bool println(const String& fileName, const String& content, bool createNew = false)`**  
  Escreve uma linha de texto em um arquivo com uma quebra de linha.

- **`bool print(const String& fileName, const String& content, bool createNew = false)`**  
  Escreve texto em um arquivo sem uma quebra de linha.

- **`String readFile(const String& fileName)`**  
  Lê o conteúdo de um arquivo.

- **`bool exists(const String& fileName)`**  
  Verifica se um arquivo existe.

- **`size_t getFileSize(const String& fileName)`**  
  Obtém o tamanho de um arquivo em bytes.

---

### Manipulação de Diretórios

- **`bool createDirectory(const String& directory)`**  
  Cria um diretório.

- **`bool remove(const String& path, bool recursive = false)`**  
  Remove um arquivo ou diretório.

- **`String listAllFiles(const String& directory, bool showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false)`**  
  Lista todos os arquivos em um diretório.

---

### Navegação em Diretórios

- **`String getFirstFileName(const String& directory = "/")`**  
  Obtém o nome do primeiro arquivo em um diretório.

- **`String getLastFileName(const String& directory = "/")`**  
  Obtém o nome do último arquivo em um diretório.

- **`String getNextFileName(const String& directory = "")`**  
  Obtém o nome do próximo arquivo em um diretório.

- **`String getPreviousFileName(const String& directory = "")`**  
  Obtém o nome do arquivo anterior em um diretório.

---

### Cópia de Arquivos e Diretórios

- **`bool copy(const String& sourceFileName, fs::FS& destFS, const String& destFileName)`**  
  Copia um arquivo de um sistema de arquivos para outro.

---

### Informações do Sistema de Arquivos

- **`size_t getTotalSpace()`**  
  Obtém o espaço total do sistema de arquivos.

- **`size_t getUsedSpace(const String& directory = "/", bool includeSubDirs = true)`**  
  Obtém o espaço usado do sistema de arquivos.

- **`size_t getAvailableSpace()`**  
  Obtém o espaço disponível do sistema de arquivos.

---

## Exemplo: Operações Básicas com Arquivos

Este exemplo demonstra como inicializar o sistema de arquivos, criar um arquivo, escrever texto, verificar sua existência, obter seu tamanho e ler seu conteúdo.

```cpp
#include <Arduino.h>
#include <ES_File.h>

ES_File fileManager;

void setup() {
    Serial.begin(115200);

    if (fileManager.begin(SPIFFS)) {
        Serial.println("Sistema de arquivos inicializado com sucesso!");
    } else {
        Serial.println("Falha ao inicializar o sistema de arquivos.");
        return;
    }

    String fileName = "/exemplo.txt";

    // Escreve no arquivo
    fileManager.println(fileName, "Linha 1: Olá, Mundo!", true);
    fileManager.println(fileName, "Linha 2: Adicionando mais texto.", false);

    // Verifica se o arquivo existe
    if (fileManager.exists(fileName)) {
        Serial.println("O arquivo existe.");
    }

    // Obtém o tamanho do arquivo
    size_t fileSize = fileManager.getFileSize(fileName);
    Serial.printf("Tamanho do arquivo: %d bytes\n", fileSize);

    // Lê o conteúdo do arquivo
    String content = fileManager.readFile(fileName);
    Serial.println("Conteúdo do arquivo:");
    Serial.println(content);
}

void loop() {
    // Não há lógica no loop para este exemplo
}
```

---

| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |