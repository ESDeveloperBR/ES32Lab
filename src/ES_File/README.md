| [Índice de classes contidas na LIB ES32Lab](https://github.com/ESDeveloperBR/ES32Lab#conjunto-de-classes-contidas-na-lib-es32lab) |
| :------: |


---


# Documentação da Classe ES_File

A classe `ES_File` é um componente essencial da biblioteca ES32Lab, projetada para simplificar o gerenciamento de arquivos e diretórios em sistemas de arquivos suportados pelo ESP32, como SPIFFS, LittleFS e SD. Ela oferece uma interface poderosa e intuitiva para realizar operações como criação, leitura, escrita, exclusão, listagem e manipulação de arquivos e diretórios.

Com suporte a funcionalidades como verificação de existência de arquivos, obtenção de tamanho, navegação entre arquivos em diretórios e cópia de arquivos entre diferentes sistemas de arquivos, a `ES_File` é uma ferramenta indispensável para projetos que exigem armazenamento e manipulação de dados. Exemplos incluem sistemas de registro de dados, armazenamento de configurações, manipulação de logs e muito mais.

Embora o SPIFFS seja amplamente utilizado devido à sua simplicidade e eficiência em dispositivos com recursos limitados, ele possui a limitação de não suportar diretórios. Para projetos que exigem manipulação de diretórios, recomenda-se o uso de sistemas de arquivos como LittleFS ou SD, que oferecem maior flexibilidade e suporte a hierarquias de arquivos.

Além disso, a classe é otimizada para oferecer alto desempenho e flexibilidade, alinhada ao compromisso da ES32Lab de fornecer ferramentas modernas, acessíveis e eficientes para desenvolvimento com ESP32.


---


## Índice

1. [Introdução](#introdução)
2. [Construtor](#construtor)
3. [Inicialização do Sistema de Arquivos](#inicialização-do-sistema-de-arquivos)
4. [Alternativas ao Uso de `begin()`](#alternativas-ao-uso-de-begin)
5. [Métodos da Classe](#métodos-da-classe)
   - [Escrita em Arquivos](#escrita-em-arquivos)
     - [`println()` - Escrita com nova linha](#println---escrita-com-nova-linha)
     - [`print()` - Escrita sem nova linha](#print---escrita-sem-nova-linha)
   - [Leitura de Arquivos](#leitura-de-arquivos)
     - [`readFile()`](#readfile)
     - [`readLine()`](#readline)
     - [`countLines()`](#countlines)
   - [Listagem de Arquivos](#listagem-de-arquivos)
   - [Verificação de Existência](#verificação-de-existência)
     - [`exists()`](#exists)
     - [`directoryExists()`](#directoryexists)
   - [Remoção de Arquivos e Diretórios](#remoção-de-arquivos-e-diretórios)
   - [Navegação entre Arquivos](#navegação-entre-arquivos)
     - [`getFirstFileName()`](#getfirstfilename)
     - [`getLastFileName()`](#getlastfilename)
     - [`getNextFileName()`](#getnextfilename)
     - [`getPreviousFileName()`](#getpreviousfilename)
   - [Criação de Diretórios](#criação-de-diretórios)
   - [Movimentação e Renomeação](#movimentação-e-renomeação)
   - [Cópia de Arquivos](#cópia-de-arquivos)
   - [Informações sobre Espaço](#informações-sobre-espaço)
     - [`getTotalSpace()`](#gettotalspace)
     - [`getUsedSpace()`](#getusedspace)
     - [`getAvailableSpace()`](#getavailablespace)
     - [`getFileSize()`](#getfilesize)
6. [Exemplo: Operações Básicas com Arquivos](#exemplo-operações-básicas-com-arquivos)


---


## Construtor

### `ES_File::ES_File()`

O construtor padrão da classe `ES_File` inicializa a instância sem associar imediatamente um sistema de arquivos. Isso permite ao desenvolvedor utilizar diferentes sistemas de arquivos ao longo da aplicação, sem a obrigatoriedade de definir um único sistema padrão global.

```cpp
ES_File file;
```

Após a criação do objeto, o desenvolvedor poderá:

* Associar um sistema de arquivos padrão (via `begin()`), ou
* Informar explicitamente o sistema de arquivos em cada chamada de método (formas sobrecarregadas).

Essa flexibilidade é especialmente útil em aplicações que envolvem múltiplos sistemas de arquivos (ex: `SD` e `LittleFS`) simultaneamente.

---

## Inicialização do sistema de arquivos

### `bool begin(fs::FS& fs)`

Este método opcional permite associar um sistema de arquivos padrão à instância atual da classe `ES_File`. A partir de então, qualquer método que não receba o sistema de arquivos explicitamente utilizará o sistema definido pelo `begin()`.

> **Importante:** O `begin()` executa a rotina de montagem do sistema de arquivos informado (incluindo chamadas como `SPIFFS.begin(true)` ou `SD.begin(SS)`). Ele cuida da inicialização completa, e não apenas da associação de ponteiros.

#### Parâmetro

* `fs`: Referência para um sistema de arquivos válido, como:

  * `SD` (cartão microSD),
  * `SPIFFS` (sistema legado),
  * `LittleFS` (sistema moderno recomendado).

#### Retorno

* `true` – Se o sistema foi montado com sucesso;
* `false` – Se a montagem falhou ou se o ponteiro for inválido.

#### Comportamento interno

O método detecta o tipo de sistema e evita reinicializações redundantes. Para cada tipo (`SD`, `SPIFFS`, `LittleFS`), a montagem só é executada uma vez por aplicação, mesmo que `begin()` seja chamado múltiplas vezes.

#### Exemplo: associando um sistema padrão à instância

```cpp
#include <FS.h>
#include <SPIFFS.h>
#include <ES32Lab.h>

ES_File file;

void setup() {
  Serial.begin(115200);

  if (!file.begin(SPIFFS)) {
    Serial.println("Erro ao iniciar SPIFFS");
    while (true);
  }

  Serial.println("SPIFFS pronto para uso");
}
```

---

## Alternativas ao uso de `begin()`

O uso de `begin()` é recomendado para simplificar o código quando um único sistema será utilizado. No entanto, em aplicações que usam múltiplos sistemas de arquivos, é possível **não usar `begin()`** e, em vez disso, informar explicitamente o sistema desejado em cada método. Todos os métodos públicos da classe `ES_File` oferecem versões sobrecarregadas com o parâmetro `fs::FS&`.

#### Exemplo: uso sem `begin()`

```cpp
file.println(LittleFS, "/log.txt", "Log de inicialização", true);
file.copy(SD, "/backup.txt", LittleFS, "/copia/backup.txt");
```

Nesse caso, nenhuma associação padrão é feita, e o sistema de arquivos deve ser sempre informado explicitamente.

---

### Resumo técnico

| Situação                                     | Comportamento                               |
| -------------------------------------------- | ------------------------------------------- |
| `begin(fs)` chamado                          | Define sistema padrão para chamadas futuras |
| Método com parâmetro `fs`                    | Utiliza o sistema explicitamente informado  |
| `begin(fs)` não chamado e sem parâmetro `fs` | Métodos não funcionarão corretamente        |



## Métodos de Escrita

A classe `ES_File` oferece dois principais métodos para escrita de dados em arquivos:

* `print(...)`
* `println(...)`

A diferença essencial entre eles é que `println()` adiciona automaticamente um caractere de nova linha (`\n`) ao final do conteúdo escrito, enquanto `print()` não adiciona nada.

Todos os métodos possuem sobrecargas para os seguintes tipos:

* `String`
* `int`
* `double`

E cada versão pode ser utilizada de duas formas:

1. Com sistema de arquivos previamente definido via `begin(fs)`.
2. Informando explicitamente o sistema de arquivos em cada chamada.

A seguir, detalharemos cada uma das sobrecargas, com descrição precisa dos parâmetros e exemplos práticos.

---

## `println()` - Escrita com nova linha

### 1. `bool println(const String& fileName, const String& content, bool createNew = false)`

Escreve uma string com quebra de linha no final.

* `fileName`: Caminho do arquivo (ex: "/log.txt").
* `content`: Texto a ser escrito.
* `createNew`: Se `true`, o arquivo é recriado; se `false`, o conteúdo é adicionado ao final.

```cpp
file.println("/log.txt", "Dispositivo iniciado");
```

### 2. `bool println(const String& fileName, int content, bool createNew = false)`

Escreve um número inteiro seguido de nova linha.

```cpp
file.println("/log.txt", 42);
```

### 3. `bool println(const String& fileName, double content, bool createNew = false, uint8_t decimalPlaces = 2)`

Método responsável por escrever um número decimal no formato especificado, com uma quantidade definida de casas decimais, e adicionar uma nova linha ao final.

Parâmetros:
- `fileName`: O caminho do arquivo onde o número será escrito (ex: "/dados.txt").
- `content`: O número decimal que será escrito no arquivo.
- `createNew`: Define se o arquivo será recriado (`true`) ou se o conteúdo será adicionado ao final (`false`).
- `decimalPlaces`: A quantidade de casas decimais que o número deve ter ao ser formatado.

Essa função é útil para garantir a formatação consistente de números decimais em saídas, especialmente em contextos onde a precisão é importante.

```cpp
file.println("/log.txt", 3.14159, false, 4);  // 3.1416\n
file.println("/log.txt", 2.5);               // 2.50\n
file.println("/log.txt", 2.5, true, 0);       // 3\n
```


### 4. `bool println(fs::FS& fs, const String& fileName, const String& content, bool createNew = false)`

Este método escreve uma linha de texto em um arquivo, adicionando automaticamente uma quebra de linha (`\n`) ao final do conteúdo. Ele permite especificar diretamente o sistema de arquivos (`fs::FS& fs`) a ser utilizado, sem a necessidade de chamar previamente o método `begin()` para definir um sistema de arquivos padrão.

#### **Parâmetros**
- **`fs`**: Referência para o sistema de arquivos a ser utilizado. Pode ser:
  - `SPIFFS`: Sistema de arquivos legado, ideal para aplicações simples.
  - `LittleFS`: Sistema moderno recomendado, com suporte a diretórios.
  - `SD`: Sistema de arquivos para cartões SD, ideal para grandes volumes de dados.
- **`fileName`**: Caminho do arquivo onde o conteúdo será escrito (ex.: `"/log.txt"`).
- **`content`**: Texto a ser escrito no arquivo.
- **`createNew`** *(opcional)*: Define se o arquivo será recriado ou se o conteúdo será adicionado ao final:
  - `true`: O arquivo será recriado, sobrescrevendo qualquer conteúdo existente.
  - `false` *(padrão)*: O conteúdo será adicionado ao final do arquivo, preservando o conteúdo existente.

#### **Retorno**
- **`true`**: Se a operação foi bem-sucedida.
- **`false`**: Se houve falha na operação, como problemas ao abrir o arquivo ou inicializar o sistema de arquivos.

#### **Comportamento**
- Quando o parâmetro `fs` é especificado, o método inicializa automaticamente o sistema de arquivos correspondente, caso ele ainda não tenha sido inicializado. Isso elimina a necessidade de chamar o método `begin()` previamente.
- O método é útil em aplicações que utilizam múltiplos sistemas de arquivos, permitindo alternar entre eles de forma explícita e independente.

#### **Exemplo**

```cpp
file.println(SD, "/log.txt", "Registro via SD");
```

#### **Notas Importantes**
1. **Inicialização Automática**: O método detecta e inicializa automaticamente o sistema de arquivos especificado, evitando reinicializações redundantes.
2. **Flexibilidade**: Ideal para aplicações que utilizam múltiplos sistemas de arquivos, permitindo alternar entre eles sem a necessidade de redefinir um sistema padrão.

#### **Considerações**
- Para projetos que utilizam apenas um sistema de arquivos, recomenda-se o uso do método `begin()` para definir um sistema padrão, simplificando as chamadas subsequentes.
- Este método é especialmente útil em cenários onde diferentes sistemas de arquivos são utilizados simultaneamente, como armazenar logs no SPIFFS e backups no SD.

---

## `print()` - Escrita sem nova linha

### 1. `bool print(const String& fileName, const String& content, bool createNew = false)`

Escreve texto exatamente como recebido, sem adicionar `\n` ao final.

```cpp
file.print("/status.txt", "Ligado: ");
file.print("/status.txt", "Sim", false);  // Resultado final: Ligado: Sim
```

### 2. `bool print(const String& fileName, int content, bool createNew = false)`

```cpp
file.print("/status.txt", 123);
```

### 3. `bool print(const String& fileName, double content, bool createNew = false, uint8_t decimalPlaces = 2)`

Permite controle de casas decimais:

```cpp
file.print("/status.txt", 5.6789, false, 3); // 5.679
```

### 4. `bool print(fs::FS& fs, const String& fileName, const String& content, bool createNew = false)`

Permite uso com sistema de arquivos externo:

```cpp
file.print(LittleFS, "/data.txt", "Texto direto");
```

> **Observação:** Todos os métodos de escrita, ao usar `createNew = true`, sobrescrevem o arquivo (modo `w`). Com `false`, operam em modo de anexação (modo `a`).

---

## Considerações de Desempenho

* Escrever em arquivos é uma operação custosa. Evite abrir e fechar arquivos com muita frequência.
* Prefira acumular informações em buffer e gravar de uma vez.
* O uso de `createNew = true` reabre o arquivo em modo "write", zerando seu conteúdo anterior.

---

## Exemplos Combinados

```cpp
file.println("/log.txt", "Inicio do sistema", true);
file.println("/log.txt", millis());
file.print("/log.txt", "Temperatura: ");
file.println("/log.txt", 22.756, false, 1);  // Temperatura: 22.8
```

Esse conjunto produz:

```
Inicio do sistema
1234
Temperatura: 22.8
```

## Métodos de Leitura

A classe `ES_File` fornece três principais métodos de leitura que atendem a diferentes necessidades:

* `readFile()`
* `readLine()`
* `countLines()`

Todos os métodos estão disponíveis tanto com uso do sistema de arquivos padrão (definido via `begin()`), quanto com especificação direta do sistema via parâmetro `fs::FS&`.

---

## `String readFile(const String& fileName)`

### Descrição

Lê todo o conteúdo do arquivo especificado e o retorna como uma única `String`. Caso o arquivo não exista ou não possa ser aberto, retorna uma string vazia.

### Parâmetros

* `fileName`: Caminho completo do arquivo.

### Retorno

* Conteúdo do arquivo como `String`, ou string vazia em caso de erro.

### Exemplo

```cpp
String dados = file.readFile("/dados.txt");
Serial.println(dados);
```

### Versão com sistema de arquivos explícito

```cpp
String dados = file.readFile(SD, "/config.txt");
```

---

## `String readLine(const String& fileName, size_t lineNumber)`

### Descrição
Retorna o conteúdo de uma linha específica de um arquivo, considerando que a contagem de linhas começa em 1 (ou seja, a primeira linha corresponde a `lineNumber = 1`).

### Parâmetros

* `fileName`: Caminho do arquivo.
* `lineNumber`: Linha desejada (1, 2, 3...).

### Retorno

* Conteúdo da linha especificada como `String`.
* Retorna string vazia se a linha não existir, o arquivo for inválido, ou algum erro ocorrer.

### Exemplo

```cpp
String linha3 = file.readLine("/dados.txt", 3);
Serial.println("Linha 3: " + linha3);
```

### Versão com sistema de arquivos explícito

```cpp
String linha2 = file.readLine(LittleFS, "/config.txt", 2);
```

> **Nota:** O método percorre o arquivo desde o início, linha a linha, até chegar na desejada. Isso pode impactar o desempenho com arquivos muito grandes.

---

## `size_t countLines(const String& fileName)`

### Descrição

Conta o número total de linhas presentes em um arquivo. Cada `\n` (quebra de linha) conta como delimitador de uma nova linha.

### Parâmetros

* `fileName`: Caminho completo do arquivo.

### Retorno

* Número de linhas (`size_t`).
* Retorna 0 se o arquivo estiver vazio ou não puder ser aberto.

### Exemplo

```cpp
size_t total = file.countLines("/dados.txt");
Serial.printf("Total de linhas: %u\n", total);
```

### Versão com sistema de arquivos explícito

```cpp
size_t total = file.countLines(SD, "/log.txt");
```

---

## Considerações

* O método `readFile()` é ideal para arquivos pequenos ou para recuperar configurações completas.
* `readLine()` é útilem casos onde é necessário extrair uma linha específica (ex: leitura de registros).
* `countLines()` pode ser usado para validar se o arquivo está completo ou para preparar uma navegação por linha.

---

## Exemplo Integrado

```cpp
file.begin(SPIFFS);
size_t total = file.countLines("/dados.txt");

for (size_t i = 1; i <= total; ++i) {
  String linha = file.readLine("/dados.txt", i);
  Serial.printf("Linha %u: %s\n", i, linha.c_str());
}
```


## Método de Listagem de Arquivos

A classe `ES_File` disponibiliza o método `listAllFiles()` para listar arquivos e diretórios contidos em uma pasta. Este é um dos métodos mais versáteis da classe, permitindo configurações como:

* Exibir ou ocultar tamanhos dos arquivos;
* Incluir ou excluir subdiretórios;
* Listar subdiretórios de forma recursiva;
* Exibir estrutura com indentacão hierárquica.

---

## `String listAllFiles(const String& directory, bool showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false)`

### Descrição

Lista todos os arquivos presentes no diretório especificado, organizados em ordem alfabética. O método possui vários parâmetros que controlam a forma de apresentação da saída.

### Parâmetros

* `directory`: Caminho do diretório a ser listado (ex: "/", "/data").
* `showFileSize` (padrão `false`): Mostra o tamanho de cada arquivo, em bytes.
* `showSubDir` (padrão `true`): Inclui os subdiretórios encontrados.
* `openSubDir` (padrão `true`): Lista o conteúdo dos subdiretórios recursivamente.
* `indentation` (padrão `false`): Apresenta a estrutura com indentacção para simular hierarquia.

### Retorno

* `String` contendo a lista formatada de arquivos e pastas. Retorna string vazia em caso de erro ou se o diretório estiver vazio.

### Exemplo básico

```cpp
String lista = file.listAllFiles("/");
Serial.println(lista);
```

### Exemplo com tamanho dos arquivos

```cpp
String lista = file.listAllFiles("/data", true);
```

### Exemplo com indentacção e recursividade

```cpp
String lista = file.listAllFiles("/", true, true, true, true);
Serial.println(lista);
```

> **Nota:** Em sistemas como SPIFFS, que não suportam hierarquia de diretórios, o comportamento será equivalente a listar todos os arquivos na raiz, independentemente dos parâmetros `showSubDir` e `openSubDir`.

---

## `String listAllFiles(fs::FS& fs, const String& directory, bool showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false)`

### Descrição

Versão alternativa que permite especificar explicitamente o sistema de arquivos a ser utilizado (ex: `SD`, `LittleFS`, `SPIFFS`).  

### Exemplo com SD

```cpp
String lista = file.listAllFiles(SD, "/logs", true, true, true, false);
Serial.println(lista);
```

### Exemplo com LittleFS e indentacção

```cpp
String lista = file.listAllFiles(LittleFS, "/config", true, true, true, true);
Serial.println(lista);
```

---

## Saída esperada (exemplo com indentacção)

```
/config/
 data.txt  532
 logs/
  log1.txt  120
  log2.txt  334
readme.md  129
```

Neste exemplo:

* O diretório `/config` contém um arquivo e um subdiretório.
* A indentacção diferencia a profundidade dos itens.

---

## Considerações Adicionais

* O método executa ordenação alfabética antes de exibir os resultados.
* Em diretórios com muitos arquivos, o uso de `openSubDir = true` pode afetar o desempenho.
* Em `SPIFFS`, diretórios não são suportados: todos os arquivos aparecerão como se estivessem na raiz.

---

## Exemplo completo

```cpp
file.begin(SD);
String resultado = file.listAllFiles("/", true, true, true, true);
Serial.println(resultado);
```


## Métodos de Verificação de Existência

A classe `ES_File` oferece dois métodos principais para verificação de existência de arquivos ou diretórios:

* `exists()` — Verifica se um arquivo ou diretório existe.
* `directoryExists()` — Verifica especificamente se um diretório existe.

Esses métodos estão disponíveis em duas formas:

1. Utilizando o sistema de arquivos padrão (definido com `begin()`);
2. Informando explicitamente o sistema de arquivos em cada chamada.

---

## `bool exists(const String& path)`

### Descrição

Verifica se um arquivo **ou** diretório existe no sistema de arquivos padrão.

### Parâmetros

* `path`: Caminho completo do arquivo ou pasta (ex: "/data.txt", "/config/").

### Retorno

* `true` se o caminho existir;
* `false` caso contrário.

### Exemplo

```cpp
if (file.exists("/dados.txt")) {
  Serial.println("Arquivo encontrado.");
} else {
  Serial.println("Arquivo não existe.");
}
```

### Versão com sistema de arquivos explícito

```cpp
if (file.exists(SD, "/dados.txt")) {
  Serial.println("Arquivo existe no SD");
}
```

> **Nota:** Para verificar se é um diretório válido (e não apenas um nome), use `directoryExists()`.

---

## `bool directoryExists(const String& directory)`

### Descrição

Verifica se um caminho representa um diretório válido no sistema de arquivos padrão.

### Parâmetros

* `directory`: Caminho do diretório (ex: "/data").

### Retorno

* `true` se o diretório existir;
* `false` caso contrário ou se o sistema de arquivos não suportar diretórios (como o SPIFFS).

### Exemplo

```cpp
if (file.directoryExists("/logs")) {
  Serial.println("Diretório encontrado.");
}
```

### Versão com sistema de arquivos explícito

```cpp
if (file.directoryExists(LittleFS, "/config")) {
  Serial.println("Diretório encontrado em LittleFS");
}
```

> **Atenção:** SPIFFS não suporta hierarquia de pastas. Ao usar esse método com SPIFFS, o retorno será sempre `false`, mesmo que o nome de "diretório" exista como prefixo em nomes de arquivos.

---

## Considerações

* A função `exists()` é genérica e retorna `true` para arquivos ou pastas.
* Use `directoryExists()` se for necessário confirmar especificamente a existência de um diretório.
* Para SPIFFS, evite lógica baseada em diretórios; trate todos os arquivos como se estivessem na raiz.

---

## Exemplo prático

```cpp
file.begin(SPIFFS);

if (file.exists("/config.json")) {
  Serial.println("Arquivo de configuração encontrado.");
} else {
  Serial.println("Arquivo ausente. Criando novo...");
  file.println("/config.json", "{}");
}
```

---


## Método de Remoção Genérica: `remove()`

A classe `ES_File` oferece um método poderoso e versátil chamado `remove()`, que permite apagar:

* Um arquivo específico;
* Todos os arquivos de um diretório (sem apagar o diretório);
* Um diretório inteiro (com todos os seus subdiretórios e arquivos), se `recursive` for `true`.

O comportamento depende de dois fatores:

1. O tipo do sistema de arquivos (ex: SPIFFS não suporta diretórios);
2. O valor do parâmetro `recursive`.

---

## `bool remove(const String& path, bool recursive = false)`

## `bool remove(fs::FS& fs, const String& path, bool recursive = false)`

### Parâmetros

* `path`: Caminho do arquivo ou diretório a ser removido.
* `recursive` (opcional):

  * `false` (padrão): remove apenas arquivos simples ou o conteúdo de um diretório, mantendo a pasta.
  * `true`: remove recursivamente o diretório e todo seu conteúdo.

---

### Comportamento por Tipo de Sistema de Arquivo

#### Em `SPIFFS`

* Se `path` for um arquivo existente: será removido.
* Se `path == "/"`: remove todos os arquivos da raiz.
* Diretórios explícitos não são suportados (SPIFFS trata todos arquivos como estando na raiz).

#### Em `LittleFS` ou `SD`

* Se `path` for arquivo: será removido.
* Se `path` for diretório:

  * `recursive == true`: remove a pasta e todo seu conteúdo.
  * `recursive == false`: remove apenas os arquivos contidos no diretório, mantendo a pasta.

---

### Retorno

* `true` se a operação for bem-sucedida;
* `false` em caso de falha, caminho inexistente ou tipo inválido de operação.

---

### Exemplos

#### 1. Removendo um único arquivo

```cpp
file.remove("/dados.json");
```

#### 2. Removendo todos os arquivos de uma pasta (sem apagar a pasta)

```cpp
file.remove("/logs", false);
```

#### 3. Removendo recursivamente um diretório

```cpp
file.remove("/backup_antigo", true);
```

#### 4. Apagando todos os arquivos da raiz

```cpp
file.remove("/");
```

#### 5. Apagando todos os arquivos do File System escolhido

```cpp
file.remove("/", true);
```

---

## Observações Técnicas

* O método garante que:
  * Arquivos são sempre removidos com segurança.
  * Diretórios vazios não causam falha quando `recursive` é `false`.
  * O uso de `recursive = true` remove subpastas e arquivos em cascata, respeitando a estrutura.

---

## Recomendações

* Evite usar `recursive = true` sem necessidade, principalmente em sistemas com grande volume de dados.
* Prefira limpar diretórios com `recursive = false` quando a estrutura de pastas deve ser mantida.
* Para SPIFFS, lembre-se de que não há suporte para subdiretórios — tudo ocorre na raiz.

---

## Exemplo Completo

```cpp
file.begin(SPIFFS);

// Remove arquivo
file.remove("/config.json");

// Remove todos os arquivos de um diretório
file.remove("/temp", false);

// Remove diretório com conteúdo
file.remove("/temp", true);
```

---

## Métodos de Navegação entre Arquivos

A classe `ES_File` oferece quatro métodos para navegar sequencialmente entre arquivos de um diretório. Todos os métodos listam os arquivos em ordem alfabética e permitem a navegação cíclica (volta ao início/fim se ultrapassado o último/primeiro arquivo).

### **Métodos disponíveis**
- `getFirstFileName()`
- `getLastFileName()`
- `getNextFileName()`
- `getPreviousFileName()`

Cada um desses métodos possui uma versão com sistema de arquivos opcional (`fs::FS&`) e parâmetros que devem seguir exatamente a definição da interface pública presente em `ES_File.h`.

---

## `getFirstFileName()`

```cpp
String getFirstFileName(const String& directory = "/");
String getFirstFileName(fs::FS& fs, const String& directory = "/");
```

Este método retorna o nome do **primeiro arquivo** encontrado no diretório especificado, de acordo com a ordem alfabética dos nomes de arquivos presentes.

### **Parâmetros**
- `directory`: Caminho do diretório a ser pesquisado. Se omitido, considera a raiz (`"/"`).
- `fs` (versão sobrecarregada): Sistema de arquivos a ser utilizado (ex: `LittleFS`, `SPIFFS`, `SD`).

### **Retorno**
- Uma `String` contendo o nome do primeiro arquivo.
- Se o diretório estiver vazio, inexistente ou inacessível, retorna uma string vazia (`""`).

### **Considerações**
- Apenas arquivos são considerados (subpastas são ignoradas).
- O método pode ser usado como ponto inicial para navegação sequencial com `getNextFileName()` e `getPreviousFileName()`.
- Embora seja possível especificar um sistema de arquivos diferente usando a versão sobrecarregada, o padrão recomendado é utilizar `String getFirstFileName(const String& directory = "/");`.

#### **Exemplo**

```cpp
String primeiro = file.getFirstFileName("/logs");
Serial.println("Primeiro arquivo: " + primeiro);

// Usando sistema de arquivos explícito
String primeiroSD = file.getFirstFileName(SD, "/backup");
```

---

## `getLastFileName()`

```cpp
String getLastFileName(const String& directory = "/");
String getLastFileName(fs::FS& fs, const String& directory = "/");
```

Este método retorna o nome do **último arquivo** encontrado no diretório especificado, conforme a ordenação alfabética dos arquivos.

### **Parâmetros**
- `directory`: Caminho do diretório onde a busca será realizada. Se omitido, considera a raiz (`"/"`).
- `fs` (versão sobrecarregada): Sistema de arquivos a ser utilizado (como `LittleFS`, `SPIFFS`, `SD`).

### **Retorno**
- Uma `String` com o nome do último arquivo encontrado em ordem alfabética.
- Retorna uma `String` vazia (`""`) se o diretório estiver vazio, não existir ou não puder ser acessado.

### **Considerações**
- Apenas arquivos são listados. Diretórios são ignorados.
- O resultado pode ser usado como ponto final para navegação com `getPreviousFileName()`.
- Útil para navegação reversa a partir do final de uma lista.

#### **Exemplo**

```cpp
String ultimo = file.getLastFileName("/dados");
Serial.println("Último arquivo: " + ultimo);

// Com sistema de arquivos explícito
String ultimoSD = file.getLastFileName(SD, "/backup");
Serial.println("Último no SD: " + ultimoSD);
```

---

## `getNextFileName()`

```cpp
String getNextFileName(const String& directory = "");
String getNextFileName(fs::FS& fs, const String& directory = "");
```

Este método retorna o nome do **arquivo seguinte**, considerando a ordem alfabética dos arquivos presentes no diretório informado.

### **Parâmetros**
- `directory`: Caminho do diretório a ser pesquisado. Se omitido, considera a raiz (`"/"`).
- `fs` (versão sobrecarregada): Sistema de arquivos a ser utilizado (`SPIFFS`, `LittleFS`, `SD`, etc).

### **Retorno**
- `String` com o nome do próximo arquivo.
- Se o diretório estiver vazio ou não existir, retorna uma string vazia (`""`).

### **Funcionamento**
- Ao ser chamado, o método considera a última referência de navegação feita no diretório informado.
- Se for a primeira chamada ou nenhuma navegação anterior existir, o primeiro arquivo é retornado.
- A navegação é **cíclica**: ao atingir o último arquivo, retorna ao primeiro.

#### **Exemplo**

```cpp
// Navegação sequencial após obter o primeiro
file.getFirstFileName("/dir");
String next = file.getNextFileName();  // Avança para o segundo arquivo

// Navegação baseada em um arquivo específico (modo estático)
String proximo = file.getNextFileName("/dir/file02.txt");  // Retorna o próximo de file02.txt
```

---

## `getPreviousFileName()`

```cpp
String getPreviousFileName(const String& directory = "");
String getPreviousFileName(fs::FS& fs, const String& directory = "");
```

Este método retorna o nome do **arquivo anterior**, com base na posição atual da navegação ou no arquivo informado como referência.

### **Parâmetros**
- `directory`: Diretório onde será realizada a navegação. Caso seja o caminho de um arquivo, a navegação será relativa a ele.
- `fs`: Sistema de arquivos a ser utilizado (`LittleFS`, `SPIFFS` ou `SD`).

### **Retorno**
- `String` com o nome do arquivo anterior (em ordem alfabética).
- Se o diretório estiver vazio ou não existir, retorna string vazia (`""`).

### **Funcionamento**
- Quando chamado com um diretório, a navegação considera a posição atual no ciclo de navegação sequencial.
- Quando chamado com o caminho de um arquivo (ex: `"/dir/file02.txt"`), o método retorna o arquivo que o precede alfabeticamente no mesmo diretório. O resultado é **sempre o mesmo** para a mesma entrada.
- A navegação é **cíclica**: ao alcançar o primeiro arquivo, o anterior será o último.

#### **Exemplo**

```cpp
// Navegação dinâmica com histórico interno
file.getLastFileName("/dir");
String anterior = file.getPreviousFileName();  // Retorna o penúltimo arquivo

// Navegação estática baseada em arquivo fixo
String anteriorFixo = file.getPreviousFileName("/dir/file02.txt");  // Retorna o anterior a file02.txt
```

---

## **Comportamento especial: navegação com arquivo como referência**

Os métodos `getNextFileName("/dir/file.txt")` e `getPreviousFileName("/dir/file.txt")` são válidos e utilizados para obter vizinhos **sem histórico interno de navegação**. Isso significa que:

```cpp
String anterior = file.getPreviousFileName("/dir/file02.txt");
String anterior2 = file.getPreviousFileName("/dir/file02.txt");
```

Ambos os comandos sempre retornarão o **mesmo resultado**, pois o parâmetro define explicitamente a referência.

Essa forma de uso é ideal para interfaces baseadas em seleção fixa (ex: listas de mídia, seletores).

---


### Métodos de Abertura de Arquivos

#### `File getFile(const String& fileName, bool edit = false)`
Este método abre um arquivo no sistema de arquivos padrão previamente definido com `begin()`. Ele permite abrir o arquivo em modo de leitura ou edição (anexação).

**Parâmetros:**
- **`fileName`**: Nome do arquivo a ser aberto (ex.: `"/log.txt"`).
- **`edit`** *(opcional)*: Define se o arquivo será aberto em modo de edição (anexação) ou leitura:
  - `true`: Abre o arquivo em modo de edição (anexação).
  - `false` *(padrão)*: Abre o arquivo em modo de leitura.

**Retorno:**
- Objeto `File` válido se o arquivo foi aberto com sucesso.
- Objeto `File` inválido se a operação falhar.

**Exemplo:**
```cpp
File file = fileManager.getFile("/log.txt", true);
if (file) {
    file.println("Adicionando nova linha ao arquivo.");
    file.close();
} else {
    Serial.println("Falha ao abrir o arquivo.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`File getFile(fs::FS& fs, const String& fileName, bool edit = false)`.

---

### Métodos de Abertura do Primeiro Arquivo em um Diretório

#### `File getFirstFile(const String& directory = "/", bool edit = false)`
Abre o primeiro arquivo encontrado em um diretório no sistema de arquivos padrão.

**Parâmetros:**
- **`directory`** *(opcional)*: Diretório onde a busca será realizada. O padrão é a raiz (`"/"`).
- **`edit`** *(opcional)*: Define se o arquivo será aberto em modo de edição (anexação) ou leitura:
  - `true`: Abre o arquivo em modo de edição (anexação).
  - `false` *(padrão)*: Abre o arquivo em modo de leitura.

**Retorno:**
- Objeto `File` do primeiro arquivo encontrado.
- Objeto `File` inválido se o diretório estiver vazio ou a operação falhar.

**Exemplo:**
```cpp
File file = fileManager.getFirstFile("/logs");
if (file) {
    Serial.println("Primeiro arquivo encontrado:");
    Serial.println(file.name());
    file.close();
} else {
    Serial.println("Nenhum arquivo encontrado no diretório.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`File getFirstFile(fs::FS& fs, const String& directory = "/", bool edit = false)`.

---

### Métodos de Abertura do Último Arquivo em um Diretório

#### `File getLastFile(const String& directory = "/", bool edit = false)`
Abre o último arquivo encontrado em um diretório no sistema de arquivos padrão.

**Parâmetros:**
- **`directory`** *(opcional)*: Diretório onde a busca será realizada. O padrão é a raiz (`"/"`).
- **`edit`** *(opcional)*: Define se o arquivo será aberto em modo de edição (anexação) ou leitura:
  - `true`: Abre o arquivo em modo de edição (anexação).
  - `false` *(padrão)*: Abre o arquivo em modo de leitura.

**Retorno:**
- Objeto `File` do último arquivo encontrado.
- Objeto `File` inválido se o diretório estiver vazio ou a operação falhar.

**Exemplo:**
```cpp
File file = fileManager.getLastFile("/dados");
if (file) {
    Serial.println("Último arquivo encontrado:");
    Serial.println(file.name());
    file.close();
} else {
    Serial.println("Nenhum arquivo encontrado no diretório.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`File getLastFile(fs::FS& fs, const String& directory = "/", bool edit = false)`.

---

### Métodos de Abertura do Próximo Arquivo em um Diretório

#### `File getNextFile(bool edit = false)`
Abre o próximo arquivo encontrado no diretório atual, considerando a ordem alfabética.

**Parâmetros:**
- **`edit`** *(opcional)*: Define se o arquivo será aberto em modo de edição (anexação) ou leitura:
  - `true`: Abre o arquivo em modo de edição (anexação).
  - `false` *(padrão)*: Abre o arquivo em modo de leitura.

**Retorno:**
- Objeto `File` do próximo arquivo encontrado.
- Objeto `File` inválido se não houver mais arquivos no diretório ou a operação falhar.

**Exemplo:**
```cpp
File file = fileManager.getNextFile();
if (file) {
    Serial.println("Próximo arquivo encontrado:");
    Serial.println(file.name());
    file.close();
} else {
    Serial.println("Nenhum próximo arquivo encontrado.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`File getNextFile(fs::FS& fs, bool edit = false)`.

---

### Métodos de Abertura do Arquivo Anterior em um Diretório

#### `File getPreviousFile(bool edit = false)`
Abre o arquivo anterior encontrado no diretório atual, considerando a ordem alfabética.

**Parâmetros:**
- **`edit`** *(opcional)*: Define se o arquivo será aberto em modo de edição (anexação) ou leitura:
  - `true`: Abre o arquivo em modo de edição (anexação).
  - `false` *(padrão)*: Abre o arquivo em modo de leitura.

**Retorno:**
- Objeto `File` do arquivo anterior encontrado.
- Objeto `File` inválido se não houver mais arquivos no diretório ou a operação falhar.

**Exemplo:**
```cpp
File file = fileManager.getPreviousFile();
if (file) {
    Serial.println("Arquivo anterior encontrado:");
    Serial.println(file.name());
    file.close();
} else {
    Serial.println("Nenhum arquivo anterior encontrado.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`File getPreviousFile(fs::FS& fs, bool edit = false)`.

---

### Métodos de Criação de Diretórios

#### `bool createDirectory(const String& directory)`
Este método cria um diretório no sistema de arquivos padrão previamente definido com `begin()`.

**Parâmetros:**
- **`directory`**: Caminho do diretório a ser criado (ex.: `"/config"`).

**Retorno:**
- **`true`**: Se o diretório foi criado com sucesso.
- **`false`**: Se a operação falhar, como no caso de o diretório já existir ou o sistema de arquivos não estar inicializado.

**Exemplo:**
```cpp
if (fileManager.createDirectory("/config")) {
    Serial.println("Diretório criado com sucesso.");
} else {
    Serial.println("Falha ao criar o diretório.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`bool createDirectory(fs::FS& fs, const String& directory)`.

---

### Métodos de Movimentação ou Renomeação de Arquivos/Diretórios

#### `bool move(const String& sourcePath, const String& destinationPath)`
Este método move ou renomeia um arquivo ou diretório no sistema de arquivos padrão.

**Parâmetros:**
- **`sourcePath`**: Caminho do arquivo ou diretório de origem (ex.: `"/dados/arquivo.txt"`).
- **`destinationPath`**: Caminho do arquivo ou diretório de destino (ex.: `"/backup/arquivo.txt"`).

**Retorno:**
- **`true`**: Se a operação foi bem-sucedida.
- **`false`**: Se a operação falhar, como no caso de o arquivo de origem não existir ou o destino já existir.

**Nota:** Se o caminho de origem e destino forem iguais, a operação falhará.

**Exemplo:**
```cpp
if (fileManager.move("/dados/arquivo.txt", "/backup/arquivo.txt")) {
    Serial.println("Arquivo movido com sucesso.");
} else {
    Serial.println("Falha ao mover o arquivo.");
}
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`bool move(fs::FS& fs, const String& sourcePath, const String& destinationPath)`.

---

### Métodos de Cópia de Arquivos

#### `bool copy(const String& sourceFileName, const String& destFileName)`
Este método copia um arquivo dentro do mesmo sistema de arquivos padrão.

**Parâmetros:**
- **`sourceFileName`**: Nome do arquivo de origem (ex.: `"/dados/origem.txt"`).
- **`destFileName`**: Nome do arquivo de destino (ex.: `"/backup/destino.txt"`).

**Retorno:**
- **`true`**: Se a cópia foi bem-sucedida.
- **`false`**: Se a operação falhar, como no caso de o arquivo de origem não existir.

**Nota:** Este método não suporta copiar arquivos entre SPIFFS e LittleFS.

**Exemplo:**
```cpp
if (fileManager.copy("/dados/origem.txt", "/backup/destino.txt")) {
    Serial.println("Arquivo copiado com sucesso.");
} else {
    Serial.println("Falha ao copiar o arquivo.");
}
```

---

#### `bool copy(const String& sourceFileName, fs::FS& destFS, const String& destFileName)`
Este método copia um arquivo do sistema de arquivos padrão para outro sistema de arquivos especificado.

**Parâmetros:**
- **`sourceFileName`**: Nome do arquivo de origem (ex.: `"/dados/origem.txt"`).
- **`destFS`**: Sistema de arquivos de destino (ex.: `SD`).
- **`destFileName`**: Nome do arquivo de destino (ex.: `"/backup/destino.txt"`).

**Retorno:**
- **`true`**: Se a cópia foi bem-sucedida.
- **`false`**: Se a operação falhar.

**Nota:** Este método não suporta copiar arquivos entre SPIFFS e LittleFS.

**Exemplo:**
```cpp
if (fileManager.copy("/dados/origem.txt", SD, "/backup/destino.txt")) {
    Serial.println("Arquivo copiado para o SD com sucesso.");
} else {
    Serial.println("Falha ao copiar o arquivo para o SD.");
}
```

---

#### `bool copy(fs::FS& sourceFS, const String& sourceFileName, fs::FS& destFS, const String& destFileName)`
Este método copia um arquivo entre dois sistemas de arquivos especificados.

**Parâmetros:**
- **`sourceFS`**: Sistema de arquivos de origem (ex.: `SPIFFS`).
- **`sourceFileName`**: Nome do arquivo de origem (ex.: `"/dados/origem.txt"`).
- **`destFS`**: Sistema de arquivos de destino (ex.: `SD`).
- **`destFileName`**: Nome do arquivo de destino (ex.: `"/backup/destino.txt"`).

**Retorno:**
- **`true`**: Se a cópia foi bem-sucedida.
- **`false`**: Se a operação falhar.

**Nota:** Este método não suporta copiar arquivos entre SPIFFS e LittleFS.

**Exemplo:**
```cpp
if (fileManager.copy(SPIFFS, "/dados/origem.txt", SD, "/backup/destino.txt")) {
    Serial.println("Arquivo copiado entre sistemas de arquivos com sucesso.");
} else {
    Serial.println("Falha ao copiar o arquivo entre sistemas de arquivos.");
}
```

---

### Métodos de Informações sobre Espaço no Sistema de Arquivos

#### `size_t getTotalSpace()`
Obtém o espaço total disponível no sistema de arquivos padrão previamente definido com `begin()`.

**Retorno:**
- O espaço total em bytes.

**Exemplo:**
```cpp
size_t totalSpace = fileManager.getTotalSpace();
Serial.print("Espaço total: ");
Serial.print(totalSpace);
Serial.println(" bytes");
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`size_t getTotalSpace(fs::FS& fs)`.

---

#### `size_t getUsedSpace(const String& directory = "/", bool includeSubDirs = true)`
Obtém o espaço usado no sistema de arquivos padrão, considerando um diretório específico e, opcionalmente, seus subdiretórios.

**Parâmetros:**
- **`directory`** *(opcional)*: Diretório a ser verificado. O padrão é a raiz (`"/"`).
- **`includeSubDirs`** *(opcional)*: Define se os subdiretórios devem ser incluídos no cálculo. O padrão é `true`.

**Retorno:**
- O espaço usado em bytes.

**Exemplo:**
```cpp
size_t usedSpace = fileManager.getUsedSpace("/dados");
Serial.print("Espaço usado: ");
Serial.print(usedSpace);
Serial.println(" bytes");
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`size_t getUsedSpace(fs::FS& fs, const String& directory = "/", bool includeSubDirs = true)`.

---

#### `size_t getAvailableSpace()`
Obtém o espaço disponível no sistema de arquivos padrão previamente definido com `begin()`.

**Retorno:**
- O espaço disponível em bytes.

**Exemplo:**
```cpp
size_t availableSpace = fileManager.getAvailableSpace();
Serial.print("Espaço disponível: ");
Serial.print(availableSpace);
Serial.println(" bytes");
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`size_t getAvailableSpace(fs::FS& fs)`.

---

### Métodos de Informações sobre Arquivos

#### `size_t getFileSize(const String& fileName)`
Obtém o tamanho de um arquivo no sistema de arquivos padrão.

**Parâmetros:**
- **`fileName`**: Nome do arquivo a ser verificado (ex.: `"/dados/arquivo.txt"`).

**Retorno:**
- O tamanho do arquivo em bytes.

**Exemplo:**
```cpp
size_t fileSize = fileManager.getFileSize("/dados/arquivo.txt");
Serial.print("Tamanho do arquivo: ");
Serial.print(fileSize);
Serial.println(" bytes");
```

**Nota:** Também é possível especificar diretamente o sistema de arquivos utilizando a versão sobrecarregada do método:  
`size_t getFileSize(fs::FS& fs, const String& fileName)`.

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
    String content = fileManager.read(fileName);
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