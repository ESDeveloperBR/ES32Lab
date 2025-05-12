/**
* @brief This example demonstrates how to use the `copy` method from the ES_File class to copy files between two different file systems.
* The example uses SD as the source file system and LittleFS as the destination, but it can be adapted to work with other file systems such as SPIFFS.
* | Este exemplo demonstra como usar o método `copy` da classe ES_File para copiar arquivos entre dois sistemas de arquivos diferentes.
* O exemplo utiliza o SD como sistema de arquivos de origem e o LittleFS como destino, mas pode ser adaptado para funcionar com outros sistemas de arquivos, como SPIFFS.
*
* @details The example initializes the file system (SD in this case) using `fileManager.begin(SD)`, ensuring that the SD card is inserted in the slot; otherwise, the program will not proceed.
* It demonstrates the use of the `println` method to create and write to a file, with optional return value analysis. 
* Afterward, the `copy` method is used to copy the file from SD to LittleFS. The results of each operation are analyzed with pauses between steps to allow for observation.
* Additionally, the example highlights the flexibility of the ES_File class, showing that methods can operate on file systems other than the one initialized in `begin`.
* | O exemplo inicializa o sistema de arquivos (SD neste caso) usando `fileManager.begin(SD)`, garantindo que o cartão SD esteja inserido no slot; caso contrário, o programa não prosseguirá.
* Ele demonstra o uso do método `println` para criar e escrever em um arquivo, com análise opcional do valor de retorno.
* Em seguida, o método `copy` é usado para copiar o arquivo do SD para o LittleFS. Os resultados de cada operação são analisados com pausas entre as etapas para permitir a observação.
* Além disso, o exemplo destaca a flexibilidade da classe ES_File, mostrando que os métodos podem operar em sistemas de arquivos diferentes do inicializado no `begin`.
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
    // fileManager.begin(LittleFS);    // Initializes the file system (LittleFS in this case) | Inicializa o sistema de arquivos (LittleFS neste caso)

    // This is a safe way to initialize the file system, as it creates a loop that tries to initialize the file system until it succeeds.
    // | Esta é uma maneira segura de inicializar o sistema de arquivos, pois cria um loop que tenta inicializar o sistema de arquivos até que tenha sucesso.
    while(!fileManager.begin(SD)) { // Initializes the file system (SD in this case) | Inicializa o sistema de arquivos (SD neste caso)
        Serial.println("EN: Failed to initialize file system.");    // Prints a message if the file system initialization fails | Imprime uma mensagem se a inicialização do sistema de arquivos falhar
        Serial.println("PT: Falha ao inicializar o sistema de arquivos.");    // Prints a message if the file system initialization fails | Imprime uma mensagem se a inicialização do sistema de arquivos falhar
        delay(1000); // Waits for 1 second before retrying | Aguarda 1 segundo antes de tentar novamente
    }
    Serial.println("EN: File system initialized successfully."); // Prints a message if the file system initialization is successful | Imprime uma mensagem se a inicialização do sistema de arquivos for bem-sucedida
    Serial.println("PT: Sistema de arquivos inicializado com sucesso."); // Prints a message if the file system initialization is successful | Imprime uma mensagem se a inicialização do sistema de arquivos for bem-sucedida


    // println(fileName, content, createNew, decimalPlaces);
    // Writes a line of text to a file with a newline character. 
    //| Escreve uma linha de texto em um arquivo com um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    if(fileManager.println("/file01.txt", "File generated from SD.", true)) { // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/file01.txt").
        Serial.println("EN: File created successfully."); // Prints a success message | Imprime uma mensagem de sucesso
        Serial.println("PT: Arquivo criado com sucesso."); // Prints a success message | Imprime uma mensagem de sucesso
    } else {
        Serial.println("EN: Failed to create file."); // Prints a failure message | Imprime uma mensagem de falha
        Serial.println("PT: Falha ao criar arquivo."); // Prints a failure message | Imprime uma mensagem de falha
    }
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo

    
    Serial.println("--- Lists the files in the root directory of the SD ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("fileManager.listAllFiles(\"/\");"); // Prints the command to list all files | Imprime o comando para listar todos os arquivos
    // listAllFiles(directory, showFileSize = false, showSubDir = true, openSubDir = true, indentation = false);    
    // Lists all files in a directory (sorted alphabetically).
    // | Lista todos os arquivos em um diretório (ordenados alfabeticamente).
    // @param fs File system to use. | Sistema de arquivos a ser usado.
    // @param directory Directory to list. | Diretório a ser listado.
    // @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
    // @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
    // @param openSubDir Whether to open subdirectories (recursive listing). | Se deve abrir subdiretórios (listagem recursiva).
    // @param indentation Whether to use indentation. If false, full file paths are displayed. | Se deve usar indentação. Se false, os caminhos completos dos arquivos são exibidos.
    // @return String containing the file list. | String contendo a lista de arquivos.
    String listAllFiles;    // Variable to store the list of files | Variável para armazenar a lista de arquivos
    listAllFiles = fileManager.listAllFiles("/"); // Lists the files in the root directory of the SD | Lista os arquivos no diretório raiz do SD
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    Serial.println("EN: WARNING: Note that the file /file01.txt was created on the SD and NOT on LittleFS."); // Prints a warning message
    Serial.println("PT: ATENÇÃO: Note que o arquivo /file01.txt foi criado no SD e NÃO no LittleFS."); // Prints a warning message
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Lists the files in the root directory of the LittleFS ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("fileManager.listAllFiles(LittleFS, \"/\");"); // Prints the command to list all files | Imprime o comando para listar todos os arquivos
    listAllFiles = fileManager.listAllFiles(LittleFS, "/"); // Lists the files in the root directory of the LittleFS | Lista os arquivos no diretório raiz do LittleFS
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    Serial.println("EN: WARNING: Note that LittleFS does NOT have the file /file01.txt, as it was created on the SD and not on LittleFS."); // Prints a warning message | Imprime uma mensagem de aviso
    Serial.println("PT: ATENÇÃO: Note que o LittleFS NÃO tem o arquivo /file01.txt, pois foi criado no SD e não no LittleFS."); // Prints a warning message | Imprime uma mensagem de aviso
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Copies the file (/file01.txt) from SD to (/file01_copy.txt) in LittleFS ---"); // Prints a separator line
    Serial.println("fileManager.copy(\"/file01.txt\", LittleFS, \"/file01_copy.txt\");\n"); // Prints the copy command | Imprime o comando de cópia
    // copy(sourceFileName, destFileName);
    // Copies a file from one file system to another.
    // | Copia um arquivo de um sistema de arquivos para outro.
    // @param sourceFS Source file system. | Sistema de arquivos de origem.
    // @param sourceFileName Source file name. | Nome do arquivo de origem.
    // @param destFS Destination file system. | Sistema de arquivos de destino.
    // @param destFileName Destination file name. | Nome do arquivo de destino.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    // @note This method does not support copying files between SPIFFS and LittleFS. | Este método não suporta copiar arquivos entre SPIFFS e LittleFS.
    boolean result = fileManager.copy("/file01.txt", LittleFS, "/file01_copy.txt"); // Copies the file from SD to LittleFS | Copia o arquivo do SD para o LittleFS
    if(result) {    // Checks if the copy was successful | Verifica se a cópia foi bem-sucedida
        Serial.println("EN: File copied successfully."); // Prints a success message | Imprime uma mensagem de sucesso
        Serial.println("PT: Arquivo copiado com sucesso."); // Prints a success message | Imprime uma mensagem de sucesso
    } else {
        Serial.println("EN: Failed to copy File."); // Prints a failure message | Imprime uma mensagem de falha
        Serial.println("PT: Falha ao copiar arquivo."); // Prints a failure message | Imprime uma mensagem de falha
    }
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    Serial.println("--- Lists the files in the root directory of the LittleFS ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("fileManager.listAllFiles(LittleFS, \"/\");"); // Prints the command to list all files | Imprime o comando para listar todos os arquivos
    listAllFiles = fileManager.listAllFiles(LittleFS, "/"); // Lists the files in the root directory of the LittleFS | Lista os arquivos no diretório raiz do LittleFS
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial
    
    Serial.println("EN: WARNING: Note that the file /file01.txt was created on the SD and COPIED to LittleFS as /file01_copy.txt."); // Prints a warning message | Imprime uma mensagem de aviso
    Serial.println("PT: ATENÇÃO: Note que o arquivo /file01.txt foi criado no SD e COPIADO para o LittleFS como /file01_copy.txt."); // Prints a warning message | Imprime uma mensagem de aviso
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Removes the file (/file01_copy.txt) from LittleFS ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("fileManager.remove(LittleFS, \"/file01_copy.txt\");"); // Prints the command to remove the file | Imprime o comando para remover o arquivo
    if(fileManager.remove(LittleFS, "/file01_copy.txt")) {    // Removes the file from LittleFS | Remove o arquivo do LittleFS
        Serial.println("EN: File removed successfully."); // Prints a success message | Imprime uma mensagem de sucesso
        Serial.println("PT: Arquivo removido com sucesso."); // Prints a success message | Imprime uma mensagem de sucesso
    } else {
        Serial.println("EN: Failed to remove File."); // Prints a failure message | Imprime uma mensagem de falha
        Serial.println("PT: Falha ao remover arquivo."); // Prints a failure message | Imprime uma mensagem de falha
    }
    
    Serial.println(); // Prints a separator line | Imprime uma linha separadora
    
    Serial.println("--- Removes the file (/file01.txt) from SD ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("fileManager.remove(\"/file01.txt\");"); // Prints the command to remove the file | Imprime o comando para remover o arquivo
    if(fileManager.remove("/file01.txt")) {    // Removes the file from SD | Remove o arquivo do SD
        Serial.println("EN: File removed successfully."); // Prints a success message | Imprime uma mensagem de sucesso
        Serial.println("PT: Arquivo removido com sucesso."); // Prints a success message | Imprime uma mensagem de sucesso
    } else {
        Serial.println("EN: Failed to remove File."); // Prints a failure message | Imprime uma mensagem de falha
        Serial.println("PT: Falha ao remover arquivo."); // Prints a failure message | Imprime uma mensagem de falha
    }

    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
}

void loop() {

}