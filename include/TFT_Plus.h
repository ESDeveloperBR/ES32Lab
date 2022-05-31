/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação.: 29/05/2020 (Derivada da LIB TFT_Pus v.0.2.0)
  Ultima Alteração: 31/05/20222
*/

#ifndef TFT_Plus_h
#define TFT_Plus_h

#include <Arduino.h>      //Biblioteca Arduino
#include <TFT_eSPI.h>     // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <JPEGDecoder.h>
#include "include/FileManager.h"

#define TFT_PULS_VERSION "0.3.1 update date 05/31/2022"

// Classe TFT_Plus 
class TFT_Plus{
    private:
      #define minimum(a,b)     (((a) < (b)) ? (a) : (b))
      boolean _trabalharComArquivos = false;
      FileManager _arquivo;
      boolean _compareStr(String str1, String str2);
      String  _fileNameRenderJPEG;
    
    public: 

      TFT_eSPI tft; // = TFT_eSPI(128, 460);  // Invoke library, pins defined in User_Setup.h

      TFT_Plus(void);                           /* Construtor */
      boolean begin();                          /* Inicializa a lib */
      void    setRotation(uint8_t r);           /* RotaÃƒÂ§ÃƒÂ£o da tela */
      void    fillScreen(uint32_t color);       /* Cor da tela de fundo */

      void    loadFontArray(const uint8_t array[]);
      void    loadFontFile(String fontName, boolean sdCard);

      void    unloadFont(void);                     /* Desvincula arquivo de font*/

      void    setCursor(int16_t x, int16_t y);      /* Coordenada do cursor no display */
      void    setTextColor(uint16_t fgcolor);         /* Cor do texto */
      void    setTextColor(uint16_t fgcolor, uint16_t bgcolor);

      size_t  print(String label);                  /* Exibe o texto no display */
      size_t  print(int16_t x, int16_t y, uint32_t color, String label, uint32_t bgcolor = 0);        /* Exibe o texto no display */
      size_t  print(int16_t x, int16_t y, String label);        /* Exibe o texto no display */
      size_t  print(uint32_t color, String label, uint32_t bgcolor = 0);        /* Exibe o texto no display */
      size_t  println(String label);                /* Exibe o texto no display com quebra de linha*/
      size_t  println(uint32_t color, String label, uint32_t bgcolor = 0);/* Exibe o texto no display */

      String  getFileNameRenderJPEG(void);
      boolean renderJPEG(String fileName, boolean sdCard, int xpos = 0, int ypos = 0);
      boolean renderFirstFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 );
      boolean renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 );
      boolean renderNextFileJPEG(int xpos = 0, int ypos = 0 );
      boolean renderBackFileJPEG(int xpos = 0, int ypos = 0 );
      
  };
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//********************************************** Implementação dos métodos da classe *********************************************************************
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Compara se as string sÃƒÂ£o iguais >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Compara se as string sÃƒÂ£o iguais
boolean TFT_Plus::_compareStr(String str1, String str2){
    str1.toUpperCase();
    str2.toUpperCase();
    if(str1 == str2) return true;
    else return false;
}

