#include "ES_File.h"
#include <esp_log.h>

// <<< Constructor for ES_File class. | Construtor para a classe ES_File. >>>
ES_File::ES_File() {
    // Nothing to initialize in constructor
}


// <<< Initializes the file system | Inicializa o sistema de arquivos. >>>
bool ES_File::_initFileSystem(fs::FS* fs) {
    if (fs == nullptr) {
        ESP_LOGE("ES_File", "File system pointer is null");
        return false;
    }

    // Flags estáticos para evitar reinicialização múltipla | Static flags to avoid multiple re-inits
    static bool sdInitialized = false;
    static bool spiffsInitialized = false;
    static bool littlefsInitialized = false;

    bool returnValue = false;
    if (fs == &SD) {
        if (!sdInitialized) {
            returnValue = SD.begin(SS);
            if (returnValue) {
                ESP_LOGI("ES_File", "SD Card initialized");
                sdInitialized = true;
            } else {
                ESP_LOGE("ES_File", "Failed to initialize SD Card");
            }
        } else {
            returnValue = true;
            // Já inicializado, não chama SD.begin novamente | Already initialized, skip SD.begin()
        }
    } else if (fs == &SPIFFS) {
        if (!spiffsInitialized) {
            returnValue = SPIFFS.begin(true);
            if (returnValue) {
                ESP_LOGI("ES_File", "SPIFFS initialized");
                spiffsInitialized = true;
            } else {
                ESP_LOGE("ES_File", "Failed to initialize SPIFFS");
            }
        } else {
            returnValue = true;
            // Já inicializado, não chama SPIFFS.begin novamente | Already initialized, skip SPIFFS.begin()
        }
    } else if (fs == &LittleFS) {
        if (!littlefsInitialized) {
            returnValue = LittleFS.begin(true);
            if (!returnValue) {
                ESP_LOGE("ES_File", "Failed to initialize LittleFS. Formatting...");
                if (LittleFS.format()) {
                    ESP_LOGI("ES_File", "LittleFS formatted successfully");
                    returnValue = LittleFS.begin(true);
                } else {
                    ESP_LOGE("ES_File", "Failed to format LittleFS");
                }
            }
            if (returnValue) {
                ESP_LOGI("ES_File", "LittleFS initialized");
                littlefsInitialized = true;
            }
        } else {
            returnValue = true;
            // Já inicializado, não chama LittleFS.begin novamente | Already initialized, skip LittleFS.begin()
        }
    } else {
        ESP_LOGE("ES_File", "Unknown file system pointer");
        return false;
    }

    return returnValue;
}


// <<< Normalizes a file or directory path. | Normaliza um caminho de arquivo ou diretório. >>>
String ES_File::_normalizePath(fs::FS& fs, const String& path) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return "";
    }

    if (path.isEmpty()) {
        return "/";
    }

    String pathStr = path;

    // Adiciona "/" ao início do caminho, se necessário
    if (pathStr.length() > 0 && pathStr[0] != '/') {
        pathStr = "/" + pathStr;
    }

    // Remove a barra final, se presente (exceto para "/")
    if (pathStr.length() > 1 && pathStr[pathStr.length() - 1] == '/') {
        pathStr = pathStr.substring(0, pathStr.length() - 1);
    }

    if(&fs == &SPIFFS) {    // SPIFFS não suporta diretórios
        int lastSlashIndex = pathStr.lastIndexOf('/'); // Encontra o último índice de '/'
        if (lastSlashIndex >= 0) {  //
            return pathStr.substring(lastSlashIndex);
        }
    }
    return pathStr;
}


