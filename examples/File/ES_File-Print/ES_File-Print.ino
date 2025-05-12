/**
* @brief This example demonstrates basic file operations using the ES_File class, including creating, writing, appending, 
* and reading files in a file system. The example initializes the file system (LittleFS in this case), writes multiple lines 
* of text to a file, checks if the file exists, retrieves its size, and reads its content to display on the Serial Monitor.
* | Este exemplo demonstra operações básicas de arquivos usando a classe ES_File, incluindo criação, escrita, anexação e 
* leitura de arquivos em um sistema de arquivos. O exemplo inicializa o sistema de arquivos (LittleFS neste caso), escreve 
* várias linhas de texto em um arquivo, verifica se o arquivo existe, obtém seu tamanho e lê seu conteúdo para exibir no 
* Monitor Serial.
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
    if (fileManager.begin(LittleFS)) {    // Initializes the file system (LittleFS in this case) | Inicializa o sistema de arquivos (LittleFS neste caso)
        Serial.println("File system initialized successfully.");    // Prints a message if the file system is initialized successfully | Imprime uma mensagem se o sistema de arquivos for inicializado com sucesso
    } else {
        Serial.println("Failed to initialize file system.");    // Prints a message if the file system initialization fails | Imprime uma mensagem se a inicialização do sistema de arquivos falhar
        return;
    }

    // println(fileName, content, createNew, decimalPlaces);
    // Writes a line of text to a file with a newline character. 
    //| Escreve uma linha de texto em um arquivo com um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    fileManager.println("/file01.txt", "In this way, a text is sent to be saved in the file.", true); // Creates a new file (createNew = true) and writes the text to the file ("/file01.txt"). | Cria um novo arquivo (createNew = true) e escreve o texto no arquivo ("/file01.txt").
    fileManager.println("/file01.txt", "This is a test text."); // Appends the text to the existing file (createNew = false). | Anexa o texto ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", 7);  // Appends the integer 7 to the existing file (createNew = false). | Anexa o inteiro 7 ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", 1.5); // Appends the float 1.5 to the existing file (createNew = false). | Anexa o float 1.5 ao arquivo existente (createNew = false).
    fileManager.println("/file01.txt", 1.12345, false, 5); // Appends the float 1.12345 to the existing file (createNew = false) with 5 decimal places. | Anexa o float 1.12345 ao arquivo existente (createNew = false) com 5 casas decimais.
    fileManager.println("/file01.txt", 1.12345, false, 3); // Appends the float 1.12345 to the existing file (createNew = false) with 3 decimal places. | Anexa o float 1.12345 ao arquivo existente (createNew = false) com 3 casas decimais.
    fileManager.println("/file01.txt", 1.12345); // Appends the float 1.12345 to the existing file (createNew = false) with 2 decimal places (defalt). | Anexa o float 1.12345 ao arquivo existente (createNew = false) com 2 casas decimais (valor padrão).

    // print(fileName, content, createNew, decimalPlaces);
    // Writes text to a file without a newline character.
    // | Escreve texto em um arquivo sem um caractere de nova linha.
    // @param fileName Name of the file. | Nome do arquivo.
    // @param content Content to write. | Conteúdo a ser escrito.
    // @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
    // @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
    // @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
    fileManager.print("/file01.txt", "Additional text without a newline character.: "); // Appends the text without a newline character. | Anexa o texto sem um caractere de nova linha.
    fileManager.print("/file01.txt", "A"); // Appends the character 'A' without a newline character. | Anexa o caractere 'A' sem um caractere de nova linha.
    fileManager.print("/file01.txt", "B"); // Appends the character 'B' without a newline character. | Anexa o caractere 'B' sem um caractere de nova linha.
    fileManager.print("/file01.txt", 1); // Appends the integer 1 without a newline character. | Anexa o inteiro 1 sem um caractere de nova linha.
    fileManager.print("/file01.txt", " float: "); // Appends the text " float: " without a newline character. | Anexa o texto " float: " sem um caractere de nova linha.
    fileManager.print("/file01.txt", 0.12345, false, 5); // Appends the float 0.12345 without a newline character with 5 decimal places. | Anexa o float 0.12345 sem um caractere de nova linha com 5 casas decimais.

    Serial.println("--------------------------------"); // Prints a separator line | Imprime uma linha separadora
    if(fileManager.exists("/file01.txt")) { // Checks if the file "/file01.txt" exists | Verifica se o arquivo "/file01.txt" existe
        Serial.println("File exists."); // Prints a message if the file exists | Imprime uma mensagem se o arquivo existir
    } else {
        Serial.println("File does not exist."); // Prints a message if the file does not exist | Imprime uma mensagem se o arquivo não existir
    }

    Serial.print("File Size: ");
    Serial.println(fileManager.getFileSize("/file01.txt")); // Prints the size of the file "/file01.txt" | Imprime o tamanho do arquivo "/file01.txt"

    Serial.println("----- Reading file content -----");
    Serial.println(fileManager.readFile("/file01.txt")); // Reads the content of the file "/file01.txt" and prints it | Lê o conteúdo do arquivo "/file01.txt" e o imprime
}
 
void loop() {
 
}