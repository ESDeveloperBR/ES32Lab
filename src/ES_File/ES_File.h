#ifndef ES_File_h
#define ES_File_h

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPIFFS.h>
#include <LittleFS.h>
#include <vector>

#define ES_FILE_VERSION "3.3.3 update 05/12/2025"   // mm/dd/yyyy

class ES_File {
private:
    File _fileHandle;                  /* File pointer | Ponteiro do arquivo */
    fs::FS* _fileSystem = nullptr;     /* Pointer to file system | Ponteiro para o sistema de arquivos */
    bool _createNewFile = false;       /* Controls whether to create a new file or just edit | Controla se vai ser criado um arquivo novo ou apenas editar */
    String _fileName = "";             /* Name of the file to be manipulated | Nome do arquivo a ser manipulado */

    /**
     * Initializes the file system.
     * | Inicializa o sistema de arquivos.
     * @param fs Pointer to the file system to use. | Ponteiro para o sistema de arquivos a ser usado.
     * @return True if initialization was successful, false otherwise. | Verdadeiro se a inicialização foi bem-sucedida, falso caso contrário.
     */
    bool _initFileSystem(fs::FS* fs);


    /**
     * Normalizes a file or directory path.
     * | Normaliza um caminho de arquivo ou diretório.
     * @param fs Pointer to the file system. | Ponteiro para o sistema de arquivos.
     * @param path Original path. | Caminho original.
     * @return Normalized path or file name. | Caminho normalizado ou nome do arquivo.
     */    
    String _normalizePath(fs::FS& fs, const String& path);


    /**
     * Saves information to a file.
     * | Salva informações em um arquivo.
     * @param fs Pointer to the file system to use. | Ponteiro para o sistema de arquivos a ser usado.
     * @param fileName Name of the file to receive the information. | Nome do arquivo que receberá as informações.
     * @param content Information to be saved. | Informação a ser salva.
     * @param addNewLine Whether to add a line break. | Se deve adicionar uma quebra de linha.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool _writeContent(fs::FS* fs, const String& fileName, const String& content, bool addNewLine, bool createNew);
    
    
    /**
     * Removes all files in a directory or the root.
     * | Remove todos os arquivos em um diretório ou na raiz.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to remove files from. | Diretório de onde os arquivos serão removidos.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool _removeAllFiles(fs::FS& fs, const String& directory);
    
    
    /**
     * Extracts the directory name from a file path.
     * | Extrai o nome do diretório de um caminho de arquivo.
     * @param path Full path including file name. | Caminho completo incluindo nome do arquivo.
     * @return Directory path. | Caminho do diretório.
     */    
    String _extractDirectoryFromPath(const String& path);
    
    
    /**
     * Lists all files in a directory (internal helper, sorted alphabetically).
     * | Lista todos os arquivos em um diretório (função interna de apoio, ordenados alfabeticamente).
     * @param fs File system reference. | Referência para o sistema de arquivos.
     * @param path Directory path to list from. | Caminho do diretório a ser listado.
     * @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
     * @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
     * @param openSubDir Whether to open subdirectories (recursive). | Se deve abrir subdiretórios (recursivo).
     * @param indentation Whether to use indentation for hierarchy. | Se deve usar indentação para hierarquia.
     * @param showTotalSize If true, returns the total size instead of listing names. | Se verdadeiro, retorna o tamanho total em vez de listar nomes.
     * @param tabCount Current indentation level (number of leading spaces). | Nível atual de indentação (número de espaços iniciais).
     * @return String containing the file list or total size. | String contendo a lista de arquivos ou o tamanho total.
     */
    String _listFilesInDirectory(fs::FS& fs, const String& path, bool showFileSize, bool showSubDir, bool openSubDir, bool indentation, bool showTotalSize = false, uint8_t tabCount = 0);
    
    
    /**
     * Locates a file in a directory based on specified option.
     * | Localiza um arquivo em um diretório com base na opção especificada.
     * @param fs Pointer to the file system to use. | Ponteiro para o sistema de arquivos a ser usado.
     * @param fileOrDirPath Path to file or directory. | Caminho para arquivo ou diretório.
     * @param option Search option (N: next, P: previous, F: first, L: last). | Opção de busca (N: próximo, P: anterior, F: primeiro, L: último).
     * @return File name found. | Nome do arquivo encontrado.
     */
    String _locateFile(fs::FS* fs, const String& fileOrDirPath, char option);
    