// <<< Saves information to a file. | Salva informações em um arquivo. >>>
bool ES_File::_writeContent(fs::FS* fs, const String& fileName, const String& content, bool addNewLine, bool createNew) {
    if (fs == nullptr) {    // File system pointer is null | Ponteiro do sistema de arquivos é nulo
        ESP_LOGE("ES_File", "File system pointer is null");
        return false;
    }

    if(!_initFileSystem(fs)) {  // Initialize the file system | Inicializa o sistema de arquivos
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    String pathStr = _normalizePath(*fs, fileName); // Normalize the path | Normaliza o caminho

    if(pathStr == "/") {    // Invalid path | Caminho inválido
        ESP_LOGE("ES_File", "Invalid file path: %s", pathStr.c_str());
        return false; // Invalid path
    }

    const char* fileMode = createNew ? "w" : "a";   // Open file in write mode or append mode | Abre o arquivo em modo de escrita ou modo de anexação
    _fileHandle.close(); // Close any previously opened file handle | Fecha qualquer ponteiro de arquivo aberto anteriormente

    if (fs != &SPIFFS) {    // If not using SPIFFS, create the directory if it doesn't exist | Se não estiver usando SPIFFS, cria o diretório se não existir
        createDirectory(*fs, _extractDirectoryFromPath(pathStr));   // Create the directory if it doesn't exist | Cria o diretório se não existir
    }
    _fileHandle = fs->open(pathStr, fileMode);  // Open the file | Abre o arquivo
    
    if (!_fileHandle) {
        ESP_LOGE("ES_File", "Failed to open file for writing: %s", pathStr);
        return false;
    }
    
    if (addNewLine) _fileHandle.println(content);
    else _fileHandle.print(content);
    
    _fileHandle.close();
    _fileName = pathStr;    // Store the file name | Armazena o nome do arquivo
    return true;
}


// <<<  Removes all files in a directory or the root. | Remove todos os arquivos em um diretório ou na raiz. >>>
bool ES_File::_removeAllFiles(fs::FS& fs, const String& directory) {
    String pathStr;
    if(&fs == &SPIFFS) {
        pathStr = "/"; 
    }else{
        pathStr = _normalizePath(fs, directory);
    }

    // Abre o diretório
    File root = fs.open(pathStr.c_str());
    if (!root || !root.isDirectory()) {
        ESP_LOGE("ES_File", "Failed to open directory: %s", pathStr.c_str());
        return false;
    }

    if(&fs == &SPIFFS) {
        pathStr = ""; 
    }

    // Itera pelos arquivos e subdiretórios
    File file = root.openNextFile();
    while (file) {
        String filePath = pathStr + "/" + file.name();
        if (file.isDirectory()) {
            // Ignora subdiretórios
            ESP_LOGI("ES_File", "Skipping subdirectory: %s", filePath.c_str());
        } else {
            file.close();   // Fecha o arquivo antes de removê-lo
            // Remove arquivo
            if (!fs.remove(filePath.c_str())) {
                ESP_LOGE("ES_File", "Failed to remove file: %s", filePath.c_str());
                root.close();
                return false;
            }
            ESP_LOGI("ES_File", "File removed: %s", filePath.c_str());
        }

        file = root.openNextFile();
    }
    root.close();
    return true;
}


// <<< Extracts the directory name from a file path. | Extrai o nome do diretório de um caminho de arquivo. >>>
String ES_File::_extractDirectoryFromPath(const String& path) {
    int length = path.length();
    for (int i = length - 1; i >= 0; i--) {
        if (path[i] == '/') {
            String dir = path.substring(0, i);
            if (dir.length() == 0) {
                return "/";
            }
            if (dir[0] != '/') {
                dir = "/" + dir;
            }
            return dir;
        }
    }
    return "/";
}


// <<< Lists all files in a directory (internal helper, sorted alphabetically). | Lista todos os arquivos em um diretório (função interna de apoio, ordenados alfabeticamente). >>>
String ES_File::_listFilesInDirectory(fs::FS& fs, const String& path, bool showFileSize, bool showSubDir, bool openSubDir, bool indentation, bool showTotalSize, uint8_t tabCount) {
    if(openSubDir) showSubDir = true; // If openSubDir is true, showSubDir must be true | Se openSubDir for verdadeiro, showSubDir deve ser verdadeiro
    
    String pathStr = _normalizePath(fs, path);  // Normalize and prepare path | Normaliza e prepara o caminho
    if (&fs == &SPIFFS) {
        pathStr = "/";
    }
    File dir = fs.open(pathStr);
    if (!dir) {
        ESP_LOGE("listAllFiles", "Failed to open directory: %s", pathStr.c_str());
        return "";
    }
    if (!dir.isDirectory()) {
        ESP_LOGE("listAllFiles", "Not a directory: %s", pathStr.c_str());
        dir.close();
        return "";
    }

    // If calculating total size only, iterate through entries and sum sizes | Se calculando apenas o tamanho total, iterar pelas entradas e somar tamanhos
    size_t totalSizeValue = 0;
    if (showTotalSize) {
        while (true) {
            File entry = dir.openNextFile();
            if (!entry) {
                dir.rewindDirectory();
                break;
            }
            if (entry.isDirectory()) {
                // If including subdirectories, accumulate their size recursively | Se incluindo subdiretórios, acumula o tamanho deles recursivamente
                if (openSubDir && showSubDir) {
                    String subDirPath = (pathStr == "/" ? String("/") + entry.name()
                                                        : pathStr + String("/") + entry.name());
                    entry.close();
                    totalSizeValue += _listFilesInDirectory(fs, subDirPath, false,
                                                           showSubDir, openSubDir,
                                                           false, true, 0).toInt();
                    continue;  // skip closing, next iteration | pula fechamento, próxima iteração
                }
            } else {
                totalSizeValue += entry.size();
            }
            entry.close();
        }
        dir.close();
        // Return total size as string | Retorna o tamanho total como string
        return String(totalSizeValue);
    }

    // Otherwise, list entries (always sorted alphabetically) | Caso contrário, lista as entradas (sempre ordenadas alfabeticamente)
    struct FileInfo { String name; bool isDir; size_t size; };
    std::vector<FileInfo> entries;
    entries.reserve(10); // reserve space (assuming few files) | reserva espaço (assumindo poucos arquivos)
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            dir.rewindDirectory();
            break;
        }
        FileInfo info;
        info.name = entry.name();
        info.isDir = entry.isDirectory();
        info.size = info.isDir ? 0 : entry.size();
        entry.close();
        entries.push_back(info);
    }
    // Sort by name (alphabetical order) | Ordena por nome (ordem alfabética)
    std::sort(entries.begin(), entries.end(),
              [](const FileInfo& a, const FileInfo& b) {
                  return a.name.compareTo(b.name) < 0;
              });
    // Iterate sorted entries and build output | Itera as entradas ordenadas e constrói a saída
    String result = "";
    for (auto& info : entries) {
        if (info.isDir) {
            if (showSubDir) {
                // Write directory name (with indent or full path) | Escreve o nome do diretório (com indentação ou caminho completo)
                if (indentation) {
                    for (uint8_t i = 0; i < tabCount; ++i) {
                        result += " ";
                    }
                    result += info.name + "/\n";
                } else {
                    String fullPath = (pathStr == "/" ? String("/") + info.name
                                                      : pathStr + String("/") + info.name);
                    result += fullPath + "/\n";
                }
                // Recurse into subdirectory if needed | Lista recursivamente o subdiretório, se necessário
                if (openSubDir) {
                    String subDirPath = (pathStr == "/" ? String("/") + info.name
                                                  : pathStr + String("/") + info.name);
                    File subDir = fs.open(subDirPath);
                    if (subDir) {
                        subDir.close();
                        String subDirResult = _listFilesInDirectory(fs, subDirPath,
                                               showFileSize, showSubDir, openSubDir,
                                               indentation, false, tabCount + 1);
                        result += subDirResult;
                    } else {
                        ESP_LOGE("ES_File", "Failed to open subdirectory: %s", subDirPath.c_str());
                    }
                }
            }
        } else {
            // Write file name (with indent or full path) and size if needed | Escreve o nome do arquivo (com indentação ou caminho completo) e tamanho, se necessário
            if (indentation) {
                for (uint8_t i = 0; i < tabCount; ++i) {
                    result += " ";
                }
                result += info.name;
            } else {
                String fullPath = (pathStr == "/" ? String("/") + info.name
                                                  : pathStr + String("/") + info.name);
                result += fullPath;
            }
            if (showFileSize) {
                result += " " + String(info.size);
            }
            result += "\n";
        }
    }
    dir.close();
    return result;
}


