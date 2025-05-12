/**
* @brief This example demonstrates how to use the `copy` method from the ES_File class to copy files within the same file system.
* The example uses LittleFS as the file system, but it can be adapted to work with other file systems such as SD or SPIFFS.
* | Este exemplo demonstra como usar o método `copy` da classe ES_File para copiar arquivos dentro do mesmo sistema de arquivos.
* O exemplo utiliza o LittleFS como sistema de arquivos, mas pode ser adaptado para funcionar com outros sistemas de arquivos, como SD ou SPIFFS.
*
* @details The example initializes the file system (LittleFS in this case), creates a source file with content, 
* and then copies it to a new destination file using the `copy` method. The content of both files is displayed to verify the operation.
* | O exemplo inicializa o sistema de arquivos (LittleFS neste caso), cria um arquivo de origem com conteúdo 
* e, em seguida, o copia para um novo arquivo de destino usando o método `copy`. O conteúdo de ambos os arquivos é exibido para verificar a operação.
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

    // println(fileName, content, createNew, decimalPlaces);
    // Writes a line of text to a file with a newline character. 
    //| Escreve uma linha de texto em um arquivo com um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    fileManager.println("/dir/file01.txt", "Symbolic content of the file. (1)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/dir/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/dir/file01.txt").
    fileManager.println("/dir/file02.txt", "Symbolic content of the file. (12)", true); // Creates a new file (createNew = true) and writes the text to the file ("/dir/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/dir/file01.txt").
    fileManager.println("/dir/file03.txt", "Symbolic content of the file. (123)", true);// Creates a new file (createNew = true) and writes the text to the file ("/dir/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/dir/file01.txt").
    fileManager.println("/dir/subDir/file04.txt", "Symbolic content of the file. (1234)", true);  // Creates a new file (createNew = true) and writes the text to the file ("/dir/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/dir/file01.txt").

    // listAllFiles(directory, showFileSize = false, showSubDir = true, openSubDir = true, indentation = false);    
    // Lists all files in a directory (sorted alphabetically).
    // | Lista todos os arquivos em um diretório (ordenados alfabeticamente).
    // @param directory Directory to list. | Diretório a ser listado.
    // @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
    // @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
    // @param openSubDir Whether to open subdirectories (recursive listing). | Se deve abrir subdiretórios (listagem recursiva).
    // @param indentation Whether to use indentation. If false, full file paths are displayed. | Se deve usar indentação. Se false, os caminhos completos dos arquivos são exibidos.
    // @return String containing the file list. | String contendo a lista de arquivos.
    String listAllFiles;    // Variable to store the list of files | Variável para armazenar a lista de arquivos
    Serial.println("--- List All Files (/dir): showFileSize = true ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true); // List all files in the directory "/dir" with file sizes. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo

    Serial.println("--- Copy File (/dir/file01.txt) to (/dir/subDir/file01_copy.txt) ---"); // Prints a separator line | Imprime uma linha separadora

    // copy(sourceFileName, destFileName);
    // Copies a file from one file system to another.
    // | Copia um arquivo de um sistema de arquivos para outro.
    // @param sourceFileName Source file name. | Nome do arquivo de origem.
    // @param destFileName Destination file name. | Nome do arquivo de destino.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    // @note This method does not support copying files between SPIFFS and LittleFS. | Este método não suporta copiar arquivos entre SPIFFS e LittleFS.
    fileManager.copy("/dir/file01.txt", "/dir/subDir/file01_copy.txt"); // Copies the file from one location to another | Copia o arquivo de um local para outro

    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo

    Serial.println("--- List All Files (/dir): showFileSize = true ---"); // Prints a separator line | Imprime uma linha separadora
    listAllFiles = fileManager.listAllFiles("/dir", true); // List all files in the directory "/dir" with file sizes. | Lista todos os arquivos no diretório "/dir" com tamanhos de arquivos.
    Serial.println(listAllFiles); // Prints the list of files to the Serial Monitor | Imprime a lista de arquivos no Monitor Serial

    delay(2000); // Waits for 2 seconds before the next example | Aguarda 2 segundos antes do próximo exemplo
    
    Serial.println("--- Removes the directory (/dir) ---"); // Prints a separator line | Imprime uma linha separadora
    if(fileManager.remove("/dir", true)) { // Removes the directory "/dir" | Remove o diretório "/dir"
        Serial.println("Directory removed successfully."); // Prints a success message | Imprime uma mensagem de sucesso
    } else {
        Serial.println("Failed to remove directory."); // Prints a failure message | Imprime uma mensagem de falha
    }
}

void loop() {

}