    /**
     * Copies a directory from one file system to another.
     * | Copia um diretório de um sistema de arquivos para outro.
     * @param sourceFS Source file system. | Sistema de arquivos de origem.
     * @param sourceDirName Source directory name. | Nome do diretório de origem.
     * @param destFS Destination file system. | Sistema de arquivos de destino.
     * @param destDirName Destination directory name. | Nome do diretório de destino.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool _copyDirectory(fs::FS& sourceFS, const String& sourceDirName, fs::FS& destFS, const String& destDirName);


    /**
     * Removes a file. | Remove um arquivo.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file to remove. | Nome do arquivo a ser removido.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool _removeFile(fs::FS& fs, const String& fileName);


    /**
     * Removes a directory and all its contents (files and subdirectories).
     * | Remove um diretório e todo o seu conteúdo (arquivos e subdiretórios).
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to remove. | Diretório a ser removido.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool _removeDirectory(fs::FS& fs, const String& directory);


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ======================================= PUBLIC =============================================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
public:

    /**
     * Constructor for ES_File class.
     * | Construtor para a classe ES_File.
     */
    ES_File();

    /**
     * Initializes the file system.
     * | Inicializa o sistema de arquivos.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @return True if initialization was successful, false otherwise. | Verdadeiro se a inicialização foi bem-sucedida, falso caso contrário.
     * @note This method is optional and has the advantage of setting File Sytem only once.| Esse método é opcional e tem a vantagem de definir o sistema de arquivos apenas uma vez.
     */
    bool begin(fs::FS& fs);


    /**
     * Lists all files in a directory (sorted alphabetically).
     * | Lista todos os arquivos em um diretório (ordenados alfabeticamente).
     * @param directory Directory to list. | Diretório a ser listado.
     * @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
     * @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
     * @param openSubDir Whether to open subdirectories (recursive listing). | Se deve abrir subdiretórios (listagem recursiva).
     * @param indentation Whether to use indentation. If false, full file paths are displayed. | Se deve usar indentação. Se false, os caminhos completos dos arquivos são exibidos.
     * @return String containing the file list. | String contendo a lista de arquivos.
     */
    String listAllFiles(const String& directory, bool showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false);
    /**
     * Lists all files in a directory (sorted alphabetically).
     * | Lista todos os arquivos em um diretório (ordenados alfabeticamente).
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to list. | Diretório a ser listado.
     * @param showFileSize Whether to show file sizes. | Se deve mostrar tamanhos de arquivos.
     * @param showSubDir Whether to show subdirectories. | Se deve mostrar subdiretórios.
     * @param openSubDir Whether to open subdirectories (recursive listing). | Se deve abrir subdiretórios (listagem recursiva).
     * @param indentation Whether to use indentation. If false, full file paths are displayed. | Se deve usar indentação. Se false, os caminhos completos dos arquivos são exibidos.
     * @return String containing the file list. | String contendo a lista de arquivos.
     */
    String listAllFiles(fs::FS& fs, const String& directory, bool showFileSize = false, bool showSubDir = true, bool openSubDir = true, bool indentation = false);


    /**
     * Checks if a file or directory exists.
     * | Verifica se um arquivo ou diretório existe.
     * @param fileName Name of the file to check. | Nome do arquivo a ser verificado.
     * @return True if exists, false otherwise. | Verdadeiro se existir, falso caso contrário.
    */
    bool exists(const String& fileName);
    /**
     * Checks if a file or directory exists.
     * | Verifica se um arquivo ou diretório existe.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file to check. | Nome do arquivo a ser verificado.
     * @return True if exists, false otherwise. | Verdadeiro se existir, falso caso contrário.
    */
    bool exists(fs::FS& fs, const String& fileName);


    /**
     * Checks if a directory exists in the file system.
     * | Verifica se um diretório existe no sistema de arquivos.
     * @param directory Directory path to check. | Caminho do diretório a ser verificado.
     * @return True if the directory exists, false otherwise. | Verdadeiro se o diretório existir, falso caso contrário.
     * @note The SPIFFS file system does not support directories, so it always returns false. | O sistema de arquivos SPIFFS não suporta diretórios, então sempre retorna falso.
     */
    bool directoryExists(const String& directory);
    /**
     * Checks if a directory exists in the file system.
     * | Verifica se um diretório existe no sistema de arquivos.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory path to check. | Caminho do diretório a ser verificado.
     * @return True if the directory exists, false otherwise. | Verdadeiro se o diretório existir, falso caso contrário.
     * @note The SPIFFS file system does not support directories, so it always returns false. | O sistema de arquivos SPIFFS não suporta diretórios, então sempre retorna falso.
     */
    bool directoryExists(fs::FS& fs, const String& directory);


