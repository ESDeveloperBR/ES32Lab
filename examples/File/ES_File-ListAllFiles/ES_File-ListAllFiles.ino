/**
* @brief This example demonstrates the usage of the `listAllFiles` method from the ES_File class to list files and directories.
* It showcases various configurations, such as displaying file sizes, including subdirectories, and enabling recursive listing with indentation.
* | Este exemplo demonstra o uso do método `listAllFiles` da classe ES_File para listar arquivos e diretórios.
* Ele apresenta várias configurações, como exibir tamanhos de arquivos, incluir subdiretórios e habilitar listagem recursiva com indentação.
*
* @details The example initializes the file system (SD in this case), creates a directory structure with files, 
* and then lists the files and directories using the `listAllFiles` method. Different configurations are demonstrated, 
* such as showing file sizes, including/excluding subdirectories, and enabling/disabling recursive listing.
* | O exemplo inicializa o sistema de arquivos (SD neste caso), cria uma estrutura de diretórios com arquivos 
* e, em seguida, lista os arquivos e diretórios usando o método `listAllFiles`. São demonstradas diferentes configurações, 
* como exibir tamanhos de arquivos, incluir/excluir subdiretórios e habilitar/desabilitar listagem recursiva.
*
* @warning Ensure that the ES32Lab library (https://github.com/ESDeveloperBR/ES32Lab) is installed and properly configured.
* | Certifique-se de que a biblioteca ES32Lab (https://github.com/ESDeveloperBR/ES32Lab) esteja instalada e configurada corretamente.
* 
* @note This example can be adapted to work with other file systems, such as LittleFS or SD, by changing the parameter 
* in the `fileManager.begin()` method.
* | Este exemplo pode ser adaptado para funcionar com outros sistemas de arquivos, como LittleFS ou SD, alterando o parâmetro 
* no método `fileManager.begin()`.
* 
* @see Official documentation: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_File/README.md
* | Documentação oficial: https://github.com/ESDeveloperBR/ES32Lab/blob/main/src/ES_File/README.md
* 
* @see Official board: https://www.esdeveloper.com.br
* | Placa oficial disponível em: https://www.esdeveloper.com.br
*/

#include <Arduino.h>    // Library for Arduino core functions | Biblioteca para funções principais do Arduino
#include <ES32Lab.h>    // Library used to facilitate the use of the ES32Lab board | Biblioteca usada para facilitar o uso da placa ES32Lab

ES_File fileManager;    // Instantiates the 'fileManager' object derived from the 'ES_File' class. | Instancia o objeto 'fileManager' derivado da classe 'ES_File'.