// <<< Locates a file in a directory based on specified option. | Localiza um arquivo em um diretório com base na opção especificada. >>>
String ES_File::_locateFile(fs::FS* fs, const String& fileOrDirPath, char option) {
    if (fs == nullptr) {
        ESP_LOGE("ES_File", "File system pointer is null");
        return "";
    }
    if (!_initFileSystem(fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return "";
    }
    
    String path = _normalizePath(*fs, fileOrDirPath);   // Normaliza o caminho de entrada | Normalize the input path

    // Determina o diretório de busca | Determine the directory to search in
    String directoryPath;
    File dir;
    if (fs == &SPIFFS) {
        // SPIFFS não suporta hierarquia de diretórios – usar raiz | SPIFFS doesn’t support directories – use root
        directoryPath = "/";  
        dir = fs->open("/");  // Abrir raiz para listar | Open root for listing
        // **Nota:** `dir.isDirectory()` pode ser false no SPIFFS, mas ainda permite openNextFile()
    } else {
        // Verifica se o caminho existe e obtém o diretório apropriado | Check if path exists and get proper directory
        if (!fs->exists(path.c_str())) {
            return "";
        }
        File target = fs->open(path.c_str());
        if (!target) {
            ESP_LOGE("ES_File", "Failed to open path: %s", path.c_str());
            return "";
        }
        if (target.isDirectory()) {
            directoryPath = path;   // Caminho já é um diretório | Path is already a directory
        } else {
            directoryPath = _extractDirectoryFromPath(path);
        }
        target.close();
        dir = fs->open(directoryPath.c_str());
        if (!dir || !dir.isDirectory()) {
            ESP_LOGE("ES_File", "Failed to open directory: %s", directoryPath.c_str());
            return "";
        }
    }

    // Ajusta prefixo para concatenação correta dos nomes | Adjust prefix for correct name concatenation
    String basePath = directoryPath;
    if (basePath == "/") {
        basePath = "";  // Usar string vazia para diretório raiz | Use empty string for root directory
    }

    // Percorre todos os arquivos do diretório e armazena os nomes | Iterate and collect all file names in the directory
    File entry;
    std::vector<String> fileList;
    
    while ((entry = dir.openNextFile())) {
        if (!entry.isDirectory()) {
            String entryName = basePath + "/" + entry.name();
            fileList.push_back(entryName);
        }
        entry.close();
    }
    dir.close();

    if (fileList.empty()) {
        // Nenhum arquivo encontrado no diretório | No files found in the directory
        return "";
    }

    // Ordena os nomes dos arquivos em ordem alfabética | Sort file names alphabetically
    std::sort(fileList.begin(), fileList.end());

    // Seleciona o arquivo com base na opção | Select file based on the option
    String result;
    if (option == 'F') {
        result = fileList.front();   // Primeiro arquivo
    } else if (option == 'L') {
        result = fileList.back();    // Último arquivo
    } else if (option == 'N' || option == 'P') {
        // Garante que o caminho fornecido corresponda a um arquivo na lista | Ensure the provided path corresponds to a file in the list
        String currentFile = path;
        int index = -1;
        for (size_t i = 0; i < fileList.size(); ++i) {
            if (fileList[i] == currentFile) {
                index = i;
                break;
            }
        }
        if (option == 'N') {
            if (index >= 0 && index < (int)fileList.size() - 1) {
                result = fileList[index + 1];      // Próximo arquivo na lista
            } else {
                result = fileList.front();         // Se não há próximo, volta ao primeiro | Wrap to first
            }
        } else { // option == 'P'
            if (index > 0) {
                result = fileList[index - 1];      // Arquivo anterior na lista
            } else {
                result = fileList.back();          // Se não há anterior, vai para o último | Wrap to last
            }
        }
    } else {
        return "";  // Opção inválida | Invalid option
    }
    
    _fileName = result.c_str(); // Armazena o último nome de arquivo usado e retorna | Store the last used file name and return
    return result;
}


// <<< Copies a directory from one file system to another. | Copia um diretório de um sistema de arquivos para outro. >>>
bool ES_File::_copyDirectory(fs::FS& sourceFS, const String& sourceDirName, fs::FS& destFS, const String& destDirName) {
    if (!_initFileSystem(&sourceFS)) {
        ESP_LOGE("ES_File", "Failed to initialize source file system");
        return false;
    }
    
    if (!_initFileSystem(&destFS)) {
        ESP_LOGE("ES_File", "Failed to initialize destination file system");
        return false;
    }
    // Normaliza os caminhos de origem e destino
    String sourcePath = _normalizePath(sourceFS, sourceDirName);
    String destPath = _normalizePath(destFS, destDirName);

    // Abre o diretório de origem
    File sourceDir = sourceFS.open(sourcePath);
    if (!sourceDir || !sourceDir.isDirectory()) {
        ESP_LOGE("ES_File", "Source is not a directory: %s", sourcePath.c_str());
        return false;
    }

    // Cria o diretório de destino, se necessário (exceto para SPIFFS)
    if (&destFS != &SPIFFS) {
        if (!createDirectory(destFS, destPath)) {
            ESP_LOGE("ES_File", "Failed to create destination directory: %s", destPath.c_str());
            sourceDir.close();
            return false;
        }
    }

    // Itera pelos arquivos e subdiretórios no diretório de origem
    File file = sourceDir.openNextFile();
    while (file) {
        String sourceFilePath = sourcePath + "/" + file.name();
        String destFilePath = destPath + "/" + file.name();

        if (file.isDirectory()) {
            // Recursivamente copia subdiretórios
            file.close();
            if (!_copyDirectory(sourceFS, sourceFilePath, destFS, destFilePath)) {
                sourceDir.close();
                return false;
            }
        } else {
            // Copia arquivos
            file.close();
            if (!copy(sourceFS, sourceFilePath, destFS, destFilePath)) {
                sourceDir.close();
                return false;
            }
        }

        file = sourceDir.openNextFile();
    }

    sourceDir.close();
    return true;
}


// <<< Removes a file. | Remove um arquivo. >>>
bool ES_File::_removeFile(fs::FS& fs, const String& fileName) {
    if (!_initFileSystem(&fs)) {    // Initialize the file system | Inicializa o sistema de arquivos
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    String pathStr = _normalizePath(fs, fileName);
    
    if (!fs.exists(pathStr)) {
        ESP_LOGW("ES_File", "File does not exist: %s", pathStr);
        return false;
    }

    String previousFileName = getPreviousFileName(fs); // Store the previous file name | Armazena o nome do arquivo anterior
    
    if (!fs.remove(pathStr)) {
        ESP_LOGE("ES_File", "Failed to remove file: %s", pathStr);
        return false;
    }

    _fileName = previousFileName; // Restore the previous file name | Restaura o nome do arquivo anterior
    return true;
}


// <<< Removes a directory and all its contents (files and subdirectories). | Remove um diretório e todo o seu conteúdo (arquivos e subdiretórios). >>>
bool ES_File::_removeDirectory(fs::FS& fs, const String& directory) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    if(&fs == &SPIFFS) {    // If the file system is SPIFFS | Se o sistema de arquivos for SPIFFS
        return _removeAllFiles(fs, directory); // Remove all files in the directory | Remove todos os arquivos no diretório
    }

    String pathStr = _normalizePath(fs, directory);

    if (!fs.exists(pathStr.c_str())) {  // Check if the directory exists | Verifica se o diretório existe
        ESP_LOGE("ES_File", "Directory does not exist: %s", pathStr.c_str());
        return false;
    }

    File root = fs.open(pathStr.c_str());
    if (!root || !root.isDirectory()) { // Check if the path is a directory | Verifica se o caminho é um diretório
        ESP_LOGE("ES_File", "Failed to open directory: %s", pathStr.c_str());
        return false;
    }

    File file = root.openNextFile();
    while (file) {
        String filePath = pathStr + "/" + file.name();

        if (file.isDirectory()) {   // Recursively remove subdirectories | Remove subdiretórios recursivamente
            file.close();
            if (!_removeDirectory(fs, filePath)) {
                root.close();
                return false;
            }
        } else {    // Remove files | Remove arquivos
            file.close();
            if (!fs.remove(filePath.c_str())) {
                ESP_LOGE("ES_File", "Failed to remove file: %s", filePath.c_str());
                root.close();
                return false;
            }
            ESP_LOGI("ES_File", "File removed: %s", filePath.c_str());
        }

        file = root.openNextFile();
    }

    root.close();

    if (pathStr == "/") {   // If the path is the root directory | Se o caminho for o diretório raiz
        ESP_LOGI("ES_File", "Root directory cleaned successfully");
        return true;
    }
    
    if (!fs.rmdir(pathStr.c_str())) {   // Remove the directory | Remove o diretório
        ESP_LOGE("ES_File", "Failed to remove directory: %s", pathStr.c_str());
        return false;
    }

    ESP_LOGI("ES_File", "Directory removed successfully: %s", pathStr.c_str());
    return true;
}


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ================================== Public methods ======================================
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// <<< Initializes the file system. | Inicializa o sistema de arquivo. >>>
bool ES_File::begin(fs::FS& fs) {
    if(_initFileSystem(&fs)) {
        _fileSystem = &fs;
        return true;
    }else{
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }
}


// <<< Lists all files in a directory. | Lista todos os arquivos em um diretório. >>>
String ES_File::listAllFiles(const String& directory, bool showFileSize, bool showSubDir, bool openSubDir, bool indentation) {
    return listAllFiles(*_fileSystem, directory, showFileSize, showSubDir, openSubDir, indentation);
}

String ES_File::listAllFiles(fs::FS& fs, const String& directory, bool showFileSize, bool showSubDir, bool openSubDir, bool indentation) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("listAllFiles", "Failed to initialize file system");
        return "";
    }
    // Use unified internal function to list files | Usa função interna unificada para listar arquivos
    return _listFilesInDirectory(fs, directory, showFileSize, showSubDir, openSubDir, indentation);
}