    /**
     * Writes a line of text to a file with a newline character.
     * | Escreve uma linha de texto em um arquivo com um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool println(const String& fileName, const String& content, bool createNew = false);
    /**
     * Writes a line of text to a file with a newline character.
     * | Escreve uma linha de texto em um arquivo com um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool println(const String& fileName, int content, bool createNew = false);
    /**
     * Writes a line of text to a file with a newline character.
     * | Escreve uma linha de texto em um arquivo com um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool println(const String& fileName, double content, bool createNew = false, uint8_t decimalPlaces = 2);
    /**
     * Writes a line of text to a file with a newline character.
     * | Escreve uma linha de texto em um arquivo com um caractere de nova linha.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool println(fs::FS& fs, const String& fileName, const String& content, bool createNew = false);


    /**
     * Writes text to a file without a newline character.
     * | Escreve texto em um arquivo sem um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool print(const String& fileName, const String& content, bool createNew = false);
    /**
     * Writes text to a file without a newline character.
     * | Escreve texto em um arquivo sem um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool print(const String& fileName, int content, bool createNew = false);
    /**
     * Writes text to a file without a newline character.
     * | Escreve texto em um arquivo sem um caractere de nova linha.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @param decimalPlaces Number of decimal places to write. | Número de casas decimais a serem escritas.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */    
    bool print(const String& fileName, double content, bool createNew = false, uint8_t decimalPlaces = 2);
    /**
     * Writes text to a file without a newline character.
     * | Escreve texto em um arquivo sem um caractere de nova linha.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file. | Nome do arquivo.
     * @param content Content to write. | Conteúdo a ser escrito.
     * @param createNew Whether to create a new file or append. | Se deve criar um novo arquivo ou anexar.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool print(fs::FS& fs, const String& fileName, const String& content, bool createNew = false);


    /**
     * Reads the content of a file.
     * | Lê o conteúdo de um arquivo.
     * @param fileName Name of the file to read. | Nome do arquivo a ser lido.
     * @return The content of the file as a String, or an empty String if an error occurs.
     * | O conteúdo do arquivo como uma String, ou uma String vazia em caso de erro.
     */
    String readFile(const String& fileName);
    /**
     * Reads the content of a file.
     * | Lê o conteúdo de um arquivo.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file to read. | Nome do arquivo a ser lido.
     * @return The content of the file as a String, or an empty String if an error occurs.
     * | O conteúdo do arquivo como uma String, ou uma String vazia em caso de erro.
     */
    String readFile(fs::FS& fs, const String& fileName);


    /**
     * Reads a specific line from a file.
     * | Lê uma linha específica de um arquivo.
     * @param fileName Name of the file to read. | Nome do arquivo a ser lido.
     * @param lineNumber Line number to read (starting from 1). | Número da linha a ser lida (começando de 1).
     * @return The content of the specified line, or an empty String if the line does not exist. 
     * | O conteúdo da linha especificada, ou uma String vazia se a linha não existir.
     */
    String readLine(const String& fileName, size_t lineNumber);


    /**
     * Counts the number of lines in a file.
     * | Conta o número de linhas em um arquivo.
     * @param fileName Name of the file to count lines. | Nome do arquivo para contar as linhas.
     * @return The total number of lines in the file. | O número total de linhas no arquivo.
     */
    size_t countLines(const String& fileName);


