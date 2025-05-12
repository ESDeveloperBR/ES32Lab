/**
* @brief This example demonstrates how to use the navigation methods from the ES_File class to traverse files in a directory.
* The methods include `getLastFileName`, `getPreviousFileName`, and `getNextFileName`, allowing navigation through files in forward and reverse order.
* | Este exemplo demonstra como usar os métodos de navegação da classe ES_File para percorrer arquivos em um diretório.
* Os métodos incluem `getLastFileName`, `getPreviousFileName` e `getNextFileName`, permitindo a navegação pelos arquivos em ordem direta e inversa.
*
* @details The example initializes the file system (LittleFS in this case) using `fileManager.begin(LittleFS)`. 
* It creates a directory with multiple files and demonstrates the following navigation methods:
* - `getFirstFileName`: Retrieves the first file in the directory.
* - `getLastFileName`: Retrieves the last file in the directory.
* - `getPreviousFileName`: Retrieves the file that comes before the current file in reverse order.
* - `getNextFileName`: Retrieves the file that comes after the current file in forward order.
* Each method is demonstrated with examples, including cases where the methods are used repeatedly to traverse all files in a directory.
* Additionally, the example shows how to pass a specific file name to `getNextFileName` to retrieve the next file relative to it.
* | O exemplo inicializa o sistema de arquivos (LittleFS neste caso) usando `fileManager.begin(LittleFS)`.
* Ele cria um diretório com vários arquivos e demonstra os seguintes métodos de navegação:
* - `getFirstFileName`: Obtém o primeiro arquivo no diretório.
* - `getLastFileName`: Obtém o último arquivo no diretório.
* - `getPreviousFileName`: Obtém o arquivo que vem antes do arquivo atual em ordem inversa.
* - `getNextFileName`: Obtém o arquivo que vem após o arquivo atual em ordem direta.
* Cada método é demonstrado com exemplos, incluindo casos em que os métodos são usados repetidamente para percorrer todos os arquivos em um diretório.
* Além disso, o exemplo mostra como passar um nome de arquivo específico para `getNextFileName` para obter o próximo arquivo relativo a ele.
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
    fileManager.println("/dir/file01.txt", "Symbolic content of the file. (1)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file02.txt", "Symbolic content of the file. (12)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file03.txt", "Symbolic content of the file. (123)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file04.txt", "Symbolic content of the file. (1234)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").
    fileManager.println("/dir/file05.txt", "Symbolic content of the file. (12345)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Creates a new file (createNew = true) and writes the text to the file ("/file01.txt").

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
    Serial.println("--- Lists the files in the directory (/dir) ---"); // Prints a separator line | Imprime uma linha separadora
    Serial.println(fileManager.listAllFiles("/dir")); // Lists all files in the directory (/dir) | Lista todos os arquivos no diretório (/dir)

    Serial.println("EN: ATTENTION: Note all the created files."); // Prints a message indicating that all files and directories were created | Imprime uma mensagem indicando que todos os arquivos e diretórios foram criados
    Serial.println("PT: ATENÇÃO: Observe todos os arquivos criados."); // Prints a message indicating that all files and directories were created | Imprime uma mensagem indicando que todos os arquivos e diretórios foram criados
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(5000); // Waits for 5 seconds before the next example | Aguarda 5 segundos antes do próximo exemplo


    // getFirstFileName(directory);
    // Gets the name of the FIRST file in a directory from a specified file system.
    // | Obtém o nome do PRIMEIRO arquivo em um diretório de um sistema de arquivos especificado.
    // @param directory Directory to search in. | Diretório a ser pesquisado.
    // @return Name of the FIRST file. | Nome do PRIMEIRO arquivo.
    Serial.println("--- getFirstFileName(\"/dir\") ---"); // Prints a separator line | Imprime uma linha separadora
    String firstFileName = fileManager.getFirstFileName("/dir"); // Gets the first file name in the directory (/dir) | Obtém o primeiro nome de arquivo no diretório (/dir)
    Serial.println("EN: First file name in (/dir).........: " + firstFileName); // Prints the first file name | Imprime o primeiro nome de arquivo
    Serial.println("PT: Primeiro nome de arquivo em (/dir): " + firstFileName); // Prints the first file name | Imprime o primeiro nome de arquivo
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    // getLastFileName(directory);
    // Gets the name of the LAST file in a directory from a specified file system.
    // | Obtém o nome do ÚLTIMO arquivo em um diretório de um sistema de arquivos especificado.
    // @param directory Directory to search in. | Diretório a ser pesquisado.
    // @return Name of the LAST file. | Nome do arquivo ÚLTIMO.
    // @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
    Serial.println("--- getLastFileName(\"/dir\") ---"); // Prints a separator line | Imprime uma linha separadora
    String lastFileName  = fileManager.getLastFileName("/dir"); // Gets the last file name in the directory (/dir) | Obtém o último nome de arquivo no diretório (/dir)
    Serial.println("EN: Last file name in (/dir)........: " + lastFileName); // Prints the last file name | Imprime o último nome de arquivo
    Serial.println("PT: Último nome de arquivo em (/dir): " + lastFileName); // Prints the last file name | Imprime o último nome de arquivo
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    // getPreviousFileName(directory);
    // Gets the name of the PREVIOUS file in a directory.
    // | Obtém o nome do arquivo ANTERIOR em um diretório.
    // @param directory Directory to search in. | Diretório a ser pesquisado.
    // @return Name of the PREVIOUS file. | Nome do arquivo ANTERIOR.
    // @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
    Serial.println("--- getPreviousFileName() ---"); // Prints a separator line | Imprime uma linha separadora
    String previousFileName = fileManager.getPreviousFileName(); // Gets the name of the previous file to the last displayed file. | Obtém o nome do arquivo anterior ao último arquivo exibido.
    Serial.println("EN: Previous file name to (/dir/file05.txt)......: " + previousFileName); // Prints the previous file name | Imprime o nome do arquivo anterior
    Serial.println("EN: WARNING: The method `getPreviousFileName()` can be used repeatedly to traverse files in reverse order."); // Prints a message indicating that the method can be used repeatedly | Imprime uma mensagem indicando que o método pode ser usado repetidamente
    Serial.println("PT: Nome do arquivo anterior ao (/dir/file05.txt): " + previousFileName); // Prints the previous file name | Imprime o nome do arquivo anterior
    Serial.println("PT: ATENÇÃO: O método `getPreviousFileName()` pode ser usado repetidamente para percorrer arquivos em ordem inversa."); // Prints a message indicating that the method can be used repeatedly | Imprime uma mensagem indicando que o método pode ser usado repetidamente
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    //getNextFileName(directory);
    // Gets the name of the NEXT file in a directory.
    // | Obtém o nome do arquivo PRÓXIMO em um diretório.
    // @param directory Directory to search in. | Diretório a ser pesquisado.
    // @return Name of the NEXT file. | Nome do arquivo PRÓXIMO.
    // @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
    Serial.println("--- getNextFileName() ---"); // Prints a separator line | Imprime uma linha separadora
    String nextFileName = fileManager.getNextFileName(); // Gets the name of the next file to the last displayed file. | Obtém o nome do próximo arquivo ao último arquivo exibido.
    Serial.println("EN: Next file name to (/dir/file04.txt).........: " + nextFileName); // Prints the next file name | Imprime o nome do próximo arquivo
    Serial.println("EN: WARNING: The method `getNextFileName()` can be used repeatedly to traverse files in forward order."); // Prints a message indicating that the method can be used repeatedly | Imprime uma mensagem indicando que o método pode ser usado repetidamente
    Serial.println("PT: Nome do próximo arquivo em (/dir/file04.txt): " + nextFileName); // Prints the next file name | Imprime o nome do próximo arquivo
    Serial.println("PT: ATENÇÃO: O método `getNextFileName()` pode ser usado repetidamente para percorrer arquivos em ordem direta."); // Prints a message indicating that the method can be used repeatedly | Imprime uma mensagem indicando que o método pode ser usado repetidamente
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    Serial.println("--- getNextFileName(\"/dir/file02.txt\") ---"); // Prints a separator line | Imprime uma linha separadora
    nextFileName = fileManager.getNextFileName("/dir/file02.txt"); // Gets the name of the next file to the specified file. | Obtém o nome do próximo arquivo para o arquivo especificado.
    Serial.println("EN: Next file name to (/dir/file02.txt).........: " + nextFileName); // Prints the next file name | Imprime o nome do próximo arquivo
    Serial.println("EN: WARNING: The method `getNextFileName(\"/dir/file02.txt\")` can be used repeatedly to traverse files in forward order."); // Prints a message indicating that the method can be used repeatedly | Imprime uma mensagem indicando que o método pode ser usado repetidamente
    Serial.println("PT: Nome do próximo arquivo em (/dir/file02.txt): " + nextFileName); // Prints the next file name | Imprime o nome do próximo arquivo
    Serial.println("PT: ATENÇÃO: O método `getNextFileName(\"/dir/file02.txt\")` pode receber um nome de arquivo como parâmetro."); // Prints a message indicating that the method can receive a file name as a parameter | Imprime uma mensagem indicando que o método pode receber um nome de arquivo como parâmetro
    Serial.println("======================================================"); // Prints a separator line | Imprime uma linha separadora
    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo


    fileManager.remove("/dir", true); // Deletes all files in the directory (/dir) and its subdirectories (recursive) | Exclui todos os arquivos no diretório (/dir) e seus subdiretórios (recursivo)
}

void loop() {

}