// <<< Checks if a file exists. | Verifica se um arquivo existe. >>>
bool ES_File::exists(const String& fileName) {
    return exists(*_fileSystem, fileName);
}

bool ES_File::exists(fs::FS& fs, const String& fileName) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }
    String _fileName = _normalizePath(fs, fileName);
    return fs.exists(_fileName);
}


// <<< Checks if a directory exists. | Verifica se um diretório existe. >>>
bool ES_File::directoryExists(const String& directory) {
    return directoryExists(*_fileSystem, directory);
}

bool ES_File::directoryExists(fs::FS& fs, const String& directory) {
    if (!_initFileSystem(&fs)) {    // Initialize the file system | Inicializa o sistema de arquivos
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    String pathStr = _normalizePath(fs, directory);

    if (!fs.exists(pathStr.c_str())) {  // Check if the path exists | Verifica se o caminho existe
        return false;
    }

    File dir = fs.open(pathStr.c_str());
    if (dir && dir.isDirectory()) { // Check if the path is a directory | Verifica se o caminho é um diretório
        dir.close();
        return true;
    }

    if (dir) {
        dir.close();
    }
    return false;
}


// <<< Prints text to a file with a newline character. | Imprime texto em um arquivo com um caractere de nova linha. >>>
bool ES_File::println(const String& fileName, const String& content, bool createNew) {
    return println(*_fileSystem, fileName, content, createNew);
}

bool ES_File::println(const String& fileName, int content, bool createNew) {
    return println(*_fileSystem, fileName, String(content), createNew);
}

bool ES_File::println(const String& fileName, double content, bool createNew, uint8_t decimalPlaces) {
    return println(*_fileSystem, fileName, String(content, (unsigned int)decimalPlaces), createNew);
}

bool ES_File::println(fs::FS& fs, const String& fileName, const String& content, bool createNew) {
    return _writeContent(&fs, fileName, content, true, createNew);
}


// <<< Prints text to a file without a newline character. | Imprime texto em um arquivo sem um caractere de nova linha. >>>
bool ES_File::print(const String& fileName, const String& content, bool createNew) {
    return print(*_fileSystem, fileName, content, createNew);
}

bool ES_File::print(const String& fileName, int content, bool createNew) {
    return print(*_fileSystem, fileName, String(content), createNew);
}

bool ES_File::print(const String& fileName, double content, bool createNew, uint8_t decimalPlaces) {
    return print(*_fileSystem, fileName, String(content, (unsigned int)decimalPlaces), createNew);
}

bool ES_File::print(fs::FS& fs, const String& fileName, const String& content, bool createNew) {
    return _writeContent(&fs, fileName, content, false, createNew);
}


// <<< Reads the content of a file. | Lê o conteúdo de um arquivo. >>>
String ES_File::readFile(const String& fileName) {
    return readFile(*_fileSystem, fileName);
}

String ES_File::readFile(fs::FS& fs, const String& fileName) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return "";
    }

    String pathStr = _normalizePath(fs, fileName);  // Normalize the file path | Normaliza o caminho do arquivo

    File file = fs.open(pathStr, "r");  // Open the file for reading | Abre o arquivo para leitura
    if (!file) {
        ESP_LOGE("ES_File", "Failed to open file for reading: %s", pathStr.c_str());
        return "";
    }

    String content = "";
    while (file.available()) {  // Read the file content | Lê o conteúdo do arquivo
        content += (char)file.read();
    }

    file.close();
    _fileName = pathStr;
    return content;
}