    /**
     * Removes a file, all files in a directory, or a directory and its contents.
     * | Remove um arquivo, todos os arquivos em um diretório ou um diretório e seu conteúdo.
     * @param path Path to the file or directory to remove. | Caminho para o arquivo ou diretório a ser removido.
     * @param recursive If true, removes directories and their contents recursively. | Se verdadeiro, remove diretórios e seus conteúdos recursivamente.
     * @return True if the operation was successful, false otherwise. | Verdadeiro se a operação foi bem-sucedida, falso caso contrário.
     * @note For SPIFFS, directories are not supported, so all files are treated as being in the root. | Para SPIFFS, diretórios não são suportados, então todos os arquivos são tratados como estando na raiz.
     * @attention If it is requested to remove the files from a directory, the directory exists and is empty, TRUE will be returned. | Se for solicitado remover os arquivos de um diretório, o diretório existe e está vazio, TRUE será retornado.
     */
    bool remove(const String& path, bool recursive = false);
    /**
     * Removes a file, all files in a directory, or a directory and its contents.
     * | Remove um arquivo, todos os arquivos em um diretório ou um diretório e seu conteúdo.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param path Path to the file or directory to remove. | Caminho para o arquivo ou diretório a ser removido.
     * @param recursive If true, removes directories and their contents recursively. | Se verdadeiro, remove diretórios e seus conteúdos recursivamente.
     * @return True if the operation was successful, false otherwise. | Verdadeiro se a operação foi bem-sucedida, falso caso contrário.
     * @note For SPIFFS, directories are not supported, so all files are treated as being in the root. | Para SPIFFS, diretórios não são suportados, então todos os arquivos são tratados como estando na raiz.
     * @attention If it is requested to remove the files from a directory, the directory exists and is empty, TRUE will be returned. | Se for solicitado remover os arquivos de um diretório, o diretório existe e está vazio, TRUE será retornado.
     */
    bool remove(fs::FS& fs, const String& path, bool recursive = false);


    /**
     * Creates a directory in a specified file system.
     * | Cria um diretório em um sistema de arquivos especificado.
     * @param directory Directory to create. | Diretório a ser criado.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool createDirectory(const String& directory);
    /**
     * Creates a directory in a specified file system.
     * | Cria um diretório em um sistema de arquivos especificado.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to create. | Diretório a ser criado.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     */
    bool createDirectory(fs::FS& fs, const String& directory);


    /**
    * Moves or renames a file or directory.
     * | Move ou renomeia um arquivo ou diretório.
     * @param sourcePath Path to the source file or directory. | Caminho para o arquivo ou diretório de origem.
     * @param destinationPath Path to the destination file or directory. | Caminho para o arquivo ou diretório de destino.
     * @return True if the operation was successful, false otherwise. | Verdadeiro se a operação foi bem-sucedida, falso caso contrário.
     * @note If the source and destination are the same, the operation will fail. | Se a origem e o destino forem iguais, a operação falhará.
     */
    bool move(const String& sourcePath, const String& destinationPath);    
    /**
    * Moves or renames a file or directory.
     * | Move ou renomeia um arquivo ou diretório.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param sourcePath Path to the source file or directory. | Caminho para o arquivo ou diretório de origem.
     * @param destinationPath Path to the destination file or directory. | Caminho para o arquivo ou diretório de destino.
     * @return True if the operation was successful, false otherwise. | Verdadeiro se a operação foi bem-sucedida, falso caso contrário.
     * @note If the source and destination are the same, the operation will fail. | Se a origem e o destino forem iguais, a operação falhará.
     */
    bool move(fs::FS& fs, const String& sourcePath, const String& destinationPath);


    /**
     * Gets the total space of a specified file system.
     * | Obtém o espaço total de um sistema de arquivos especificado.
     * @return Total space in bytes. | Espaço total em bytes.
     */
    size_t getTotalSpace();
    /**
     * Gets the total space of a specified file system.
     * | Obtém o espaço total de um sistema de arquivos especificado.
     * @param fs File system to check. | Sistema de arquivos a ser verificado.
     * @return Total space in bytes. | Espaço total em bytes.
     */
    size_t getTotalSpace(fs::FS& fs);


    /**
     * Gets the used space of a specified file system.
     * | Obtém o espaço usado de um sistema de arquivos especificado.
     * @param directory Directory to check. | Diretório a ser verificado.
     * @param includeSubDirs Whether to include subdirectories. | Se deve incluir subdiretórios.
     * @return Used space in bytes. | Espaço usado em bytes.
     */
    size_t getUsedSpace(const String& directory = "/", bool includeSubDirs = true);
    /**
     * Gets the used space of a specified file system.
     * | Obtém o espaço usado de um sistema de arquivos especificado.
     * @param fs File system to check. | Sistema de arquivos a ser verificado.
     * @param directory Directory to check. | Diretório a ser verificado.
     * @param includeSubDirs Whether to include subdirectories. | Se deve incluir subdiretórios.
     * @return Used space in bytes. | Espaço usado em bytes.
     */
    size_t getUsedSpace(fs::FS& fs, const String& directory = "/", bool includeSubDirs = true);