void setup() {
    Serial.begin(115200);   // Initializes serial communication at 115200 baud rate | Inicializa a comunicação serial a 115200 bps

    // File System is a structure that allows organizing, storing, and accessing data on storage devices.
    // | File System (Sistema de Arquivos) é uma estrutura que permite organizar, armazenar e acessar dados em dispositivos de armazenamento.
    // - SD: Used for SD cards, ideal for large volumes of data. | SD: Usado para cartões SD, ideal para grandes volumes de dados.
    // - LittleFS: A lightweight and efficient file system designed for flash memory. | LittleFS: Um sistema de arquivos leve e eficiente projetado para memória flash.
    // - SPIFFS: A simple file system for flash memory, but with fewer features than LittleFS. | SPIFFS: Um sistema de arquivos simples para memória flash, mas com menos recursos que o LittleFS.
    // The `fileManager.begin()` method initializes the chosen file system. | O método `fileManager.begin()` inicializa o sistema de arquivos escolhido.
    // The parameter can be SD, SPIFFS, or LittleFS. | O parâmetro pode ser SD, SPIFFS ou LittleFS.
    // fileManager.begin(SD);    // Initializes the file system (SD in this case) | Inicializa o sistema de arquivos (SD neste caso)

    // This is a safe way to initialize the file system, as it creates a loop that tries to initialize the file system until it succeeds.
    // | Esta é uma maneira segura de inicializar o sistema de arquivos, pois cria um loop que tenta inicializar o sistema de arquivos até que tenha sucesso.
    while(!fileManager.begin(SD)) { // Initializes the file system (SD in this case) | Inicializa o sistema de arquivos (SD neste caso)
        Serial.println("Failed to initialize file system.");    // Prints a message if the file system initialization fails | Imprime uma mensagem se a inicialização do sistema de arquivos falhar
        delay(1000); // Waits for 1 second before retrying | Aguarda 1 segundo antes de tentar novamente
    }

    // println(fileName, content, createNew, decimalPlaces);
    // Writes a line of text to a file with a newline character. 
    //| Escreve uma linha de texto em um arquivo com um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    fileManager.println("/dir/file01.txt", "Symbolic content of the file. (1)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file02.txt", "Symbolic content of the file. (12)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file03.txt", "Symbolic content of the file. (123)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/subDir/file04.txt", "Symbolic content of the file. (1234)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").

    // listAllFiles(directory, showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false);    
    // Lists all files in a directory (sorted alphabetically).
    // | Lista todos os arquivos em um diretório (ordenados alfabeticamente).
    // @param directory Directory to list. | Diretório a ser listado.
    // @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
    // @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
    // @param openSubDir Whether to open subdirectories (recursive listing). | Se deve abrir subdiretórios (listagem recursiva).
    // @param indentation Whether to use indentation. If false, full file paths are displayed. | Se deve usar indentação. Se false, os caminhos completos dos arquivos são exibidos.
    // @return String containing the file list. | String contendo a lista de arquivos.
    String listAllFiles;    // Variable to store the list of files | Variável para armazenar a lista de arquivos
    Serial.println("--- Ex.1 List All Files (/dir): Default parameters ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir"); // List all files in the directory "/dir" with default parameters. | Lista todos os arquivos no diretório "/dir" com parâmetros padrão.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    Serial.println("EN: This example shows the default parameters of the `listAllFiles` method."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: Este exemplo mostra os parâmetros padrão do método `listAllFiles`."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo

    
    Serial.println("--- Ex.2 List All Files (/dir): showFileSize = true ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true); // List all files in the directory "/dir" with file sizes. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    Serial.println("EN: The parameter `showFileSize = true` that shows the file sizes."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: O parâmetro `showFileSize = true` que mostra os tamanhos dos arquivos."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Ex.3 List All Files (/dir): showFileSize = true, showSubdir = true, openSubDir = false ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true, true, false); // List all files in the directory "/dir" with file sizes and subdirectories, but without opening subdirectories. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos e subdiretórios, mas sem abrir subdiretórios.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    Serial.println("EN: The parameters `showFileSize = true`, `showSubdir = true` and `openSubDir = false` that shows the file sizes and subdirectories, but does not open subdirectories."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: Os parâmetros `showFileSize = true`, `showSubdir = true` e `openSubDir = false` que mostram os tamanhos dos arquivos e subdiretórios, mas não abrem subdiretórios."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Ex.4 List All Files (/dir): showFileSize = true, showSubdir = false, openSubDir = false ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true, false, false); // List all files in the directory "/dir" with file sizes, but without subdirectories and without opening subdirectories. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos, mas sem subdiretórios e sem abrir subdiretórios.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    Serial.println("EN: The parameters `showFileSize = true`, `showSubdir = false` and `openSubDir = false` that shows the file sizes, but does not show subdirectories and does not open subdirectories."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: Os parâmetros `showFileSize = true`, `showSubdir = false` e `openSubDir = false` que mostram os tamanhos dos arquivos, mas não mostram subdiretórios e não abrem subdiretórios."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo

    Serial.println("--- EX.5 List All Files (/dir): showFileSize = true, showSubdir = true, openSubDir = true, indentation = true ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true, true, true, true); // List all files in the directory "/dir" with file sizes, subdirectories, and indentation. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos, subdiretórios e indentação.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    Serial.println("EN: The parameters `showFileSize = true`, `showSubdir = true`, `openSubDir = true` and `indentation = true` that shows the file sizes, subdirectories, opens subdirectories and uses indentation."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: Os parâmetros `showFileSize = true`, `showSubdir = true`, `openSubDir = true` e `indentation = true` que mostram os tamanhos dos arquivos, subdiretórios, abrem subdiretórios e usam indentação."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo

    Serial.println("=== Display all files in the root ==="); // Prints a separator line | Imprime uma linha separadora
    Serial.println("--- EX.6 List All Files (/): showFileSize = false, showSubdir = true, openSubDir = true, indentation = true ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/", false, true, true, true); // List all files in the root directory with subdirectories and indentation. | Lista todos os arquivos no diretório raiz com subdiretórios e indentação.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    Serial.println("EN: The parameters `showFileSize = false`, `showSubdir = true`, `openSubDir = true` and `indentation = true` that does not show file sizes, shows subdirectories, opens subdirectories and uses indentation."); // Prints a message in English | Imprime uma mensagem em inglês
    Serial.println("PT: Os parâmetros `showFileSize = false`, `showSubdir = true`, `openSubDir = true` e `indentation = true` que não mostram tamanhos de arquivos, mostram subdiretórios, abrem subdiretórios e usam indentação."); // Prints a message in Portuguese | Imprime uma mensagem em português
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora

}

void loop() {

}