// <<< Reads a specific line from a file. | Lê uma linha específica de um arquivo. >>>
String ES_File::readLine(const String& fileName, size_t lineNumber) {
    if (!_fileSystem) {
        return "";
    }

    File file = _fileSystem->open(fileName, FILE_READ);
    if (!file) {    // File not found | Arquivo não encontrado
        return ""; 
    }

    size_t currentLine = 0;
    String lineContent = "";

    while (file.available()) {  // Read the file line by line | Lê o arquivo linha por linha
        lineContent = file.readStringUntil('\n');
        currentLine++;

        if (currentLine == lineNumber) {    // If the current line matches the requested line number | Se a linha atual corresponder ao número da linha solicitada
            file.close();
            return lineContent;
        }
    }

    file.close();
    return "";
}


// <<< Counts the number of lines in a file. | Conta o número de linhas em um arquivo. >>>
size_t ES_File::countLines(const String& fileName) {
    if (!_fileSystem) {
        return 0; 
    }

    File file = _fileSystem->open(fileName, FILE_READ);
    if (!file) {
        return 0;
    }

    size_t lineCount = 0;

    while (file.available()) {  // Read the file line by line | Lê o arquivo linha por linha
        file.readStringUntil('\n');
        lineCount++;
    }
    file.close();
    return lineCount;
}


// <<< Removes a file or directory. | Remove um arquivo ou diretório. >>>
bool ES_File::remove(const String& path, bool recursive) {
    return remove(*_fileSystem, path, recursive);
}
bool ES_File::remove(fs::FS& fs, const String& path, bool recursive) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    String normalizedPath = _normalizePath(fs, path);

    if (&fs == &SPIFFS) {   // If the file system is SPIFFS. | Se o sistema de arquivos for SPIFFS.
        if (exists(fs, normalizedPath)) {   // Check if the path exists | Verifica se o caminho existe
            return _removeFile(fs, normalizedPath);
        }else if(normalizedPath == "/") {   // If the path is the root directory | Se o caminho for o diretório raiz.
            return _removeDirectory(fs, normalizedPath);
        }else{
            ESP_LOGE("ES_File", "Path does not exist: %s", normalizedPath.c_str());
            return false;
        }
    }else{  // If the file system is NOT SPIFFS. | Se o sistema de arquivos NÃO for SPIFFS.
        if (!exists(fs, normalizedPath)) {  // Check if the path exists | Verifica se o caminho existe
            ESP_LOGE("ES_File", "Path does not exist: %s", normalizedPath.c_str());
            return false;
        }

        if (directoryExists(fs, normalizedPath)) {  // Check if the path is a directory | Verifica se o caminho é um diretório
            if (recursive) {
                return _removeDirectory(fs, normalizedPath); // Remove the directory and its contents | Remove o diretório e seu conteúdo
            } else {
                return _removeAllFiles(fs, normalizedPath); // Remove all files in the directory | Remove todos os arquivos no diretório
            }
        } else {
            return _removeFile(fs, normalizedPath);  // Remove a single file | Remove um único arquivo
        }
    }
}


// <<< Creates a directory. | Cria um diretório. >>>
bool ES_File::createDirectory(const String& directory) {
    return createDirectory(*_fileSystem, directory);
}