    /**
     * Gets the available space of a specified file system.
     * | Obtém o espaço disponível de um sistema de arquivos especificado.
     * @return Available space in bytes. | Espaço disponível em bytes.
     */    
    size_t getAvailableSpace();
    /**
     * Gets the available space of a specified file system.
     * | Obtém o espaço disponível de um sistema de arquivos especificado.
     * @param fs File system to check. | Sistema de arquivos a ser verificado.
     * @return Available space in bytes. | Espaço disponível em bytes.
     */    
    size_t getAvailableSpace(fs::FS& fs);


    /**
     * Gets the size of a specified file from a specific file system.
     * | Obtém o tamanho de um arquivo especificado de um sistema de arquivos específico.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file. | Nome do arquivo.
     * @return Size of the file in bytes. | Tamanho do arquivo em bytes.
     */
    size_t getFileSize(const String& fileName);
    /**
     * Gets the size of a specified file from a specific file system.
     * | Obtém o tamanho de um arquivo especificado de um sistema de arquivos específico.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file. | Nome do arquivo.
     * @return Size of the file in bytes. | Tamanho do arquivo em bytes.
     */
    size_t getFileSize(fs::FS& fs, const String& fileName);


    /**
     * Gets the name of the FIRST file in a directory from a specified file system.
     * | Obtém o nome do PRIMEIRO arquivo em um diretório de um sistema de arquivos especificado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the FIRST file. | Nome do PRIMEIRO arquivo.
     */    
    String getFirstFileName(const String& directory = "/");
    /**
     * Gets the name of the FIRST file in a directory from a specified file system.
     * | Obtém o nome do PRIMEIRO arquivo em um diretório de um sistema de arquivos especificado.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the FIRST file. | Nome do PRIMEIRO arquivo.
     */    
    String getFirstFileName(fs::FS& fs, const String& directory = "/");


    /**
     * Gets the name of the LAST file in a directory from a specified file system.
     * | Obtém o nome do ÚLTIMO arquivo em um diretório de um sistema de arquivos especificado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the LAST file. | Nome do arquivo ÚLTIMO.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getLastFileName(const String& directory = "/");
    /**
     * Gets the name of the LAST file in a directory from a specified file system.
     * | Obtém o nome do ÚLTIMO arquivo em um diretório de um sistema de arquivos especificado.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the LAST file. | Nome do arquivo ÚLTIMO.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getLastFileName(fs::FS& fs, const String& directory = "/");


    /**
     * Gets the name of the PREVIOUS file in a directory.
     * | Obtém o nome do arquivo ANTERIOR em um diretório.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the PREVIOUS file. | Nome do arquivo ANTERIOR.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getPreviousFileName(const String& directory = "");
    /**
     * Gets the name of the PREVIOUS file in a directory.
     * | Obtém o nome do arquivo ANTERIOR em um diretório.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the PREVIOUS file. | Nome do arquivo ANTERIOR.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getPreviousFileName(fs::FS& fs, const String& directory = "");


    /**
     * Gets the name of the NEXT file in a directory.
     * | Obtém o nome do PRÓXIMO arquivo em um diretório.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the NEXT file. | Nome do arquivo PRÓXIMO.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getNextFileName(const String& directory = "");
    /**
     * Gets the name of the NEXT file in a directory.
     * | Obtém o nome do PRÓXIMO arquivo em um diretório.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @return Name of the NEXT file. | Nome do arquivo PRÓXIMO.
     * @note The method returns an empty string if the directory is empty or does not exist. | O método retorna uma string vazia se o diretório estiver vazio ou não existir.
     */
    String getNextFileName(fs::FS& fs, const String& directory = "");


    /**
     * Opens a file in the specified file system.
     * | Abre um arquivo no sistema de arquivos especificado.
     * @param fileName Name of the file to open. | Nome do arquivo a ser aberto.
     * @param edit Whether to open the file in edit mode (append) or read mode. | Se deve abrir o arquivo em modo de edição (anexar) ou leitura.
     * @return File object if successful, or an invalid File object if failed. | Objeto File se bem-sucedido, ou um objeto File inválido se falhar.
     */
    File getFile(const String& fileName, bool edit = false);
    /**
     * Opens a file in the specified file system.
     * | Abre um arquivo no sistema de arquivos especificado.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param fileName Name of the file to open. | Nome do arquivo a ser aberto.
     * @param edit Whether to open the file in edit mode (append) or read mode. | Se deve abrir o arquivo em modo de edição (anexar) ou leitura.
     * @return File object if successful, or an invalid File object if failed. | Objeto File se bem-sucedido, ou um objeto File inválido se falhar.
     */
    File getFile(fs::FS& fs, const String& fileName, bool edit = false);


