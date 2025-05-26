#ifndef ES_TFT_h
#define ES_TFT_h

#include <TFT_eSPI.h>
#include "JPEGDecoder/src/JPEGDecoder.h"
#include "ES_File/ES_File.h"
#include "ES_Camera/ES_Camera.h"

#define ES_TFT_VERSION "0.11.2 update 25/05/2024"

class ES_TFT : public TFT_eSPI {
private:
    #define minimum(a,b)     (((a) < (b)) ? (a) : (b))
    bool _trabalharComArquivos = false;
    ES_File _arquivo;
    bool _compareStr(String str1, String str2);
    bool _renderDecodedJPEG(int xpos, int ypos);

public:
    /**
     * @brief Constructor of the class | Construtor da classe
    */
    ES_TFT(void);


    /**
     * @brief Draws a centered string on the screen | Desenha uma string centralizada na tela
     * @param string A string to be drawn | Uma string a ser desenhada
     * @param y The vertical position to draw the string | A posição vertical para desenhar a string
     * @param font The font size to use (default is 1) | O tamanho da fonte a ser usada (padrão é 1)
    */
    int16_t drawCentreScreenString(const char *string, int32_t y, uint8_t font = 1);
        /**
     * @brief Draws a centered string on the screen | Desenha uma string centralizada na tela
     * @param string A string to be drawn | Uma string a ser desenhada
     * @param y The vertical position to draw the string | A posição vertical para desenhar a string
     * @param font The font size to use (default is 1) | O tamanho da fonte a ser usada (padrão é 1)
    */
    int16_t drawCentreScreenString(const String& string, int32_t y, uint8_t font = 1);


    /**
     * @brief Draws a right-aligned string on the screen | Desenha uma string alinhada à direita na tela
     * @param string A string to be drawn | Uma string a ser desenhada
     * @param y The vertical position to draw the string | A posição vertical para desenhar a string
     * @param font The font size to use (default is 1) | O tamanho da fonte a ser usada (padrão é 1)
    */
    int16_t drawRightScreenString(const char *string, int32_t y, uint8_t font = 1);
    /**
     * @brief Draws a right-aligned string on the screen | Desenha uma string alinhada à direita na tela
     * @param string A string to be drawn | Uma string a ser desenhada
     * @param y The vertical position to draw the string | A posição vertical para desenhar a string
     * @param font The font size to use (default is 1) | O tamanho da fonte a ser usada (padrão é 1)
    */    
    int16_t drawRightScreenString(const String& string, int32_t y, uint8_t font = 1);


    /**
     * @brief Renders a JPEG image from the file system | Renderiza uma imagem JPEG do sistema de arquivos
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param fileName The name of the JPEG file to render | O nome do arquivo JPEG a ser renderizado
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if the image was rendered successfully, false otherwise | Verdadeiro se a imagem foi renderizada com sucesso, falso caso contrário
    */
    bool renderJPEG(fs::FS& fs, const String& fileName, int xpos = 0, int ypos = 0);


    /**
     * @brief Renders a JPEG image from a buffer in RAM | Renderiza uma imagem JPEG de um buffer na RAM
     * @param jpegBuf Pointer to the JPEG buffer | Ponteiro para o buffer JPEG
     * @param jpegLen Length of the JPEG buffer | Comprimento do buffer JPEG
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if the image was rendered successfully, false otherwise | Verdadeiro se a imagem foi renderizada com sucesso, falso caso contrário
    */
    bool renderJpegBuffer(const uint8_t* jpegBuf, size_t jpegLen, int xpos = 0, int ypos = 0);


    /**
     * @brief Renders a camera frame to the display | Renderiza um frame da câmera para o display
     * @param camera The camera object to use | O objeto da câmera a ser usado
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if the frame was rendered successfully, false otherwise | Verdadeiro se o frame foi renderizado com sucesso, falso caso contrário
    */
    bool renderCameraFrame(ES_Camera& camera, int xpos = 0, int ypos = 0);


    /**
     * @brief Renders the first JPEG file in a directory | Renderiza o primeiro arquivo JPEG em um diretório
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param directory The directory to search for JPEG files | O diretório para procurar arquivos JPEG
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if a JPEG file was found and rendered, false otherwise | Verdadeiro se um arquivo JPEG foi encontrado e renderizado, falso caso contrário
    */
    bool renderFirstFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0);
    /**
     * @brief Renders the last JPEG file in a directory | Renderiza o último arquivo JPEG em um diretório
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param directory The directory to search for JPEG files | O diretório para procurar arquivos JPEG
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if a JPEG file was found and rendered, false otherwise | Verdadeiro se um arquivo JPEG foi encontrado e renderizado, falso caso contrário
    */
    bool renderLastFileJPEG(fs::FS& fs, const String& directory = "/", int xpos = 0, int ypos = 0);
    /**
     * @brief Renders the next JPEG file based on the last rendered file | Renderiza o próximo arquivo JPEG com base no último arquivo renderizado
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param path The path to search for JPEG files | O caminho para procurar arquivos JPEG
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if a JPEG file was found and rendered, false otherwise | Verdadeiro se um arquivo JPEG foi encontrado e renderizado, falso caso contrário
    */
    bool renderNextFileJPEG(fs::FS& fs, const String& path = "", int xpos = 0, int ypos = 0);
    /**
     * @brief Renders the previous JPEG file based on the last rendered file | Renderiza o arquivo JPEG anterior com base no último arquivo renderizado
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param path The path to search for JPEG files | O caminho para procurar arquivos JPEG
     * @param xpos The horizontal position to render the image | A posição horizontal para renderizar a imagem
     * @param ypos The vertical position to render the image | A posição vertical para renderizar a imagem
     * @return True if a JPEG file was found and rendered, false otherwise | Verdadeiro se um arquivo JPEG foi encontrado e renderizado, falso caso contrário
     */
    bool renderPreviousFileJPEG(fs::FS& fs, const String& path = "", int xpos = 0, int ypos = 0);


    /**
     * @brief Loads a font file from the file system | Carrega um arquivo de fonte do sistema de arquivos
     * @param fs The file system to use | O sistema de arquivos a ser usado
     * @param fontName The name of the font file to load | O nome do arquivo de fonte a ser carregado
     * @return void | Retorna vazio
    */
    void loadFontFile(fs::FS& fs, const String& fontName);
    
};

#endif