bool ES_File::createDirectory(fs::FS& fs, const String& directory) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }

    if (&fs == &SPIFFS) {   // SPIFFS does not support directories. | SPIFFS não suporta diretórios.
        ESP_LOGE("ES_File", "SPIFFS does not support directories.");
        return false;
    }

    String pathStr = _normalizePath(fs, directory);

    if (fs.exists(pathStr.c_str())) {   // Check if the path exists | Verifica se o caminho existe
        File file = fs.open(pathStr.c_str());
        bool isDir = file.isDirectory();
        file.close();

        if (isDir) {
            ESP_LOGI("ES_File", "Directory already exists: %s", pathStr.c_str());
            return true;
        } else {
            ESP_LOGE("ES_File", "Path exists but is not a directory: %s", pathStr.c_str());
            return false;
        }
    }

    int lastSlash = pathStr.lastIndexOf('/');
    if (lastSlash > 0) {
        String parentPath = pathStr.substring(0, lastSlash);
        if (!createDirectory(fs, parentPath)) {
            return false;
        }
    }

    if (!fs.mkdir(pathStr.c_str())) {   // Create the directory | Cria o diretório
        ESP_LOGE("ES_File", "Failed to create directory: %s", pathStr.c_str());
        return false;
    }

    return true;
}


// <<< Moves a file or directory. | Move um arquivo ou diretório. >>>
bool ES_File::move(const String& sourcePath, const String& destinationPath) {
    return move(*_fileSystem, sourcePath, destinationPath);
}
bool ES_File::move(fs::FS& fs, const String& sourcePath, const String& destinationPath) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return false;
    }
    
    String normalizeSource      = _normalizePath(fs, sourcePath);
    String normalizeDestination = _normalizePath(fs, destinationPath);
    
    if (!fs.exists(normalizeSource.c_str())) {   // Check if the source file exists | Verifica se o arquivo de origem existe
        ESP_LOGE("ES_File", "Source file does not exist: %s", normalizeSource.c_str());
        return false;
    }
    
    createDirectory(fs, _extractDirectoryFromPath(normalizeDestination)); // Create the destination directory if it doesn't exist | Cria o diretório de destino se não existir
    
    if (!fs.rename(normalizeSource.c_str(), normalizeDestination.c_str())) {  // Rename the file | Renomeia o arquivo
        ESP_LOGE("ES_File", "Failed to rename file from %s to %s", normalizeSource.c_str(), normalizeDestination.c_str());
        return false;
    }
    
    _fileName = normalizeDestination;
    
    return true;
}


// <<< Gets the total space of the file system. | Obtém o espaço total do sistema de arquivos. >>>
size_t ES_File::getTotalSpace() {
    return getTotalSpace(*_fileSystem);
}

size_t ES_File::getTotalSpace(fs::FS& fs) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return 0;
    }
        
    if (&fs == &SD) {
        return SD.totalBytes();
    } else if (&fs == &SPIFFS) {
        return SPIFFS.totalBytes();
    } else if (&fs == &LittleFS) {
        return LittleFS.totalBytes();
    } else {
        ESP_LOGW("ES_File", "getTotalSpace not fully implemented for this file system");
        return 0;
    }
}


// <<< Gets the used space of the file system. | Obtém o espaço usado do sistema de arquivos. >>>
size_t ES_File::getUsedSpace(const String& directory, bool includeSubDirs) {
    return getUsedSpace(*_fileSystem, directory, includeSubDirs);
}

size_t ES_File::getUsedSpace(fs::FS& fs, const String& directory, bool includeSubDirs) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("listAllFiles", "Failed to initialize file system");
        return 0;
    }
    // Get total size as string and convert to size_t | Obtém o tamanho total como string e converte para size_t
    String totalStr = _listFilesInDirectory(fs, directory, false, includeSubDirs, includeSubDirs, true, true);

    // Remove trailing newline if present | Remove a quebra de linha final, se presente
    if (totalStr.endsWith("\n")) {
        totalStr = totalStr.substring(0, totalStr.length() - 1);
    }

    return totalStr.toInt();
}


// <<< Gets the available space of the file system. | Obtém o espaço disponível do sistema de arquivos. >>>
size_t ES_File::getAvailableSpace() {
    return getAvailableSpace(*_fileSystem);
}

size_t ES_File::getAvailableSpace(fs::FS& fs) {
    return getTotalSpace(fs) - getUsedSpace(fs);
}


// <<< Gets the size of a file. | Obtém o tamanho de um arquivo. >>>
size_t ES_File::getFileSize(const String& fileName) {
    return getFileSize(*_fileSystem, fileName);
}

size_t ES_File::getFileSize(fs::FS& fs, const String& fileName) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return 0;
    }
    
    String pathStr = _normalizePath(fs, fileName);
    
    if (!fs.exists(pathStr.c_str())) {
        ESP_LOGE("ES_File", "File does not exist: %s", pathStr.c_str());
        return 0;
    }
    
    File file = fs.open(pathStr.c_str(), "r");
    if (!file) {
        ESP_LOGE("ES_File", "Failed to open file for reading: %s", pathStr.c_str());
        return 0;
    }
    
    size_t size = file.size();
    file.close();
    
    _fileName = pathStr.c_str();
    
    return size;
}


// <<< Gets the name of the first file in a directory. | Obtém o nome do primeiro arquivo em um diretório. >>>
String ES_File::getFirstFileName(const String& directory) {
    return getFirstFileName(*_fileSystem, directory);
}
String ES_File::getFirstFileName(fs::FS& fs, const String& directory) {
    return _locateFile(&fs, directory, 'F');
}


// <<< Gets the name of the last file in a directory. | Obtém o nome do último arquivo em um diretório. >>>
String ES_File::getLastFileName(const String& directory) {
    return getLastFileName(*_fileSystem, directory);
}

String ES_File::getLastFileName(fs::FS& fs, const String& directory) {
    return _locateFile(&fs, directory, 'L');    
}


// <<< Gets the name of the previous file in a directory. | Obtém o nome do arquivo anterior em um diretório. >>>
String ES_File::getPreviousFileName(const String& directory) {
    return getPreviousFileName(*_fileSystem, directory);
}