    /**
     * Gets the FIRST file in a directory.
     * | Obtém o PRIMEIRO arquivo em um diretório.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo em modo de anexação.
     * @return File object of the first file. | Objeto File do primeiro arquivo.
     */
    File getFirstFile(const String& directory = "/", bool edit = false);
    /**
     * Gets the FIRST file in a directory.
     * | Obtém o PRIMEIRO arquivo em um diretório.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo em modo de anexação.
     * @return File object of the first file. | Objeto File do primeiro arquivo.
     */
    File getFirstFile(fs::FS& fs, const String& directory = "/", bool edit = false);


    /**
     * Gets the LAST file in a directory.
     * | Obtém o ÚLTIMO arquivo em um diretório.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo em modo de anexação.
     * @return File object of the last file. | Objeto File do último arquivo.
     */
    File getLastFile(const String& directory = "/", bool edit = false);
    /**
     * Gets the LAST file in a directory.
     * | Obtém o ÚLTIMO arquivo em um diretório.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param directory Directory to search in. | Diretório a ser pesquisado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo em modo de anexação.
     * @return File object of the last file. | Objeto File do último arquivo.
     */
    File getLastFile(fs::FS& fs, const String& directory = "/", bool edit = false);


    /**
     * Gets the NEXT file in the current directory.
     * | Obtém o PRÓXIMO arquivo no diretório atual.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo no modo de anexação.
     * @return File object of the next file. | Objeto File do próximo arquivo.
     */
    File getNextFile(bool edit = false);
    /**
     * Gets the NEXT file in the current directory.
     * | Obtém o PRÓXIMO arquivo no diretório atual.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo no modo de anexação.
     * @return File object of the next file. | Objeto File do próximo arquivo.
     */
    File getNextFile(fs::FS& fs, bool edit = false);


    /**
     * Gets the PREVIOUS file in the current directory.
     * | Obtém o arquivo ANTERIOR no diretório atual.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo no modo de anexação.
     * @return File object of the next file. | Objeto File do próximo arquivo.
     */
    File getPreviousFile(bool edit = false);
    /**
     * Gets the PREVIOUS file in the current directory.
     * | Obtém o arquivo ANTERIOR no diretório atual.
     * @param fs File system to use. | Sistema de arquivos a ser usado.
     * @param edit If true, opens the file in append mode. | Se verdadeiro, abre o arquivo no modo de anexação.
     * @return File object of the next file. | Objeto File do próximo arquivo.
     */
    File getPreviousFile(fs::FS& fs, bool edit = false);


    /**
     * Copies a file from one file system to another.
     * | Copia um arquivo de um sistema de arquivos para outro.
     * @param sourceFileName Source file name. | Nome do arquivo de origem.
     * @param destFileName Destination file name. | Nome do arquivo de destino.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     * @note This method does not support copying files between SPIFFS and LittleFS. | Este método não suporta copiar arquivos entre SPIFFS e LittleFS.
     */
    bool copy(const String& sourceFileName, const String& destFileName);
    /**
     * Copies a file from one file system to another.
     * | Copia um arquivo de um sistema de arquivos para outro.
     * @param sourceFileName Source file name. | Nome do arquivo de origem.
     * @param destFS Destination file system. | Sistema de arquivos de destino.
     * @param destFileName Destination file name. | Nome do arquivo de destino.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     * @note This method does not support copying files between SPIFFS and LittleFS. | Este método não suporta copiar arquivos entre SPIFFS e LittleFS.
     */
    bool copy(const String& sourceFileName, fs::FS& destFS, const String& destFileName);
    /**
     * Copies a file from one file system to another.
     * | Copia um arquivo de um sistema de arquivos para outro.
     * @param sourceFS Source file system. | Sistema de arquivos de origem.
     * @param sourceFileName Source file name. | Nome do arquivo de origem.
     * @param destFS Destination file system. | Sistema de arquivos de destino.
     * @param destFileName Destination file name. | Nome do arquivo de destino.
     * @return True if successful, false otherwise. | Verdadeiro se bem-sucedido, falso caso contrário.
     * @note This method does not support copying files between SPIFFS and LittleFS. | Este método não suporta copiar arquivos entre SPIFFS e LittleFS.
     */
    bool copy(fs::FS& sourceFS, const String& sourceFileName, fs::FS& destFS, const String& destFileName);

};

#endif