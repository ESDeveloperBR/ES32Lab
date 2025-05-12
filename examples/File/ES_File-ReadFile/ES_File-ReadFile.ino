/**
* @brief This example demonstrates the simplicity and usage of the `readFile` method from the ES_File class to read the entire content of a file.
* It also includes examples of creating, writing, and appending text to a file to prepare the content for reading.
* | Este exemplo demonstra a simplicidade e a utilização do método `readFile` da classe ES_File para ler todo o conteúdo de um arquivo.
* Também inclui exemplos de criação, escrita e anexação de texto em um arquivo para preparar o conteúdo para leitura.
*
* @details The example initializes the file system (LittleFS in this case), writes multiple lines of text to a file, 
* and then reads the entire content of the file using the `readFile` method. The content is displayed on the Serial Monitor.
* | O exemplo inicializa o sistema de arquivos (LittleFS neste caso), escreve várias linhas de texto em um arquivo 
* e, em seguida, lê todo o conteúdo do arquivo usando o método `readFile`. O conteúdo é exibido no Monitor Serial.
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
    fileManager.println("/file01.txt", "This is line 1 of the file.", true);  // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/file01.txt").
    fileManager.println("/file01.txt", "This is line 2 of the file.", false); // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", "This is line 3 of the file.");        // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", "This is line 4 of the file.");        // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", "This is line 5 of the file.");        // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", "This is line 6 of the file.");        // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).

    String readFile = fileManager.readFile("/file01.txt"); // Reads the content of the file | Lê o conteúdo do arquivo
    Serial.println("------------- Read File -------------"); // Prints a separator line | Imprime uma linha separadora
    Serial.println(readFile); // Prints the content of the file | Imprime o conteúdo do arquivo

    fileManager.remove("/file01.txt"); // Removes the file | Remove o arquivo
}

void loop() {

}