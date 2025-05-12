/**
* @brief This example demonstrates how to use the `remove` method from the ES_File class to delete files, directories, or their contents.
* The example highlights the flexibility of the `remove` method, including recursive deletion and its application to different file systems.
* | Este exemplo demonstra como usar o método `remove` da classe ES_File para excluir arquivos, diretórios ou seus conteúdos.
* O exemplo destaca a flexibilidade do método `remove`, incluindo exclusão recursiva e sua aplicação em diferentes sistemas de arquivos.
*
* @details The example initializes the file system (LittleFS in this case) using `fileManager.begin(LittleFS)`. 
* It demonstrates the creation of files and directories, followed by various use cases of the `remove` method:
* - Deleting a single file.
* - Deleting all files in a directory without affecting subdirectories (non-recursive).
* - Deleting all files in a directory and its subdirectories (recursive).
* - Listing files before and after each operation to observe the results.
* Additionally, the example shows how to delete all files in the root directory using `remove("/", true)`.
* | O exemplo inicializa o sistema de arquivos (LittleFS neste caso) usando `fileManager.begin(LittleFS)`.
* Ele demonstra a criação de arquivos e diretórios, seguido por vários casos de uso do método `remove`:
* - Exclusão de um único arquivo.
* - Exclusão de todos os arquivos em um diretório sem afetar subdiretórios (não-recursivo).
* - Exclusão de todos os arquivos em um diretório e seus subdiretórios (recursivo).
* - Listagem de arquivos antes e depois de cada operação para observar os resultados.
* Além disso, o exemplo mostra como excluir todos os arquivos no diretório raiz usando `remove("/", true)`.
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
    while(!fileManager.begin(LittleFS)) { // Initializes the file system (LittleFS in this case) | Inicializa o sistema de arquivos (LittleFS neste caso)
        Serial.println("Failed to initialize file system.");    // Prints a message if the file system initialization fails | Imprime uma mensagem se a inicialização do sistema de arquivos falhar
        delay(1000); // Waits for 1 second before retrying | Aguarda 1 segundo antes de tentar novamente
    }
    Serial.println("File system initialized successfully."); // Prints a message if the file system initialization is successful | Imprime uma mensagem se a inicialização do sistema de arquivos for bem-sucedida


    // println(fileName, content, createNew, decimalPlaces);
    // Writes a line of text to a file with a newline character. 
    //| Escreve uma linha de texto em um arquivo com um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    fileManager.println("/file01.txt", "Symbolic content of the file. (1)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file02.txt", "Symbolic content of the file. (12)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file03.txt", "Symbolic content of the file. (123)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/subDir/file04.txt", "Symbolic content of the file. (1234)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/subDir/file05.txt", "Symbolic content of the file. (12345)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").

    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo
    

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
    Serial.println("--- Lists the files in the directory (/) ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/"); // Lists all files in the root directory | Lista todos os arquivos no diretório raiz
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    Serial.println("EN: ATTENTION: Note all the created files and directories."); // Prints a message indicating that all files and directories were created | Imprime uma mensagem indicando que todos os arquivos e diretórios foram criados
    Serial.println("PT: ATENÇÃO: Observe todos os arquivos criados e diretórios."); // Prints a message indicating that all files and directories were created | Imprime uma mensagem indicando que todos os arquivos e diretórios foram criados
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    // remove(path, recursive);
    // Removes a file, all files in a directory, or a directory and its contents.
    // | Remove um arquivo, todos os arquivos em um diretório ou um diretório e seu conteúdo.
    // @param path Path to the file or directory to remove. | Caminho para o arquivo ou diretório a ser removido.
    // @param recursive If true, removes directories and their contents recursively. | Se verdadeiro, remove diretórios e seus conteúdos recursivamente.
    // @return True if the operation was successful, false otherwise. | Verdadeiro se a operação foi bem-sucedida, falso caso contrário.
    // @note For SPIFFS, directories are not supported, so all files are treated as being in the root. | Para SPIFFS, diretórios não são suportados, então todos os arquivos são tratados como estando na raiz.
    // @attention If it is requested to remove the files from a directory, the directory exists and is empty, TRUE will be returned. | Se for solicitado remover os arquivos de um diretório, o diretório existe e está vazio, TRUE será retornado.
    Serial.println("--- Remove only the file (/file01.txt) ---"); // Prints a separator line | Imprime uma linha separadora
    if(fileManager.remove("/file01.txt")) { // Removes the file "/file01.txt" | Remove o arquivo "/file01.txt"
        Serial.println("EN: The file /file01.txt was removed."); // Prints a message indicating that the file was removed | Imprime uma mensagem indicando que o arquivo foi removido
        Serial.println("PT: O arquivo /file01.txt foi removido."); // Prints a message indicating that the file was removed | Imprime uma mensagem indicando que o arquivo foi removido
    } else {
        Serial.println("EN: The file /file01.txt was not removed."); // Prints a message indicating that the file was not removed | Imprime uma mensagem indicando que o arquivo não foi removido
        Serial.println("PT: O arquivo /file01.txt não foi removido."); // Prints a message indicating that the file was not removed | Imprime uma mensagem indicando que o arquivo não foi removido
    }
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    Serial.println("--- Lists the files in the directory (/) ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println(fileManager.listAllFiles("/")); // Lists all files in the root directory | Lista todos os arquivos no diretório raiz
    Serial.println("EN: Note that only the file /file01.txt was removed."); // Prints a message indicating that only the file was removed | Imprime uma mensagem indicando que apenas o arquivo foi removido
    Serial.println("PT: Note que apenas o arquivo /file01.txt foi removido."); // Prints a message indicating that only the file was removed | Imprime uma mensagem indicando que apenas o arquivo foi removido
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Removes the files in the directory (/dir) ---"); // Prints a separator line | Imprime uma linha separadora
    if(fileManager.remove("/dir")) { // Removes the files in the "/dir" directory | Remove os arquivos no diretório "/dir"
        Serial.println("EN: The files in the /dir directory were removed."); // Prints a message indicating that the files were removed | Imprime uma mensagem indicando que os arquivos foram removidos
        Serial.println("PT: Os arquivos no diretório /dir foram removidos."); // Prints a message indicating that the files were removed | Imprime uma mensagem indicando que os arquivos foram removidos
    } else {
        Serial.println("EN: The files in the /dir directory were not removed."); // Prints a message indicating that the files were not removed | Imprime uma mensagem indicando que os arquivos não foram removidos
        Serial.println("PT: Os arquivos no diretório /dir não foram removidos."); // Prints a message indicating that the files were not removed | Imprime uma mensagem indicando que os arquivos não foram removidos
    }
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    Serial.println("--- Lists the files in the directory (/) ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println(fileManager.listAllFiles("/")); // Lists all files in the root directory | Lista todos os arquivos no diretório raiz
    Serial.println("EN: Note that only the files in the /dir directory were removed, the subdirectory remains. This happens due to the parameter 'recursive = false'."); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    Serial.println("PT: Note que apenas os arquivos no diretório /dir foram removidos, o subdiretório permanece. Isso acontece devido ao parâmetro 'recursive = false'."); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Removes the files in the directory (/dir) and its subdirectory ---"); // Prints a separator line | Imprime uma linha separadora
    if(fileManager.remove("/dir", true)) { // Removes the files in the "/dir" directory and its subdirectory | Remove os arquivos no diretório "/dir" e seu subdiretório
        Serial.println("EN: The files in the /dir directory and its subdirectory were removed. This happens due to the parameter 'recursive = true'"); // Prints a message indicating that the files were removed | Imprime uma mensagem indicando que os arquivos foram removidos
        Serial.println("PT: Os arquivos no diretório /dir e seu subdiretório foram removidos. Isso acontece devido ao parâmetro 'recursive = true'"); // Prints a message indicating that the files were removed | Imprime uma mensagem indicando que os arquivos foram removidos
    } else {
        Serial.println("EN: The files in the /dir directory and its subdirectory were not removed."); // Prints a message indicating that the files were not removed | Imprime uma mensagem indicando que os arquivos não foram removidos
        Serial.println("PT: Os arquivos no diretório /dir e seu subdiretório não foram removidos."); // Prints a message indicating that the files were not removed | Imprime uma mensagem indicando que os arquivos não foram removidos
    }
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    Serial.println("--- Lists the files in the directory (/) ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println(fileManager.listAllFiles("/")); // Lists all files in the root directory | Lista todos os arquivos no diretório raiz
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    //if(fileManager.remove("/", true)) { // Removes all files in the root directory | Remove todos os arquivos no diretório raiz
    //    Serial.println("EN: All files in the root directory were removed."); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    //    Serial.println("PT: Todos os arquivos no diretório raiz foram removidos."); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    //} else {
    //    Serial.println("EN: All files in the root directory were not removed."); // Prints a message indicating that all files were not removed | Imprime uma mensagem indicando que todos os arquivos não foram removidos
    //    Serial.println("PT: Todos os arquivos no diretório raiz não foram removidos."); // Prints a message indicating that all files were not removed | Imprime uma mensagem indicando que todos os arquivos não foram removidos
    //}
    Serial.println("ES: WARNING: If you want to DELETE all the content of the file system, just use the method 'remove(\"/\", true)'"); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    Serial.println("PT: AVISO: Se você quiser APAGAR todo o conteúdo do sistema de arquivos, basta usar o método 'remove(\"/\", true)'"); // Prints a message indicating that all files were removed | Imprime uma mensagem indicando que todos os arquivos foram removidos
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
}

void loop() {

}