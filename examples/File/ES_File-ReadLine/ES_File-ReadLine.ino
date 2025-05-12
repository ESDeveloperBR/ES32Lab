/**
* @brief This example demonstrates how to use the `readLine` method from the ES_File class to read specific lines from a file. 
* It also includes examples of creating, writing, and appending text to a file, as well as counting the total number of lines in a file.
* | Este exemplo demonstra como usar o método `readLine` da classe ES_File para ler linhas específicas de um arquivo. 
* Também inclui exemplos de criação, escrita e anexação de texto a um arquivo, bem como a contagem do número total de linhas em um arquivo.
*
* @details The example initializes the file system (LittleFS in this case), writes multiple lines of text to a file, 
* and then reads each line sequentially using the `readLine` method. The total number of lines in the file is also counted and displayed.
* | O exemplo inicializa o sistema de arquivos (LittleFS neste caso), escreve várias linhas de texto em um arquivo 
* e, em seguida, lê cada linha sequencialmente usando o método `readLine`. O número total de linhas no arquivo também é contado e exibido.
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
int lineIndex = 1;          // Variable to keep track of the current line number | Variável para acompanhar o número da linha atual

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

    Serial.println("-----------------------------------"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("EN: Number of lines in the file: " + String(fileManager.countLines("/file01.txt"))); // Counts the number of lines in the file "/file01.txt" and prints it | Conta o número de linhas no arquivo "/file01.txt" e o imprime
    Serial.println("PT: Número de linhas no arquivo: " + String(fileManager.countLines("/file01.txt"))); // Conta o número de linhas no arquivo "/file01.txt" e o imprime
    Serial.println("-----------------------------------"); // Prints a separator line | Imprime uma linha separadora
    Serial.println("EN: The content of the file `/file01.txt` will be displayed line by line in the `void loop()`."); // Will display line by line the content of the file '/file01.txt' | Será exibido linha por linha o conteúdo do arquivo '/file01.txt'
    Serial.println("PT: Será exibido linha por linha o conteúdo do arquivo `/file01.txt` no `void loop()`."); // Will display line by line the content of the file '/file01.txt' | Será exibido linha por linha o conteúdo do arquivo '/file01.txt'
    Serial.println("==================================="); // Prints a separator line | Imprime uma linha separadora
}

void loop() {
    int countLines = fileManager.countLines("/file01.txt"); // Counts the number of lines in the file "/file01.txt" | Conta o número de linhas no arquivo "/file01.txt"
    if(lineIndex <= countLines) { // Checks if the current line number is less than the total number of lines | Verifica se o número da linha atual é menor que o número total de linhas
        String line = fileManager.readLine("/file01.txt", lineIndex); // Reads the specified line from the file "/file01.txt" | Lê a linha especificada do arquivo "/file01.txt"
        Serial.println(line); // Prints the content of the line | Imprime o conteúdo da linha
        lineIndex++; // Increments the line number | Incrementa o número da linha
    } else {
        Serial.println("==================================="); // Prints a separator line | Imprime uma linha separadora
        lineIndex = 1; // Resets the line number to 1 | Redefine o número da linha para 1
    }
    delay(2000); // Waits for 2 seconds before the next iteration | Aguarda 2 segundos antes da próxima iteração
}