// <<<<<<<<< Construtor da Classe >>>>>>>>>>>>>>>>>>>>
TFT_Plus::TFT_Plus(void){
    /*
    Serial.println("Construtor");
    */
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Inicializa a lib TFT_Plus >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
//  Inicializa a lib TFT_Plus.
//  this.begin();
boolean TFT_Plus::begin(){  
    tft.begin();
    return true;
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< RotaÃƒÂ§ÃƒÂ£o da tela >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// RotaÃƒÂ§ÃƒÂ£o da tela
void TFT_Plus::setRotation(uint8_t r){  
    tft.setRotation(r);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Cor da tela de fundo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Cor da tela de fundo
void TFT_Plus::fillScreen(uint32_t color){  
    tft.fillScreen(color);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Carrega arquivo de font (letras) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Carrega um arquivo do tipo ARRAY com a fonte em questÃƒÂ£o. Ex.:
//
// #include <NotoSansBold36.h>
// this.loadFont(NotoSansBold36);
void TFT_Plus::loadFontArray(const uint8_t array[]){
    tft.loadFont(array);
}
// Carrega um arquivo salvo em um SD ou SPPIF do tipo fonte (.vlw)
void TFT_Plus::loadFontFile(String fontName, boolean sdCard){
    fontName.toLowerCase();

    /* Se o nome do arquivo comecar com '/' entÃƒÂ£o remova a '/' */
    if(fontName[0] == '/') fontName = fontName.substring(1, fontName.length());

    /* Se o nome do arquivo tiver extensÃƒÂ£o, remova */
    if(fontName.substring(fontName.length() - 4, fontName.length()) == ".vlw"){ 
        fontName = fontName.substring(0, fontName.length() - 4);
    }

    /* Escolhe se o arquivo esta em SD ou SPIFFS */
    _arquivo.begin(sdCard);
    if(sdCard) tft.loadFont(fontName, SD);
    else tft.loadFont(fontName, SPIFFS);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Desvincula arquivo de font >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Desvincula arquivo de font. Ex.: this.unloadFont();
void TFT_Plus::unloadFont(void){
    tft.unloadFont();
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Coordenada do cursor no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Coordenada do cursor no display
void TFT_Plus::setCursor(int16_t x, int16_t y){  
    tft.setCursor(x, y);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Cor do texto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Cor do texto
void TFT_Plus::setTextColor(uint16_t fgcolor){  
    tft.setTextColor(fgcolor);
}
void TFT_Plus::setTextColor(uint16_t fgcolor, uint16_t bgcolor){  
    tft.setTextColor(fgcolor, bgcolor);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe o texto no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe o texto no display
size_t TFT_Plus::print(String label){  
    return tft.print(label);
}
size_t TFT_Plus::print(int16_t x, int16_t y, uint32_t color, String label, uint32_t bgcolor){ 
    tft.setCursor(x, y);
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.print(label);
}
size_t TFT_Plus::print(int16_t x, int16_t y, String label){ 
    tft.setCursor(x, y);
    return tft.print(label);
}
size_t TFT_Plus::print(uint32_t color, String label, uint32_t bgcolor){ 
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.print(label);
}
/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe o texto no display com quebra de linha >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe o texto no display com quebra de linha
size_t TFT_Plus::println(String label){  
    return tft.println(label);
}
size_t TFT_Plus::println(uint32_t color, String label, uint32_t bgcolor){ 
//    tft.setTextColor(color, bgcolor);
    tft.setTextColor(color);
    return tft.println(label);
}


/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Retorna o nome do ultimo arquivo JPEG aberto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
// Retorna o nome do ultimo arquivo JPEG aberto
String TFT_Plus::getFileNameRenderJPEG(void){
    return _fileNameRenderJPEG;
}

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Exibe uma imagem JPG no display >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a partir de um arquivo em SPIFFs ou SD
// - fileName: Nome do arquivo a ser aberto
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderJPEG(String fileName, boolean sdCard, int xpos, int ypos) {
    /* Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg", encerre.  */
    if(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        return false;
    }

    _arquivo.begin(fileName, sdCard);

    if(!_arquivo.existe()) return false;

    JpegDec.decodeFsFile(_arquivo.getFile());

    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    bool swapBytes = tft.getSwapBytes();
    tft.setSwapBytes(true);
  
    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
    uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    // save the coordinate of the right and bottom edges to assist image cropping
    // to the screen size
    max_x += xpos;
    max_y += ypos;

    // Fetch data from the file, decode and display
    while (JpegDec.read()) {    // While there is more data in the file
        pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

        // Calculate coordinates of top left corner of current MCU
        int mcu_x = JpegDec.MCUx * mcu_w + xpos;
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;

        // check if the image block size needs to be changed for the right edge
        if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
        else win_w = min_w;

        // check if the image block size needs to be changed for the bottom edge
        if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
        else win_h = min_h;

        // copy pixels into a contiguous block
        if (win_w != mcu_w){
            uint16_t *cImg;
            int p = 0;
            cImg = pImg + win_w;
            for (int h = 1; h < win_h; h++){
                p += mcu_w;
                for (int w = 0; w < win_w; w++){
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        // draw image MCU block only if it will fit on the screen
        if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
            tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
        else if ( (mcu_y + win_h) >= tft.height())
            JpegDec.abort(); // Image has run off bottom of screen so abort decoding
    }
    tft.setSwapBytes(swapBytes);
    _fileNameRenderJPEG = fileName;
    return true;
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no PRIMEIRO arquivo do diretÃƒÂ³rio >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o PRIMEIRO arquivo no diretÃƒÂ³rio. SD ou SPPIFs
// - directory: Nome do diretÃƒÂ³rio com os arquivos a serem abertos
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos){
    String fileName = _arquivo.listaPrimeiroArquivoNome(directory, sdCard);
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaProximoArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }
    if(_arquivo.existe(fileName, sdCard)) _arquivo.begin(fileName, sdCard);
    return renderJPEG(_arquivo.getNomeArquivo(), sdCard, xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no ultimo arquivo do diretÃƒÂ³rio >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o ULTIMO arquivo no diretÃƒÂ³rio. SD ou SPPIFs
// - directory: Nome do diretÃƒÂ³rio com os arquivos a serem abertos
// - sdCard: SD = true / SPIFFs = false
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
boolean TFT_Plus::renderLastFileJPEG(String directory, boolean sdCard, int xpos, int ypos){
    String fileName = _arquivo.listaUltimoArquivoNome(directory, sdCard);
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaAnteriorArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }
    if(_arquivo.existe(fileName, sdCard)) _arquivo.begin(fileName, sdCard);
    return renderJPEG(_arquivo.getNomeArquivo(), sdCard, xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado no proximo arquivo do diretÃƒÂ³rio selecionado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o PROXIMO arquivo com base na ultima imagem aberta
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
// ATENCAO: A imagem sÃƒÂ³ serÃƒÂ¡ aberta apos a utilizaÃƒÂ§ÃƒÂ£o dos seguintes metodos, visto que ÃƒÂ© necessÃƒÂ¡rio um arquivo como referencia
//   ExecuÃƒÂ§ÃƒÂ£o obrigatÃƒÂ³ria de um dos mÃƒÂ©todos para referenciar um arquivo
//   - renderJPEG(String fileName, boolean sdCard, int xpos, int ypos)
//   - renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos)
//   - renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 )
boolean TFT_Plus::renderNextFileJPEG(int xpos, int ypos){
    String fileName = _arquivo.listaProximoArquivoNome();
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaProximoArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }

    if(_arquivo.existe(fileName)) _arquivo.setNomeArquivo(fileName);

    return renderJPEG(_arquivo.getNomeArquivo(), _arquivo.getSdCard(), xpos, ypos);
}

/* <<<<<<<<<<<< Exibe uma imagem JPG no display baseado arquivo ANTERIOR do diretÃƒÂ³rio selecionado >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
// Exibe uma imagem JPG no display a sendo o arquivo ANTERIOR com base na ultima imagem aberta
// - xpos: Referencia X no plano cartesiano do display
// - ypos: Referencia Y no plano cartesiano do display
// ATENCAO: A imagem sÃƒÂ³ serÃƒÂ¡ aberta apos a utilizaÃƒÂ§ÃƒÂ£o dos seguintes metodos, visto que ÃƒÂ© necessÃƒÂ¡rio um arquivo como referencia
//   ExecuÃƒÂ§ÃƒÂ£o obrigatÃƒÂ³ria de um dos mÃƒÂ©todos para referenciar um arquivo
//   - renderJPEG(String fileName, boolean sdCard, int xpos, int ypos)
//   - renderFirstFileJPEG(String directory, boolean sdCard, int xpos, int ypos)
//   - renderLastFileJPEG(String directory, boolean sdCard, int xpos = 0, int ypos = 0 )
boolean TFT_Plus::renderBackFileJPEG(int xpos, int ypos){
    String fileName = _arquivo.listaAnteriorArquivoNome();
    // Se o nome do arquivo nÃƒÂ£o tiver extensÃƒÂ£o ".jpg"
    while(!_compareStr(fileName.substring(fileName.length() - 4, fileName.length()), ".jpg") ){ 
        fileName = _arquivo.listaAnteriorArquivoNome(fileName);
        if( !_arquivo.existe(fileName) ) return false;
    }

    if(_arquivo.existe(fileName)) _arquivo.setNomeArquivo(fileName);

    return renderJPEG(_arquivo.getNomeArquivo(), _arquivo.getSdCard(), xpos, ypos);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#endif