String ES_File::getPreviousFileName(fs::FS& fs, const String& directory) {
    String normalizedDirectory = _normalizePath(fs, directory);

    if (!directory.isEmpty() && fs.exists(normalizedDirectory)) {   // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
        if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
            if (directoryExists(fs, normalizedDirectory)) { // If the directory exists. | Se o diretório existir.
                if (_extractDirectoryFromPath(_fileName).equals(normalizedDirectory)) { // If _fileName belongs to the same directory. | Se _fileName pertence ao mesmo diretório.
                    return _locateFile(&fs, _fileName, 'P');
                }
                return _locateFile(&fs, normalizedDirectory, 'P');
            } else {    // If _fileName and normalizedDirectory are in the same directory. | Se _fileName e normalizedDirectory estão no mesmo diretório.
                /*
                if (_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) {  // If _fileName and normalizedDirectory are in the same directory.
                    return _locateFile(&fs, _fileName, 'P');
                }
                */
                return _locateFile(&fs, normalizedDirectory, 'P');
            }
        }
        return _locateFile(&fs, normalizedDirectory, 'P');
    }

    if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
        if (!directory.isEmpty() && directoryExists(fs, normalizedDirectory)) { // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
            return _locateFile(&fs, normalizedDirectory, 'P');
        }
        if (!directory.isEmpty() && !_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) { // If _fileName and normalizedDirectory are not in the same directory. | Se _fileName e normalizedDirectory não estão no mesmo diretório.
            return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'P');
        }
        return _locateFile(&fs, _fileName, 'P');
    }
    return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'P');
}


// <<< Gets the name of the next file in a directory. | Obtém o nome do próximo arquivo em um diretório. >>>
String ES_File::getNextFileName(const String& directory) {
    return getNextFileName(*_fileSystem, directory);
}
/*
String ES_File::getNextFileName(fs::FS& fs, const String& directory) {
    String normalizedDirectory = _normalizePath(fs, directory);
    Serial.println("directory..........: " + directory);
    Serial.println("normalizedDirectory: " + normalizedDirectory);


    if (!directory.isEmpty() && fs.exists(normalizedDirectory)) {   // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
        Serial.println("111");

        if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
            Serial.println("222");

            if (directoryExists(fs, normalizedDirectory)) { // If the directory exists. | Se o diretório existir.
                Serial.println("333");

                if (_extractDirectoryFromPath(_fileName).equals(normalizedDirectory)) { // If _fileName belongs to the same directory. | Se _fileName pertence ao mesmo diretório.
                    Serial.println("444");
                    Serial.println("_locateFile(&fs, "+ _fileName + ", 'N');");
                    return _locateFile(&fs, _fileName, 'N'); 
                }
                return _locateFile(&fs, normalizedDirectory, 'N');
            } else {    // If _fileName and normalizedDirectory are in the same directory. | Se _fileName e normalizedDirectory estão no mesmo diretório.
                Serial.println("333 - ELSE");

                if (_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) {  // If _fileName and normalizedDirectory are in the same directory.
                    Serial.println("555");
                    Serial.println("_locateFile(&fs, " + _fileName +", 'N');");
                    return _locateFile(&fs, _fileName, 'N');
                }
                Serial.println("_locateFile(&fs, " + normalizedDirectory + ", 'N');");
                return _locateFile(&fs, normalizedDirectory, 'N');
            }
        }
        Serial.println("_locateFile(&fs," + normalizedDirectory +", 'N');");
        return _locateFile(&fs, normalizedDirectory, 'N');
    }

    if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
        Serial.println("666");
        if (!directory.isEmpty() && directoryExists(fs, normalizedDirectory)) { // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
            Serial.println("777");
            Serial.println("_locateFile(&fs, " + normalizedDirectory +", 'N');");
            return _locateFile(&fs, normalizedDirectory, 'N');
        }
        if (!directory.isEmpty() && !_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) { // If _fileName and normalizedDirectory are not in the same directory. | Se _fileName e normalizedDirectory não estão no mesmo diretório.
            Serial.println("888");
            Serial.println("_locateFile(&fs, " + _extractDirectoryFromPath(normalizedDirectory) +", 'N');");
            return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'N');
        }
        Serial.println("_locateFile(&fs, " + _fileName +", 'N');");
        return _locateFile(&fs, _fileName, 'N');
    }
    Serial.println("999");
    Serial.println("_locateFile(&fs, " + _extractDirectoryFromPath(normalizedDirectory) +", 'N');");
    return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'N');
}

*/
String ES_File::getNextFileName(fs::FS& fs, const String& directory) {
    String normalizedDirectory = _normalizePath(fs, directory);

    if (!directory.isEmpty() && fs.exists(normalizedDirectory)) {   // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
        if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
            if (directoryExists(fs, normalizedDirectory)) { // If the directory exists. | Se o diretório existir.
                if (_extractDirectoryFromPath(_fileName).equals(normalizedDirectory)) { // If _fileName belongs to the same directory. | Se _fileName pertence ao mesmo diretório.
                    return _locateFile(&fs, _fileName, 'N'); 
                }
                return _locateFile(&fs, normalizedDirectory, 'N');
            } else {    // If _fileName and normalizedDirectory are in the same directory. | Se _fileName e normalizedDirectory estão no mesmo diretório.
                /*
                if (_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) {  // If _fileName and normalizedDirectory are in the same directory.
                    return _locateFile(&fs, _fileName, 'N');
                }
                */
                return _locateFile(&fs, normalizedDirectory, 'N');
            }
        }
        return _locateFile(&fs, normalizedDirectory, 'N');
    }

    if (!_fileName.isEmpty()) { // If _fileName is not empty. | Se _fileName não estiver vazio.
        if (!directory.isEmpty() && directoryExists(fs, normalizedDirectory)) { // If the directory is not empty and exists. | Se o diretório não estiver vazio e existir.
            return _locateFile(&fs, normalizedDirectory, 'N');
        }
        if (!directory.isEmpty() && !_extractDirectoryFromPath(_fileName).equals(_extractDirectoryFromPath(normalizedDirectory))) { // If _fileName and normalizedDirectory are not in the same directory. | Se _fileName e normalizedDirectory não estão no mesmo diretório.
            return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'N');
        }
        return _locateFile(&fs, _fileName, 'N');
    }
    return _locateFile(&fs, _extractDirectoryFromPath(normalizedDirectory), 'N');
}


// <<< Gets a file object. | Obtém um objeto de arquivo. >>>
File ES_File::getFile(const String& fileName, bool edit) {
    return getFile(*_fileSystem, fileName, edit);
}

File ES_File::getFile(fs::FS& fs, const String& fileName, bool edit) {
    if (!_initFileSystem(&fs)) {
        ESP_LOGE("ES_File", "Failed to initialize file system");
        return File();
    }
    String pathStr = _normalizePath(fs, fileName);
    String fileMode = edit ? "a" : "r";  // Modo de abertura: anexar ou leitura
    if (edit) {
        createDirectory(fs, _extractDirectoryFromPath(pathStr));
    }
    File file = fs.open(pathStr.c_str(), fileMode.c_str());
    if (!file) {
        ESP_LOGE("ES_File", "Failed to open file: %s with mode: %s", pathStr.c_str(), fileMode.c_str());
        return File();
    }
    _fileName = pathStr.c_str();
    return file;
}


// <<< Gets the first file in a directory. | Obtém o primeiro arquivo em um diretório. >>>
File ES_File::getFirstFile(const String& directory, bool edit) {
    return getFirstFile(*_fileSystem, directory, edit);
}

File ES_File::getFirstFile(fs::FS& fs, const String& directory, bool edit) {
    return getFile(fs, getFirstFileName(fs, directory), edit); 
}


// <<< Gets the last file in a directory. | Obtém o último arquivo em um diretório. >>>
File ES_File::getLastFile(const String& directory, bool edit) {
    return getLastFile(*_fileSystem, directory, edit);
}

File ES_File::getLastFile(fs::FS& fs, const String& directory, bool edit) {
    return getFile(fs, getLastFileName(fs, directory), edit); 
}


// <<< Gets the next file in a directory. | Obtém o próximo arquivo em um diretório. >>>
File ES_File::getNextFile(bool edit) {
    return getNextFile(*_fileSystem, edit); 
}
File ES_File::getNextFile(fs::FS& fs, bool edit) {
    return getFile(fs, getNextFileName(fs), edit); 
}


// <<< Gets the previous file in a directory. | Obtém o arquivo anterior em um diretório. >>>
File ES_File::getPreviousFile(bool edit) {
    return getPreviousFile(*_fileSystem, edit); 
}
File ES_File::getPreviousFile(fs::FS& fs, bool edit) {
    return getFile(fs, getPreviousFileName(fs), edit); 
}


// <<< Copies a file from one file system to another. | Copia um arquivo de um sistema de arquivos para outro. >>>
bool ES_File::copy(const String& sourceFileName, const String& destFileName) {
    return copy(*_fileSystem, sourceFileName, *_fileSystem, destFileName);
}
bool ES_File::copy(const String& sourceFileName, fs::FS& destFS, const String& destFileName) {
    return copy(*_fileSystem, sourceFileName, destFS, destFileName);
}
bool ES_File::copy(fs::FS& sourceFS, const String& sourceFileName, fs::FS& destFS, const String& destFileName) {
    if (!_initFileSystem(&sourceFS)) {
        ESP_LOGE("ES_File", "Failed to initialize source file system");
        return false;
    }
    if (!_initFileSystem(&destFS)) {
        ESP_LOGE("ES_File", "Failed to initialize destination file system");
        return false;
    }

    String sourcePath = _normalizePath(sourceFS, sourceFileName);
    String destPath   = _normalizePath(destFS, destFileName);

    if (!sourceFS.exists(sourcePath)) {
        ESP_LOGE("ES_File", "Source path does not exist: %s", sourcePath.c_str());
        return false;
    }

    File sourceFile = sourceFS.open(sourcePath);
    if (!sourceFile) {
        ESP_LOGE("ES_File", "Failed to open source path: %s", sourcePath.c_str());
        return false;
    }

    if (sourceFile.isDirectory()) {
        sourceFile.close();
        return _copyDirectory(sourceFS, sourcePath, destFS, destPath);
    }
    sourceFile.close();

    if (sourcePath.equals(destPath) && (&sourceFS == &destFS)) {
        ESP_LOGE("ES_File", "Cannot copy a file to itself: %s", sourcePath.c_str());
        return false;
    }

    sourceFile = sourceFS.open(sourcePath, "r");
    if (!sourceFile) {
        ESP_LOGE("ES_File", "Failed to open source file: %s", sourcePath.c_str());
        return false;
    }

    if (&destFS != &SPIFFS) {
        if (!createDirectory(destFS, _extractDirectoryFromPath(destPath))) {
            ESP_LOGE("ES_File", "Failed to create destination directory for: %s", destPath.c_str());
            sourceFile.close();
            return false;
        }
    }

    File destFile = destFS.open(destPath, "w");
    if (!destFile) {
        ESP_LOGE("ES_File", "Failed to open destination file: %s", destPath.c_str());
        sourceFile.close();
        return false;
    }

    static const size_t BUFFER_SIZE = 512;
    uint8_t buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = sourceFile.read(buffer, BUFFER_SIZE)) > 0) {
        if (destFile.write(buffer, bytesRead) != bytesRead) {
            ESP_LOGE("ES_File", "Failed to write to destination file: %s", destPath.c_str());
            sourceFile.close();
            destFile.close();
            return false;
        }
    }

    sourceFile.close();
    destFile.close();

    _fileName = destPath;

    return true;
}